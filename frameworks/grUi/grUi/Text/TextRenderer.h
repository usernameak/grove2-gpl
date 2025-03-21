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

#include <grUi/Font/FontRenderer.h>
#include <grUi/Font/FontCache.h>

#include "SpannedText.h"
#include <deque>

class GR_UI_DLLIMPEXP grUiTextRenderer {
    grUiMetricContext m_metricContext;

    gnaPointer<grUiFont> m_font;

    float m_originX, m_originY;
    float m_ellipsizeMaxX;
    float m_currentX, m_currentY;
    float m_fontSize;

    gtl::WIDECHAR m_previousChar = 0;

    struct TextPosition {
        float originX;
        float originY;
        float currentX;
        float currentY;
        gtl::WIDECHAR previousChar;
    };

public:
    enum class HorizontalAlign {
        LEFT, CENTER, RIGHT
    };

    grUiTextRenderer(const grUiMetricContext &metricContext);

    explicit grUiTextRenderer(const grUiMetricContext &metricContext, const grUiFontKey &fontKey);

    void reset();

    void setOrigin(float x, float y) {
        m_originX = x;
        m_originY = y;
        reset();
    }

    void setEllipsize(float maxX) {
        m_ellipsizeMaxX = maxX;
    }

    static void set_enableDebugDraw(bool debugDraw);

    void render(grUiRenderer *render, const grUiSpannedText &text, uint32_t color = 0xFFFFFFFF);
    void renderWithOutline(grUiRenderer *render, const grUiSpannedText &text, uint32_t color = 0xFFFFFFFF);
    void renderWrapped(grUiRenderer *render, const grUiSpannedText &text, float maximumWidth, uint32_t color = 0xFFFFFFFF,
                       HorizontalAlign align = HorizontalAlign::LEFT);
    float renderCharacter(grUiRenderer *render, gtl::WIDECHAR c, uint32_t color = 0xFFFFFFFF);

    void findLineBreakOffsets(const grUiSpannedText &text, float maximumWidth,
        std::deque<std::pair<uint32_t, float>> &lineBreakOffsets);

    float advanceCharacter(gtl::WIDECHAR c);
    float advanceCharacterDryRun(gtl::WIDECHAR c);
    void setupCurrLineBegin(HorizontalAlign align, float lineLength, float maximumWidth);

    gnaWeakPointer<grUiFont> get_font() const {
        return m_font;
    }

    float get_fontSize() const {
        return m_fontSize;
    }

    void set_fontSize(float size) {
        m_fontSize = size;
    }

    float get_width(const grUiSpannedText &text, int untilChar = -1);
    float getWidthWrapped(const grUiSpannedText &text, float maximumWidth, int untilChar = -1);
    int get_charPositionFromX(const grUiSpannedText &text, float x);
    float get_ascender() const;
    float get_descender() const;
    float get_lineHeight() const;
    float get_baselineOffsetFromLineTop() const;

private:
    void renderBegin(grUiRenderer *render, float bias = 0.0f);
    void renderEnd(grUiRenderer *render);

    void doRender(grUiRenderer *render, const grUiSpannedText &text, uint32_t color = 0xFFFFFFFF, bool forceColor = false);

    [[nodiscard]] TextPosition saveTextPosition() const {
        TextPosition tpos{};
        tpos.currentX     = m_currentX;
        tpos.currentY     = m_currentY;
        tpos.originX      = m_originX;
        tpos.originY      = m_originY;
        tpos.previousChar = m_previousChar;

        return tpos;
    }

    void restoreTextPosition(const TextPosition &tpos) {
        m_currentX     = tpos.currentX;
        m_currentY     = tpos.currentY;
        m_originX      = tpos.originX;
        m_originY      = tpos.originY;
        m_previousChar = tpos.previousChar;
    }
};
