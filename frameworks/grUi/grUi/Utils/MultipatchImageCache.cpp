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

#include "MultipatchImageCache.h"

#include <nxfResource/Asset/AssetManager.h>

gnaPointer<grUiMultipatchImage> grUiMultipatchImageCache::findOrLoadImage(const nxfRID &rid) {
    auto it = m_cachedImages.find(rid);
    if (it != m_cachedImages.end()) {
        return it->second;
    }

    return loadImage(rid);
}

void grUiMultipatchImageCache::dropCaches() {
    m_cachedImages.clear();
}

gnaPointer<grUiMultipatchImage> grUiMultipatchImageCache::loadImage(const nxfRID &rid) {
    if (!rid) {
        return nullptr;
    }

    GR_INFO(GTXT("Load multi-patch image: %ls"), rid.name.toCString());

    gnaPointer<grImg::Image> image;
    gnaSingleton<nxfAssetManager>()->loadOrGetAsset(rid.name, image, nxfAssetManager::LOAD_FLAG_NO_CACHE);

    auto mpimage = image ? gnaNew<grUiMultipatchImage>(image) : nullptr;
    m_cachedImages[rid] = mpimage;

    return mpimage;
}

GNA_SINGLETON_IMPLEMENT(grUiMultipatchImageCache);
