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
#include <grUi/Style/Background/BackgroundBase.h>

struct GR_UI_DLLIMPEXP grUiGSSBackgroundImagePropVal : public grUiGSSPropVal {
    GTL_RTTI_DECLARE();

    class Parser : public grUiGSSPropertyValueParser {
    public:
        gnaStatus parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) override;
    };

    gnaPointer<grUiBackgroundBase> background;

    grUiGSSBackgroundImagePropVal() = default;
    explicit grUiGSSBackgroundImagePropVal(const gnaPointer<grUiBackgroundBase> &background) : background(background) {}
};
