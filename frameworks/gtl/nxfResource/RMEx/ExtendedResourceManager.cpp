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

#include "ExtendedResourceManager.h"

#include <nxfResource/Index/GridResourceIndex.h>

using namespace nxfResource;

GTL_RTTI_DEFINE(nxfResource::ExtendedResourceManager, GTL_RTTI_INHERITS(nxfMutableResourceManager));

void ExtendedResourceManager::initializeIndex(bool reinitialize) {
    for (auto &nsArchives : m_archives) {
        for (auto *arch : nsArchives) {
            arch->initializeIndex(reinitialize);
        }
    }
}

gnaPointer<GridResourceIndex> ExtendedResourceManager::getGridIndex(const gtl::String &root, const gtl::String &extension, bool allowDirect) {
    for (int ns = NS_MAX - 1; ns >= 0; ns--) {
        auto &nsArchives = m_archives[ns];
        for (auto *arch : nsArchives) {
            gnaPointer<GridResourceIndex> index = arch->getGridIndex(root, extension, false);
            if (index) {
                return index;
            }
        }
    }
    return nxfResourceManager::getGridIndex(root, extension, allowDirect);
}

void ExtendedResourceManager::addArchiveToNamespace(OrderNamespace ns, nxfResourceManager *arch) {
    arch->initializeIndex();
    m_archives[ns].push_back(arch);
}

void ExtendedResourceManager::clearNamespace(OrderNamespace ns) {
    for (auto *arch : m_archives[ns]) {
        gtlDelete arch;
    }
    m_archives[ns].clear();
}

bool ExtendedResourceManager::isFile(gtl::String name) {
    for (auto &nsArchives : m_archives) {
        for (auto *arch : nsArchives) {
            if (arch->isFile(name)) {
                return true;
            }
        }
    }
    return false;
}

bool ExtendedResourceManager::listFiles(gtl::String directory, std::unordered_set<grFsPlatform::ListFilesEntry> &filenames) {
    bool success = false;
    for (int ns = NS_MAX - 1; ns >= 0; ns--) {
        auto &nsArchives = m_archives[ns];
        for (auto *arch : nsArchives) {
            success |= arch->listFiles(directory, filenames);
        }
    }
    return success;
}

bool ExtendedResourceManager::createDirectory(gtl::String name) {
    if (!m_editResourceManager) {
        GR_FATAL(GTXT("Cannot edit files when there's no edit resource manager"));
    }
    return m_editResourceManager->createDirectory(name);
}

gnaStatus ExtendedResourceManager::get_resourceStream(gtl::String name, gnaPointer<nxfInputStream> &outStream, uint32_t flags) {
    gnaPointer<nxfInputStream> stream(nullptr);
    for (int ns = NS_MAX - 1; ns >= 0; ns--) {
        auto &nsArchives = m_archives[ns];
        for (auto it = nsArchives.rbegin(); it != nsArchives.rend(); ++it) {
            nxfResourceManager *arch = *it;
            gnaStatus status         = arch->get_resourceStream(name, outStream, flags);
            if (status && outStream) {
                return status;
            }
        }
    }
    return GNA_E_FILE_NOT_FOUND;
}

#define NEW_RESOURCE_OUTPUT_STREAM_BEHAVIOR

gnaStatus ExtendedResourceManager::get_resourceOutputStream(gtl::String name, gnaPointer<nxfOutputStream> &outStream) {
#ifdef NEW_RESOURCE_OUTPUT_STREAM_BEHAVIOR
    gnaStatus status = GNA_E_FILE_NOT_FOUND;
    gnaPointer<nxfOutputStream> stream(nullptr);
    for (int ns = NS_MAX - 1; ns >= 0; ns--) {
        auto &nsArchives = m_archives[ns];
        for (auto it = nsArchives.rbegin(); it != nsArchives.rend(); ++it) {
            auto *arch = dynamic_cast<nxfMutableResourceManager *>(*it);
            if (!arch) continue;

            status = arch->get_resourceOutputStream(name, stream);
            if (status) {
                outStream = stream;
                return status;
            }
        }
    }
    return status;
#else
    if (!m_editResourceManager) {
        GR_FATAL(GTXT("Cannot edit files when there's no edit resource manager"));
    }
    return m_editResourceManager->get_resourceOutputStream(name);
#endif
}

bool ExtendedResourceManager::findResourcePathFromNativePath(const gtl::String &nativePath, gtl::String &outResourcePath) {
    for (int ns = NS_MAX - 1; ns >= 0; ns--) {
        auto &nsArchives = m_archives[ns];
        for (auto it = nsArchives.rbegin(); it != nsArchives.rend(); ++it) {
            nxfResourceManager *arch = *it;
            if (arch->findResourcePathFromNativePath(nativePath, outResourcePath)) {
                return true;
            }
        }
    }
    return nxfResourceManager::findResourcePathFromNativePath(nativePath, outResourcePath);
}
