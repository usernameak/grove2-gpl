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

#include "Padding.h"

gnaStatus grUiGSSPaddingPropParser::parseProperty(grUiGSSRule &rule, gtl::PooledAString name, grUiGSSParser &parser) {
    grUiUnitSizeI sizes[4];
    static gtl::PooledAString NAMES[4] = {
        "padding-top", "padding-right", "padding-bottom", "padding-left"
    };
    static int INDEXES[4][4] = {
        { 0, 0, 0, 0 },
        { 0, 1, 0, 1 },
        { 0, 1, 2, 1 },
        { 0, 1, 2, 3 },
    };

    int numSizes = 0;
    for (; numSizes < 4; numSizes++) {
        if (!grUiGSSUnitIPropVal::Parser::peekUnitValue(parser)) {
            break;
        }

        GNA_CHECK_STATUS(grUiGSSUnitIPropVal::Parser::parseUnitValue(sizes[numSizes], parser));
        parser.swallowWhitespaceTokens();
    }

    if (numSizes == 0) {
        return { GNA_E_INVALID_CONFIG, GTXT("Expected 1 to 4 UnitValues") };
    }

    for (int i = 0; i < 4; i++) {
        rule.properties.push_back(
            { NAMES[i],
                gnaNew<grUiGSSUnitIPropVal>(sizes[INDEXES[numSizes - 1][i]]) });
    }

    return GNA_E_OK;
}
