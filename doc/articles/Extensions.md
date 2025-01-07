# Extensions {#Extensions}

`webgpu.h` is designed to be an extensible and forward-compatible API.
The following types of extensions are supported:

```
wgpuPrefixNewFunction

WGPUPrefixNewObject
wgpuPrefixNewObjectNewMethod
wgpuOldObjectPrefixNewMethod

WGPUPrefixNewEnum
WGPUPrefixNewEnum_NewValue
WGPUOldEnum_PrefixNewValue

WGPUPrefixNewStruct

WGPUPrefixNewBitflagType
WGPUPrefixNewBitflagType_NewValue
WGPUOldBitflagType_PrefixNewValue

WGPUPrefixNewCallback

WGPU_PREFIX_NEW_CONSTANT
```

("Prefix" is the name of the implementation that owns the extension, if any; see below.)

When an application is running against an unknown `webgpu.h` implementation, extension support may be detected at runtime as follows:

- New functions/methods may be runtime-detected by loading them dynamically, and checking whether loading succeeds. (@ref wgpuGetProcAddress() returns `NULL` for unknown function names.)
    - New objects may be detected by the presence of the methods that create them.
    - New (root) structs, enum/bitflag types, and callback types are always supported if the methods that accept them exist.
- New enum/bitflag values and [chained structs](@ref StructChaining) are available iff the corresponding "feature" was already explicitly enabled for the context where they're used:
    - Device features are detected via @ref wgpuAdapterGetFeatures() and enabled via @ref WGPUDeviceDescriptor::requiredFeatures.
    - Instance features are detected via @ref wgpuGetInstanceCapabilities() and enabled via @ref WGPUInstanceDescriptor::capabilities.

The following design principles should be followed to ensure future extensibility:

- Enums always have a `Force32 = 0x7FFFFFFF` value to force them to be 32-bit (and have a stable ABI representation).
- Bitflag types are always 64-bit.
- Structures should be extensible (have a `nextInChain`), or at least be associated with some struct (e.g. child, sibling, or parent) that is extensible.

Note also:

- Whenever necessary a version `2` or implementation-specific version of an existing method or type can be added.

## Registry of prefixes and enum blocks

Implementation extensions **should**, and multi-implementation extensions **must**, use the naming conventions listed above with the prefixes listed here.

Implementation-specific and multi-implementation extensions **must** not use block `0x0000_????` when adding values to existing enums.

|                    | Prefix       | Enum Block    | Description
|--------------------|--------------|---------------|------------
| Core               | (none)       | `0x0000_????` | Extensions that are required to implement (e.g. added after 1.0).
| Multi-Vendor       | (none)       | `0x0001_????` | Extensions that are optional to implement (e.g. platform-specific extensions). *TBD if enum values in this block may become required, or if they would be aliased into block `0x0000_????` first.*
| Compatibility Mode | *TBD*        | `0x0002_????` | **Special:** implementations that don't support Compatibility Mode must ignore any chained structs with @ref WGPUSType values in this block, instead of erroring. This block must only be used for Compat additions that can be ignored without affecting the semantics of a non-erroring program.
| wgpu-native        | `Wgpu`       | `0x0003_????` |
| Emscripten         | `Emscripten` | `0x0004_????` |
| Dawn               | `Dawn`       | `0x0005_????` |

## Registry of extension bit flag values

Implementation-specific and multi-implementation extensions **should** (*TBD: **must**?*) register new bit flag values of existing bit flag types here.

Core and Compatibility Mode bits will always be in the least-significant 53 bits, because the JS API can only represent 53 bits.
Therefore, extended bit flag values **should** be in the most-significant 11 bits, overflowing into the most-significant end of the least-significant 53 bits if necessary (or avoiding doing so by adding a new bit flag type entirely).

- (None have been registered yet!)
