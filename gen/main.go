package main

import (
	"flag"
	"os"
	"path/filepath"
	"slices"
	"strings"

	_ "embed"

	"github.com/goccy/go-yaml"
)

//go:embed cheader.tmpl
var tmpl string

var (
	schemaPath  string
	headerPaths StringListFlag
	yamlPaths   StringListFlag
	extPrefix   bool
)

func main() {
	flag.StringVar(&schemaPath, "schema", "", "path of the json schema")
	flag.Var(&yamlPaths, "yaml", "path of the yaml spec")
	flag.Var(&headerPaths, "header", "output path of the header")
	flag.BoolVar(&extPrefix, "extprefix", true, "append prefix to extension identifiers")
	flag.Parse()
	if schemaPath == "" || len(headerPaths) == 0 || len(yamlPaths) == 0 || len(headerPaths) != len(yamlPaths) {
		flag.Usage()
		os.Exit(1)
	}

	// Order matters for validation steps, so enforce it.
	if len(yamlPaths) > 1 && filepath.Base(yamlPaths[0]) != "webgpu.yml" {
		panic(`"webgpu.yml" must be the first sequence in the order`)
	}

	// Validate the yaml files (jsonschema, duplications)
	if err := ValidateYamls(schemaPath, yamlPaths); err != nil {
		panic(err)
	}

	// Generate the header files
	for i, yamlPath := range yamlPaths {
		headerPath := headerPaths[i]
		headerFileName := filepath.Base(headerPath)
		headerFileNameSplit := strings.Split(headerFileName, ".")
		if len(headerFileNameSplit) != 2 {
			panic("got invalid header file name: " + headerFileName)
		}

		src, err := os.ReadFile(yamlPath)
		if err != nil {
			panic(err)
		}

		dst, err := os.Create(headerPath)
		if err != nil {
			panic(err)
		}

		var yml Yml
		if err := yaml.Unmarshal(src, &yml); err != nil {
			panic(err)
		}

		SortAndTransform(&yml)

		prefix := ""
		if yml.Name != "webgpu" && extPrefix {
			prefix = yml.Name
		}
		g := &Generator{
			Yml:        &yml,
			HeaderName: headerFileNameSplit[0],
			ExtPrefix:  prefix,
		}
		if err := g.Gen(dst); err != nil {
			panic(err)
		}
	}
}

func UpperConcatCase(s string) string {
	return strings.ToUpper(PascalCase(s))
}

func SortAndTransform(yml *Yml) {
	// Sort structs
	SortStructs(yml.Structs)

	// Sort constants
	slices.SortStableFunc(yml.Constants, func(a, b Constant) int {
		return strings.Compare(UpperConcatCase(a.Name), UpperConcatCase(b.Name))
	})

	// Sort enums
	slices.SortStableFunc(yml.Enums, func(a, b Enum) int {
		// We want to generate extended enum declarations before the normal ones.
		if a.Extended && !b.Extended {
			return -1
		} else if !a.Extended && b.Extended {
			return 1
		}
		return strings.Compare(UpperConcatCase(a.Name), UpperConcatCase(b.Name))
	})

	// Sort bitflags
	slices.SortStableFunc(yml.Bitflags, func(a, b Bitflag) int {
		// We want to generate extended bitflag declarations before the normal ones.
		if a.Extended && !b.Extended {
			return -1
		} else if !a.Extended && b.Extended {
			return 1
		}
		return strings.Compare(UpperConcatCase(a.Name), UpperConcatCase(b.Name))
	})

	// Add free_member function for relevant structs
	for _, s := range yml.Structs {
		if s.FreeMembers {
			yml.Objects = append(yml.Objects, Object{
				Base:     Base{Name: s.Name, Namespace: s.Namespace},
				IsStruct: true,
				Methods: []Function{{
					Base: Base{
						Name:      "free_members",
						Namespace: s.Namespace,
						Doc:       "Frees members which were allocated by the API."},
				}},
			})
		}
	}

	// Sort objects
	slices.SortStableFunc(yml.Objects, func(a, b Object) int {
		return strings.Compare(UpperConcatCase(a.Name), UpperConcatCase(b.Name))
	})

	// Sort methods
	for _, obj := range yml.Objects {
		slices.SortStableFunc(obj.Methods, func(a, b Function) int {
			return strings.Compare(UpperConcatCase(a.Name), UpperConcatCase(b.Name))
		})
	}

	// Add add_ref and release methods for objects
	for i, o := range yml.Objects {
		if !o.Extended && !o.IsStruct {
			yml.Objects[i].Methods = append(yml.Objects[i].Methods,
				Function{
					Base: Base{
						Name:      "add_ref",
						Namespace: o.Namespace,
						Doc:       "TODO",
					},
				},
				Function{
					Base: Base{
						Name:      "release",
						Namespace: o.Namespace,
						Doc:       "TODO",
					},
				})
		}
	}
}
