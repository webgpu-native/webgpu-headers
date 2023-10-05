# WebGPU headers

This repository contains C headers equivalent to the [WebGPU](https://gpuweb.github.io/gpuweb/) API and (soon) documentation on the native specificities of the headers.

While WebGPU is a JavaScript API made for the Web, it is a good tradeoff of ergonomic, efficient and portable graphics API.
Almost all of its concepts are not specific to the Web platform and the headers replicate them exactly, while adding capabilities to interact with native concepts (like windows).

All of the API is defined in the [webgpu.h](./webgpu.h) header.

Implementations of this header include:

 - [Dawn](https://dawn.googlesource.com/dawn) (C++), Chromium's WebGPU implementation library.
 - [wgpu](https://github.com/gfx-rs/wgpu-native) (Rust), Firefox's WebGPU impelementation library.
 - [Emscripten](https://github.com/emscripten-core/emscripten/blob/main/src/library_webgpu.js) translates [webgpu.h](./webgpu.h) calls to JavaScript WebGPU calls when compiling to WASM
