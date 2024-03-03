

# RenderPassColorAttachment { #WGPURenderPassColorAttachment }

```C
struct WGPURenderPassColorAttachment {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE WGPUTextureView view;
    uint32_t depthSlice;
    WGPU_NULLABLE WGPUTextureView resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColor clearValue;
};
```


TODO


**Members:**


 - `view` (`WGPUTextureView`, **nullable**):


TODO


 - `depthSlice` (`uint32_t`):


TODO


 - `resolveTarget` (`WGPUTextureView`, **nullable**):


TODO


 - `loadOp` (`WGPULoadOp`):


TODO


 - `storeOp` (`WGPUStoreOp`):


TODO


 - `clearValue` (`WGPUColor`):


TODO




