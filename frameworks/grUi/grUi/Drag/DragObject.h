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
#include <nxfResource/RID.h>
#include <grUi/UiDLL.h>

class GR_UI_DLLIMPEXP grUiDragObject : public gtlRcObject {
public:
    GTL_RTTI_DECLARE();

    enum Type {
        TYPE_NONE    = 0,
        TYPE_SPECIAL = 1
    };

    virtual Type get_type() const = 0;
};

class grUiEmptyDragObject : public grUiDragObject {
public:
    GTL_RTTI_DECLARE();

    Type get_type() const override { return TYPE_NONE; }
};

class GR_UI_DLLIMPEXP grUiResourceIDDragObject : public grUiDragObject {
public:
    GTL_RTTI_DECLARE();

    const nxfRID m_rid;

    grUiResourceIDDragObject(nxfRID rid) : m_rid(rid) {}

    Type get_type() const override { return TYPE_SPECIAL; }
};
