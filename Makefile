.PHONY: gen gen-check doc

fix: webgpu.yml
	go run ./fix -yaml webgpu.yml

gen: schema.json webgpu.yml
	go run ./gen -schema schema.json -yaml webgpu.yml -header webgpu.h

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

doc: webgpu.h Doxyfile
	doxygen Doxyfile
