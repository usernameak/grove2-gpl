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

#include "AssetManager.h"

#include <ranges>
#include <nxfResource/MutableResourceManager.h>

#include <nxfSerialization/NXFFileReader.h>
#include <nxfSerialization/NXFFileWriter.h>

GTL_RTTI_DEFINE(nxfAssetLoader, GTL_RTTI_INHERITS(gtlRcObject));
GTL_RTTI_DEFINE(nxfAssetLoaderNXF, GTL_RTTI_INHERITS(nxfAssetLoader));

bool nxfAssetLoaderNXF::requiresMetadataObject() const {
    return false;
}

const gtl::WIDECHAR *const *nxfAssetLoaderNXF::getFileExtensions() const {
    static const gtl::WIDECHAR *fileExtensions[] = {
        GTXT("nxf"),
        nullptr
    };
    return fileExtensions;
}

gnaStatus nxfAssetLoaderNXF::loadAsset(const nxfAssetLoadContext &loadContext, gnaPointer<gtlObject> &resultObject) {
    nxfSerialization::NXFFileReader reader(loadContext.primaryStream);
    GNA_CHECK_STATUS(reader.readNXFFile());

    resultObject = reader.getRootObject();
    if (!resultObject) {
        return {
            GNA_E_FAILED,
            gtl::String::format(GTXT("`%ls`: nxf file: root object missing"), loadContext.filename)
        };
    }
    return GNA_E_OK;
}

GNA_SINGLETON_IMPLEMENT(nxfAssetManager);

nxfAssetManager::nxfAssetManager() {
    registerAssetLoader(gnaNew<nxfAssetLoaderNXF>());
}

void nxfAssetManager::registerAssetLoader(gnaPointer<nxfAssetLoader> assetLoader) {
    auto *const *extensions = assetLoader->getFileExtensions();
    auto *const *curExtension = extensions;
    while (*curExtension) {
        assert(!m_registeredFileExtensions.contains(*curExtension));

        m_registeredFileExtensions[*curExtension] = std::move(assetLoader);
        curExtension++;
    }
}

void nxfAssetManager::registerFallbackObject(const gtlRTTI *objectType, gnaPointer<gtlObject> object) {
    assert(!m_fallbackObjects.contains(objectType));

    m_fallbackObjects[objectType] = std::move(object);
}

