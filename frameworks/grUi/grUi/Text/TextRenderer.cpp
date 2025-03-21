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

#include "TextRenderer.h"

#include <grUi/Font/FontCache.h>
#include <unicode/utext.h>
#include <unicode/brkiter.h>
#include <deque>

grUiTextRenderer::grUiTextRenderer(const grUiMetricContext &metricContext)
    : grUiTextRenderer(metricContext, grUiFontKey{ GTXT("Default"), GR_UI_DEFAULT_FONT_SIZE }) {
}

grUiTextRenderer::grUiTextRenderer(const grUiMetricContext &metricContext, const grUiFontKey &fontKey)
    : m_metricContext(metricContext),
      m_font(gnaSingleton<grUiFontCache>()->get_font(fontKey)),
      m_fontSize(fontKey.fontSize.toPixels(metricContext)),
      m_ellipsizeMaxX(std::numeric_limits<float>::quiet_NaN()) {
    setOrigin(0, 0);
}

void grUiTextRenderer::reset() {
    m_currentX     = m_originX;
    m_currentY     = m_originY;
    m_previousChar = 0;
}

static bool g_enableTextRendererDebugDraw = false;

void grUiTextRenderer::set_enableDebugDraw(bool debugDraw) {
    g_enableTextRendererDebugDraw = debugDraw;
}

void grUiTextRenderer::render(grUiRenderer *render, const grUiSpannedText &str, uint32_t color) {
    float startX = m_currentX;
    renderBegin(render);

    doRender(render, str, color);

    renderEnd(render);
    float endX = m_currentX;

    // float yOffset =

    if (g_enableTextRendererDebugDraw) {
        render->drawRectf(startX, m_currentY, endX - startX, 1.0f, 0xFFFF0000);
        render->drawRectf(startX, m_currentY - m_font->get_ascender(m_fontSize), endX - startX, 1.0f, 0xFF0000FF);
        render->drawRectf(startX, m_currentY - m_font->get_ascender(m_fontSize) + m_font->get_lineHeight(m_fontSize), endX - startX, 1.0f, 0xFFFF00FF);
        render->drawRectf(startX, m_currentY - m_font->get_descender(m_fontSize), endX - startX, 1.0f, 0xFF00FF00);
    }
}

void grUiTextRenderer::doRender(grUiRenderer *render, const grUiSpannedText &str, uint32_t color, bool forceColor) {
    bool doEllipsize = !std::isnan(m_ellipsizeMaxX);
    float ellipsisWidth;
    if (doEllipsize) {
        ellipsisWidth = advanceCharacterDryRun(GTXT('\u2026'));
    }

    // for (const grUiTextSpan &span : str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        const grUiTextSpan &span = *it;
        for (gtl::WIDECHAR c : span.text) {
            if (doEllipsize) {
                // TODO: ellipsize currently does not support images in the text
                float nextX           = m_currentX + advanceCharacterDryRun(c);
                float ellipsizedNextX = m_currentX + ellipsisWidth;
                if (nextX > m_ellipsizeMaxX || ellipsizedNextX > m_ellipsizeMaxX) {
                    renderCharacter(render, GTXT('\u2026'), span.hasColor && !forceColor ? span.color.argb : color);
                    break;
                } else {
                    renderCharacter(render, c, span.hasColor && !forceColor ? span.color.argb : color);
                }
            } else {
                if (!span.image.empty()) {
                    renderEnd(render);
                    grUiSprite sprite(span.image);
                    float y    = m_currentY - get_ascender() / 2 - sprite.dstHeight / 2;
                    m_currentX = ceil(m_currentX);
                    render->drawSprite(m_currentX, round(y), sprite);
                    m_previousChar = 0;
                    m_currentX += sprite.dstWidth;
                    renderBegin(render);
                } else {
                    renderCharacter(render, c, span.hasColor && !forceColor ? span.color.argb : color);
                }
            }
        }
    }
}

