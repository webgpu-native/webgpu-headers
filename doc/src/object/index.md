# Objects

WebGPU objects are referenced through blind handles, which are homogenous to pointers. The following objects are defined and detailed below:

 - [`WGPUAdapter`](#WGPUAdapter)
 - [`WGPUBindGroup`](#WGPUBindGroup)
 - [`WGPUBindGroupLayout`](#WGPUBindGroupLayout)
 - [`WGPUBuffer`](#WGPUBuffer)
 - [`WGPUCommandBuffer`](#WGPUCommandBuffer)
 - [`WGPUCommandEncoder`](#WGPUCommandEncoder)
 - [`WGPUComputePassEncoder`](#WGPUComputePassEncoder)
 - [`WGPUComputePipeline`](#WGPUComputePipeline)
 - [`WGPUDevice`](#WGPUDevice)
 - [`WGPUInstance`](#WGPUInstance)
 - [`WGPUPipelineLayout`](#WGPUPipelineLayout)
 - [`WGPUQuerySet`](#WGPUQuerySet)
 - [`WGPUQueue`](#WGPUQueue)
 - [`WGPURenderBundle`](#WGPURenderBundle)
 - [`WGPURenderBundleEncoder`](#WGPURenderBundleEncoder)
 - [`WGPURenderPassEncoder`](#WGPURenderPassEncoder)
 - [`WGPURenderPipeline`](#WGPURenderPipeline)
 - [`WGPUSampler`](#WGPUSampler)
 - [`WGPUShaderModule`](#WGPUShaderModule)
 - [`WGPUSurface`](#WGPUSurface)
 - [`WGPUTexture`](#WGPUTexture)
 - [`WGPUTextureView`](#WGPUTextureView)

**NB** Additionally, all objects provide a `Release` and a `Reference` methods:

 - `void wgpu<ObjectName>Reference(WGPU<ObjectName>)`
 - `void wgpu<ObjectName>Release(WGPU<ObjectName>)`


