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

#include "ImageLoaderSTBI.h"

#include <nxfResource/Open.h>

#include "grImg/Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb_image.h"

GTL_RTTI_DEFINE(grImg::AssetLoaderSTBI, GTL_RTTI_INHERITS(nxfAssetLoader));


const gtl::WIDECHAR *const *grImg::AssetLoaderSTBI::getFileExtensions() const {
    static const gtl::WIDECHAR *fileExtensions[] = {
        GTXT("png"),
        GTXT("jpg"),
        GTXT("tga"),
        nullptr
    };
    return fileExtensions;
}

gnaStatus grImg::AssetLoaderSTBI::loadAsset(const nxfAssetLoadContext &loadContext, gnaPointer<gtlObject> &resultObject) {
    gnaPointer<nxfBinaryResource> br;
    GNA_CHECK_STATUS(loadContext.primaryStream->readAll(br));

    int width, height, channelsInFile;
    unsigned char *textureDataOrig = stbi_load_from_memory((const stbi_uc *)br->data, br->size, &width, &height, &channelsInFile, 4);

    br = nullptr;

    if (textureDataOrig == NULL) {
        return { GNA_E_FAILED, GTXT("Failed to load image with STBI") };
    }

    auto *textureData = gtlNew unsigned char[width * height * 4];
    for (size_t i = 0; i < width * height * 4; i += 4) {
        textureData[i + 3] = textureDataOrig[i + 3];
        textureData[i + 2] = textureDataOrig[i];
        textureData[i + 1] = textureDataOrig[i + 1];
        textureData[i + 0] = textureDataOrig[i + 2];
    }
    stbi_image_free(textureDataOrig);

    gnaPointer<Image> img = gnaNew<Image>(static_cast<gtl::String>(loadContext.filename));
    img->loadBitmapData(width, height, IMGFMT_ARGB8_SRGB, textureData, 1);

    resultObject = img;

    return GNA_E_OK;
}
