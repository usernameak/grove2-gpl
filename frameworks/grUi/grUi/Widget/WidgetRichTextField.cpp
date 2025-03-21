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

#include "WidgetRichTextField.h"

#include <grUi/Render/UiRenderer.h>
#include <grUi/Text/TextRenderer.h>
#include <grUi/Utils/ClipboardManager.h>
#include <grUi/Style/GSS/Props/Color.h>

// todo add support for Home/End movement buttons

grUiWidgetRichTextField::grUiWidgetRichTextField()
    : m_editable(true) {
    this->eventSink_textInput.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTextInput));
    this->eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyEvent));
    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown));
}

void grUiWidgetRichTextField::set_text(const grUiSpannedText &text, bool bUpdateScroll) {
    this->text = text;

    markTextDirty(bUpdateScroll);
}

void grUiWidgetRichTextField::markTextDirty(bool bUpdateScroll) {
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

void grUiWidgetRichTextField::update() {
    grUiWidget::update();

    updateScroll();
}

void grUiWidgetRichTextField::draw(grUiRenderer *uiRenderer) {
    grUiWidget::draw(uiRenderer);

    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());

    grUiTextRenderer tr(get_metricContext(), fontKey);

    float asc = tr.get_ascender();
    float dsc = tr.get_descender();

    int y = (int)(rc.y + asc + (rc.height - asc) / 2);

    uiRenderer->pushClip({ 0, 0, get_size().width, get_size().height });

    bool fullyFocused = get_fullyFocused();

    if (fullyFocused && m_editable) {
        if (cursorPos != selectionStartPos) {
            int start = std::min(cursorPos, selectionStartPos);
            int end   = std::max(cursorPos, selectionStartPos);

            float lpwStart = tr.get_width(text, start);
            float lpwEnd   = tr.get_width(text, end);
            uiRenderer->drawRectf(
                rc.x + lpwStart - scrollOffset,
                static_cast<float>(y) - asc,
                lpwEnd - lpwStart,
                asc - dsc,
                0xFF264F78);
        }
    }

    const grUiSpannedText &textToDraw = text.empty() && !fullyFocused
                                          ? shadowText
                                          : text;
    auto textDrawColor = m_textColor;
    if (text.empty())
        textDrawColor.set_alpha(textDrawColor.getAlpha() >> 1);

    tr.setOrigin(rc.x - scrollOffset, y);
    tr.render(uiRenderer, textToDraw, textDrawColor.argb);

    if (fullyFocused && m_editable) {
        tr.reset();
        float lpw = tr.get_width(text, cursorPos);
        uiRenderer->drawRectf(
            rc.x + lpw - scrollOffset,
            static_cast<float>(y) - asc,
            1,
            asc - dsc,
            m_textColor.argb);
    }

    uiRenderer->popClip();
}

grDimension grUiWidgetRichTextField::initialMeasure(int biasedSize) {
    grUiTextRenderer tr(get_metricContext(), fontKey);

    return get_baseInsets().outsetDimension({ 1, (int)tr.get_ascender() });
}

void grUiWidgetRichTextField::updateCursorPosition(int mouseX, int mouseY) {
    set_focused(true);

    grInsets ins = get_baseInsets();

    grUiTextRenderer tr(get_metricContext(), fontKey);
    cursorPos = tr.get_charPositionFromX(text, mouseX - ins.left + scrollOffset);

    // do we need this check?
    if (cursorPos > text.size())
        cursorPos = text.size();
    if (cursorPos < 0)
        cursorPos = 0;
}

bool grUiWidgetRichTextField::onMouseDown(const grUiEventMouseDown &ev) {
    if (!m_editable) return true;

    updateCursorPosition(ev.x, ev.y);
    selectionStartPos = cursorPos;

    auto dndctx = gnaNew<TextSelectDnDContext>(this, ev.button);
    grUi_gRootWindowManager->startDragAndDrop(dndctx);

    return true;
}

void grUiWidgetRichTextField::selectAll() {
    selectionStartPos = 0;
    cursorPos         = text.size();
    updateScroll();
}

void grUiWidgetRichTextField::moveCursorToEnd() {
    selectionStartPos = text.size();
    cursorPos         = text.size();
    updateScroll();
}

void grUiWidgetRichTextField::emitTextChanged() {
    grUiEventRichTextFieldChanged ev{ text };
    eventSink_textFieldChanged.emit(ev);
}

