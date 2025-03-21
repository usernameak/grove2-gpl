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
import org.aerisdev.bindingtool.desc.types.AccessMode;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import java.util.ArrayList;
import java.util.List;

public class MethodDescriptor extends BaseDescriptor {
    private final List<MethodArgDescriptor> arguments = new ArrayList<>();
    private MethodReturnDescriptor returnDesc;
    private boolean isVirtual = false;
    private boolean isAbstract = false;
    private boolean isConst = false;
    private boolean isStatic = false;

    public boolean isVirtual() {
        return isVirtual;
    }

    public boolean isAbstract() {
        return isAbstract;
    }

    public boolean isConst() {
        return isConst;
    }

    public boolean isStatic() {
        return isStatic;
    }

    public MethodDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public List<MethodArgDescriptor> getArguments() {
        return arguments;
    }

    public MethodReturnDescriptor getReturnDesc() {
        return returnDesc;
    }

    @Override
    public void parseFromXML(Element root) throws DescriptorParseException {
        super.parseFromXML(root);

        if ("true".equals(root.getAttribute("virtual"))) {
            isVirtual = true;
        }
        if ("true".equals(root.getAttribute("abstract"))) {
            isAbstract = true;
        }
        if ("true".equals(root.getAttribute("const"))) {
            isConst = true;
        }
        if ("true".equals(root.getAttribute("static"))) {
            isStatic = true;
        }

        for (Node node : nodeListIterable(root.getChildNodes())) {
            if (!(node instanceof Element element)) continue;

            if (!NAMESPACE_URI.equals(element.getNamespaceURI())) continue;
            BaseDescriptor desc = switch (element.getTagName()) {
                case "arg" -> new MethodArgDescriptor(this);
                case "return" -> new MethodReturnDescriptor(this);
                default -> throw new DescriptorParseException("Invalid element in method descriptor");
            };
            desc.parseFromXML(element);
            if (desc instanceof MethodArgDescriptor arg) {
                arguments.add(arg);
            } else if (desc instanceof MethodReturnDescriptor ret) {
                if (returnDesc != null)
                    throw new DescriptorParseException("Duplicate <return> element in method descriptor");
                returnDesc = ret;
            } else {
                assert false;
            }
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
        sb.append('m');
        sb.append(name.length());
        sb.append(name);
        sb.append('_');
        sb.append(arguments.size());
        for (MethodArgDescriptor arg : arguments) {
            sb.append(arg.mangleType());
        }
        return sb.toString();

    }
}
