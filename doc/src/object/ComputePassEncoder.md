

# ComputePassEncoder { #WGPUComputePassEncoder }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## DispatchWorkgroups { #wgpuComputePassEncoderDispatchWorkgroups }

```C
void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ)
```


TODO




**Arguments:**


 - `workgroupCountX` (`uint32_t`):


TODO


 - `workgroupCountY` (`uint32_t`):


TODO


 - `workgroupCountZ` (`uint32_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## DispatchWorkgroupsIndirect { #wgpuComputePassEncoderDispatchWorkgroupsIndirect }

```C
void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset)
```


TODO




**Arguments:**


 - `indirectBuffer` (`WGPUBuffer`):


TODO


 - `indirectOffset` (`uint64_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## End { #wgpuComputePassEncoderEnd }

```C
void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## InsertDebugMarker { #wgpuComputePassEncoderInsertDebugMarker }

```C
void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel)
```


TODO




**Arguments:**


 - `markerLabel` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PopDebugGroup { #wgpuComputePassEncoderPopDebugGroup }

```C
void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## PushDebugGroup { #wgpuComputePassEncoderPushDebugGroup }

```C
void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel)
```


TODO




**Arguments:**


 - `groupLabel` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetBindGroup { #wgpuComputePassEncoderSetBindGroup }

```C
void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets)
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

## SetLabel { #wgpuComputePassEncoderSetLabel }

```C
void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetPipeline { #wgpuComputePassEncoderSetPipeline }

```C
void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline)
```


TODO




**Arguments:**


 - `pipeline` (`WGPUComputePipeline`):


TODO






