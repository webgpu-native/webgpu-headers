.PHONY: all all-help-message fix gen gen-check doc

# default target if you just type `make`
all: all-help-message fix gen doc

# help message before starting `make all`
all-help-message: help
	@echo 'Running default targets: fix gen doc'

help:
	@echo 'Targets are: all, help, fix, gen, gen-check, doc'

fix: webgpu.yml
	go run ../../fix -yaml webgpu-sample-extension.yml

gen: ../../schema.json webgpu-sample-extension.yml
	go run ../../gen -schema ../../schema.json -yaml webgpu-sample-extension.yml -header webgpu-sample-extension.h

gen-check: fix gen
	@git diff --quiet -- webgpu-sample-extension.h || {                                                      \
		echo "error: The re-generated header from yml doesn't match the checked-in header"; \
		git diff -- webgpu-sample-extension.h;                                                               \
		exit 1;                                                                             \
	}
	@git diff --quiet -- webgpu-sample-extension.yml || {                          \
		echo "error: Please re-run 'make fix' to format the yml"; \
		git diff -- webgpu-sample-extension.yml;                                   \
		exit 1;                                                   \
	}

doc: webgpu-sample-extension.h Doxyfile
	doxygen Doxyfile
	# Verify that no ` or :: made it through into the final docs
	! grep -RE '`|>::' doc/generated/**/*.html
