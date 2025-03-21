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

#include "BackgroundBase.h"
#include <grUi/Utils/MultipatchImage.h>

class GR_UI_DLLIMPEXP grUiBackgroundMultipatch : public grUiBackgroundBase {
    gnaPointer<grUiMultipatchImage> m_multipatchImage;
    uint32_t m_tint;

public:
    GTL_RTTI_DECLARE();
    GTL_DECLARE_OBJECT_CLONE;

    grUiBackgroundMultipatch() : grUiBackgroundMultipatch(nullptr) {}

    explicit grUiBackgroundMultipatch(gnaPointer<grUiMultipatchImage> multipatchImage)
        : m_multipatchImage(std::move(multipatchImage)),
          m_tint(0xFFFFFFFF) {}

    explicit grUiBackgroundMultipatch(nxfRID imageSource);

    void setTint(uint32_t tint) {
        m_tint = tint;
    }

    uint32_t getTint() const {
        return m_tint;
    }

    void draw(grUiRenderer *render, int x, int y, int width, int height) override;

    grInsets get_multipatchInsets() const override;

    grDimension get_minimumDimensions() const override;
};
