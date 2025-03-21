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

#include <grUi/UiDLL.h>
#include <gtlMemory/RcObject.h>
#include <gr2DCoords.h>
#include <gtlString/String.h>
#include "LayoutEnums.h"

class grUiWidget;
class grUiWidgetLayout;

class GR_UI_DLLIMPEXP grUiLayoutManager : public gtlRcObject {
protected:
    friend class grUiWidgetLayout;

    virtual grDimension initialMeasure(grUiWidgetLayout *parent, int biasedSize) = 0;
    virtual void layout(grUiWidgetLayout *parent)                                = 0;

    virtual grUiEnumContentBias get_contentBias(grUiWidgetLayout *parent) {
        return grUiEnumContentBias::CONTENT_BIAS_NONE;
    }

    virtual uint32_t get_flags() {
        return 0;
    }

    virtual void drawDebug() {}

public:
    GTL_RTTI_DECLARE();

    virtual gnaPointer<gtlRcObject> createLayoutDataFromString(const gtl::AString &str) const {
        return nullptr;
    }
};
