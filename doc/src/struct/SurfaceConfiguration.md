

# SurfaceConfiguration { #WGPUSurfaceConfiguration }

```C
struct WGPUSurfaceConfiguration {
    WGPUChainedStruct const * nextInChain;
    WGPUDevice device;
    WGPUTextureFormat format;
    WGPUTextureUsageFlags usage;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
    WGPUCompositeAlphaMode alphaMode;
    uint32_t width;
    uint32_t height;
    WGPUPresentMode presentMode;
};
```


TODO


**Members:**


 - `device` (`WGPUDevice`):


TODO


 - `format` (`WGPUTextureFormat`):


TODO


 - `usage` (`WGPUTextureUsageFlags`):


TODO


 - `viewFormats` (``):


TODO


 - `alphaMode` (`WGPUCompositeAlphaMode`):


TODO


 - `width` (`uint32_t`):


TODO


 - `height` (`uint32_t`):


TODO


 - `presentMode` (`WGPUPresentMode`):


TODO




