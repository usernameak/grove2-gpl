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

#include <grImg/Image.h>
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiMultipatchImage : public gtlRcObject {
    std::vector<uint32_t> m_verticalPatchSizes;
    std::vector<uint32_t> m_horizontalPatchSizes;
    grInsets m_contentInsets;
    gnaPointer<grImg::Image> m_croppedImage;
    grDimension m_totalFixedSize;

public:
    explicit grUiMultipatchImage(gnaWeakPointer<grImg::Image> image);

    gnaWeakPointer<grImg::Image> get_croppedImage() const {
        return m_croppedImage;
    }

    const grInsets &get_contentInsets() const {
        return m_contentInsets;
    }

    const std::vector<uint32_t> &get_verticalPatchSizes() const {
        return m_verticalPatchSizes;
    }

    const std::vector<uint32_t> &get_horizontalPatchSizes() const {
        return m_horizontalPatchSizes;
    }

    grDimension get_totalFixedSize() const {
        return m_totalFixedSize;
    }

private:
    static void decodePatches(gnaWeakPointer<grImg::Image> image, std::vector<uint32_t> &patchSizes, uint32_t pixelStart, uint32_t pixelCount, uint32_t pixelStride, uint32_t *extraValue = nullptr);
    static gnaPointer<grImg::Image> cropImage(gnaWeakPointer<grImg::Image> image);
};
