

# Texture { #WGPUTexture }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## CreateView { #wgpuTextureCreateView }

```C
WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPUTextureViewDescriptor const *`, **nullable**):


TODO






**Returns:** `WGPUTextureView` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Destroy { #wgpuTextureDestroy }

```C
void wgpuTextureDestroy(WGPUTexture texture)
```


TODO








<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetDepthOrArrayLayers { #wgpuTextureGetDepthOrArrayLayers }

```C
uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture texture)
```


TODO






**Returns:** `uint32_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetDimension { #wgpuTextureGetDimension }

```C
WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture texture)
```


TODO






**Returns:** `WGPUTextureDimension` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetFormat { #wgpuTextureGetFormat }

```C
WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture texture)
```


TODO






**Returns:** `WGPUTextureFormat` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetHeight { #wgpuTextureGetHeight }

```C
uint32_t wgpuTextureGetHeight(WGPUTexture texture)
```


TODO






**Returns:** `uint32_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetMipLevelCount { #wgpuTextureGetMipLevelCount }

```C
uint32_t wgpuTextureGetMipLevelCount(WGPUTexture texture)
```


TODO






**Returns:** `uint32_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetSampleCount { #wgpuTextureGetSampleCount }

```C
uint32_t wgpuTextureGetSampleCount(WGPUTexture texture)
```


TODO






**Returns:** `uint32_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetUsage { #wgpuTextureGetUsage }

```C
WGPUTextureUsageFlags wgpuTextureGetUsage(WGPUTexture texture)
```


TODO






**Returns:** `WGPUTextureUsageFlags` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetWidth { #wgpuTextureGetWidth }

```C
uint32_t wgpuTextureGetWidth(WGPUTexture texture)
```


TODO






**Returns:** `uint32_t` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetLabel { #wgpuTextureSetLabel }

```C
void wgpuTextureSetLabel(WGPUTexture texture, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO






