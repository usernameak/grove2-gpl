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

#include <gtlMemory/RcObject.h>
#include <gtlTypeInfo/RTTI.h>

class gtlCloneContext;

class GTL_DLLIMPEXP gtlCloneable : public gtlRcObject {
protected:
    virtual gnaPointer<gtlCloneable> constructCloneObject(gtlCloneContext &cctx) const {
        return nullptr;
    }

    virtual void cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const {}
    virtual void postClone() {}

public:
    gnaPointer<gtlCloneable> clone() const;

    gnaPointer<gtlCloneable> clone(gtlCloneContext &cctx) const;

    GTL_RTTI_DECLARE();
};

// ---- //
#define GTL_DECLARE_SIMPLE_OBJECT_CLONE                                                            \
protected:                                                                                         \
    virtual gnaPointer<gtlCloneable> constructCloneObject(gtlCloneContext &cctx) const override {  \
        using ThisType               = std::remove_cv_t<std::remove_reference_t<decltype(*this)>>; \
        gnaPointer<gtlCloneable> ptr = gnaNew<ThisType>();                                         \
        return ptr;                                                                                \
    }                                                                                              \
                                                                                                   \
public:
// ---- //

// ---- //
#define GTL_DECLARE_ABSTRACT_OBJECT_CLONE \
public:                                   \
    virtual void cloneMembers(gnaWeakPointer<gtlCloneable> dest, gtlCloneContext &cctx) const override
// ---- //

// ---- //
#define GTL_DECLARE_OBJECT_CLONE     \
    GTL_DECLARE_SIMPLE_OBJECT_CLONE; \
    GTL_DECLARE_ABSTRACT_OBJECT_CLONE
// ---- //

#define GTL_DEFINE_OBJECT_CLONE(cls) static_assert(true, "")

// ---- //

class GTL_DLLIMPEXP gtlCloneContext {
    std::unordered_map<gnaPointer<gtlCloneable>, gnaPointer<gtlCloneable>> m_objectMap;

public:
    template<typename T = gtlCloneable>
    gnaWeakPointer<T> getOrCloneObject(gnaWeakPointer<T> obj) {
        if (!obj) return nullptr;

        auto &clonedObj = m_objectMap[obj];
        if (!clonedObj) {
            clonedObj = obj->clone(*this);
        }
        return clonedObj.template cast<T>();
    }
};
