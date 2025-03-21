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

#include "WidgetText.h"

#include <cmath>
#include <grUi/Text/TextRenderer.h>
#include <gtlUtil/Logging.h>

#include <grUi/Style/GSS/Props/Color.h>
#include <grUi/Style/GSS/Props/Font.h>
#include <grUi/Style/GSS/Props/TextAlign.h>
#include <grUi/Style/GSS/Props/Unit.h>

GTL_RTTI_DEFINE(grUiWidgetText, GTL_RTTI_INHERITS(grUiWidget));

grUiWidgetText::grUiWidgetText(grUiSpannedText text)
    : text(text),
      m_multiline(false),
      fontKey{ GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE },
      m_ellipsize(false),
      m_outline(false),
      m_maxWidth(INT_MAX) {}

grUiWidgetText::~grUiWidgetText() = default;

grDimension grUiWidgetText::initialMeasure(int biasedSize) {
    grDimension dim;

    auto fontRenderer = gnaSingleton<grUiFontCache>()->get_font(fontKey);

    grInsets textInsets = get_insets(INSET_TEXT);

    grUiTextRenderer tr(get_metricContext(), fontKey);

    if (!fontRenderer) {
        dim = { 0, 0 };
    } else if (m_multiline) {
        int maxWidth = m_maxWidth;

        if (m_maxWidth == INT_MAX) {
            dim.width = biasedSize - textInsets.left - textInsets.right;
            maxWidth  = dim.width;
        } else {
            dim.width = (int)std::ceil(tr.getWidthWrapped(text, maxWidth)) + textInsets.left + textInsets.right;
        }

        std::deque<std::pair<uint32_t, float>> lineBreakOffsets;
        tr.findLineBreakOffsets(text, maxWidth, lineBreakOffsets);

        dim.height = (int)ceil((float)(lineBreakOffsets.size()) * tr.get_lineHeight());
    } else {
        if (m_ellipsize) {
            dim.width = 0;
        } else {
            dim.width = (int)ceil(tr.get_width(text));
        }
        // dim.height = static_cast<int>(ceil(fontRenderer->get_lineHeight() + (m_openDescent ? 0.0f : fontRenderer->get_descender())));
        dim.height = static_cast<int>(ceil(tr.get_lineHeight()));
    }

    return textInsets.outsetDimension(dim);
}

grUiEnumContentBias grUiWidgetText::get_contentBias() {
    return m_multiline && m_maxWidth == INT_MAX
             ? grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL
             : grUiWidget::get_contentBias();
}

void grUiWidgetText::draw(grUiRenderer *render) {
    grUiWidget::draw(render);

    auto fontRenderer = gnaSingleton<grUiFontCache>()->get_font(fontKey);

    if (!fontRenderer)
        return;

    grUiTextRenderer tr(get_metricContext(), fontKey);

    grInsets ins   = get_insets(INSET_TEXT);
    grRectangle rc = ins.insetDimensionToRect(get_size());

    if (m_multiline) {
        int x = rc.x;
        int y = (int) (rc.y + tr.get_baselineOffsetFromLineTop());

        std::deque<std::pair<uint32_t, float>> lineBreakOffsets;
        tr.findLineBreakOffsets(text, rc.width, lineBreakOffsets);
        float maxWidth = 0;
        for (auto [idx, width] : lineBreakOffsets)
            maxWidth = std::max(maxWidth, width);

        auto render_align = grUiTextRenderer::HorizontalAlign::LEFT;
        if ((alignment & GR_TEXT_ALIGN_CENTER) == GR_TEXT_ALIGN_CENTER)
            render_align = grUiTextRenderer::HorizontalAlign::CENTER;
        else if (alignment & GR_TEXT_ALIGN_LEFT)
            render_align = grUiTextRenderer::HorizontalAlign::LEFT;
        else if (alignment & GR_TEXT_ALIGN_RIGHT)
            render_align = grUiTextRenderer::HorizontalAlign::RIGHT;

        tr.setOrigin(x, y);

        tr.renderWrapped(render, text, rc.width, color.argb, render_align);
    } else {
        float y = (int)(rc.y + tr.get_baselineOffsetFromLineTop());
        float totalHeight = tr.get_lineHeight();
        if ((alignment & GR_TEXT_ALIGN_MIDDLE) == GR_TEXT_ALIGN_MIDDLE) {
            y += (int)((rc.height - totalHeight) / 2);
        } else if (alignment & GR_TEXT_ALIGN_TOP) {
        } else if (alignment & GR_TEXT_ALIGN_BOTTOM) {
            y += (int)(rc.height - totalHeight);
        } else {
            GR_FATAL(GTXT("invalid text alignment value"));
        }

        float totalWidth = tr.get_width(text);

        int x = rc.x;

        if ((alignment & GR_TEXT_ALIGN_CENTER) == GR_TEXT_ALIGN_CENTER) {
            x += (int)((rc.width - totalWidth) / 2);
        } else if (alignment & GR_TEXT_ALIGN_LEFT) {
        } else if (alignment & GR_TEXT_ALIGN_RIGHT) {
            x += (int)(rc.width - totalWidth);
        } else {
            GR_FATAL(GTXT("invalid text alignment value"));
        }
        if (m_ellipsize) {
            tr.setEllipsize(rc.x + rc.width);
        }

        tr.setOrigin(x, y);
        if (m_outline) {
            tr.renderWithOutline(render, text, color.argb);
        } else {
            tr.render(render, text, color.argb);
        }
    }
}

