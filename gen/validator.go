package main

import (
	"fmt"
	"os"

	"github.com/goccy/go-yaml"
	"github.com/santhosh-tekuri/jsonschema/v5"
	_ "github.com/santhosh-tekuri/jsonschema/v5/httploader"
)

func ValidateYaml(schemaPath string, yamlPath string) error {
	yamlFile, err := os.ReadFile(yamlPath)
	if err != nil {
		return fmt.Errorf("ValidateYaml: %w", err)
	}
	var yml map[string]any
	if err := yaml.Unmarshal(yamlFile, &yml); err != nil {
		return fmt.Errorf("ValidateYaml: %w", err)
	}

	schema := jsonschema.MustCompile(schemaPath)
	if err := schema.Validate(yml); err != nil {
		return fmt.Errorf("ValidateYaml: %w", err)
	}

	// TODO: add dependency check validations
	return nil
}
