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

#include <grUi/Widget/WidgetLayout.h>
#include <grUi/UiDLL.h>
#include <grUi/Drag/DragContext.h>

class grUiFrameCaptionInterface;

class GR_UI_DLLIMPEXP grUiFrame : public grUiWidgetLayout {
    gtl::String m_title;
    gnaPointer<grUiWidget> contentWidget;
    gnaPointer<grUiWidget> m_captionWidget;
    grUiFrameCaptionInterface *m_captionInterface;

    bool m_needsCaptionRefresh = false;
    bool m_autoPack = false;

    class grUiFrameDragContext : public grUiDragContext {
        gnaPointer<grUiFrame> m_frame;
        grPoint m_startOffset;
    public:
        grUiFrameDragContext(gnaPointer<grUiFrame> frame, grPoint startOffset, int button);

        void dragMove(gnaWeakPointer<grUiRootWindowManager> root, int x, int y, int dx, int dy) override;
        void dragRelease(gnaWeakPointer<grUiRootWindowManager> root) override;
    };

public:
    GTL_RTTI_DECLARE();

    grUiFrame();
    virtual ~grUiFrame() override;

    void update() override;

    void set_title(gtl::String title);
    gtl::String get_title();
    void closeFrame();

    void set_contentWidget(gnaPointer<grUiWidget> widget);

    grDimension initialMeasure(int biasedSize) override;

    gnaWeakPointer<grUiWidget> get_contentWidget() {
        return contentWidget;
    }

    gnaWeakPointer<grUiWidget> get_nativeViewportWidget() override {
        return get_contentWidget();
    }

    void handleParentChanged(gnaWeakPointer<grUiWidgetLayout> parent) override;

    enum PopupFlags : uint32_t {
        POPF_NOPACK = 1,
        POPF_NOCENTER = 2,
    };

    void displayPopup(gnaWeakPointer<grUiWidgetLayout> windowManager, uint32_t flags = 0);
    void togglePopup(gnaWeakPointer<grUiWidgetLayout> windowManager, uint32_t flags = 0);

    void bringToFront();

    void set_autoPack(bool autoPack) {
        m_autoPack = autoPack;
    }
    bool get_autoPack() const {
        return m_autoPack;
    }

    gnaEventSink<grUiEventPerformAction> eventSink_windowClose;
    gnaEventSink<grUiEventPerformAction> eventSink_windowOpen;

protected:
    void widgetBorderChanged() override;

    void onLostParent() override;
    void onBoundsChanged() override;

private:
    void updateCaptionDimensions();

    bool onMouseDown(const grUiEventMouseDown &ev);
    bool onMouseUp(const grUiEventMouseUp &ev);
};
