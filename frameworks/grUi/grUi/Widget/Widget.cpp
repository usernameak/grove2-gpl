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

#include "Widget.h"

#include <gtlUtil/Logging.h>

#include <grUi/Widget/WidgetLayout.h>

#include <grUi/Native/NativePlatformDevice.h>
#include "Native/NativeFramePlatform.h"
#include "grUi/Style/GSS/Props/Unit.h"

#include <grUi/Style/GSS/Props/Color.h>
#include <grUi/Style/GSS/Props/Border.h>
#include <grUi/Style/Border/BorderMultipatch.h>
#include <grUi/Style/GSS/Props/Background.h>
#include <grUi/Style/Border/BorderNative.h>
#include <grUi/Style/GSS/StyleSheet.h>

GTL_RTTI_DEFINE(grUiWidget, GTL_RTTI_INHERITS(gtlRcObject));

grUiWidget::grUiWidget()
    : gtlRcObject(),
      m_platform(nullptr),
      m_nativeDevice(nullptr),
      m_renderer(nullptr),
      m_currentDpiScaleFactor(0),
      m_visibility(VISIBILITY_VISIBLE) {}

grUiWidget::~grUiWidget() {
    gtlDelete m_renderer;
    gtlDelete m_platform;
}

void grUiWidget::update() {
    if (m_platform) {
        m_platform->update();

        if (m_platform->usesExternalWindowManager()) {
            grRectangle vp = m_platform->get_windowViewport();
            auto vpWidget  = get_nativeViewportWidget();
            if (vpWidget && vpWidget != this) {
                vpWidget->set_bounds(vp.x, vp.y, vp.width, vp.height);
            }
        }
    }
}

void grUiWidget::set_parent(gnaWeakPointer<grUiWidgetLayout> newParent, uint32_t pflag) {
    if (parent != newParent) {
        set_layoutDirty(true);
    }
    bool lostParent = false;
    if (parent && !newParent) {
        lostParent = true;
    }
    if (newParent && focused) {
        newParent->releaseFocusFromChildren();
        newParent->set_focused(true);
    }
    parent = newParent;

    if (!(pflag & PFLAG_NO_EVENTS)) {
        if (lostParent) {
            onLostParent();
        }

        handleParentChanged(parent);
    }
}

bool grUiWidget::isRootWidget() const {
    return m_isRootWidget;
}

void grUiWidget::set_isRootWidget(bool value) {
    m_isRootWidget = value;

    handleParentChanged(parent); // update parent info
}

void grUiWidget::updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> parent) {
    if (!m_isRootWidget) { // root widgets retain their device during their lifetime
        if (parent) {
            m_nativeDevice = parent.cast<grUiWidget>()->m_nativeDevice;
        } else {
            m_nativeDevice = nullptr;
        }
    }
}

void grUiWidget::handleParentChanged(gnaWeakPointer<grUiWidgetLayout> parent) {
    // get device from parent if necessary
    updateNativeDevice(parent);

    // initialize platform window and renderer if necessary
    // TODO: check this code later, there might be some issues.
    bool isParentDesktop = false;
    if (m_nativeDevice && m_nativeDevice->isDesktopWidget(parent)) {
        isParentDesktop = true;
        if (!m_platform) {
            m_platform = m_nativeDevice->createFramePlatform(this);
        }
    }

    if (m_nativeDevice && m_nativeDevice->shouldHaveOwnRenderer(this, parent)) {
        if (!m_renderer) {
            m_renderer = m_nativeDevice->createRenderer(this);
        }
    } else if (parent) {
        gtlDelete m_renderer;
        m_renderer = nullptr;
    }

    if (parent && !isParentDesktop) {
        gtlDelete m_platform;
        m_platform = nullptr;
    }

    if (m_platform) {
        // set visibility depending on parent presence
        m_platform->set_windowVisible(parent.hasValue());
    }

    if (m_platform) {
        // update native frame border if required
        if (auto nativeBorder = border.rttiCast2<grUiBorderNative>()) {
            if (m_platform->updateNativeBorderInsets(nativeBorder)) {
                set_layoutDirty(true);
                widgetBorderChanged();
            }
        }
    }

    // update DPI scaling factor (can change the way how styles
    // are interpreted, so ordered before style update)
    updateDpiScaleFactor(parent);

    updateStyleHierarchy();
}

