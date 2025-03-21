// GroveEngine 2
// Copyright (C) 2020-2025 usernameak
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License, version 3, as
// published by the Free Software Foundation.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "Tokenizer.h"
#include "Parser.h"
#include "Utils.h"

void grUiGSSTokenizer::setChars(gtl::AString str) {
    m_chars            = str;
    m_currentCharIndex = 0;
}

int32_t grUiGSSTokenizer::consumeNextCodePoint() {
    if (m_currentCharIndex >= m_chars.size()) {
        return -1; // EOF
    }
    return static_cast<unsigned char>(m_chars[m_currentCharIndex++]);
}

int32_t grUiGSSTokenizer::peekNextCodePoint(int32_t index) {
    if (m_currentCharIndex + index >= m_chars.size()) [[unlikely]] {
        return -1; // EOF
    }
    return static_cast<unsigned char>(m_chars[m_currentCharIndex + index]);
}

void grUiGSSTokenizer::consumeCodePoints(int amount) {
    m_currentCharIndex += amount;
    if (m_currentCharIndex > m_chars.size()) {
        m_currentCharIndex = m_chars.size();
    }
}

void grUiGSSTokenizer::reconsumeCodePoint() {
    if (m_currentCharIndex == 0) [[unlikely]] {
        GR_FATAL(GTXT("Reconsuming a code point from empty CSS stream"));
    }
    m_currentCharIndex--;
}

bool grUiGSSTokenizer::peekIsValidEscape(int32_t index) {
    return peekNextCodePoint(index + 0) == '\\' && peekNextCodePoint(index + 1) != '\n';
}

bool grUiGSSTokenizer::peekIsIdentSequenceStart(int32_t index) {
    int32_t c0 = peekNextCodePoint(index + 0);
    int32_t c1 = peekNextCodePoint(index + 1);
    if (c0 == '-') {
        return isIdentStart(c1) || peekIsValidEscape(index + 1);
    } else if (isIdentStart(c0)) {
        return true;
    } else if (peekIsValidEscape(index + 0)) {
        return true;
    } else {
        return false;
    }
}

bool grUiGSSTokenizer::peekIsNumber(int32_t index) {
    int32_t c0 = peekNextCodePoint(index + 0);
    int32_t c1 = peekNextCodePoint(index + 1);
    int32_t c2 = peekNextCodePoint(index + 2);
    if (c0 == '+' || c0 == '-') {
        if (isDigit(c1)) {
            return true;
        } else if (c1 == '.' && isDigit(c2)) {
            return true;
        } else {
            return false;
        }
    } else if (c0 == '.' && isDigit(c1)) {
        return true;
    } else if (isDigit(c0)) {
        return true;
    } else {
        return false;
    }
}

bool grUiGSSTokenizer::isWhitespace(int32_t c) {
    return c == ' ' || c == '\n' || c == '\r' || c == '\t';
}

bool grUiGSSTokenizer::isIdentStart(int32_t c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_' || c >= 0x80;
}

bool grUiGSSTokenizer::isIdent(int32_t c) {
    return isIdentStart(c) || (c >= '0' && c <= '9') || c == '-';
}

bool grUiGSSTokenizer::isDigit(int32_t c) {
    return c >= '0' && c <= '9';
}

