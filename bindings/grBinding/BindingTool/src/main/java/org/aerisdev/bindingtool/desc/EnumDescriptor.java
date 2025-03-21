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
import org.aerisdev.bindingtool.desc.compound.ClassDescriptor;
import org.aerisdev.bindingtool.desc.compound.StructDescriptor;
import org.aerisdev.bindingtool.desc.member.ConstructorDescriptor;
import org.aerisdev.bindingtool.desc.member.EventSinkDescriptor;
import org.aerisdev.bindingtool.desc.member.FieldDescriptor;
import org.aerisdev.bindingtool.desc.member.MethodDescriptor;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.w3c.dom.Element;
import org.w3c.dom.Node;

import java.util.ArrayList;
import java.util.List;

public class EnumDescriptor extends BaseDescriptor {
    public enum EnumMode {
        NORMAL,
        FLAGS,
        BARE
    }

    private FullyQualifiedName typeName = new FullyQualifiedName("int");
    private final List<EnumValueDescriptor> values = new ArrayList<>();
    private EnumMode mode = EnumMode.NORMAL;

    public FullyQualifiedName getTypeName() {
        return typeName;
    }

    public List<EnumValueDescriptor> getValues() {
        return values;
    }

    public EnumMode getMode() {
        return mode;
    }

    public EnumDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    @Override
    @SuppressWarnings("SwitchStatementWithTooFewBranches")
    public void parseFromXML(Element enumElement) throws DescriptorParseException {
        super.parseFromXML(enumElement);

        String tName = Strings.emptyToNull(enumElement.getAttribute("type"));
        if (tName != null) {
            typeName = new FullyQualifiedName(tName);
        }

        mode = switch(Strings.nullToEmpty(enumElement.getAttribute("mode"))) {
            case "" -> EnumMode.NORMAL;
            case "flags" -> EnumMode.FLAGS;
            case "bare" -> EnumMode.BARE;
            default -> throw new DescriptorParseException("Enum descriptor: invalid mode");
        };

        for (Node node : nodeListIterable(enumElement.getChildNodes())) {
            if (!(node instanceof Element element)) continue;

            if (!NAMESPACE_URI.equals(element.getNamespaceURI())) continue;
            EnumValueDescriptor desc = switch (element.getTagName()) {
                case "enumvalue" -> new EnumValueDescriptor(this);
                default -> throw new DescriptorParseException("Invalid member descriptor tag");
            };
            desc.parseFromXML(element);
            values.add(desc);
        }
    }
}
