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

#include "Icon.h"
#include "Helpers.h"

GTL_RTTI_DEFINE(grUiGSSIconPropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

gnaStatus grUiGSSIconPropVal::Parser::parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) {
    using enum grUiGSSTokenizer::CSSTokenType;

    auto &tok = parser.consumeNextToken();
    {
        grUiSprite sprite;
        gnaStatus spriteStatus = grUiGSSHelpers::parseSprite(tok, sprite, parser);
        if (spriteStatus.errorCode != GNA_E_PARSE_WRONG_START_TOKEN) {
            GNA_CHECK_STATUS(spriteStatus);

            property.value = gnaNew<grUiGSSIconPropVal>(sprite);

            return GNA_E_OK;
        }
    }

    if (tok.tokenType == TT_IDENT && tok.tokenValue == "none") {
        property.value = gnaNew<grUiGSSIconPropVal>(grUiSprite{});
    } else {
        return { GNA_E_INVALID_CONFIG, GTXT("Expected -gr-sprite or none") };
    }

    return GNA_E_OK;
}
