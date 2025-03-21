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

import com.google.common.collect.HashMultimap;
import com.google.common.collect.LinkedHashMultimap;
import org.aerisdev.bindingtool.desc.BaseDescriptor;
import org.aerisdev.bindingtool.desc.DescriptorParseException;
import org.aerisdev.bindingtool.desc.EnumDescriptor;
import org.aerisdev.bindingtool.desc.StringTypeDescriptor;
import org.aerisdev.bindingtool.desc.member.ConstructorDescriptor;
import org.aerisdev.bindingtool.desc.member.EventSinkDescriptor;
import org.aerisdev.bindingtool.desc.member.FieldDescriptor;
import org.aerisdev.bindingtool.desc.member.MethodDescriptor;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import java.util.Set;

public class CompoundTypeDescriptor extends BaseDescriptor {
    private boolean isManuallyDefined = false;

    private final LinkedHashMultimap<String, BaseDescriptor> members = LinkedHashMultimap.create();

    public CompoundTypeDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public boolean isManuallyDefined() {
        return isManuallyDefined;
    }

    public LinkedHashMultimap<String, BaseDescriptor> getMembers() {
        return members;
    }

    @Override
    public void parseFromXML(Element compoundElement) throws DescriptorParseException {
        super.parseFromXML(compoundElement);

        if ("true".equals(compoundElement.getAttribute("manuallyDefined"))) {
            isManuallyDefined = true;
        }

        for (Node node : nodeListIterable(compoundElement.getChildNodes())) {
            if (!(node instanceof Element element)) continue;

            if (!NAMESPACE_URI.equals(element.getNamespaceURI())) continue;
            BaseDescriptor desc = switch (element.getTagName()) {
                case "method" -> new MethodDescriptor(this);
                case "constructor" -> new ConstructorDescriptor(this);
                case "eventSink" -> new EventSinkDescriptor(this);
                case "field" -> new FieldDescriptor(this);
                case "class" -> new ClassDescriptor(this);
                case "struct" -> new StructDescriptor(this);
                case "event" -> new EventDescriptor(this);
                // case "namespace" -> new NamespaceDescriptor(this);
                case "enum" -> new EnumDescriptor(this);
                case "stringtype" -> new StringTypeDescriptor(this);
                default -> throw new DescriptorParseException("Invalid member descriptor tag");
            };
            desc.parseFromXML(element);
            members.put(desc.getName(), desc);
        }
    }

    @Override
    public BaseDescriptor querySubdescriptor(String name) {
        Set<BaseDescriptor> set = members.get(name);
        return set.size() == 1 ? set.iterator().next() : null;
    }
}
