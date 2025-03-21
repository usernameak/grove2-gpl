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

#include <gr2DCoords.h>
#include <grUi/Style/Background/Background.h>
#include <grUi/Style/Border/Border.h>
#include <gnaEventSink.h>
#include <grUi/Render/UiRenderer.h>
#include <grUi/Event/UIEvents.h>
#include <grUi/UiDLL.h>
#include <gtlString/PooledString.h>
#include <gtlTypeInfo/RTTI.h>
#include <grUi/Utils/UnitSize.h>
#include <grUi/Layout/LayoutEnums.h>

class grUiWidgetLayout;

class grUiNativeFramePlatform;
class grUiNativePlatformDevice;

class grUiGSSPropVal;
class grUiGSSOptimizedRule;
class grUiGSSStyleSheet;

class GR_UI_DLLIMPEXP grUiWidget : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    enum EnumVisibility {
        VISIBILITY_VISIBLE   = 0,
        VISIBILITY_INVISIBLE = 1,
        VISIBILITY_GONE      = 2
    };

    struct LayoutInfo {
    private:
        friend class grUiWidgetLayout;

        gnaPointer<grUiWidget> m_nextSibling;
        gnaWeakPointer<grUiWidget> m_previousSibling;

    public:
        gnaWeakPointer<grUiWidget> nextSibling() const {
            return m_nextSibling;
        }

        gnaWeakPointer<grUiWidget> previousSibling() const {
            return m_previousSibling;
        }
    };

private:
    LayoutInfo m_layoutInfo;
    gnaWeakPointer<grUiWidgetLayout> parent = nullptr; // it's not a grPointer because this one should not hold a reference

    bool layoutDirty = true;

    grPoint position{ 0, 0 };
    grDimension size{ 0, 0 };
    grUiUnitDimension m_minimumSize{ 0, 0 };
    grUiUnitInsets margin{ 0 };
    grUiUnitInsets padding{ 0 };

    grDimension m_lastMeasuredSize{ INT_MIN, INT_MIN };
    bool m_measuredSizeDirty = true;

    gnaPointer<gtlRcObject> layoutData;

    gnaPointer<grUiBorderBase> border = gnaNew<grUiBorder>(0, grColor::C_TRANSPARENT);

    bool focused        = false;
    bool m_ignoresMouse = false;

    gtl::Name m_id;
    uint64_t m_styleStateBits = 0;
    bool m_stylingEnabled     = true;
    int m_currentDpiScaleFactor;

    EnumVisibility m_visibility;

protected:
    grUiNativeFramePlatform *m_platform;
    grUiNativePlatformDevice *m_nativeDevice;

    friend class grUiRootWindowManager;

    gnaPointer<grUiGSSStyleSheet> m_styleSheet;
    gnaPointer<grUiGSSStyleSheet> m_actualStyleSheet;
    std::vector<gtl::PooledAString> m_styleClass;

private:
    grUiRenderer *m_renderer;

    bool m_isRootWidget = false;

    gtl::PooledAString m_cursor;

