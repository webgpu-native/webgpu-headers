.PHONY: gen

gen: schema.json webgpu.yml
	go run ./gen -schema schema.json -yaml webgpu.yml -header webgpu.h
