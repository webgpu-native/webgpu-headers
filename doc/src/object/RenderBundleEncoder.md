

# RenderBundleEncoder { #WGPURenderBundleEncoder }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Draw { #wgpuRenderBundleEncoderDraw }

```C
void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance)
```


TODO




**Arguments:**


 - `vertexCount` (`uint32_t`):


TODO


 - `instanceCount` (`uint32_t`):


TODO


 - `firstVertex` (`uint32_t`):


TODO


 - `firstInstance` (`uint32_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## DrawIndexed { #wgpuRenderBundleEncoderDrawIndexed }

```C
void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance)
```


TODO




**Arguments:**


 - `indexCount` (`uint32_t`):


TODO


 - `instanceCount` (`uint32_t`):


TODO


 - `firstIndex` (`uint32_t`):


TODO


 - `baseVertex` (`int32_t`):


TODO


 - `firstInstance` (`uint32_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## DrawIndexedIndirect { #wgpuRenderBundleEncoderDrawIndexedIndirect }

```C
void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset)
```


TODO




**Arguments:**


 - `indirectBuffer` (`WGPUBuffer`):


TODO


 - `indirectOffset` (`uint64_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## DrawIndirect { #wgpuRenderBundleEncoderDrawIndirect }

```C
void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset)
```


TODO




**Arguments:**


 - `indirectBuffer` (`WGPUBuffer`):


TODO


 - `indirectOffset` (`uint64_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Finish { #wgpuRenderBundleEncoderFinish }

```C
WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor)
```


TODO




**Arguments:**


 - `descriptor` (`WGPURenderBundleDescriptor const *`, **nullable**):


TODO






**Returns:** `WGPURenderBundle` 
TODO





<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## InsertDebugMarker { #wgpuRenderBundleEncoderInsertDebugMarker }

```C
void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel)
```


TODO




**Arguments:**


 - `markerLabel` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PopDebugGroup { #wgpuRenderBundleEncoderPopDebugGroup }

```C
void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PushDebugGroup { #wgpuRenderBundleEncoderPushDebugGroup }

```C
void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel)
```


TODO




**Arguments:**


 - `groupLabel` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetBindGroup { #wgpuRenderBundleEncoderSetBindGroup }

```C
void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets)
```


TODO




**Arguments:**


 - `groupIndex` (`uint32_t`):


TODO


 - `group` (`WGPUBindGroup`, **nullable**):


TODO


 - `dynamicOffsets` (``):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetIndexBuffer { #wgpuRenderBundleEncoderSetIndexBuffer }

```C
void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size)
```


TODO




**Arguments:**


 - `buffer` (`WGPUBuffer`):


TODO


 - `format` (`WGPUIndexFormat`):


TODO


 - `offset` (`uint64_t`):


TODO


 - `size` (`uint64_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetLabel { #wgpuRenderBundleEncoderSetLabel }

```C
void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetPipeline { #wgpuRenderBundleEncoderSetPipeline }

```C
void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline)
```


TODO




**Arguments:**


 - `pipeline` (`WGPURenderPipeline`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetVertexBuffer { #wgpuRenderBundleEncoderSetVertexBuffer }

```C
void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size)
```


TODO




**Arguments:**


 - `slot` (`uint32_t`):


TODO


 - `buffer` (`WGPUBuffer`, **nullable**):


TODO


 - `offset` (`uint64_t`):


TODO


 - `size` (`uint64_t`):


TODO






