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
#include <utility>
#include <type_traits>
#include <climits>
#include <functional>
#include <atomic>
#include <source_location>
#include <gtlMemory/MemAlloc.h>
#include <gtlUtil/Misc.h>
#include <gtlTypeInfo/RTTI.h>

template <typename T>
class gnaPointer;

class GTL_DLLIMPEXP gtlRcObject {
    std::atomic_uint m_refCount;

public:
    GTL_RTTI_DECLARE();

    GTL_FORCEINLINE gtlRcObject() : m_refCount(1) {}

    gtlRcObject(const gtlRcObject &) = delete;
    gtlRcObject(gtlRcObject &&)      = delete;

    gtlRcObject &operator=(const gtlRcObject &) = delete;
    gtlRcObject &operator=(gtlRcObject &&)      = delete;

    GTL_FORCEINLINE virtual ~gtlRcObject() = default;

    GTL_FORCEINLINE unsigned int addRef() noexcept {
        assert(((void)"addRef with zero refcount", m_refCount != 0));
        assert(((void)"refcount overflow", m_refCount != UINT_MAX)); // how the fuck would this break, eh?
        return m_refCount.fetch_add(1, std::memory_order_relaxed) + 1;
    }

    GTL_FORCEINLINE unsigned int release() noexcept {
        unsigned int rc = m_refCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
        if (rc == 0) {
            gtlDelete this;
        }
        return rc;
    }

    /// gets the current reference count.
    /// pretty useful in some caches or whatever. use with care.
    GTL_FORCEINLINE unsigned int get_refCount() const noexcept {
        return m_refCount;
    }
};

#define GTL_RC_OBJECT_IMPL(Superclass) \
    using Superclass::addRef;          \
    using Superclass::release;         \
    using Superclass::get_refCount;

class gtlRcInterface {
    gtlRcObject *const m_self;

public:
    GTL_FORCEINLINE gtlRcInterface(gtlRcObject *self) : m_self(self) {}

    gtlRcInterface(const gtlRcInterface &) = delete;
    gtlRcInterface(gtlRcInterface &&)      = delete;

    gtlRcInterface &operator=(const gtlRcInterface &) = delete;
    gtlRcInterface &operator=(gtlRcInterface &&)      = delete;

    GTL_FORCEINLINE virtual ~gtlRcInterface() = default;

    GTL_FORCEINLINE unsigned int addRef() {
        return m_self->addRef();
    }

    GTL_FORCEINLINE unsigned int release() {
        return m_self->release();
    }

    /// gets the current reference count.
    /// pretty useful in some caches or whatever. use with care.
    GTL_FORCEINLINE unsigned int get_refCount() const {
        return m_self->get_refCount();
    }
};

template <typename T>
class gnaWeakPointer;

template <typename T>
class gnaPointer {
    template <typename U>
    friend class gnaPointer;
    template <typename U>
    friend class gnaWeakPointer;
    template <typename U, typename V>
    friend bool operator==(const gnaPointer<U> &a, const gnaWeakPointer<V> &b);
    template <typename U, typename V>
    friend bool operator==(const gnaWeakPointer<U> &a, const gnaPointer<V> &b);

    T *m_ptr;

public:
    GTL_FORCEINLINE gnaPointer() noexcept : m_ptr(nullptr) {}

    // GTL_FORCEINLINE gnaPointer(nullptr_t obj) noexcept : m_ptr(nullptr) {}

    GTL_FORCEINLINE gnaPointer(T *obj) noexcept : m_ptr(obj) {}

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaPointer(const gnaWeakPointer<U> &other) noexcept : m_ptr(other.m_ptr) {
        if (m_ptr) {
            m_ptr->addRef();
        }
    }

    GTL_FORCEINLINE gnaPointer(const gnaPointer &other) noexcept : m_ptr(other.m_ptr) {
        if (m_ptr) {
            m_ptr->addRef();
        }
    }

