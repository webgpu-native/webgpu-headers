

# TextureDescriptor { #WGPUTextureDescriptor }

```C
struct WGPUTextureDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUTextureUsageFlags usage;
    WGPUTextureDimension dimension;
    WGPUExtent3D size;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `usage` (`WGPUTextureUsageFlags`):


TODO


 - `dimension` (`WGPUTextureDimension`):


TODO


 - `size` (`WGPUExtent3D`):


TODO


 - `format` (`WGPUTextureFormat`):


TODO


 - `mipLevelCount` (`uint32_t`):


TODO


 - `sampleCount` (`uint32_t`):


TODO


 - `viewFormats` (``):


TODO




