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

#include <gtlMemory/RcObject.h>
#include <nxfResource/RID.h>
#include <unordered_map>
#include <grUi/Render/UiRenderer.h>
#include <grUi/UiDLL.h>

constexpr float GR_UI_DEFAULT_FONT_SIZE = 12.0f;

class nxfResourceManager;

struct grFontKerningPairKey {
    char32_t a, b;

    bool operator==(const grFontKerningPairKey &other) const {
        return other.a == a && other.b == b;
    }
};

namespace std {
    template <>
    struct hash<grFontKerningPairKey> {
        std::uint64_t operator()(grFontKerningPairKey const &s) const noexcept {
            return static_cast<uint64_t>(s.a) ^ (static_cast<uint64_t>(s.b) << 32);
        }
    };
}

struct grFontSpec {
    float lineHeight;
    float ascender;
    float descender;
    float underlineY;
    float underlineThickness;

    int atlasWidth, atlasHeight;
    float atlasSize;
    float distanceRange;

    bool useMSDF;

    std::unordered_map<grFontKerningPairKey, float> kerningPairs;
};

struct grFontBoundsSpec {
    float left, bottom, right, top;
};

struct grFontGlyphSpec {
    float advance;
    bool hasBounds;
    grFontBoundsSpec planeBounds;
    grFontBoundsSpec atlasBounds;
};

class GR_UI_DLLIMPEXP grUiFont;

class GR_UI_DLLIMPEXP grUiFontMeasurer : public gtlRcObject {
    gnaWeakPointer<const grUiFont> m_fontRenderer;
    float m_currentX;
    gtl::WIDECHAR m_lastCharacter;
    float m_size;

public:
    grUiFontMeasurer(gnaWeakPointer<const grUiFont> fontRenderer, float size)
        : m_fontRenderer(std::move(fontRenderer)),
          m_currentX(0.0f),
          m_lastCharacter(0),
          m_size(size) {}

    float get_currentX() const { return m_currentX; }

    void reset() {
        m_currentX      = 0.0f;
        m_lastCharacter = 0;
    }

    float append(const gtl::String &str, int32_t fromChar = 0, int32_t untilChar = -1);
};

class GR_UI_DLLIMPEXP grUiFont : public gtlRcObject {
public:
    nxfRID textureSRID;

    grFontSpec fontSpec;

    std::unordered_map<char32_t, grFontGlyphSpec> charToGlyph;

    explicit grUiFont(gtl::String name);

    float get_ascender(float size) const { return size * fontSpec.ascender; }
    float get_lineHeight(float size) const { return size * fontSpec.lineHeight; }
    float get_descender(float size) const { return size * fontSpec.descender; }

    float get_width(float size, gtl::String str, int untilChar = -1) const;
    int get_charPositionFromX(float size, gtl::String str, float x) const;

    gnaPointer<grUiFontMeasurer> createMeasurer(float size) const {
        return gnaNew<grUiFontMeasurer>(gnaWeakPointer(this), size);
    }

    const grFontGlyphSpec &get_glyphFromChar(gtl::WIDECHAR c) const;
};
