# Ownership {#Ownership}

Objects in `webgpu.h` are refcounted via the `AddRef` and `Release` functions.
The refcount only changes when these methods are called explicitly (not, for example, in \ref wgpuCommandEncoderFinish or \ref wgpuQueueSubmit).

Memory for variable-sized outputs from the API (message strings, capability arrays, etc.) is managed in different ways depending on whether they are returned values or callback arguments.

## Returned with Ownership {#ReturnedWithOwnership}

Objects returned directly from the API (e.g. \ref WGPUBuffer from \ref wgpuDeviceCreateBuffer and \ref WGPUTexture via \ref WGPUSurfaceTexture from \ref wgpuSurfaceGetCurrentTexture) start with one application-owned ref.
The application must `Release` this ref before losing the pointer.
(The returned object may _also_ have other refs, either API-owned refs or existing application-owned refs, but this should not be relied upon.)

Variable-sized outputs returned from the API (e.g. the strings in \ref WGPUAdapterInfo, from \ref wgpuAdapterGetInfo) are application-owned.
The application must call the appropriate `FreeMembers` function (e.g. \ref wgpuAdapterInfoFreeMembers) before losing the pointers.
Note that such functions will *not* free any previously-allocated data: overwriting an output structure (e.g. using \ref wgpuAdapterGetInfo) without first calling `FreeMembers` (e.g. `wgpuAdapterInfoFreeMembers) will leak the allocations.

## Callback Arguments {#CallbackArgs}

Output arguments passed from the API to application callbacks include objects and message strings, which are passed to most callbacks.

### Passed with Ownership {#PassedWithOwnership}

Usually, object arguments passed to callbacks start with one application-owned ref, which the application must free before losing the pointer.

### Passed without Ownership {#PassedWithoutOwnership}

A.k.a. "pass by reference".

Sometimes, object arguments passed to callbacks are non-owning (such as the \ref WGPUDevice in \ref WGPUDeviceLostCallback) - the application doesn't need to free them.

Variable-sized outputs passed from the API to callbacks (such as message strings in most callbacks) are always owned by the API and guaranteed to be valid only during the callback's execution, after which the pointers passed to the callback are no longer valid.