void grUiWidget::set_bounds(int x, int y, int width, int height) {
    if (size.width != width || size.height != height) {
        // boundsChanged = true;
        onBoundsChanged();
    }
    position.x  = x;
    position.y  = y;
    size.width  = width;
    size.height = height;
}

bool grUiWidget::get_fullyFocused() {
    gnaWeakPointer<grUiWidget> w = this;

    while (w) {
        if (!w->get_focused()) {
            return false;
        }
        w = w->get_parent();
    }

    return true;
}

void grUiWidget::set_focused(bool in_focused, bool suppressEvent) {
    if (in_focused) {
        if (!focused) {
            auto parent = get_parent();
            if (parent) {
                parent->releaseFocusFromChildren();
                parent->set_focused(true);
            }

            focused = true;

            set_styleStateBits(get_styleStateBits() | STSTBIT_FOCUSED);

            if (!suppressEvent) {
                grUiEventFocus ev;
                eventSink_focus.emit(ev);
            }
        } else {
            auto parent = get_parent();
            if (parent) {
                parent->set_focused(true);
            }
        }
    } else {
        if (focused) {
            focused = false;

            set_styleStateBits(get_styleStateBits() & ~STSTBIT_FOCUSED);

            if (!suppressEvent) {
                grUiEventDefocus ev;
                eventSink_defocus.emit(ev);
            }
        }
    }
}

grPoint grUiWidget::computeRelativePosition(gnaPointer<grUiWidget> widget) {
    auto parent = get_parent();
    if (!parent) {
        if (widget) {
            GR_FATAL(GTXT("grUiWidget: computing relative position from non - parent widget"));
        }
        return get_position(); // this shall work
    }
    if (parent == widget) {
        return get_position();
    }
    return parent->computeRelativePosition(widget) + position;
}

gnaWeakPointer<grUiWidget> grUiWidget::findNativeWindow() {
    if (m_platform)
        return this;
    if (get_parent())
        return get_parent()->findNativeWindow();
    return nullptr;
}

grUiRenderer *grUiWidget::get_windowRenderer() const {
    if (m_renderer)
        return m_renderer;
    if (parent)
        return parent->get_windowRenderer();
    return nullptr;
}

void grUiWidget::drawClipped(grUiRenderer *render, const grRectangle &clipRect) {
    draw(render);
}

void grUiWidget::draw(grUiRenderer *render) {
    grRectangle borderRect = get_insets(INSET_MARGIN).insetDimensionToRect(get_size());
    background->draw(render, borderRect.x, borderRect.y, borderRect.width, borderRect.height);
    border->draw(this, render, borderRect.x, borderRect.y, borderRect.width, borderRect.height);
}

void grUiWidget::preDraw(grUiRenderer *render, const grRectangle &clipRect) {
}

void grUiWidget::drawDebug(grUiRenderer *render) {
    grDimension dim = get_size();

    render->drawRectf(0.0f, 0.0f, (float)dim.width, 1.0f, 0xFFFF0000);
    render->drawRectf(0.0f, 1.0f, 1.0f, (float)dim.height - 2.0f, 0xFFFF0000);

    render->drawRectf(0.0f, (float)dim.height - 1.0f, (float)dim.width, 1.0f, 0xFFFF0000);
    render->drawRectf((float)dim.width - 1.0f, 1.0f, 1.0f, (float)dim.height - 2.0f, 0xFFFF0000);
}

void grUiWidget::nativeWidgetDraw() {
    if (m_nativeDevice) {
        m_nativeDevice->nativeWidgetDraw(this);
    }
}