void grUiWidgetRichTextField::updateScroll() {
    grUiTextRenderer tr(get_metricContext(), fontKey);

    grInsets ins   = get_baseInsets();
    grRectangle rc = ins.insetDimensionToRect(get_size());
    float tw       = tr.get_width(text);
    float cpw      = tr.get_width(text, cursorPos);
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

bool grUiWidgetRichTextField::onTextInput(const grUiEventTextInput &ev) {
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

        gtl::WIDECHAR wc = c;
        gtl::String tempStr(&wc, 1);
        text.replaceRange(start, end, tempStr);
        markTextDirty(false);

        cursorPos         = start + 1;
        selectionStartPos = cursorPos;
        updateScroll();
    }
    return true;
}

bool grUiWidgetRichTextField::onKeyEvent(const grUiEventKeyPress &ev) {
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
                text.replaceRange(start, end, gtl::String());
                markTextDirty();
            } else if (cursorPos > 0) {
                cursorPos--;
                text.replaceRange(cursorPos, cursorPos + 1, gtl::String());
                markTextDirty();
            }
            selectionStartPos = cursorPos;
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_DELETE) {
            if (selectionStartPos != cursorPos) {
                int end   = std::max(selectionStartPos, cursorPos);
                int start = cursorPos = std::min(selectionStartPos, cursorPos);
                text.replaceRange(start, end, gtl::String());
                markTextDirty();
            } else if (cursorPos < text.size()) {
                text.replaceRange(cursorPos, cursorPos + 1, gtl::String());
                markTextDirty();
            }
            return false;
        } else if (ev.keycode == grKeycode::GR_KEY_C) {
            if ((ev.mods & GR_KEY_MOD_CTRL_OR_CMD) && cursorPos != selectionStartPos) {
                int start          = std::min(cursorPos, selectionStartPos);
                int end            = std::max(cursorPos, selectionStartPos);
                gtl::String copied = text.get_text().substr(start, end);
                grUiClipboardManager::set_clipboardString(copied);
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_X) {
            if ((ev.mods & GR_KEY_MOD_CTRL_OR_CMD) && cursorPos != selectionStartPos) {
                int start          = std::min(cursorPos, selectionStartPos);
                int end            = std::max(cursorPos, selectionStartPos);
                gtl::String copied = text.get_text().substr(start, end);
                grUiClipboardManager::set_clipboardString(copied);
                cursorPos         = start;
                selectionStartPos = cursorPos;
                text.replaceRange(start, end, gtl::String());
                markTextDirty();
                return false;
            }
        } else if (ev.keycode == grKeycode::GR_KEY_V) {
            if (ev.mods & GR_KEY_MOD_CTRL_OR_CMD) {
                gtl::String pasted = grUiClipboardManager::get_clipboardString();
                if (text.size() <= m_lengthLimit && pasted.size() + text.size() > m_lengthLimit) {
                    pasted = pasted.substr(0, m_lengthLimit - text.size());
                }

                int start = std::min(cursorPos, selectionStartPos);
                int end   = std::max(cursorPos, selectionStartPos);
                text.replaceRange(start, end, pasted);
                markTextDirty(false);

                cursorPos         = start + pasted.size();
                selectionStartPos = cursorPos;
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

void grUiWidgetRichTextField::insertImage(gtl::PooledString path) {
    int start = std::min(cursorPos, selectionStartPos);
    int end   = std::max(cursorPos, selectionStartPos);

    grUiTextSpan span(std::move(path));
    text.replaceRange(start, end, span);
    markTextDirty(false);

    cursorPos         = start + 1;
    selectionStartPos = cursorPos;
}

bool grUiWidgetRichTextField::applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) {
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

GTL_RTTI_DEFINE(grUiWidgetRichTextField, GTL_RTTI_INHERITS(grUiWidget));

void grUiWidgetRichTextField::set_shadowText(gtl::String text_) {
    shadowText = text_;
    updateScroll();
}

//-------------//

grUiWidgetRichTextField::TextSelectDnDContext::TextSelectDnDContext(
    gnaWeakPointer<grUiWidgetRichTextField> view,
    int mouseButton) : grUiDragContext(view, mouseButton),
                       m_view(view) {}

void grUiWidgetRichTextField::TextSelectDnDContext::dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) {
    const grPoint widgetPosition = m_view->computeRelativePosition(root);
    m_view->updateCursorPosition(x - widgetPosition.x, y - widgetPosition.y);
}

void grUiWidgetRichTextField::TextSelectDnDContext::dragRelease(gnaWeakPointer<grUiRootWindowManager> root) {}
