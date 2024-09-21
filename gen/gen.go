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
	ExtSuffix  string
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
			"MCommentEnum": func(v string, indent int, prefix string, e Enum, entryIndex int) string {
				if v == "" || strings.TrimSpace(v) == "TODO" {
					return ""
				}
				value, _ := g.EnumValue(prefix, e, entryIndex)
				return Comment("`"+value+"`.\n"+v, CommentTypeMultiLine, indent, true)
			},
			"MCommentBitflag": func(v string, indent int, b Bitflag, entryIndex int) string {
				if v == "" || strings.TrimSpace(v) == "TODO" {
					return ""
				}
				value, _ := g.BitflagValue(b, entryIndex)
				return Comment("`"+value+"`.\n"+v, CommentTypeMultiLine, indent, true)
			},
			"MCommentFunction": func(funcDoc string, indent int, returns *ParameterType) string {
				var s string
				funcDoc = strings.TrimSpace(funcDoc)
				if funcDoc != "" && funcDoc != "TODO" {
					s += funcDoc
				}
				if returns != nil {
					returnsDoc := strings.TrimSpace(returns.Doc)
					if returnsDoc != "" && returnsDoc != "TODO" {
						s += "\n\n@returns " + returnsDoc
					}
				}
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
			"FunctionArgs": g.FunctionArgs,
			"CallbackArgs": g.CallbackArgs,
			"StructMember": g.StructMember,
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
	case "string":
		return appendModifiers("char", PointerTypeImmutable)
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
		var typeSuffix string
		if o.Namespace == "" {
			typeSuffix = ConstantCase(g.ExtSuffix)
		} else if o.Namespace != "webgpu" {
			typeSuffix = ConstantCase(o.Namespace)
		}
		if len(f.Args) > 0 {
			fmt.Fprintf(sb, "WGPU%s%s %s, ", PascalCase(o.Name), typeSuffix, CamelCase(o.Name))
		} else {
			fmt.Fprintf(sb, "WGPU%s%s %s", PascalCase(o.Name), typeSuffix, CamelCase(o.Name))
		}
	}
	for i, arg := range f.Args {
		if arg.Optional {
			sb.WriteString("WGPU_NULLABLE ")
		}
		var typeSuffix string
		if arg.Namespace == "" {
			typeSuffix = ConstantCase(g.ExtSuffix)
		} else if arg.Namespace != "webgpu" {
			typeSuffix = ConstantCase(arg.Namespace)
		}
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(sb, "%s %s", g.CType(matches[1], arg.Pointer, typeSuffix), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(sb, "%s %s", g.CType(arg.Type, arg.Pointer, typeSuffix), CamelCase(arg.Name))
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
		var typeSuffix string
		if arg.Namespace == "" {
			typeSuffix = ConstantCase(g.ExtSuffix)
		} else if arg.Namespace != "webgpu" {
			typeSuffix = ConstantCase(arg.Namespace)
		}
		var structPrefix string
		if strings.HasPrefix(arg.Type, "struct.") {
			structPrefix = "struct "
		}
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(sb, "%s%s %s, ", structPrefix, g.CType(matches[1], arg.Pointer, typeSuffix), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(sb, "%s%s %s, ", structPrefix, g.CType(arg.Type, arg.Pointer, typeSuffix), CamelCase(arg.Name))
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
			entryComment += PascalCase(v)
			if g.ExtSuffix != "" {
				entryComment += "_" + g.ExtSuffix
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

func (g *Generator) StructMember(s Struct, memberIndex int) (string, error) {
	member := s.Members[memberIndex]
	sb := &strings.Builder{}
	if member.Optional {
		sb.WriteString("WGPU_NULLABLE ")
	}
	var typeSuffix string
	if member.Namespace == "" {
		typeSuffix = ConstantCase(g.ExtSuffix)
	} else if member.Namespace != "webgpu" {
		typeSuffix = ConstantCase(member.Namespace)
	}
	matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
	if len(matches) == 2 {
		fmt.Fprintf(sb, "size_t %sCount;\n", CamelCase(Singularize(member.Name)))
		fmt.Fprintf(sb, "    %s %s;", g.CType(matches[1], member.Pointer, typeSuffix), CamelCase(member.Name))
	} else {
		if strings.HasPrefix(member.Type, "callback.") {
			fmt.Fprintf(sb, "%s %s;", g.CType(member.Type, "", "Info"), CamelCase(member.Name))
		} else {
			fmt.Fprintf(sb, "%s %s;", g.CType(member.Type, member.Pointer, typeSuffix), CamelCase(member.Name))
		}
	}
	return sb.String(), nil
}
