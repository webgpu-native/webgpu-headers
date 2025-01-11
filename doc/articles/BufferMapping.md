# Buffer Mapping {#BufferMapping}

## Mapped Range Behavior {#MappedRangeBehavior}

The @ref wgpuBufferGetMappedRange, @ref wgpuBufferGetConstMappedRange, @ref wgpuBufferReadMappedRange, and @ref wgpuBufferWriteMappedRange methods:

- Fail (return `NULL` or `WGPUStatus_Error`) with @ref ImplementationDefinedLogging if:
    - There is any content-timeline error, as defined in the WebGPU specification for `getMappedRange()`, given the same buffer, offset, and size (buffer is not mapped, alignment constraints, overlaps, etc.)
        - All four calls reserve a range which cannot be overlapped by any future call.
        - Note that implementations must validate overlap rules, even if they do not have such constraints or could avoid them.
    - @ref wgpuBufferGetMappedRange or @ref wgpuBufferWriteMappedRange is called, but the buffer is not mapped with @ref WGPUMapMode_Write.

@ref wgpuBufferGetMappedRange, @ref wgpuBufferGetConstMappedRange additionally:

- Do not guarantee they will return any particular address value relative to another GetMappedRange call.
- Guarantee that the mapped pointer will be aligned to 16 bytes if the `MapAsync` and `GetMappedRange` offsets are also aligned to 16 bytes.

    More specifically: `GetMappedRange pointer` and `MapAsync offset + GetMappedRange offset` must be _congruent modulo_ `16`.

    - Implementations **should** try to guarantee better alignments (as large as 256 bytes), if they can do so without significant runtime overhead (i.e. without allocating new memory and copying data).
