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

package org.aerisdev.bindingtool.gen.cxxthunks;

import com.google.common.base.Strings;
import org.aerisdev.bindingtool.desc.*;
import org.aerisdev.bindingtool.desc.compound.ClassDescriptor;
import org.aerisdev.bindingtool.desc.compound.StructDescriptor;
import org.aerisdev.bindingtool.desc.member.*;
import org.aerisdev.bindingtool.desc.types.AccessMode;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;

import java.util.Collections;
import java.util.HashSet;
import java.util.List;

public class CxxThunkGenerator {
    private final BindingDescriptor desc;
    private final BindingDescriptor lookupDesc;

    public CxxThunkGenerator(BindingDescriptor desc, BindingDescriptor lookupDesc) {
        this.desc = desc;
        this.lookupDesc = lookupDesc;
    }

    private String tryTranslatePrimitiveType(FullyQualifiedName fqn) {
        if (fqn.getQualifiers().length == 1) {
            // single-qualifier type, test for known names
            String name = fqn.getQualifiers()[0];
            switch (name) {
                case "bool" -> {
                    return "bool";
                }
                case "uchar" -> {
                    return "unsigned char";
                }
                case "schar" -> {
                    return "signed char";
                }
                case "char" -> {
                    return "char";
                }
                case "uint8_t" -> {
                    return "uint8_t";
                }
                case "int8_t" -> {
                    return "int8_t";
                }
                case "ushort", "uint16_t" -> {
                    return "uint16_t";
                }
                case "short", "int16_t" -> {
                    return "int16_t";
                }
                case "uint", "uint32_t" -> {
                    return "uint32_t";
                }
                case "int", "int32_t" -> {
                    return "int32_t";
                }
                case "uint64_t" -> {
                    return "uint64_t";
                }
                case "int64_t" -> {
                    return "int64_t";
                }
                case "float" -> {
                    return "float";
                }
                case "double" -> {
                    return "double";
                }
                case "size_t" -> {
                    return "size_t";
                }
                case "CIntPtr" -> {
                    return "const void *";
                }
                case "IntPtr" -> {
                    return "void *";
                }
                case "RuntimeType" -> {
                    return "const gtlRTTI *";
                }
            }
        }
        return null;
    }

    private void emitManagedToNativeTypeConversion(StringBuilder sb, String ident, TypedDescriptor type) {
        if (type.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
            sb.append(ident);
            sb.append(".toFixedArray()");
            return;
        }
        boolean isPrimitive = tryTranslatePrimitiveType(type.getTypeName()) != null;
        if (!isPrimitive) {
            BaseDescriptor typeDesc = lookupDesc.lookupType(type.getTypeName());
            switch (type.getRefType()) {
                case WEAK:
                case STRONG:
                    sb.append("grBindingExpandWeakPtr<");
                    break;
                case RAW_PTR:
                    sb.append("static_cast<");
                    break;
                default:
                    if (typeDesc instanceof ClassDescriptor) {
                        sb.append("*static_cast<");
                    } else {
                        sb.append("static_cast<");
                    }
                    break;
            }
            sb.append(type.getTypeName());
            if (type.getRefType() == TypedDescriptor.ReferenceType.RAW_PTR
                    || (typeDesc instanceof ClassDescriptor &&
                    (type.getRefType() == TypedDescriptor.ReferenceType.NONE
                            || type.getRefType() == TypedDescriptor.ReferenceType.CONST_REF
                            || type.getRefType() == TypedDescriptor.ReferenceType.REF))) {
                sb.append(" *");
            }
            sb.append(">(");
        }
        sb.append(ident);
        if (!isPrimitive) {
            sb.append(')');
        }
    }

