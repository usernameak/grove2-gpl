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

#include <cstring>
#include <gtlMemory/MemAlloc.h>
#include <type_traits>

class gtlRawFixedArray {
    size_t m_size;
    size_t m_itemSize;
    void *m_data;

    explicit gtlRawFixedArray(size_t size, size_t itemSize, void *data)
        : m_size(size), m_itemSize(itemSize), m_data(data) {}

public:
    explicit gtlRawFixedArray(size_t size, size_t itemSize)
        : m_size(size),
          m_itemSize(itemSize),
          m_data(gtlMalloc(size * itemSize)) {
    }

    gtlRawFixedArray(const gtlRawFixedArray &other)
        : m_size(other.m_size),
          m_itemSize(other.m_itemSize),
          m_data(gtlMalloc(m_size * m_itemSize)) {
        memcpy(m_data, other.m_data, m_size * m_itemSize);
    }

    gtlRawFixedArray(gtlRawFixedArray &&other) noexcept
        : m_size(other.m_size),
          m_itemSize(other.m_itemSize),
          m_data(other.m_data) {
        other.m_size = 0;
        other.m_data = nullptr;
    }

    ~gtlRawFixedArray() {
        gtlFree(m_data);
    }

    static gtlRawFixedArray createUnsafe(size_t size, size_t itemSize, void *data) {
        return gtlRawFixedArray(size, itemSize, data);
    }

    gtlRawFixedArray &operator=(const gtlRawFixedArray &other) {
        gtlFree(m_data);
        m_size     = other.m_size;
        m_itemSize = other.m_itemSize;
        m_data     = gtlMalloc(m_size * m_itemSize);
        memcpy(m_data, other.m_data, m_size * m_itemSize);
        return *this;
    }

    gtlRawFixedArray &operator=(gtlRawFixedArray &&other) {
        m_size     = other.m_size;
        m_itemSize = other.m_itemSize;
        m_data     = other.m_data;
        other.m_size = 0;
        other.m_data = nullptr;
        return *this;
    }

    size_t size() const {
        return m_size;
    }

    template <typename T>
    T *toPointer() {
        static_assert(std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>);

        return static_cast<T *>(m_data);
    }

    template <typename T>
    const T *toPointer() const {
        static_assert(std::is_trivially_copyable_v<T> && std::is_standard_layout_v<T>);

        return static_cast<const T *>(m_data);
    }
};

template <typename T>
class gtlFixedArrayView {
    const gtlRawFixedArray &m_viewedArray;

public:
    gtlFixedArrayView(const gtlRawFixedArray &viewedArray) : m_viewedArray(viewedArray) {
    }

    const T &operator[](size_t index) const {
        return m_viewedArray.toPointer<T>()[index];
    }

    size_t size() const {
        return m_viewedArray.size();
    }

    const T *begin() const {
        return m_viewedArray.toPointer<T>();
    }

    const T *end() const {
        return m_viewedArray.toPointer<T>() + m_viewedArray.size();
    }
};
