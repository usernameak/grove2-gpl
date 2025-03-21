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

#include "Color.h"

#include <grUi/Style/GSS/Utils.h>

GTL_RTTI_DEFINE(grUiGSSColorPropVal, GTL_RTTI_INHERITS(grUiGSSPropVal));

static std::unordered_map<gtl::AString, uint32_t> colorConstants{
    { "transparent", 0 },
    { "aliceblue", 0xfff0f8ff },
    { "antiquewhite", 0xfffaebd7 },
    { "aqua", 0xff00ffff },
    { "aquamarine", 0xff7fffd4 },
    { "azure", 0xfff0ffff },
    { "beige", 0xfff5f5dc },
    { "bisque", 0xffffe4c4 },
    { "black", 0xff000000 },
    { "blanchedalmond", 0xffffebcd },
    { "blue", 0xff0000ff },
    { "blueviolet", 0xff8a2be2 },
    { "brown", 0xffa52a2a },
    { "burlywood", 0xffdeb887 },
    { "cadetblue", 0xff5f9ea0 },
    { "chartreuse", 0xff7fff00 },
    { "chocolate", 0xffd2691e },
    { "coral", 0xffff7f50 },
    { "cornflowerblue", 0xff6495ed },
    { "cornsilk", 0xfffff8dc },
    { "crimson", 0xffdc143c },
    { "cyan", 0xff00ffff },
    { "darkblue", 0xff00008b },
    { "darkcyan", 0xff008b8b },
    { "darkgoldenrod", 0xffb8860b },
    { "darkgray", 0xffa9a9a9 },
    { "darkgreen", 0xff006400 },
    { "darkkhaki", 0xffbdb76b },
    { "darkmagenta", 0xff8b008b },
    { "darkolivegreen", 0xff556b2f },
    { "darkorange", 0xffff8c00 },
    { "darkorchid", 0xff9932cc },
    { "darkred", 0xff8b0000 },
    { "darksalmon", 0xffe9967a },
    { "darkseagreen", 0xff8fbc8f },
    { "darkslateblue", 0xff483d8b },
    { "darkslategray", 0xff2f4f4f },
    { "darkturquoise", 0xff00ced1 },
    { "darkviolet", 0xff9400d3 },
    { "deeppink", 0xffff1493 },
    { "deepskyblue", 0xff00bfff },
    { "dimgray", 0xff696969 },
    { "dodgerblue", 0xff1e90ff },
    { "firebrick", 0xffb22222 },
    { "floralwhite", 0xfffffaf0 },
    { "forestgreen", 0xff228b22 },
    { "fuchsia", 0xffff00ff },
    { "gainsboro", 0xffdcdcdc },
    { "ghostwhite", 0xfff8f8ff },
    { "gold", 0xffffd700 },
    { "goldenrod", 0xffdaa520 },
    { "gray", 0xff808080 },
    { "green", 0xff008000 },
    { "greenyellow", 0xffadff2f },
    { "honeydew", 0xfff0fff0 },
    { "hotpink", 0xffff69b4 },
    { "indianred", 0xffcd5c5c },
    { "indigo", 0xff4b0082 },
    { "ivory", 0xfffffff0 },
    { "khaki", 0xfff0e68c },
    { "lavender", 0xffe6e6fa },
    { "lavenderblush", 0xfffff0f5 },
    { "lawngreen", 0xff7cfc00 },
    { "lemonchiffon", 0xfffffacd },
    { "lightblue", 0xffadd8e6 },
    { "lightcoral", 0xfff08080 },
    { "lightcyan", 0xffe0ffff },
    { "lightgoldenrodyellow", 0xfffafad2 },
    { "lightgreen", 0xff90ee90 },
    { "lightgrey", 0xffd3d3d3 },
    { "lightpink", 0xffffb6c1 },
    { "lightsalmon", 0xffffa07a },
    { "lightseagreen", 0xff20b2aa },
    { "lightskyblue", 0xff87cefa },
    { "lightslategray", 0xff778899 },
    { "lightsteelblue", 0xffb0c4de },
    { "lightyellow", 0xffffffe0 },
    { "lime", 0xff00ff00 },
    { "limegreen", 0xff32cd32 },
    { "linen", 0xfffaf0e6 },
    { "magenta", 0xffff00ff },
    { "maroon", 0xff800000 },
    { "mediumaquamarine", 0xff66cdaa },
    { "mediumblue", 0xff0000cd },
    { "mediumorchid", 0xffba55d3 },
    { "mediumpurple", 0xff9370db },
    { "mediumseagreen", 0xff3cb371 },
    { "mediumslateblue", 0xff7b68ee },
    { "mediumspringgreen", 0xff00fa9a },
    { "mediumturquoise", 0xff48d1cc },
    { "mediumvioletred", 0xffc71585 },
    { "midnightblue", 0xff191970 },
    { "mintcream", 0xfff5fffa },
    { "mistyrose", 0xffffe4e1 },
    { "moccasin", 0xffffe4b5 },
    { "navajowhite", 0xffffdead },
    { "navy", 0xff000080 },
    { "oldlace", 0xfffdf5e6 },
    { "olive", 0xff808000 },
    { "olivedrab", 0xff6b8e23 },
    { "orange", 0xffffa500 },
    { "orangered", 0xffff4500 },
    { "orchid", 0xffda70d6 },
    { "palegoldenrod", 0xffeee8aa },
    { "palegreen", 0xff98fb98 },
    { "paleturquoise", 0xffafeeee },
    { "palevioletred", 0xffdb7093 },
    { "papayawhip", 0xffffefd5 },
    { "peachpuff", 0xffffdab9 },
    { "peru", 0xffcd853f },
    { "pink", 0xffffc0cb },
    { "plum", 0xffdda0dd },
    { "powderblue", 0xffb0e0e6 },
    { "purple", 0xff800080 },
    { "red", 0xffff0000 },
    { "rosybrown", 0xffbc8f8f },
    { "royalblue", 0xff4169e1 },
    { "saddlebrown", 0xff8b4513 },
    { "salmon", 0xfffa8072 },
    { "sandybrown", 0xfff4a460 },
    { "seagreen", 0xff2e8b57 },
    { "seashell", 0xfffff5ee },
    { "sienna", 0xffa0522d },
    { "silver", 0xffc0c0c0 },
    { "skyblue", 0xff87ceeb },
    { "slateblue", 0xff6a5acd },
    { "slategray", 0xff708090 },
    { "snow", 0xfffffafa },
    { "springgreen", 0xff00ff7f },
    { "steelblue", 0xff4682b4 },
    { "tan", 0xffd2b48c },
    { "teal", 0xff008080 },
    { "thistle", 0xffd8bfd8 },
    { "tomato", 0xffff6347 },
    { "turquoise", 0xff40e0d0 },
    { "violet", 0xffee82ee },
    { "wheat", 0xfff5deb3 },
    { "white", 0xffffffff },
    { "whitesmoke", 0xfff5f5f5 },
    { "yellow", 0xffffff00 },
    { "yellowgreen", 0xff9acd32 },
};

