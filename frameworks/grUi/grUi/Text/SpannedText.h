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

#include <gtlString/String.h>
#include <grColor.h>

struct grUiTextSpan {
    gtl::String text;
    grColor color;
    gtl::PooledString image;

    bool hasColor : 1;

    grUiTextSpan() : color(), hasColor(false) {}
    grUiTextSpan(gtl::String text) : text(std::move(text)), hasColor(false) {}
    grUiTextSpan(gtl::String text, grColor color) : text(std::move(text)), color(color), hasColor(true) {}
    explicit grUiTextSpan(gtl::PooledString image)
        : text(GTXT("\uFFFC")),
          color(),
          image(std::move(image)),
          hasColor(false) {}

    bool empty() const {
        return text.empty();
    }
};

class grUiSpannedText {
    std::vector<grUiTextSpan> m_spans;
    gtl::String m_text;

public:
    typedef decltype(m_spans)::const_iterator iterator;

    grUiSpannedText() {}

    grUiSpannedText(const gtl::String &rawString) {
        set_text(rawString);
    }

    auto begin() const {
        return m_spans.begin();
    }

    auto end() const {
        return m_spans.end();
    }

    void clear() {
        m_text = gtl::String();
        m_spans.clear();
    }

    uint32_t size() const {
        return m_text.size();
    }

    bool empty() const {
        if (m_spans.empty()) return true;

        for (auto &span : m_spans) {
            if (!span.empty()) return false;
        }

        return true;
    }

    void addSpan(grUiTextSpan span) {
        m_text += span.text;
        m_spans.push_back(std::move(span));
    }

    void append(grUiSpannedText text) {
        for (auto &span : text) {
            m_spans.push_back(span);
        }

        m_text += text.get_text();
    }

    void append(grUiSpannedText text, grColor color) {
        for (auto &span : text) {
            grUiTextSpan spanCopy = span;
            if (!spanCopy.hasColor) {
                spanCopy.hasColor = true;
                spanCopy.color    = color;
            }
            m_spans.push_back(spanCopy);
        }

        m_text += text.get_text();
    }

    void replaceRange(size_t startIndex, size_t endIndex, const gtl::String &str) {
        assert(endIndex >= startIndex);

        // find range
        auto startSpan = m_spans.end(), endSpan = m_spans.end();
        size_t startCharIndex = 0, endCharIndex = 0;
        size_t curIndex = 0;
        for (auto it = m_spans.begin(); it != m_spans.end(); ++it) {
            auto &span = *it;
            for (size_t i = 0; i < span.text.size(); i++) {
                if (curIndex == startIndex) {
                    // we start here
                    startSpan      = it;
                    startCharIndex = i;
                }

                if (curIndex == endIndex) {
                    // ... and end here
                    endSpan      = it;
                    endCharIndex = i;
                    goto finishLoop;
                }

                curIndex++;
            }
        }
    finishLoop:

        if (startSpan != m_spans.end() && !startSpan->image.empty()) {
            replaceRange(startIndex, endIndex, grUiTextSpan(str));
            return;
        }

        m_text = m_text.substr(0, startIndex) + str + m_text.substr(endIndex);
        if (startSpan == m_spans.end()) {
            if (m_spans.empty()) {
                m_spans.push_back(str);
            } else {
                auto finalSpan = m_spans.rbegin();
                if (!finalSpan->image.empty()) {
                    m_spans.push_back(str);
                } else {
                    m_spans.rbegin()->text += str;
                }
            }
        } else if (endSpan != startSpan) {
            startSpan->text = startSpan->text.substr(0, startCharIndex) + str;
            if (endSpan != m_spans.end()) {
                endSpan->text = endSpan->text.substr(endCharIndex);
            }

            if (startSpan->empty()) {
                m_spans.erase(startSpan, endSpan);
            } else {
                auto cutoutStartSpan = startSpan;
                ++cutoutStartSpan;
                m_spans.erase(cutoutStartSpan, endSpan);
            }
        } else {
            startSpan->text = startSpan->text.substr(0, startCharIndex) + str + startSpan->text.substr(endCharIndex);
            if (startSpan->empty()) {
                m_spans.erase(startSpan);
            }
        }
    }

    void replaceRange(size_t startIndex, size_t endIndex, const grUiTextSpan &span) {
        assert(endIndex >= startIndex);

        // find range
        auto startSpan = m_spans.end(), endSpan = m_spans.end();
        size_t startCharIndex = 0, endCharIndex = 0;
        size_t curIndex = 0;
        for (auto it = m_spans.begin(); it != m_spans.end(); ++it) {
            auto &curSpan = *it;
            for (size_t i = 0; i < curSpan.text.size(); i++) {
                if (curIndex == startIndex) {
                    // we start here
                    startSpan      = it;
                    startCharIndex = i;
                }

                if (curIndex == endIndex) {
                    // ... and end here
                    endSpan      = it;
                    endCharIndex = i;
                    goto finishLoop;
                }

                curIndex++;
            }
        }
    finishLoop:

        if (startSpan == m_spans.end()) {
            m_text += span.text;

            m_spans.push_back(span);
        } else if (endSpan != startSpan) {
            m_text = m_text.substr(0, startIndex) + span.text + m_text.substr(endIndex);

            startSpan->text = startSpan->text.substr(0, startCharIndex);
            if (endSpan != m_spans.end()) {
                endSpan->text = endSpan->text.substr(endCharIndex);
            }

            auto cutoutStartSpan = startSpan;
            if (!startSpan->empty()) ++cutoutStartSpan;
            m_spans.insert(m_spans.erase(cutoutStartSpan, endSpan), span);
        } else {
            m_text = m_text.substr(0, startIndex) + span.text + m_text.substr(endIndex);

            std::vector<grUiTextSpan>::iterator it;
            grUiTextSpan tmpSpan = *startSpan;
            tmpSpan.text         = tmpSpan.text.substr(endCharIndex);

            if (startCharIndex == 0) {
                it = m_spans.erase(startSpan);
            } else {
                startSpan->text = startSpan->text.substr(0, startCharIndex);
                it              = startSpan;
                ++it;
            }

            it = m_spans.insert(it, span);
            ++it;
            m_spans.insert(it, tmpSpan);
        }
    }

    const gtl::String &get_text() const {
        return m_text;
    }

    void set_text(const gtl::String &text) {
        clear();
        addSpan(text);
    }

    grUiSpannedText &operator=(const grUiSpannedText &other) {
        if (&other == this) return *this;

        m_spans = other.m_spans;
        m_text  = other.m_text;

        return *this;
    }

    grUiSpannedText &operator=(const gtl::String &str) {
        set_text(str);

        return *this;
    }

    // following methods are intended for use in bindings

    void addTextSpan(const gtl::String &str) {
        addSpan(grUiTextSpan{ str });
    }

    void addTextSpan(const gtl::String &str, grColor color) {
        addSpan(grUiTextSpan{ str, color });
    }

    void addImageSpan(const gtl::PooledString &str) {
        addSpan(grUiTextSpan{ str });
    }
};
