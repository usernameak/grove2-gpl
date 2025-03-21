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

#include <gtlCollections/FixedArray.h>
#include <gtlMemory/RcObject.h>
#include <gtlString/PooledString.h>
#include <gtlModule/ModuleLoader.h>
#include <gtlUtil/Singleton.h>

#define GR_BINDING_THUNK_EXPORT __declspec(dllexport)
#define GR_BINDING_THUNK_CALLCONV __stdcall
#define GR_BINDING_DELEGATE_CALLCONV __stdcall
#ifdef _WIN32
#if defined(GR_BINDING_BUILD_DLL)
#define GR_BINDING_DLLIMPEXP __declspec(dllexport)
#elif defined(GR_BINDING_LOAD_DLL)
#define GR_BINDING_DLLIMPEXP __declspec(dllimport)
#else
#define GR_BINDING_DLLIMPEXP
#endif
#else
#define GR_BINDING_DLLIMPEXP
#endif


template <typename T>
gnaWeakPointer<T> grBindingExpandWeakPtr(void *p) {
    return static_cast<T *>(p);
}

inline const char *grBindingAllocateString(const gtl::PooledAString &str) {
    auto *pstr = gtlNew char[str.size() + 1];
    memcpy(pstr, str.toCString(), str.size() + 1);
    return pstr;
}

inline const gtl::WIDECHAR *grBindingAllocateWString(const gtl::String &str) {
    auto *pstr = gtlNew gtl::WIDECHAR[str.size() + 1];
    memcpy(pstr, str.toCString(), sizeof(gtl::WIDECHAR) * (str.size() + 1));
    return pstr;
}

typedef void(GR_BINDING_DELEGATE_CALLCONV *grBindingReleaseGchType)(void *delegateGCHandle);
GR_BINDING_DLLIMPEXP extern grBindingReleaseGchType grBindingGlobal_releaseGch;

class GR_BINDING_DLLIMPEXP grBindingGCHandleHolder : public gtlRcObject {
    void *m_gch;

public:
    GTL_RTTI_DECLARE();

    explicit grBindingGCHandleHolder(void *gch);

    ~grBindingGCHandleHolder() override;
};

template <typename T>
struct grBindingHandlerWrapper {
    bool(__stdcall *callback)(T &event);
    gnaPointer<grBindingGCHandleHolder> m_gch;

    grBindingHandlerWrapper(bool (*callback)(T &event), void *gch)
        : callback(callback),
          m_gch(gnaNew<grBindingGCHandleHolder>(gch)) {}

    bool operator()(T &event) {
        return callback(event);
    }
};

struct grBindingProxyInfo {
    void *gch;
};

template <typename T>
struct grBindingTypeUtils {
    static T translateArgFromNativeToManaged(T val) {
        return val;
    }

    static T translateReturnFromManagedToNative(T val) {
        return val;
    }

    static T translateReturnFromManagedToNative(void *val) {
        return *static_cast<T *>(val);
    }
};

template <typename T>
struct grBindingTypeUtils<const T &> {
    static const T &translateReturnFromManagedToNative(const T &val) {
        return val;
    }

    static const T &translateArgFromNativeToManaged(const T &val) {
        return val;
    }

    static void *translateArgFromNativeToManagedCls(const T &val) {
        return const_cast<void *>(static_cast<const void *>(&val));
    }

    static const T &translateReturnFromManagedToNative(void *val) {
        return *static_cast<T *>(val);
    }
};

template <typename T>
struct grBindingTypeUtils<T *> {
    static void *translateArgFromNativeToManaged(T *val) {
        return val;
    }

    static void *translateArgFromNativeToManagedCls(T *val) {
        return val;
    }

    static T *translateReturnFromManagedToNative(void *val) {
        return static_cast<T *>(val);
    }
};

template <typename T>
    requires(std::is_enum_v<T>)
struct grBindingTypeUtils<T> {
    static std::underlying_type_t<T> translateArgFromNativeToManaged(T val) {
        return static_cast<std::underlying_type_t<T>>(val);
    }

    static T translateReturnFromManagedToNative(std::underlying_type_t<T> val) {
        return static_cast<T>(val);
    }
};

template <typename T>
struct grBindingTypeUtils<gnaWeakPointer<T>> {
    static void *translateArgFromNativeToManagedCls(gnaWeakPointer<T> val) {
        if (val) {
            val->addRef();
            return &*val;
        } else {
            return nullptr;
        }
    }

    static gnaWeakPointer<T> translateReturnFromManagedToNative(void *val) {
        return static_cast<T *>(val);
    }
};

template <typename T>
struct grBindingTypeUtils<gnaPointer<T>> {
    static void *translateArgFromNativeToManagedCls(gnaWeakPointer<T> val) {
        if (val) {
            val->addRef();
            return &*val;
        } else {
            return nullptr;
        }
    }

    static gnaWeakPointer<T> translateReturnFromManagedToNative(void *val) {
        return static_cast<T *>(val);
    }
};

template <>
struct grBindingTypeUtils<gtl::PooledAString> {
    static const gtl::ASCIICHAR *translateArgFromNativeToManaged(const gtl::PooledAString &val) {
        return val.toCString();
    }

    static gtl::PooledAString translateReturnFromManagedToNative(const gtl::ASCIICHAR *val) {
        gtl::PooledAString str = val;
        gtlDeleteArray val;
        return str;
    }
};

template <>
struct grBindingTypeUtils<gtl::String> {
    static const gtl::WIDECHAR *translateArgFromNativeToManaged(const gtl::String &val) {
        return val.toCString();
    }

    static gtl::String translateReturnFromManagedToNative(const gtl::WIDECHAR *val) {
        gtl::String str = val;
        gtlDeleteArray val;
        return str;
    }
};

template <>
struct grBindingTypeUtils<gtl::PooledString> {
    static const gtl::WIDECHAR *translateArgFromNativeToManaged(const gtl::PooledString &val) {
        return val.toCString();
    }

    static gtl::PooledString translateReturnFromManagedToNative(const gtl::WIDECHAR *val) {
        gtl::PooledString str = val;
        gtlDeleteArray val;
        return str;
    }
};

template <>
struct grBindingTypeUtils<const gtl::String &> : grBindingTypeUtils<gtl::String> {};

template <>
struct grBindingTypeUtils<const gtl::PooledAString &> : grBindingTypeUtils<gtl::PooledAString> {};

template <>
struct grBindingTypeUtils<const gtl::PooledString &> : grBindingTypeUtils<gtl::PooledString> {};

struct grBindingArray {
    size_t size;
    size_t elementSize;
    void *array;

    gtlRawFixedArray toFixedArray() {
        gtlRawFixedArray arr = gtlRawFixedArray::createUnsafe(size, elementSize, array);
        return std::move(arr);
    }
};
