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

#include "Widget.h"

class GR_UI_DLLIMPEXP grUiWidgetImage : public grUiWidget {
    grUiSprite m_image;
    bool m_dpiScaleImage : 1;
    float m_imageScale;

public:
    GTL_RTTI_DECLARE();

    grUiWidgetImage() : grUiWidgetImage(grUiSprite{}) {}
    explicit grUiWidgetImage(grUiSprite sprite)
        : m_image(std::move(sprite)),
          m_dpiScaleImage(true),
          m_imageScale(1.0f) {}

    grDimension initialMeasure(int biasedSize) override;
    void draw(grUiRenderer *render) override;

    [[nodiscard]] const grUiSprite &get_image() const {
        return m_image;
    }

    void set_image(grUiSprite image) {
        m_image = std::move(image);
        set_layoutDirty(true);
    }

    [[nodiscard]] bool get_dpiScaleImage() const { return m_dpiScaleImage; }
    void set_dpiScaleImage(bool dpiScaleImage) { m_dpiScaleImage = dpiScaleImage; }

    [[nodiscard]] float get_imageScale() const { return m_imageScale; }
    void set_imageScale(float imageScale) { m_imageScale = imageScale; }
};