void grUiWidgetText::set_text(gtl::String text) {
    if (this->text.get_text() != text) {
        set_layoutDirty(true);
    }
    this->text = text;
}

void grUiWidgetText::set_font(const grUiFontKey &font) {
    if (this->fontKey != font) {
        set_layoutDirty(true);
    }
    this->fontKey = font;
}

gtl::String grUiWidgetText::get_text() const {
    return this->text.get_text();
}

void grUiWidgetText::set_multiline(bool multiline) {
    if (multiline != m_multiline) {
        set_layoutDirty(true);
    }
    m_multiline = multiline;
}

void grUiWidgetText::set_ellipsize(bool ellipsize) {
    if (ellipsize != m_ellipsize) {
        set_layoutDirty(true);
    }
    m_ellipsize = ellipsize;
}

bool grUiWidgetText::applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) {
    bool superResult = grUiWidget::applyStyleProperty(name, value);

    static const gtl::PooledAString NAME_COLOR("color");
    static const gtl::PooledAString NAME_FONT_FAMILY("font-family");
    static const gtl::PooledAString NAME_FONT_SIZE("font-size");
    static const gtl::PooledAString NAME_TEXT_ALIGN("text-align");
    static const gtl::PooledAString NAME_VERTICAL_ALIGN("vertical-align");

    if (name == NAME_COLOR) {
        color = value.cast<grUiGSSColorPropVal>()->color;
    } else if (name == NAME_FONT_FAMILY) {
        set_font({ value.cast<grUiGSSFontFamilyPropVal>()->fontName, get_font().fontSize });
    } else if (name == NAME_FONT_SIZE) {
        set_font({ get_font().fontName, value.cast<grUiGSSUnitFPropVal>()->value });
    } else if (name == NAME_TEXT_ALIGN) {
        alignment &= ~GR_TEXT_ALIGN_HORZ_MASK;
        switch (value.cast<grUiGSSTextAlignPropVal>()->textAlign) {
        case grUiGSSTextAlignPropVal::TEXT_ALIGN_LEFT:
            alignment |= GR_TEXT_ALIGN_LEFT;
            break;
        case grUiGSSTextAlignPropVal::TEXT_ALIGN_CENTER:
            alignment |= GR_TEXT_ALIGN_CENTER;
            break;
        case grUiGSSTextAlignPropVal::TEXT_ALIGN_RIGHT:
            alignment |= GR_TEXT_ALIGN_RIGHT;
            break;
        }
    } else if (name == NAME_VERTICAL_ALIGN) {
        alignment &= ~GR_TEXT_ALIGN_VERT_MASK;
        switch (value.cast<grUiGSSVerticalAlignPropVal>()->verticalAlign) {
        case grUiGSSVerticalAlignPropVal::VERTICAL_ALIGN_TOP:
            alignment |= GR_TEXT_ALIGN_TOP;
            break;
        case grUiGSSVerticalAlignPropVal::VERTICAL_ALIGN_MIDDLE:
            alignment |= GR_TEXT_ALIGN_MIDDLE;
            break;
        case grUiGSSVerticalAlignPropVal::VERTICAL_ALIGN_BOTTOM:
            alignment |= GR_TEXT_ALIGN_BOTTOM;
            break;
        }
    } else {
        return superResult;
    }
    return true;
}