void grUiTextRenderer::renderWithOutline(grUiRenderer *render, const grUiSpannedText &text, uint32_t color) {
    auto pos = saveTextPosition();

    grColor grc{ color };

    renderBegin(render, 1.0f);
    doRender(
        render,
        text,
        grc.get_red() >= 0x80 || grc.get_green() >= 0x80 || grc.get_blue() >= 0x80
            ? ((color & 0xFF000000) | 0x000000)
            : ((color & 0xFF000000) | 0xFFFFFF),
        true);
    renderEnd(render);

    restoreTextPosition(pos);

    renderBegin(render);
    doRender(render, text, color);
    renderEnd(render);
}

void grUiTextRenderer::renderWrapped(grUiRenderer *render, const grUiSpannedText &text, float maximumWidth,
    uint32_t color, HorizontalAlign align) {
    renderBegin(render);

    std::deque<std::pair<uint32_t, float>> lineBreakOffsets;
    findLineBreakOffsets(text, maximumWidth, lineBreakOffsets);

    reset();

    uint32_t nextLineBreakOffset = UINT32_MAX;
    float currLineLength         = maximumWidth;
    if (!lineBreakOffsets.empty()) {
        nextLineBreakOffset = lineBreakOffsets.front().first;
        currLineLength      = lineBreakOffsets.front().second;
        setupCurrLineBegin(align, currLineLength, maximumWidth);
        lineBreakOffsets.pop_front();
    }
    uint32_t characterIndex = 0;
    float lineHeight        = get_lineHeight();
    for (const grUiTextSpan &span : text) {
        for (gtl::WIDECHAR c : span.text) {
            if (nextLineBreakOffset != UINT32_MAX && characterIndex == nextLineBreakOffset) {
                m_currentX = m_originX;
                m_currentY += lineHeight;

                if (!lineBreakOffsets.empty()) {
                    nextLineBreakOffset = lineBreakOffsets.front().first;
                    currLineLength      = lineBreakOffsets.front().second;
                    setupCurrLineBegin(align, currLineLength, maximumWidth);
                    lineBreakOffsets.pop_front();
                } else {
                    nextLineBreakOffset = UINT32_MAX;
                }
            }
            if (!span.image.empty()) {
                renderEnd(render);
                grUiSprite sprite(span.image);
                float y                 = m_currentY - get_ascender();
                m_currentX              = ceil(m_currentX);
                auto iconRatio          = std::min(1.0f, lineHeight / sprite.dstHeight);
                grUiSprite scaledSprite = sprite.withDstSize(iconRatio * sprite.dstWidth, iconRatio * sprite.dstHeight);
                render->drawSprite(
                    m_currentX,
                    round(y),
                    scaledSprite);
                m_previousChar = 0;
                m_currentX += scaledSprite.dstWidth;
                characterIndex++;
                renderBegin(render);
            } else {
                renderCharacter(render, c, span.hasColor ? span.color.argb : color);
                characterIndex++;
            }
        }
    }

    renderEnd(render);
}

float grUiTextRenderer::renderCharacter(grUiRenderer *render, gtl::WIDECHAR c, uint32_t color) {
    const grFontSpec &fontSpec = m_font->fontSpec;

    if (c != '\t' && c != '\n' && c != '\r') {
        const grFontGlyphSpec &glyph = m_font->get_glyphFromChar(c);

        if (glyph.hasBounds) {
            float minU        = glyph.atlasBounds.left / (float)fontSpec.atlasWidth;
            float minV        = 1.0f - glyph.atlasBounds.top / (float)fontSpec.atlasHeight;
            float maxU        = glyph.atlasBounds.right / (float)fontSpec.atlasWidth;
            float maxV        = 1.0f - glyph.atlasBounds.bottom / (float)fontSpec.atlasHeight;
            float szTop       = glyph.planeBounds.top * m_fontSize;
            float szLeft      = glyph.planeBounds.left * m_fontSize;
            float dstWidth    = (glyph.planeBounds.right - glyph.planeBounds.left) * m_fontSize;
            float dstHeight   = (glyph.planeBounds.top - glyph.planeBounds.bottom) * m_fontSize;
            grUiSprite sprite = { m_font->textureSRID, minU, minV, maxU, maxV, dstWidth, dstHeight };
            render->drawSprite(m_currentX + szLeft, m_currentY - szTop, sprite, color);
        }
    }

    return advanceCharacter(c);
}

