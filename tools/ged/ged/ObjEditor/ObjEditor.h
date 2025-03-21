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

#include <gtlUtil/Singleton.h>
#include <grUi/Widget/Widget.h>
#include <gtlMemory/RcObject.h>

namespace ged {
    class Editor;

    class ObjEditor : public gtlRcObject {
    public:
        virtual void populatePropertyGui(
            Editor *editor,
            gnaWeakPointer<gtlObject> obj,
            gnaWeakPointer<grUiWidgetLayout> container);
    };

    class ObjEditorRegistry {
        std::unordered_map<const gtlRTTI *, gnaPointer<ObjEditor>> m_registeredEditors;
    public:
        void registerEditor(const gtlRTTI *rtti, gnaPointer<ObjEditor> factory);

        gnaWeakPointer<ObjEditor> findEditor(const gtlRTTI *rtti);

        void registerDefaultEditors();
    };
}

GNA_SINGLETON_DECLARE(ged::ObjEditorRegistry);
