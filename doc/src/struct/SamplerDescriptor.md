

# SamplerDescriptor { #WGPUSamplerDescriptor }

```C
struct WGPUSamplerDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUMipmapFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;
    uint16_t maxAnisotropy;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `addressModeU` (`WGPUAddressMode`):


TODO


 - `addressModeV` (`WGPUAddressMode`):


TODO


 - `addressModeW` (`WGPUAddressMode`):


TODO


 - `magFilter` (`WGPUFilterMode`):


TODO


 - `minFilter` (`WGPUFilterMode`):


TODO


 - `mipmapFilter` (`WGPUMipmapFilterMode`):


TODO


 - `lodMinClamp` (`float`):


TODO


 - `lodMaxClamp` (`float`):


TODO


 - `compare` (`WGPUCompareFunction`):


TODO


 - `maxAnisotropy` (`uint16_t`):


TODO




