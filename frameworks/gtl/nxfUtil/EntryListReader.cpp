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

#include "EntryListReader.h"

#include <vector>
#include <cassert>

nxfUtil::EntryListReader::EntryListReader(gnaPointer<nxfInputStream> stream)
    : m_stream(std::move(stream)) {
}

gnaStatus nxfUtil::EntryListReader::readEntry2(gtl::AString &entryName, gtl::AString &entryValue) {
    std::vector<gtl::ASCIICHAR> entryname;
    std::vector<gtl::ASCIICHAR> entryvalue;
    entryname.reserve(16);
    entryvalue.reserve(32);

    bool readingName  = true;
    bool readingValue = false;

    while (true) {
        gtl::ASCIICHAR c;
        uint32_t nRead;
        GNA_CHECK_STATUS(m_stream->read(&c, sizeof(gtl::ASCIICHAR), &nRead));
        if (nRead == 0) {
            if (readingName && !entryname.empty()) {
                assert(false);
            }
            if (readingValue) break;

            return GNA_E_END_OF_DATA;
        }

        if (readingName) {
            if (c == ' ' || c == '\t') {
                continue;
            }
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
                entryname.push_back(c);
            } else if (c == ':') {
                readingName = false;
            } else if (c == '\n' || c == '\r') {
                if (!entryname.empty()) assert(false);
            } else {
                return { GNA_E_INVALID_CONFIG, GTXT("Invalid character encountered in entry list") };
            }
        } else {
            if ((c == ' ' || c == '\t') && !readingValue) {
                continue;
            }
            readingValue = true;
            if (c == '\\') {
                GNA_CHECK_STATUS(m_stream->read(&c, sizeof(gtl::ASCIICHAR), &nRead));
                assert(nRead != 0);
                if (c == 'n') {
                    entryvalue.push_back('\n');
                } else if (c == 't') {
                    entryvalue.push_back('\t');
                } else if (c == 'r') {
                    entryvalue.push_back('\r');
                } else {
                    entryvalue.push_back(c);
                }
            } else if (c == '\n') {
                break;
            } else if (c == '\r') {
                continue;
            } else {
                entryvalue.push_back(c);
            }
        }
    }

    entryName.assign(entryname.data(), entryname.size());
    entryValue.assign(entryvalue.data(), entryvalue.size());

    return GNA_E_OK;
}

nxfUtil::EntryListReader::~EntryListReader() = default;
