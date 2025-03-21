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

#include <gtlMath2/Matrix/Matrix3x2.h>

#include <grUi/Utils/Sprite.h>
#include <grUi/UiDLL.h>
#include <gtlTypeInfo/RTTI.h>
#include <gtlString/PooledString.h>

#include <gr2DCoords.h>

class grUiWidget;

struct grUiDrawEffectData {
    uint32_t effectId;
    float effectParam1;
    float effectParam2;

    // effect id 0: no effect

    // effect id 1: MSDF text rendering
    // - effectParam1: (float) screenPxDistance
    // - effectParam2: (float) bias (thickness)
};

class GR_UI_DLLIMPEXP grUiRenderer {
    gtlMath2::Matrix3x2f m_transform;
    gnaWeakPointer<grUiWidget> m_renderWidget;

protected:
    gnaPointer<grImg::Image> m_whiteTexture;
    bool m_flipTriangles;

public:
    grUiRenderer();

    virtual ~grUiRenderer() = default;

    void set_renderWidget(gnaWeakPointer<grUiWidget> renderWidget) {
        m_renderWidget = renderWidget;
    }

    gnaWeakPointer<grUiWidget> get_renderWidget() const {
        return m_renderWidget;
    }

    gtlMath2::Matrix3x2f &get_transform() {
        return m_transform;
    }

    const gtlMath2::Matrix3x2f &get_transform() const {
        return m_transform;
    }

    virtual void drawSprite(float ox, float oy, const grUiSprite &sprite, uint32_t tint) = 0;

    void drawSprite(float ox, float oy, const grUiSprite &sprite) {
        drawSprite(ox, oy, sprite, 0xFFFFFFFF);
    }

    // obsolete
    [[deprecated]] void drawNinePatch(int x, int y, int width, int height, const nxfRID &sprite);

    virtual void set_uiDrawEffect(const grUiDrawEffectData &effectData, gtl::Name pipelineName = "UI") = 0;

    void drawRectf(float x, float y, float width, float height, uint32_t color) {
        drawSprite(x, y, grUiSprite(m_whiteTexture, width, height), color);
    }

    void set_flipTriangles(bool value) {
        m_flipTriangles = value;
    }

    virtual void drawTriangle(float x0, float y0, float x1, float y1, float x2, float y2, uint32_t color) = 0;

    virtual void pushClip(const grRectangle &rc) = 0;

    virtual void popClip() = 0;

    virtual void swapCompositionLayers() = 0;

    virtual grUiSprite get_compositionLayerSprite(int x, int y, int width, int height) = 0;

    GTL_RTTI_DECLARE();
};
