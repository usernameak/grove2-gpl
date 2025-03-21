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

#include <nxfResource/RID.h>
#include <gtlString/PooledString.h>
#include <grImg/Image.h>
#include <grUi/UiDLL.h>
#include <gtlMath2/MathUtils.h>

struct GR_UI_DLLIMPEXP grUiSprite {
    gnaPointer<grImg::Image> m_texture;
    float minU, minV;
    float maxU, maxV;
    float dstWidth, dstHeight;

    grUiSprite()
        : minU(0), minV(0), maxU(0), maxV(0), dstWidth(0), dstHeight(0) {}

    /**
     * @brief creates sprite from image resource with automatic width/height
     * <p>
     * note: this forces image to load
     * </p>
     * @param resource the resource to load
     */
    grUiSprite(const nxfRID &resource);

    grUiSprite(const nxfRID &resource, float dstWidth, float dstHeight);

    explicit grUiSprite(gtl::PooledString resource);
    explicit grUiSprite(gtl::PooledString resource, float dstWidth, float dstHeight);
    explicit grUiSprite(
        gtl::PooledString resource,
        float minU, float minV,
        float maxU, float maxV,
        float dstWidth, float dstHeight);

    grUiSprite(gnaPointer<grImg::Image> texturePtr)
        : m_texture(std::move(texturePtr)),
          dstWidth(m_texture->get_width()),
          dstHeight(m_texture->get_height()),
          minU(0.0f), minV(0.0f),
          maxU(1.0f), maxV(1.0f) {}

    grUiSprite(gnaPointer<grImg::Image> texturePtr, float dstWidth, float dstHeight)
        : m_texture(std::move(texturePtr)),
          dstWidth(dstWidth),
          dstHeight(dstHeight),
          minU(0.0f), minV(0.0f),
          maxU(1.0f), maxV(1.0f) {}

    grUiSprite(
        const nxfRID &resource,
        float minU, float minV,
        float maxU, float maxV,
        float dstWidth, float dstHeight);

    grUiSprite(
        gnaPointer<grImg::Image> texturePtr,
        float minU, float minV,
        float maxU, float maxV,
        float dstWidth, float dstHeight);

    static grUiSprite createTexModalRect(
        const nxfRID &resource,
        int x, int y,
        int width, int height,
        int atlasWidth, int atlasHeight);

    static grUiSprite createTexModalRect(
        gtl::PooledString resource,
        int x, int y,
        int width, int height,
        int atlasWidth, int atlasHeight);

    static grUiSprite createTexModalRect(
        gnaPointer<grImg::Image> resource,
        int x, int y,
        int width, int height,
        int atlasWidth, int atlasHeight);

    [[nodiscard]] grUiSprite withDstSize(float width, float height) const {
        return { m_texture, minU, minV, maxU, maxV, (float)width, (float)height };
    }

    [[nodiscard]] grUiSprite crop(float x, float y, float width, float height) const {
        return { m_texture,
            gtlMath2::lerp(minU, maxU, x / dstWidth),
            gtlMath2::lerp(minV, maxV, y / dstHeight),
            gtlMath2::lerp(minU, maxU, (x + width) / dstWidth),
            gtlMath2::lerp(minV, maxV, (y + height) / dstHeight),
            width, height };
    }

    explicit operator bool() const {
        return m_texture.hasValue();
    }
};
