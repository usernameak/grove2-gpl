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

#include <cassert>
#include <gtlUtil/Misc.h>
#include <gtlMemory/MemAlloc.h>
#include <gtlString/CString.h>
#include <cstdarg>
#include <functional>
#include <atomic>
#include <unicode/unistr.h>

namespace gtl {
    /// Mutable copy-on-write string type.
    ///
    /// <p><strong>Thread safety notice:</strong> if a string is copied at the same time as it is modified,
    /// both strings might become in an invalid state. Synchronization is required.
    /// Reference counting is synchronized, though.</p>
    template <typename TCharType>
    class
#ifdef GTL_LOAD_DLL
        GTL_DLLIMPEXP
#endif
            BaseString {
    public:
        typedef TCharType CharType;
        typedef const CharType *iterator;

    private:
        struct StringPeer {
            uint32_t length;
            uint32_t capacity;
            std::atomic_uint32_t refcount;
            CharType strdata[1];

            GTL_FORCEINLINE static StringPeer *create(uint32_t capacity) {
                StringPeer *peer = (StringPeer *)gtlMalloc(sizeofPeer(capacity));
                new (peer) StringPeer(capacity);
                return peer;
            }

            GTL_FORCEINLINE void release() {
                if (refcount.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                    this->~StringPeer();
                    gtlFree(this);
                }
            }

            StringPeer(uint32_t capacity)
                : length(0),
                  capacity(capacity),
                  refcount(1),
                  strdata{ 0 } {}
        } *m_peer;

        static_assert(std::is_standard_layout_v<StringPeer>, "StringPeer is not standard layout");

        GTL_FORCEINLINE static constexpr size_t sizeofPeer(size_t len) {
            return offsetof(StringPeer, strdata) + (len + 1) * sizeof(CharType);
        }

    public:
        enum SCharset {
            S_CHARSET_ASCII,
            S_CHARSET_UTF8,
            S_CHARSET_NATIVE,

            S_CHARSET_MAX
        };

        BaseString() {
            static StringPeer emptyStringPeer{ 0 };
            m_peer = &emptyStringPeer;
            m_peer->refcount.fetch_add(1, std::memory_order_acq_rel);
        }

        explicit BaseString(uint32_t capacity) {
            m_peer = StringPeer::create(capacity);
        }

        BaseString(const CharType *str) {
            size_t len = StrLen(str);
            assert(len <= UINT32_MAX);
            m_peer         = StringPeer::create((uint32_t)len);
            m_peer->length = (uint32_t)len;
            StrCpy(m_peer->strdata, str);
        }

        BaseString(const CharType *str, int32_t len) {
            m_peer         = StringPeer::create(len);
            m_peer->length = len;
            memcpy(m_peer->strdata, str, sizeof(CharType) * len);
            m_peer->strdata[len] = 0;
        }

        template <typename U = CharType>
        BaseString(const ASCIICHAR *str, SCharset charset = S_CHARSET_UTF8) = delete;

        template <typename U = CharType>
        BaseString(const WIDECHAR *str, SCharset charset = S_CHARSET_UTF8) = delete;

        template <typename U = CharType>
        BaseString(int32_t length, const ASCIICHAR *str, SCharset charset = S_CHARSET_UTF8) = delete;

        template <typename U = CharType>
        BaseString(int32_t length, const WIDECHAR *str, SCharset charset = S_CHARSET_UTF8) = delete;

        template <typename U = CharType>
        BaseString(const BaseString<ASCIICHAR> &str, SCharset charset = S_CHARSET_UTF8) = delete;

        template <typename U = CharType>
        BaseString(const BaseString<WIDECHAR> &str, SCharset charset = S_CHARSET_UTF8) = delete;

        GTL_FORCEINLINE BaseString(const BaseString<CharType> &other) : m_peer(other.m_peer) {
            m_peer->refcount.fetch_add(1, std::memory_order_acq_rel);
        }

        GTL_FORCEINLINE ~BaseString() {
            m_peer->release();
        }

        void reserve(size_t newCapacity) {
            assert(m_peer->refcount.load(std::memory_order_relaxed) >= 1);

            if (newCapacity == m_peer->capacity)
                return;

            StringPeer *oldPeer = m_peer;
            size_t newLength    = oldPeer->length;
            if (newLength > newCapacity) {
                newLength = newCapacity;
            }

            m_peer         = StringPeer::create((uint32_t)newCapacity);
            m_peer->length = (uint32_t)newLength;
            memcpy(m_peer->strdata, oldPeer->strdata, newLength * sizeof(CharType));
            oldPeer->release();

            m_peer->strdata[newLength] = 0;
        }

        void resize(uint32_t newLength) {
            if (size() == newLength)
                return;
            if (newLength > m_peer->capacity) {
                reserve(newLength);
            }
            CharType *str       = forceCopy();
            m_peer->length      = newLength;
            str[m_peer->length] = 0;
        }

        GTL_FORCEINLINE iterator begin() const {
            return &operator[](0);
        }

        GTL_FORCEINLINE iterator end() const {
            return &operator[](size());
        }

        GTL_FORCEINLINE uint32_t size() const {
            return m_peer->length;
        }

        BaseString<CharType> &operator+=(const BaseString<CharType> &other) {
            if (empty()) {
                return operator=(other);
            }
            append(other.toCString(), other.size());
            return *this;
        }

        BaseString<CharType> &operator+=(const CharType *other) {
            size_t len = StrLen(other);
            append(other, len);
            return *this;
        }

        BaseString<CharType> &operator+=(CharType ch) {
            if (empty()) {
                return operator=(ch);
            }
            append(&ch, 1);
            return *this;
        }

        void append(const CharType *str, size_t len) {
            if (len == 0) {
                return;
            }
            if (empty()) {
                return assign(str, len);
            }
            if (m_peer->capacity < len + size()) {
                reserve(len + size());
            }
            CharType *thisstr = forceCopy();
            memcpy(thisstr + size(), str, len * sizeof(CharType));
            m_peer->length          = size() + (uint32_t)len;
            thisstr[m_peer->length] = 0;
        }

        BaseString &operator=(const BaseString<CharType> &other) { // NOLINT(bugprone-unhandled-self-assignment)
            if (other.m_peer == m_peer) {                          // self-assignment
                return *this;
            }
            m_peer->release();
            m_peer = other.m_peer;
            m_peer->refcount.fetch_add(1, std::memory_order_acq_rel);
            return *this;
        }

        BaseString &operator=(const CharType *other) {
            if (other == m_peer->strdata) { // self-assignment
                return *this;
            }
            size_t len = StrLen(other);
            assert(len <= UINT32_MAX);

            assign(other, len);

            return *this;
        }

        BaseString &operator=(CharType ch) {
            assign(&ch, 1);

            return *this;
        }

        void assign(const CharType *str, size_t len) {
            if (str == m_peer->strdata) { // self-assignment
                return;
            }
            if (m_peer->refcount.load(std::memory_order_relaxed) == 1) {
                if (m_peer->capacity < len) {
                    reserve(len);
                }
            } else {
                m_peer->release();
                m_peer = StringPeer::create((uint32_t)len);
            }

            m_peer->length = (uint32_t)len;
            memcpy(m_peer->strdata, str, len * sizeof(CharType));
            m_peer->strdata[m_peer->length] = 0;
        }

        uint32_t find(const gtl::BaseString<CharType> &needle) const {
            if (needle.size() == 0) {
                return 0;
            }
            if (needle.size() > size()) {
                return size();
            }

            for (uint32_t i = 0; i <= size() - needle.size(); ++i) {
                if (memcmp(toCString() + i, needle.toCString(), needle.size() * sizeof(CharType)) == 0) {
                    return i;
                }
            }
            return size();
        }

        template <typename U = CharType>
        uint32_t findIgnoreCase(const gtl::BaseString<CharType> &needle) const {
            static_assert(std::is_same_v<CharType, WIDECHAR>);

            return findIgnoreCaseImpl(needle);
        }

        template <typename U = CharType>
        icu::UnicodeString toICUStringCOW() const {
            static_assert(std::is_same_v<CharType, WIDECHAR>);

            return { true, toCString(), (int32_t)size() };
        }

        template <typename U = CharType>
        icu::UnicodeString toICUString() const {
            static_assert(std::is_same_v<CharType, WIDECHAR>);

            return { toCString(), (int32_t)size() };
        }

        template <typename U = CharType>
        static BaseString<WIDECHAR> fromICUString(const icu::UnicodeString &icustr) {
            static_assert(std::is_same_v<CharType, WIDECHAR>);

            return { (const WIDECHAR *)icustr.getBuffer(), icustr.length() };
        }

        uint32_t indexOf(CharType ch, uint32_t from = 0) const {
            for (uint32_t i = from; i < size(); ++i) {
                if (operator[](i) == ch)
                    return i;
            }
            return size();
        }

        uint32_t lastIndexOf(CharType ch) const {
            if (empty()) return 0;

            for (uint32_t i = size() - 1;; --i) {
                if (operator[](i) == ch)
                    return i;

                if (i == 0) break;
            }
            return size();
        }

        BaseString<CharType> toLowerCase() const {
            auto str        = *this;
            CharType *chars = str.forceCopy();
            for (uint32_t i = 0; i < str.size(); i++) {
                chars[i] = gtl::ToLower(chars[i]);
            }
            return str;
        }

        BaseString<CharType> toUpperCase() const {
            auto str        = *this;
            CharType *chars = str.forceCopy();
            for (uint32_t i = 0; i < str.size(); i++) {
                chars[i] = gtl::ToUpper(chars[i]);
            }
            return str;
        }

        BaseString<CharType> substr(uint32_t start, uint32_t end = UINT32_MAX) const {
            BaseString<CharType> newStr;
            if (end > size())
                end = size();
            if (start < end) {
                newStr.assign(toCString() + start, end - start);
            }
            return newStr;
        }

        GTL_FORCEINLINE BaseString<CharType> operator+(const BaseString<CharType> &other) const {
            BaseString newStr(size() + other.size());
            newStr += *this;
            newStr += other;
            return newStr;
        }

        GTL_FORCEINLINE BaseString<CharType> operator+(const CharType *other) const {
            size_t len = StrLen(other);
            BaseString newStr(size() + (uint32_t)len);
            newStr += *this;
            newStr.append(other, len);
            return newStr;
        }

        GTL_FORCEINLINE BaseString<CharType> operator+(CharType ch) const {
            BaseString newStr(size() + 1);
            newStr += *this;
            newStr += ch;
            return newStr;
        }

        bool operator==(const BaseString &other) const {
            if (other.m_peer == m_peer)
                return true;

            if (other.size() != size())
                return false;

            return memcmp(other.m_peer->strdata, m_peer->strdata, size() * sizeof(CharType)) == 0;
        }

        GTL_FORCEINLINE bool operator!=(const BaseString &other) const {
            return !operator==(other);
        }

        int compare(uint32_t start, uint32_t len, const BaseString<CharType> &str) const {
            uint32_t ssiz   = str.size();
            uint32_t minLen = len < ssiz ? len : ssiz;
            int cmp         = memcmp(toCString() + start, str.toCString(), minLen * sizeof(CharType));
            if (cmp != 0)
                return cmp;
            if (len < ssiz) {
                return -1;
            }
            if (len > ssiz) {
                return 1;
            }
            return 0;
        }

        GTL_FORCEINLINE bool operator<(const BaseString<CharType> &other) const {
            return compare(0, size(), other) < 0;
        }

        GTL_FORCEINLINE bool operator<=(const BaseString<CharType> &other) const {
            return compare(0, size(), other) <= 0;
        }

        GTL_FORCEINLINE bool operator>(const BaseString<CharType> &other) const {
            return compare(0, size(), other) > 0;
        }

        GTL_FORCEINLINE bool operator>=(const BaseString<CharType> &other) const {
            return compare(0, size(), other) >= 0;
        }

        bool startsWith(const BaseString<CharType> &needle) const {
            if (size() < needle.size()) {
                return false;
            }
            return memcmp(needle.toCString(), toCString(), sizeof(CharType) * needle.size()) == 0;
        }

        bool endsWith(const BaseString<CharType> &needle) const {
            if (size() < needle.size()) {
                return false;
            }
            return 0 == compare(size() - needle.size(), needle.size(), needle);
        }

        GTL_FORCEINLINE const CharType &operator[](uint32_t pos) const {
            return toCString()[pos];
        }

        GTL_FORCEINLINE bool empty() const {
            return size() == 0;
        }

        /// Copies the string if the reference count is non-zero.
        /// Requires synchronization if used in a multithreaded context!
        CharType *forceCopy() {
            uint32_t oldRefcount = m_peer->refcount.load(std::memory_order_relaxed);

            assert(oldRefcount >= 1);

            if (oldRefcount == 1)
                return m_peer->strdata;

            StringPeer *oldPeer = m_peer;
            m_peer              = (StringPeer *)gtlMalloc(sizeofPeer(oldPeer->capacity)); // or should we copy by length, hm?
            memcpy(m_peer, oldPeer, sizeofPeer(oldPeer->length));                         // memcpy by length because we don't need data beyond string
            oldPeer->release();
            return m_peer->strdata;
        }

        GTL_FORCEINLINE const CharType *toCString() const {
            return m_peer->strdata;
        }

        static BaseString<CharType> vformat(const CharType *format, va_list args) {
            using namespace gtl;

            va_list argscopy;
            va_copy(argscopy, args);
            int length = gtl::VSPrintf(NULL, 0, format, args);
            if (length < 0) {
                va_end(argscopy);
                return GTXT("<Format error>");
            }
            BaseString<CharType> str(length);
            str.resize(length);
            gtl::VSPrintf(str.forceCopy(), length + 1, format, argscopy);
            va_end(argscopy);
            return str;
        }

        GTL_FORCEINLINE static BaseString<CharType> format(const CharType *format, ...) {
            va_list args;

            va_start(args, format);
            BaseString<CharType> str = vformat(format, args);
            va_end(args);

            return str;
        }

        bool toLongLong(long long &result, int radix = 10) const {
            errno               = 0;
            const CharType *str = toCString();
            CharType *endptr    = nullptr;
            long long val       = StrToLL(str, &endptr, radix);
            if (endptr == str) {
                return false;
            }
            if ((val == LLONG_MAX || val == LLONG_MIN) && errno == ERANGE) {
                return false;
            }
            result = val;
            return true;
        }

        bool toUInt32(std::uint32_t &result, int radix = 10) const {
            const CharType *str = toCString();
            CharType *endptr    = nullptr;
            errno               = 0;
            long long val       = StrToUL(str, &endptr, radix);
            if (endptr == str) {
                return false;
            }
            if ((val == ULONG_MAX) && errno == ERANGE) {
                return false;
            }
            if (val > (unsigned long long)UINT32_MAX) {
                return false;
            }
            result = (uint32_t)val;
            return true;
        }

        bool toDouble(double &result) const {
            const CharType *str = toCString();
            CharType *endptr    = nullptr;
            errno               = 0;
            double val          = StrToD(str, &endptr);
            if (endptr == str) {
                return false;
            }
            if (errno) {
                return false;
            }
            result = val;
            return true;
        }

        void insertCharacter(size_t offset, CharType ch) {
            size_t oldSize = size();
            assert(offset <= oldSize);

            resize(oldSize + 1);
            CharType *chars = forceCopy();
            memmove(chars + offset + 1, chars + offset, sizeof(CharType) * (oldSize - offset));
            chars[offset] = ch;
        }

    private:
        uint32_t findIgnoreCaseImpl(const gtl::BaseString<CharType> &needle) const;
    };

