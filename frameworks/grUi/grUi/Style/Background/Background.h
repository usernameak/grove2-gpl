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

#include <grColor.h>
#include <nxfResource/RID.h>

class GR_UI_DLLIMPEXP grUiBackground : public grUiBackgroundBase {
    grColor m_color;
    grUiSprite m_sprite;

public:
    GTL_RTTI_DECLARE();
    GTL_DECLARE_OBJECT_CLONE;

    grUiBackground(grColor color, const grUiSprite &sprite) : m_color(color), m_sprite(sprite) {}
    grUiBackground(const grUiSprite &sprite) : grUiBackground(grColor::C_TRANSPARENT, sprite) {}
    grUiBackground(grColor color) : grUiBackground(color, grUiSprite{}) {}
    grUiBackground() : grUiBackground(grColor::C_TRANSPARENT) {}

    void set_color(grColor color) {
        m_color = color;
    }

    void set_sprite(grUiSprite sprite) {
        m_sprite = sprite;
    }

    void draw(grUiRenderer *render, int x, int y, int width, int height) override;

    grDimension get_dimensions() const override;
};
