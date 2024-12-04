# Errors {#Errors}

Errors are surfaced in several ways.

Most errors only result from incorrect use of the API and should not need to be handled at runtime.
However, a few (@ref WGPUErrorType_OutOfMemory, @ref WGPUErrorType_Internal) are potentially useful to handle.

## Device Error {#DeviceError}

These behave the same way as [in the WebGPU JavaScript API specification](https://www.w3.org/TR/webgpu/#errors-and-debugging).
They are receivable via @ref wgpuDevicePopErrorScope() and @ref WGPUDeviceDescriptor::uncapturedErrorCallbackInfo.

These errors include:

- All device-timeline errors in the WebGPU specification.
- Enum values which are numerically invalid (this is not possible in JavaScript).
- Enum values which are require features not enabled on the device (a [content-timeline](https://www.w3.org/TR/webgpu/#content-timeline) error in JavaScript), for example compressed texture formats.
- Other content-timeline errors where specified.

### Error Scopes {#ErrorScopes}

Error scopes are used via @ref wgpuDevicePushErrorScope, @ref wgpuDevicePopErrorScope, and @ref WGPUDeviceDescriptor::uncapturedErrorCallbackInfo. These behave the same as in the JavaScript API, except for considerations around multi-threading (which JavaScript doesn't have at the time of this writing):

- The error scope stack state is **thread-local**: each thread has a separate stack, which is initially empty. The error scope that captures an error depends on which thread made the API call that generated the error.
- The UncapturedError callback receives uncaptured errors from all threads.

### Error Sinks {#ErrorSinks}

`webgpu.h` adds error sinks as a new error management primitive over the JavaScript API: @ref WGPUErrorSinkOutOfMemory and @ref WGPUErrorSinkInternal.
This can be set in certain API calls to absorb an error from that API call only, rather than having it go to the error scope stack. It is equivalent to pushing and popping error scopes of the corresponding types around the call, but is more straightforward because it doesn't use thread-local storage.

- @ref WGPUErrorSinkOutOfMemory
    - @ref wgpuDeviceCreateBuffer
    - @ref wgpuDeviceCreateTexture
    - @ref wgpuDeviceCreateQuerySet
- @ref WGPUErrorSinkInternal
    - @ref wgpuDeviceCreateComputePipeline
    - @ref wgpuDeviceCreateRenderPipeline

## Callback Error {#CallbackError}

These behave similarly to the Promise-returning JavaScript APIs. Instead of there being two callbacks like in JavaScript (one for resolve and one for reject), there is a single callback which receives a status code, and depending on the status, _either_ a valid result with an empty message string (`{NULL, 0}`), _or_ an invalid result with a non-empty message string.

## Synchronous Error {#SynchronousError}

These errors include:

- @ref StructChainingError cases.
- [Content-timeline](https://www.w3.org/TR/webgpu/#content-timeline) errors other than those which are surfaced as @ref DeviceError in `webgpu.h`. See specific documentation to determine how each error is exposed.

Generally these will return some kind of failure status (like \ref WGPUStatus_Error) or `NULL`, and produce an @ref ImplementationDefinedLogging message.

### Implementation-Defined Logging {#ImplementationDefinedLogging}

Entry points may also specify that they produce "implementation-defined logging".
These messages are logged in an implementation defined way (e.g. to an implementation-specific callback, or to a logging runtime).
They are intended to be intended to be read by humans, useful primarily for development and crash reporting.

## Struct-Chaining Error {#StructChainingError}

A struct-chaining error happens when the @ref WGPUSType of a struct in a struct chain is not valid for that chain.

Struct chains which are used in device-timeline validation/operations (e.g. @ref WGPUBufferDescriptor in @ref wgpuDeviceCreateBuffer) have their chain errors surfaced asynchronously, like any other validation error.

### Out-Struct-Chain Error {#OutStructChainError}

Operations which take out-struct-chains (e.g. @ref WGPULimits, in @ref wgpuAdapterGetLimits and @ref wgpuDeviceGetLimits, but not in @ref WGPUDeviceDescriptor) handle struct-chaining errors as follows:

- The output struct and struct chain is not modified.
- The operation produces a @ref SynchronousError (return value and log message).
