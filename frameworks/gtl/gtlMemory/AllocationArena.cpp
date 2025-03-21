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

#include "AllocationArena.h"

#include "MemAlloc.h"

using namespace gtlMemory;

AllocationArena::AllocationArena(size_t size)
    : m_size(size),
      m_allocationOffset(0),
      firstAllocatedEntry(nullptr),
      lastAllocatedEntry(nullptr) {
    m_data = gtlMalloc(size);
}

AllocationArena::AllocatedEntry *AllocationArena::allocateNewEntry(size_t size) {
    size_t totalRequiredSize = sizeof(AllocatedEntry) + alignedSize(size);

    if (totalRequiredSize > m_size - m_allocationOffset) {
        return nullptr;
    }

    auto *entry = reinterpret_cast<AllocatedEntry *>(static_cast<unsigned char *>(m_data) + m_allocationOffset);
    m_allocationOffset += totalRequiredSize;

    entry->size    = size;
    entry->destroy = nullptr;
    entry->next = nullptr;

    return entry;
}

AllocationArena::~AllocationArena() {
    AllocatedEntry *entry = firstAllocatedEntry;
    while (entry) {
        if (entry->destroy) {
            entry->destroy(entry->get_data());
        }
        entry = entry->next;
    }

    gtlFree(m_data);
}
