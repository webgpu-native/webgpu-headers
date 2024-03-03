

# RenderPassDescriptor { #WGPURenderPassDescriptor }

```C
struct WGPURenderPassDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t colorAttachmentCount;
    WGPURenderPassColorAttachment const * colorAttachments;
    WGPU_NULLABLE WGPURenderPassDepthStencilAttachment const * depthStencilAttachment;
    WGPU_NULLABLE WGPUQuerySet occlusionQuerySet;
    WGPU_NULLABLE WGPURenderPassTimestampWrites const * timestampWrites;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `colorAttachments` (``):


TODO


 - `depthStencilAttachment` (`WGPURenderPassDepthStencilAttachment const *`, **nullable**):


TODO


 - `occlusionQuerySet` (`WGPUQuerySet`, **nullable**):


TODO


 - `timestampWrites` (`WGPURenderPassTimestampWrites const *`, **nullable**):


TODO




