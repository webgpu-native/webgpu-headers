# WebGPU headers

This repository contains C headers equivalent to the [WebGPU](https://gpuweb.github.io/gpuweb/) API and (soon) documentation on the native specificities of the headers.

While WebGPU is a JavaScript API made for the Web, it is a good tradeoff of ergonomic, efficient and portable graphics API.
Almost all of its concepts are not specific to the Web platform and the headers replicate them exactly, while adding capabilities to interact with native concepts (like windows).

All of the API is defined in the [webgpu.h](./webgpu.h) header.

Implementations of this header include:

 - [Dawn](https://dawn.googlesource.com/dawn), Chromium's C++ WebGPU implementation library
 - [wgpu-native](https://github.com/gfx-rs/wgpu-native), Firefox's Rust WebGPU implementation library
 - [Emscripten](https://github.com/emscripten-core/emscripten/blob/main/src/library_webgpu.js) translates [webgpu.h](./webgpu.h) calls to JavaScript WebGPU calls when compiling to WASM

## Details

Here are some details about the structure of this repository.

### Main files

 - `webgpu.h` is the one and only header file that defines the WebGPU C API. Only this needs to be integrated in a C project that links against a WebGPU implementation.

 - `webgpu.yml` is the main machine-readable source of truth for the C API and its documentation (in [YAML](https://yaml.org/) format). It is used to generate the official `webgpu.h` header present in this repository, (will be used) to generate the official documentation, and may be used by any other third party to design tools and wrappers around WebGPU-Native.

 - `schema.json` is the [JSON schema](https://json-schema.org/) that formally specifies the structure of `webgpu.yml`.

### Generator

 - `Makefile` defines the rules to automatically generate `webgpu.h` from `webgpu.yml` and check the result.

 - `gen/` and the `go.*` files are the source code of the generator called by the `Makefile`.

 - `tests/compile` is used to check that the generated C header is indeed valid C/C++ code.

### Workflows

 - `.github/workflows` defines the automated processes that run upon new commits/PR, to check that changes in `webgpu.yml` and `webgpu.h` are consistent.

## Contributing

**Important** When submitting a change, one must modify both the `webgpu.yml` and `webgpu.h` files in a consistent way. One should first edit `webgpu.yml` (the source of truth), then run `make gen` to update `webgpu.h` and finally commit both changes together.
