

# RenderPipelineDescriptor { #WGPURenderPipelineDescriptor }

```C
struct WGPURenderPipelineDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPU_NULLABLE WGPUPipelineLayout layout;
    WGPUVertexState vertex;
    WGPUPrimitiveState primitive;
    WGPU_NULLABLE WGPUDepthStencilState const * depthStencil;
    WGPUMultisampleState multisample;
    WGPU_NULLABLE WGPUFragmentState const * fragment;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `layout` (`WGPUPipelineLayout`, **nullable**):


TODO


 - `vertex` (`WGPUVertexState`):


TODO


 - `primitive` (`WGPUPrimitiveState`):


TODO


 - `depthStencil` (`WGPUDepthStencilState const *`, **nullable**):


TODO


 - `multisample` (`WGPUMultisampleState`):


TODO


 - `fragment` (`WGPUFragmentState const *`, **nullable**):


TODO




