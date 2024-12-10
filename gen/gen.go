package main

import (
	"fmt"
	"io"
	"math"
	"reflect"
	"strconv"
	"strings"
	"text/template"
)

type Generator struct {
	ExtPrefix  string
	HeaderName string
	*Yml
}

func (g *Generator) Gen(dst io.Writer) error {
	t := template.
		New("").
		Funcs(template.FuncMap{
			"SComment":  func(v string, indent int) string { return Comment(v, CommentTypeSingleLine, indent, true) },
			"MComment":  func(v string, indent int) string { return Comment(v, CommentTypeMultiLine, indent, true) },
			"SCommentN": func(v string, indent int) string { return Comment(v, CommentTypeSingleLine, indent, false) },
			"MCommentN": func(v string, indent int) string { return Comment(v, CommentTypeMultiLine, indent, false) },
			"MCommentMainPage": func(v string, indent int) string {
				if v == "" || strings.TrimSpace(v) == "TODO" {
					return ""
				}
				return Comment("\\mainpage\n\n"+strings.TrimSpace(v), CommentTypeMultiLine, indent, true)
			},
			"MCommentEnum": func(v string, indent int, prefix string, e Enum, entryIndex int) string {
				if v == "" || strings.TrimSpace(v) == "TODO" {
					return ""
				}
				value, _ := g.EnumValue(prefix, e, entryIndex)
				return Comment("`"+value+"`.\n"+strings.TrimSpace(v), CommentTypeMultiLine, indent, true)
			},
			"MCommentBitflag": func(v string, indent int, b Bitflag, entryIndex int) string {
				if v == "" || strings.TrimSpace(v) == "TODO" {
					return ""
				}
				value, _ := g.BitflagValue(b, entryIndex)
				return Comment("`"+value+"`.\n"+v, CommentTypeMultiLine, indent, true)
			},
			"MCommentFunction": func(fn *Function, indent int) string {
				var s string
				{
					var funcDoc = strings.TrimSpace(fn.Doc)
					if funcDoc != "" && funcDoc != "TODO" {
						s += funcDoc
					}
				}
				for _, arg := range fn.Args {
					var argDoc = strings.TrimSpace(arg.Doc)
					var sArg string
					if argDoc != "" && argDoc != "TODO" {
						sArg += argDoc
					}

					if arg.PassedWithOwnership != nil {
						if *arg.PassedWithOwnership {
							sArg += "\nThis parameter is @ref ReturnedWithOwnership."
						} else {
							panic("invalid")
						}
					}

					sArg = strings.TrimSpace(sArg)
					if sArg != "" {
						s += "\n\n@param " + CamelCase(arg.Name) + "\n" + sArg
					}
				}
				if fn.Returns != nil {
					returnsDoc := strings.TrimSpace(fn.Returns.Doc)
					if returnsDoc != "" && returnsDoc != "TODO" {
						s += "\n\n@returns\n" + returnsDoc
					}
				}
				return Comment(strings.TrimSpace(s), CommentTypeMultiLine, indent, true)
			},
			"MCommentCallback": func(cb *Callback, indent int) string {
				var s string
				{
					var funcDoc = strings.TrimSpace(cb.Doc)
					if funcDoc != "" && funcDoc != "TODO" {
						s += funcDoc
					}
					s += "\n\nSee also @ref CallbackError."
				}
				for _, arg := range cb.Args {
					var argDoc = strings.TrimSpace(arg.Doc)
					var sArg string
					if argDoc != "" && argDoc != "TODO" {
						sArg += argDoc
					}

					if arg.PassedWithOwnership != nil {
						if *arg.PassedWithOwnership {
							sArg += "\nThis parameter is @ref PassedWithOwnership."
						} else {
							sArg += "\nThis parameter is @ref PassedWithoutOwnership."
						}
					}

					sArg = strings.TrimSpace(sArg)
					if sArg != "" {
						s += "\n\n@param " + CamelCase(arg.Name) + "\n" + sArg
					}
				}
				return Comment(strings.TrimSpace(s), CommentTypeMultiLine, indent, true)
			},
			"MCommentMember": func(member *ParameterType, indent int) string {
				var s string

				var srcDoc = strings.TrimSpace(member.Doc)
				if srcDoc != "" && srcDoc != "TODO" {
					s += srcDoc
				}

				switch member.Type {
				case "nullable_string":
					s += "\n\nThis is a \\ref NullableInputString."
				case "string_with_default_empty":
					s += "\n\nThis is a \\ref NonNullInputString."
				case "out_string":
					s += "\n\nThis is an \\ref OutputString."
				}

				s += "\n\nThe `INIT` macro sets this to " + g.DefaultValue(*member, true /* isDocString */) + "."

				if member.PassedWithOwnership != nil {
					panic("invalid")
				}

				return Comment(strings.TrimSpace(s), CommentTypeMultiLine, indent, true)
			},
			"MCommentStruct": func(st *Struct, indent int) string {
				var s string

				var srcDoc = strings.TrimSpace(st.Doc)
				if srcDoc != "" && srcDoc != "TODO" {
					s += srcDoc
				}

				s += "\n\nDefault values can be set using @ref WGPU_" + ConstantCase(st.Name) + "_INIT as initializer."

				return Comment(strings.TrimSpace(s), CommentTypeMultiLine, indent, true)
			},
			"ConstantCase": ConstantCase,
			"PascalCase":   PascalCase,
			"CamelCase":    CamelCase,
			"CType":        g.CType,
			"CValue":       g.CValue,
			"EnumValue":    g.EnumValue,
			"BitflagValue": g.BitflagValue,
			"IsArray": func(typ string) bool {
				return arrayTypeRegexp.Match([]byte(typ))
			},
			"ArrayType": func(typ string, pointer PointerType) string {
				matches := arrayTypeRegexp.FindStringSubmatch(typ)
				if len(matches) == 2 {
					return g.CType(matches[1], pointer, "")
				}
				return ""
			},
			"Singularize": Singularize,
			"IsLast":      func(i int, s any) bool { return i == reflect.ValueOf(s).Len()-1 },
			"FunctionReturns": func(f Function) string {
				if f.Callback != nil {
					return "WGPUFuture"
				}
				if f.Returns != nil {
					return g.CType(f.Returns.Type, f.Returns.Pointer, "")
				}
				return "void"
			},
			"FunctionArgs":            g.FunctionArgs,
			"CallbackArgs":            g.CallbackArgs,
			"StructMember":            g.StructMember,
			"StructMemberArrayCount":  g.StructMemberArrayCount,
			"StructMemberArrayData":   g.StructMemberArrayData,
			"StructMemberInitializer": g.StructMemberInitializer,
		})
	t, err := t.Parse(tmpl)
	if err != nil {
		return fmt.Errorf("GenCHeader: failed to parse template: %w", err)
	}
	if err := t.Execute(dst, g); err != nil {
		return fmt.Errorf("GenCHeader: failed to execute template: %w", err)
	}
	return nil
}