    private void emitNativeToManagedTypeConversion(StringBuilder sb, String ident, TypedDescriptor type) {
        boolean isPrimitive = tryTranslatePrimitiveType(type.getTypeName()) != null;
        if (!isPrimitive) {
            if (type.getRefType() == TypedDescriptor.ReferenceType.WEAK || type.getRefType() == TypedDescriptor.ReferenceType.STRONG) {
                sb.append("&*");
            }
        }
        BaseDescriptor ld = this.lookupDesc.lookupType(type.getTypeName());
        if (ld instanceof StringTypeDescriptor sd) {
            sb.append(sd.isWide() ? "grBindingAllocateWString" : "grBindingAllocateString");
        } else if (ld instanceof EnumDescriptor) {
            sb.append("static_cast<");
            sb.append(translateTypeToPublicType(type));
            sb.append('>');
        } else if (ld instanceof ClassDescriptor) {
            if (type.getRefType() == TypedDescriptor.ReferenceType.NONE ||
                    type.getRefType() == TypedDescriptor.ReferenceType.CONST_REF) {
                sb.append("gtlNew ");
                sb.append(type.getTypeName());
            }
            if (type.getRefType() == TypedDescriptor.ReferenceType.REF) {
                sb.append("&");
            }
        }
        sb.append('(');
        sb.append(ident);
        sb.append(')');
        if (type.getTypeName().toString().equals("gnaStatus")) {
            sb.append(".errorCode");
        }
    }

    private String translateTypeToPublicType(TypedDescriptor td) {
        if (td == null) return "void";

        if (td.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
            return "grBindingArray";
        }

        FullyQualifiedName fqn = td.getTypeName();
        String primitive = tryTranslatePrimitiveType(fqn);
        if (primitive != null) return primitive;

        if (fqn.toString().equals("gnaStatus")) {
            return "uint32_t";
        }

        BaseDescriptor ld = this.lookupDesc.lookupType(fqn);

        String type;
        if (ld instanceof StringTypeDescriptor sd) {
            type = sd.isWide() ? "const gtl::WIDECHAR *" : "const gtl::ASCIICHAR *";
        } else if (ld instanceof StructDescriptor) {
            type = fqn.toString();
        } else if (ld instanceof ClassDescriptor) {
            type = "void *";
        } else if (ld instanceof EnumDescriptor) {
            type = "int";
        } else {
            throw new IllegalArgumentException("Invalid type " + fqn);
        }
        if ((td.getRefType() == TypedDescriptor.ReferenceType.REF && !(ld instanceof ClassDescriptor))
                || td.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
            type += " &";
        }
        return type;
    }

    private String translateTypeToNativeType(TypedDescriptor td) {
        if (td == null) return "void";

        FullyQualifiedName fqn = td.getTypeName();
        String primitive = tryTranslatePrimitiveType(fqn);
        String resultTypeName;
        if (td.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
            resultTypeName = "gtlRawFixedArray";
        } else if (primitive != null) {
            resultTypeName = primitive;
        } else {
            resultTypeName = switch (td.getRefType()) {
                case NONE -> fqn.toString();
                case WEAK -> "gnaWeakPointer<" + fqn + ">";
                case STRONG -> "gnaPointer<" + fqn + ">";
                case RAW_PTR -> fqn + " *";
                case CONST_REF -> "const " + fqn + " &";
                case REF -> fqn + " &";
                case OUT_STRONG -> "gnaPointer<" + fqn + "> &";
            };
        }


        return resultTypeName;
    }

    private StringBuilder mangleName(StringBuilder sb, String name) {
        sb.append(name.length());
        sb.append(name);
        return sb;
    }

    private StringBuilder mangleMember(StringBuilder sb, String prefix, char typePrefix, String name) {
        sb.append(prefix);
        sb.append(typePrefix);
        return mangleName(sb, name);
    }

    private String mangleMember(String prefix, char typePrefix, String name) {
        return mangleMember(new StringBuilder(), prefix, typePrefix, name).toString();
    }

    private static final int FLAG_SETTER = 1;
    private static final int FLAG_VIRTUAL_CALL = 1 << 1;
    private static final int FLAG_VIRTUAL_CTOR = 1 << 2;

