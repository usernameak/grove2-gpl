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

#include <stdint.h>
#include <gtlUtil/Misc.h>
#include <gtlMemory/MemAlloc.h>

namespace gtl {
    template <typename T>
    class FastRemoveArray {
    public:
        typedef uint32_t SizeType;

        typedef T *Iterator;
        typedef const T *ConstIterator;

    private:
        T *m_data;
        SizeType m_capacity;
        SizeType m_size;

    public:
        FastRemoveArray(SizeType initialCapacity = 1)
            : m_data(gtlNew T[initialCapacity]),
              m_capacity(initialCapacity),
              m_size(0) {
        }

        ~FastRemoveArray() {
            gtlDeleteArray m_data;
        }

        void add(const T &val) {
            allocateSpaceForNewElement();
            m_data[m_size++] = val;
        }

        void add(T &&val) {
            allocateSpaceForNewElement();
            m_data[m_size++] = val;
        }

        T *remove(T *ptr) {
            *ptr = std::move(m_data[--m_size]);
            return ptr;
        }

        T *begin() {
            return m_data;
        }

        const T *begin() const {
            return m_data;
        }

        T *end() {
            return m_data + m_size;
        }

        const T *end() const {
            return m_data + m_size;
        }

    private:
        void allocateSpaceForNewElement() {
            if (m_size >= m_capacity) {
                SizeType newCapacity = m_capacity <= 1 ? m_capacity + 1 : m_capacity * 2;
                changeCapacity(newCapacity);
            }
        }

        void changeCapacity(SizeType newCapacity) {
            auto *newArray = gtlNew T[newCapacity];

            for (SizeType i = 0; i < m_size; i++) {
                newArray[i] = std::move(m_data[i]);
            }

            gtlDeleteArray m_data;

            m_capacity = newCapacity;
            if (m_size > m_capacity) {
                m_size = m_capacity;
            }
            m_data = newArray;
        }
    };
}