public:
    enum EnumInsetType {
        INSET_TEXT = 0,
        INSET_BASE = 1,
        INSET_BORDER = 2,
        INSET_MARGIN = 3
    };

    // warning: do not reorder this enum, StyleSheet.cpp depends on the order of bits
    enum EnumStyleStateBit : uint64_t {
        STSTBIT_HOVERED   = GTL_BIT(0),
        STSTBIT_PRESSED   = GTL_BIT(1),
        STSTBIT_FOCUSED   = GTL_BIT(2),
        STSTBIT_DISABLED  = GTL_BIT(3),
        STSTBIT_CHECKED   = GTL_BIT(4),
        STSTBIT_HIGHLIGHT = GTL_BIT(5)
    };

    enum ParentingFlag : uint32_t {
        PFLAG_NO_EVENTS = GTL_BIT(0),
        PFLAG_IF_EXISTS = GTL_BIT(1),
    };

    grUiWidget();
    virtual ~grUiWidget() override;

    virtual grDimension initialMeasure(int biasedSize) = 0;

    virtual grUiEnumContentBias get_contentBias() {
        return grUiEnumContentBias::CONTENT_BIAS_NONE;
    }

    virtual uint32_t get_layoutFlags() {
        return 0;
    }

    inline grDimension measure(int biasedSize = 0) {
        if (!m_measuredSizeDirty && get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_NONE) {
            return m_lastMeasuredSize;
        }

        m_measuredSizeDirty = false;

        uint32_t layoutFlags = get_layoutFlags();
        grDimension minSize  = m_minimumSize.toPixels(get_metricContext());
        if (get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_HORIZONTAL) {
            if (biasedSize < minSize.width) {
                biasedSize = minSize.width;
            }
        } else if (get_contentBias() == grUiEnumContentBias::CONTENT_BIAS_VERTICAL) {
            if (biasedSize < minSize.height) {
                biasedSize = minSize.height;
            }
        }
        grDimension dim = initialMeasure(biasedSize);
        if (!(layoutFlags & grUiLayoutFlags::FLAG_RESPECTS_MINIMUM_SIZE)) {
            if (dim.width < minSize.width) {
                dim.width = minSize.width;
            }
            if (dim.height < minSize.height) {
                dim.height = minSize.height;
            }
        }
        if (background) {
            grDimension bdim = get_insets(INSET_MARGIN).outsetDimension(background->get_minimumDimensions());
            if (dim.width < bdim.width) {
                dim.width = bdim.width;
            }
            if (dim.height < bdim.height) {
                dim.height = bdim.height;
            }
        }
        m_lastMeasuredSize = dim;
        return dim;
    }

    virtual void update();
    virtual void tick(float deltaTime) {}

    virtual gnaWeakPointer<grUiWidget> findNativeWindow();

    /**
     * @brief gets renderer that draws window containing this widget
     * <p>
     * <em>Note:</em> <b>Do not use except some special internal rendering usecases! </b>
     * </p>
     * @return renderer
     */
    grUiRenderer *get_windowRenderer() const;

    grUiNativeFramePlatform *get_nativeFrame() const {
        return m_platform;
    }

    grUiNativePlatformDevice *get_nativeDevice() const {
        return m_nativeDevice;
    }

    virtual void preDraw(grUiRenderer *render, const grRectangle &clipRect);
    virtual void drawClipped(grUiRenderer *render, const grRectangle &clipRect);
    virtual void draw(grUiRenderer *render);
    virtual void nativeWidgetDraw();
    virtual void nativeWidgetPreDraw(float deltaTime);
    virtual void nativeWidgetPresent();

    virtual void drawDebug(grUiRenderer *render);

    virtual gnaWeakPointer<grUiWidget> get_nativeViewportWidget();
    virtual bool usesNativeChildEventBehavior() { return false; }

    grInsets get_insets(EnumInsetType type) {
        if (type == INSET_MARGIN) {
            return margin.toPxInsets(get_metricContext());
        } else if (type == INSET_BORDER) {
            return margin.toPxInsets(get_metricContext()) +
                   border->getInsetsWithBackground(background).toPxInsets(get_metricContext());
        } else if (type == INSET_BASE) {
            return margin.toPxInsets(get_metricContext()) +
                   border->getInsetsWithBackground(background).toPxInsets(get_metricContext()) +
                   padding.toPxInsets(get_metricContext());
        } else {
            return get_extendedInsets(type);
        }
    }

    virtual grInsets get_extendedInsets(EnumInsetType type) {
        return get_insets(INSET_BASE);
    }

    grInsets get_baseInsets() { return get_insets(INSET_BASE); }

    gnaWeakPointer<grUiWidgetLayout> get_parent() const {
        return parent;
    }
    void set_parent(gnaWeakPointer<grUiWidgetLayout> val, uint32_t pflag = 0);

    bool isRootWidget() const;

    virtual void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> parent);

    virtual void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> parent);

    void set_layoutDirty(bool value);
    virtual bool get_layoutDirty() {
        return layoutDirty;
    }

    grPoint get_position() const {
        return position;
    }
    grDimension get_size() const {
        return size;
    }

    gnaPointer<gtlRcObject> get_layoutData() const {
        return layoutData;
    }
    void set_layoutData(gnaPointer<gtlRcObject> val) {
        if (val != this->layoutData) {
            set_layoutDirty(true);
        }
        this->layoutData = std::move(val);
    }

    gnaPointer<grUiBorderBase> get_border() const {
        return border;
    }
    void set_border(gnaPointer<grUiBorderBase> val) {
        if (val == this->border) return;

        set_layoutDirty(true);
        this->border = std::move(val);
        widgetBorderChanged();
    }

    grUiUnitInsets get_padding() const {
        return padding;
    }
    void set_padding(grUiUnitInsets val) {
        if (val != this->padding) {
            set_layoutDirty(true);
        }
        this->padding = val;
    }

    inline grUiUnitDimension get_minimumSize() const {
        return m_minimumSize;
    }

    inline void set_minimumSize(grUiUnitDimension val) {
        if (val != m_minimumSize) {
            set_layoutDirty(true);
        }
        m_minimumSize = val;
    }

    grUiUnitInsets get_margin() const {
        return margin;
    }
    void set_margin(grUiUnitInsets val) {
        if (val != this->margin) {
            set_layoutDirty(true);
        }
        this->margin = val;
    }

    grRectangle get_bounds() const {
        return { position.x, position.y, size.width, size.height };
    }

    void set_bounds(int x, int y, int width, int height);
    void set_bounds(const grRectangle &rc) { set_bounds(rc.x, rc.y, rc.width, rc.height); }

    void set_size(int width, int height) { set_bounds(position.x, position.y, width, height); }
    void set_size(grDimension dim) { set_size(dim.width, dim.height); }

    void set_position(int x, int y) { set_bounds(x, y, size.width, size.height); }
    void set_position(grPoint pt) { set_position(pt.x, pt.y); }

    EnumVisibility get_visibility() const { return m_visibility; }
    void set_visibility(EnumVisibility visibility) {
        if (m_visibility != visibility) {
            if (visibility == VISIBILITY_GONE || m_visibility == VISIBILITY_GONE) {
                set_layoutDirty(true);
            }
        }

        m_visibility = visibility;
    }

    bool get_focused() const {
        return focused;
    }

    bool get_fullyFocused();
    void set_focused(bool focused, bool suppressEvent = false);

    bool get_ignoresMouse() const {
        return m_ignoresMouse;
    }

    void set_ignoresMouse(bool ignoresMouse) {
        m_ignoresMouse = true;
    }

    const gtl::PooledAString &get_cursor() const {
        return m_cursor;
    }

    void set_cursor(const gtl::PooledAString &cursor) {
        m_cursor = cursor;
    }

    virtual gtl::PooledAString get_actualCursor() const {
        return get_cursor();
    }

    virtual bool hitTest(grPoint point) {
        grRectangle bounds = get_bounds();
        return point.x >= bounds.x && point.y >= bounds.y &&
               point.x < bounds.x + bounds.width && point.y < bounds.y + bounds.height;
    }

    grPoint computeRelativePosition(gnaPointer<grUiWidget> widget);

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::Name &id) {
        if (m_id == id) return this;
        return nullptr;
    }

    void set_id(const gtl::Name &id) {
        m_id = id;
    }

    const gtl::Name &get_id() const {
        return m_id;
    }

    auto get_styleStateBits() const { return m_styleStateBits; }
    void set_styleStateBits(uint64_t bits);

    void set_stylingEnabled(bool enabled);
    void set_styleSheet(gnaPointer<grUiGSSStyleSheet> ns);

    virtual bool applyStyleProperty(const gtl::PooledAString &name, gnaWeakPointer<grUiGSSPropVal> value);
    void updateStyle();
    virtual void updateStyleHierarchy();

    void add_styleClass(gtl::PooledAString cls);
    [[deprecated]] void set_styleClass(gtl::PooledAString cls);
    void remove_styleClass(gtl::PooledAString cls);
    const std::vector<gtl::PooledAString> get_styleClasses() const {
        return m_styleClass;
    }

    void updateDpiScaleFactor();
    int get_dpiScaleFactor() const;

    grUiMetricContext get_metricContext() const {
        grUiMetricContext cx{};
        cx.dpiScaleFactor = get_dpiScaleFactor();
        return cx;
    }

    LayoutInfo &get_layoutInfo() {
        return m_layoutInfo;
    }

    const LayoutInfo &get_layoutInfo() const {
        return m_layoutInfo;
    }

    gnaWeakPointer<grUiWidget> nextSibling() const {
        return get_layoutInfo().nextSibling();
    }

    gnaWeakPointer<grUiWidget> previousSibling() const {
        return get_layoutInfo().previousSibling();
    }

    void pack();
    void pack(grDimension minSize);
    void center(gnaWeakPointer<grUiWidget> parent);

    gnaPointer<grUiBackgroundBase> background = gnaNew<grUiBackground>();

    // bool boundsChanged = true;
    bool clipToBounds = false;

    gnaEventSink<grUiEventMouseMove> eventSink_mouseMove;
    gnaEventSink<grUiEventMouseDown> eventSink_mouseDown;
    gnaEventSink<grUiEventMouseUp> eventSink_mouseUp;
    gnaEventSink<grUiEventMouseWheel> eventSink_mouseWheel;
    gnaEventSink<grUiEventMouseLeave> eventSink_mouseLeave;
    gnaEventSink<grUiEventMouseEnter> eventSink_mouseEnter;

    gnaEventSink<grUiEventFocus> eventSink_focus;
    gnaEventSink<grUiEventDefocus> eventSink_defocus;
    gnaEventSink<grUiEventDefocus> eventSink_parentDefocus;

    gnaEventSink<grUiEventKeyPress> eventSink_keyEvent;
    gnaEventSink<grUiEventTextInput> eventSink_textInput;

    gnaEventSink<grUiEventObjectDrop> eventSink_objectDrop;

    // gnaEventSink<grUiEventCheckDrop> eventSink_checkDrop;

    void *key           = nullptr;
    void *extensionData = nullptr;

    gnaPointer<grUiWidget> withStyleClass(gtl::PooledAString cls) {
        add_styleClass(cls);
        return gnaWeakPointer<grUiWidget>(this);
    }

    gnaPointer<grUiWidget> withLayoutData(gnaPointer<gtlRcObject> val) {
        set_layoutData(std::move(val));
        return gnaWeakPointer<grUiWidget>(this);
    }

    gnaPointer<grUiWidget> withIgnoresMouse(bool ignoresMouse) {
        set_ignoresMouse(ignoresMouse);
        return gnaWeakPointer<grUiWidget>(this);
    }

protected:
    void set_isRootWidget(bool value);
    virtual void widgetBorderChanged() {}
    virtual void set_dpiScaleFactor(int value);
    virtual void onLostParent() {}
    virtual void onBoundsChanged() {}

    friend class grUiWidgetLayout;

    void updateDpiScaleFactor(gnaWeakPointer<grUiWidget> parent);

private:
    void applyStyleProperties(const grUiGSSOptimizedRule &styleSheet);
};
