# gen

The generator for generating `webgpu.h` header and other extension headers or implementation specific headers from the yaml spec files.

# yaml spec

### Types

| Primitive types | Complex types     |
| --------------- | ----------------- |
| `bool`          | `enum.*`          |
| `string`        | `bitflag.*`       |
| `uint16`        | `struct.*`        |
| `uint32`        | `function_type.*` |
| `uint64`        | `object.*`        |
| `usize`         |
| `int16`         |
| `int32`         |
| `float32`       |
| `float64`       |
| `c_void`        |

| Structure types |                                                         |
| --------------- | ------------------------------------------------------- |
| `base_in`       | in-structs that can be extended                         |
| `base_out`      | out-structs that can be extended                        |
| `extension_in`  | in-structs that are extensions                          |
| `extension_out` | out-structs that are extensions                         |
| `standalone`    | structs that are niether extensions nor can be extended |

#### Arrays

Arrays are supported using a special syntax, for example `array<uint32>`. The generator will emit two fields for array types, one for element count and another for the pointer to the type.
