# Multithreading {#Multithreading}

`webgpu.h` implementations are allowed to require that all returned objects, except for `WGPUInstance`, can only be used from the thread they were created on, causing undefined behavior otherwise.

Where multithreading is supported:

- The implementation must provide the documented @ref ThreadSafety guarantees.
- All objects must be freely usable on any thread at any time.
- State must be thread-global, except where otherwise defined.
    - For example, buffer map state is thread-global, and mapped memory ranges may be used from any thread.
    - Note: Error scope state is thread-local. See @ref ErrorScopes.

Native (non-Wasm) implementations **should** support multithreading.

## In WebAssembly

At the time of this writing, the JS WebGPU API is not multithreading-capable.
Initial `webgpu.h` implementations will not be multithreading-capable.

Wasm-on-JS implementations *may* implement multithreading by proxying calls to a single JS "thread", as long as the C API behavior is conformant.

Once the JS API is multithreading-capable, there are still expected to be some thread-local behaviors (such as buffer mapping state being thread-local). These limitations may still be exposed, but multithreading-capable Wasm-on-JS implementations may also avoid exposing them where feasible (e.g. by proxying all mapping calls to a single JS thread).

## Thread Safety {#ThreadSafety}

TODO

### Callback Reentrancy

See @ref CallbackReentrancy.
