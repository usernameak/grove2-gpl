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

#include <gtlMemory/MemAlloc.h>

template <typename T>
T *gnaSingleton() = delete;

template <typename T>
inline T *gnaSingletonLateinitValue = nullptr;

#define GNA_SINGLETON_DECLARE(T) \
    template <>                  \
    T *gnaSingleton<T>()

#define GNA_SINGLETON_EXPORTED_DECLARE(DECLSPEC, T) \
    template <>                                     \
    DECLSPEC T *gnaSingleton<T>()

#define GNA_SINGLETON_IMPLEMENT(T) \
    template <>                    \
    T *gnaSingleton<T>() {         \
        static T inst;             \
        return &inst;              \
    }

#define GNA_SINGLETON_LATEINIT_IMPLEMENT(T)  \
    template <>                              \
    T *gnaSingleton<T>() {                   \
        return gnaSingletonLateinitValue<T>; \
    }

#define GNA_SINGLETON_LATEINIT_INIT(T)       \
    gnaSingletonLateinitValue<T> = gtlNew T; \
    static_assert(true)

#define GNA_SINGLETON_LATEINIT_RELEASE(T)   \
    gtlDelete gnaSingletonLateinitValue<T>; \
    gnaSingletonLateinitValue<T> = nullptr; \
    static_assert(true)
