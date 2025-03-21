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

#include "String.h"

#include <unicode/ucnv.h>
#include <unicode/stsearch.h>
#include <gtlUtil/Logging.h>

template class GTL_DLLIMPEXP gtl::BaseString<gtl::ASCIICHAR>;
template class GTL_DLLIMPEXP gtl::BaseString<gtl::WIDECHAR>;

static const char *unicodeConverterNames[gtl::String::S_CHARSET_MAX]{
    "US-ASCII",
    "UTF-8",
    nullptr
};

static UConverter *unicodeConverters[gtl::String::S_CHARSET_MAX]{};

static UConverter *getUnicodeConverter(int charset) {
    UConverter *&conv = unicodeConverters[charset];
    if (!conv) {
        UErrorCode err = U_ZERO_ERROR;
        conv           = ucnv_open(unicodeConverterNames[charset], &err);
        if (U_FAILURE(err)) {
            GR_FATAL(GTXT("cannot open unicode converter %hs"), unicodeConverterNames[charset]);
        }
    }
    return conv;
}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::WIDECHAR>::BaseString(const ASCIICHAR *str, SCharset charset)
    : BaseString(-1, str, charset) {}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::ASCIICHAR>::BaseString(const WIDECHAR *str, SCharset charset)
    : BaseString(-1, str, charset) {
}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::WIDECHAR>::BaseString(int32_t length, const ASCIICHAR *str, SCharset charset) : BaseString() {
    UConverter *cvt    = getUnicodeConverter(charset);
    UErrorCode errCode = U_ZERO_ERROR;
    int32_t size       = ucnv_toUChars(cvt, nullptr, 0, str, length, &errCode);
    if (U_FAILURE(errCode) && errCode != U_BUFFER_OVERFLOW_ERROR) {
        GR_FATAL(GTXT("Cannot convert string to UTF-16: %hs"), u_errorName(errCode));
    }
    resize(size);
    errCode = U_ZERO_ERROR;
    size    = ucnv_toUChars(cvt, reinterpret_cast<UChar *>(forceCopy()), size + 1, str, length, &errCode);
    if (U_FAILURE(errCode)) {
        GR_FATAL(GTXT("Cannot convert string to UTF-16: %hs"), u_errorName(errCode));
    }
}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::ASCIICHAR>::BaseString(int32_t length, const WIDECHAR *str, SCharset charset) : BaseString() {
    UConverter *cvt    = getUnicodeConverter(charset);
    UErrorCode errCode = U_ZERO_ERROR;
    int32_t size       = ucnv_fromUChars(cvt, nullptr, 0, reinterpret_cast<const UChar *>(str), length, &errCode);
    if (U_FAILURE(errCode) && errCode != U_BUFFER_OVERFLOW_ERROR) {
        GR_FATAL(GTXT("Cannot convert string from UTF-16: %hs"), u_errorName(errCode));
    }
    resize(size);
    errCode = U_ZERO_ERROR;
    size    = ucnv_fromUChars(cvt, forceCopy(), size + 1, reinterpret_cast<const UChar *>(str), length, &errCode);
    if (U_FAILURE(errCode)) {
        GR_FATAL(GTXT("Cannot convert string from UTF-16: %hs"), u_errorName(errCode));
    }
}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::WIDECHAR>::BaseString(const gtl::AString &str, SCharset charset)
    : BaseString(str.size(), str.toCString(), charset) {}

template <>
template <>
GTL_DLLIMPEXP gtl::BaseString<gtl::ASCIICHAR>::BaseString(const gtl::String &str, SCharset charset)
    : BaseString(str.size(), str.toCString(), charset) {}


template <>
GTL_DLLIMPEXP uint32_t gtl::BaseString<gtl::WIDECHAR>::findIgnoreCaseImpl(const gtl::BaseString<gtl::WIDECHAR> &needle) const {
    icu::UnicodeString uSelf(true, toCString(), (int32_t)size());
    icu::UnicodeString uNeedle(true, needle.toCString(), (int32_t)needle.size());

    UErrorCode status = U_ZERO_ERROR;
    auto *search = new icu::StringSearch(
        uNeedle,
        uSelf,
        icu::Locale::getRoot(),
        nullptr,
        status);

    search->getCollator()->setStrength(icu::Collator::SECONDARY); // make case-insensitive

    uint32_t result = size();

    if (status == U_ZERO_ERROR) {
        int32_t pos = search->first(status);
        if (status == U_ZERO_ERROR && pos != USEARCH_DONE) {
            result = pos;
        }
    }

    delete search;

    return result;
}
