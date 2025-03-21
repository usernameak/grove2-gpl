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

package org.aerisdev.bindingtool.desc;

import com.google.common.base.Strings;
import org.w3c.dom.Element;

public class IncludeDescriptor extends BaseDescriptor {
    private String path;

    public String getPath() {
        return path;
    }

    public IncludeDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    @Override
    public void parseFromXML(Element element) throws DescriptorParseException {
        super.parseFromXML(element);

        path = Strings.emptyToNull(element.getAttribute("path"));
    }

    @Override
    public boolean isNamed() {
        return false;
    }
}
