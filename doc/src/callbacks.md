# Callback types


### `WGPUAdapterRequestAdapterInfoCallback` { #WGPUAdapterRequestAdapterInfoCallback }

```C
typedef void (*WGPUAdapterRequestAdapterInfoCallback)(struct WGPUAdapterInfo adapterInfo, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUAdapterRequestDeviceCallback` { #WGPUAdapterRequestDeviceCallback }

```C
typedef void (*WGPUAdapterRequestDeviceCallback)(WGPURequestDeviceStatus status, WGPUDevice device, char const * message, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUBufferMapAsyncCallback` { #WGPUBufferMapAsyncCallback }

```C
typedef void (*WGPUBufferMapAsyncCallback)(WGPUBufferMapAsyncStatus status, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUDeviceCreateComputePipelineAsyncCallback` { #WGPUDeviceCreateComputePipelineAsyncCallback }

```C
typedef void (*WGPUDeviceCreateComputePipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPUComputePipeline pipeline, char const * message, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUDeviceCreateRenderPipelineAsyncCallback` { #WGPUDeviceCreateRenderPipelineAsyncCallback }

```C
typedef void (*WGPUDeviceCreateRenderPipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPURenderPipeline pipeline, char const * message, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUInstanceRequestAdapterCallback` { #WGPUInstanceRequestAdapterCallback }

```C
typedef void (*WGPUInstanceRequestAdapterCallback)(WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUQueueOnSubmittedWorkDoneCallback` { #WGPUQueueOnSubmittedWorkDoneCallback }

```C
typedef void (*WGPUQueueOnSubmittedWorkDoneCallback)(WGPUQueueWorkDoneStatus status, WGPU_NULLABLE void * userdata)`
```


TODO


### `WGPUShaderModuleGetCompilationInfoCallback` { #WGPUShaderModuleGetCompilationInfoCallback }

```C
typedef void (*WGPUShaderModuleGetCompilationInfoCallback)(WGPUCompilationInfoRequestStatus status, struct WGPUCompilationInfo const * compilationInfo, WGPU_NULLABLE void * userdata)`
```


TODO


