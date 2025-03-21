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

#include "MultipatchImage.h"

grUiMultipatchImage::grUiMultipatchImage(gnaWeakPointer<grImg::Image> image) {
    if (image->get_numMipMaps() != 1) {
        GR_WARNING(GTXT("Image for multipatch image %ls has more than one mipmap, specifically %d"), image->get_name().toCString(), image->get_numMipMaps());
    }

    if (image->get_width() < 3 || image->get_height() < 3) {
        GR_FATAL(GTXT("Multipatch image %ls is too small"), image->get_name().toCString());
    }

    if (image->get_format() != grImg::ImageFormat::IMGFMT_ARGB8 &&
        image->get_format() != grImg::ImageFormat::IMGFMT_ARGB8_SRGB) {
        GR_FATAL(GTXT("Multipatch image %ls is not ARGB8/ARGB8_SRGB"), image->get_name().toCString());
    }

    decodePatches(image, m_horizontalPatchSizes, 1, image->get_width() - 2, 1);
    decodePatches(image, m_verticalPatchSizes, image->get_width(), image->get_height() - 2, image->get_width());

    std::vector<uint32_t> horizontalContentPatchSizes;
    std::vector<uint32_t> verticalContentPatchSizes;

    decodePatches(image, horizontalContentPatchSizes, image->get_width() * (image->get_height() - 1) + 1, image->get_width() - 2, 1);
    decodePatches(image, verticalContentPatchSizes, (image->get_width() * 2) - 1, image->get_height() - 2, image->get_width());

    if (horizontalContentPatchSizes.size() > 3 || verticalContentPatchSizes.size() > 3) {
        GR_FATAL(GTXT("Multipatch image %ls has more than nine content patches"), image->get_name().toCString());
    }

    m_totalFixedSize.width = 0;
    for (size_t i = 0; i < m_horizontalPatchSizes.size(); i += 2) {
        m_totalFixedSize.width += (int)m_horizontalPatchSizes[i];
    }

    m_totalFixedSize.height = 0;
    for (size_t i = 0; i < m_verticalPatchSizes.size(); i += 2) {
        m_totalFixedSize.height += (int)m_verticalPatchSizes[i];
    }

    m_contentInsets = { 0, 0, 0, 0 };
    if (horizontalContentPatchSizes.size() >= 1) { // NOLINT(readability-container-size-empty)
        m_contentInsets.left = (int)horizontalContentPatchSizes[0];
    }
    if (horizontalContentPatchSizes.size() >= 3) {
        m_contentInsets.right = (int)horizontalContentPatchSizes[2];
    }
    if (verticalContentPatchSizes.size() >= 1) { // NOLINT(readability-container-size-empty)
        m_contentInsets.top = (int)verticalContentPatchSizes[0];
    }
    if (verticalContentPatchSizes.size() >= 3) {
        m_contentInsets.bottom = (int)verticalContentPatchSizes[2];
    }

    m_croppedImage = cropImage(image);
}

void grUiMultipatchImage::decodePatches(gnaWeakPointer<grImg::Image> image, std::vector<uint32_t> &patchSizes, uint32_t pixelStart, uint32_t pixelCount, uint32_t pixelStride, uint32_t *extraValue) {
    // patchSizes format is following:
    // (<non-stretchable size>, <stretchable size>, <non-stretchable size>, <stretchable size>, ...)

    const uint8_t *data = image->get_bitmapData();

    int currentPatchLength       = 0;
    bool currentPatchStretchable = false;

    for (uint32_t i = pixelStart, j = 0; j < pixelCount; i += pixelStride, j++) {
        uint8_t b = data[i * 4];
        uint8_t g = data[i * 4 + 1];
        uint8_t r = data[i * 4 + 2];
        uint8_t a = data[i * 4 + 3];

        bool currentPixelStretchable = a == 255 && r == 0 && g == 0 && b == 0;

        if (a == 255 && r == 0 && g == 0 && b == 255 && extraValue) {
            (*extraValue)++;
        }

        if (currentPatchStretchable == currentPixelStretchable) {
            currentPatchLength++;
        } else {
            patchSizes.push_back(currentPatchLength);

            currentPatchLength      = 1;
            currentPatchStretchable = currentPixelStretchable;
        }
    }

    // push the last patch
    patchSizes.push_back(currentPatchLength);
}

gnaPointer<grImg::Image> grUiMultipatchImage::cropImage(gnaWeakPointer<grImg::Image> image) {
    auto croppedImage = gnaNew<grImg::Image>(image->get_name() + GTXT("<nine-patch content>"));

    const uint8_t *origData = image->get_bitmapData();

    uint32_t origWidth  = image->get_width();
    uint32_t origHeight = image->get_height();

    uint32_t width  = origWidth - 2;
    uint32_t height = origHeight - 2;

    auto *textureData = gtlNew unsigned char[width * height * 4];
    for (uint32_t y = 1; y < origHeight - 1; y++) {
        for (uint32_t x = 1; x < origWidth - 1; x++) {
            uint32_t origIdx = (x + y * origWidth);
            uint32_t idx     = ((x - 1) + (y - 1) * width);

            textureData[idx * 4]     = origData[origIdx * 4];
            textureData[idx * 4 + 1] = origData[origIdx * 4 + 1];
            textureData[idx * 4 + 2] = origData[origIdx * 4 + 2];
            textureData[idx * 4 + 3] = origData[origIdx * 4 + 3];
        }
    }

    croppedImage->loadBitmapData(
        width,
        height,
        image->get_format(),
        textureData,
        1);

    return croppedImage;
}
