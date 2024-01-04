package main

import (
	"os"

	"github.com/goccy/go-yaml"
	"github.com/santhosh-tekuri/jsonschema/v5"
	_ "github.com/santhosh-tekuri/jsonschema/v5/httploader"
)

func MustValidateYaml(schemaPath string, yamlPath string) {
	yamlFile, err := os.ReadFile(yamlPath)
	if err != nil {
		panic(err)
	}
	var yml map[string]any
	if err := yaml.Unmarshal(yamlFile, &yml); err != nil {
		panic(err)
	}

	schema := jsonschema.MustCompile(schemaPath)
	if err := schema.Validate(yml); err != nil {
		panic(err)
	}

	// TODO: add dependency check validations
}
