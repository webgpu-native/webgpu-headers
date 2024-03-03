

# Surface { #WGPUSurface }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Configure { #wgpuSurfaceConfigure }

```C
void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const * config)
```


TODO




**Arguments:**


 - `config` (`WGPUSurfaceConfiguration const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetCapabilities { #wgpuSurfaceGetCapabilities }

```C
void wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities)
```


TODO




**Arguments:**


 - `adapter` (`WGPUAdapter`):


TODO


 - `capabilities` (`WGPUSurfaceCapabilities *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetCurrentTexture { #wgpuSurfaceGetCurrentTexture }

```C
void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture)
```


TODO




**Arguments:**


 - `surfaceTexture` (`WGPUSurfaceTexture *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## GetPreferredFormat { #wgpuSurfaceGetPreferredFormat }

```C
WGPUTextureFormat wgpuSurfaceGetPreferredFormat(WGPUSurface surface, WGPUAdapter adapter)
```


TODO




**Arguments:**


 - `adapter` (`WGPUAdapter`):


TODO






**Returns:** `WGPUTextureFormat` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Present { #wgpuSurfacePresent }

```C
void wgpuSurfacePresent(WGPUSurface surface)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetLabel { #wgpuSurfaceSetLabel }

```C
void wgpuSurfaceSetLabel(WGPUSurface surface, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Unconfigure { #wgpuSurfaceUnconfigure }

```C
void wgpuSurfaceUnconfigure(WGPUSurface surface)
```


TODO






