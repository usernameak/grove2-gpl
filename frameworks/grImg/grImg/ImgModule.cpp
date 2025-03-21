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

#include "ImgModule.h"

#include <cassert>
#include <gtlModule/ModuleInfo.h>

#include "Image.h"
#include "Loaders/ImageLoaderSTBI.h"
#include "Loaders/ImageLoaderDDS.h"
#include "nxfSerialization/SerializationTypeRegistry.h"

static gnaPointer<grImg::Image> createFallbackImage() {
    gnaPointer<grImg::Image> image = gnaNew<grImg::Image>(GTXT("<NULL_TEXTURE>"));

    unsigned char *imageData = gtlNew unsigned char[32 * 32 * 4];
    for (uint32_t y = 0; y < 32; y++) {
        for (uint32_t x = 0; x < 32; x++) {
            unsigned char rb = x < 16 ^ y < 16 ? 0x00 : 0xFF;
            imageData[(x + y * 32) * 4 + 0] = rb;
            imageData[(x + y * 32) * 4 + 1] = 0x00;
            imageData[(x + y * 32) * 4 + 2] = rb;
            imageData[(x + y * 32) * 4 + 3] = 0xFF;
        }
    }

    image->loadBitmapData(32, 32, grImg::IMGFMT_ARGB8, imageData, 1);
    return image;
}

static void grImgStaticInit() {
    using namespace grImg;

    gnaSingleton<nxfSerialization::SerializationTypeRegistry>()->registerType<Image>("grImg::Image");

    gnaSingleton<nxfAssetManager>()->registerAssetLoader(gnaNew<AssetLoaderDDS>());
    gnaSingleton<nxfAssetManager>()->registerAssetLoader(gnaNew<AssetLoaderSTBI>());
    gnaSingleton<nxfAssetManager>()->registerFallbackObject<Image>(createFallbackImage());
}

static void grImgStaticRelease() {
    // TODO: release all the stuff
    assert(false);
}

GROVE2_DECLARE_MODULE(grImg){
    .moduleName        = "grImg",
    .moduleDescription = GTXT("Grove2 Image Loader"),
    .staticInit        = &grImgStaticInit,
    .staticRelease     = &grImgStaticRelease,
    .provideService    = nullptr
};