    GTL_FORCEINLINE gnaPointer(gnaPointer &&other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaPointer(const gnaPointer<U> &other) noexcept : m_ptr(static_cast<T *>(other.m_ptr)) {
        if (m_ptr) {
            m_ptr->addRef();
        }
    }

    // template sorcery. nice try c++11!
    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaPointer(gnaPointer<U> &&other) noexcept : m_ptr(static_cast<T *>(other.m_ptr)) {
        other.m_ptr = nullptr;
    }

    GTL_FORCEINLINE T &operator*() const {
        return *m_ptr;
    }

    GTL_FORCEINLINE T *operator->() const {
        return m_ptr;
    }

    template <typename MFP>
    GTL_FORCEINLINE auto &operator->*(MFP T::*mfp) const {
        return m_ptr->*mfp;
    }

    GTL_FORCEINLINE gnaPointer &operator=(T *obj) {
        if (m_ptr) {
            m_ptr->release();
        }
        m_ptr = obj;

        return *this;
    }

    GTL_FORCEINLINE gnaPointer &operator=(const gnaPointer &other) {
        // this exact order for the case other.m_ptr == m_ptr
        if (other.m_ptr) {
            other.m_ptr->addRef();
        }
        if (m_ptr) {
            m_ptr->release();
        }
        m_ptr = other.m_ptr;

        return *this;
    }

    GTL_FORCEINLINE gnaPointer &operator=(gnaPointer &&other) noexcept {
        if (this == &other)
            return *this;

        if (m_ptr) {
            m_ptr->release();
        }
        m_ptr       = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaPointer &operator=(const gnaPointer<U> &other) {
        // this exact order for the case other.m_ptr == m_ptr
        if (other.m_ptr) {
            other.m_ptr->addRef();
        }
        if (m_ptr) {
            m_ptr->release();
        }
        m_ptr = other.m_ptr;

        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaPointer &operator=(gnaPointer<U> &&other) {
        if (m_ptr) {
            m_ptr->release();
        }
        m_ptr       = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    GTL_FORCEINLINE bool operator==(const gnaPointer &other) const {
        return other.m_ptr == this->m_ptr;
    }

    GTL_FORCEINLINE bool operator!=(const gnaPointer &other) const {
        return !operator==(other);
    }

    template <typename U>
    GTL_FORCEINLINE bool operator==(const U *other) const {
        return other == this->m_ptr;
    }

    template <typename U>
    GTL_FORCEINLINE bool operator!=(const U *other) const {
        return !operator==(other);
    }

    template <typename U>
    GTL_FORCEINLINE bool operator==(const gnaPointer<U> &other) const {
        return other == this->m_ptr;
    }

    template <typename U>
    GTL_FORCEINLINE bool operator!=(const gnaPointer<U> &other) const {
        return !operator==(other);
    }

    GTL_FORCEINLINE explicit operator bool() const {
        return m_ptr != nullptr;
    }

    GTL_FORCEINLINE ~gnaPointer() {
        if (m_ptr) {
            m_ptr->release();
        }
    }

    GTL_FORCEINLINE bool hasValue() const {
        return this->operator bool();
    }

    template <typename V>
    GTL_FORCEINLINE gnaWeakPointer<V> rttiCast2() const {
        return gtlRttiCast<V *>(m_ptr);
    }

    template <typename V>
    GTL_FORCEINLINE gnaWeakPointer<V> cast() const {
        return static_cast<V *>(m_ptr);
    }
};

template <typename T, typename U>
GTL_FORCEINLINE bool operator==(const T *a, const gnaPointer<U> b) {
    return b == a;
}

template <typename T>
class [[jetbrains::pass_by_value]] gnaWeakPointer {
    template <typename U>
    friend class gnaPointer;
    template <typename U>
    friend class gnaWeakPointer;
    template <typename U, typename V>
    friend bool ::operator==(const gnaPointer<U> &a, const gnaWeakPointer<V> &b);
    template <typename U, typename V>
    friend bool ::operator==(const gnaWeakPointer<U> &a, const gnaPointer<V> &b);

    T *m_ptr;

public:
    GTL_FORCEINLINE gnaWeakPointer() noexcept : m_ptr(nullptr) {}

    GTL_FORCEINLINE gnaWeakPointer(nullptr_t) noexcept : m_ptr(nullptr) {}

    GTL_FORCEINLINE gnaWeakPointer(T *obj) noexcept : m_ptr(obj) {}

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaWeakPointer(const gnaPointer<U> &other) noexcept : m_ptr(other.m_ptr) {}

    template <typename U>
    GTL_FORCEINLINE gnaWeakPointer(gnaPointer<U> &&) noexcept = delete;

    GTL_FORCEINLINE gnaWeakPointer(const gnaWeakPointer<T> &other) noexcept : m_ptr(other.m_ptr) {}

    GTL_FORCEINLINE gnaWeakPointer(gnaWeakPointer<T> &&other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaWeakPointer(const gnaWeakPointer<U> &other) noexcept : m_ptr(static_cast<T *>(other.m_ptr)) {}

    // template sorcery. nice try c++11!
    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE gnaWeakPointer(gnaWeakPointer<U> &&other) noexcept : m_ptr(static_cast<T *>(other.m_ptr)) {
        other.m_ptr = nullptr;
    }

    GTL_FORCEINLINE T &operator*() const {
        return *m_ptr;
    }

    GTL_FORCEINLINE T *operator->() const {
        return m_ptr;
    }

    template <typename MFP>
    GTL_FORCEINLINE auto &operator->*(MFP T::*mfp) const {
        return m_ptr->*mfp;
    }

    GTL_FORCEINLINE T *operator=(T *obj) {
        m_ptr = obj;
        return obj;
    }

    GTL_FORCEINLINE const gnaWeakPointer &operator=(const gnaWeakPointer &other) {
        m_ptr = other.m_ptr;

        return *this;
    }

    GTL_FORCEINLINE const gnaWeakPointer &operator=(gnaWeakPointer &&other) {
        if (this == &other)
            return *this;

        m_ptr       = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE const gnaWeakPointer &operator=(const gnaWeakPointer<U> &other) {
        m_ptr = other.m_ptr;

        return *this;
    }

    template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
    GTL_FORCEINLINE const gnaWeakPointer &operator=(gnaWeakPointer<U> &&other) {
        m_ptr       = other.m_ptr;
        other.m_ptr = nullptr;

        return *this;
    }

    GTL_FORCEINLINE bool operator==(const gnaWeakPointer &other) const {
        return other.m_ptr == this->m_ptr;
    }

    GTL_FORCEINLINE bool operator!=(const gnaWeakPointer &other) const {
        return !operator==(other);
    }

    template <typename U>
    GTL_FORCEINLINE bool operator==(const U *other) const {
        return other == this->m_ptr;
    }

    template <typename U>
    GTL_FORCEINLINE bool operator!=(const U *other) const {
        return !operator==(other);
    }

    GTL_FORCEINLINE explicit operator bool() const {
        return m_ptr != nullptr;
    }

    GTL_FORCEINLINE ~gnaWeakPointer() {
    }

    GTL_FORCEINLINE bool hasValue() {
        return this->operator bool();
    }

    template <typename V>
    GTL_FORCEINLINE gnaWeakPointer<V> rttiCast2() const {
        return gtlRttiCast<V *>(m_ptr);
    }

    template <typename V>
    GTL_FORCEINLINE gnaWeakPointer<V> cast() const {
        return static_cast<V *>(m_ptr);
    }
};

template <typename T, typename U>
GTL_FORCEINLINE bool operator==(const T *a, const gnaWeakPointer<U> b) {
    return b == a;
}

template <typename T, typename U>
GTL_FORCEINLINE bool operator==(const gnaPointer<T> &a, const gnaWeakPointer<U> &b) {
    return a.m_ptr == b.m_ptr;
}

template <typename T, typename U>
GTL_FORCEINLINE bool operator==(const gnaWeakPointer<T> &a, const gnaPointer<U> &b) {
    return a.m_ptr == b.m_ptr;
}

#ifdef _DEBUG

struct gnaNewWithSourceLocImpl {
    const std::source_location &loc;

    constexpr explicit gnaNewWithSourceLocImpl(const std::source_location &loc) : loc(loc) {}

    template <typename T, typename... Args>
    GTL_FORCEINLINE gnaPointer<T> operator()(Args &&...args) noexcept
        requires std::constructible_from<T, Args...> // used as a hint for IDE
    {
        auto *ptr = gtlNewWithFileLineNothrow(loc.file_name(), loc.line()) T(std::forward<Args>(args)...);
        return gnaPointer<std::remove_reference_t<decltype(*ptr)>>(ptr);
    }

    template <template <typename...> typename T, typename... Args>
    GTL_FORCEINLINE auto operator()(Args &&...args) noexcept {
        auto *ptr = gtlNewWithFileLineNothrow(loc.file_name(), loc.line()) T(std::forward<Args>(args)...);
        return gnaPointer<std::remove_reference_t<decltype(*ptr)>>(ptr);
    }
};

GTL_FORCEINLINE constexpr auto gnaNewWithSourceLocation(const std::source_location &loc = std::source_location::current()) noexcept {
    return gnaNewWithSourceLocImpl(loc);
}

#define gnaNew gnaNewWithSourceLocation().template operator()

#else

template <template <typename...> typename T, typename... Args>
GTL_FORCEINLINE auto gnaNew(Args &&...args) noexcept {
    auto *ptr = gtlNewNothrow T(std::forward<Args>(args)...);
    return gnaPointer<std::remove_reference_t<decltype(*ptr)>>(ptr);
}

template <typename T, typename... Args>
GTL_FORCEINLINE gnaPointer<T> gnaNew(Args &&...args) noexcept {
    return gnaPointer<T>(gtlNewNothrow T(std::forward<Args>(args)...));
}

#endif

namespace std {
    template <typename T>
    struct hash<gnaPointer<T>> {
        GTL_FORCEINLINE auto operator()(const gnaPointer<T> &p) const {
            return hash<T *>{}(&*p);
        }
    };
}

namespace std {
    template <typename T>
    struct hash<gnaWeakPointer<T>> {
        GTL_FORCEINLINE auto operator()(const gnaWeakPointer<T> &p) const {
            return hash<T *>{}(&*p);
        }
    };
}
