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

#include "BackgroundMultipatch.h"

#include <grUi/Utils/MultipatchImageCache.h>

GTL_RTTI_DEFINE(grUiBackgroundMultipatch, GTL_RTTI_INHERITS(grUiBackgroundBase));

grUiBackgroundMultipatch::grUiBackgroundMultipatch(nxfRID imageSource)
    : grUiBackgroundMultipatch(gnaSingleton<grUiMultipatchImageCache>()->findOrLoadImage(imageSource)) {
}

void grUiBackgroundMultipatch::draw(grUiRenderer *render, int x, int y, int width, int height) {
    if (!m_multipatchImage) return;

    const auto &horizontalPatchSizes = m_multipatchImage->get_horizontalPatchSizes();
    uint32_t totalFixedWidth         = 0;
    uint32_t totalStretchWidth       = 0;
    for (int patchX = 0; patchX < horizontalPatchSizes.size(); patchX += 2) {
        totalFixedWidth += horizontalPatchSizes[patchX];
    }
    for (int patchX = 1; patchX < horizontalPatchSizes.size(); patchX += 2) {
        totalStretchWidth += horizontalPatchSizes[patchX];
    }

    const auto &verticalPatchSizes = m_multipatchImage->get_verticalPatchSizes();
    uint32_t totalFixedHeight      = 0;
    uint32_t totalStretchHeight    = 0;
    for (int patchY = 0; patchY < verticalPatchSizes.size(); patchY += 2) {
        totalFixedHeight += verticalPatchSizes[patchY];
    }
    for (int patchY = 1; patchY < verticalPatchSizes.size(); patchY += 2) {
        totalStretchHeight += verticalPatchSizes[patchY];
    }

    uint32_t remainingWidth  = totalFixedWidth > width ? 0 : width - totalFixedWidth;
    uint32_t remainingHeight = totalFixedHeight > height ? 0 : height - totalFixedHeight;

    uint32_t offsetY    = 0;
    int32_t destOffsetY = 0;
    for (size_t patchY = 0; patchY < verticalPatchSizes.size(); patchY++) {
        uint32_t verticalPatchSize     = verticalPatchSizes[patchY];
        uint32_t verticalDestPatchSize = verticalPatchSize;
        if (patchY % 2 == 1) { // stretchable patch
            verticalDestPatchSize = (uint32_t)((uint64_t)verticalPatchSize * remainingHeight / totalStretchHeight);
        }

        uint32_t offsetX    = 0;
        int32_t destOffsetX = 0;
        for (size_t patchX = 0; patchX < horizontalPatchSizes.size(); patchX++) {
            uint32_t horizontalPatchSize     = horizontalPatchSizes[patchX];
            uint32_t horizontalDestPatchSize = horizontalPatchSize;
            if (patchX % 2 == 1) { // stretchable patch
                horizontalDestPatchSize = (uint32_t)((uint64_t)horizontalPatchSize * remainingWidth / totalStretchWidth);
            }

            render->drawSprite(
                (float)(x + destOffsetX),
                (float)(y + destOffsetY),
                grUiSprite(m_multipatchImage->get_croppedImage())
                    .crop(
                        (float)offsetX, (float)offsetY,
                        (float)horizontalPatchSize, (float)verticalPatchSize)
                    .withDstSize((float)horizontalDestPatchSize, (float)verticalDestPatchSize),
                m_tint);

            offsetX += horizontalPatchSize;
            destOffsetX += horizontalDestPatchSize;
        }
        offsetY += verticalPatchSize;
        destOffsetY += verticalDestPatchSize;
    }
}

grInsets grUiBackgroundMultipatch::get_multipatchInsets() const {
    if (!m_multipatchImage) return { 0, 0, 0, 0 };
    return m_multipatchImage->get_contentInsets();
}

grDimension grUiBackgroundMultipatch::get_minimumDimensions() const {
    if (!m_multipatchImage) return { 0, 0 };
    return m_multipatchImage->get_totalFixedSize();
}

void grUiBackgroundMultipatch::cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {
    gtlCloneable::cloneMembers(dest, cctx);

    auto cDest = dest.cast<grUiBackgroundMultipatch>();
    cDest->m_multipatchImage = m_multipatchImage;
    cDest->m_tint = m_tint;
}
