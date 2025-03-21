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

#include "WidgetLayout.h"

#include <gtlUtil/Logging.h>

#include <grUi/Render/UiRenderer.h>

GTL_RTTI_DEFINE(grUiWidgetLayout, GTL_RTTI_INHERITS(grUiWidget));

void grUiWidgetLayout::update() {
    grUiWidget::update();

    forceLayout(false);
}

void grUiWidgetLayout::tick(float deltaTime) {
    grUiWidget::tick(deltaTime);

    auto child = firstChild();
    auto next  = child ? child->nextSibling() : nullptr;
    while (child) {
        child->tick(deltaTime);

        child = next;
        next  = child ? child->nextSibling() : nullptr;
    }
}

bool grUiWidgetLayout::needsLayout() {
    return m_needsLayout;
}

void grUiWidgetLayout::markNeedsLayout() {
    m_needsLayout = true;
}

void grUiWidgetLayout::onBoundsChanged() {
    grUiWidget::onBoundsChanged();

    markNeedsLayout();
}

grUiWidgetLayout::grUiWidgetLayout() : grUiWidget(), m_numChildren(0) {
    // register event handlers

    this->eventSink_mouseMove.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseMove), gnaEventPriority::PRIORITY_MONITOR);
    this->eventSink_mouseDown.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseDown), gnaEventPriority::PRIORITY_LOW);
    this->eventSink_mouseUp.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseUp), gnaEventPriority::PRIORITY_LOW);
    this->eventSink_mouseWheel.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseWheel), gnaEventPriority::PRIORITY_LOW);
    // no mouse enter event -- it should not be forwarded to children!
    this->eventSink_mouseLeave.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onMouseLeave), gnaEventPriority::PRIORITY_MONITOR);

    this->eventSink_textInput.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onTextInput), gnaEventPriority::PRIORITY_LOW);
    this->eventSink_keyEvent.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onKeyEvent), gnaEventPriority::PRIORITY_LOW);

    this->eventSink_defocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDefocus), gnaEventPriority::PRIORITY_MONITOR);
    this->eventSink_parentDefocus.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onDefocus), gnaEventPriority::PRIORITY_MONITOR);

    this->eventSink_objectDrop.addHandler(GNA_MEMBER_METHOD_EVENT_HANDLER(*this, onObjectDrop), gnaEventPriority::PRIORITY_MONITOR);
}

grUiWidgetLayout::~grUiWidgetLayout() {
    gnaPointer<grUiWidget> w = m_lastChild;
    while (w) {
        gnaPointer<grUiWidget> next = w->previousSibling();
        w->set_parent(nullptr);
        w->get_layoutInfo().m_previousSibling = nullptr;
        w->get_layoutInfo().m_nextSibling     = nullptr;
        w                                     = std::move(next);
    }
}

grDimension grUiWidgetLayout::initialMeasure(int biasedSize) {
    return layout.hasValue() ? layout->initialMeasure(this, biasedSize) : grDimension{ 0, 0 };
}

void grUiWidgetLayout::insertAfter(gnaPointer<grUiWidget> child, gnaWeakPointer<grUiWidget> after, uint32_t pflags) {
    insertBefore(std::move(child), after->nextSibling(), pflags);
}

void grUiWidgetLayout::insertBefore(gnaPointer<grUiWidget> child, gnaWeakPointer<grUiWidget> before, uint32_t pflags) {
    if (child->get_parent() == this) {
        GR_WARNING(GTXT("WTF? inserting widget twice"));
        return; // already here
    }
    if (child->get_parent()) {
        GR_FATAL(GTXT("child cannot have more than one parent"));
    }
    if (child->get_focused()) {
        releaseFocusFromChildren();
    }
    child->set_parent(this, pflags);
    m_numChildren++;
    if (before) {
        auto &childLayoutInfo              = child->get_layoutInfo();
        auto &beforeLayoutInfo             = before->get_layoutInfo();
        childLayoutInfo.m_previousSibling  = beforeLayoutInfo.m_previousSibling;
        beforeLayoutInfo.m_previousSibling = child;
        childLayoutInfo.m_nextSibling      = before;
        if (childLayoutInfo.m_previousSibling) {
            childLayoutInfo.m_previousSibling->get_layoutInfo().m_nextSibling = child;
        } else {
            m_firstChild = child;
        }
    } else {
        if (m_lastChild) {
            m_lastChild->get_layoutInfo().m_nextSibling = child;
        }
        child->get_layoutInfo().m_previousSibling = m_lastChild;
        if (!m_firstChild) {
            m_firstChild = child;
        }
        m_lastChild = child;
    }

    set_layoutDirty(true);
    markNeedsLayout();
    // child->updateRootWidget();
}

