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

#include "Parser.h"
#include "Selector.h"

#include "Props/Color.h"
#include "Props/Background.h"
#include "Props/Unit.h"
#include "Props/Border.h"
#include "Props/TextAlign.h"
#include "Props/Icon.h"
#include "Props/Font.h"
#include "Props/Padding.h"

grUiGSSParser::CSSToken grUiGSSParser::st_eofToken{ TT_EOF };

const grUiGSSParser::CSSToken &grUiGSSParser::consumeNextToken() {
    if (m_currentTokenIndex >= m_tokens.size()) {
        return st_eofToken; // EOF
    }
    return m_tokens[m_currentTokenIndex++];
}

const grUiGSSParser::CSSToken &grUiGSSParser::peekNextToken() const {
    if (m_currentTokenIndex >= m_tokens.size()) {
        return st_eofToken; // EOF
    }
    return m_tokens[m_currentTokenIndex];
}

void grUiGSSParser::reconsumeToken() {
    if (m_currentTokenIndex == 0) [[unlikely]] {
        GR_FATAL(GTXT("Reconsuming a token from empty CSS stream"));
    }
    m_currentTokenIndex--;
}

void grUiGSSParser::swallowWhitespaceTokens() {
    while (peekNextToken().get_tokenType() == TT_WHITESPACE) {
        consumeNextToken();
    }
}

gnaStatus grUiGSSParser::parseComma() {
    swallowWhitespaceTokens();
    auto &commaTok = consumeNextToken();
    if (commaTok.get_tokenType() != TT_COMMA) {
        return { GNA_E_INVALID_CONFIG, GTXT("Expected comma") };
    }
    swallowWhitespaceTokens();
    return GNA_E_OK;
}

gnaStatus grUiGSSParser::parseFloat(float &fValue) {
    auto &token = consumeNextToken();

    if (token.get_tokenType() == TT_NUMBER) {
        double dValue;
        bool result = token.tokenValue.toDouble(dValue);
        if (!result)
            return { GNA_E_INVALID_CONFIG, GTXT("Float specification: cannot decode float value") };
        if (isnan(dValue))
            return { GNA_E_INVALID_CONFIG, GTXT("Float specification: NaN value") };

        fValue = (float)dValue;
    }
    return GNA_E_OK;
}

bool grUiGSSParser::peekIsUrl() const {
    auto &tok = peekNextToken();
    return tok.get_tokenType() == TT_URL || (tok.get_tokenType() == TT_FUNCTION && tok.tokenValue.toLowerCase() == "url");
}

gnaStatus grUiGSSParser::parseUrl(gtl::AString &url) {
    auto &funcTok = consumeNextToken();
    if (funcTok.get_tokenType() == TT_URL) {
        url = funcTok.tokenValue;
        return GNA_E_OK;
    } else if (funcTok.get_tokenType() == TT_FUNCTION && funcTok.tokenValue.toLowerCase() == "url") {
        swallowWhitespaceTokens();

        auto &strTok = consumeNextToken();
        if (strTok.get_tokenType() != TT_STRING) {
            return { GNA_E_INVALID_CONFIG, GTXT("Expected a string in url()") };
        }
        url = strTok.tokenValue;

        swallowWhitespaceTokens();

        if (consumeNextToken().get_tokenType() != TT_RPAREN) {
            return { GNA_E_INVALID_CONFIG, GTXT("Expected ) after url") };
        }

        return GNA_E_OK;
    } else {
        return { GNA_E_INVALID_CONFIG, GTXT("Expected an url") };
    }
}

gnaStatus grUiGSSParser::parse(std::vector<grUiGSSRule> &ruleList) {
    while (true) {
        const auto &tok = consumeNextToken();
        switch (tok.get_tokenType()) {
        case TT_WHITESPACE:
            break;
        case TT_EOF:
            return GNA_E_OK;
        default:
            reconsumeToken();
            GNA_CHECK_STATUS(parseRule(ruleList.emplace_back()));
            break;
        }
    }
}

