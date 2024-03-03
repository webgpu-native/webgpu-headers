

# Queue { #WGPUQueue }


TODO




<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## OnSubmittedWorkDone { #wgpuQueueOnSubmittedWorkDone }

```C
void wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueOnSubmittedWorkDoneCallback callback, WGPU_NULLABLE void * userdata)
```


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## SetLabel { #wgpuQueueSetLabel }

```C
void wgpuQueueSetLabel(WGPUQueue queue, char const * label)
```


TODO




**Arguments:**


 - `label` (`char const *`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## Submit { #wgpuQueueSubmit }

```C
void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands)
```


TODO




**Arguments:**


 - `commands` (``):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## WriteBuffer { #wgpuQueueWriteBuffer }

```C
void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size)
```


TODO




**Arguments:**


 - `buffer` (`WGPUBuffer`):


TODO


 - `bufferOffset` (`uint64_t`):


TODO


 - `data` (`void const *`):


TODO


 - `size` (`size_t`):


TODO







<br/><!-- poor man's styling, just for the demo before we use a non default theme -->
***

## WriteTexture { #wgpuQueueWriteTexture }

```C
void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize)
```


TODO




**Arguments:**


 - `destination` (`WGPUImageCopyTexture const *`):


TODO


 - `data` (`void const *`):


TODO


 - `dataSize` (`size_t`):


TODO


 - `dataLayout` (`WGPUTextureDataLayout const *`):


TODO


 - `writeSize` (`WGPUExtent3D const *`):


TODO






