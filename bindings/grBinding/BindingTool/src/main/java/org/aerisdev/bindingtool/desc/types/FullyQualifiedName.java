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

package org.aerisdev.bindingtool.desc.types;

import java.util.Arrays;

public class FullyQualifiedName {
    private final String[] qualifiers;

    public String[] getQualifiers() {
        return qualifiers;
    }

    public FullyQualifiedName(String[] qualifiers) {
        this.qualifiers = qualifiers;
    }

    public FullyQualifiedName(String fullName) {
        this.qualifiers = fullName.split("::");
    }

    @Override
    public String toString() {
        return String.join("::", qualifiers);
    }

    public String toCsName() {
        return "GroveEngine2." + String.join(".", qualifiers);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        FullyQualifiedName that = (FullyQualifiedName) o;
        return Arrays.equals(qualifiers, that.qualifiers);
    }

    @Override
    public int hashCode() {
        return Arrays.hashCode(qualifiers);
    }

    public String getLastName() {
        return qualifiers[qualifiers.length - 1];
    }
}
