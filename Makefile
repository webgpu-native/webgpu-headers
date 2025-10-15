.PHONY: all all-help-message help check-schema fix gen gen-check doc

# default target if you just type `make`
all: all-help-message gen fix doc

# help message before starting `make all`
all-help-message: help
	@echo 'Running default targets: gen fix doc'

help:
	@echo 'Targets are: all, help, gen, fix, gen-check, doc'

# Validate schema and regenerate JSON and header from YAML
gen: schema.json webgpu.yml tests/extensions/extension.yml
	go run ./gen -schema schema.json \
		-yaml webgpu.yml \
		-outjson webgpu.json \
		-header webgpu.h \
		-yaml tests/extensions/extension.yml \
		-outjson tests/extensions/extension.json \
		-header tests/extensions/webgpu_extension.h

# Regenerate files (to validate schema) then autoformat YAML
fix: gen
	go run ./fix -yaml webgpu.yml
	go run ./fix -yaml tests/extensions/extension.yml

# Verify that generation and autoformat are up to date (used for pull request checks)
gen-check: fix gen
	@git diff --quiet -- webgpu.h || {                                                       \
		echo "error: The re-generated header from yml doesn't match the checked-in version"; \
		git diff -- webgpu.h;                                                                \
		exit 1;                                                                              \
	}
	@git diff --quiet -- webgpu.json || {                                                                 \
		echo "error: The re-translated webgpu.json from webgpu.yml doesn't match the checked-in version"; \
		git diff -- webgpu.json;                                                                          \
		exit 1;                                                                                           \
	}
	@git diff --quiet -- webgpu.yml || {                          \
		echo "error: Please re-run 'make fix' to format the yml"; \
		git diff -- webgpu.yml;                                   \
		exit 1;                                                   \
	}
	@git diff --quiet -- tests/extensions/webgpu_extension.h || {                                      \
		echo "error: The re-generated extension header from yml doesn't match the checked-in version"; \
		git diff -- tests/extensions/webgpu_extension.h;                                               \
		exit 1;                                                                                        \
	}
	@git diff --quiet -- tests/extensions/webgpu_extension.json || {                                  \
		echo "error: The re-translated extension json from yml doesn't match the checked-in version"; \
		git diff -- tests/extensions/webgpu_extension.json;                                           \
		exit 1;                                                                                       \
	}
	@git diff --quiet -- tests/extensions/extension.yml || {                \
		echo "error: Please re-run 'make fix' to format the extension yml"; \
		git diff -- tests/extensions/extension.yml;                         \
		exit 1;                                                             \
	}

doc: webgpu.h Doxyfile
	doxygen Doxyfile
	# Verify that no ` or :: made it through into the final docs
	! grep -RE '`|>::' doc/generated/**/*.html
