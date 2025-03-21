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

#include <grMain.h>
#include <gtlUtil/Logging.h>

#include <gtlModule/ModuleLoader.h>
#include <grImg/ImgModule.h>
#include <grImg/Image.h>
#include <nxfIO/FileOutputStream.h>
#include <nxfResource/SystemResourceManager.h>
#include <nxfResource/Asset/AssetManager.h>
#include <nxfSerialization/NXFFileWriter.h>

int GR_MAIN_CALLCONV grMain(int argc, gtl::WIDECHAR *argv[]) {
    grLog_useWindowsDebugOutput = false;

    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(grImg));

    if (argc < 3) {
        GR_FATAL(GTXT(
            "invalid arguments.\n"
            "usage: textool [-linearsamp] [-linear] <source> <destination>\n"));
    }

    grImg::Image::SamplingMode samplingMode = grImg::Image::SAMP_POINT;
    grImg::Image::ColorSpace colorSpace = grImg::Image::COLORSPACE_SRGB;
    gtl::String source, destination;

    for (int i = 1; i < argc; i++) {
        if (gtl::StrCmp(argv[i], GTXT("-linearsamp")) == 0) {
            samplingMode = grImg::Image::SAMP_LINEAR;
        } else if (gtl::StrCmp(argv[i], GTXT("-linear")) == 0) {
            colorSpace = grImg::Image::COLORSPACE_LINEAR;
        } else {
            if (source.empty()) {
                source = argv[i];
                continue;
            }
            if (destination.empty()) {
                destination = argv[i];
            }
        }
    }

    if (source.empty() || destination.empty()) {
        GR_FATAL(GTXT(
            "invalid arguments.\n"
            "usage: textool [-linearsamp] [-linear] <source> <destination>\n"));
    }

    nxfSystemResourceManager *rm = new nxfSystemResourceManager;
    nxf_setRM(rm);

    gtl::String path;
    if (!rm->findResourcePathFromNativePath(source, path)) {
        GR_FATAL(GTXT("cannot find res path from native source path"));
    }

    gnaPointer<grImg::Image> image;
    gnaStatus status = gnaSingleton<nxfAssetManager>()->loadOrGetAsset<grImg::Image>(path, image);
    if (!status) {
        GR_FATAL(GTXT("failed to read image"));
    }
    image->m_samplingMode = samplingMode;
    image->setFormatToColorSpace(colorSpace);

    auto ostream = gnaNew<nxfFileOutputStream>();
    status       = ostream->open(destination);
    if (!status) {
        GR_FATAL(GTXT("failed to open image file for writing"));
    }
    nxfSerialization::NXFFileWriter writer(ostream);

    writer.writeNXFFile(image);

    writer.finish();

    return 0;
}
