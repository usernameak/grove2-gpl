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

#include "ResourceConfig.h"

#include "FlatFileResourceManager.h"
#include "RMEx/ExtendedResourceManager.h"

#include <nxfIO/FileInputStream.h>
#include <nxfUtil/EntryListReader.h>

using namespace nxfResource;

ResourceConfig::ResourceConfig()
    : m_rmEx(gtlNew ExtendedResourceManager) {
}

ResourceConfig::~ResourceConfig() {
    gtlDelete m_rmEx;
}

gnaStatus ResourceConfig::loadConfig(const gtl::String &file) {
    auto stream = gnaNew<nxfFileInputStream>();
    GNA_CHECK_STATUS(stream->open(file));
    return loadConfig(stream);
}

gnaStatus ResourceConfig::loadConfig(gnaPointer<nxfInputStream> stream) {
    nxfUtil::EntryListReader rd(stream);

    ExtendedResourceManager::OrderNamespace orderNamespace =
        ExtendedResourceManager::OrderNamespace::NS_GAME;

    gtl::AString name, value;
    gnaStatus status;
    while ((status = rd.readEntry2(name, value)).errorCode == GNA_E_OK) {
        if (name == "namespace") {
            if (value == "game") {
                orderNamespace =
                    ExtendedResourceManager::OrderNamespace::NS_GAME;
            } else if (value == "engine") {
                orderNamespace =
                    ExtendedResourceManager::OrderNamespace::NS_ENGINE;
            } else if (value == "editor") {
                orderNamespace =
                    ExtendedResourceManager::OrderNamespace::NS_EDITOR;
            } else {
                return { GNA_E_INVALID_CONFIG, gtl::String::format(GTXT("Invalid namespace name %hs"), value.toCString()) };
            }
        } else if (name == "resman_flatfile") {
            nxfFlatFileResourceManager *resMan = gtlNew nxfFlatFileResourceManager(value);
            m_rmEx->addArchiveToNamespace(orderNamespace, resMan);
        } else {
            return { GNA_E_INVALID_CONFIG, gtl::String::format(GTXT("Invalid resource config property %hs"), name.toCString()) };
        }
    }
    GNA_CHECK_STATUS(status);

    return GNA_E_OK;
}

ExtendedResourceManager *ResourceConfig::buildResourceManager() {
    auto *manager = m_rmEx;
    m_rmEx        = nullptr;
    return manager;
}
