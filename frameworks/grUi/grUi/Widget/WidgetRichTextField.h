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
#include <nxfResource/ResourceManager.h>
#include <grUi/Font/FontCache.h>
#include <grUi/Widget/Window/RootWindowManager.h>
#include <grUi/UiDLL.h>
#include <grUi/Text/SpannedText.h>

struct grUiEventRichTextFieldChanged {
    const grUiSpannedText &newText;
};

// TODO: merge shared code with WidgetTextField

class GR_UI_DLLIMPEXP grUiWidgetRichTextField : public grUiWidget {
    grUiFontKey fontKey = { GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE };

    grUiSpannedText text;
    gtl::String shadowText; // displayed when no user text inputted

    int cursorPos         = 0;
    int selectionStartPos = 0;

    int m_lengthLimit = INT32_MAX;

    float scrollOffset = 0.0f;

    bool m_editable : 1;

    class TextSelectDnDContext : public grUiDragContext {
        gnaWeakPointer<grUiWidgetRichTextField> m_view;

    public:
        TextSelectDnDContext(gnaWeakPointer<grUiWidgetRichTextField> view, int mouseButton);

        void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;

        void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override;
    };

public:
    grUiWidgetRichTextField();

    inline const grUiFontKey &get_font() {
        return fontKey;
    }

    const grUiSpannedText &get_text() {
        return text;
    }
    void set_text(const grUiSpannedText &text, bool bUpdateScroll = true);

    void markTextDirty(bool bUpdateScroll = true);

    void set_shadowText(gtl::String text_);

    bool get_editable() const {
        return m_editable;
    }

    void set_editable(bool value) {
        m_editable = value;
        if (!value) {
            cursorPos = selectionStartPos = 0;
        }
    }

    void set_lengthLimit(int value) {
        m_lengthLimit = value;
    }

    int get_lengthLimit() const {
        return m_lengthLimit;
    }

    void update() override;
    void draw(grUiRenderer *) override;

    grDimension initialMeasure(int biasedSize) override;

    gnaEventSink<grUiEventRichTextFieldChanged> eventSink_textFieldChanged;
    gnaEventSink<grUiEventPerformAction> eventSink_textFieldConfirm;

    void selectAll();
    void moveCursorToEnd();

    void insertImage(gtl::PooledString path);

    bool applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) override;

    grColor m_textColor = grColor::WHITE;

private:
    void emitTextChanged();
    void updateScroll();

    bool onTextInput(const grUiEventTextInput &ev);
    bool onKeyEvent(const grUiEventKeyPress &ev);

    void updateCursorPosition(int mouseX, int mouseY);

    bool onMouseDown(const grUiEventMouseDown &ev);

public:
    GTL_RTTI_DECLARE();
};