void grUiWidgetLayout::add(gnaPointer<grUiWidget> child, uint32_t pflags) {
    insertBefore(std::move(child), nullptr, pflags);
}

void grUiWidgetLayout::remove(gnaWeakPointer<grUiWidget> child, uint32_t pflags) {
    if (child->get_parent() != this) {
        if (pflags & PFLAG_IF_EXISTS)
            return;
        GR_FATAL(GTXT("removing child that does not exist"));
    }
    child->set_parent(nullptr, pflags);

    if (m_mouseEnteredWidget == child) {
        // emit mouse leave event
        grUiEventMouseLeave ev;
        child->eventSink_mouseLeave.emit(ev);

        m_mouseEnteredWidget = nullptr;
    }

    // TODO: optimize this without breaking anything
    [[maybe_unused]] gnaPointer<grUiWidget> temp(child);

    gnaPointer<grUiWidget> prevSibling = child->previousSibling();
    gnaPointer<grUiWidget> nextSibling = child->nextSibling();

    if (nextSibling) {
        nextSibling->get_layoutInfo().m_previousSibling = prevSibling;
    }
    if (prevSibling) {
        prevSibling->get_layoutInfo().m_nextSibling = nextSibling;
    }

    child->get_layoutInfo().m_previousSibling = nullptr;
    child->get_layoutInfo().m_nextSibling     = nullptr;
    if (m_lastChild == child) {
        m_lastChild = prevSibling;
    }
    if (m_firstChild == child) {
        m_firstChild = nextSibling;
    }
    m_numChildren--;

    set_layoutDirty(true);
    markNeedsLayout();
}

void grUiWidgetLayout::removeAll() {
    gnaPointer<grUiWidget> w = m_lastChild;
    while (w) {
        gnaPointer<grUiWidget> next = w->previousSibling();
        w->set_parent(nullptr);
        w->get_layoutInfo().m_previousSibling = nullptr;
        w->get_layoutInfo().m_nextSibling     = nullptr;
        w                                     = next;
    }

    m_firstChild  = nullptr;
    m_lastChild   = nullptr;
    m_numChildren = 0;

    if (m_mouseEnteredWidget) {
        // emit mouse leave event
        grUiEventMouseLeave ev;
        m_mouseEnteredWidget->eventSink_mouseLeave.emit(ev);
    }
    m_mouseEnteredWidget = nullptr;

    set_layoutDirty(true);
    markNeedsLayout();
}

bool grUiWidgetLayout::onMouseMove(grUiEventMouseMove &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    // TODO: this should have some kind of z-index, eh?

    auto oldMouseEnteredWidget = std::move(m_mouseEnteredWidget);
    m_mouseEnteredWidget       = nullptr;

    auto child = m_lastChild;
    while (child) {
        if (child->get_ignoresMouse() || child->get_visibility() != VISIBILITY_VISIBLE) {
            child = child->previousSibling();
            continue;
        }

        if (child->hitTest({ ev.x, ev.y })) {
            m_mouseEnteredWidget = child;
            break;
        }
        child = child->previousSibling();
    }

    if (m_mouseEnteredWidget != oldMouseEnteredWidget && oldMouseEnteredWidget) {
        grUiEventMouseLeave ev1;
        oldMouseEnteredWidget->eventSink_mouseLeave.emit(ev1);
    }
    if (m_mouseEnteredWidget) {
        if (m_mouseEnteredWidget != oldMouseEnteredWidget) {
            grUiEventMouseEnter ev1;
            m_mouseEnteredWidget->eventSink_mouseEnter.emit(ev1);
        }

        int cx = m_mouseEnteredWidget->get_position().x;
        int cy = m_mouseEnteredWidget->get_position().y;

        grUiEventMouseMove ev1 = ev;
        ev1.x -= cx;
        ev1.y -= cy;
        m_mouseEnteredWidget->eventSink_mouseMove.emit(ev1);
    }

    return true;
}

