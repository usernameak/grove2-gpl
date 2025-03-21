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
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.w3c.dom.Element;

import java.util.Objects;

public class TypedDescriptor extends BaseDescriptor {
    public enum ReferenceType {
        NONE, WEAK, STRONG, RAW_PTR, CONST_REF, REF, OUT_STRONG
    }

    public enum ArrayType {
        NONE, FIXED
    }

    private FullyQualifiedName typeName;
    private ReferenceType refType = ReferenceType.NONE;
    private ArrayType arrayType = ArrayType.NONE;

    public TypedDescriptor(BaseDescriptor parent) {
        super(parent);
    }

    public TypedDescriptor(BaseDescriptor parent, FullyQualifiedName typeName, ReferenceType refType) {
        super(parent);
        this.typeName = typeName;
        this.refType = refType;
    }

    public FullyQualifiedName getTypeName() {
        return typeName;
    }

    public ReferenceType getRefType() {
        return refType;
    }

    public ArrayType getArrayType() {
        return arrayType;
    }

    public void copyTypeInfo(TypedDescriptor from) {
        typeName = from.typeName;
        refType = from.refType;
    }

    @Override
    public void parseFromXML(Element element) throws DescriptorParseException {
        super.parseFromXML(element);

        String name = Strings.emptyToNull(element.getAttribute("type"));
        if (name == null || name.isEmpty()) throw new DescriptorParseException("Typed descriptor missing a type");
        typeName = new FullyQualifiedName(name);

        refType = switch(Strings.nullToEmpty(element.getAttribute("reftype"))) {
            case "" -> ReferenceType.NONE;
            case "weak" -> ReferenceType.WEAK;
            case "strong" -> ReferenceType.STRONG;
            case "rawptr" -> ReferenceType.RAW_PTR;
            case "constref" -> ReferenceType.CONST_REF;
            case "ref" -> ReferenceType.REF;
            case "outstrong" -> ReferenceType.OUT_STRONG;
            default -> throw new DescriptorParseException("Typed descriptor: invalid reftype");
        };

        arrayType = switch(Strings.nullToEmpty(element.getAttribute("arraytype"))) {
            case "" -> ArrayType.NONE;
            case "fixed" -> ArrayType.FIXED;
            default -> throw new DescriptorParseException("Typed descriptor: invalid arraytype");
        };
    }

    public boolean isSameType(TypedDescriptor other) {
        return typeName.equals(other.typeName) && refType.equals(other.refType) && arrayType.equals(other.arrayType);
    }

    public String mangleType() {
        StringBuilder sb = new StringBuilder();
        sb.append('t');
        var qualifierList = getTypeName().getQualifiers();
        sb.append(qualifierList.length);
        sb.append('_');
        for (String qual : qualifierList) {
            sb.append(qual.length());
            sb.append(qual);
        }
        return sb.toString();
    }

    public int typeHash() {
        return Objects.hash(typeName, refType, arrayType);
    }
}
