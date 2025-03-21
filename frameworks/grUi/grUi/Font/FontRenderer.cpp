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

#include "FontRenderer.h"

#include <nxfResource/ResourceManager.h>
#include <nlohmann/json.hpp>
#include <grUi/Utils/Sprite.h>
#include <nxfResource/Open.h>
#include <grUi/Render/UiRenderer.h>
#include <grUi/Text/TextRenderer.h>

using json = nlohmann::json;

static void parseBoundsFromJson(const json &boundsJson, grFontBoundsSpec &spec) {
    spec.left   = boundsJson["left"].get<float>();
    spec.top    = boundsJson["top"].get<float>();
    spec.right  = boundsJson["right"].get<float>();
    spec.bottom = boundsJson["bottom"].get<float>();
}

grUiFont::grUiFont(gtl::String name) {
    textureSRID         = { GTXT("/textures/fonts/") + name + GTXT(".nxf") };
    nxfRID fontFileSRID = { GTXT("/textures/fonts/") + name + GTXT(".json") };

    gnaPointer<nxfInputStream> is = nxfOpen(fontFileSRID);
    if (!is) {
        GR_FATAL(GTXT("font file not found"));
    }
    int64_t sizef = is->get_size();
    if (sizef < 0) {
        GR_FATAL(GTXT("cannot determine font file size"));
    }
    char *jsonText  = gtlNew char[sizef + 1];
    jsonText[sizef] = 0;
    is->read(jsonText, sizef);
    json fontSpecJson = json::parse(jsonText);
    gtlDeleteArray jsonText;

    fontSpec.lineHeight         = fontSpecJson["metrics"]["lineHeight"].get<float>();
    fontSpec.ascender           = fontSpecJson["metrics"]["ascender"].get<float>();
    fontSpec.descender          = fontSpecJson["metrics"]["descender"].get<float>();
    fontSpec.underlineY         = fontSpecJson["metrics"]["underlineY"].get<float>();
    fontSpec.underlineThickness = fontSpecJson["metrics"]["underlineThickness"].get<float>();

    fontSpec.atlasWidth    = fontSpecJson["atlas"]["width"].get<int>();
    fontSpec.atlasHeight   = fontSpecJson["atlas"]["height"].get<int>();
    fontSpec.atlasSize     = fontSpecJson["atlas"]["size"].get<float>();
    fontSpec.distanceRange = fontSpecJson["atlas"]["distanceRange"].get<float>();
    fontSpec.useMSDF       = fontSpecJson["atlas"]["type"].get<std::string>() == "msdf";

    for (auto &glyphJson : fontSpecJson["glyphs"]) {
        auto &glyph           = charToGlyph[glyphJson["unicode"].get<char32_t>()];
        glyph.advance         = glyphJson["advance"].get<float>();
        auto &planeBoundsJson = glyphJson["planeBounds"];
        if (planeBoundsJson.is_null()) {
            glyph.hasBounds = false;
        } else {
            glyph.hasBounds = true;
            parseBoundsFromJson(glyphJson["planeBounds"], glyph.planeBounds);
            parseBoundsFromJson(glyphJson["atlasBounds"], glyph.atlasBounds);
        }
    }

    for (auto &kerningJson : fontSpecJson["kerning"]) {
        char32_t c1   = kerningJson["unicode1"].get<char32_t>();
        char32_t c2   = kerningJson["unicode2"].get<char32_t>();
        float advance = kerningJson["advance"].get<float>();

        fontSpec.kerningPairs[grFontKerningPairKey{ c1, c2 }] = advance;
    }
}

float grUiFont::get_width(float size, gtl::String str, int untilChar) const {
    auto measurer = createMeasurer(size);
    return measurer->append(str, 0, untilChar);
}

int grUiFont::get_charPositionFromX(float size, gtl::String str, float x) const {
    float width         = 0.0f;
    gtl::WIDECHAR prevC = 0;
    for (int i = 0; i < str.size(); i++) {
        gtl::WIDECHAR c = str[i];

        const grFontGlyphSpec &glyph = get_glyphFromChar(c);

        if (width >= x) {
            return i;
        }

        grFontKerningPairKey kpk{ prevC, c };
        float advance = glyph.advance;
        auto it       = fontSpec.kerningPairs.find(kpk);
        if (it != fontSpec.kerningPairs.end()) {
            advance += it->second;
        }
        width += advance * size;

        prevC = c;
    }
    return str.size();
}

const grFontGlyphSpec &grUiFont::get_glyphFromChar(gtl::WIDECHAR c) const {
    auto it = charToGlyph.find((char32_t)c);
    if (it == charToGlyph.end()) {
        it = charToGlyph.find(U'?');
    }
    return it->second;
}

float grUiFontMeasurer::append(const gtl::String &str, int32_t fromChar, int32_t untilChar) {
    if (untilChar == -1) {
        untilChar = (int32_t)str.size();
    }
    for (int i = fromChar; i < untilChar; i++) {
        gtl::WIDECHAR c              = str[i];
        const grFontGlyphSpec &glyph = m_fontRenderer->get_glyphFromChar(c);

        grFontKerningPairKey kpk{ m_lastCharacter, c };
        float advance = glyph.advance;
        auto it       = m_fontRenderer->fontSpec.kerningPairs.find(kpk);
        if (it != m_fontRenderer->fontSpec.kerningPairs.end()) {
            advance += it->second;
        }
        m_currentX += advance * m_size;

        m_lastCharacter = c;
    }

    return m_currentX;
}
