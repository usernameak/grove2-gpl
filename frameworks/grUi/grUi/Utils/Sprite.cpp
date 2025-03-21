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

#include "Sprite.h"

#include <nxfResource/Asset/AssetManager.h>

grUiSprite::grUiSprite(gtl::PooledString resource)
    : minU(0.0f), minV(0.0f),
      maxU(1.0f), maxV(1.0f) {
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(resource, m_texture);
    if (m_texture) {
        auto dim  = m_texture->get_size();
        dstWidth  = (float)dim.width;
        dstHeight = (float)dim.height;
    } else {
        dstWidth = dstHeight = 0;
    }
}

grUiSprite::grUiSprite(
    gtl::PooledString resource, float dstWidth, float dstHeight)
    : minU(0.0f), minV(0.0f),
      maxU(1.0f), maxV(1.0f),
      dstWidth(dstWidth), dstHeight(dstHeight) {
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(resource, m_texture);
}

grUiSprite::grUiSprite(
    gtl::PooledString resource,
    float minU, float minV,
    float maxU, float maxV,
    float dstWidth, float dstHeight)
    : minU(minU), minV(minV),
      maxU(maxU), maxV(maxV),
      dstWidth(dstWidth), dstHeight(dstHeight) {
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(resource, m_texture);
}

grUiSprite::grUiSprite(const nxfRID &resource) : grUiSprite(static_cast<gtl::PooledString>(resource.name)) {}

grUiSprite::grUiSprite(const nxfRID &resource,
    float dstWidth, float dstHeight)
    : grUiSprite(static_cast<gtl::PooledString>(resource.name), dstWidth, dstHeight) {}

grUiSprite::grUiSprite(const nxfRID &resource,
    float minU, float minV,
    float maxU, float maxV,
    float dstWidth, float dstHeight)
    : grUiSprite(static_cast<gtl::PooledString>(resource.name), minU, minV, maxU, maxV, dstWidth, dstHeight) {}

grUiSprite::grUiSprite(gnaPointer<grImg::Image> texturePtr,
    float minU, float minV,
    float maxU, float maxV,
    float dstWidth, float dstHeight)
    : m_texture(std::move(texturePtr)),
      minU(minU), minV(minV),
      maxU(maxU), maxV(maxV),
      dstWidth(dstWidth), dstHeight(dstHeight) {
}

grUiSprite grUiSprite::createTexModalRect(
    const nxfRID &resource,
    int x, int y,
    int width, int height,
    int atlasWidth, int atlasHeight) {

    return createTexModalRect(
        static_cast<gtl::PooledString>(resource.name),
        x, y,
        width, height,
        atlasWidth, atlasHeight);
}

grUiSprite grUiSprite::createTexModalRect(
    gtl::PooledString resource,
    int x, int y,
    int width, int height,
    int atlasWidth, int atlasHeight) {

    gnaPointer<grImg::Image> image;
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(resource, image);

    return createTexModalRect(image, x, y, width, height, atlasWidth, atlasHeight);
}

grUiSprite grUiSprite::createTexModalRect(gnaPointer<grImg::Image> resource, int x, int y, int width, int height, int atlasWidth, int atlasHeight) {
    float minU = (float)x / (float)atlasWidth;
    float minV = (float)y / (float)atlasHeight;
    float maxU = (float)minU + ((float)width / (float)atlasWidth);
    float maxV = (float)minV + ((float)height / (float)atlasHeight);

    return { resource, minU, minV, maxU, maxV, (float)width, (float)height };
}
