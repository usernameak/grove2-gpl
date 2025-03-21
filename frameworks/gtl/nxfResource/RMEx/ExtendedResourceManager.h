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

#include <nxfResource/MutableResourceManager.h>

namespace nxfResource {
    class GTL_DLLIMPEXP ExtendedResourceManager : public nxfMutableResourceManager {
    public:
        enum OrderNamespace : uint8_t {
            NS_ENGINE = 0,
            NS_EDITOR = 1,
            NS_GAME = 2,
            NS_MAX = 3
        };

        nxfMutableResourceManager *m_editResourceManager = nullptr;

    private:
        std::vector<nxfResourceManager *> m_archives[NS_MAX];

    public:
        GTL_RTTI_DECLARE();

        ExtendedResourceManager()                                = default;
        ExtendedResourceManager(const ExtendedResourceManager &) = delete;
        ExtendedResourceManager(ExtendedResourceManager &&)      = delete;

        virtual ~ExtendedResourceManager() override {
            for (auto &nsArchives : m_archives) {
                for (auto *arch : nsArchives) {
                    gtlDelete arch;
                }
            }
        }

        void initializeIndex(bool reinitialize) override;

        gnaPointer<GridResourceIndex> getGridIndex(
            const gtl::String &root,
            const gtl::String &extension,
            bool allowDirect = true) override;

        void addArchiveToNamespace(OrderNamespace ns, nxfResourceManager *arch);
        void clearNamespace(OrderNamespace ns);

        bool isFile(gtl::String name) override;

        bool listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) override;

        bool createDirectory(gtl::String name) override;

        gnaStatus get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) override;

        gnaStatus get_resourceOutputStream(gtl::String name, gnaPointer<nxfOutputStream> &outStream) override;
        bool findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) override;
    };
}
