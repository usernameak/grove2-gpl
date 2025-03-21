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

#include <grUi/Widget/Widget.h>
#include <gtlString/String.h>
#include <grUi/Font/FontCache.h>
#include <nxfResource/ResourceManager.h>
#include <grUi/UiDLL.h>
#include <grUi/Text/SpannedText.h>

enum grUiTextAlignment : uint8_t {
    GR_TEXT_ALIGN_INVALID = 0,

    // horizontal
    GR_TEXT_ALIGN_LEFT      = 1,
    GR_TEXT_ALIGN_RIGHT     = 2,
    GR_TEXT_ALIGN_CENTER    = GR_TEXT_ALIGN_LEFT | GR_TEXT_ALIGN_RIGHT,
    GR_TEXT_ALIGN_HORZ_MASK = GR_TEXT_ALIGN_CENTER,

    // vertical
    GR_TEXT_ALIGN_TOP       = 4,
    GR_TEXT_ALIGN_BOTTOM    = 8,
    GR_TEXT_ALIGN_MIDDLE    = GR_TEXT_ALIGN_TOP | GR_TEXT_ALIGN_BOTTOM,
    GR_TEXT_ALIGN_VERT_MASK = GR_TEXT_ALIGN_MIDDLE,
};

class GR_UI_DLLIMPEXP grUiWidgetText : public grUiWidget {
    grUiSpannedText text;

    grUiFontKey fontKey;

    int m_maxWidth;

public:
    GTL_RTTI_DECLARE();

    grUiWidgetText(grUiSpannedText text);

    grUiWidgetText() : grUiWidgetText(grUiSpannedText()) {
    }

    grUiWidgetText(gtl::String text) : grUiWidgetText(grUiSpannedText(text)) {
    }

    virtual ~grUiWidgetText() override;

    grDimension initialMeasure(int biasedSize) override;

    grUiEnumContentBias get_contentBias() override;

    void draw(grUiRenderer *) override;

    void set_text(gtl::String text);
    gtl::String get_text() const;

    const grUiSpannedText &get_spannedText() const {
        return this->text;
    }

    grUiSpannedText &get_spannedText() {
        return this->text;
    }

    void refreshTextLayout();

    void set_maxWidth(int maxWidth) {
        if (maxWidth != m_maxWidth) set_layoutDirty(true);
        m_maxWidth = maxWidth;
    }

    int get_maxWidth() const {
        return m_maxWidth;
    }

    const grUiSpannedText &get_formattedText() const {
        return text;
    }

    void set_font(const grUiFontKey &font);
    const grUiFontKey &get_font() const { return fontKey; }

    void set_multiline(bool multiline);
    bool get_multiline() const { return m_multiline; }

    void set_ellipsize(bool ellipsize);
    bool get_ellipsize() const { return m_ellipsize; }

    void set_outline(bool outline) {
        m_outline = outline;
    }
    bool get_outline() const { return m_outline; }

    bool applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) override;

    grColor color     = grColor::WHITE;
    uint8_t alignment = GR_TEXT_ALIGN_CENTER | GR_TEXT_ALIGN_MIDDLE;

private:
    bool m_multiline : 1;
    bool m_ellipsize : 1;
    bool m_outline   : 1;
};
