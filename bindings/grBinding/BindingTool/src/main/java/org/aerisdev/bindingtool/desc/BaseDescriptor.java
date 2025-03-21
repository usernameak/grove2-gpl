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
import org.aerisdev.bindingtool.desc.types.AccessMode;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

public abstract class BaseDescriptor {
    public static final String NAMESPACE_URI = "urn:x-grove2xml:bindings.xsd";

    protected String name;

    public final BaseDescriptor parent;

    private AccessMode accessMode = AccessMode.PUBLIC;

    public BaseDescriptor(BaseDescriptor parent) {
        this.parent = parent;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public AccessMode getAccessMode() {
        return accessMode;
    }

    public FullyQualifiedName getFullyQualifiedName() {
        List<String> nameList = new ArrayList<>();
        BaseDescriptor cur = this;
        while (cur != null && !(cur instanceof BindingDescriptor)) {
            nameList.add(cur.getName());
            cur = cur.parent;
        }
        Collections.reverse(nameList);
        return new FullyQualifiedName(nameList.toArray(String[]::new));
    }

    public void parseFromXML(Element element) throws DescriptorParseException {
        accessMode = switch (element.getAttribute("access")) {
            case "protected" -> AccessMode.PROTECTED;
            case "public", "" -> AccessMode.PUBLIC;
            default -> throw new DescriptorParseException("Invalid access mode");
        };

        if (isNamed()) {
            name = Strings.emptyToNull(element.getAttribute("name"));
            if (name == null) throw new DescriptorParseException("Named descriptor missing name");
        }
    }

    public boolean isNamed() {
        return true;
    }

    protected static Iterable<Node> nodeListIterable(NodeList nodeList) {
        return () -> new Iterator<>() {
            private int index = 0;

            @Override
            public boolean hasNext() {
                return index < nodeList.getLength();
            }

            @Override
            public Node next() {
                return nodeList.item(index++);
            }
        };
    }

    public BaseDescriptor querySubdescriptor(String name) {
        return null;
    }

    public void merge(BaseDescriptor from) {
        throw new UnsupportedOperationException("Cannot merge this descriptor type");
    }

    public String mangleName() {
        throw new UnsupportedOperationException("This descriptor name cannot be mangled");
    }
}
