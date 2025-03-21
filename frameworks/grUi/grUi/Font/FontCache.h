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
#include <gtlUtil/Hash.h>
#include <grUi/Font/FontRenderer.h>
#include <gtlUtil/Singleton.h>
#include <grUi/UiDLL.h>
#include <grUi/Utils/UnitSize.h>

class nxfResourceManager;

struct grUiFontKey {
    gtl::String fontName;
    grUiUnitSizeF fontSize;

    bool operator==(const grUiFontKey &other) const {
        return other.fontName == fontName && other.fontSize == fontSize;
    }

    bool operator!=(const grUiFontKey &other) const {
        return !operator==(other);
    }
};

namespace std {
    template <>
    struct hash<grUiFontKey> {
        std::size_t operator()(grUiFontKey const &s) const noexcept {
            std::size_t seed = 0;
            gutlHashCombine(seed, s.fontName);
            gutlHashCombine(seed, s.fontSize);

            return seed;
        }
    };
}

class GR_UI_DLLIMPEXP grUiFontCache {
    std::unordered_map<gtl::String, gnaPointer<grUiFont>> m_fontRenderersCache;

public:
    gnaPointer<grUiFont> get_font(const grUiFontKey &fontKey);
};

GNA_SINGLETON_EXPORTED_DECLARE(GR_UI_DLLIMPEXP, grUiFontCache);
