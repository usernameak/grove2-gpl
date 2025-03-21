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
#include <gtlUtil/Singleton.h>
#include "Rule.h"
#include "Tokenizer.h"

class GR_UI_DLLIMPEXP grUiGSSParser {
    using enum grUiGSSTokenizer::CSSTokenType;
    using CSSToken = grUiGSSTokenizer::CSSToken;

    std::vector<grUiGSSTokenizer::CSSToken> m_tokens;
    uint32_t m_currentTokenIndex;

    static grUiGSSTokenizer::CSSToken st_eofToken;

public:
    grUiGSSParser() : m_currentTokenIndex(0) {}

    gnaStatus parse(std::vector<grUiGSSRule> &ruleList);

    void addToken(const grUiGSSTokenizer::CSSToken &token) {
        m_tokens.push_back(token);
    }

    void addToken(grUiGSSTokenizer::CSSToken &&token) {
        m_tokens.push_back(token);
    }

    const grUiGSSTokenizer::CSSToken &consumeNextToken();
    const grUiGSSTokenizer::CSSToken &peekNextToken() const;
    void reconsumeToken();

    void swallowWhitespaceTokens();
    gnaStatus parseComma();
    gnaStatus parseFloat(float &fValue);

    bool peekIsUrl() const;
    gnaStatus parseUrl(gtl::AString &url);

private:
    gnaStatus parseRule(grUiGSSRule &rule);
    gnaStatus parseSelector(grUiGSSSelectors::ComplexSelector &selector);
};

class grUiGSSPropertyValueParserBase : public gtlRcObject {
public:
    virtual ~grUiGSSPropertyValueParserBase() = default;

    virtual gnaStatus parseProperty(grUiGSSRule &rule, gtl::PooledAString name, grUiGSSParser &parser) = 0;
};

class grUiGSSPropertyValueParser : public grUiGSSPropertyValueParserBase {
public:
    virtual ~grUiGSSPropertyValueParser() = default;

    virtual gnaStatus parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) = 0;

    gnaStatus parseProperty(grUiGSSRule &rule, gtl::PooledAString name, grUiGSSParser &parser) override;
};

class GR_UI_DLLIMPEXP grUiGSSPropertyValueParserRegistry {
    std::unordered_map<gtl::PooledAString, gnaPointer<grUiGSSPropertyValueParserBase>> m_parsers;

public:
    void registerParser(gtl::PooledAString propertyName, gnaPointer<grUiGSSPropertyValueParserBase> parser);
    void unregisterParser(gtl::PooledAString propertyName);
    gnaWeakPointer<grUiGSSPropertyValueParserBase> findParser(gtl::PooledAString propertyName);

    static void staticInit();
    static void staticRelease();
};

GNA_SINGLETON_EXPORTED_DECLARE(GR_UI_DLLIMPEXP, grUiGSSPropertyValueParserRegistry);