    @SuppressWarnings("ConstantValue")
    private void generateMethodOrField(StringBuilder sb, ClassDescriptor classDesc, BaseDescriptor root, String prefix, int flags) {
        StringBuilder thunkNameBuilder = new StringBuilder();

        char suffix;
        if (root instanceof FieldDescriptor) {
            suffix = 'f';
        } else if (root instanceof ConstructorDescriptor) {
            suffix = 'n';
        } else if (root instanceof MethodDescriptor) {
            suffix = 'm';
        } else {
            throw new IllegalArgumentException("Invalid descriptor type");
        }
        mangleMember(
                thunkNameBuilder,
                prefix,
                suffix,
                Strings.nullToEmpty(root.getName())
        );
        if (root instanceof MethodDescriptor md) {
            thunkNameBuilder.append('_');
            thunkNameBuilder.append(md.getArguments().size());
            for (MethodArgDescriptor arg : md.getArguments()) {
                thunkNameBuilder.append(arg.mangleType());
            }
            if ((flags & FLAG_VIRTUAL_CALL) == FLAG_VIRTUAL_CALL) {
                if (md.getAccessMode() == AccessMode.PROTECTED) {
                    return; // omit virt. calls for protected methods
                }
                thunkNameBuilder.append("v");
            }
            if (classDesc.isNoInherit() && md.getAccessMode() == AccessMode.PROTECTED) {
                return;
            }
            if ((flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
                thunkNameBuilder.append("v");
            } else if (root instanceof ConstructorDescriptor && classDesc.isAbstract()) {
                return; // omit non virt. ctors for abstract classes
            }
        } else if (root instanceof FieldDescriptor) {
            if ((flags & FLAG_SETTER) == FLAG_SETTER) {
                if (((FieldDescriptor) root).isConst()) {
                    return;
                }
                thunkNameBuilder.append('s');
            } else {
                thunkNameBuilder.append('g');
            }
        }

        TypedDescriptor returnType = null;

        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT ");
        if (root instanceof ConstructorDescriptor) {
            returnType = new TypedDescriptor(root, classDesc.getFullyQualifiedName(), TypedDescriptor.ReferenceType.RAW_PTR);
        } else if (root instanceof MethodDescriptor md) {
            returnType = md.getReturnDesc();
        } else if (root instanceof FieldDescriptor fd) {
            if ((flags & FLAG_SETTER) != FLAG_SETTER) {
                returnType = fd;
            }
        }

        BaseDescriptor returnActualType = returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

        boolean returnInArg = false;
        if (returnActualType instanceof StructDescriptor &&
                returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
            returnInArg = true;
            sb.append("void");
        } else {
            sb.append(translateTypeToPublicType(returnType));
        }
        sb.append(" GR_BINDING_THUNK_CALLCONV ");
        sb.append(thunkNameBuilder);
        sb.append('(');
        List<MethodArgDescriptor> arguments;
        if (root instanceof MethodDescriptor md) {
            arguments = md.getArguments();
        } else if ((flags & FLAG_SETTER) == FLAG_SETTER && root instanceof FieldDescriptor fd) {
            MethodArgDescriptor arg = new MethodArgDescriptor(fd);
            arg.setName("val");
            arg.copyTypeInfo(fd);
            arguments = Collections.singletonList(arg);
        } else {
            arguments = Collections.emptyList();
        }
        boolean isStatic = root instanceof ConstructorDescriptor
                || (root instanceof MethodDescriptor && ((MethodDescriptor) root).isStatic());
        boolean needsComma = false;
        if (returnInArg) {
            sb.append(translateTypeToPublicType(returnType));
            sb.append(" * grBindingReturnPtr");
            needsComma = true;
        }
        if (!isStatic) {
            if (needsComma)
                sb.append(", ");
            sb.append("void * grBindingSelfRaw");
            needsComma = true;
        }
        for (int i = 0; i < arguments.size(); i++) {
            if (needsComma)
                sb.append(", ");
            MethodArgDescriptor arg = arguments.get(i);
            sb.append(translateTypeToPublicType(arg));
            sb.append(" grBindingArgRaw_");
            sb.append(arg.getName());
            needsComma = true;
        }
        sb.append(") {\n");

        if (!isStatic) {
            sb.append("    auto grBindingSelf = static_cast<");
            if (root.getAccessMode() == AccessMode.PROTECTED) {
                sb.append("grBindingProxyClass_").append(classDesc.mangleName());
            } else {
                sb.append(classDesc.getFullyQualifiedName());
            }
            sb.append(" *>(grBindingSelfRaw);\n");
        }

        for (MethodArgDescriptor arg : arguments) {
            if (arg.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                sb.append("    gnaPointer<");
                sb.append(arg.getTypeName());
                sb.append("> grBindingArg_");
                sb.append(arg.getName());
                sb.append(";\n");
            } else {
                sb.append("    auto grBindingArg_");
                sb.append(arg.getName());
                sb.append(" = ");
                emitManagedToNativeTypeConversion(sb, "grBindingArgRaw_" + arg.getName(), arg);
                sb.append(";\n");
            }
        }

        boolean willReturn = returnType != null;
        sb.append("    ");
        if (willReturn) {
            sb.append("auto ");
            if (returnType.getRefType() == TypedDescriptor.ReferenceType.REF) {
                sb.append("& ");
            }
            sb.append("grBindingReturnValue = ");
        }
        if (root instanceof ConstructorDescriptor) {
            sb.append("gtlNew ");
            if ((flags & FLAG_VIRTUAL_CTOR) != FLAG_VIRTUAL_CTOR) {
                sb.append(classDesc.getFullyQualifiedName());
            } else {
                sb.append("grBindingProxyClass_").append(classDesc.mangleName());
            }
        } else if (isStatic) {
            sb.append(classDesc.getFullyQualifiedName());
            sb.append("::");
            sb.append(root.getName());
        } else {
            sb.append("grBindingSelf->");
            if ((flags & FLAG_VIRTUAL_CALL) != FLAG_VIRTUAL_CALL) {
                if (root.getAccessMode() == AccessMode.PROTECTED) {
                    sb.append("grBindingMemberAccessor_");
                } else {
                    sb.append(classDesc.getFullyQualifiedName());
                    sb.append("::");
                }
            }
            sb.append(root.getName());
            if (root.getAccessMode() == AccessMode.PROTECTED && root instanceof FieldDescriptor) {
                sb.append("()");
            }
        }
        if (root instanceof FieldDescriptor) {
            if ((flags & FLAG_SETTER) == FLAG_SETTER) {
                sb.append(" = ");
                MethodArgDescriptor arg = arguments.get(0);
                sb.append("grBindingArg_").append(arg.getName());
            }
        } else {
            sb.append("(");
            for (int i = 0; i < arguments.size(); i++) {
                MethodArgDescriptor arg = arguments.get(i);
                if (i != 0) sb.append(", ");
                sb.append("grBindingArg_").append(arg.getName());
            }
            sb.append(")");
        }
        sb.append(";\n");
        for (MethodArgDescriptor arg : arguments) {
            if (arg.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                sb.append("    if (");
                sb.append("grBindingArg_");
                sb.append(arg.getName());
                sb.append(") ");
                sb.append("grBindingArg_");
                sb.append(arg.getName());
                sb.append("->addRef();\n");
                sb.append("    grBindingArgRaw_");
                sb.append(arg.getName());
                sb.append(" = &*");
                sb.append("grBindingArg_");
                sb.append(arg.getName());
                sb.append(";\n");
            }
        }
        if (returnType != null && (
                returnType.getRefType() == TypedDescriptor.ReferenceType.WEAK ||
                        returnType.getRefType() == TypedDescriptor.ReferenceType.STRONG)) {
            sb.append("    if (grBindingReturnValue) grBindingReturnValue->addRef();\n");
        }
        if (willReturn) {
            if (returnInArg) {
                sb.append("    *grBindingReturnPtr = ");
            } else {
                sb.append("    return ");
            }
            if (root instanceof ConstructorDescriptor) {
                sb.append("grBindingReturnValue");
            } else {
                emitNativeToManagedTypeConversion(sb, "grBindingReturnValue", returnType);
            }
            sb.append(";\n");
        }

        sb.append("}\n\n");
    }

    private void generateEventSink(StringBuilder sb, EventSinkDescriptor root) {
        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT uintptr_t GR_BINDING_THUNK_CALLCONV ");
        sb.append(root.mangleName());
        sb.append("_addHandler(void * grBindingSelfRaw, bool (GR_BINDING_DELEGATE_CALLCONV * grBindingHandler)(");
        sb.append(root.getTypeName());
        sb.append("&), void *grBindingHandlerGch, gnaEventPriority priority) {\n");

        sb.append("    auto grBindingSelf = static_cast<");
        sb.append(root.parent.getFullyQualifiedName());
        sb.append(" *>(grBindingSelfRaw);\n");

        sb.append("    return grBindingSelf->").append(root.getName());
        sb.append(".addHandler(grBindingHandlerWrapper<");
        sb.append(root.getTypeName());
        sb.append(">{grBindingHandler, grBindingHandlerGch}, priority).internal_getHandleValue();\n");

        sb.append("}\n\n");

        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT bool GR_BINDING_THUNK_CALLCONV ");
        sb.append(root.mangleName());
        sb.append("_emit(void * grBindingSelfRaw, ");
        sb.append(root.getTypeName());
        sb.append(" &ev) {\n");

        sb.append("    auto grBindingSelf = static_cast<");
        sb.append(root.parent.getFullyQualifiedName());
        sb.append(" *>(grBindingSelfRaw);\n");

        sb.append("    return grBindingSelf->").append(root.getName()).append(".emit(ev);\n");

        sb.append("}\n\n");

        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV ");
        sb.append(root.mangleName());
        sb.append("_removeHandler(void * grBindingSelfRaw, std::uintptr_t handle) {\n");

        sb.append("    auto grBindingSelf = static_cast<");
        sb.append(root.parent.getFullyQualifiedName());
        sb.append(" *>(grBindingSelfRaw);\n");

        sb.append("    grBindingSelf->").append(root.getName()).append(".removeHandler(static_cast<gnaEventHandlerHandle>(handle));\n");

        sb.append("}\n\n");
    }

    @SuppressWarnings("ConstantValue")
    private void generateProxyClassMethodOrField(StringBuilder sb, BaseDescriptor root, String prefix, boolean isVirtual) {
        sb.append("    ");
        if (isVirtual) {
            sb.append("virtual ");
        }
        TypedDescriptor returnType;
        if (root instanceof FieldDescriptor fd) {
            returnType = fd;
        } else if (root instanceof MethodDescriptor md) {
            returnType = md.getReturnDesc();
        } else {
            throw new IllegalArgumentException("Not method nor field desc");
        }
        sb.append(translateTypeToNativeType(returnType));
        if (root instanceof FieldDescriptor) {
            sb.append(" &");
        }
        sb.append(' ');
        if (!isVirtual) {
            sb.append("grBindingMemberAccessor_");
        }
        sb.append(root.getName());

        sb.append("(");
        List<MethodArgDescriptor> arguments;
        if (root instanceof MethodDescriptor md) {
            arguments = md.getArguments();
            for (int i = 0; i < arguments.size(); i++) {
                MethodArgDescriptor arg = arguments.get(i);
                sb.append(translateTypeToNativeType(arg));
                sb.append(" grBindingArg_");
                sb.append(arg.getName());
                if (i != arguments.size() - 1)
                    sb.append(", ");
            }
        } else {
            arguments = Collections.emptyList();
        }
        sb.append(") ");

        if (root instanceof MethodDescriptor md && md.isConst()) {
            sb.append("const ");
        }

        if (isVirtual) {
            sb.append("override ");
        }

        sb.append("{\n");

        sb.append("        ");
        if (root instanceof MethodDescriptor) {
            BaseDescriptor returnActualType = returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

            boolean returnInArg = returnActualType instanceof StructDescriptor &&
                    returnType.getRefType() == TypedDescriptor.ReferenceType.NONE;

            if (returnType != null) {
                if (isVirtual) {
                    if (returnInArg) {
                        sb.append(translateTypeToPublicType(returnType));
                        sb.append(" grBindingReturnValue;\n");
                        sb.append("        ");
                    } else {
                        sb.append("return ");
                        sb.append("grBindingTypeUtils<");
                        sb.append(translateTypeToNativeType(returnType));
                        sb.append(">::translateReturnFromManagedToNative(");
                    }
                } else {
                    sb.append("return ");
                }
            }

            if (isVirtual) {
                sb.append("grBindingProxyInfoInstance_").append(prefix);
                sb.append(".").append(root.mangleName()).append("(");
                if (returnInArg) {
                    sb.append("&grBindingReturnValue, ");
                }
                sb.append("grBindingGch");
                if (!arguments.isEmpty()) {
                    sb.append(", ");
                }
            } else {
                sb.append(root.parent.getFullyQualifiedName()).append("::").append(root.getName()).append("(");
            }
            for (int i = 0; i < arguments.size(); i++) {
                MethodArgDescriptor arg = arguments.get(i);
                if (isVirtual) {
                    sb.append("grBindingTypeUtils<");
                    sb.append(translateTypeToNativeType(arg));
                    BaseDescriptor desc = lookupDesc.lookupType(arg.getTypeName());
                    if (desc instanceof ClassDescriptor) {
                        sb.append(">::translateArgFromNativeToManagedCls(");
                    } else {
                        sb.append(">::translateArgFromNativeToManaged(");
                    }
                }
                sb.append("grBindingArg_").append(arg.getName());
                if (isVirtual) {
                    sb.append(")");
                }
                if (i != arguments.size() - 1) {
                    sb.append(", ");
                }
            }
            sb.append(")");
            if (!returnInArg && isVirtual && returnType != null) {
                sb.append(")");
            }
            sb.append(";\n");
            if (isVirtual && returnInArg) {
                sb.append("        return grBindingReturnValue;\n");
            }
        } else if (root instanceof FieldDescriptor) {
            sb.append("return this->").append(root.getName()).append(";\n");
        }

        sb.append("    }\n\n");
    }

    private void generateMethodProxyInfo(StringBuilder sb, MethodDescriptor root, HashSet<MethodComparisonInfo> usedMethods) {
        MethodComparisonInfo mci = new MethodComparisonInfo(root);
        if (!usedMethods.add(mci)) return;

        sb.append("    ");

        MethodReturnDescriptor returnType = root.getReturnDesc();

        BaseDescriptor returnActualType = returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

        boolean returnInArg = false;
        if (returnActualType instanceof StructDescriptor &&
                returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
            returnInArg = true;
            sb.append("void");
        } else {
            sb.append(translateTypeToPublicType(returnType));
        }

        sb.append(" (GR_BINDING_DELEGATE_CALLCONV *").append(root.mangleName()).append(")");

        sb.append("(");
        List<MethodArgDescriptor> arguments = root.getArguments();
        boolean needsComma = false;
        if (returnInArg) {
            sb.append(translateTypeToPublicType(returnType));
            sb.append(" * grBindingReturnPtr");
            needsComma = true;
        }
        if (needsComma) {
            sb.append(", ");
        }
        sb.append("void * grBindingGchRaw");
        for (int i = 0; i < arguments.size(); i++) {
            sb.append(", ");
            MethodArgDescriptor arg = arguments.get(i);
            sb.append(translateTypeToPublicType(arg));
            sb.append(" grBindingArgRaw_");
            sb.append(arg.getName());
        }
        sb.append(");\n");
    }

    private void generateProxyClassMethods(StringBuilder sb, ClassDescriptor root, String prefix, HashSet<MethodComparisonInfo> usedMethods) {
        for (BaseDescriptor desc : root.getMembers().values()) {
            if ((desc instanceof FieldDescriptor || desc instanceof MethodDescriptor)
                    && !(desc instanceof ConstructorDescriptor)) {

                if (desc instanceof MethodDescriptor methodDesc && methodDesc.isVirtual()) {
                    MethodComparisonInfo mci = new MethodComparisonInfo(methodDesc);
                    if (!usedMethods.add(mci)) continue;

                    generateProxyClassMethodOrField(sb, methodDesc, prefix, true);
                }

                if (desc.getAccessMode() == AccessMode.PROTECTED) {
                    generateProxyClassMethodOrField(sb, desc, prefix, false);
                }
            }
        }
    }

    private void generateProxyClass(StringBuilder sb, ClassDescriptor root, String prefix) {
        sb.append("struct grBindingProxyInfo_").append(prefix);
        sb.append(" {\n");
        sb.append("    void * (GR_BINDING_DELEGATE_CALLCONV *dtor)(void *gch);\n");
        {
            ClassDescriptor curClassDesc = root;
            HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
            while (true) {
                for (BaseDescriptor desc : curClassDesc.getMembers().values()) {
                    if (desc instanceof MethodDescriptor methodDesc && !(desc instanceof ConstructorDescriptor)) {
                        if (methodDesc.isVirtual()) {
                            generateMethodProxyInfo(sb, methodDesc, usedMethods);
                        }
                    }
                }
                BaseDescriptor desc = lookupDesc.lookupType(curClassDesc.getBaseClassName());
                if (desc instanceof ClassDescriptor) {
                    curClassDesc = (ClassDescriptor) desc;
                } else if (desc != null) {
                    throw new IllegalArgumentException("Class inherited from non-class");
                } else {
                    break;
                }
            }
        }
        sb.append("} static grBindingProxyInfoInstance_").append(prefix).append(";\n\n");

        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV ").append(prefix).append('p');
        sb.append("(const grBindingProxyInfo_").append(prefix).append(" *info").append(") {\n");
        sb.append("    grBindingProxyInfoInstance_").append(prefix).append(" = *info;\n");
        sb.append("}\n\n");

        FullyQualifiedName superclass = root.getFullyQualifiedName();
        sb.append("class grBindingProxyClass_").append(prefix);
        sb.append(" : public ").append(superclass).append(" {\n");
        sb.append("public:\n");
        sb.append("    GTL_RTTI_DECLARE();\n\n");
        sb.append("    using ").append(superclass).append("::").append(superclass.getLastName()).append(";\n\n");
        sb.append("    void *grBindingGch;\n\n");
        sb.append("    virtual ~grBindingProxyClass_").append(prefix).append("() override {\n");
        sb.append("        grBindingProxyInfoInstance_").append(prefix).append(".dtor(grBindingGch);\n");
        sb.append("        grBindingGlobal_releaseGch(grBindingGch);\n");
        sb.append("    };\n\n");
        {
            ClassDescriptor curClassDesc = root;
            HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
            while (true) {
                generateProxyClassMethods(sb, curClassDesc, prefix, usedMethods);
                BaseDescriptor desc = lookupDesc.lookupType(curClassDesc.getBaseClassName());
                if (desc instanceof ClassDescriptor) {
                    curClassDesc = (ClassDescriptor) desc;
                } else if (desc != null) {
                    throw new IllegalArgumentException("Class inherited from non-class");
                } else {
                    break;
                }
            }
        }
        sb.append("};\n\n");

        sb.append("GTL_RTTI_DEFINE(grBindingProxyClass_").append(prefix);
        sb.append(", GTL_RTTI_INHERITS(").append(root.getFullyQualifiedName());
        sb.append("), GTL_RTTI_BINDING('.NET', offsetof(grBindingProxyClass_").append(prefix).append(", grBindingGch)));\n\n");
    }

    private void generateClass(StringBuilder sb, ClassDescriptor root, String prefix) {
        if (root.isVirtual()) {
            sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV ").append(prefix).append('r').append("() {\n");
            sb.append("    return &").append(root.getFullyQualifiedName()).append("::st_rtti;\n");
            sb.append("}\n\n");

            sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT const void *GR_BINDING_THUNK_CALLCONV ").append(prefix).append('d').append("(void *self) {\n");
            sb.append("    if (!self) return nullptr;\n");
            sb.append("    return static_cast<").append(root.getFullyQualifiedName()).append("*>(self)->get_rtti();\n");
            sb.append("}\n\n");

            if (!root.isNoInherit()) {
                generateProxyClass(sb, root, prefix);

                sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV ").append(prefix).append('g').append("(void *self, void *gch) {\n");
                sb.append("    static_cast<grBindingProxyClass_").append(prefix).append("*>(self)->grBindingGch = gch;\n");
                sb.append("}\n\n");
            }
        }

        if (root.isSingleton()) {
            sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void *GR_BINDING_THUNK_CALLCONV ").append(prefix).append('s').append("() {\n");
            sb.append("    return gnaSingleton<").append(root.getFullyQualifiedName()).append(">();\n");
            sb.append("}\n\n");
        }

        sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV ").append(prefix).append('x').append("(void *self) {\n");
        sb.append("    return gtlDelete static_cast<").append(root.getFullyQualifiedName()).append("*>(self);\n");
        sb.append("}\n\n");

        HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
        HashSet<String> usedFields = new HashSet<>();
        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof ConstructorDescriptor ctorDesc) {
                if (!root.isNoInherit() && root.isVirtual()) {
                    generateMethodOrField(sb, root, ctorDesc, prefix, FLAG_VIRTUAL_CTOR);
                }
                generateMethodOrField(sb, root, ctorDesc, prefix, 0);
            } else if (desc instanceof MethodDescriptor methodDesc) {
                usedMethods.add(new MethodComparisonInfo(methodDesc));
                if (methodDesc.isVirtual()) {
                    generateMethodOrField(sb, root, methodDesc, prefix, FLAG_VIRTUAL_CALL);
                }
                if (!methodDesc.isAbstract()) {
                    generateMethodOrField(sb, root, methodDesc, prefix, 0);
                }
            } else if (desc instanceof FieldDescriptor fieldDesc) {
                usedFields.add(fieldDesc.getName());
                generateMethodOrField(sb, root, fieldDesc, prefix, 0);
                generateMethodOrField(sb, root, fieldDesc, prefix, FLAG_SETTER);
            } else if (desc instanceof EventSinkDescriptor sinkDesc) {
                generateEventSink(sb, sinkDesc);
            } else if (desc instanceof ClassDescriptor classDesc) {
                generateClass(sb, classDesc, mangleMember(prefix, 'c', classDesc.getName()));
            }
        }
        {
            ClassDescriptor curClassDesc = root;
            while (true) {
                for (BaseDescriptor desc : curClassDesc.getMembers().values()) {
                    if ((desc instanceof MethodDescriptor || desc instanceof FieldDescriptor)
                            && !(desc instanceof ConstructorDescriptor)) {

                        if (desc instanceof MethodDescriptor methodDesc) {
                            MethodComparisonInfo mci = new MethodComparisonInfo(methodDesc);
                            if (!usedMethods.add(mci)) continue;
                        }

                        if (desc instanceof FieldDescriptor fieldDesc) {
                            if (!usedFields.add(fieldDesc.getName())) continue;
                        }

                        if (desc.getAccessMode() == AccessMode.PROTECTED) {
                            generateMethodOrField(sb, root, desc, prefix, 0);
                            if (desc instanceof FieldDescriptor) {
                                generateMethodOrField(sb, root, desc, prefix, FLAG_SETTER);
                            }
                        }
                    }
                }
                BaseDescriptor desc = lookupDesc.lookupType(curClassDesc.getBaseClassName());
                if (desc instanceof ClassDescriptor) {
                    curClassDesc = (ClassDescriptor) desc;
                } else if (desc != null) {
                    throw new IllegalArgumentException("Class inherited from non-class");
                } else {
                    break;
                }
            }
        }
    }

    private void generateNamespace(StringBuilder sb, NamespaceDescriptor root, String prefix) {
        for (BaseDescriptor desc : root.getNamespaceElements().values()) {
            if (desc instanceof NamespaceDescriptor nsDesc) {
                generateNamespace(sb, nsDesc, mangleMember(prefix, 'n', nsDesc.getName()));
            } else if (desc instanceof ClassDescriptor classDesc) {
                generateClass(sb, classDesc, mangleMember(prefix, 'c', classDesc.getName()));
            }
        }
    }

    public String generate() {
        StringBuilder sb = new StringBuilder();

        sb.append("#include <grBinding/BindingSupport.h>\n\n");
        for (IncludeDescriptor includeDescriptor : desc.getIncludes()) {
            sb.append("#include <");
            sb.append(includeDescriptor.getPath());
            sb.append(">\n");
        }
        sb.append('\n');

        if (desc.getNeedsModuleLoader()) {
            sb.append("extern \"C\" GR_BINDING_THUNK_EXPORT void GR_BINDING_THUNK_CALLCONV grBindingLoadModule_").append(desc.getModule()).append("() {\n");
            sb.append("    gnaSingleton<gtlModuleLoader>()->loadModule(&GROVE2_MODULE_INFO(").append(desc.getModule()).append("));\n");
            sb.append("}\n\n");
        }

        generateNamespace(sb, desc, "grBinding_");

        return sb.toString();
    }
}
