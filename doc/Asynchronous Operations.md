# Asynchronous Operations {#Asynchronous-Operations}

Asynchronous operations in webgpu.h return a @ref WGPUFuture. This is an opaque handle which applications may use to poll or wait for completion of the asynchronous operation.

On all implementations of webgpu.h, it must be possible to react to async operations without undue latency or spin-waiting.

## Creation

All asynchronous operations start when the application calls an asynchronous webgpu.h function. These functions return `WGPUFuture`, and take in their arguments a `CallbackInfo` struct like @ref WGPURequestDeviceCallbackInfo or @ref WGPUBufferMapCallbackInfo. `CallbackInfo` structs have the following members:
 - a `WGPUChainedStruct const * nextInChain` pointer, for extensions.
 - a @ref WGPUCallbackMode `mode` enum.
 - a `callback` function pointer. For example:
   ```typedef void (*WGPUBufferMapCallback)(
        WGPUMapAsyncStatus status,
        char const * message,
        WGPU_NULLABLE void* userdata1,
        WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;```
 - Two application-owned userdata members.\n
   `void* userdata1`\n
   `void* userdata2`

The `callback` function pointer is called when the application callback fires. The `userdata1` and `userdata2` members are passed back to the application as the last two arguments in the callback function. Callbacks may not fire unless the application explicitly flushes them. It depends on the @ref WGPUCallbackMode of the operation. webgpu.h provides three callback modes: `::WGPUCallbackMode_WaitAnyOnly`, `::WGPUCallbackMode_AllowProcessEvents`, and `::WGPUCallbackMode_AllowSpontaneous`.


## wgpuInstanceWaitAny {#Wait-Any}
`WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance, size_t futureCount, WGPUFutureWaitInfo * futures, uint64_t timeoutNS)`

Waits on any WGPUFuture in the list of `futures` to complete for `timeoutNS` nanoseconds. Returns when at least one `WGPUFuture` is completed or `timeoutNS` elapses, whichever is first.

Returns `::WGPUWaitStatus_Success` if at least one `WGPUFuture` completes. WGPUFutureWaitInfo::completed is set to true for all completed futures. See @ref WGPUWaitStatus for other status codes.

Within this call, any `WGPUFuture`s that completed, their respective callbacks will fire.

### Timed Wait {#Timed-Wait}

Use of _timed waits_ (`timeoutNS > 0`), must be enabled on the WGPUInstance with WGPUInstanceFeatures::timedWaitAnyEnable, and the number of futures waited on must be less than or equal to WGPUInstanceFeatures::timedWaitAnyMaxCount. Supported instance features may be queried using `::wgpuGetInstanceFeatures`.

### Mixed Sources {#Mixed-Sources}

Asynchronous operations may originate from different sources. There are CPU-timeline operations and there are Queue-timeline operations. Within a _timed wait_, it is only valid to wait on `WGPUFuture`s originating from a single `WGPUQueue`. Waiting on two futures from different queues, or waiting on a Queue-timeline future and some other CPU-timeline future is an error.

#### CPU-Timeline Operations
 - ::wgpuInstanceRequestAdapter
 - ::wgpuAdapterRequestDevice
 - ::wgpuShaderModuleGetCompilationInfo
 - ::wgpuDeviceCreateRenderPipelineAsync
 - ::wgpuDeviceCreateComputePipelineAsync
 - ::wgpuDevicePopErrorScope

#### Queue-Timeline Operations
 - ::wgpuBufferMapAsync
 - ::wgpuQueueOnSubmittedWorkDone

## wgpuInstanceProcessEvents {#Process-Events}
`void wgpuInstanceProcessEvents(WGPUInstance)`

Processes asynchronous events on this `WGPUInstance`, calling any callbacks for asynchronous operations created with `WGPUCallbackMode_AllowProcessEvents` that have completed. This is a non-blocking operation.

## Device Events

Device events are slightly different in that their callback info (`WGPUDeviceLostCallbackInfo` and `WGPUUncapturedErrorCallbackInfo`) are passed on the `WGPUDeviceDescriptor`, instead of in a function argument. There is no `WGPUFuture` returned for either callback.

The `WGPUUncapturedErrorCallbackInfo` _does not_ have a callback mode member. It is always as-if it were `::WGPUCallbackMode_AllowSpontaneous`. Note also that the uncaptured error callback is a _repeating_ callback that fires multiple times, unlike other callbacks in webgpu.h.

The uncaptured error callback is guaranteed not to fire after the device becomes lost. When the device is lost, it is an appropriate time for the application to free userdata variables for the uncaptured error callback. Note that the device becomes lost _before_ the actual device lost callback fires. First the device state transitions to lost, then the device lost callback fires. The timing of the callback depends on the device lost callback mode.
