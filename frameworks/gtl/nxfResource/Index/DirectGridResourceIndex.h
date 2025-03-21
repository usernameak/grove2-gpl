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

#include "GridResourceIndex.h"
#include <nxfResource/ResourceManager.h>

namespace nxfResource {
    class GTL_DLLIMPEXP DirectGridResourceIndex : public GridResourceIndex {
        nxfResourceManager *m_resMan;
        gtl::String m_root;
        gtl::String m_fileExtension;

    public:
        DirectGridResourceIndex(nxfResourceManager *resMan, const gtl::String &root, const gtl::String &fileExtension);

        virtual ~DirectGridResourceIndex() override;

        gnaStatus get_nodeByIndex(int64_t x, int64_t y, gnaPointer<nxfInputStream> &stream, uint32_t flags = 0) override;
    };
}
