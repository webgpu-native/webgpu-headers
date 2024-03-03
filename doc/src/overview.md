# API Overview

This page introduces the key entities used throughout the WebGPU Native API. For a raw list of all symbols defined by the C header, see the [API index](api.md).

**NB** This documentation is not meant to introduce the elementary notions of graphics programming needed to understand it but rather assumes that the reader is familiar with it in order to focus on the structure of the API.

## Naming convention

All types and enumerations defined by this API start with `WGPU`, followed by a [PascalCased](https://en.wikipedia.org/wiki/Camel_case) name. Example:

```C
   WGPUCommandEncoder;
//     ^^^^^^^^^^^^^^ Name of the object/structure/enum
// ^^^^ Namespace prefix
```

All functions defined by the API start with `wgpu`, immediately followed by the name of the object/structure they primarily act on and that is the type of their first argument. Example:

```C
size_t wgpuAdapterEnumerateFeatures(WGPUAdapter adapter, WGPUFeatureName * features);
//                ^^^^^^^^^^^^^^^^^ Name of the action
//         ^^^^^^^ Type of the first argument
//     ^^^^ Namespace prefix
```

## Objects

This is the **main type of entity** that a WebGPU Native developer manipulates. An object may represent a device, a shader module, a command encoder, etc.

WebGPU objects are defined on the backend side, and we only interact with them through API functions. Hence WebGPU objects are referenced through **blind handles**, which are homogeneous to pointers and can be cheaply copied.

Objects are **reference counted**. After an object of type `WGPU<ObjectName>` is created, typically using `wgpuDeviceCreate<ObjectName>()`, its internal counter is set to 1. Calling `wgpu<ObjectName>Reference()` increases this reference counter, while `wgpu<ObjectName>Release()` decrements it. This object gets freed as soon as its reference counter falls to 0. It must then never be used again.

[See all WebGPU objects.](object/index.md)

## Structures

Structures are allocated on the user side, contrary to objects.

The primary type of structure is called **descriptor** and is used to enclose all the parameters needed to call an object creation function. More precisely, the `wgpuDeviceCreate<ObjectName>` function takes as single argument a pointer to a `WGPU<ObjectName>Descriptor` value. Descriptors and their members do not need to live beyond the function call that uses them.

Other types are used either as sub members of descriptors (e.g., [`GPUBlendState`](struct/BlendState.md)), or for the backend to report information about objects (e.g., [`GPUAdapterInfo`](struct/AdapterInfo.md)). Some types (e.g., [`WGPUSurfaceCapabilities`](struct/SurfaceCapabilities.md)) contain pointer fields allocated by the backend. In such a case, they must be freed using the associated `FreeMembers` function (e.g., `wgpuSurfaceCapabilitiesFreeMembers()`).

[See all WebGPU structures.](struct/index.md)

## Enumerations

WebGPU defines a lot of enumerations. In order to make them extensible, they are however not represented as C `enum` but rather as a collection of constants.

[See all WebGPU enumerations.](enum/index.md)

## Callback types

Multiple functions of the API are **asynchronous**, meaning that instead of immediately returning a value, they eventually invoke a **callback** that was passed as one of their arguments.

In order to pass some **context** from around the function call to the body of the, callbacks itself, a callback arguments is always followed by a `void* userdata` pointer that is then forwarded to the callback as its last argument. This can be left null if no context is needed.

[See all WebGPU callback types.](callbacks.md)

## Constants

[See all WebGPU constants.](constants.md)

## Typedefs

[See all WebGPU constants.](typedefs.md)
