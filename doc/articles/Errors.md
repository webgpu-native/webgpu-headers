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

## Callback Errors {#CallbackErrors}

These behave similarly to the Promise-returning JavaScript APIs. Instead of there being two callbacks like in JavaScript (one for resolve and one for reject), there is a single callback which receives a status code, and depending on the status, _either_ a valid result with an empty message string (`{NULL, 0}`), _or_ an invalid result with a non-empty message string.

## Synchronous Errors {#SynchronousErrors}

These errors include:

- @ref StructChainingError cases.
- [Content-timeline](https://www.w3.org/TR/webgpu/#content-timeline) errors other than those which are surfaced as @ref DeviceError in `webgpu.h`. See specific documentation to determine how each error is exposed.

Generally these will return some kind of failure status (like \ref WGPUStatus_Error), or `NULL`.

### Struct-Chaining Error {#StructChainingError}

A struct-chaining error happens when the `SType` of a struct in a struct chain is not valid for that chain.
The API returns a failure status or `NULL` and produces an @ref ImplementationDefinedLogging message.

### Implementation-Defined Logging {#ImplementationDefinedLogging}

Entry points may also specify that they produce "implementation-defined logging".
These messages are logged in an implementation defined way (e.g. to an implementation-specific callback, or to a logging runtime).
They are intended to be intended to be read by humans, useful primarily for development and crash reporting.
