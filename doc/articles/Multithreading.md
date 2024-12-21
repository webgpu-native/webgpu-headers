# Multithreading {#Multithreading}

`webgpu.h` implementations are allowed to require that all returned objects, except for `WGPUInstance`, can only be used from the thread they were created on, causing undefined behavior otherwise.

Where multithreading is supported:

- The implementation must provide the documented @ref ThreadSafety guarantees.
- All objects must be freely usable on any thread at any time, except:
    - Where APIs are specified as being non-thread-safe, they must mutexed.
    - The exceptions for Wasm, below.
- State must be thread-global, except where otherwise defined.
    - For example, buffer map state is thread-global, and mapped memory ranges may be used from any thread.
    - Note: Error scope state is thread-local. See @ref ErrorScopes.

Native (non-Wasm) implementations **should** support multithreading.

## In WebAssembly

At the time of this writing, the JS WebGPU API is not multithreading-capable.
Initial `webgpu.h` implementations will not be multithreading-capable.

Wasm-on-JS implementations *may* implement multithreading by proxying calls to a single JS "thread", as long as the C API behavior is conformant.

Once the JS API is multithreading-capable, there are still expected to be some thread-local behaviors:

- Buffer mapping state may be thread-local.
    - Implementations *should* make this state thread-global if feasible (e.g. by proxying all mapping calls to a single JS thread).
- Any object which is non-shareable or non-transferable in JS may also be fully or partially non-shareable or non-transferable in Wasm (e.g. encoder objects may be thread-locked, similar to how they are not thread safe in `webgpu.h` in general). (In Rust terms, shareable = `Send`+`Sync`, transferable = `Send`.)
    - Implementations *may* make them shareable. (For example, proxying all encoder methods to a single thread would make them fully shareable but be inefficient; alternatively, encoder commands can be buffered, which might enable some multithreaded use-cases even if `Finish()` still must happen on the thread that created the encoder.)

## Thread Safety {#ThreadSafety}

TODO

### Callback Reentrancy

See @ref CallbackReentrancy.
