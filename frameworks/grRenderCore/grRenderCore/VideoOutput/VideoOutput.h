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

#include <gtlMemory/RcObject.h>
#include <grImg/Image.h>

namespace grRenderCore {
    class RenderTargetSet;

    class VideoOutput : public gtlRcObject {
    public:
        virtual ~VideoOutput() = default;

        virtual gnaWeakPointer<RenderTargetSet> getBackbufferRenderTargetSet() = 0;

        virtual void swapBuffers() = 0;

        /** Resizes the backbuffers of the video output.
         * Might be a no-op on some graphics APIs.
         *
         * @param width - new width of the backbuffer
         * @param height - new height of the backbuffer
         */
        virtual void resizeBackbuffers(uint32_t width, uint32_t height) {}

        /**
         * Prepares backbuffers for rendering.
         *
         * Note that there should be no references to the
         * backbuffer RTS held when this function is called
         * (even inside command lists), otherwise you might
         * get a fatal error.
         */
        virtual void prepareBackbuffers() {}
    };
}