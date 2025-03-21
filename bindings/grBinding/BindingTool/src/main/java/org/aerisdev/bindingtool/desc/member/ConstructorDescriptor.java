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

public class ConstructorDescriptor extends MethodDescriptor {
    public ConstructorDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    @Override
    public boolean isNamed() {
        return false;
    }

    @Override
    public String mangleNameWithBase(BaseDescriptor base) {
        StringBuilder sb = new StringBuilder();
        if (base != null) {
            sb.append(base.mangleName());
        }
        sb.append("n0");
        sb.append('_');
        sb.append(getArguments().size());
        for (MethodArgDescriptor arg : getArguments()) {
            sb.append(arg.mangleType());
        }
        return sb.toString();
    }
}