    template <>
    template <>
    BaseString<WIDECHAR>::BaseString(const ASCIICHAR *str, SCharset charset);

    template <>
    template <>
    BaseString<ASCIICHAR>::BaseString(const WIDECHAR *str, SCharset charset);

    template <>
    template <>
    BaseString<WIDECHAR>::BaseString(int32_t length, const ASCIICHAR *str, SCharset charset);

    template <>
    template <>
    BaseString<ASCIICHAR>::BaseString(int32_t length, const WIDECHAR *str, SCharset charset);

    template <>
    template <>
    BaseString<WIDECHAR>::BaseString(const BaseString<ASCIICHAR> &str, SCharset charset);

    template <>
    template <>
    BaseString<ASCIICHAR>::BaseString(const BaseString<WIDECHAR> &str, SCharset charset);

    template <>
    uint32_t gtl::BaseString<gtl::WIDECHAR>::findIgnoreCaseImpl(const gtl::BaseString<gtl::WIDECHAR> &needle) const;

#ifdef GTL_LOAD_DLL
    extern template class GTL_DLLIMPEXP BaseString<ASCIICHAR>;
    extern template class GTL_DLLIMPEXP BaseString<WIDECHAR>;
#else
    extern template class BaseString<ASCIICHAR>;
    extern template class BaseString<WIDECHAR>;
#endif