bool grUiWidgetLayout::onMouseDown(grUiEventMouseDown &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    set_focused(true);

    if (m_mouseEnteredWidget) {
        gnaPointer child = m_mouseEnteredWidget;

        int cx = child->get_position().x;
        int cy = child->get_position().y;

        grUiEventMouseDown ev1 = ev;
        ev1.x -= cx;
        ev1.y -= cy;
        if (!child->eventSink_mouseDown.emit(ev1)) {
            return false;
        }
    }

    return true;
}

bool grUiWidgetLayout::onMouseUp(grUiEventMouseUp &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    if (m_mouseEnteredWidget) {
        gnaPointer child = m_mouseEnteredWidget;

        int cx = child->get_position().x;
        int cy = child->get_position().y;

        grUiEventMouseUp ev1 = ev;
        ev1.x -= cx;
        ev1.y -= cy;
        if (!child->eventSink_mouseUp.emit(ev1)) {
            return false;
        }
    }
    return true;
}

bool grUiWidgetLayout::onMouseWheel(grUiEventMouseWheel &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    if (m_mouseEnteredWidget) {
        gnaPointer child = m_mouseEnteredWidget;

        int cx = child->get_position().x;
        int cy = child->get_position().y;

        grUiEventMouseWheel ev1 = ev;
        ev1.x -= cx;
        ev1.y -= cy;

        child->eventSink_mouseWheel.emit(ev1);
    }
    return true;
}

bool grUiWidgetLayout::onDefocus(grUiEventDefocus &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    for (auto child : *this) {
        if (child->get_focused()) {
            child->eventSink_parentDefocus.emit(ev);
        }
    }

    return true;
}

bool grUiWidgetLayout::onObjectDrop(grUiEventObjectDrop &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    if (m_mouseEnteredWidget) {
        gnaPointer child = m_mouseEnteredWidget;

        grUiEventObjectDrop ev1 = ev;

        int cx = child->get_position().x;
        int cy = child->get_position().y;

        ev1.x -= cx;
        ev1.y -= cy;

        if (!child->eventSink_objectDrop.emit(ev1)) {
            return false;
        }
    }

    return true;
}

void grUiWidgetLayout::forceLayout(bool ignoreCheck) {
    if (ignoreCheck || needsLayout()) {
        m_needsLayout = false;
        if (layout) {
            layout->layout(this);
        }
    }

    for (auto child : *this)
        child->set_layoutDirty(false);

    for (auto child : *this) {
        child->update();
    }
}

bool grUiWidgetLayout::onMouseLeave(grUiEventMouseLeave &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    if (m_mouseEnteredWidget) {
        gnaPointer child = m_mouseEnteredWidget;
        child->eventSink_mouseLeave.emit(ev);

        m_mouseEnteredWidget = nullptr;
    }

    return true;
}

bool grUiWidgetLayout::onKeyEvent(grUiEventKeyPress &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    for (auto child : *this) {
        if (child->get_focused()) {
            if (!child->eventSink_keyEvent.emit(ev)) return false;
        }
    }
    return true;
}

void grUiWidgetLayout::releaseFocusFromChildren(bool suppressEvent) {
    if (usesNativeChildEventBehavior())
        return;

    gnaPointer<grUiWidget> widget = m_firstChild;
    while (widget) {
        widget->set_focused(false, suppressEvent);
        widget = widget->nextSibling();
    }
}

gnaWeakPointer<grUiWidget> grUiWidgetLayout::findByID(const gtl::Name &id) {
    gnaWeakPointer<grUiWidget> widget = grUiWidget::findByID(id);
    if (widget) return widget;

    for (auto child : *this) {
        widget = child->findByID(id);
        if (widget) return widget;
    }

    return nullptr;
}

bool grUiWidgetLayout::onTextInput(grUiEventTextInput &ev) {
    if (usesNativeChildEventBehavior())
        return true;

    for (auto child : *this) {
        if (child->get_focused()) {
            child->eventSink_textInput.emit(ev);
        }
    }
    return true;
}

