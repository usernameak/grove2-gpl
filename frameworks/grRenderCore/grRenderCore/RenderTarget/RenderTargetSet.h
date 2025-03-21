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

#include <grRenderCore/RenderCoreDLL.h>
#include <grImg/Image.h>

namespace grRenderCore {
    class RenderTargetSet : public gtlRcObject {
    public:
        static constexpr size_t MAX_COLOR_IMAGES = 8;

        virtual gnaWeakPointer<grImg::Image> getColorImage(size_t imageIndex) const = 0;
        virtual gnaWeakPointer<grImg::Image> getDepthImage() const = 0;

        grDimension get_size() const {
            if (auto image = getColorImage(0)) {
                return image->get_size();
            } else {
                return getDepthImage()->get_size();
            }
        }

        virtual void invalidate() = 0;
        virtual bool isValid() const = 0;
    };

    class RenderTargetSetBuilder : public gtlRcObject {
    public:

        virtual void setColorImage(size_t imageIndex, gnaPointer<grImg::Image> image) = 0;
        virtual void setDepthImage(gnaPointer<grImg::Image> image) = 0;

        virtual gnaPointer<RenderTargetSet> build() = 0;
    };
}