func (g *Generator) CValue(s string) (string, error) {
	switch s {
	case "usize_max":
		return "SIZE_MAX", nil
	case "uint32_max":
		return "UINT32_MAX", nil
	case "uint64_max":
		return "UINT64_MAX", nil
	case "nan":
		return "NAN", nil
	default:
		var num string
		var base int
		if strings.HasPrefix(s, "0x") {
			base = 16
			num = strings.TrimPrefix(s, "0x")
		} else {
			base = 10
			num = s
		}
		v, err := strconv.ParseUint(num, base, 64)
		if err != nil {
			return "", fmt.Errorf("CValue: failed to parse \"%s\": %w", s, err)
		}
		var suffix string
		if v <= math.MaxUint32 {
			suffix = "UL"
		} else {
			suffix = "ULL"
		}
		return "0x" + strconv.FormatUint(v, 16) + suffix, nil
	}
}

func (g *Generator) CType(typ string, pointerType PointerType, suffix string) string {
	appendModifiers := func(s string, pointerType PointerType) string {
		var sb strings.Builder
		sb.WriteString(s)
		switch pointerType {
		case PointerTypeImmutable:
			sb.WriteString(" const *")
		case PointerTypeMutable:
			sb.WriteString(" *")
		}
		return sb.String()
	}
	switch typ {
	case "bool":
		return appendModifiers("WGPUBool", pointerType)
	case "nullable_string", "string_with_default_empty", "out_string":
		return "WGPUStringView"
	case "uint16":
		return appendModifiers("uint16_t", pointerType)
	case "uint32":
		return appendModifiers("uint32_t", pointerType)
	case "uint64":
		return appendModifiers("uint64_t", pointerType)
	case "usize":
		return appendModifiers("size_t", pointerType)
	case "int16":
		return appendModifiers("int16_t", pointerType)
	case "int32":
		return appendModifiers("int32_t", pointerType)
	case "float32":
		return appendModifiers("float", pointerType)
	case "float64":
		return appendModifiers("double", pointerType)
	case "c_void":
		return appendModifiers("void", pointerType)
	}

	switch {
	case strings.HasPrefix(typ, "enum."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "enum.")) + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "typedef."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "typedef.")) + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "bitflag."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "bitflag.")) + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "struct."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "struct.")) + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "function_type."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "function_type.")) + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "callback."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "callback.")) + "Callback" + suffix
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "object."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "object.")) + suffix
		return appendModifiers(ctype, pointerType)
	default:
		return ""
	}
}

