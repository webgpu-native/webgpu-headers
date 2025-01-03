# Buffer Mapping {#BufferMapping}

## GetMappedRange/GetConstMappedRange Behavior {#GetMappedRangeBehavior}

@ref wgpuBufferGetMappedRange and @ref wgpuBufferGetConstMappedRange...:

- Return `NULL` with @ref ImplementationDefinedLogging if:
    - There is any content-timeline error, as defined in the WebGPU specification for `getMappedRange()` (buffer is not mapped, alignment constraints, overlaps, etc.)
        - **Except** for overlaps between *const* ranges, which are allowed in C *in non-Wasm targets only*.
            (Wasm does not allow this because const ranges do not exist in JS.)
    - @ref wgpuBufferGetMappedRange is called, but the buffer is not mapped with @ref WGPUMapMode_Write.
- Do not guarantee they will return any particular address value relative to another GetMappedRange call.
- Guarantee that the mapped pointer will be aligned to 16 bytes if the `MapAsync` and `GetMappedRange` offsets are also aligned to 16 bytes.

    More specifically: `GetMappedRange pointer` and `MapAsync offset + GetMappedRange offset` must be _congruent modulo_ `16`.

    - Implementations **should** try to guarantee better alignments (as large as 256 bytes) if possible without significant runtime overhead (e.g. allocating new memory and copying data).
