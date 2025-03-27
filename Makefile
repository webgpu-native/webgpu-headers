.PHONY: all all-help-message help gen gen-check doc

# default target if you just type `make`
all: all-help-message fix gen doc

# help message before starting `make all`
all-help-message: help
	@echo 'Running default targets: fix gen doc'

help:
	@echo 'Targets are: all, help, fix, gen, gen-check, doc'

fix: webgpu.yml
	go run ./fix -yaml webgpu.yml

gen: schema.json webgpu.yml tests/extensions/extension.yml
	go run ./gen -schema schema.json -yaml webgpu.yml -header webgpu.h -yaml tests/extensions/extension.yml -header tests/extensions/webgpu_extension.h

gen-check: fix gen
	@git diff --quiet -- webgpu.h || {                                                      \
		echo "error: The re-generated header from yml doesn't match the checked-in header"; \
		git diff -- webgpu.h;                                                               \
		exit 1;                                                                             \
	}
	@git diff --quiet -- webgpu.yml || {                          \
		echo "error: Please re-run 'make fix' to format the yml"; \
		git diff -- webgpu.yml;                                   \
		exit 1;                                                   \
	}
	@git diff --quiet -- tests/extensions/webgpu_extension.h || {                                       \
		echo "error: The re-generated extensions header from yml doesn't match the checked-in header"; \
		git diff -- tests/extensions/webgpu_extension.h;                                                \
		exit 1;                                                                                        \
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