func (g *Generator) FunctionArgs(f Function, o *Object) string {
	sb := &strings.Builder{}
	if o != nil {
		typePrefix := g.TypePrefixForNamespace(o.Namespace)
		if len(f.Args) > 0 {
			fmt.Fprintf(sb, "WGPU%s %s, ", PascalCase(typePrefix + o.Name), CamelCase(o.Name))
		} else {
			fmt.Fprintf(sb, "WGPU%s %s", PascalCase(typePrefix + o.Name), CamelCase(o.Name))
		}
	}
	for i, arg := range f.Args {
		if arg.Optional {
			sb.WriteString("WGPU_NULLABLE ")
		}
		typePrefix := g.TypePrefixForNamespace(arg.Namespace)
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(sb, "%s %s", g.CType(typePrefix + matches[1], arg.Pointer, ""), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(sb, "%s %s", g.CType(typePrefix + arg.Type, arg.Pointer, ""), CamelCase(arg.Name))
		}
		if i != len(f.Args)-1 {
			sb.WriteString(", ")
		}
	}
	if f.Callback != nil {
		fmt.Fprintf(sb, ", %s callbackInfo", g.CType(*f.Callback, "", "Info"))
	}
	return sb.String()
}

func (g *Generator) CallbackArgs(f Callback) string {
	sb := &strings.Builder{}
	for _, arg := range f.Args {
		if arg.Optional {
			sb.WriteString("WGPU_NULLABLE ")
		}
		typePrefix := g.TypePrefixForNamespace(arg.Namespace)
		var structPrefix string
		if strings.HasPrefix(arg.Type, "struct.") {
			structPrefix = "struct "
		}
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(sb, "%s%s %s, ", structPrefix, g.CType(typePrefix + matches[1], arg.Pointer, ""), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(sb, "%s%s %s, ", structPrefix, g.CType(typePrefix + arg.Type, arg.Pointer, ""), CamelCase(arg.Name))
		}
	}
	sb.WriteString("WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2")
	return sb.String()
}

func (g *Generator) EnumValue(prefix string, e Enum, entryIndex int) (string, error) {
	var entryValue uint16
	entry := e.Entries[entryIndex]
	if entry.Value == "" {
		entryValue = uint16(entryIndex)
	} else {
		var num string
		var base int
		if strings.HasPrefix(entry.Value, "0x") {
			base = 16
			num = strings.TrimPrefix(entry.Value, "0x")
		} else {
			base = 10
			num = entry.Value
		}
		value, err := strconv.ParseUint(num, base, 16)
		if err != nil {
			return "", err
		}
		entryValue = uint16(value)
	}
	return fmt.Sprintf("%s%.4X", prefix, entryValue), nil
}

func bitflagEntryValue(entry BitflagEntry, entryIndex int) (uint64, error) {
	if entry.Value == "" {
		value := uint64(math.Pow(2, float64(entryIndex-1)))
		return value, nil
	} else {
		var num string
		var base int
		if strings.HasPrefix(entry.Value, "0x") {
			base = 16
			num = strings.TrimPrefix(entry.Value, "0x")
		} else {
			base = 10
			num = entry.Value
		}
		return strconv.ParseUint(num, base, 64)
	}
}