gnaStatus grUiGSSTokenizer::tokenize() {
    while (true) {
        // consume comments
        if (m_chars.size() >= m_currentCharIndex + 2) {
            if (m_chars[m_currentCharIndex] == '/' &&
                m_chars[m_currentCharIndex + 1] == '*') {
                consumeCodePoints(2);
                while (true) {
                    int32_t c = consumeNextCodePoint();
                    if (c == -1) {
                        return { GNA_E_INVALID_CONFIG, GTXT("Unterminated comment") };
                    } else if (c == '*') {
                        if (peekNextCodePoint() == '/') {
                            consumeCodePoints(1);
                            break;
                        }
                    }
                }
                continue;
            }
        }

        // consume the next input code point
        int32_t c = consumeNextCodePoint();

        // consume as much whitespace as possible
        if (isWhitespace(c)) {
            do {
                c = consumeNextCodePoint();
            } while (isWhitespace(c));

            m_parser.addToken({ TT_WHITESPACE });

            if (c != -1) {
                reconsumeCodePoint();
            }
            continue;
        }

        if (c == '"' || c == '\'') {
            GNA_CHECK_STATUS(tokenizeStringToken(c));
        } else if (c == '#') {
            if (isIdent(peekNextCodePoint()) || peekIsValidEscape()) {
                uint16_t tokenType = TT_HASH;
                if (peekIsIdentSequenceStart()) {
                    tokenType |= TT_FLAG_ID;
                }
                gtl::AString str;
                GNA_CHECK_STATUS(consumeIdentSequence(str));
                m_parser.addToken({ tokenType, str });
            } else {
                m_parser.addToken({ TT_DELIM, "#" });
            }
        } else if (c == '(') {
            m_parser.addToken({ TT_LPAREN });
        } else if (c == ')') {
            m_parser.addToken({ TT_RPAREN });
        } else if (c == '+') {
            if (peekIsNumber(-1)) {
                reconsumeCodePoint();
                GNA_CHECK_STATUS(tokenizeNumberToken());
            } else {
                m_parser.addToken({ TT_DELIM, "+" });
            }
        } else if (c == ',') {
            m_parser.addToken({ TT_COMMA });
        } else if (c == '-') {
            // CDC/CDO tokens are not supported
            if (peekIsNumber(-1)) {
                reconsumeCodePoint();
                GNA_CHECK_STATUS(tokenizeNumberToken());
            } else if (peekIsIdentSequenceStart(-1)) {
                reconsumeCodePoint();
                GNA_CHECK_STATUS(tokenizeIdentLikeToken());
            } else {
                m_parser.addToken({ TT_DELIM, "-" });
            }
        } else if (c == '.') {
            if (peekIsNumber(-1)) {
                reconsumeCodePoint();
                GNA_CHECK_STATUS(tokenizeNumberToken());
            } else {
                m_parser.addToken({ TT_DELIM, "." });
            }
        } else if (c == ':') {
            m_parser.addToken({ TT_COLON });
        } else if (c == ';') {
            m_parser.addToken({ TT_SEMICOLON });
        } else if (c == '@') {
            if (peekIsIdentSequenceStart()) {
                gtl::AString str;
                GNA_CHECK_STATUS(consumeIdentSequence(str));
                m_parser.addToken({ TT_ATKEYWORD, str });
            } else {
                m_parser.addToken({ TT_DELIM });
            }
        } else if (c == '[') {
            m_parser.addToken({ TT_LBRACK });
        } else if (c == ']') {
            m_parser.addToken({ TT_RBRACK });
        } else if (c == '{') {
            m_parser.addToken({ TT_LBRACE });
        } else if (c == '}') {
            m_parser.addToken({ TT_RBRACE });
        } else if (c >= '0' && c <= '9') {
            reconsumeCodePoint();
            GNA_CHECK_STATUS(tokenizeNumberToken());
        } else if (isIdentStart(c)) {
            reconsumeCodePoint();
            GNA_CHECK_STATUS(tokenizeIdentLikeToken());
        } else if (c == -1) {
            break;
        } else {
            gtl::ASCIICHAR ac = static_cast<unsigned char>(c);
            m_parser.addToken({ TT_DELIM, gtl::AString(&ac, 1) });
        }
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::consumeEscapedCodePoint(gtl::AString &outStr) {
    int32_t c = consumeNextCodePoint();
    if (c == -1) {
        return { GNA_E_INVALID_CONFIG, GTXT("EOF after escape character") };
    } else if (grUiGSSUtils::isHexDigit(c)) {
        uint32_t value = grUiGSSUtils::decodeHexDigit(c);
        for (int i = 1; i < 6; i++) {
            c = peekNextCodePoint();
            if (!grUiGSSUtils::isHexDigit(c)) break;
            consumeCodePoints(1);

            value <<= 4;
            value |= grUiGSSUtils::decodeHexDigit(c);
        }

        if (value >= 0x80) {
            // TODO: proper unicode support

            return { GNA_E_INVALID_CONFIG, GTXT("CSS parser does not currently support Unicode escapes") };
        }

        outStr += (gtl::ASCIICHAR)value;
    } else {
        outStr += (gtl::ASCIICHAR)(unsigned char)c;
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::consumeIdentSequence(gtl::AString &outStr) {
    while (true) {
        // consume the next input code point
        int32_t c = consumeNextCodePoint();

        if (isIdent(c)) {
            outStr += (gtl::ASCIICHAR)(unsigned char)c;
        } else {
            if (peekIsValidEscape(-1)) {
                GNA_CHECK_STATUS(consumeEscapedCodePoint(outStr));
            } else {
                reconsumeCodePoint();
                break;
            }
        }
    }
    return GNA_E_OK;
}

#define GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr) outStr += (gtl::ASCIICHAR)(unsigned char)consumeNextCodePoint()

gnaStatus grUiGSSTokenizer::consumeNumber(gtl::AString &outStr, bool &isFloat) {
    isFloat = false;

    if (peekNextCodePoint() == '+' || peekNextCodePoint() == '-') {
        GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
    }
    while (isDigit(peekNextCodePoint())) {
        GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
    }
    if (peekNextCodePoint(0) == '.' && isDigit(peekNextCodePoint(1))) {
        GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
        GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);

        isFloat = true;
        while (isDigit(peekNextCodePoint())) {
            GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
        }
    }
    if (peekNextCodePoint(0) == 'e' || peekNextCodePoint(0) == 'E') {
        bool foundExp = false;
        if ((peekNextCodePoint(1) == '-' || peekNextCodePoint(1) == '+') && isDigit(peekNextCodePoint(2))) {
            GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
            GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
            isFloat  = true;
            foundExp = true;
        } else if (isDigit(peekNextCodePoint(1))) {
            GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
            isFloat  = true;
            foundExp = true;
        }
        if (foundExp) {
            while (isDigit(peekNextCodePoint())) {
                GSSPARSER_EMIT_CODEPOINT_TO_STRING(outStr);
            }
        }
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::tokenizeStringToken(int32_t endingCodePoint) {
    gtl::AString finalString;

    while (true) {
        // consume the next input code point
        int32_t c = consumeNextCodePoint();

        if (c == endingCodePoint) {
            m_parser.addToken({ TT_STRING, finalString });
            break;
        } else if (c == -1) {
            return { GNA_E_INVALID_CONFIG, GTXT("EOF inside an unterminated string") };
        } else if (c == '\n' || c == '\r') {
            return { GNA_E_INVALID_CONFIG, GTXT("Newline inside an unterminated string") };
        } else if (c == '\\') {
            int32_t c1 = peekNextCodePoint();
            if (c1 == -1) {
                continue;
            } else if (c1 == '\r' && peekNextCodePoint(1) == '\n') {
                consumeCodePoints(2);
                continue;
            } else if (c1 == '\n') {
                consumeCodePoints(1);
                continue;
            } else {
                GNA_CHECK_STATUS(consumeEscapedCodePoint(finalString));
            }
        } else {
            finalString += (gtl::ASCIICHAR)c;
        }
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::tokenizeNumberToken() {
    bool isFloat = false;
    gtl::AString repr;
    GNA_CHECK_STATUS(consumeNumber(repr, isFloat));

    uint16_t flags = isFloat ? TT_FLAG_FLOAT : 0;

    if (peekIsIdentSequenceStart()) {
        gtl::AString unit;
        GNA_CHECK_STATUS(consumeIdentSequence(unit));

        m_parser.addToken({ static_cast<uint16_t>(TT_DIMENSION | flags), repr, unit });
    } else if (peekNextCodePoint() == '%') {
        consumeCodePoints(1);

        m_parser.addToken({ static_cast<uint16_t>(TT_PERCENTAGE | flags), repr });
    } else {
        m_parser.addToken({ static_cast<uint16_t>(TT_NUMBER | flags), repr });
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::tokenizeIdentLikeToken() {
    gtl::AString ident;
    GNA_CHECK_STATUS(consumeIdentSequence(ident));

    if (peekNextCodePoint() == '(') {
        consumeCodePoints(1);
        if (ident.toLowerCase() == "url") {
            while (isWhitespace(peekNextCodePoint(0)) && isWhitespace(peekNextCodePoint(1))) {
                consumeCodePoints(1);
            }
            if (isWhitespace(peekNextCodePoint(0)) && (peekNextCodePoint(1) == '\'' || peekNextCodePoint(1) == '"') ||
                (peekNextCodePoint(0) == '\'' || peekNextCodePoint(0) == '"')) {
                m_parser.addToken({ static_cast<uint16_t>(TT_FUNCTION), ident });
            } else {
                GNA_CHECK_STATUS(tokenizeURLToken());
            }
        } else {
            m_parser.addToken({ static_cast<uint16_t>(TT_FUNCTION), ident });
        }
    } else {
        m_parser.addToken({ static_cast<uint16_t>(TT_IDENT), ident });
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSTokenizer::tokenizeURLToken() {
    while (isWhitespace(peekNextCodePoint())) {
        consumeNextCodePoint();
    }
    gtl::AString outStr;
    while (true) {
        int32_t c = consumeNextCodePoint();
        if (isWhitespace(c)) {
            while (isWhitespace(peekNextCodePoint())) {
                consumeNextCodePoint();
            }
            if (peekNextCodePoint() != ')') {
                return { GNA_E_INVALID_CONFIG, GTXT("Stray whitespace inside an URL") };
            }
        } else if (c == '"' || c == '\'' || c == '(' || (c >= 0x00 && c <= 0x08) || c == 0x0B || (c >= 0x0E && c <= 0x1F) || c == 0x7F) {
            return { GNA_E_INVALID_CONFIG, GTXT("Invalid character inside an URL") };
        } else if (c == -1) {
            return { GNA_E_INVALID_CONFIG, GTXT("Unterminated URL") };
        } else if (c == '\\') {
            if (peekIsValidEscape(-1)) {
                GNA_CHECK_STATUS(consumeEscapedCodePoint(outStr));
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Invalid escape inside of an URL") };
            }
        } else if (c == ')') {
            m_parser.addToken({ static_cast<uint16_t>(TT_URL), outStr });
            break;
        } else {
            outStr += (gtl::ASCIICHAR)(unsigned char)c;
        }
    }
    return GNA_E_OK;
}

const gtl::ASCIICHAR *grUiGSSTokenizer::stringifyTokenType(uint16_t tokenType) {
    switch (tokenType & TT_TYPE_MASK) {
    case TT_EOF: return "TT_EOF";
    case TT_WHITESPACE: return "TT_WHITESPACE";
    case TT_LPAREN: return "TT_LPAREN";
    case TT_RPAREN: return "TT_RPAREN";
    case TT_COMMA: return "TT_COMMA";
    case TT_COLON: return "TT_COLON";
    case TT_SEMICOLON: return "TT_SEMICOLON";
    case TT_LBRACK: return "TT_LBRACK";
    case TT_RBRACK: return "TT_RBRACK";
    case TT_LBRACE: return "TT_LBRACE";
    case TT_RBRACE: return "TT_RBRACE";
    case TT_DELIM: return "TT_DELIM";
    case TT_STRING: return "TT_STRING";
    case TT_HASH: return "TT_HASH";
    case TT_ATKEYWORD: return "TT_ATKEYWORD";
    case TT_NUMBER: return "TT_NUMBER";
    case TT_PERCENTAGE: return "TT_PERCENTAGE";
    case TT_DIMENSION: return "TT_DIMENSION";
    case TT_FUNCTION: return "TT_FUNCTION";
    case TT_URL: return "TT_URL";
    case TT_IDENT: return "TT_IDENT";
    default: return "TT_UNKNOWN";
    }
}
