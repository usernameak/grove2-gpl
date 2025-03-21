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

#include <cstddef>
#include <type_traits>
#include <gtlUtil/Misc.h>
#include <gtlMemory/MemAlloc.h>

namespace gtlMemory {
    class GTL_DLLIMPEXP AllocationArena {
        enum : size_t {
            alignmentAmount = alignof(std::max_align_t)
        };

        void *m_data;
        size_t m_size;
        size_t m_allocationOffset;

        constexpr static size_t alignedSize(size_t size) {
            size_t paddingSize = size - size % alignmentAmount;
            if (paddingSize == alignmentAmount) {
                paddingSize = 0;
            }
            return size + paddingSize;
        }

        struct alignas(alignmentAmount) AllocatedEntry {
            size_t size;
            void (*destroy)(const void *);
            AllocatedEntry *next;

            void *get_data() {
                return this + 1;
            }
        } * firstAllocatedEntry, *lastAllocatedEntry;

        AllocatedEntry *allocateNewEntry(size_t size);

    public:
        AllocationArena(size_t size);

        AllocationArena(const AllocationArena &) = delete;
        AllocationArena(AllocationArena &&) = delete;
        AllocationArena &operator=(const AllocationArena &) = delete;
        AllocationArena &operator=(AllocationArena &&) = delete;

        template <typename T, typename... Args>
        T *allocate(Args... args) {
            AllocatedEntry *entry = allocateNewEntry(sizeof(T));
            if (!entry) {
                return nullptr;
            }
            if (lastAllocatedEntry) {
                lastAllocatedEntry->next = entry;
            }
            lastAllocatedEntry = entry;
            if (!firstAllocatedEntry) {
                firstAllocatedEntry = entry;
            }

            void *ptr = entry->get_data();

            new (ptr) T(std::forward<Args>(args)...);
            if constexpr (!std::is_trivially_destructible_v<T>) {
                entry->destroy = [](const void *ptr) { static_cast<const T *>(ptr)->~T(); };
            }

            return static_cast<T *>(ptr);
        }

        ~AllocationArena();
    };
}
