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
#include <grUi/Layout/Layout.h>
#include <vector>
#include <unordered_set>
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiWidgetLayout : public grUiWidget {
public:
    GTL_RTTI_DECLARE();

private:
    // std::vector<gnaPointer<grUiWidget>> children;
    gnaPointer<grUiWidget> m_firstChild;
    gnaWeakPointer<grUiWidget> m_lastChild;

    gnaPointer<grUiWidget> m_mouseEnteredWidget; // do not make this protected or public -- there is a special case here

    uint32_t m_numChildren;
    bool m_needsLayout          = false;
    bool m_isTransparentHitTest = false;

public:
    class Iterator : public std::bidirectional_iterator_tag {
        gnaWeakPointer<grUiWidgetLayout> m_layout;
        gnaWeakPointer<grUiWidget> m_current;

    public:
        explicit Iterator(gnaWeakPointer<grUiWidgetLayout> layout, gnaWeakPointer<grUiWidget> widget)
            : m_layout(std::move(layout)),
              m_current(std::move(widget)) {}

        Iterator &operator++() {
            m_current = m_current->nextSibling();
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy = *this;
            operator++();
            return copy;
        }

        Iterator &operator--() {
            if (m_current) {
                m_current = m_current->previousSibling();
            } else {
                m_current = m_layout->m_lastChild;
            }

            return *this;
        }

        Iterator operator--(int) {
            Iterator copy = *this;
            operator--();
            return copy;
        }

        gnaWeakPointer<grUiWidget> operator*() const {
            return m_current;
        }

        bool operator==(const Iterator &other) const {
            return other.m_current == m_current;
        }

        bool operator!=(const Iterator &other) const {
            return other.m_current != m_current;
        }
    };

    grUiWidgetLayout();
    template <typename... TContents>
    explicit grUiWidgetLayout(gnaPointer<grUiLayoutManager> layoutManager, gnaPointer<TContents>... contents)
    : grUiWidgetLayout() {
        // validate types
        using _ = typename std::enable_if<std::conjunction_v<
                std::integral_constant<bool, std::is_base_of_v<grUiWidget, TContents>>...>>::type;

        // constructor itself
        layout = std::move(layoutManager);
        (add(std::forward<gnaPointer<TContents>>(contents)), ...);
    }

    ~grUiWidgetLayout() override;

    grDimension initialMeasure(int biasedSize) override;
    grUiEnumContentBias get_contentBias() override;
    uint32_t get_layoutFlags() override;

    void insertAfter(gnaPointer<grUiWidget> child, gnaWeakPointer<grUiWidget> after, uint32_t pflags = 0);
    void insertBefore(gnaPointer<grUiWidget> child, gnaWeakPointer<grUiWidget> before, uint32_t pflags = 0);
    void add(gnaPointer<grUiWidget> child, uint32_t pflags = 0);
    void add(gnaPointer<grUiWidget> child, gnaPointer<gtlRcObject> layoutData, uint32_t pflags = 0) {
        child->set_layoutData(layoutData);
        add(child, pflags);
    }
    void remove(gnaWeakPointer<grUiWidget> child, uint32_t pflags = 0);
    [[deprecated]] void remove(gnaWeakPointer<grUiWidget> child, bool ignoreNonexistent) {
        remove(child, ignoreNonexistent ? PFLAG_IF_EXISTS : 0);
    }
    void removeAll();

    void update() override;
    void tick(float deltaTime) override;

    void drawClipped(grUiRenderer *, const grRectangle &rect) override;
    void draw(grUiRenderer *) override;
    void preDraw(grUiRenderer *render, const grRectangle &clipRect) override;
    void drawDebug(grUiRenderer *render) override;

    bool needsLayout();
    void markNeedsLayout();

    bool get_layoutDirty() override {
        // set_layoutDirty(grUiWidget::get_layoutDirty() || needsLayout());
        return grUiWidget::get_layoutDirty();
    }

    void releaseFocusFromChildren(bool suppressEvent = false);

    virtual gnaWeakPointer<grUiWidget> findByID(const gtl::Name &id) override;

    void updateStyleHierarchy() override;

    Iterator begin() {
        return Iterator(gnaWeakPointer(this), m_firstChild);
    }

    Iterator end() {
        return Iterator(gnaWeakPointer(this), nullptr);
    }

    gnaWeakPointer<grUiWidget> firstChild() {
        return m_firstChild;
    }

    uint32_t numChildren() const {
        return m_numChildren;
    }

    void updateNativeDevice(gnaWeakPointer<grUiWidgetLayout> parent) override;

    void set_transparentHitTest(bool value) {
        m_isTransparentHitTest = value;
    }

    bool is_transparentHitTest() const {
        return m_isTransparentHitTest;
    }

    bool hitTest(grPoint point) override;
    gtl::PooledAString get_actualCursor() const override;

    gnaPointer<grUiLayoutManager> layout;

    void forceLayout(bool ignoreCheck = true);

protected:
    void set_dpiScaleFactor(int value) override;
    void onBoundsChanged() override;
    void onLostParent() override;

private:
    // no actual need in mouseEnter
    bool onMouseLeave(grUiEventMouseLeave &ev);
    bool onKeyEvent(grUiEventKeyPress &ev);
    bool onTextInput(grUiEventTextInput &ev);
    bool onMouseMove(grUiEventMouseMove &ev);
    bool onMouseDown(grUiEventMouseDown &ev);
    bool onMouseUp(grUiEventMouseUp &ev);
    bool onMouseWheel(grUiEventMouseWheel &ev);
    bool onDefocus(grUiEventDefocus &ev);
    bool onObjectDrop(grUiEventObjectDrop &ev);
};
