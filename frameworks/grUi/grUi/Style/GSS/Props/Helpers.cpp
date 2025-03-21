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

#include "Helpers.h"

#include <nxfResource/RID.h>
#include <grUi/Style/GSS/Utils.h>
#include <grUi/Utils/Sprite.h>

gnaStatus grUiGSSHelpers::parseRID(nxfRID &rid, grUiGSSParser &parser) {
    gtl::AString url;
    GNA_CHECK_STATUS(parser.parseUrl(url));

    GNA_CHECK_STATUS(grUiGSSUtils::convertUrlToRID(url, rid));

    return GNA_E_OK;
}

gnaStatus grUiGSSHelpers::parseSprite(
    const grUiGSSTokenizer::CSSToken &firstToken,
    grUiSprite &sprite,
    grUiGSSParser &parser) {

    using enum grUiGSSTokenizer::CSSTokenType;

    auto &tok = firstToken;
    if (tok.tokenType != TT_FUNCTION || tok.tokenValue != "-gr-sprite") {
        return { GNA_E_PARSE_WRONG_START_TOKEN, GTXT("Expected -gr-sprite") };
    }

    parser.swallowWhitespaceTokens();

    nxfRID rid;
    GNA_CHECK_STATUS(parseRID(rid, parser));
    if (parser.peekNextToken().get_tokenType() == TT_COMMA) {
        float dstWidth, dstHeight;

        GNA_CHECK_STATUS(parser.parseComma());
        GNA_CHECK_STATUS(parser.parseFloat(dstWidth));
        GNA_CHECK_STATUS(parser.parseComma());
        GNA_CHECK_STATUS(parser.parseFloat(dstHeight));
        if (parser.peekNextToken().get_tokenType() == TT_COMMA) {
            float minU, minV, maxU, maxV;

            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parser.parseFloat(minU));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parser.parseFloat(minV));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parser.parseFloat(maxU));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parser.parseFloat(maxV));
            sprite = { rid, minU, minV, maxU, maxV, dstWidth, dstHeight };
        } else {
            sprite = { rid, dstWidth, dstHeight };
        }
    } else {
        sprite = { rid };
    }

    parser.swallowWhitespaceTokens();
    if (parser.consumeNextToken().get_tokenType() != TT_RPAREN) {
        return { GNA_E_FAILED, GTXT("Expected ) after -gr-sprite") };
    }

    return GNA_E_OK;
}