func (g *Generator) BitflagValue(b Bitflag, entryIndex int) (string, error) {
	entry := b.Entries[entryIndex]

	var value uint64
	var entryComment string
	if len(entry.ValueCombination) > 0 {
		if entry.Value != "" {
			return "", fmt.Errorf("BitflagValue: found conflicting 'value' and 'value_combination' in '%s'", b.Name)
		}
		entryComment += " /* "
		for valueIndex, v := range entry.ValueCombination {
			// find the value by searching in b, bitwise-OR it into the result
			for searchIndex, search := range b.Entries {
				if search.Name == v {
					searchValue, err := bitflagEntryValue(search, searchIndex)
					if err != nil {
						return "", nil
					}
					value |= searchValue
					break
				}
			}
			// construct comment
			if g.ExtPrefix != "" {
				entryComment += PascalCase(g.ExtPrefix + "_" + v)
			} else {
				entryComment += PascalCase(v)
			}
			if valueIndex != len(entry.ValueCombination)-1 {
				entryComment += " | "
			}
		}
		entryComment += " */"
	} else {
		var err error
		value, err = bitflagEntryValue(entry, entryIndex)
		if err != nil {
			return "", nil
		}
	}
	entryValue := fmt.Sprintf("0x%.16X", value) + entryComment
	return entryValue, nil
}

func (g *Generator) TypePrefixForNamespace(namespace string) string {
	switch namespace {
	case "":
		return g.ExtPrefix + "_"
	case "webgpu":
		return ""
	default:
		return namespace + "_"
	}
}

func (g *Generator) StructMember(s Struct, memberIndex int) (string, error) {
	member := s.Members[memberIndex]
	typePrefix := g.TypePrefixForNamespace(member.Namespace)

	matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
	if len(matches) == 2 {
		panic("StructMember used on array type")
	}

	sb := &strings.Builder{}
	if member.Optional {
		sb.WriteString("WGPU_NULLABLE ")
	}
	if strings.HasPrefix(member.Type, "callback.") {
		fmt.Fprintf(sb, "%s %s;", g.CType(typePrefix + member.Type, "", "Info"), CamelCase(member.Name))
	} else {
		fmt.Fprintf(sb, "%s %s;", g.CType(typePrefix + member.Type, member.Pointer, ""), CamelCase(member.Name))
	}
	return sb.String(), nil
}

func (g *Generator) StructMemberArrayCount(s Struct, memberIndex int) (string, error) {
	member := s.Members[memberIndex]

	matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
	if len(matches) != 2 {
		panic("StructMemberArrayCount used on non-array")
	}

	return fmt.Sprintf("size_t %sCount;", CamelCase(Singularize(member.Name))), nil
}

func (g *Generator) StructMemberArrayData(s Struct, memberIndex int) (string, error) {
	member := s.Members[memberIndex]
	typePrefix := g.TypePrefixForNamespace(member.Namespace)

	matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
	if len(matches) != 2 {
		panic("StructMemberArrayCount used on non-array")
	}

	sb := &strings.Builder{}
	if member.Optional {
		sb.WriteString("WGPU_NULLABLE ")
	}
	fmt.Fprintf(sb, "%s %s;", g.CType(typePrefix + matches[1], member.Pointer, ""), CamelCase(member.Name))
	return sb.String(), nil
}

func (g *Generator) StructMemberInitializer(s Struct, memberIndex int) (string, error) {
	member := s.Members[memberIndex]
	sb := &strings.Builder{}
	matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
	if len(matches) == 2 {
		fmt.Fprintf(sb, "/*.%sCount=*/0 _wgpu_COMMA \\\n", CamelCase(Singularize(member.Name)))
		fmt.Fprintf(sb, "    /*.%s=*/NULL _wgpu_COMMA \\", CamelCase(member.Name))
	} else {
		fmt.Fprintf(sb, "/*.%s=*/%s _wgpu_COMMA \\", CamelCase(member.Name), g.DefaultValue(member, false /* isDocString */))
	}
	return sb.String(), nil
}