void grUiWidget::nativeWidgetPreDraw(float deltaTime) {
    if (m_nativeDevice) {
        m_nativeDevice->nativeWidgetPreDraw(this, deltaTime);
    }
}

void grUiWidget::nativeWidgetPresent() {
    if (m_platform) {
        m_platform->nativeWidgetPresent();
    }
}

gnaWeakPointer<grUiWidget> grUiWidget::get_nativeViewportWidget() {
    return this;
}

bool grUiWidget::applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value) {
    static const gtl::PooledAString NAME_BACKGROUND_IMAGE("background-image");
    static const gtl::PooledAString NAME_BACKGROUND_COLOR("background-color");
    static const gtl::PooledAString NAME_BORDER_STYLE("border-style");
    static const gtl::PooledAString NAME_BORDER_WIDTH("border-width");
    static const gtl::PooledAString NAME_BORDER_COLOR("border-color");
    static const gtl::PooledAString NAME_PADDING_LEFT("padding-left");
    static const gtl::PooledAString NAME_PADDING_TOP("padding-top");
    static const gtl::PooledAString NAME_PADDING_RIGHT("padding-right");
    static const gtl::PooledAString NAME_PADDING_BOTTOM("padding-bottom");

    if (name == NAME_BACKGROUND_IMAGE) {
        background = value.cast<grUiGSSBackgroundImagePropVal>()->background->clone().cast<grUiBackgroundBase>();
    } else if (name == NAME_BACKGROUND_COLOR) {
        // TODO: check this later, might cause a problem with shared backgrounds
        if (auto bg = background.rttiCast2<grUiBackground>()) {
            bg->set_color(value.cast<grUiGSSColorPropVal>()->color);
        }
    } else if (name == NAME_BORDER_STYLE) {
        // TODO: add ability to dynamically add custom border types
        switch (value.cast<grUiGSSBorderTypePropVal>()->borderType) {
        case grUiGSSBorderTypePropVal::BORDER_TYPE_NONE:
            set_border(gnaNew<grUiBorder>(0, grColor::C_TRANSPARENT));
            break;
        case grUiGSSBorderTypePropVal::BORDER_TYPE_NORMAL:
            set_border(gnaNew<grUiBorder>(1, grColor::C_BLACK));
            break;
        case grUiGSSBorderTypePropVal::BORDER_TYPE_NATIVE:
            set_border(gnaNew<grUiBorderNative>());
            break;
        case grUiGSSBorderTypePropVal::BORDER_TYPE_MULTIPATCH:
            set_border(gnaNew<grUiBorderMultipatch>());
            break;
        }
    } else if (name == NAME_BORDER_WIDTH) {
        if (auto bd = border.rttiCast2<grUiBorder>()) {
            set_border(gnaNew<grUiBorder>(
                value.cast<grUiGSSUnitIPropVal>()->value,
                bd->get_color())); // FIXME: this is unoptimized as hell
        }
    } else if (name == NAME_BORDER_COLOR) {
        if (auto bd = border.rttiCast2<grUiBorder>()) {
            set_border(gnaNew<grUiBorder>(
                bd->get_width(),
                value.cast<grUiGSSColorPropVal>()->color)); // FIXME: this is unoptimized as hell
        }
    } else if (name == NAME_PADDING_LEFT) {
        grUiUnitInsets oldPadding = get_padding();
        set_padding({ value.cast<grUiGSSUnitIPropVal>()->value, oldPadding.top, oldPadding.right, oldPadding.bottom });
    } else if (name == NAME_PADDING_TOP) {
        grUiUnitInsets oldPadding = get_padding();
        set_padding({ oldPadding.left, value.cast<grUiGSSUnitIPropVal>()->value, oldPadding.right, oldPadding.bottom });
    } else if (name == NAME_PADDING_RIGHT) {
        grUiUnitInsets oldPadding = get_padding();
        set_padding({ oldPadding.left, oldPadding.top, value.cast<grUiGSSUnitIPropVal>()->value, oldPadding.bottom });
    } else if (name == NAME_PADDING_BOTTOM) {
        grUiUnitInsets oldPadding = get_padding();
        set_padding({ oldPadding.left, oldPadding.top, oldPadding.right, value.cast<grUiGSSUnitIPropVal>()->value });
    } else {
        return false;
    }
    return true;
}

