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

#include "WidgetTextField.h"

#include <grUi/Render/UiRenderer.h>
#include <grUi/Text/TextRenderer.h>
#include <grUi/Utils/ClipboardManager.h>
#include <grUi/Style/GSS/Props/Color.h>

grUiWidgetTextField::grUiWidgetTextField()
    : m_editable(true),
      m_isPassword(false) {
    this->eventSink_textInput.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTextInput));
    this->eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyEvent));
    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

void grUiWidgetTextField::set_text(gtl::String text, bool bUpdateScroll) {
    if (text == this->text) return;

    this->text = text;

    if (m_isPassword) {
        // std::fill_n(visibleText.begin(), text.size(), GTXT('*'));
        visibleText.resize(text.size());
        auto str_content = visibleText.forceCopy();
        for (auto i = 0; i < text.size(); ++i)
            str_content[i] = GTXT('\u2022');
    } else {
        visibleText = text;
    }

    if (cursorPos < 0) {
        cursorPos = 0;
    }
    if (cursorPos > text.size())
        cursorPos = text.size();

    if (bUpdateScroll) {
        updateScroll();
    }

    emitTextChanged();
}

void grUiWidgetTextField::update() {
    grUiWidget::update();

    updateScroll();
}

void grUiWidgetTextField::draw(grUiRenderer *uiRenderer) {
    grUiWidget::draw(uiRenderer);

    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());

    grRectangle mrc = get_insets(INSET_MARGIN).insetDimensionToRect(get_size());

    auto fontRenderer = gnaSingleton<grUiFontCache>()->get_font(fontKey);

    grUiTextRenderer tr(get_metricContext(), fontKey);
    float asc = tr.get_ascender();
    float dsc = tr.get_descender();
    float lh  = tr.get_lineHeight();
    int y     = (int)(rc.y + asc + (rc.height - asc) / 2);

    uiRenderer->pushClip(mrc);

    bool fullyFocused = get_fullyFocused();

    if (fullyFocused && m_editable) {
        if (cursorPos != selectionStartPos) {
            int start = std::min(cursorPos, selectionStartPos);
            int end   = std::max(cursorPos, selectionStartPos);

            float lpwStart = tr.get_width(visibleText, start);
            float lpwEnd   = tr.get_width(visibleText, end);
            uiRenderer->drawRectf(
                rc.x + lpwStart - scrollOffset,
                static_cast<float>(y) - asc,
                lpwEnd - lpwStart,
                asc - dsc,
                0xFF264F78);
        }
    }

    grColor textDrawColor = m_textColor;
    gtl::String textToDraw = visibleText;

    if (visibleText.empty() && !fullyFocused) {
        textToDraw = shadowText;
        textDrawColor.set_alpha(textDrawColor.getAlpha() >> 1);
    }

    if (fontRenderer) {
        tr.setOrigin(rc.x - scrollOffset, y);
        tr.render(uiRenderer, textToDraw, textDrawColor.argb);
    }

    if (fullyFocused && m_editable) {
        float lpw = tr.get_width(visibleText, cursorPos);
        uiRenderer->drawRectf(
            rc.x + lpw - scrollOffset,
            static_cast<float>(y) - asc,
            1,
            asc - dsc,
            m_textColor.argb);
    }

    uiRenderer->popClip();
}

grDimension grUiWidgetTextField::initialMeasure(int biasedSize) {
    grUiTextRenderer tr(get_metricContext(), fontKey);
    return get_baseInsets().outsetDimension({ 1, (int)std::ceil(tr.get_ascender()) });
}

void grUiWidgetTextField::updateCursorPosition(int mouseX, int mouseY) {
    set_focused(true);

    grInsets ins = get_baseInsets();

    grUiTextRenderer tr(get_metricContext(), fontKey);
    cursorPos = tr.get_charPositionFromX(visibleText, mouseX - ins.left + scrollOffset);

    // do we need this check?
    if (cursorPos > text.size())
        cursorPos = text.size();
    if (cursorPos < 0)
        cursorPos = 0;
}

