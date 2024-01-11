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
	schemaPath string
	headerPath string
	yamlPath   string
)

func main() {
	flag.StringVar(&yamlPath, "yaml", "", "path of the yaml spec")
	flag.StringVar(&schemaPath, "schema", "", "path of the json schema")
	flag.StringVar(&headerPath, "header", "", "output path of the header")
	flag.Parse()
	if schemaPath == "" || headerPath == "" || yamlPath == "" {
		flag.Usage()
		os.Exit(1)
	}

	if err := ValidateYaml(schemaPath, yamlPath); err != nil {
		panic(err)
	}

	src, err := os.ReadFile(yamlPath)
	if err != nil {
		panic(err)
	}

	var yml Yml
	if err := yaml.Unmarshal(src, &yml); err != nil {
		panic(err)
	}

	SortAndTransform(&yml)

	dst, err := os.Create(headerPath)
	if err != nil {
		panic(err)
	}

	fileName := filepath.Base(yamlPath)
	fileNameSplit := strings.Split(fileName, ".")
	if len(fileNameSplit) != 2 {
		panic("got invalid file name: " + fileName)
	}

	var data Data
	data.Yml = &yml
	data.Name = fileNameSplit[0]
	if err := GenCHeader(&data, dst); err != nil {
		panic(err)
	}
}

func SortAndTransform(yml *Yml) {
	// Sort structs
	SortStructs(yml.Structs)
	// Sort constants
	slices.SortStableFunc(yml.Constants, func(a, b Constant) int {
		return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
	})
	// Sort enums
	slices.SortStableFunc(yml.Enums, func(a, b Enum) int {
		return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
	})
	// Sort bitflags
	slices.SortStableFunc(yml.Bitflags, func(a, b Bitflag) int {
		return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
	})

	for _, s := range yml.Structs {
		if s.FreeMembers {
			yml.Objects = append(yml.Objects, Object{
				IsStruct: true,
				Name:     s.Name,
				Methods:  []Function{{Name: "free_members"}},
			})
		}
	}

	// Sort objects
	slices.SortStableFunc(yml.Objects, func(a, b Object) int {
		return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
	})
	// Sort methods
	for _, obj := range yml.Objects {
		slices.SortStableFunc(obj.Methods, func(a, b Function) int {
			return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
		})
	}
}

// Merges multiple yaml specs to generate a single header
//
// func ParseAndMergeYamls(yamlPaths []string, yml *Yml) {
// 	constants := make(map[string]Constant)
// 	enums := make(map[string]Enum)
// 	bitflags := make(map[string]Bitflag)
// 	functionTypes := make(map[string]Function)
// 	structs := make(map[string]Struct)
// 	functions := make(map[string]Function)
// 	objects := make(map[string]Object)

// 	for _, yamlPath := range yamlPaths {
// 		src, err := os.ReadFile(yamlPath)
// 		if err != nil {
// 			panic(err)
// 		}

// 		var data Yml
// 		if err := yaml.Unmarshal(src, &data); err != nil {
// 			panic(err)
// 		}

// 		yml.Copyrights = append(yml.Copyrights, data.Copyright)

// 		for _, c := range data.Constants {
// 			if _, ok := constants[c.Name]; ok {
// 				panic(fmt.Sprintf("merge: constants.%s in %s was already found previously while parsing, duplicates are not allowed", c.Name, yamlPath))
// 			}
// 			constants[c.Name] = c
// 		}
// 		for _, enum := range data.Enums {
// 			if prevEnum, ok := enums[enum.Name]; ok {
// 				for _, entry := range enum.Entries {
// 					if slices.ContainsFunc(prevEnum.Entries, func(e EnumEntry) bool { return e.Name == entry.Name }) {
// 						panic(fmt.Sprintf("merge: enums.%s.%s in %s was already found previously while parsing, duplicates are not allowed", enum.Name, entry.Name, yamlPath))
// 					}
// 					entry.ValuePrefix = data.EnumPrefix
// 					prevEnum.Entries = append(prevEnum.Entries, entry)
// 				}
// 				enums[enum.Name] = prevEnum
// 			} else {
// 				for i := range enum.Entries {
// 					enum.Entries[i].ValuePrefix = data.EnumPrefix
// 				}
// 				enums[enum.Name] = enum
// 			}
// 		}
// 		for _, bf := range data.Bitflags {
// 			if prevBf, ok := bitflags[bf.Name]; ok {
// 				for _, entry := range bf.Entries {
// 					if slices.ContainsFunc(prevBf.Entries, func(e BitflagEntry) bool { return e.Name == entry.Name }) {
// 						panic(fmt.Sprintf("merge: bitflags.%s.%s in %s was already found previously while parsing, duplicates are not allowed", bf.Name, entry.Name, yamlPath))
// 					}
// 					prevBf.Entries = append(prevBf.Entries, entry)
// 				}
// 				bitflags[bf.Name] = prevBf
// 			} else {
// 				bitflags[bf.Name] = bf
// 			}
// 		}
// 		for _, ft := range data.FunctionTypes {
// 			if _, ok := functionTypes[ft.Name]; ok {
// 				panic(fmt.Sprintf("merge: function_types.%s in %s was already found previously while parsing, duplicates are not allowed", ft.Name, yamlPath))
// 			}
// 			functionTypes[ft.Name] = ft
// 		}
// 		for _, s := range data.Structs {
// 			if _, ok := structs[s.Name]; ok {
// 				panic(fmt.Sprintf("merge: structs.%s in %s was already found previously while parsing, duplicates are not allowed", s.Name, yamlPath))
// 			}
// 			structs[s.Name] = s
// 		}
// 		for _, f := range data.Functions {
// 			if _, ok := functions[f.Name]; ok {
// 				panic(fmt.Sprintf("merge: functions.%s in %s was already found previously while parsing, duplicates are not allowed", f.Name, yamlPath))
// 			}
// 			functions[f.Name] = f
// 		}
// 		for _, o := range data.Objects {
// 			if prevObj, ok := objects[o.Name]; ok {
// 				for _, method := range o.Methods {
// 					if slices.ContainsFunc(prevObj.Methods, func(f Function) bool { return f.Name == method.Name }) {
// 						panic(fmt.Sprintf("merge: objects.%s.%s in %s was already found previously while parsing, duplicates are not allowed", o.Name, method.Name, yamlPath))
// 					}
// 					prevObj.Methods = append(prevObj.Methods, method)
// 				}
// 				objects[o.Name] = prevObj
// 			} else {
// 				objects[o.Name] = o
// 			}
// 		}
// 	}

// 	for _, c := range constants {
// 		yml.Constants = append(yml.Constants, c)
// 	}
// 	for _, e := range enums {
// 		yml.Enums = append(yml.Enums, e)
// 	}
// 	for _, b := range bitflags {
// 		yml.Bitflags = append(yml.Bitflags, b)
// 	}
// 	for _, ft := range functionTypes {
// 		yml.FunctionTypes = append(yml.FunctionTypes, ft)
// 	}
// 	for _, f := range functions {
// 		yml.Functions = append(yml.Functions, f)
// 	}
// 	for _, s := range structs {
// 		yml.Structs = append(yml.Structs, s)
// 	}
// 	for _, o := range objects {
// 		yml.Objects = append(yml.Objects, o)
// 	}
// }
