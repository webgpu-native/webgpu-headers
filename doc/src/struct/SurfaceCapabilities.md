

# SurfaceCapabilities { #WGPUSurfaceCapabilities }

```C
struct WGPUSurfaceCapabilities {
    WGPUChainedStructOut * nextInChain;
    size_t formatCount;
    WGPUTextureFormat const * formats;
    size_t presentModeCount;
    WGPUPresentMode const * presentModes;
    size_t alphaModeCount;
    WGPUCompositeAlphaMode const * alphaModes;
};
```


TODO


**Members:**


 - `formats` (``):


TODO


 - `presentModes` (``):


TODO


 - `alphaModes` (``):


TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## FreeMembers { #wgpuSurfaceCapabilitiesFreeMembers }

```C
void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities)
```

Free all pointer members.