void grUiTextRenderer::renderBegin(grUiRenderer *render, float bias) {
    const grFontSpec &fontSpec = m_font->fontSpec;

    if (fontSpec.useMSDF) {
        grUiDrawEffectData msdfEffect{};
        msdfEffect.effectId     = 1;
        msdfEffect.effectParam1 = (m_fontSize / fontSpec.atlasSize) * fontSpec.distanceRange;
        msdfEffect.effectParam2 = bias;
        render->set_uiDrawEffect(msdfEffect);
    }
}

void grUiTextRenderer::renderEnd(grUiRenderer *render) {
    const grFontSpec &fontSpec = m_font->fontSpec;

    if (fontSpec.useMSDF) {
        grUiDrawEffectData defEffect{};
        defEffect.effectId = 0;
        render->set_uiDrawEffect(defEffect);
    }
}

float grUiTextRenderer::advanceCharacter(gtl::WIDECHAR c) {
    float adv = advanceCharacterDryRun(c);

    m_currentX += adv;
    m_previousChar = c;

    return adv;
}

float grUiTextRenderer::advanceCharacterDryRun(gtl::WIDECHAR c) {
    float adv;
    if (c == '\t') {
        adv = 1.0f * m_fontSize;
    } else {
        const grFontSpec &fontSpec = m_font->fontSpec;

        const grFontGlyphSpec &glyph = m_font->get_glyphFromChar(c);

        grFontKerningPairKey kpk{ m_previousChar, c };
        float advance = glyph.advance;
        auto it       = fontSpec.kerningPairs.find(kpk);
        if (it != fontSpec.kerningPairs.end()) {
            advance += it->second;
        }
        adv = advance * m_fontSize;
    }

    return adv;
}

void grUiTextRenderer::setupCurrLineBegin(HorizontalAlign align, float lineLength, float maximumWidth) {
    m_currentX = m_originX;

    switch (align) {
    case HorizontalAlign::LEFT:
        break;

    case HorizontalAlign::CENTER:
        m_currentX += std::floor((maximumWidth - lineLength) / 2);
        break;

    case HorizontalAlign::RIGHT:
        m_currentX += std::floor(maximumWidth - lineLength);
        break;
    }
}