bool grUiWidgetTextField::onMouseDown(const grUiEventMouseDown &ev) {
    if (!m_editable) return true;

    updateCursorPosition(ev.x, ev.y);
    selectionStartPos = cursorPos;

    auto dndctx = gnaNew<TextSelectDnDContext>(this, ev.button);
    grUi_gRootWindowManager->startDragAndDrop(dndctx);

    return true;
}

void grUiWidgetTextField::selectAll() {
    selectionStartPos = 0;
    cursorPos         = text.size();
    updateScroll();
}

void grUiWidgetTextField::moveCursorToEnd() {
    selectionStartPos = text.size();
    cursorPos         = text.size();
    updateScroll();
}

void grUiWidgetTextField::emitTextChanged() {
    grUiEventTextFieldChanged ev;
    ev.newText = text;
    eventSink_textFieldChanged.emit(ev);
}

void grUiWidgetTextField::updateScroll() {
    grUiTextRenderer tr(get_metricContext(), fontKey);
    grInsets ins      = get_baseInsets();
    grRectangle rc    = ins.insetDimensionToRect(get_size());
    float tw          = tr.get_width(visibleText);
    float cpw         = tr.get_width(visibleText, cursorPos);
    if (scrollOffset < cpw - rc.width) {
        scrollOffset = cpw - rc.width;
    }
    if (cpw < scrollOffset) {
        scrollOffset = cpw;
    }
    if (scrollOffset >= tw - rc.width) {
        scrollOffset = tw - rc.width;
    }
    if (scrollOffset < 0.0f) {
        scrollOffset = 0.0f;
    }
}

bool grUiWidgetTextField::onTextInput(const grUiEventTextInput &ev) {
    if (!m_editable) return true;
    char32_t c = ev.c;
    if (c > UINT_LEAST16_MAX) {
        return true;
    }
    if (text.size() >= m_lengthLimit) {
        return true;
    }
    if (c >= 32 && c != 127) {
        int start = std::min(cursorPos, selectionStartPos);
        int end   = std::max(cursorPos, selectionStartPos);
        cursorPos         = start + 1;
        selectionStartPos = cursorPos;
        set_text(text.substr(0, start) + static_cast<gtl::WIDECHAR>(c) + text.substr(end), false);
        updateScroll();
    }
    return true;
}

