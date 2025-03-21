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

#include "String.h"
#include "StringPool.h"

namespace gtl {
    template <typename CharType>
        requires std::integral<CharType>
    class BasePooledString {
        typename StringPool<CharType>::Handle m_handle;

        inline static CharType ZERO_CHAR = 0;

    public:
        constexpr BasePooledString()
            : m_handle(StringPool<CharType>::acquireEmptyString()) {}

        BasePooledString(const CharType *str)
            : m_handle(StringPool<CharType>::acquireString(str)) {}

        BasePooledString(const BaseString<CharType> &str)
            : m_handle(StringPool<CharType>::acquireString(str.toCString(), str.size())) {}

        BasePooledString(const BasePooledString &other)
            : m_handle(StringPool<CharType>::acquireString(other.m_handle)) {}

        BasePooledString(BasePooledString &&other) noexcept
            : m_handle(other.m_handle) {
            other.m_handle = StringPool<CharType>::acquireEmptyString();
        }

        ~BasePooledString() {
            StringPool<CharType>::releaseString(m_handle);
        }

        size_t hash() const {
            return StringPool<CharType>::getHash(m_handle);
        }

        size_t size() const {
            return StringPool<CharType>::getLength(m_handle);
        }

        GTL_FORCEINLINE bool empty() const {
            return size() == 0;
        }

        const CharType *toCString() const {
            return StringPool<CharType>::getStringPtr(m_handle);
        }

        explicit operator const CharType *() const {
            return toCString();
        }

        BasePooledString &operator=(const BasePooledString &other) {
            StringPool<CharType>::releaseString(m_handle);
            m_handle = StringPool<CharType>::acquireString(other.m_handle);
            return *this;
        }

        BasePooledString &operator=(BasePooledString &&other) noexcept {
            m_handle       = other.m_handle;
            other.m_handle = StringPool<CharType>::acquireEmptyString();
            return *this;
        }

        GTL_FORCEINLINE bool operator==(const BasePooledString &other) const {
            return other.m_handle == m_handle;
        }

        GTL_FORCEINLINE bool operator!=(const BasePooledString &other) const {
            return other.m_handle != m_handle;
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

        bool startsWith(const BasePooledString &needle) const {
            if (size() < needle.size()) {
                return false;
            }
            return memcmp(needle.toCString(), toCString(), sizeof(CharType) * needle.size()) == 0;
        }

        bool endsWith(const BasePooledString &needle) const {
            if (size() < needle.size()) {
                return false;
            }
            return 0 == compare(size() - needle.size(), needle.size(), needle);
        }

        int compare(uint32_t start, uint32_t len, const BasePooledString &str) const {
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

        GTL_FORCEINLINE const CharType &operator[](uint32_t pos) const {
            return toCString()[pos];
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

        explicit operator BaseString<CharType>() const {
            return BaseString<CharType>(toCString(), size());
        }

        friend struct std::hash<BasePooledString>;
    };

    using PooledString  = BasePooledString<WIDECHAR>;
    using PooledAString = BasePooledString<ASCIICHAR>;

    using Name = PooledAString;
}

namespace std {
    template <typename CharType>
    struct hash<gtl::BasePooledString<CharType>> {
        std::size_t operator()(const gtl::BasePooledString<CharType> &str) const noexcept {
            return str.hash();
        }
    };
}