void grUiWidget::applyStyleProperties(const grUiGSSOptimizedRule &styleSheet) {
    for (auto &[name, value] : styleSheet.properties) {
        applyStyleProperty(name, value);
    }
}

void grUiWidget::set_stylingEnabled(bool enabled) {
    if (enabled != m_stylingEnabled) {
        m_stylingEnabled = enabled;

        updateStyleHierarchy();
    }
}

void grUiWidget::set_styleSheet(gnaPointer<grUiGSSStyleSheet> ns) {
    m_styleSheet = std::move(ns);

    updateStyleHierarchy();
}

void grUiWidget::add_styleClass(gtl::PooledAString cls) {
    m_styleClass.push_back(cls);

    updateStyle();
}

void grUiWidget::set_styleClass(gtl::PooledAString cls) {
    m_styleClass.clear();
    add_styleClass(cls);
}

void grUiWidget::remove_styleClass(gtl::PooledAString cls) {
    std::erase(m_styleClass, cls);
    updateStyle();
}

void grUiWidget::updateStyle() {
    if (!m_stylingEnabled) return;

    if (!m_styleSheet) {
        m_actualStyleSheet = parent ? parent->m_actualStyleSheet : nullptr;
    } else {
        m_actualStyleSheet = m_styleSheet;
    }

    if (!m_actualStyleSheet) return;

    grUiGSSStyleSheet::FinalRuleList finalRuleList;
    m_actualStyleSheet->matchRulesAgainstWidget(this, finalRuleList);

    for (const grUiGSSOptimizedRule &rule : finalRuleList) {
        applyStyleProperties(rule);
    }
}

void grUiWidget::updateStyleHierarchy() {
    updateStyle();
}

void grUiWidget::set_styleStateBits(uint64_t bits) {
    if (m_styleStateBits == bits) return;

    m_styleStateBits = bits;
    updateStyle();
}

int grUiWidget::get_dpiScaleFactor() const {
    if (m_currentDpiScaleFactor <= 0) {
        return 100; // fallback value
    }
    return m_currentDpiScaleFactor;
}

void grUiWidget::set_dpiScaleFactor(int value) {
     if (value != m_currentDpiScaleFactor) {
        set_layoutDirty(true);
    }
    m_currentDpiScaleFactor = value;
}

void grUiWidget::updateDpiScaleFactor() {
    updateDpiScaleFactor(parent);
    updateStyleHierarchy();
}

void grUiWidget::updateDpiScaleFactor(gnaWeakPointer<grUiWidget> parent) {
    if (parent && parent->m_currentDpiScaleFactor > 0) {
        set_dpiScaleFactor(parent->m_currentDpiScaleFactor);
    } else if (m_platform) {
        set_dpiScaleFactor(m_platform->get_scaleFactor());
    } else {
        set_dpiScaleFactor(0);
    }
}

void grUiWidget::set_layoutDirty(bool value) {
    if (value) {
        m_measuredSizeDirty = true;
    }
    layoutDirty = value;
    if (parent) {
        if (value) {
            parent->markNeedsLayout();
            parent->set_layoutDirty(true);
        }
    }
}

void grUiWidget::pack() {
    pack({0, 0});
}

void grUiWidget::pack(grDimension minSize) {
    grDimension winSize = measure();
    if (minSize.width > winSize.width)
        winSize.width = minSize.width;
    if (minSize.height > winSize.height)
        winSize.height = minSize.height;
    set_size(winSize.width, winSize.height);
}

void grUiWidget::center(gnaWeakPointer<grUiWidget> parent) {
    grDimension dims = get_size();
    set_position(
        (parent->get_size().width - dims.width) / 2,
        (parent->get_size().height - dims.height) / 2);
}