gnaStatus nxfAssetManager::loadOrGetAsset(
    gtl::PooledString filename,
    const gtlRTTI *objectType,
    gnaPointer<gtlObject> &object,
    uint32_t loadFlags) {

    object = nullptr; // clear it to avoid weird stuff on failures

    if (!(loadFlags & LOAD_FLAG_NO_FALLBACK)) {
        gnaStatus status = loadOrGetAsset(filename, objectType, object, loadFlags | LOAD_FLAG_NO_FALLBACK);
        if (!status) {
            const gtlRTTI *rtti = objectType;
            while (rtti) {
                if (auto it = m_fallbackObjects.find(rtti); it != m_fallbackObjects.end()) {
                    object = it->second;
                    break;
                }
                rtti = rtti->get_baseClass();
            }
        }
        return status;
    }

    if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
        if (auto it = m_loadedObjects.find(filename); it != m_loadedObjects.end()) {
            CachedAssetInfo &info = it->second;
            object                = info.object;
            return info.status;
        }
    }

    auto index = filename.lastIndexOf(GTXT('.'));
    if (index == filename.size()) {
        if (auto it = m_cachedAssetLinks.find(filename); it != m_cachedAssetLinks.end()) {
            if (it->second.status) {
                return loadOrGetAsset(it->second.targetFilename, object, loadFlags | LOAD_FLAG_NO_DETECT_EXT);
            } else {
                return it->second.status;
            }
        }

        if (!(loadFlags & LOAD_FLAG_NO_DETECT_EXT)) {
            // try detecting the file extension (SLOW!.. for now)
            for (const auto &ext : m_registeredFileExtensions | std::views::keys) {
                auto modifiedFilename = static_cast<gtl::String>(filename);
                modifiedFilename += GTXT('.');
                modifiedFilename += ext;

                gnaStatus status = loadOrGetAsset(modifiedFilename, object, loadFlags | LOAD_FLAG_NO_DETECT_EXT);
                if (status.errorCode == GNA_E_FILE_NOT_FOUND) continue;

                // in any other cases, fail or succeed early.
                if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
                    CachedAssetLinkInfo &info = m_cachedAssetLinks[filename];
                    info.targetFilename       = modifiedFilename;
                    info.status               = GNA_E_OK;
                }
                return status;
            }
        }

        // cache a failure
        gnaStatus status = {
            GNA_E_INVALID_ARGUMENT,
            gtl::String::format(
                GTXT("Missing file extension in loadOrGetAsset(`%ls`)"),
                filename.toCString())
        };
        if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
            CachedAssetLinkInfo &info = m_cachedAssetLinks[filename];
            info.targetFilename       = {};
            info.status               = status;
        }
        return status;
    }

    auto it = m_registeredFileExtensions.find(filename.substr(index + 1));
    if (it == m_registeredFileExtensions.end()) {
        gnaStatus status = {
            GNA_E_INVALID_ARGUMENT,
            gtl::String::format(
                GTXT("Cannot find asset loader in loadOrGetAsset(`%ls`)"),
                filename.toCString())
        };
        if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
            cacheFailure(filename, status);
        }
        return status;
    }

    gnaWeakPointer<nxfAssetLoader> loader = it->second;

    nxfResourceManager *resMan = nxf_getRM();
    nxfAssetLoadContext ctx{
        .resourceManager = resMan,
        .filename        = filename
    };
    gnaStatus status = resMan->get_resourceStream(static_cast<gtl::String>(filename), ctx.primaryStream);
    if (!status) {
        if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
            cacheFailure(filename, status);
        }
        return status;
    }
    if (it->second->requiresMetadataObject()) {
        // TODO: load a metadata object
    }

    status = loader->loadAsset(ctx, object);
    if (!(loadFlags & LOAD_FLAG_NO_CACHE)) {
        CachedAssetInfo &info = m_loadedObjects[filename];
        info.object           = object;
        info.status           = status;
    }
    return status;
}

gnaStatus nxfAssetManager::loadAssetAsCopy(gtl::PooledString filename, gnaPointer<gtlObject> &object, gtlCloneContext &cctx) {
    gnaPointer<gtlObject> templateObject;
    GNA_CHECK_STATUS(loadOrGetAsset(filename, templateObject));

    object = templateObject->clone(cctx).cast<gtlObject>();

    return GNA_E_OK;
}

gnaStatus nxfAssetManager::saveAsset(gtl::PooledString filename, gnaWeakPointer<gtlObject> object, uint32_t saveFlags) {
    auto *mutRM = gtlRttiCast<nxfMutableResourceManager *>(nxf_getRM());
    if (!mutRM) return { GNA_E_INVALID_STATE, GTXT("Resource manager is immutable") };

    gnaPointer<nxfOutputStream> stream;
    GNA_CHECK_STATUS(mutRM->get_resourceOutputStream(static_cast<gtl::String>(filename), stream));

    if (saveFlags & SAVE_FLAG_JSON) {
        nxfSerialization::NXJFileWriter writer(stream);
        GNA_CHECK_STATUS(writer.writeNXJFile(object));
    } else {
        nxfSerialization::NXFFileWriter writer(stream);
        GNA_CHECK_STATUS(writer.writeNXFFile(object));
    }

    CachedAssetInfo &info = m_loadedObjects[mutRM->normalizePath(static_cast<gtl::String>(filename))];
    info.status           = GNA_E_OK;
    info.object           = object;

    return GNA_E_OK;
}

void nxfAssetManager::dropCaches() {
    m_cachedAssetLinks.clear();
    m_loadedObjects.clear();
}

void nxfAssetManager::cacheFailure(gtl::PooledString filename, gnaStatus status) {
    CachedAssetInfo &info = m_loadedObjects[filename];
    info.object           = nullptr;
    info.status           = status;
}
