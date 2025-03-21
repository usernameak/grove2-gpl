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

#include <gtlUtil/Misc.h>
#include <gnaStatus.h>
#include <nxfSerialization/SerializationMacros.h>
#include "Cloneable.h"

class gtlObject;

class GTL_DLLIMPEXP gtlProperty {
    typedef const void *GetterType(gnaWeakPointer<gtlObject> object);
    typedef void SetterType(gnaWeakPointer<gtlObject> object, const void *value);

public:
    const char *const m_name;

    const gtlTypeInfo * const m_typeInfo;

private:
    GetterType *m_getter;
    SetterType *m_setter;

    explicit constexpr gtlProperty(
        const char *name,
        GetterType *getter,
        SetterType *setter,
        const gtlTypeInfo *typeInfo
    ) : m_name(name),
        m_typeInfo(typeInfo),
        m_getter(getter),
        m_setter(setter) {}

public:
    template <typename ObjectType, typename T, T ObjectType::*ValuePtr>
    static constexpr gtlProperty create(const char *name) {
        return gtlProperty(
            name,
            [](gnaWeakPointer<gtlObject> object) -> const void * {
                return &(object.cast<ObjectType>()->*ValuePtr);
            },
            [](gnaWeakPointer<gtlObject> object, const void *value) {
                object.cast<ObjectType>()->*ValuePtr = *(const T *)value;
            },
            gtlTypeInfo::of<T>()
        );
    }

    template <typename T>
    const T &get(gnaWeakPointer<gtlObject> object) const {
        return *static_cast<const T *>(m_getter(object));
    }

    template <typename T>
    void set(gnaWeakPointer<gtlObject> object, const T &value) const {
        m_setter(object, &value);
    }

    static const gtlProperty *findProperty(gnaWeakPointer<gtlObject> object, const char *name);

    template <typename F>
    static void enumerateProperties(gnaWeakPointer<gtlObject> object, F func);
};

class gtlPropertyTable {
    const gtlProperty *m_propertyTablePtr;
    size_t m_size;

public:
    template <int size>
    explicit constexpr gtlPropertyTable(
        const gtlProperty (&propertyTablePtr)[size],
        const gtlPropertyTable *basePropertyTable = nullptr
    ) : gtlPropertyTable(propertyTablePtr, size, basePropertyTable) {}

    explicit constexpr gtlPropertyTable(
        const gtlProperty *propertyTablePtr,
        size_t size,
        const gtlPropertyTable *basePropertyTable = nullptr
    ) : m_propertyTablePtr(propertyTablePtr),
        m_size(size) {}

    size_t get_propertyCount() const {
        return m_size;
    }

    const gtlProperty &getProperty(size_t index) const {
        assert(index < m_size);
        return m_propertyTablePtr[index];
    }
};

// the property table was supposed to be constinit, but due to
// limitations of the DLL mechanism on Windows, taking a pointer
// to a global variable in another DLL is not a constant expression,
// so making it constinit is not possible

#define GTL_OBJECT_PROPERTY_TABLE_DECLARE()             \
private:                                                \
    static const gtlProperty st_propertyTableContent[]; \
                                                        \
protected:                                              \
    static const gtlPropertyTable st_propertyTable;     \
                                                        \
public:                                                 \
    virtual const gtlPropertyTable *get_propertyTable(int baseIndex) const;


#define GTL_OBJECT_PROPERTY_TABLE_DEFINE(Class, BaseClass, ...)             \
    const gtlProperty Class::st_propertyTableContent[] = {                  \
        __VA_ARGS__                                                         \
    };                                                                      \
                                                                            \
    const gtlPropertyTable Class::st_propertyTable{                         \
        st_propertyTableContent                                             \
    };                                                                      \
                                                                            \
    const gtlPropertyTable *Class::get_propertyTable(int baseIndex) const { \
        if (baseIndex > 0) {                                                \
            return BaseClass::get_propertyTable(baseIndex - 1);             \
        }                                                                   \
        return &st_propertyTable;                                           \
    }


class GTL_DLLIMPEXP gtlObject : public gtlCloneable {
public:
    GTL_RTTI_DECLARE();
    NXF_SERIALIZABLE_DECLARE();
    GTL_OBJECT_PROPERTY_TABLE_DECLARE();

    template <nxfSerialization::SerializationInterface TSerializationInterface>
    gnaStatus serializationImpl(TSerializationInterface &proxy);

    virtual void postDeserialize() {}
};

template <typename F>
void gtlProperty::enumerateProperties(gnaWeakPointer<gtlObject> object, F func) {
    for (int i = 0;; i++) {
        auto *table = object->get_propertyTable(i);
        if (!table) break;

        size_t count = table->get_propertyCount();
        for (int j = 0; j < count; j++) {
            auto &property = table->getProperty(j);
            func(property);
        }
    }
}
