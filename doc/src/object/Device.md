

# Device { #WGPUDevice }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateBindGroup { #wgpuDeviceCreateBindGroup }

```C
WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUBindGroupDescriptor const *`):


TODO






**Returns:** `WGPUBindGroup` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateBindGroupLayout { #wgpuDeviceCreateBindGroupLayout }

```C
WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUBindGroupLayoutDescriptor const *`):


TODO






**Returns:** `WGPUBindGroupLayout` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateBuffer { #wgpuDeviceCreateBuffer }

```C
WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUBufferDescriptor const *`):


TODO






**Returns:** `WGPUBuffer` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateCommandEncoder { #wgpuDeviceCreateCommandEncoder }

```C
WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUCommandEncoderDescriptor const *`, **nullable**):


TODO






**Returns:** `WGPUCommandEncoder` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateComputePipeline { #wgpuDeviceCreateComputePipeline }

```C
WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUComputePipelineDescriptor const *`):


TODO






**Returns:** `WGPUComputePipeline` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateComputePipelineAsync { #wgpuDeviceCreateComputePipelineAsync }

```C
void wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUDeviceCreateComputePipelineAsyncCallback callback, WGPU_NULLABLE void * userdata)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUComputePipelineDescriptor const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreatePipelineLayout { #wgpuDeviceCreatePipelineLayout }

```C
WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUPipelineLayoutDescriptor const *`):


TODO






**Returns:** `WGPUPipelineLayout` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateQuerySet { #wgpuDeviceCreateQuerySet }

```C
WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUQuerySetDescriptor const *`):


TODO






**Returns:** `WGPUQuerySet` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateRenderBundleEncoder { #wgpuDeviceCreateRenderBundleEncoder }

```C
WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPURenderBundleEncoderDescriptor const *`):


TODO






**Returns:** `WGPURenderBundleEncoder` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateRenderPipeline { #wgpuDeviceCreateRenderPipeline }

```C
WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPURenderPipelineDescriptor const *`):


TODO






**Returns:** `WGPURenderPipeline` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateRenderPipelineAsync { #wgpuDeviceCreateRenderPipelineAsync }

```C
void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUDeviceCreateRenderPipelineAsyncCallback callback, WGPU_NULLABLE void * userdata)
```


TODO




**Arguments:**


 - `descriptor` (`WGPURenderPipelineDescriptor const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateSampler { #wgpuDeviceCreateSampler }

```C
WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUSamplerDescriptor const *`, **nullable**):


TODO






**Returns:** `WGPUSampler` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateShaderModule { #wgpuDeviceCreateShaderModule }

```C
WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUShaderModuleDescriptor const *`):


TODO






**Returns:** `WGPUShaderModule` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateTexture { #wgpuDeviceCreateTexture }

```C
WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUTextureDescriptor const *`):


TODO






**Returns:** `WGPUTexture` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Destroy { #wgpuDeviceDestroy }

```C
void wgpuDeviceDestroy(WGPUDevice device)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## EnumerateFeatures { #wgpuDeviceEnumerateFeatures }

```C
size_t wgpuDeviceEnumerateFeatures(WGPUDevice device, WGPUFeatureName * features)
```


TODO




**Arguments:**


 - `features` (`WGPUFeatureName *`):


TODO






**Returns:** `size_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetLimits { #wgpuDeviceGetLimits }

```C
WGPUBool wgpuDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits * limits)
```


TODO




**Arguments:**


 - `limits` (`WGPUSupportedLimits *`):


TODO






**Returns:** `WGPUBool` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetQueue { #wgpuDeviceGetQueue }

```C
WGPUQueue wgpuDeviceGetQueue(WGPUDevice device)
```


TODO






**Returns:** `WGPUQueue` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## HasFeature { #wgpuDeviceHasFeature }

```C
WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature)
```


TODO




**Arguments:**


 - `feature` (`WGPUFeatureName`):


TODO






**Returns:** `WGPUBool` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PopErrorScope { #wgpuDevicePopErrorScope }

```C
void wgpuDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata)
```


TODO




**Arguments:**


 - `callback` (`WGPUErrorCallback`):


TODO


 - `userdata` (`void *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PushErrorScope { #wgpuDevicePushErrorScope }

```C
void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter)
```


TODO




**Arguments:**


 - `filter` (`WGPUErrorFilter`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetLabel { #wgpuDeviceSetLabel }

```C
void wgpuDeviceSetLabel(WGPUDevice device, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetUncapturedErrorCallback { #wgpuDeviceSetUncapturedErrorCallback }

```C
void wgpuDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata)
```


TODO




**Arguments:**


 - `callback` (`WGPUErrorCallback`):


TODO


 - `userdata` (`void *`):


TODO






