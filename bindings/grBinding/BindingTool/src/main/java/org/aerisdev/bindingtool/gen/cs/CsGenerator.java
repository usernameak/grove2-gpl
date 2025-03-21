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

package org.aerisdev.bindingtool.gen.cs;

import org.aerisdev.bindingtool.desc.*;
import org.aerisdev.bindingtool.desc.compound.ClassDescriptor;
import org.aerisdev.bindingtool.desc.compound.StructDescriptor;
import org.aerisdev.bindingtool.desc.member.*;
import org.aerisdev.bindingtool.desc.types.AccessMode;
import org.aerisdev.bindingtool.desc.types.FullyQualifiedName;
import org.apache.commons.text.StringEscapeUtils;

import java.util.HashSet;
import java.util.List;

public class CsGenerator {
    private final BindingDescriptor desc;
    private final BindingDescriptor lookupDesc;

    public CsGenerator(BindingDescriptor desc, BindingDescriptor lookupDesc) {
        this.desc = desc;
        this.lookupDesc = lookupDesc;
    }

    private String tryTranslatePrimitiveType(FullyQualifiedName fqn, boolean interop) {
        if (fqn.getQualifiers().length == 1) {
            // single-qualifier type, test for known names
            String name = fqn.getQualifiers()[0];
            switch (name) {
                case "bool" -> {
                    return "bool";
                }
                case "uchar", "uint8_t" -> {
                    return "byte";
                }
                case "schar", "char", "int8_t" -> {
                    return "sbyte";
                }
                case "ushort", "uint16_t" -> {
                    return "UInt16";
                }
                case "short", "int16_t" -> {
                    return "Int16";
                }
                case "uint", "uint32_t" -> {
                    return "UInt32";
                }
                case "int", "int32_t" -> {
                    return "Int32";
                }
                case "uint64_t" -> {
                    return "UInt64";
                }
                case "int64_t" -> {
                    return "Int64";
                }
                case "float" -> {
                    return "float";
                }
                case "double" -> {
                    return "double";
                }
                case "size_t" -> {
                    return "UIntPtr";
                }
                case "CIntPtr", "IntPtr" -> {
                    return "IntPtr";
                }
                case "RuntimeType" -> {
                    return interop ? "IntPtr" : "System.Type";
                }
            }
        }
        return null;
    }

    private String translateTypeToCsType2(TypedDescriptor td) {
        if (td == null) return "void";

        FullyQualifiedName fqn = td.getTypeName();
        String primitive = tryTranslatePrimitiveType(fqn, false);
        if (primitive != null) return primitive;

        if (fqn.toString().equals("gnaStatus")) {
            return "gnaStatus";
        }

        BaseDescriptor ld = this.lookupDesc.lookupType(fqn);
        if (ld instanceof StringTypeDescriptor) {
            return "string";
        } else if (ld instanceof StructDescriptor) {
            return fqn.toCsName();
        } else if (ld instanceof ClassDescriptor) {
            return fqn.toCsName();
        } else if (ld instanceof EnumDescriptor) {
            return fqn.toCsName();
        } else {
            throw new IllegalArgumentException("Invalid type " + fqn);
        }
    }

    private String translateTypeToCsType(TypedDescriptor td, boolean includeRefs) {
        if (td != null) {
            StringBuilder sb = new StringBuilder();
            BaseDescriptor desc = lookupDesc.lookupType(td.getTypeName());

            if (includeRefs && td.getRefType() == TypedDescriptor.ReferenceType.REF && !(desc instanceof ClassDescriptor)) {
                sb.append("ref ");
            }
            if (includeRefs && td.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                sb.append("out ");
            }
            sb.append(translateTypeToCsType2(td));
            if (td.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
                sb.append("[]");
            }
            return sb.toString();
        }
        return translateTypeToCsType2(td);
    }

    private String translateTypeToInteropType2(TypedDescriptor td, boolean isArgument) {
        if (td == null) return "void";

        if (td.getArrayType() != TypedDescriptor.ArrayType.NONE) {
            return "GroveEngine2.Binding.BindingArray";
        }

        FullyQualifiedName fqn = td.getTypeName();
        String primitive = tryTranslatePrimitiveType(fqn, true);
        if (primitive != null) return primitive;

        if (fqn.toString().equals("gnaStatus")) {
            return "UInt32";
        }

        BaseDescriptor ld = this.lookupDesc.lookupType(fqn);
        if (ld instanceof StringTypeDescriptor sd) {
            if (isArgument) {
                if (sd.isWide()) {
                    return "[MarshalAs(UnmanagedType.LPWStr)] string";
                } else {
                    return "[MarshalAs(UnmanagedType.LPUTF8Str)] string";
                }
            } else {
                return "IntPtr";
            }
        } else if (ld instanceof StructDescriptor) {
            return fqn.toCsName();
        } else if (ld instanceof ClassDescriptor) {
            return "IntPtr";
        } else if (ld instanceof EnumDescriptor) {
            return fqn.toCsName();
        } else {
            throw new IllegalArgumentException("Invalid type " + fqn);
        }
    }

    private String translateTypeToInteropType(TypedDescriptor td, boolean isArgument) {
        BaseDescriptor ld = td == null ? null : this.lookupDesc.lookupType(td.getTypeName());
        if (td != null && td.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG && isArgument) {
            return "out " + translateTypeToInteropType2(td, isArgument);
        } else if (td != null && td.getRefType() == TypedDescriptor.ReferenceType.REF && !(ld instanceof ClassDescriptor)) {
            return "ref " + translateTypeToInteropType2(td, isArgument);
        } else {
            return translateTypeToInteropType2(td, isArgument);
        }
    }

