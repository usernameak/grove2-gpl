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

#include <unordered_set>
#include "CString.h"
#include <cstdint>
// ReSharper disable once CppUnusedIncludeDirective
#include <gtlUtil/Misc.h>
#include <gtlCollections/FastRemoveArray.h>
#include <gtlMemory/MemAlloc.h>
#include <cassert>
#include <atomic>
#include <mutex>
#include <concepts>

namespace gtl {
    template <typename CharType>
        requires std::integral<CharType>
    class StringPool {
        struct StringPoolEntry {
            uint32_t length;
            std::atomic_uint32_t refcount;
            size_t hash;
            CharType strdata[1];
        };

        static constinit StringPoolEntry EMPTY_STR;

        static constexpr size_t NUM_BUCKETS = 523;

        static FastRemoveArray<StringPoolEntry *> m_buckets[NUM_BUCKETS];
        static std::mutex m_bucketMutexes[NUM_BUCKETS];

        typedef std::size_t Hash;

    public:
        typedef StringPoolEntry *Handle;

        constexpr static Handle acquireEmptyString() noexcept {
            return &EMPTY_STR;
        }

        static Handle acquireString(const CharType *str) {
            return acquireString(str, StrLen(str));
        }

        static Handle acquireString(const CharType *str, uint32_t length) {
            // we will not manage refcount of the constant empty string
            if (length == 0) {
                return &EMPTY_STR;
            }

            Handle handle = findString(str, length);
            if (handle) {
                handle->refcount.fetch_add(1, std::memory_order_acq_rel);

                return handle;
            }

            handle           = (Handle)gtlMalloc(offsetof(StringPoolEntry, strdata) + sizeof(CharType) * (length + 1));
            handle->length   = length;
            handle->refcount = 1;
            handle->hash     = hashString(str, length);

            memcpy(handle->strdata, str, length * sizeof(CharType));
            handle->strdata[length] = 0;

            size_t bucketIndex = handle->hash % NUM_BUCKETS;
            std::lock_guard lock(m_bucketMutexes[bucketIndex]);
            m_buckets[bucketIndex].add(handle);

            return handle;
        }

        static Handle acquireString(Handle handle) {
            // we will not manage refcount of the constant empty string
            if (handle == &EMPTY_STR) return handle;
            assert(handle->length != 0);

            handle->refcount.fetch_add(1, std::memory_order_acq_rel);

            return handle;
        }

        static void releaseString(Handle handle) {
            // we will not manage refcount of the constant empty string
            if (handle == &EMPTY_STR) return;
            assert(handle->length != 0);

            if (handle->refcount.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                size_t bucketIndex = handle->hash % NUM_BUCKETS;

                std::lock_guard lock(m_bucketMutexes[bucketIndex]);

                auto &bucket = m_buckets[handle->hash % NUM_BUCKETS];
                auto it      = std::find(bucket.begin(), bucket.end(), handle);
                assert(it != bucket.end());

                bucket.remove(it);

                gtlFree(handle);
            }
        }

        static size_t getLength(Handle handle) {
            return handle->length;
        }

        static size_t getHash(Handle handle) {
            return handle->hash;
        }

        static const CharType *getStringPtr(Handle handle) {
            return handle->strdata;
        }

    private:
        static Handle findString(const CharType *str, size_t length) {
            auto hash          = hashString(str, length);
            size_t bucketIndex = hash % NUM_BUCKETS;
            std::lock_guard lock(m_bucketMutexes[bucketIndex]);
            for (auto &bucket = m_buckets[bucketIndex]; Handle handle : bucket) {
                if (handle->length != length) continue;

                if (memcmp(handle->strdata, str, length * sizeof(CharType)) == 0) return handle;
            }

            return nullptr;
        }

        static Hash hashString(const CharType *str, size_t length) {
            Hash h = 0;
            for (size_t i = 0; i < length; i++) {
                h = 31 * h + str[i];
            }
            return h;
        }
    };

#ifdef GTL_LOAD_DLL
    extern template class GTL_DLLIMPEXP StringPool<ASCIICHAR>;
    extern template class GTL_DLLIMPEXP StringPool<WIDECHAR>;
#else
    extern template class StringPool<ASCIICHAR>;
    extern template class StringPool<WIDECHAR>;
#endif

}