void grUiWidgetLayout::drawClipped(grUiRenderer *render, const grRectangle &rect) {
    grUiWidget::draw(render);

    gtlMath2::Matrix3x2f &transform    = render->get_transform();
    gtlMath2::Matrix3x2f origTransform = transform;

    for (const auto &child : *this) {
        if (child->get_visibility() != VISIBILITY_VISIBLE) continue;

        grRectangle childBounds  = child->get_bounds();
        grRectangle intersection = childBounds.intersect(rect);
        if (intersection.width <= 0 || intersection.height <= 0) {
            continue;
        }

        transform = origTransform;
        transform.translate(gtlMath2::Vector2f{ (float)child->get_position().x, (float)child->get_position().y });

        if (child->clipToBounds) {
            render->pushClip({ 0, 0, child->get_size().width, child->get_size().height });
        }

        child->drawClipped(render, { intersection.x - childBounds.x, intersection.y - childBounds.y, intersection.width, intersection.height });

        if (child->clipToBounds) {
            render->popClip();
        }
    }

    transform = origTransform;
}

void grUiWidgetLayout::draw(grUiRenderer *render) {
    drawClipped(render, { 0, 0, get_size().width, get_size().height });
}

void grUiWidgetLayout::preDraw(grUiRenderer *render, const grRectangle &clipRect) {
    grUiWidget::preDraw(render, clipRect);
    for (const auto &child : *this) {
        if (child->get_visibility() != VISIBILITY_VISIBLE) continue;

        grRectangle childBounds  = child->get_bounds();
        grRectangle intersection = childBounds.intersect(clipRect);
        if (intersection.width <= 0 || intersection.height <= 0) {
            continue;
        }

        child->preDraw(
            render,
            { intersection.x - childBounds.x,
                intersection.y - childBounds.y,
                intersection.width,
                intersection.height });
    }
}

void grUiWidgetLayout::drawDebug(grUiRenderer *render) {
    grUiWidget::drawDebug(render);

    gtlMath2::Matrix3x2f &transform    = render->get_transform();
    gtlMath2::Matrix3x2f origTransform = transform;

    for (const auto &child : *this) {
        if (child->get_visibility() != VISIBILITY_VISIBLE) continue;

        transform = origTransform;
        transform.translate(gtlMath2::Vector2f{ (float)child->get_position().x, (float)child->get_position().y });

        child->drawDebug(render);
    }

    transform = origTransform;
}

void grUiWidgetLayout::updateStyleHierarchy() {
    grUiWidget::updateStyleHierarchy();

    for (gnaWeakPointer<grUiWidget> child : *this) {
        child->updateStyleHierarchy();
    }
}

void grUiWidgetLayout::set_dpiScaleFactor(int value) {
    grUiWidget::set_dpiScaleFactor(value);

    for (gnaWeakPointer<grUiWidget> child : *this) {
        child->updateDpiScaleFactor(this);
    }
}

grUiEnumContentBias grUiWidgetLayout::get_contentBias() {
    if (layout) {
        return layout->get_contentBias(this);
    }
    return grUiWidget::get_contentBias();
}

uint32_t grUiWidgetLayout::get_layoutFlags() {
    if (layout) {
        return layout->get_flags();
    }
    return grUiWidget::get_layoutFlags();
}

void grUiWidgetLayout::updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> parent) {
    grUiWidget::updateNativeDevice(parent);

    for (gnaWeakPointer<grUiWidget> child : *this) {
        child->updateNativeDevice(this);
    }
}

bool grUiWidgetLayout::hitTest(grPoint point) {
    if (!grUiWidget::hitTest(point)) return false;
    if (!m_isTransparentHitTest) return true;

    auto child = m_lastChild;
    while (child) {
        if (child->get_ignoresMouse() || child->get_visibility() != VISIBILITY_VISIBLE) {
            child = child->previousSibling();
            continue;
        }

        if (child->hitTest(point - get_position())) {
            return true;
        }
        child = child->previousSibling();
    }
    return false;
}

void grUiWidgetLayout::onLostParent() {
    if (usesNativeChildEventBehavior())
        return;

    if (m_mouseEnteredWidget) {
        grUiEventMouseLeave ev{};

        gnaPointer child = m_mouseEnteredWidget;
        child->eventSink_mouseLeave.emit(ev);

        m_mouseEnteredWidget = nullptr;
    }
}

gtl::PooledAString grUiWidgetLayout::get_actualCursor() const {
    if (m_mouseEnteredWidget) {
        gtl::PooledAString name = m_mouseEnteredWidget->get_actualCursor();
        if (!name.empty()) {
            return name;
        }
    }
    return grUiWidget::get_actualCursor();
}
