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

import org.aerisdev.bindingtool.desc.compound.ClassDescriptor;
import org.aerisdev.bindingtool.desc.compound.EventDescriptor;
import org.aerisdev.bindingtool.desc.compound.StructDescriptor;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import java.util.HashMap;

public class NamespaceDescriptor extends BaseDescriptor {
    private final HashMap<String, BaseDescriptor> namespaceElements = new HashMap<>();

    public NamespaceDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public HashMap<String, BaseDescriptor> getNamespaceElements() {
        return namespaceElements;
    }

    @Override
    public void parseFromXML(Element nsElement) throws DescriptorParseException {
        super.parseFromXML(nsElement);

        for (Node node : nodeListIterable(nsElement.getChildNodes())) {
            if (!(node instanceof Element element)) continue;

            if (!NAMESPACE_URI.equals(element.getNamespaceURI())) continue;
            BaseDescriptor desc = resolveTypeName(element.getTagName());
            desc.parseFromXML(element);
            if (desc instanceof IncludeDescriptor id) {
                handleIncludeDescriptor(id);
            } else {
                if (namespaceElements.containsKey(desc.getName())) {
                    throw new DescriptorParseException("Duplicate declaration name " + desc.getName());
                }
                namespaceElements.put(desc.getName(), desc);
            }
        }
    }

    protected BaseDescriptor resolveTypeName(String name) throws DescriptorParseException {
        return switch (name) {
            case "class" -> new ClassDescriptor(this);
            case "struct" -> new StructDescriptor(this);
            case "event" -> new EventDescriptor(this);
            case "namespace" -> new NamespaceDescriptor(this);
            case "enum" -> new EnumDescriptor(this);
            case "stringtype" -> new StringTypeDescriptor(this);
            default -> throw new DescriptorParseException("Invalid element in descriptor");
        };
    }

    protected void handleIncludeDescriptor(IncludeDescriptor desc) throws DescriptorParseException {

    }

    @Override
    public BaseDescriptor querySubdescriptor(String name) {
        return namespaceElements.get(name);
    }

    @Override
    public void merge(BaseDescriptor from) {
        namespaceElements.putAll(((NamespaceDescriptor) from).getNamespaceElements());
    }

    @Override
    public String mangleName() {
        StringBuilder sb = new StringBuilder();
        if (parent != null) {
            sb.append(parent.mangleName());
        }
        sb.append('n');
        sb.append(name.length());
        sb.append(name);
        return sb.toString();
    }
}