gnaStatus grUiGSSColorPropVal::Parser::parseRGBSingleNumber(uint8_t &value, grUiGSSParser &parser, bool forceFloat) {
    using enum grUiGSSTokenizer::CSSTokenType;

    auto &token = parser.consumeNextToken();

    if (token.get_tokenType() == TT_NUMBER) {
        if (forceFloat || (token.get_tokenFlags() & TT_FLAG_FLOAT)) {
            double dValue;
            bool result = token.tokenValue.toDouble(dValue);
            if (!result) {
                return { GNA_E_INVALID_CONFIG, GTXT("Color specification: cannot decode float value") };
            }

            if (isnan(dValue)) {
                return { GNA_E_INVALID_CONFIG, GTXT("Color specification: NaN value") };
            } else if (dValue >= 1.0) {
                value = 0xFF;
            } else if (dValue <= 0.0) {
                value = 0;
            } else {
                value = (uint8_t)(dValue * 255.0);
            }
        } else {
            long long iValue;
            bool result = token.tokenValue.toLongLong(iValue);
            if (!result) {
                return { GNA_E_INVALID_CONFIG, GTXT("Color specification: cannot decode int value") };
            }

            if (iValue <= 0) {
                value = 0;
            } else if (iValue >= 0xFF) {
                value = 0xFF;
            } else {
                value = (uint8_t)iValue;
            }
        }
    } else if (token.get_tokenType() == TT_PERCENTAGE) {
        double dValue;
        bool result = token.tokenValue.toDouble(dValue);
        if (!result) {
            return { GNA_E_INVALID_CONFIG, GTXT("Color specification: cannot decode float value") };
        }

        if (isnan(dValue)) {
            return { GNA_E_INVALID_CONFIG, GTXT("Color specification: NaN value") };
        } else if (dValue >= 100.0) {
            value = 0xFF;
        } else if (dValue <= 0.0) {
            value = 0;
        } else {
            value = (uint8_t)(dValue / 100.0 * 255.0);
        }
    } else {
        return { GNA_E_INVALID_CONFIG, GTXT("Color specification: unexpected token") };
    }

    return GNA_E_OK;
}

