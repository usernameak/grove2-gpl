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

package org.aerisdev.bindingtool.desc.compound;

import com.google.common.base.Strings;
import org.aerisdev.bindingtool.desc.BaseDescriptor;
import org.aerisdev.bindingtool.desc.DescriptorParseException;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.w3c.dom.Element;

public class ClassDescriptor extends CompoundTypeDescriptor {
    private boolean isVirtual = false;
    private boolean isAbstract = false;
    private boolean noInherit = false;
    private boolean isSingleton = false;
    private boolean isDisposable = false;
    private FullyQualifiedName baseClassName = null;

    public ClassDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public boolean isVirtual() {
        return isVirtual;
    }

    public boolean isAbstract() {
        return isAbstract;
    }

    public boolean isNoInherit() {
        return noInherit;
    }

    public boolean isSingleton() {
        return isSingleton;
    }

    public boolean isDisposable() {
        return isDisposable;
    }

    public FullyQualifiedName getBaseClassName() {
        return baseClassName;
    }

    @Override
    public void parseFromXML(Element element) throws DescriptorParseException {
        super.parseFromXML(element);

        if ("true".equals(element.getAttribute("virtual"))) {
            isVirtual = true;
        }
        if ("true".equals(element.getAttribute("abstract"))) {
            isAbstract = true;
        }
        if ("true".equals(element.getAttribute("noinherit"))) {
            noInherit = true;
        }
        if ("true".equals(element.getAttribute("singleton"))) {
            isSingleton = true;
        }
        if ("true".equals(element.getAttribute("disposable"))) {
            isDisposable = true;
        }

        String baseClassNameStr = Strings.emptyToNull(element.getAttribute("base"));
        if (baseClassNameStr != null) {
            baseClassName = new FullyQualifiedName(baseClassNameStr);
        }
    }

    @Override
    public String mangleName() {
        StringBuilder sb = new StringBuilder();
        if (parent != null) {
            sb.append(parent.mangleName());
        }
        sb.append('c');
        sb.append(name.length());
        sb.append(name);
        return sb.toString();
    }
}
