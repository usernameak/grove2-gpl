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

#include "ImageLoaderDDS.h"
#include "nxfSerialization/PrimitiveSerializers.h"

#include <grImg/Image.h>
#include <nxfResource/Open.h>

GTL_RTTI_DEFINE(grImg::AssetLoaderDDS, GTL_RTTI_INHERITS(nxfAssetLoader));

struct grDDSPixFmt {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwFourCC;
    uint32_t dwRGBBitCount;
    uint32_t dwRBitMask;
    uint32_t dwGBitMask;
    uint32_t dwBBitMask;
    uint32_t dwABitMask;
};

struct grDDSHeader {
    uint32_t dwSize;
    uint32_t dwFlags;
    uint32_t dwHeight;
    uint32_t dwWidth;
    uint32_t dwPitchOrLinearSize;
    uint32_t dwDepth;
    uint32_t dwMipMapCount;
    uint32_t dwReserved1[11];
    grDDSPixFmt ddspf;
    uint32_t dwCaps;
    uint32_t dwCaps2;
    uint32_t dwCaps3;
    uint32_t dwCaps4;
    uint32_t dwReserved2;
};

const gtl::WIDECHAR *const *grImg::AssetLoaderDDS::getFileExtensions() const {
    static const gtl::WIDECHAR *fileExtensions[] = {
        GTXT("dds"),
        nullptr
    };
    return fileExtensions;
}

gnaStatus grImg::AssetLoaderDDS::loadAsset(const nxfAssetLoadContext &loadContext, gnaPointer<gtlObject> &resultObject) {
    nxfInputStream &stream = *loadContext.primaryStream;

    uint32_t magic;
    GNA_CHECK_STATUS(stream >> magic);

    if (magic != GNA_FOURCC('DDS ')) {
        return {
            GNA_E_INVALID_DATA_FORMAT,
            gtl::String::format(
                GTXT("DDS has invalid magic (file %ls)"),
                loadContext.filename.toCString())
        };
    }

    // FIXME: might not be portable
    grDDSHeader header;
    GNA_CHECK_STATUS(stream.read(&header, sizeof(header)));

    if (header.dwSize != sizeof(grDDSHeader)) {
        return {
            GNA_E_INVALID_DATA_FORMAT,
            gtl::String::format(
                GTXT("DDS has invalid header size (file %ls)"),
                loadContext.filename.toCString())
        };
    }

    grImg::ImageFormat format;
    if (header.ddspf.dwFlags & 0x4) {
        // fourcc-based format
        switch (header.ddspf.dwFourCC) {
        case GNA_FOURCC('DX10'): {
            // TODO: dx10 format support
            return {
                GNA_E_UNSUPPORTED,
                gtl::String::format(
                    GTXT("DDS DX10 fourcc isn't currently supported (file %ls)"),
                    loadContext.filename.toCString())
            };
        }
        case GNA_FOURCC('DXT1'):
            format = IMGFMT_DXT1_SRGB;
            break;
        case GNA_FOURCC('DXT2'):
        case GNA_FOURCC('DXT3'):
            format = IMGFMT_DXT3_SRGB;
            break;
        case GNA_FOURCC('DXT4'):
        case GNA_FOURCC('DXT5'):
            format = IMGFMT_DXT5_SRGB;
            break;
        default:
            return {
                GNA_E_INVALID_DATA_FORMAT,
                gtl::String::format(
                    GTXT("Invalid DDS fourcc (file %ls)"),
                    loadContext.filename.toCString())
            };
        }
    } else if (header.ddspf.dwFlags & 0x40) {
        // RGB image
        bool hasAlpha = header.ddspf.dwFlags & 0x1;
        if (hasAlpha &&
            header.ddspf.dwRGBBitCount == 32 &&
            header.ddspf.dwRBitMask == 0x00ff0000 &&
            header.ddspf.dwGBitMask == 0x0000ff00 &&
            header.ddspf.dwBBitMask == 0x000000ff &&
            header.ddspf.dwABitMask == 0xff000000) {
            format = IMGFMT_ARGB8_SRGB;
        } else {
            return {
                GNA_E_UNSUPPORTED,
                gtl::String::format(
                    GTXT("Unsupported DDS pixfmt (file %ls)"),
                    loadContext.filename.toCString())
            };
        }
    } else {
        return {
            GNA_E_UNSUPPORTED,
            gtl::String::format(
                GTXT("Unsupported DDS flag combination (file %ls)"),
                loadContext.filename.toCString())
        };
    }

    int numMipMaps = 1;
    if (header.dwFlags & 0x20000) {
        numMipMaps = header.dwMipMapCount;
    }

    size_t totalSize = 0;
    for (int i = 0; i < numMipMaps; i++) {
        totalSize += Image::calculateByteSize(format, header.dwWidth, header.dwHeight, i);
    }

    unsigned char *data = gtlNew unsigned char[totalSize];
    GNA_CHECK_STATUS(stream.read(data, totalSize));

    gnaPointer<Image> img = gnaNew<Image>(static_cast<gtl::String>(loadContext.filename));
    img->loadBitmapData(header.dwWidth, header.dwHeight, format, data, numMipMaps);

    resultObject = img;

    return GNA_E_OK;
}
