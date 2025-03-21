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

#include <grUi/UiDLL.h>
#include <nxfResource/RID.h>
#include "MultipatchImage.h"
#include <gtlUtil/Singleton.h>

class GR_UI_DLLIMPEXP grUiMultipatchImageCache {
    std::unordered_map<nxfRID, gnaPointer<grUiMultipatchImage>> m_cachedImages;

public:
    gnaPointer<grUiMultipatchImage> findOrLoadImage(const nxfRID &rid);
    void dropCaches();

private:
    gnaPointer<grUiMultipatchImage> loadImage(const nxfRID &rid);
};

GNA_SINGLETON_EXPORTED_DECLARE(GR_UI_DLLIMPEXP, grUiMultipatchImageCache);
