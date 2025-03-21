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

#include "Background.h"

#include "../Utils.h"
#include "Helpers.h"
#include <grUi/Style/Background/BackgroundMultipatch.h>
#include <grUi/Style/Background/Background.h>

GTL_RTTI_DEFINE(grUiGSSBackgroundImagePropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

gnaStatus grUiGSSBackgroundImagePropVal::Parser::parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) {
    using enum grUiGSSTokenizer::CSSTokenType;

    if (parser.peekIsUrl()) {
        nxfRID rid;
        GNA_CHECK_STATUS(grUiGSSHelpers::parseRID(rid, parser));

        property.value = gnaNew<grUiGSSBackgroundImagePropVal>(gnaNew<grUiBackground>(grUiSprite{ rid }));

        return GNA_E_OK;
    }

    auto &tok = parser.consumeNextToken();
    {
        grUiSprite sprite;
        gnaStatus spriteStatus = grUiGSSHelpers::parseSprite(tok, sprite, parser);
        if (spriteStatus.errorCode != GNA_E_PARSE_WRONG_START_TOKEN) {
            GNA_CHECK_STATUS(spriteStatus);

            property.value = gnaNew<grUiGSSBackgroundImagePropVal>(gnaNew<grUiBackground>(sprite));

            return GNA_E_OK;
        }
    }
    if (tok.get_tokenType() == TT_FUNCTION) {
        parser.swallowWhitespaceTokens();

        if (tok.tokenValue == "-gr-9patch") {
            // 9-patch image
            nxfRID rid;
            GNA_CHECK_STATUS(grUiGSSHelpers::parseRID(rid, parser));

            property.value = gnaNew<grUiGSSBackgroundImagePropVal>(gnaNew<grUiBackgroundMultipatch>(rid));
        } else {
            return { GNA_E_INVALID_CONFIG, GTXT("Unknown function in background-image") };
        }

        parser.swallowWhitespaceTokens();
        if (parser.consumeNextToken().get_tokenType() != TT_RPAREN) {
            return { GNA_E_FAILED, GTXT("Expected ) after url") };
        }
    } else {
        return { GNA_E_INVALID_CONFIG, GTXT("Invalid background-image value") };
    }

    return GNA_E_OK;
}
