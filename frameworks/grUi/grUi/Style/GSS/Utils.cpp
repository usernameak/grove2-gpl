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

#include "Utils.h"

gnaStatus grUiGSSUtils::convertUrlToRID(const gtl::AString &url, nxfRID &rid) {
    static gtl::AString URL_PREFIX = "resource://root/";
    if (!url.startsWith(URL_PREFIX)) {
        return { GNA_E_FAILED, gtl::String::format(GTXT("Unsupported URL: `%hs`"), url.toCString()) };
    }
    rid = { url.substr(URL_PREFIX.size() - 1) };
    return GNA_E_OK;
}
