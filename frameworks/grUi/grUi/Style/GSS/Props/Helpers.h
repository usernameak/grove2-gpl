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

#include "../Parser.h"

template <typename TProperty, typename TEnum>
class grUiGSSEnumPropValParser : public grUiGSSPropertyValueParser {
public:
    gnaStatus parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) override {
        using enum grUiGSSTokenizer::CSSTokenType;

        auto &tok = parser.consumeNextToken();
        if (tok.get_tokenType() == TT_IDENT) {
            TEnum value;
            if (stringToEnum(tok.tokenValue, value)) {
                property.value = gnaNew<TProperty>(value);
            } else {
                return { GNA_E_INVALID_CONFIG, gtl::String::format(GTXT("Unknown enum: %hs"), tok.tokenValue) };
            }
        } else {
            return { GNA_E_INVALID_CONFIG, GTXT("Invalid border-style value") };
        }

        return GNA_E_OK;
    }

    virtual bool stringToEnum(const gtl::PooledAString &str, TEnum &value) const = 0;
};

struct nxfRID;
struct grUiSprite;

namespace grUiGSSHelpers {
    gnaStatus GR_UI_DLLIMPEXP parseRID(nxfRID &rid, grUiGSSParser &parser);
    gnaStatus GR_UI_DLLIMPEXP parseSprite(const grUiGSSTokenizer::CSSToken &firstToken, grUiSprite &sprite, grUiGSSParser &parser);
}
