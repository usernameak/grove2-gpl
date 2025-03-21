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

#include "StringPool.h"

template <typename CharType>
    requires std::integral<CharType>
constinit typename gtl::StringPool<CharType>::StringPoolEntry gtl::StringPool<CharType>::EMPTY_STR = {
    0,
    1,

    // for consistency, make sure this hash is *actually* equal to
    // an empty string's hash. with the current hash function ~ it is.
    0,

    { 0 }
};

template <typename CharType>
    requires std::integral<CharType>
gtl::FastRemoveArray<typename gtl::StringPool<CharType>::StringPoolEntry *>
    gtl::StringPool<CharType>::m_buckets[NUM_BUCKETS];

template <typename CharType>
    requires std::integral<CharType>
std::mutex gtl::StringPool<CharType>::m_bucketMutexes[NUM_BUCKETS];

template class GTL_DLLIMPEXP gtl::StringPool<gtl::ASCIICHAR>;
template class GTL_DLLIMPEXP gtl::StringPool<gtl::WIDECHAR>;