func (g *Generator) DefaultValue(member ParameterType, isDocString bool) string {
	ref := func(s string) string {
		if isDocString {
			return "@ref " + s
		} else {
			return s
		}
	}
	literal := func(s string) string {
		if isDocString {
			return "`" + s + "`"
		} else {
			return s
		}
	}

	switch {
	case member.Pointer != "":
		if member.Default != nil {
			panic("pointer type should not have a default")
		}
		return literal("NULL")

	// Cases that may have member.Default
	case strings.HasPrefix(member.Type, "enum."):
		if member.Default == nil {
			if member.Type == "enum.optional_bool" {
				// This Undefined is a special one that is not the zero-value, so that
				// a stdbool.h bool cast correctly to WGPUOptionalBool; this means we
				// must explicitly initialize it
				return ref("WGPUOptionalBool_Undefined")
			} else if isDocString {
				return "(@ref WGPU" + PascalCase(strings.TrimPrefix(member.Type, "enum.")) + ")0"
			} else {
				return "_wgpu_ENUM_ZERO_INIT(WGPU" + PascalCase(strings.TrimPrefix(member.Type, "enum.")) + ")"
			}
		} else {
			return ref("WGPU" + PascalCase(strings.TrimPrefix(member.Type, "enum.")) + "_" + PascalCase(*member.Default))
		}
	case strings.HasPrefix(member.Type, "bitflag."):
		if member.Default == nil {
			return ref("WGPU" + PascalCase(strings.TrimPrefix(member.Type, "bitflag.")) + "_None")
		} else {
			return ref("WGPU" + PascalCase(strings.TrimPrefix(member.Type, "bitflag.")) + "_" + PascalCase(*member.Default))
		}
	case member.Type == "uint16", member.Type == "uint32", member.Type == "uint64", member.Type == "usize", member.Type == "int32":
		if member.Default == nil {
			return literal("0")
		} else if strings.HasPrefix(*member.Default, "constant.") {
			return ref("WGPU_" + ConstantCase(strings.TrimPrefix(*member.Default, "constant.")))
		} else {
			return literal(*member.Default)
		}
	case member.Type == "float32":
		if member.Default == nil {
			return literal("0.f")
		} else if strings.HasPrefix(*member.Default, "constant.") {
			return ref("WGPU_" + ConstantCase(strings.TrimPrefix(*member.Default, "constant.")))
		} else if strings.Contains(*member.Default, ".") {
			return literal(*member.Default + "f")
		} else {
			return literal(*member.Default + ".f")
		}
	case member.Type == "float64":
		if member.Default == nil {
			return literal("0.")
		} else if strings.HasPrefix(*member.Default, "constant.") {
			return ref("WGPU_" + ConstantCase(strings.TrimPrefix(*member.Default, "constant.")))
		} else {
			return literal(*member.Default)
		}
	case member.Type == "bool":
		if member.Default == nil {
			return literal("0")
		} else if strings.HasPrefix(*member.Default, "constant.") {
			return ref("WGPU_" + ConstantCase(strings.TrimPrefix(*member.Default, "constant.")))
		} else if *member.Default == "true" {
			return literal("1")
		} else if *member.Default == "false" {
			return literal("0")
		} else {
			return *member.Default
		}
	case member.Default != nil:
		panic(fmt.Errorf("type %s should not have a default", member.Type))

	// Cases that should not have member.Default
	case strings.HasPrefix(member.Type, "struct."):
		if member.Optional {
			return literal("NULL")
		} else {
			typ := strings.TrimPrefix(member.Type, "struct.")
			return ref("WGPU_" + g.ConstantExtPrefix() + ConstantCase(typ) + "_INIT")
		}
	case strings.HasPrefix(member.Type, "callback."):
		typ := strings.TrimPrefix(member.Type, "callback.")
		return ref("WGPU_" + g.ConstantExtPrefix() + ConstantCase(typ) + "_CALLBACK_INFO" + "_INIT")
	case strings.HasPrefix(member.Type, "object."):
		return literal("NULL")
	case strings.HasPrefix(member.Type, "array<"):
		return literal("NULL")
	case member.Type == "out_string", member.Type == "string_with_default_empty", member.Type == "nullable_string":
		return ref("WGPU_STRING_VIEW_INIT")
	case member.Type == "c_void":
		return literal("NULL")
	default:
		panic("invalid prefix: " + member.Type + " in member " + member.Name)
	}
}

func (g *Generator) ConstantExtPrefix() string {
	if g.ExtPrefix != "" {
		return ConstantCase(g.ExtPrefix) + "_"
	} else {
		return ""
	}
}
