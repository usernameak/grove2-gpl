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

#include <unordered_map>

#include <gtlObject/Object.h>
#include <gtlString/PooledString.h>
#include <gtlUtil/Singleton.h>
#include <gtlUtil/Misc.h>
#include <nxfResource/ResourceManager.h>

struct nxfAssetLoadContext {
    nxfResourceManager *resourceManager;

    gtl::PooledString filename;

    /**
     * The file stream for the asset being loaded
     */
    gnaPointer<nxfInputStream> primaryStream;

    /**
     * A metadata object. Non-null only if nxfAssetLoader::requiresMetadataObject()
     * is non-null and the metadata object exists.
     */
    gnaPointer<gtlObject> metadataObject;
};

class GTL_DLLIMPEXP nxfAssetLoader : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    /**
     * @return if a metadata object is required by this asset loader, true;
     * otherwise it won't be loaded by asset manager
     */
    virtual bool requiresMetadataObject() const {
        return true;
    }

    /**
     * @return file extension list for this asset type, null-terminated
     */
    virtual const gtl::WIDECHAR *const *getFileExtensions() const = 0;

    /**
     * Tries to load an asset using this asset manager.
     *
     * @param loadContext contains information about the asset
     *
     * @return status of the operation
     */
    virtual gnaStatus loadAsset(const nxfAssetLoadContext &loadContext, gnaPointer<gtlObject> &resultObject) = 0;
};

class GTL_DLLIMPEXP nxfAssetLoaderNXF final : public nxfAssetLoader {
public:
    GTL_RTTI_DECLARE();

    bool requiresMetadataObject() const override;
    const gtl::WIDECHAR *const *getFileExtensions() const override;

    gnaStatus loadAsset(const nxfAssetLoadContext &loadContext, gnaPointer<gtlObject> &resultObject) override;
};

class GTL_DLLIMPEXP nxfAssetManager {
    struct CachedAssetInfo {
        gnaPointer<gtlObject> object;
        gnaStatus status;
    };

    struct CachedAssetLinkInfo {
        gtl::PooledString targetFilename;
        gnaStatus status;
    };

    std::unordered_map<gtl::PooledString, CachedAssetLinkInfo> m_cachedAssetLinks;
    std::unordered_map<gtl::PooledString, CachedAssetInfo> m_loadedObjects;
    std::unordered_map<gtl::String, gnaPointer<nxfAssetLoader>> m_registeredFileExtensions;
    std::unordered_map<const gtlRTTI *, gnaPointer<gtlObject>> m_fallbackObjects;

public:
    enum LoadFlags : uint32_t {
        /**
         * Always load the resource again, bypassing cache
         */
        LOAD_FLAG_NO_CACHE = GTL_BIT(0),

        /**
         * Skip file extension detection
         */
        LOAD_FLAG_NO_DETECT_EXT = GTL_BIT(1),

        /**
         * Return nullptr instead of a fallback resource on failure
         */
        LOAD_FLAG_NO_FALLBACK = GTL_BIT(2),
    };

    enum SaveFlags : uint32_t {
        /**
         * Save to JSON instead of a binary format
         */
        SAVE_FLAG_JSON = GTL_BIT(0)
    };

    nxfAssetManager();

    /**
     * Registers an asset loader in asset manager
     *
     * @param assetLoader the asset loader to register
     */
    void registerAssetLoader(gnaPointer<nxfAssetLoader> assetLoader);

    /**
     * Registers a fallback object for a given object type
     *
     * @param objectType the RTTI type of the object
     * @param object the object to register as the default for the given type
     */
    void registerFallbackObject(const gtlRTTI *objectType, gnaPointer<gtlObject> object);

    template <typename T>
    void registerFallbackObject(gnaPointer<gtlObject> object) {
        registerFallbackObject(&T::st_rtti, std::move(object));
    }

    /**
     * Loads an asset or retrieves an already-loaded one.
     * @param filename the filename to load
     * @param objectType the RTTI type of the object
     * @param object output parameter; the object that has been loaded
     * @param loadFlags load flags from LoadFlags enum
     * @return status of the operation
     */
    gnaStatus loadOrGetAsset(
        gtl::PooledString filename,
        const gtlRTTI *objectType,
        gnaPointer<gtlObject> &object,
        uint32_t loadFlags = 0);

    /**
     * Loads a new copy of an asset (possibly cloning using an already-loaded one as a template).
     * @param filename the filename to load
     * @param objectType the RTTI type of the object
     * @param object output parameter; the object that has been loaded
     * @return status of the operation
     */
    gnaStatus loadAssetAsCopy(
        gtl::PooledString filename,
        const gtlRTTI *objectType,
        gnaPointer<gtlObject> &object) {

        gtlCloneContext cctx{};
        return loadAssetAsCopy(std::move(filename), object, cctx);
    }

    template <typename T>
    gnaStatus loadOrGetAsset(gtl::PooledString filename, gnaPointer<T> &object, uint32_t loadFlags = 0) {
        gnaPointer<gtlObject> rawObject;

        gnaStatus status = loadOrGetAsset(filename, &T::st_rtti, rawObject, loadFlags);
        object           = rawObject.rttiCast2<T>();
        if (rawObject && !object) {
            return {
                GNA_E_INCOMPATIBLE_CLS,
                gtl::String::format(
                    GTXT("Failed to load object (file `%ls`) as %hs: incompatible class"),
                    filename.toCString(),
                    T::st_rtti.get_className())
            };
        }

        return status;
    }

    template <typename T>
    gnaStatus loadAssetAsCopy(gtl::PooledString filename, gnaPointer<T> &object) {
        gnaPointer<gtlObject> rawObject;

        gnaStatus status = loadAssetAsCopy(filename, &T::st_rtti, rawObject);
        GNA_CHECK_STATUS(status);

        object = rawObject.rttiCast2<T>();
        if (rawObject && !object) {
            return {
                GNA_E_INCOMPATIBLE_CLS,
                gtl::String::format(
                    GTXT("Failed to load object (file `%ls`) as %hs: incompatible class"),
                    filename.toCString(),
                    T::st_rtti.get_className())
            };
        }

        return status;
    }

    /**
     * Loads a new copy of an asset (possibly cloning using an already-loaded one as a template),
     * using a user-provided clone context.
     * @param filename the filename to load
     * @param object output parameter; the object that has been loaded
     * @param cctx optional; clone content
     * @return status of the operation
     */
    gnaStatus loadAssetAsCopy(gtl::PooledString filename, gnaPointer<gtlObject> &object, gtlCloneContext &cctx);

    gnaStatus saveAsset(gtl::PooledString filename, gnaWeakPointer<gtlObject> object, uint32_t saveFlags = 0);

    void dropCaches();

private:
    void cacheFailure(gtl::PooledString filename, gnaStatus status);
};

GNA_SINGLETON_EXPORTED_DECLARE(GTL_DLLIMPEXP, nxfAssetManager);
