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

import org.aerisdev.bindingtool.desc.TypedDescriptor;

import java.util.ArrayList;
import java.util.List;

public class MethodComparisonInfo {
    public final String name;
    public final List<MethodArgDescriptor> args = new ArrayList<>();

    public MethodComparisonInfo(String name, TypedDescriptor returnType, List<MethodArgDescriptor> args) {
        this.name = name;
        this.args.addAll(args);
    }

    public MethodComparisonInfo(MethodDescriptor desc) {
        this.name = desc.getName();
        this.args.addAll(desc.getArguments());
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        MethodComparisonInfo that = (MethodComparisonInfo) o;

        if (!name.equals(that.name)) return false;

        if (args.size() != that.args.size()) return false;
        for (int i = 0; i < args.size(); i++) {
            MethodArgDescriptor arg = args.get(i);
            if (!arg.isSameType(that.args.get(i))) {
                return false;
            }
        }
        return true;
    }

    private static int hashCombine(int seed, int v) {
        seed ^= v + 0x9e3779b9 + (seed << 6) + (seed >>> 2);
        return seed;
    }

    @Override
    public int hashCode() {
        int nameHash = name.hashCode();
        int[] argsHash = args.stream().mapToInt(TypedDescriptor::typeHash).toArray();

        int hash = nameHash;
        for (int argHash : argsHash) {
            hash = hashCombine(hash, argHash);
        }
        return hash;
    }
}
