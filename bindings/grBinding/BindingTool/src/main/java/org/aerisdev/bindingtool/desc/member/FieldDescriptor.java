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

package org.aerisdev.bindingtool.desc.member;

import org.aerisdev.bindingtool.desc.BaseDescriptor;
import org.aerisdev.bindingtool.desc.DescriptorParseException;
import org.aerisdev.bindingtool.desc.TypedDescriptor;
import org.aerisdev.bindingtool.desc.types.AccessMode;
import org.w3c.dom.Element;

public class FieldDescriptor extends TypedDescriptor {
    private boolean isConst = false;

    public boolean isConst() {
        return isConst;
    }
    public FieldDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    @Override
    public void parseFromXML(Element element) throws DescriptorParseException {
        super.parseFromXML(element);

        if ("true".equals(element.getAttribute("const"))) {
            isConst = true;
        }
    }

    @Override
    public String mangleName() {
        return mangleNameWithBase(parent);
    }

    public String mangleNameWithBase(BaseDescriptor base) {
        StringBuilder sb = new StringBuilder();
        if (base != null) {
            sb.append(base.mangleName());
        }
        sb.append('f');
        sb.append(name.length());
        sb.append(name);
        return sb.toString();
    }
}