bool grUiWidgetTextField::onKeyEvent(const grUiEventKeyPress &ev) {
    if (!m_editable) return true;
    if (ev.action == GR_ACTION_KEY_PRESSED || ev.action == GR_ACTION_KEY_REPEATED) {
        bool shiftPressed = ev.mods & GR_KEY_MOD_SHIFT;
        if (ev.keycode == grKeycode::GR_KEY_RIGHT) {
            if (!shiftPressed && selectionStartPos != cursorPos) {
                cursorPos = std::max(selectionStartPos, cursorPos);
            } else if (++cursorPos > text.size()) {
                cursorPos = text.size();
            }
            if (!shiftPressed) {
                selectionStartPos = cursorPos;
            }
            updateScroll();
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_HOME) {
            cursorPos = 0;
            if (!shiftPressed) {
                selectionStartPos = cursorPos;
            }
            updateScroll();
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_END) {
            cursorPos = text.size();
            if (!shiftPressed) {
                selectionStartPos = cursorPos;
            }
            updateScroll();
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_LEFT) {
            if (!shiftPressed && selectionStartPos != cursorPos) {
                cursorPos = std::min(selectionStartPos, cursorPos);
            } else if (--cursorPos < 0) {
                cursorPos = 0;
            }
            if (!shiftPressed) {
                selectionStartPos = cursorPos;
            }
            updateScroll();
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_BACK) {
            if (selectionStartPos != cursorPos) {
                int end   = std::max(selectionStartPos, cursorPos);
                int start = cursorPos = std::min(selectionStartPos, cursorPos);
                selectionStartPos = cursorPos;
                set_text(text.substr(0, start) + text.substr(end));
            } else if (cursorPos > 0) {
                cursorPos--;
                selectionStartPos = cursorPos;
                set_text(text.substr(0, cursorPos) + text.substr(cursorPos + 1));
            }
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_DELETE) {
            if (selectionStartPos != cursorPos) {
                int end   = std::max(selectionStartPos, cursorPos);
                int start = cursorPos = std::min(selectionStartPos, cursorPos);
                set_text(text.substr(0, start) + text.substr(end));
            } else if (cursorPos < text.size()) {
                set_text(text.substr(0, cursorPos) + text.substr(cursorPos + 1));
            }
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_C) {
            if ((ev.mods & GR_KEY_MOD_CTRL_OR_CMD) && cursorPos != selectionStartPos) {
                int start          = std::min(cursorPos, selectionStartPos);
                int end            = std::max(cursorPos, selectionStartPos);
                gtl::String copied = text.substr(start, end);
                grUiClipboardManager::set_clipboardString(copied);
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_X) {
            if ((ev.mods & GR_KEY_MOD_CTRL_OR_CMD) && cursorPos != selectionStartPos) {
                int start          = std::min(cursorPos, selectionStartPos);
                int end            = std::max(cursorPos, selectionStartPos);
                gtl::String copied = text.substr(start, end);
                grUiClipboardManager::set_clipboardString(copied);
                cursorPos         = start;
                selectionStartPos = cursorPos;
                set_text(text.substr(0, start) + text.substr(end));
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_V) {
            if (ev.mods & GR_KEY_MOD_CTRL_OR_CMD) {
                gtl::String pasted = grUiClipboardManager::get_clipboardString();
                if (text.size() <= m_lengthLimit && pasted.size() + text.size() > m_lengthLimit) {
                    pasted = pasted.substr(0, m_lengthLimit - text.size());
                }
                int start = cursorPos;
                int end = cursorPos;
                cursorPos += pasted.size();
                selectionStartPos = cursorPos;
                set_text(text.substr(0, start) + pasted + text.substr(end), false);
                updateScroll();
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_A) {
            if (ev.mods & GR_KEY_MOD_CTRL_OR_CMD) {
                selectAll();
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_RETURN) {
            grUiEventPerformAction ev1;
            eventSink_textFieldConfirm.emit(ev1);
            return false;
        }
    }

    return (ev.mods != 0 && ev.mods != GR_KEY_MOD_SHIFT) ||
           !((ev.keycode >= grKeycode::GR_KEY_A && ev.keycode <= grKeycode::GR_KEY_Z) ||
               (ev.keycode >= grKeycode::GR_KEY_0 && ev.keycode <= grKeycode::GR_KEY_9) ||
               ev.keycode == grKeycode::GR_KEY_OEM_PLUS ||
               ev.keycode == grKeycode::GR_KEY_OEM_MINUS ||
               ev.keycode == grKeycode::GR_KEY_OEM_3);
}

bool grUiWidgetTextField::applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) {
    bool superResult = grUiWidget::applyStyleProperty(name, value);

    // TODO: unify this with WidgetText styling mechanism

    static const gtl::PooledAString NAME_COLOR("color");
    if (name == NAME_COLOR) {
        m_textColor = value.cast<grUiGSSColorPropVal>()->color;
    } else {
        return superResult;
    }
    return true;
}

GTL_RTTI_DEFINE(grUiWidgetTextField, GTL_RTTI_INHERITS(grUiWidget));

void grUiWidgetTextField::set_shadowText(gtl::String text_) {
    shadowText = text_;
    updateScroll();
}

//-------------//

grUiWidgetTextField::TextSelectDnDContext::TextSelectDnDContext(
    gnaWeakPointer<grUiWidgetTextField> view,
    int mouseButton) : grUiDragContext(view, mouseButton),
                       m_view(view) {}

void grUiWidgetTextField::TextSelectDnDContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    const grPoint widgetPosition = m_view->computeRelativePosition(root);
    m_view->updateCursorPosition(x - widgetPosition.x, y - widgetPosition.y);
}

void grUiWidgetTextField::TextSelectDnDContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {}
