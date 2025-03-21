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

#pragma once

#include <nxfIO/InputStream.h>
#include <grUi/UiDLL.h>
#include "Rule.h"

class grUiGSSParser;

class GR_UI_DLLIMPEXP grUiGSSTokenizer {
public:
    enum CSSTokenType : uint16_t {
        TT_EOF        = 0x00,
        TT_WHITESPACE = 0x01,
        TT_LPAREN     = 0x02,
        TT_RPAREN     = 0x03,
        TT_COMMA      = 0x04,
        TT_COLON      = 0x05,
        TT_SEMICOLON  = 0x06,
        TT_LBRACK     = 0x07,
        TT_RBRACK     = 0x08,
        TT_LBRACE     = 0x09,
        TT_RBRACE     = 0x0A,
        TT_DELIM      = 0x0B,
        TT_STRING     = 0x0C,
        TT_HASH       = 0x0D,
        TT_ATKEYWORD  = 0x0E,
        TT_NUMBER     = 0x0F,
        TT_PERCENTAGE = 0x10,
        TT_DIMENSION  = 0x11,
        TT_FUNCTION   = 0x12,
        TT_URL        = 0x13,
        TT_IDENT      = 0x14,

        TT_FLAG_ID    = 1u << 8u,
        TT_FLAG_FLOAT = 1u << 8u,

        TT_TYPE_MASK  = 0xFF,
        TT_FLAGS_MASK = 0xFFu << 8u
    };

    struct CSSToken {
        uint16_t tokenType;
        gtl::AString tokenValue;
        gtl::AString tokenUnit;

        CSSToken(uint16_t tokenType)
            : tokenType(tokenType) {}

        CSSToken(uint16_t tokenType, gtl::AString tokenValue)
            : tokenType(tokenType),
              tokenValue(tokenValue) {}

        CSSToken(uint16_t tokenType, gtl::AString tokenValue, gtl::AString tokenUnit)
            : tokenType(tokenType),
              tokenValue(tokenValue),
              tokenUnit(tokenUnit) {}

        uint16_t get_tokenType() const {
            return tokenType & TT_TYPE_MASK;
        }

        uint16_t get_tokenFlags() const {
            return tokenType & TT_FLAGS_MASK;
        }
    };

private:
    gtl::AString m_chars;
    uint32_t m_currentCharIndex;

    grUiGSSParser &m_parser;

public:
    grUiGSSTokenizer(grUiGSSParser &parser) : m_currentCharIndex(0), m_parser(parser) {}

    void setChars(gtl::AString str);

    gnaStatus tokenize();

    static const gtl::ASCIICHAR *stringifyTokenType(uint16_t tokenType);

private:
    static bool isWhitespace(int32_t c);
    static bool isIdentStart(int32_t c);
    static bool isIdent(int32_t c);
    static bool isDigit(int32_t c);

    int32_t consumeNextCodePoint();
    int32_t peekNextCodePoint(int32_t index = 0);
    void consumeCodePoints(int amount);
    void reconsumeCodePoint();

    bool peekIsValidEscape(int32_t index = 0);
    bool peekIsIdentSequenceStart(int32_t index = 0);
    bool peekIsNumber(int32_t index = 0);

    gnaStatus consumeEscapedCodePoint(gtl::AString &outStr);
    gnaStatus consumeIdentSequence(gtl::AString &outStr);
    gnaStatus consumeNumber(gtl::AString &outStr, bool &isFloat);

    gnaStatus tokenizeStringToken(int32_t endingCodePoint);
    gnaStatus tokenizeNumberToken();
    gnaStatus tokenizeIdentLikeToken();
    gnaStatus tokenizeURLToken();

    const CSSToken &consumeNextToken();
    const CSSToken &peekNextToken();
    void reconsumeToken();

    void swallowWhitespaceTokens();

    gnaStatus parseRule(grUiGSSRule &rule);
    gnaStatus parseSelector(grUiGSSSelectors::ComplexSelector &selector);
};
