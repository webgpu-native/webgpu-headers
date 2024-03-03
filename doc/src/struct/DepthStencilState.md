

# DepthStencilState { #WGPUDepthStencilState }

```C
struct WGPUDepthStencilState {
    WGPUChainedStruct const * nextInChain;
    WGPUTextureFormat format;
    WGPUBool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilFaceState stencilFront;
    WGPUStencilFaceState stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
};
```


TODO


**Members:**


 - `format` (`WGPUTextureFormat`):


TODO


 - `depthWriteEnabled` (`WGPUBool`):


TODO


 - `depthCompare` (`WGPUCompareFunction`):


TODO


 - `stencilFront` (`WGPUStencilFaceState`):


TODO


 - `stencilBack` (`WGPUStencilFaceState`):


TODO


 - `stencilReadMask` (`uint32_t`):


TODO


 - `stencilWriteMask` (`uint32_t`):


TODO


 - `depthBias` (`int32_t`):


TODO


 - `depthBiasSlopeScale` (`float`):


TODO


 - `depthBiasClamp` (`float`):


TODO