    typedef BaseString<ASCIICHAR> AString;
    typedef BaseString<WIDECHAR> String;
}

template <typename T>
gtl::BaseString<T> operator+(const T *a, const gtl::BaseString<T> b) {
    using namespace gtl;

    size_t len = StrLen(a);
    BaseString<T> ret(len + b.size());
    ret.assign(a, len);
    ret += b;
    return ret;
}

template <typename T>
bool operator==(const T *a, const gtl::BaseString<T> &b) {
    using namespace gtl;

    size_t len = StrLen(a);
    if (len != b.size()) {
        return false;
    }

    return memcmp(a, b.toCString(), len * sizeof(T)) == 0;
}

template <typename T>
bool operator==(const gtl::BaseString<T> &a, const T *b) {
    return b == a;
}

template <typename T>
bool operator!=(const T *a, const gtl::BaseString<T> &b) {
    return !(a == b);
}

template <typename T>
bool operator!=(const gtl::BaseString<T> &a, const T *b) {
    return b != a;
}

namespace std {
    template <typename T>
    struct hash<gtl::BaseString<T>> {
        std::size_t operator()(gtl::BaseString<T> s) const noexcept {
            // TODO: cache string hash values?
            std::size_t h = 0;
            for (gtl::WIDECHAR wc : s) {
                h = 31 * h + wc;
            }
            return h;
        }
    };
}
