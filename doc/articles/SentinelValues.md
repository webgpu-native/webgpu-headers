# Sentinel Values {#SentinelValues}

## Undefined

Since WebGPU is defined first as a JavaScript API, it uses the JavaScript value
`undefined` in many places to indicate the lack of a value.

This is usually used in dictionaries, where, for example, `{}` and
`{ powerPreference: undefined }` are equivalent, and distinct from both
`{ powerPreference: "high-performance" }` and `{ powerPreference: "low-power" }`.

It may also be used in functions/methods. For example, `GPUBuffer`'s
`getMappedRange(optional GPUSize64 offset = 0, optional GPUSize64 size)`
can be called equivalently as `b.getMappedRange()`, `b.getMappedRange(0)`,
`b.getMappedRange(undefined)`, or `b.getMappedRange(undefined, undefined)`.

To represent `undefined` in C, `webgpu.h` uses `*_UNDEFINED` sentinel numeric values
(generally `UINT32_MAX`, etc.) and `*_Undefined` enum values (generally `0`).

The place that uses the type will define what to do with an undefined value.
It may be:

- Required, in which case an error is produced.
- Defaulting, in which case it trivially defaults to some other value.
- Optional, in which case the API accepts the sentinel value and handles it
  (usually this is either a special value or it has more complex defaulting,
  for example depending on other values).

## Other sentinel values

Undefined values are also be used in C-specific ways in place of WebIDL's
more flexible typing:

- \ref WGPUVertexStepMode_VertexBufferNotUsed
- \ref WGPUBufferBindingType_BindingNotUsed
- \ref WGPUSamplerBindingType_BindingNotUsed
- \ref WGPUTextureSampleType_BindingNotUsed
- \ref WGPUStorageTextureAccess_BindingNotUsed
