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

#include "LCStringTable.h"

#include <nxfUtil/EntryListReader.h>
#include <nxfResource/ResourceManager.h>

gnaStatus gtlLocale::LCStringTable::loadLocale(const nxfRID &rid) {
    m_stringMap.clear();

    auto stream = nxf_getRM()->get_resourceStream(rid.name);
    if (!stream)
        return GNA_E_FAILED;

    nxfUtil::EntryListReader rd(stream);

    gtl::AString entryName;
    gtl::AString entryValue;
    while (rd.readEntry(entryName, entryValue)) {
        m_stringMap[entryName] = gtl::String(entryValue, gtl::String::S_CHARSET_UTF8);
    }

    return GNA_E_OK;
}

gtl::String gtlLocale::LCStringTable::lookupString(const gtl::AString &name) {
    auto it = m_stringMap.find(name);
    if (it == m_stringMap.end()) return gtl::String(name, gtl::String::S_CHARSET_ASCII);
    return it->second;
}

bool gtlLocale::LCStringTable::lookupString(const gtl::AString &name, gtl::String &result) {
    auto it = m_stringMap.find(name);
    if (it == m_stringMap.end()) return false;
    result = it->second;
    return true;
}
