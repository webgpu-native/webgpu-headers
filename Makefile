.PHONY: gen

gen: schema.json webgpu.yml
	go run ./gen -schema schema.json -yaml webgpu.yml -header webgpu.h

gen-check: gen
	@git diff --quiet -- webgpu.h || {                                                      \
		echo "error: The re-generated header from yml doesn't match the checked-in header"; \
		git diff -- webgpu.h;                                                               \
		exit 1;                                                                             \
	}
