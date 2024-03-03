

# Adapter { #WGPUAdapter }


This is a test.




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## EnumerateFeatures { #wgpuAdapterEnumerateFeatures }

```C
size_t wgpuAdapterEnumerateFeatures(WGPUAdapter adapter, WGPUFeatureName * features)
```


TODO




**Arguments:**


 - `features` (`WGPUFeatureName *`):


TODO






**Returns:** `size_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetLimits { #wgpuAdapterGetLimits }

```C
WGPUBool wgpuAdapterGetLimits(WGPUAdapter adapter, WGPUSupportedLimits * limits)
```


Get the limits that the adapter supports. This is used to drive the
choice of required limits in {device_descriptor.required_limits}.




**Arguments:**


 - `limits` (`WGPUSupportedLimits *`):


TODO






**Returns:** `WGPUBool` 
True iff limits were successfully retrieved.





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetProperties { #wgpuAdapterGetProperties }

```C
void wgpuAdapterGetProperties(WGPUAdapter adapter, WGPUAdapterProperties * properties)
```


TODO




**Arguments:**


 - `properties` (`WGPUAdapterProperties *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## HasFeature { #wgpuAdapterHasFeature }

```C
WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature)
```


TODO




**Arguments:**


 - `feature` (`WGPUFeatureName`):


TODO






**Returns:** `WGPUBool` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## RequestAdapterInfo { #wgpuAdapterRequestAdapterInfo }

```C
void wgpuAdapterRequestAdapterInfo(WGPUAdapter adapter, WGPUAdapterRequestAdapterInfoCallback callback, WGPU_NULLABLE void * userdata)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## RequestDevice { #wgpuAdapterRequestDevice }

```C
void wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPUAdapterRequestDeviceCallback callback, WGPU_NULLABLE void * userdata)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUDeviceDescriptor const *`, **nullable**):


TODO






