

# RenderBundleEncoderDescriptor { #WGPURenderBundleEncoderDescriptor }

```C
struct WGPURenderBundleEncoderDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t colorFormatCount;
    WGPUTextureFormat const * colorFormats;
    WGPUTextureFormat depthStencilFormat;
    uint32_t sampleCount;
    WGPUBool depthReadOnly;
    WGPUBool stencilReadOnly;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `colorFormats` (``):


TODO


 - `depthStencilFormat` (`WGPUTextureFormat`):


TODO


 - `sampleCount` (`uint32_t`):


TODO


 - `depthReadOnly` (`WGPUBool`):


TODO


 - `stencilReadOnly` (`WGPUBool`):


TODO




