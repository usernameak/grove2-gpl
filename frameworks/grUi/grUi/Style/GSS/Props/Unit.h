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

#include "PropVal.h"
#include "../Parser.h"
#include <grUi/Utils/UnitSize.h>

template <typename C /* CRTP */, typename T>
struct grUiGSSUnitPropVal_Impl : public grUiGSSPropVal {
    class Parser : public grUiGSSPropertyValueParser {
    public:
        static bool peekUnitValue(grUiGSSParser &parser) {
            using enum grUiGSSTokenizer::CSSTokenType;

            return parser.peekNextToken().get_tokenType() == TT_DIMENSION;
        }

        static gnaStatus parseUnitValue(grUiUnitSize<T> &resVal, grUiGSSParser &parser) {
            using enum grUiGSSTokenizer::CSSTokenType;

            auto &tok = parser.consumeNextToken();
            if (tok.get_tokenType() == TT_DIMENSION) {
                T val;

                static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);

                if constexpr (std::is_integral_v<T>) {
                    long long iValue;
                    bool result = tok.tokenValue.toLongLong(iValue);
                    if (!result) {
                        return { GNA_E_INVALID_CONFIG, GTXT("Unit value specification: cannot decode int value") };
                    }
                    val = (T)iValue;
                } else if constexpr (std::is_floating_point_v<T>) {
                    double dValue;
                    bool result = tok.tokenValue.toDouble(dValue);
                    if (!result) {
                        return { GNA_E_INVALID_CONFIG, GTXT("Unit value specification: cannot decode float value") };
                    }
                    val = (T)dValue;
                }

                typename grUiUnitSize<T>::Unit unit;
                if (tok.tokenUnit == "dp") {
                    unit = grUiUnitSize<T>::UNIT_DP;
                } else if (tok.tokenUnit == "px") {
                    unit = grUiUnitSize<T>::UNIT_PX;
                } else {
                    return {
                        GNA_E_INVALID_CONFIG,
                        gtl::String::format(GTXT("Unit value specification: unsupported unit name %hs"),
                            tok.tokenUnit.toCString())
                    };
                }

                resVal = grUiUnitSize<T>{ unit, val };
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Invalid unit value") };
            }

            return GNA_E_OK;
        }

        gnaStatus parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) override {
            grUiUnitSize<T> val;
            gnaStatus status = parseUnitValue(val, parser);
            property.value   = gnaNew<C>(val);
            return status;
        }
    };

    grUiUnitSize<T> value;

    grUiGSSUnitPropVal_Impl() = default;
    explicit grUiGSSUnitPropVal_Impl(grUiUnitSize<T> value) : value(value) {}
};

struct GR_UI_DLLIMPEXP grUiGSSUnitIPropVal : grUiGSSUnitPropVal_Impl<grUiGSSUnitIPropVal, int> {
    GTL_RTTI_DECLARE();

    using grUiGSSUnitPropVal_Impl::grUiGSSUnitPropVal_Impl;
};

struct GR_UI_DLLIMPEXP grUiGSSUnitFPropVal : grUiGSSUnitPropVal_Impl<grUiGSSUnitFPropVal, float> {
    GTL_RTTI_DECLARE();

    using grUiGSSUnitPropVal_Impl::grUiGSSUnitPropVal_Impl;
};
