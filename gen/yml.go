package main

import (
	"math"
	"regexp"
	"slices"
	"strings"
)

type Yml struct {
	Copyright  string `yaml:"copyright"`
	Name       string `yaml:"name"`
	EnumPrefix string `yaml:"enum_prefix"`

	Constants     []Constant `yaml:"constants"`
	Typedefs      []Typedef  `yaml:"typedefs"`
	Enums         []Enum     `yaml:"enums"`
	Bitflags      []Bitflag  `yaml:"bitflags"`
	FunctionTypes []Function `yaml:"function_types"`
	Structs       []Struct   `yaml:"structs"`
	Functions     []Function `yaml:"functions"`
	Objects       []Object   `yaml:"objects"`
}

type Constant struct {
	Name  string `yaml:"name"`
	Value string `yaml:"value"`
	Doc   string `yaml:"doc"`
}

type Typedef struct {
	Name string `yaml:"name"`
	Doc  string `yaml:"doc"`
	Type string `yaml:"type"`
}

type Enum struct {
	Name     string      `yaml:"name"`
	Doc      string      `yaml:"doc"`
	Entries  []EnumEntry `yaml:"entries"`
	Extended bool        `yaml:"extended"`
}
type EnumEntry struct {
	Name  string `yaml:"name"`
	Doc   string `yaml:"doc"`
	Value string `yaml:"value"`
}

type Bitflag struct {
	Name     string         `yaml:"name"`
	Doc      string         `yaml:"doc"`
	Entries  []BitflagEntry `yaml:"entries"`
	Extended bool           `yaml:"extended"`
}
type BitflagEntry struct {
	Name             string   `yaml:"name"`
	Doc              string   `yaml:"doc"`
	Value            string   `yaml:"value"`
	ValueCombination []string `yaml:"value_combination"`
}

type PointerType string

const (
	PointerTypeMutable   PointerType = "mutable"
	PointerTypeImmutable PointerType = "immutable"
)

type ParameterType struct {
	Name      string      `yaml:"name"`
	Doc       string      `yaml:"doc"`
	Type      string      `yaml:"type"`
	Pointer   PointerType `yaml:"pointer"`
	Optional  bool        `yaml:"optional"`
	Namespace string      `yaml:"namespace"`
}

type Function struct {
	Name         string          `yaml:"name"`
	Doc          string          `yaml:"doc"`
	ReturnsAsync []ParameterType `yaml:"returns_async"`
	Returns      *ParameterType  `yaml:"returns"`
	Args         []ParameterType `yaml:"args"`
}

type Struct struct {
	Name        string          `yaml:"name"`
	Type        string          `yaml:"type"`
	Doc         string          `yaml:"doc"`
	FreeMembers bool            `yaml:"free_members"`
	Members     []ParameterType `yaml:"members"`
}

type Object struct {
	Name      string     `yaml:"name"`
	Doc       string     `yaml:"doc"`
	Methods   []Function `yaml:"methods"`
	Extended  bool       `yaml:"extended"`
	Namespace string     `yaml:"namespace"`

	IsStruct bool `yaml:"-"`
}

var arrayTypeRegexp = regexp.MustCompile(`array<([a-zA-Z0-9._]+)>`)

func SortStructs(structs []Struct) {
	type node struct {
		visited bool
		depth   int
		Struct
	}
	nodeMap := make(map[string]node, len(structs))
	for _, s := range structs {
		nodeMap[s.Name] = node{Struct: s}
	}

	slices.SortStableFunc(structs, func(a, b Struct) int {
		return strings.Compare(PascalCase(a.Name), PascalCase(b.Name))
	})

	var computeDepth func(string) int
	computeDepth = func(name string) int {
		if nodeMap[name].visited {
			return nodeMap[name].depth
		}

		maxDependentDepth := 0
		for _, member := range nodeMap[name].Members {
			if strings.HasPrefix(member.Type, "struct.") {
				dependentDepth := computeDepth(strings.TrimPrefix(member.Type, "struct."))
				maxDependentDepth = int(math.Max(float64(maxDependentDepth), float64(dependentDepth+1)))
			} else {
				matches := arrayTypeRegexp.FindStringSubmatch(member.Type)
				if len(matches) == 2 {
					typ := matches[1]
					if strings.HasPrefix(typ, "struct.") {
						dependentDepth := computeDepth(strings.TrimPrefix(typ, "struct."))
						maxDependentDepth = int(math.Max(float64(maxDependentDepth), float64(dependentDepth+1)))
					}
				}
			}
		}

		node := nodeMap[name]
		node.depth = maxDependentDepth
		node.visited = true
		nodeMap[name] = node
		return maxDependentDepth
	}

	for _, s := range structs {
		computeDepth(s.Name)
	}
	slices.SortStableFunc(structs, func(a, b Struct) int {
		return nodeMap[a.Name].depth - nodeMap[b.Name].depth
	})
}
