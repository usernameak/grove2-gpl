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
import org.aerisdev.bindingtool.desc.TypedDescriptor;

public class EventSinkDescriptor extends TypedDescriptor {
    public EventSinkDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    @Override
    public String mangleName() {
        StringBuilder sb = new StringBuilder();
        if (parent != null) {
            sb.append(parent.mangleName());
        }
        sb.append('e');
        sb.append(name.length());
        sb.append(name);
        return sb.toString();
    }
}
