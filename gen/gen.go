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

type Data struct {
	Name string
	*Yml
}

func GenCHeader(data *Data, dst io.Writer) error {
	t := template.
		New("").
		Funcs(template.FuncMap{
			"SComment":     func(v string, indent int) string { return Comment(v, CommentTypeSingleLine, indent, true) },
			"MComment":     func(v string, indent int) string { return Comment(v, CommentTypeMultiLine, indent, true) },
			"SCommentN":    func(v string, indent int) string { return Comment(v, CommentTypeSingleLine, indent, false) },
			"MCommentN":    func(v string, indent int) string { return Comment(v, CommentTypeMultiLine, indent, false) },
			"ConstantCase": ConstantCase,
			"PascalCase":   PascalCase,
			"CamelCase":    CamelCase,
			"CType":        CType,
			"CValue":       CValue,
			"BitFlagValue": func(index int) uint64 { return uint64(math.Pow(2, float64(index-1))) },
			"ParseUint": func(s string, bitSize int) uint64 {
				v, err := strconv.ParseUint(s, 10, bitSize)
				if err != nil {
					panic(err)
				}
				return v
			},
			"IsArray": func(typ string) bool {
				return arrayTypeRegexp.Match([]byte(typ))
			},
			"ArrayType": func(typ string, pointer PointerType) string {
				matches := arrayTypeRegexp.FindStringSubmatch(typ)
				if len(matches) == 2 {
					return CType(matches[1], pointer)
				}
				return ""
			},
			"Singularize": Singularize,
			"IsLast": func(i int, s interface{}) bool {
				return i == reflect.ValueOf(s).Len()-1
			},
			"FunctionReturns": func(f Function) string {
				if f.Returns != nil {
					return CType(f.Returns.Type, f.Returns.Pointer)
				}
				return "void"
			},
			"FunctionArgs": FunctionArgs,
			"CallbackArgs": CallbackArgs,
		})
	t, err := t.Parse(tmpl)
	if err != nil {
		return fmt.Errorf("GenCHeader: failed to parse template: %w", err)
	}
	if err := t.Execute(dst, data); err != nil {
		return fmt.Errorf("GenCHeader: failed to execute template: %w", err)
	}
	return nil
}

func CValue(s string) string {
	switch s {
	case "usize_max":
		return "SIZE_MAX"
	case "uint32_max":
		return "0xffffffffUL"
	case "uint64_max":
		return "0xffffffffffffffffULL"
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
			panic(fmt.Errorf("CValue: failed to parse \"%s\": %w", s, err))
		}
		var suffix string
		if v <= math.MaxUint32 {
			suffix = "UL"
		} else {
			suffix = "ULL"
		}
		return "0x" + strconv.FormatUint(v, 16) + suffix
	}
}

func CType(typ string, pointerType PointerType) string {
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
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "enum."))
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "bitflag."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "bitflag.")) + "Flags"
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "struct."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "struct."))
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "function_type."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "function_type."))
		return appendModifiers(ctype, pointerType)
	case strings.HasPrefix(typ, "object."):
		ctype := "WGPU" + PascalCase(strings.TrimPrefix(typ, "object."))
		return appendModifiers(ctype, pointerType)
	default:
		return ""
	}
}

func FunctionArgs(f Function, o *Object) string {
	var sb strings.Builder
	if o != nil {
		if len(f.Args) > 0 {
			fmt.Fprintf(&sb, "WGPU%s %s, ", PascalCase(o.Name), CamelCase(o.Name))
		} else {
			fmt.Fprintf(&sb, "WGPU%s %s", PascalCase(o.Name), CamelCase(o.Name))
		}
	}
	for i, arg := range f.Args {
		if arg.Optional {
			sb.WriteString("WGPU_NULLABLE ")
		}
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(&sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(&sb, "%s %s", CType(matches[1], arg.Pointer), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(&sb, "%s %s", CType(arg.Type, arg.Pointer), CamelCase(arg.Name))
		}
		if i != len(f.Args)-1 {
			sb.WriteString(", ")
		}
	}
	if len(f.ReturnsAsync) > 0 {
		var name string
		if o != nil {
			name = PascalCase(o.Name) + PascalCase(f.Name)
		} else {
			name = PascalCase(f.Name)
		}
		fmt.Fprintf(&sb, ", WGPU%sCallback callback, WGPU_NULLABLE void * userdata", name)
	}
	return sb.String()
}

func CallbackArgs(f Function) string {
	var sb strings.Builder
	for _, arg := range f.ReturnsAsync {
		if arg.Optional {
			sb.WriteString("WGPU_NULLABLE ")
		}
		var structPrefix string
		if strings.HasPrefix(arg.Type, "struct.") {
			structPrefix = "struct "
		}
		matches := arrayTypeRegexp.FindStringSubmatch(arg.Type)
		if len(matches) == 2 {
			fmt.Fprintf(&sb, "size_t %sCount, ", CamelCase(Singularize(arg.Name)))
			fmt.Fprintf(&sb, "%s%s %s, ", structPrefix, CType(matches[1], arg.Pointer), CamelCase(arg.Name))
		} else {
			fmt.Fprintf(&sb, "%s%s %s, ", structPrefix, CType(arg.Type, arg.Pointer), CamelCase(arg.Name))
		}
	}
	sb.WriteString("WGPU_NULLABLE void * userdata")
	return sb.String()
}
