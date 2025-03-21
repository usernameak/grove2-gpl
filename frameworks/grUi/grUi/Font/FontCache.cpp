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

#include "FontCache.h"

gnaPointer<grUiFont> grUiFontCache::get_font(const grUiFontKey &fontKey) {
    auto it = m_fontRenderersCache.find(fontKey.fontName);
    if (it == m_fontRenderersCache.end()) {
        auto fontRenderer = gnaNew<grUiFont>(fontKey.fontName);

        m_fontRenderersCache[fontKey.fontName] = fontRenderer;
        return fontRenderer;
    } else {
        return it->second;
    }
}

GNA_SINGLETON_IMPLEMENT(grUiFontCache);
