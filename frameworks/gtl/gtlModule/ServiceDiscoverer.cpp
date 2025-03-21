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

#include "ServiceDiscoverer.h"


#include "ModuleLoader.h"

#include <nxfIO/FileInputStream.h>
#include <nxfIO/FsPlatform.h>
#include <nxfUtil/EntryListReader.h>

GNA_SINGLETON_IMPLEMENT(gtlServiceDiscoverer);

gtlServiceDiscoverer::gtlServiceDiscoverer()
    : m_hasScannedServices(false) {}

void gtlServiceDiscoverer::scanServicesIfNecessary() {
    if (m_hasScannedServices) return;

    rescanServices();
}

void gtlServiceDiscoverer::rescanServices() {
    m_hasScannedServices = true;

    GR_INFO(GTXT("Scanning engine service DLLs"));

    m_availableServices.clear();

    gtl::String executablePath = nxfFsPlatform::getExecutablePath();
    gtl::String parentPath     = nxfFsPlatform::parentPath(executablePath);

    std::unordered_set<nxfFsPlatform::ListFilesEntry> entries;
    listFiles(parentPath, entries);
    for (auto &entry : entries) {
        static gtl::String ending(GTXT(".dll.svc"));
        if (!entry.filename.endsWith(ending)) continue;

        auto stream = gnaNew<nxfFileInputStream>();

        gtl::String filename    = nxfFsPlatform::combinePaths(parentPath, entry.filename);
        gtl::String dllFilename = filename.substr(0, filename.size() - 4); // strip 4 characters: .svc

        // if svc file has no corresponding dll, skip
        if (!nxfFsPlatform::isFile(dllFilename)) continue;

        gnaStatus status = stream->open(filename);
        if (!status) {
            GR_WARNING(GTXT("Could not open service manifest file `%ls`: %ls"),
                filename.toCString(),
                status.get_errorMessage().toCString());
        }

        nxfUtil::EntryListReader rd(stream);
        while (true) {
            gtl::AString entryName, entryValue;
            status = rd.readEntry2(entryName, entryValue);

            if (status.errorCode == GNA_E_END_OF_DATA) break;
            if (!status) {
                GR_WARNING(GTXT("Could not read entry from service manifest file `%ls`: %ls"),
                    filename.toCString(),
                    status.get_errorMessage().toCString());
                break;
            }

            if (entryName == "providesService") {
                if (m_availableServices.contains(entryValue)) {
                    GR_WARNING(GTXT("Duplicate service DLL with name `%hs`"), entryValue.toCString());
                } else {
                    m_availableServices[entryValue] = dllFilename;
                }
            }
        }
    }
}

void *gtlServiceDiscoverer::lookupService(gtl::AString name) {
    scanServicesIfNecessary();

    auto it = m_availableServices.find(name);
    if (it == m_availableServices.end()) return nullptr;

    const gtlModuleInfo *moduleInfo = gnaSingleton<gtlModuleLoader>()->loadModuleDLL(it->second);
    if (!moduleInfo) return nullptr;
    if (!moduleInfo->provideService) return nullptr;

    return moduleInfo->provideService(name.toCString());
}