    private void generateDllImportAttribute(StringBuilder sb) {
        sb.append("    [DllImport(\"").append(desc.getDll()).append("\", CallingConvention = CallingConvention.StdCall, ExactSpelling = true)]\n");
    }

    private static final int FLAG_VIRTUAL_CALL = 1 << 1;
    private static final int FLAG_VIRTUAL_CTOR = 1 << 2;
    private static final int FLAG_NEVER_VIRTUAL = 1 << 4;

    private void generateMethodExterns(StringBuilder sb, ClassDescriptor classDesc, MethodDescriptor root, int flags) {
        if ((flags & FLAG_VIRTUAL_CTOR) != FLAG_VIRTUAL_CTOR
                && root instanceof ConstructorDescriptor && classDesc.isAbstract()) {
            return;
        }
        generateDllImportAttribute(sb);
        sb.append("    private static extern ");
        TypedDescriptor returnType;
        boolean returnInArg = false;
        if (root instanceof ConstructorDescriptor) {
            returnType = new TypedDescriptor(root, classDesc.getFullyQualifiedName(), TypedDescriptor.ReferenceType.RAW_PTR);
            sb.append("IntPtr");
        } else {
            returnType = root.getReturnDesc();
            BaseDescriptor returnActualType =
                    returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

            if (returnActualType instanceof StructDescriptor &&
                    returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
                returnInArg = true;
                sb.append("void");
            } else {
                sb.append(translateTypeToInteropType(returnType, false));
            }
        }
        sb.append(' ');
        sb.append(root.mangleNameWithBase(classDesc));
        if ((flags & FLAG_VIRTUAL_CALL) == FLAG_VIRTUAL_CALL) {
            sb.append('v');
        }
        if ((flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
            sb.append('v');
        }
        sb.append('(');
        int argIndex = 0;
        List<MethodArgDescriptor> arguments = root.getArguments();
        boolean isStatic = root instanceof ConstructorDescriptor || root.isStatic();
        if (returnInArg) {
            sb.append("out ");
            sb.append(translateTypeToInteropType(returnType, false));
            sb.append(" grBindingCS_returnValue");
            argIndex++;
        }
        if (!isStatic) {
            if (argIndex >= 1)
                sb.append(", ");
            sb.append("IntPtr grBindingCS_self");
            argIndex++;
        }
        for (MethodArgDescriptor arg : arguments) {
            if (argIndex >= 1)
                sb.append(", ");
            sb.append(translateTypeToInteropType(arg, true));
            sb.append(' ');
            sb.append(arg.getName());
            argIndex++;
        }
        sb.append(");\n\n");
    }

    private void generateFieldExterns(StringBuilder sb, FieldDescriptor root) {
        generateDllImportAttribute(sb);
        sb.append("    private static extern ");
        sb.append(translateTypeToInteropType(root, false));
        sb.append(' ');
        sb.append(root.mangleName());
        sb.append("g(");
        sb.append("IntPtr grBindingCS_self);\n\n");

        if (root.isConst()) {
            return;
        }
        generateDllImportAttribute(sb);
        sb.append("    private static extern ");
        sb.append("void ");
        sb.append(root.mangleName());
        sb.append("s(");
        sb.append("IntPtr grBindingCS_self, ");
        sb.append(translateTypeToInteropType(root, true));
        sb.append(" grBindingCS_value);\n\n");
    }

    private String generateMethodResultValue(ClassDescriptor classDesc, MethodDescriptor root, int flags) {
        StringBuilder sbResultValue = new StringBuilder();
        sbResultValue.append(root.mangleNameWithBase(classDesc));
        if ((flags & FLAG_VIRTUAL_CALL) == FLAG_VIRTUAL_CALL || (flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
            sbResultValue.append('v');
        }
        sbResultValue.append('(');
        List<MethodArgDescriptor> arguments = root.getArguments();
        boolean isStatic = root instanceof ConstructorDescriptor || root.isStatic();
        boolean needsComma = false;
        if ((flags & FLAG_RETURN_IN_ARG) == FLAG_RETURN_IN_ARG) {
            sbResultValue.append("out grBindingCS_returnValueTmp");
            needsComma = true;
        }
        if (!isStatic) {
            if (needsComma)
                sbResultValue.append(", ");
            sbResultValue.append("ToNativePtr()");
            needsComma = true;
        }
        for (int i = 0; i < arguments.size(); i++) {
            if (needsComma)
                sbResultValue.append(", ");
            MethodArgDescriptor arg = arguments.get(i);
            String name = arg.getName();
            if (arg.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                name = "grBindingCS_outValue_" + name;
            }
            generateManagedToNativeConversion(sbResultValue, name, arg, false);
            needsComma = true;
        }
        sbResultValue.append(")");
        return sbResultValue.toString();
    }

    private boolean requiresAutoRelease(ClassDescriptor classDesc) {
        ClassDescriptor curClassDesc = classDesc;
        while (true) {
            if (curClassDesc.getFullyQualifiedName().toString().equals("gtlRcObject")) {
                return true;
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
        return false;
    }

    private void generateMethodResult(StringBuilder sb, ClassDescriptor classDesc, MethodDescriptor root, int flags) {
        MethodReturnDescriptor returnDesc = root.getReturnDesc();
        TypedDescriptor returnType;
        boolean returnInArg = false;
        if (root instanceof ConstructorDescriptor) {
            returnType = new TypedDescriptor(root, classDesc.getFullyQualifiedName(), TypedDescriptor.ReferenceType.RAW_PTR);
        } else {
            returnType = root.getReturnDesc();
            BaseDescriptor returnActualType =
                    returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

            if (returnActualType instanceof StructDescriptor &&
                    returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
                returnInArg = true;
            }
        }
        if (returnInArg) {
            flags |= FLAG_RETURN_IN_ARG;
        }

        for (int i = 0; i < root.getArguments().size(); i++) {
            MethodArgDescriptor arg = root.getArguments().get(i);
            if (arg.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                sb.append("        ");
                sb.append(translateTypeToInteropType(arg, false));
                sb.append(" grBindingCS_outValue_").append(arg.getName());
                sb.append(" = default(");
                sb.append(translateTypeToInteropType(arg, false));
                sb.append(");\n");
            }
        }

        BaseDescriptor returnTypeDesc = returnDesc == null ? null : lookupDesc.lookupType(returnDesc.getTypeName());

        String resultValue = generateMethodResultValue(classDesc, root, flags);
        if (returnDesc != null) {
            sb.append("        ");
            sb.append(translateTypeToCsType(returnType, true));
            sb.append(" grBindingCS_returnValueTmp");
            if (returnInArg) {
                sb.append(" = default(");
                sb.append(translateTypeToCsType(returnType, false));
                sb.append(");\n");
                sb.append("        ");
            } else {
                sb.append(" = ");
            }

            if (returnDesc.getRefType() == TypedDescriptor.ReferenceType.REF
                    && !(returnTypeDesc instanceof ClassDescriptor)) {
                sb.append("ref ");
            }

            generateNativeToManagedConversion(sb, resultValue, returnDesc, 0);

            sb.append(";\n");
        } else if (root instanceof ConstructorDescriptor) {
            sb.append("return new ");
            sb.append(root.parent.getName());
            sb.append('(');
            sb.append(resultValue);
            sb.append(")");
            if (requiresAutoRelease(classDesc)) {
                sb.append(".AutoRelease()");
            }
        } else {
            sb.append(resultValue);
        }

        for (int i = 0; i < root.getArguments().size(); i++) {
            MethodArgDescriptor arg = root.getArguments().get(i);
            if (arg.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
                sb.append("        ");
                sb.append(arg.getName()).append(" = ");
                generateNativeToManagedConversion(sb, "grBindingCS_outValue_" + arg.getName(), arg, 0);
                sb.append(";\n");
            }
        }

        if (returnDesc != null) {
            sb.append("        return ");
            if (returnDesc.getRefType() == TypedDescriptor.ReferenceType.REF
                    && !(returnTypeDesc instanceof ClassDescriptor)) {
                sb.append("ref ");
            }
            sb.append("grBindingCS_returnValueTmp");
        }
        sb.append(";\n");
    }

    private void generateMethod(StringBuilder sb, ClassDescriptor classDesc, MethodDescriptor root, int flags) {
        if ((flags & FLAG_VIRTUAL_CTOR) != FLAG_VIRTUAL_CTOR
                && root instanceof ConstructorDescriptor && classDesc.isAbstract()) {
            return;
        }

        sb.append("    ");
        if (root instanceof ConstructorDescriptor) {
            if ((flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
                sb.append("protected ");
                sb.append(classDesc.getName());
            } else {
                sb.append("public static ");
                sb.append(classDesc.getName());
                sb.append(" Create");
            }
        } else {
            switch (root.getAccessMode()) {
                case PROTECTED -> sb.append("protected ");
                case PUBLIC -> sb.append("public ");
            }
            if (root.isStatic()) {
                sb.append("static ");
            }
            if (root.isVirtual()) {
                sb.append("virtual ");
            }
            sb.append(translateTypeToCsType(root.getReturnDesc(), true));
            sb.append(' ');
            sb.append(root.getName());
        }
        sb.append('(');
        {
            List<MethodArgDescriptor> arguments = root.getArguments();
            for (int i = 0; i < arguments.size(); i++) {
                MethodArgDescriptor arg = arguments.get(i);
                if (i != 0) sb.append(", ");
                BaseDescriptor ldesc = lookupDesc.lookupType(arg.getTypeName());
                sb.append(translateTypeToCsType(arg, true));
                sb.append(' ');
                sb.append(arg.getName());
                if (arg.getDefaultValue() != null) {
                    sb.append(" = ");
                    if (ldesc instanceof StringTypeDescriptor) {
                        sb.append("\"").append(StringEscapeUtils.escapeJava(arg.getDefaultValue())).append("\"");
                    } else {
                        sb.append(arg.getDefaultValue());
                    }
                }
            }
        }
        sb.append(")");
        if ((flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
            sb.append(" : this(");
            sb.append(generateMethodResultValue(classDesc, root, flags));
            sb.append(")");
        }
        sb.append(" {\n");

        if (root.isVirtual()) {
            sb.append("    if (!grBindingCS_isFullyNative) {\n");
            if (root.getAccessMode() != AccessMode.PUBLIC && classDesc.isNoInherit()) {
                sb.append("        throw new InvalidOperationException(\"Cannot invoke protected method externally\");\n");
            } else if (root.isAbstract()) {
                sb.append("        throw new InvalidOperationException(\"Cannot invoke abstract method\");\n");
            } else {
                generateMethodResult(sb, classDesc, root, 0);
            }
            sb.append("    } else {\n");
            if ((flags & FLAG_NEVER_VIRTUAL) == FLAG_NEVER_VIRTUAL) {
                sb.append("        throw new InvalidOperationException(\"Cannot invoke protected method externally\");\n");
            } else {
                generateMethodResult(sb, classDesc, root, FLAG_VIRTUAL_CALL | flags);
            }
            sb.append("    }\n");
        } else if ((flags & FLAG_VIRTUAL_CTOR) == FLAG_VIRTUAL_CTOR) {
            sb.append("        ").append(classDesc.mangleName()).append("g(ToNativePtr(), GCHandle.ToIntPtr(GCHandle.Alloc(this)));\n");
            if (requiresAutoRelease(classDesc)) {
                sb.append("        this.AutoRelease();\n");
            }
        } else {
            generateMethodResult(sb, classDesc, root, flags);
        }

        sb.append("    }\n\n");
    }

    private static final int FLAG_NO_FREE_STRING = 1 << 3;
    private static final int FLAG_RETURN_IN_ARG = 1 << 5;

    private void generateNativeToManagedConversion(StringBuilder sb, String value, TypedDescriptor typedDesc, int flags) {
        BaseDescriptor returnType = lookupDesc.lookupType(typedDesc.getTypeName());
        boolean needsParens = false;
        if (returnType instanceof ClassDescriptor) {
            sb.append(typedDesc.getTypeName().toCsName());
            sb.append(".FromNativePtr");
            needsParens = true;
        } else if (returnType instanceof StringTypeDescriptor sd) {
            if ((flags & FLAG_NO_FREE_STRING) != FLAG_NO_FREE_STRING) {
                if (sd.isWide()) {
                    sb.append("GroveEngine2.Binding.BindingSupport.ConvertAndFreeWString");
                } else {
                    sb.append("GroveEngine2.Binding.BindingSupport.ConvertAndFreeString");
                }
                needsParens = true;
            }
        }
        if (needsParens) sb.append('(');
        sb.append(value);
        if (needsParens) sb.append(')');
        if (typedDesc.getRefType() == TypedDescriptor.ReferenceType.WEAK
                || typedDesc.getRefType() == TypedDescriptor.ReferenceType.STRONG
                || typedDesc.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
            sb.append(".AutoRelease()");
        }
    }

    private void generateManagedToNativeConversion(StringBuilder sb, String value, TypedDescriptor td, boolean isReturn) {
        if (td.getTypeName().equals(new FullyQualifiedName("RuntimeType"))) {
            sb.append("GroveEngine2.Binding.RTTIRegistry.LookupRTTIFromType(");
            sb.append(value);
            sb.append(")");
            return;
        }
        BaseDescriptor ldesc = lookupDesc.lookupType(td.getTypeName());
        boolean needsToNativePtr =
                (ldesc instanceof ClassDescriptor ||
                        td.getRefType() == TypedDescriptor.ReferenceType.WEAK ||
                        td.getRefType() == TypedDescriptor.ReferenceType.STRONG ||
                        td.getRefType() == TypedDescriptor.ReferenceType.RAW_PTR)
                        && td.getRefType() != TypedDescriptor.ReferenceType.OUT_STRONG;
        if (td.getRefType() == TypedDescriptor.ReferenceType.OUT_STRONG) {
            sb.append("out ");
        }
        if (td.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
            sb.append("GroveEngine2.Binding.BindingSupport.AllocateBindingArray(");
        }
        if (needsToNativePtr) {
            sb.append("GroveEngine2.Binding.BindingSupport.ToNativePtr(");
        }
        if (isReturn) {
            if (ldesc instanceof StringTypeDescriptor sd) {
                if (sd.isWide()) {
                    sb.append("GroveEngine2.Binding.BindingSupport.AllocWString");
                } else {
                    sb.append("GroveEngine2.Binding.BindingSupport.AllocString");
                }
            }
            sb.append("(");
        }
        sb.append(value);
        if (isReturn) {
            sb.append(")");
        }
        if (needsToNativePtr) {
            sb.append(")");
        }
        if (td.getArrayType() == TypedDescriptor.ArrayType.FIXED) {
            sb.append(")");
        }
    }

    private void generateField(StringBuilder sb, ClassDescriptor classDesc, FieldDescriptor root) {
        sb.append("    public ");
        sb.append(translateTypeToCsType(root, true));
        sb.append(' ');
        sb.append(root.getName());
        sb.append(" {\n");

        sb.append("        get {\n");
        if (root.getAccessMode() == AccessMode.PROTECTED) {
            sb.append("            if (grBindingCS_isFullyNative) throw new InvalidOperationException(\"Accessing protected field directly. Are you debugging?\");\n");
        }
        sb.append("            return ");
        generateNativeToManagedConversion(sb, root.mangleNameWithBase(classDesc) + "g(ToNativePtr())", root, 0);
        sb.append(";\n");
        sb.append("        }\n");

        if (!root.isConst()) {
            sb.append("        set { ").append(root.mangleNameWithBase(classDesc)).append("s(ToNativePtr(), ");
            MethodArgDescriptor arg = new MethodArgDescriptor(root);
            arg.setName("value");
            arg.copyTypeInfo(root);
            generateManagedToNativeConversion(sb, arg.getName(), arg, false);
            sb.append("); }\n");
        }

        sb.append("    }\n\n");
    }

    private void generateClassExterns(StringBuilder sb, ClassDescriptor root) {
        // rtti
        if (root.isVirtual()) {
            generateDllImportAttribute(sb);
            sb.append("    private static extern IntPtr ").append(root.mangleName()).append("d(IntPtr ptr);\n\n");
            generateDllImportAttribute(sb);
            sb.append("    private static extern IntPtr ").append(root.mangleName()).append("r();\n\n");
            if (!root.isNoInherit()) {
                generateDllImportAttribute(sb);
                sb.append("    private static extern void ").append(root.mangleName()).append("g(IntPtr ptr, IntPtr gch);\n\n");
            }
        }
        if (root.isSingleton()) {
            generateDllImportAttribute(sb);
            sb.append("    private static extern IntPtr ").append(root.mangleName()).append("s();\n\n");
        }

        // deleter
        generateDllImportAttribute(sb);
        sb.append("    private static extern IntPtr ").append(root.mangleName()).append("x(IntPtr ptr);\n\n");

        HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof ConstructorDescriptor constrDesc) {
                if (!root.isNoInherit() && root.isVirtual()) {
                    generateMethodExterns(sb, root, constrDesc, FLAG_VIRTUAL_CTOR);
                }
                generateMethodExterns(sb, root, constrDesc, 0);
            } else if (desc instanceof MethodDescriptor methodDesc) {
                usedMethods.add(new MethodComparisonInfo(methodDesc));
                if (methodDesc.isVirtual()) {
                    generateMethodExterns(sb, root, methodDesc, FLAG_VIRTUAL_CALL);
                }
                if ((!root.isNoInherit() || !methodDesc.isVirtual()) && !methodDesc.isAbstract()) {
                    generateMethodExterns(sb, root, methodDesc, 0);
                }
            } else if (desc instanceof FieldDescriptor fieldDesc) {
                generateFieldExterns(sb, fieldDesc);
            }
        }
        {
            ClassDescriptor curClassDesc = root;
            while (true) {
                for (BaseDescriptor desc : curClassDesc.getMembers().values()) {
                    if (desc instanceof MethodDescriptor methodDesc && !(desc instanceof ConstructorDescriptor)) {
                        MethodComparisonInfo mci = new MethodComparisonInfo(methodDesc);
                        if (!usedMethods.add(mci)) continue;

                        if (methodDesc.getAccessMode() == AccessMode.PROTECTED) {
                            generateMethodExterns(sb, root, methodDesc, FLAG_NEVER_VIRTUAL);
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

    @SuppressWarnings("ConstantValue")
    private void generateClassThunks(StringBuilder sb, ClassDescriptor root) {
        sb.append("    protected ").append(root.getName()).append("(IntPtr ptr) : base(ptr) {\n");
        sb.append("        grBindingCS_ClassBindingInit();\n");
        sb.append("    }\n\n");

        if (root.isDisposable()) {
            sb.append("    public void Dispose() {\n");
            sb.append("        Destroy();\n");
            sb.append("    }\n\n");
        }

        if (root.isSingleton()) {
            sb.append("    public static ").append(root.getName()).append(" instance => FromNativePtr(").append(root.mangleName()).append("s());\n\n");
        }

        sb.append("    public new static GroveEngine2.Binding.Object FromNativePtrUnsafe(IntPtr ptr) {\n");
        sb.append("        if (ptr == IntPtr.Zero) return null;\n");
        sb.append("        return new ").append(root.getName()).append("(ptr);\n");
        sb.append("    }\n\n");

        sb.append("    public new static ").append(root.getName()).append(" FromNativePtr(IntPtr ptr) {\n");
        if (root.isVirtual()) {
            sb.append("        if (ptr == IntPtr.Zero) return null;\n");

            sb.append("        return (").append(root.getName()).append(")");
            sb.append("GroveEngine2.Binding.RTTIRegistry.LookupTypedObject(ptr, ");
            sb.append(root.mangleName()).append("d(ptr), FromNativePtrUnsafe);\n");
        } else {
            sb.append("        return (").append(root.getName()).append(") FromNativePtrUnsafe(ptr);\n");
        }
        sb.append("    }\n\n");

        sb.append("    public new static void RegisterClass() {\n");
        if (root.isVirtual()) {
            sb.append("        GroveEngine2.Binding.RTTIRegistry.RegisterType(")
                    .append(root.mangleName())
                    .append("r(), typeof(")
                    .append(root.getName())
                    .append("), FromNativePtrUnsafe);\n");
        }
        sb.append("    }\n\n");

        sb.append("    public override void Destroy() {\n");
        sb.append("        ").append(root.mangleName()).append("x(ToNativePtr());\n");
        sb.append("    }\n\n");

        HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
        HashSet<String> usedFields = new HashSet<>();
        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof ConstructorDescriptor ctorDesc) {
                if (!root.isNoInherit() && root.isVirtual()) {
                    generateMethod(sb, root, ctorDesc, FLAG_VIRTUAL_CTOR);
                }
                generateMethod(sb, root, ctorDesc, 0);
            } else if (desc instanceof MethodDescriptor methodDesc) {
                usedMethods.add(new MethodComparisonInfo(methodDesc));
                generateMethod(sb, root, methodDesc, 0);
            } else if (desc instanceof FieldDescriptor fieldDesc) {
                usedFields.add(fieldDesc.getName());
                generateField(sb, root, fieldDesc);
            } else if (desc instanceof ClassDescriptor classDesc) {
                generateClass(sb, classDesc);
            } else if (desc instanceof StructDescriptor structDesc) {
                generateStruct(sb, structDesc);
            } else if (desc instanceof EnumDescriptor enumDesc) {
                generateEnum(sb, enumDesc);
            } else if (desc instanceof EventSinkDescriptor sinkDesc) {
                generateEventSink(sb, sinkDesc);
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
                            if (desc instanceof MethodDescriptor methodDesc) {
                                generateMethod(sb, root, methodDesc, FLAG_NEVER_VIRTUAL);
                            } else if (desc instanceof FieldDescriptor fieldDesc) {
                                generateField(sb, root, fieldDesc);
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

    private void generateEventSink(StringBuilder sb, EventSinkDescriptor sinkDesc) {
        String eventTypeName = sinkDesc.getTypeName().toCsName();

        sb.append("    private class grBindingCS_EventSink_").append(sinkDesc.getName());
        sb.append(" : GroveEngine2.EventSystem.EventSink<").append(eventTypeName).append("> {\n");

        sb.append("        private GroveEngine2.Binding.Object owner;\n\n");
        sb.append("        private delegate bool HandlerFuncTyped(ref ").append(eventTypeName).append(" ev);\n\n");

        generateDllImportAttribute(sb);
        sb.append("        private static extern UIntPtr ");
        sb.append(sinkDesc.mangleName());
        sb.append("_addHandler(IntPtr self, HandlerFuncTyped handler, IntPtr handlerGch, GroveEngine2.EventSystem.EventPriority eventPriority);\n\n");

        generateDllImportAttribute(sb);
        sb.append("        private static extern bool ");
        sb.append(sinkDesc.mangleName());
        sb.append("_emit(IntPtr self, ref ").append(eventTypeName).append(" ev);\n\n");

        generateDllImportAttribute(sb);
        sb.append("        private static extern void ");
        sb.append(sinkDesc.mangleName());
        sb.append("_removeHandler(IntPtr self, UIntPtr handle);\n\n");

        sb.append("        public grBindingCS_EventSink_").append(sinkDesc.getName()).append("(GroveEngine2.Binding.Object owner) {\n");
        sb.append("            this.owner = owner;\n");
        sb.append("        }\n\n");

        sb.append("        public override GroveEngine2.EventSystem.EventHandlerHandle AddHandler(HandlerFunc handler, GroveEngine2.EventSystem.EventPriority eventPriority) {\n");
        sb.append("            HandlerFuncTyped hft = new HandlerFuncTyped(handler);\n");
        sb.append("            return new GroveEngine2.EventSystem.EventHandlerHandle(").append(sinkDesc.mangleName()).append("_addHandler(owner.ToNativePtr(), hft, GCHandle.ToIntPtr(GCHandle.Alloc(hft)), eventPriority));\n");
        sb.append("        }\n\n");

        sb.append("        public override bool Emit(ref ").append(eventTypeName).append(" ev) {\n");
        sb.append("            return ").append(sinkDesc.mangleName()).append("_emit(owner.ToNativePtr(), ref ev);\n");
        sb.append("        }\n\n");

        sb.append("        public override void RemoveHandler(GroveEngine2.EventSystem.EventHandlerHandle handle) {\n");
        sb.append("            ").append(sinkDesc.mangleName()).append("_removeHandler(owner.ToNativePtr(), handle.handle);\n");
        sb.append("        }\n\n");

        sb.append("    }\n\n");

        sb.append("    public GroveEngine2.EventSystem.EventSink<").append(eventTypeName);
        sb.append("> ").append(sinkDesc.getName()).append(";\n");
    }

    private void generateBindingInitializer(StringBuilder sb, ClassDescriptor root) {
        sb.append("    private void grBindingCS_ClassBindingInit() {\n");

        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof EventSinkDescriptor sinkDesc) {
                generateEventSinkBindingInitializer(sb, sinkDesc);
            }
        }

        sb.append("    }\n\n");
    }

    private void generateEventSinkBindingInitializer(StringBuilder sb, EventSinkDescriptor sinkDesc) {
        sb.append("        ");
        sb.append(sinkDesc.getName());
        sb.append(" = new grBindingCS_EventSink_").append(sinkDesc.getName());
        sb.append("(this);\n");
    }

    private void generateMethodProxyInfo(StringBuilder sb, MethodDescriptor root, HashSet<MethodComparisonInfo> usedMethods) {
        MethodComparisonInfo mci = new MethodComparisonInfo(root);
        if (!usedMethods.add(mci)) return;


        sb.append("        public delegate ");

        boolean returnInArg = false;

        MethodReturnDescriptor returnType = root.getReturnDesc();
        BaseDescriptor returnActualType =
                returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

        if (returnActualType instanceof StructDescriptor &&
                returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
            returnInArg = true;
            sb.append("void");
        } else {
            sb.append(translateTypeToInteropType(returnType, false));
        }

        sb.append(" grBindingCS_DelegateType_").append(root.mangleName());

        sb.append("(");

        boolean needsComma = false;

        List<MethodArgDescriptor> arguments = root.getArguments();

        if (returnInArg) {
            sb.append("out ");
            sb.append(translateTypeToInteropType(returnType, false));
            sb.append(" grBindingCS_returnValue");
            needsComma = true;
        }

        if (needsComma) {
            sb.append(", ");
        }
        sb.append("IntPtr gch");

        for (int i = 0; i < arguments.size(); i++) {
            sb.append(", ");
            MethodArgDescriptor arg = arguments.get(i);
            sb.append(translateTypeToInteropType(arg, true));
            sb.append(' ');
            sb.append(arg.getName());
        }
        sb.append(");\n");

        sb.append("        public grBindingCS_DelegateType_").append(root.mangleName());
        sb.append(' ').append(root.mangleName()).append(";\n");
    }

    private void generateMethodProxyImpl(StringBuilder sb, ClassDescriptor classDesc, MethodDescriptor root, HashSet<MethodComparisonInfo> usedMethods) {
        MethodComparisonInfo mci = new MethodComparisonInfo(root);
        if (!usedMethods.add(mci)) return;

        sb.append("    private static ");
        boolean returnInArg = false;

        MethodReturnDescriptor returnType = root.getReturnDesc();
        BaseDescriptor returnActualType =
                returnType != null ? lookupDesc.lookupType(returnType.getTypeName()) : null;

        if (returnActualType instanceof StructDescriptor &&
                returnType.getRefType() == TypedDescriptor.ReferenceType.NONE) {
            returnInArg = true;
            sb.append("void");
        } else {
            sb.append(translateTypeToInteropType(returnType, false));
        }
        sb.append(" grBindingCS_ClassMethodProxy_").append(root.mangleName());
        sb.append("(");
        {
            boolean needsComma = false;

            List<MethodArgDescriptor> arguments = root.getArguments();

            if (returnInArg) {
                sb.append("out ");
                sb.append(translateTypeToInteropType(returnType, false));
                sb.append(" grBindingCS_returnValue");
                needsComma = true;
            }

            if (needsComma) {
                sb.append(", ");
            }
            sb.append("IntPtr grBindingCS_gch");
            for (int i = 0; i < arguments.size(); i++) {
                sb.append(", ");
                MethodArgDescriptor arg = arguments.get(i);
                sb.append(translateTypeToInteropType(arg, true));
                sb.append(' ');
                sb.append(arg.getName());
            }
        }
        sb.append(") {\n");
        StringBuilder sbReturnValue = new StringBuilder();
        sbReturnValue.append("((").append(classDesc.getName()).append(")GCHandle.FromIntPtr(grBindingCS_gch).Target).");
        sbReturnValue.append(root.getName());
        sbReturnValue.append('(');
        {
            List<MethodArgDescriptor> arguments = root.getArguments();
            for (int i = 0; i < arguments.size(); i++) {
                MethodArgDescriptor arg = arguments.get(i);
                generateNativeToManagedConversion(sbReturnValue, arg.getName(), arg, FLAG_NO_FREE_STRING);
                if (i != arguments.size() - 1) {
                    sbReturnValue.append(", ");
                }
            }
        }
        sbReturnValue.append(")");
        sb.append("        ");
        if (root.getReturnDesc() != null) {
            if (returnInArg) {
                sb.append("grBindingCS_returnValue = ");
            } else {
                sb.append("return ");
            }
            generateManagedToNativeConversion(sb, sbReturnValue.toString(), root.getReturnDesc(), true);
        } else {
            sb.append(sbReturnValue);
        }
        sb.append(";\n");
        sb.append("    }\n");
    }

    private void generateMethodProxyAssignment(StringBuilder sb, MethodDescriptor root, HashSet<MethodComparisonInfo> usedMethods) {
        MethodComparisonInfo mci = new MethodComparisonInfo(root);
        if (!usedMethods.add(mci)) return;

        sb.append("        grBindingCS_ClassProxyInstance.").append(root.mangleName()).append(" = ");
        sb.append("grBindingCS_ClassMethodProxy_").append(root.mangleName()).append(";\n");
    }

    private void generateClassProxy(StringBuilder sb, ClassDescriptor root) {
        generateCodegenAttribute(sb);
        sb.append("    [StructLayout(LayoutKind.Sequential)]\n");
        sb.append("    private struct grBindingCS_ClassProxy {\n");
        sb.append("        public delegate void grBindingCS_DelegateTypeDtor(IntPtr gch);\n");
        sb.append("        public grBindingCS_DelegateTypeDtor dtor;\n");
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
        sb.append("    }\n\n");
        sb.append("    private static grBindingCS_ClassProxy grBindingCS_ClassProxyInstance = new grBindingCS_ClassProxy();\n\n");
        sb.append("    private static void grBindingCS_ClassDtorProxy(IntPtr grBindingCS_gch) {\n");
        sb.append("        ((").append(root.getName()).append(")GCHandle.FromIntPtr(grBindingCS_gch).Target).OnDestroy();\n");
        sb.append("    }\n");
        {
            ClassDescriptor curClassDesc = root;
            HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
            while (true) {
                for (BaseDescriptor desc : curClassDesc.getMembers().values()) {
                    if (desc instanceof MethodDescriptor methodDesc && !(desc instanceof ConstructorDescriptor)) {
                        if (methodDesc.isVirtual()) {
                            generateMethodProxyImpl(sb, root, methodDesc, usedMethods);
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
        generateDllImportAttribute(sb);
        sb.append("    private static extern void ").append(root.mangleName()).append("p(grBindingCS_ClassProxy proxy);\n\n");
        sb.append("    static ").append(root.getName()).append("() {\n");
        sb.append("        grBindingCS_ClassProxyInstance.dtor = grBindingCS_ClassDtorProxy;\n");
        {
            ClassDescriptor curClassDesc = root;
            HashSet<MethodComparisonInfo> usedMethods = new HashSet<>();
            while (true) {
                for (BaseDescriptor desc : curClassDesc.getMembers().values()) {
                    if (desc instanceof MethodDescriptor methodDesc && !(desc instanceof ConstructorDescriptor)) {
                        if (methodDesc.isVirtual()) {
                            generateMethodProxyAssignment(sb, methodDesc, usedMethods);
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
        sb.append("        ").append(root.mangleName()).append("p(grBindingCS_ClassProxyInstance);\n");
        sb.append("    }\n\n");
    }

    private void generateClass(StringBuilder sb, ClassDescriptor root) {
        if (root.isManuallyDefined()) {
            return; // do not generate this class - it will be externally defined
        }

        generateCodegenAttribute(sb);
        sb.append("[GroveEngine2.Binding.NativeClass]\n");
        sb.append("public class ");
        sb.append(root.getName());
        sb.append(" : GroveEngine2.");
        sb.append(root.getBaseClassName() != null ? root.getBaseClassName() : "Binding.Object");
        if (root.isDisposable()) {
            sb.append(", IDisposable");
        }
        sb.append(" {\n");

        if (!root.isNoInherit() && root.isVirtual()) {
            generateClassProxy(sb, root);
        }

        generateClassExterns(sb, root);
        generateClassThunks(sb, root);
        generateBindingInitializer(sb, root);

        sb.append("}\n\n");
    }

    private void generateStructField(StringBuilder sb, FieldDescriptor root) {
        sb.append("    public ");
        sb.append(translateTypeToCsType(root, true));
        sb.append(' ');
        sb.append(root.getName());
        sb.append(";\n\n");
    }

    private void generateStruct(StringBuilder sb, StructDescriptor root) {
        if (root.isManuallyDefined()) {
            return; // do not generate this struct - it will be externally defined
        }

        generateCodegenAttribute(sb);
        sb.append("[StructLayout(LayoutKind.Sequential)]\n");
        sb.append("public struct ");
        sb.append(root.getName());
        sb.append(" {\n");

        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof FieldDescriptor fieldDesc) {
                generateStructField(sb, fieldDesc);
            }
        }

        sb.append("}\n\n");
    }

    private void generateEnum(StringBuilder sb, EnumDescriptor root) {
        generateCodegenAttribute(sb);
        if (root.getMode() == EnumDescriptor.EnumMode.FLAGS) {
            sb.append("[System.Flags]");
        }
        sb.append("public enum ").append(root.getName());
        sb.append(" : ").append(tryTranslatePrimitiveType(root.getTypeName(), false));
        sb.append(" {\n");

        for (EnumValueDescriptor val : root.getValues()) {
            sb.append("    ");
            sb.append(val.getName());
            sb.append(" = ");
            sb.append(val.getValue());
            sb.append(",\n");
        }

        sb.append("}\n\n");
    }

    private void generateNamespace(StringBuilder sb, NamespaceDescriptor root) {
        for (BaseDescriptor desc : root.getNamespaceElements().values()) {
            if (desc instanceof NamespaceDescriptor nsDesc) {
                sb.append("namespace ");
                sb.append(nsDesc.getName());
                sb.append(" {\n");
                generateNamespace(sb, nsDesc);
                sb.append("}\n\n");
            } else if (desc instanceof ClassDescriptor classDesc) {
                generateClass(sb, classDesc);
            } else if (desc instanceof StructDescriptor structDesc) {
                generateStruct(sb, structDesc);
            } else if (desc instanceof EnumDescriptor enumDesc) {
                generateEnum(sb, enumDesc);
            }
        }
    }

    private void generateClassRegistrations(StringBuilder sb, ClassDescriptor root) {
        generateClassRegistration(sb, root);
        for (BaseDescriptor desc : root.getMembers().values()) {
            if (desc instanceof ClassDescriptor classDesc) {
                generateClassRegistrations(sb, classDesc);
            }
        }
    }

    private void generateNamespaceRegistrations(StringBuilder sb, NamespaceDescriptor root) {
        for (BaseDescriptor desc : root.getNamespaceElements().values()) {
            if (desc instanceof NamespaceDescriptor nsDesc) {
                generateNamespaceRegistrations(sb, nsDesc);
            } else if (desc instanceof ClassDescriptor classDesc) {
                generateClassRegistrations(sb, classDesc);
            }
        }
    }

    private void generateClassRegistration(StringBuilder sb, ClassDescriptor classDesc) {
        sb.append("        ").append(classDesc.getFullyQualifiedName().toCsName()).append(".RegisterClass();\n");
    }

    private void generateCodegenAttribute(StringBuilder sb) {
        sb.append("[GeneratedCode(\"GroveEngine2 BindingTool\", \"1.0.0.0\")]\n");
    }

    public String generate() {
        StringBuilder sb = new StringBuilder();

        sb.append("//------------------------------------------------------------------------------\n");
        sb.append("// <auto-generated>\n");
        sb.append("// AUTO-GENERATED CODE. DO NOT MODIFY!\n");
        sb.append("// </auto-generated>\n");
        sb.append("//------------------------------------------------------------------------------\n\n");
        sb.append("#pragma warning disable CS0108, CS0114, CS0109\n");
        sb.append("using System;\n");
        sb.append("using System.Runtime.InteropServices;\n");
        sb.append("using System.CodeDom.Compiler;\n");
        sb.append("using GroveEngine2.Binding;\n\n");
        sb.append("namespace GroveEngine2 {\n");

        generateCodegenAttribute(sb);
        sb.append("public class ").append(desc.getModule()).append("Module {\n");
        generateDllImportAttribute(sb);

        String moduleLoadFuncName = "grBindingLoadModule_" + desc.getModule();
        sb.append("    private static extern void ").append(moduleLoadFuncName).append("();\n");
        sb.append("    public static void Load() {\n");
        if (desc.getNeedsModuleLoader()) {
            sb.append("        ").append(moduleLoadFuncName).append("();\n");
        }
        generateNamespaceRegistrations(sb, desc);
        sb.append("    }\n");
        sb.append("}\n\n");

        generateNamespace(sb, desc);
        sb.append("}\n");

        return sb.toString();
    }
}