gnaStatus grUiGSSColorPropVal::Parser::parseValue(grUiGSSRuleProperty &property, grUiGSSParser &parser) {
    using enum grUiGSSTokenizer::CSSTokenType;

    auto &colorToken = parser.consumeNextToken();
    if (colorToken.get_tokenType() == TT_HASH) {
        // hex encoded color
        uint32_t len       = colorToken.tokenValue.size();
        uint32_t colorRGBA = 0;
        if (len != 3 && len != 4 && len != 6 && len != 8) {
            return { GNA_E_INVALID_CONFIG, GTXT("Color specification: invalid hex value length") };
        }
        for (uint32_t i = 0; i < len; i++) {
            gtl::ASCIICHAR c = colorToken.tokenValue[i];

            if (!grUiGSSUtils::isHexDigit(c))
                return { GNA_E_INVALID_CONFIG, GTXT("Color specification: invalid hex digit") };

            uint32_t digit = grUiGSSUtils::decodeHexDigit(c);
            colorRGBA <<= 4;
            colorRGBA |= digit;
            if (len == 3 || len == 4) {
                colorRGBA <<= 4;
                colorRGBA |= digit;
            }
        }
        if (len == 3 || len == 6) {
            colorRGBA <<= 8;
            colorRGBA |= 0xFFu;
        }
        uint32_t colorARGB = ((colorRGBA & 0xFFFFFF00u) >> 8u) | ((colorRGBA & 0x000000FFu) << 24u);
        property.value     = gnaNew<grUiGSSColorPropVal>(grColor{ colorARGB });
    } else if (colorToken.get_tokenType() == TT_IDENT) {
        // color name
        auto it = colorConstants.find(colorToken.tokenValue);
        if (it == colorConstants.end()) {
            return { GNA_E_INVALID_CONFIG, GTXT("Color specification: unknown CSS color constant") };
        }
        property.value = gnaNew<grUiGSSColorPropVal>(grColor{ it->second });
    } else if (colorToken.get_tokenType() == TT_FUNCTION) {
        // rgb(), rgba() etc.
        if (colorToken.tokenValue == "rgb") {
            parser.swallowWhitespaceTokens();
            uint8_t r, g, b;
            GNA_CHECK_STATUS(parseRGBSingleNumber(r, parser));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parseRGBSingleNumber(g, parser));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parseRGBSingleNumber(b, parser));
            uint32_t argb  = 0xFF000000u | ((uint32_t)r << 16u) | ((uint32_t)g << 8u) | ((uint32_t)b);
            property.value = gnaNew<grUiGSSColorPropVal>(grColor{ argb });
        } else if (colorToken.tokenValue == "rgba") {
            parser.swallowWhitespaceTokens();
            uint8_t r, g, b, a;
            GNA_CHECK_STATUS(parseRGBSingleNumber(r, parser));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parseRGBSingleNumber(g, parser));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parseRGBSingleNumber(b, parser));
            GNA_CHECK_STATUS(parser.parseComma());
            GNA_CHECK_STATUS(parseRGBSingleNumber(a, parser, true));
            uint32_t argb  = ((uint32_t)a << 24u) | ((uint32_t)r << 16u) | ((uint32_t)g << 8u) | ((uint32_t)b);
            property.value = gnaNew<grUiGSSColorPropVal>(grColor{ argb });
        } else {
            return { GNA_E_FAILED, GTXT("Unsupported color function") };
        }
        parser.swallowWhitespaceTokens();
        if (parser.consumeNextToken().get_tokenType() != grUiGSSTokenizer::TT_RPAREN) {
            return { GNA_E_FAILED, GTXT("Expected ) after rgb") };
        }
    }
    return GNA_E_OK;
}
