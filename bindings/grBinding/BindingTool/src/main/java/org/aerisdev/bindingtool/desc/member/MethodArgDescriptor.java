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
import org.w3c.dom.Element;

public class MethodArgDescriptor extends TypedDescriptor {
    private String defaultValue;

    public MethodArgDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public String getDefaultValue() {
        return defaultValue;
    }

    @Override
    public void parseFromXML(Element element) throws DescriptorParseException {
        super.parseFromXML(element);

        if (element.hasAttribute("default")) {
            defaultValue = element.getAttribute("default");
        }
    }
}