gnaStatus grUiGSSParser::parseRule(grUiGSSRule &rule) {
    do {
        swallowWhitespaceTokens();

        grUiGSSSelectors::ComplexSelector selector;

        GNA_CHECK_STATUS(parseSelector(selector));
        if (selector.empty()) {
            return { GNA_E_INVALID_CONFIG, GTXT("Got an empty selector in a CSS rule") };
        }

        rule.selectorList.push_back(std::move(selector));

        swallowWhitespaceTokens();
    } while (consumeNextToken().get_tokenType() == TT_COMMA);

    reconsumeToken();
    const auto &lbraceTok = consumeNextToken();
    if (lbraceTok.get_tokenType() != TT_LBRACE) {
        return { GNA_E_INVALID_CONFIG, GTXT("Expected left brace after a CSS rule") };
    }

    // parse the actual property list
    while (true) {
        swallowWhitespaceTokens();

        gtl::PooledAString propName;

        auto &startTok = consumeNextToken();
        if (startTok.get_tokenType() == TT_IDENT) {
            propName = startTok.tokenValue;
        } else if (startTok.get_tokenType() == TT_RBRACE) {
            break;
        } else {
            return { GNA_E_INVALID_CONFIG, GTXT("Expected a } or a property name") };
        }

        swallowWhitespaceTokens();

        auto &colonTok = consumeNextToken();
        if (colonTok.get_tokenType() != TT_COLON) {
            return { GNA_E_INVALID_CONFIG, GTXT("Expected a colon after property name") };
        }

        swallowWhitespaceTokens();

        auto parser = gnaSingleton<grUiGSSPropertyValueParserRegistry>()->findParser(propName);
        if (!parser) {
            return { GNA_E_INVALID_CONFIG, gtl::String::format(GTXT("Unsupported property %hs"), propName.toCString()) };
        }
        GNA_CHECK_STATUS(parser->parseProperty(rule, propName, *this));

        auto &semiTok = consumeNextToken();
        if (semiTok.get_tokenType() != TT_SEMICOLON) {
            return { GNA_E_INVALID_CONFIG, GTXT("Expected a semicolon after property value") };
        }
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSParser::parseSelector(grUiGSSSelectors::ComplexSelector &selector) {
    struct SelectorBuilder {
        grUiGSSSelectors::ComplexSelector selector;

        grUiGSSSelectors::CompoundSelector &currentCompoundSelector() {
            if (selector.compoundSelectors.empty()) {
                return newCompoundSelector();
            } else {
                return selector.compoundSelectors.back();
            }
        }

        grUiGSSSelectors::CompoundSelector &newCompoundSelector() {
            if (!selector.compoundSelectors.empty() && selector.compoundSelectors.back().selectors.empty()) {
                return selector.compoundSelectors.back();
            }
            return selector.compoundSelectors.emplace_back();
        }

        grUiGSSSelectors::ComplexSelector &&build() {
            return std::move(selector);
        }
    } builder;

    while (true) {
        const auto &tok = consumeNextToken();
        switch (tok.get_tokenType()) {
        case TT_IDENT: {
            auto &vSelectors = builder.currentCompoundSelector().selectors;
            if (vSelectors.empty()) {
                auto &sel = vSelectors.emplace_back();
                sel.type  = grUiGSSSelectors::Selector::TYPE_ELEMENT;
                sel.name  = tok.tokenValue;
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Unexpected identifier") };
            }
            break;
        }
        case TT_COLON: {
            auto &vSelectors  = builder.currentCompoundSelector().selectors;
            auto &sel         = vSelectors.emplace_back();
            sel.type          = grUiGSSSelectors::Selector::TYPE_PSEUDOCLASS;
            const auto &idTok = consumeNextToken();
            if (idTok.get_tokenType() != TT_IDENT) {
                return { GNA_E_INVALID_CONFIG, GTXT("Expected identifier") };
            }
            sel.name = idTok.tokenValue;
            break;
        }
        case TT_DELIM: {
            if (tok.tokenValue == ".") {
                auto &vSelectors = builder.currentCompoundSelector().selectors;
                auto &sel        = vSelectors.emplace_back();
                sel.type         = grUiGSSSelectors::Selector::TYPE_CLASS;

                const auto &idTok = consumeNextToken();
                if (idTok.get_tokenType() != TT_IDENT) {
                    return { GNA_E_INVALID_CONFIG, GTXT("Expected identifier") };
                }

                sel.name = idTok.tokenValue;
            } else if (tok.tokenValue == "*") {
                auto &vSelectors = builder.currentCompoundSelector().selectors;
                auto &sel        = vSelectors.emplace_back();
                sel.type         = grUiGSSSelectors::Selector::TYPE_ANY;
            } else if (tok.tokenValue == ">") {
                if (builder.selector.empty()) {
                    return { GNA_E_INVALID_CONFIG, GTXT("Selector cannot start with child combinator") };
                }

                if (!builder.selector.cleanupExtraneousSelectors()) {
                    return { GNA_E_INVALID_CONFIG, GTXT("Selector cannot have multiple combinators in a row") };
                }

                auto &combinator = builder.currentCompoundSelector().combinator;

                // should be true unless cleanupExtraneousSelectors failed above
                assert(combinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_NONE);
                combinator = grUiGSSSelectors::CompoundSelector::COMBINATOR_CHILD;

                builder.newCompoundSelector();

                // swallow the remaining whitespaces
                swallowWhitespaceTokens();
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Invalid token in selector") };
            }
            break;
        }
        case TT_HASH: {
            if (tok.get_tokenFlags() & TT_FLAG_ID) {
                auto &vSelectors = builder.currentCompoundSelector().selectors;
                auto &sel        = vSelectors.emplace_back();
                sel.type         = grUiGSSSelectors::Selector::TYPE_ID;
                sel.name         = tok.tokenValue;
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Invalid #id") };
            }
            break;
        }
        case TT_WHITESPACE: {
            if (builder.currentCompoundSelector().combinator == grUiGSSSelectors::CompoundSelector::COMBINATOR_NONE) {
                builder.currentCompoundSelector().combinator = grUiGSSSelectors::CompoundSelector::COMBINATOR_DESCENDANT;
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Selector cannot have multiple combinators in a row") };
            }
            builder.newCompoundSelector();

            break;
        }
        default:
            reconsumeToken();
            goto endBuild;
        }
    }

endBuild:
    if (!builder.selector.cleanupExtraneousSelectors()) {
        return { GNA_E_INVALID_CONFIG, GTXT("Selector cannot have end with a combinator") };
    }

    selector = builder.build();

    return GNA_E_OK;
}

gnaStatus grUiGSSPropertyValueParser::parseProperty(grUiGSSRule &rule, gtl::PooledAString name, grUiGSSParser &parser) {
    auto &property = rule.properties.emplace_back();
    property.name  = name;

    return parseValue(property, parser);
}

GNA_SINGLETON_LATEINIT_IMPLEMENT(grUiGSSPropertyValueParserRegistry);

void grUiGSSPropertyValueParserRegistry::registerParser(
    gtl::PooledAString propertyName,
    gnaPointer<grUiGSSPropertyValueParserBase> parser) {

    assert(m_parsers.find(propertyName) == m_parsers.end());
    m_parsers.emplace(propertyName, std::move(parser));
}

void grUiGSSPropertyValueParserRegistry::unregisterParser(gtl::PooledAString propertyName) {
    m_parsers.erase(propertyName);
}

gnaWeakPointer<grUiGSSPropertyValueParserBase> grUiGSSPropertyValueParserRegistry::findParser(gtl::PooledAString propertyName) {
    auto it = m_parsers.find(propertyName);
    if (it == m_parsers.end()) return nullptr;
    return it->second;
}

void grUiGSSPropertyValueParserRegistry::staticInit() {
    GNA_SINGLETON_LATEINIT_INIT(grUiGSSPropertyValueParserRegistry);

    auto *registry = gnaSingleton<grUiGSSPropertyValueParserRegistry>();

    registry->registerParser("background-image", gnaNew<grUiGSSBackgroundImagePropVal::Parser>());
    registry->registerParser("background-color", gnaNew<grUiGSSColorPropVal::Parser>());
    registry->registerParser("color", gnaNew<grUiGSSColorPropVal::Parser>());

    registry->registerParser("border-style", gnaNew<grUiGSSBorderTypePropVal::Parser>());
    registry->registerParser("border-width", gnaNew<grUiGSSUnitIPropVal::Parser>());
    registry->registerParser("border-color", gnaNew<grUiGSSColorPropVal::Parser>());

    registry->registerParser("text-align", gnaNew<grUiGSSTextAlignPropVal::Parser>());
    registry->registerParser("vertical-align", gnaNew<grUiGSSVerticalAlignPropVal::Parser>());

    registry->registerParser("padding", gnaNew<grUiGSSPaddingPropParser>());
    registry->registerParser("padding-left", gnaNew<grUiGSSUnitIPropVal::Parser>());
    registry->registerParser("padding-top", gnaNew<grUiGSSUnitIPropVal::Parser>());
    registry->registerParser("padding-right", gnaNew<grUiGSSUnitIPropVal::Parser>());
    registry->registerParser("padding-bottom", gnaNew<grUiGSSUnitIPropVal::Parser>());

    registry->registerParser("-gr-icon", gnaNew<grUiGSSIconPropVal::Parser>());

    registry->registerParser("font-family", gnaNew<grUiGSSFontFamilyPropVal::Parser>());
    registry->registerParser("font-size", gnaNew<grUiGSSUnitFPropVal::Parser>());
}

void grUiGSSPropertyValueParserRegistry::staticRelease() {
    auto *registry = gnaSingleton<grUiGSSPropertyValueParserRegistry>();

    registry->unregisterParser("background-image");
    registry->unregisterParser("background-color");
    registry->unregisterParser("color");

    registry->unregisterParser("border-style");
    registry->unregisterParser("border-width");
    registry->unregisterParser("border-color");

    registry->unregisterParser("text-align");
    registry->unregisterParser("vertical-align");

    registry->unregisterParser("padding");
    registry->unregisterParser("padding-left");
    registry->unregisterParser("padding-top");
    registry->unregisterParser("padding-right");
    registry->unregisterParser("padding-bottom");

    registry->unregisterParser("-gr-icon");

    registry->unregisterParser("font-family");
    registry->unregisterParser("font-size");

    GNA_SINGLETON_LATEINIT_RELEASE(grUiGSSPropertyValueParserRegistry);
}