void grUiTextRenderer::findLineBreakOffsets(const grUiSpannedText &text, float maximumWidth,
    std::deque<std::pair<uint32_t, float>> &lineBreakOffsets) {
    gtl::String str = text.get_text();

    UErrorCode err = U_ZERO_ERROR;
    UText *ut      = utext_openUChars(nullptr, reinterpret_cast<const UChar *>(str.toCString()), str.size(), &err);
    if (U_FAILURE(err)) {
        GR_FATAL(GTXT("utext_openUChars failed: %hs"), u_errorName(err));
    }

    err = U_ZERO_ERROR;

    static icu::BreakIterator *brit = icu::BreakIterator::createLineInstance(icu::Locale::getUS(), err);
    if (U_FAILURE(err)) {
        GR_FATAL(GTXT("icu::BreakIterator::createWordInstance failed: %hs"), u_errorName(err));
    }

    err = U_ZERO_ERROR;
    brit->setText(ut, err);
    if (U_FAILURE(err)) {
        GR_FATAL(GTXT("icu::BreakIterator::setText failed: %hs"), u_errorName(err));
    }

    reset();

    uint32_t characterIndex = 0;

    auto lastBreakSpanIterator      = text.begin();
    uint32_t lastBreakSpanCharIndex = 0;

    int32_t nextBreakOffset       = brit->first();
    int32_t lastBreakOffset       = 0;
    int32_t lastActualBreakOffset = 0;
    float lastCurrLineLength      = 0;
    for (auto spit = text.begin(); spit != text.end(); ++spit) {
        for (uint32_t i = 0; i < spit->text.size(); i++) {
            if (spit->text[i] == '\n') {
                lineBreakOffsets.emplace_back(characterIndex + 1, m_currentX - m_originX);
                lastBreakSpanIterator  = spit;
                lastBreakSpanCharIndex = i;
                lastBreakOffset        = characterIndex;
                while (nextBreakOffset <= characterIndex && nextBreakOffset != icu::BreakIterator::DONE) {
                    nextBreakOffset = brit->next();
                }
                characterIndex++;
                m_currentX = m_originX;
                continue;
            }
            if (m_currentX >= m_originX + maximumWidth) {
                if (lastBreakOffset == lastActualBreakOffset) {
                    lineBreakOffsets.emplace_back(characterIndex, m_currentX - m_originX);

                    lastBreakSpanIterator  = spit;
                    lastBreakSpanCharIndex = i;
                    lastBreakOffset        = characterIndex;
                } else {
                    lineBreakOffsets.emplace_back(lastBreakOffset, lastCurrLineLength);

                    spit           = lastBreakSpanIterator;
                    i              = lastBreakSpanCharIndex;
                    characterIndex = lastBreakOffset;
                }
                lastActualBreakOffset = lastBreakOffset;
                m_currentX            = m_originX;
            }
            if (nextBreakOffset != icu::BreakIterator::DONE && characterIndex == nextBreakOffset) {
                lastBreakSpanIterator  = spit;
                lastBreakSpanCharIndex = i;
                lastBreakOffset        = characterIndex;
                lastCurrLineLength     = m_currentX - m_originX;

                nextBreakOffset = brit->next();
            }
            if (!spit->image.empty()) {
                grUiSprite sprite(spit->image);
                m_previousChar = 0;
                m_currentX     = ceil(m_currentX);
                m_currentX += sprite.dstWidth;
            } else {
                advanceCharacter(spit->text[i]);
            }
            characterIndex++;
        }
    }

    lineBreakOffsets.emplace_back(characterIndex + 1, m_currentX - m_originX);

    utext_close(ut);
}

float grUiTextRenderer::get_width(const grUiSpannedText &text, int untilChar) {
    int characterIndex = 0;
    float width        = 0.0f;
    for (const grUiTextSpan &span : text) {
        for (gtl::WIDECHAR c : span.text) {
            if (untilChar >= 0 && characterIndex >= untilChar) return width;

            if (!span.image.empty()) {
                grUiSprite sprite(span.image);
                m_previousChar = 0;
                m_currentX     = ceil(m_currentX);
                m_currentX += sprite.dstWidth;
                width += sprite.dstWidth;

                characterIndex++;
            } else {
                width += advanceCharacter(c);
                characterIndex++;
            }
        }
    }
    return width;
}

float grUiTextRenderer::getWidthWrapped(const grUiSpannedText &text, float maximumWidth, int untilChar) {
    std::deque<std::pair<uint32_t, float>> lineBreakOffsets;
    findLineBreakOffsets(text, maximumWidth, lineBreakOffsets);

    if (lineBreakOffsets.size() > 1) {
        return maximumWidth;
    }

    return get_width(text, untilChar);
}

int grUiTextRenderer::get_charPositionFromX(const grUiSpannedText &text, float x) {
    int characterIndex = 0;
    float width        = 0.0f;
    for (const grUiTextSpan &span : text) {
        for (gtl::WIDECHAR c : span.text) {
            if (width >= x) return characterIndex;

            if (!span.image.empty()) {
                grUiSprite sprite(span.image);
                m_previousChar = 0;
                m_currentX     = ceil(m_currentX);
                m_currentX += sprite.dstWidth;
                width += sprite.dstWidth;

                characterIndex++;
            } else {
                width += advanceCharacter(c);
                characterIndex++;
            }
        }
    }
    return characterIndex;
}

float grUiTextRenderer::get_ascender() const {
    return m_font->get_ascender(m_fontSize);
}

float grUiTextRenderer::get_descender() const {
    return m_font->get_descender(m_fontSize);
}

float grUiTextRenderer::get_lineHeight() const {
    return m_font->get_lineHeight(m_fontSize);
}

float grUiTextRenderer::get_baselineOffsetFromLineTop() const {
    return (get_lineHeight() + get_ascender()) * 0.5f;
}
