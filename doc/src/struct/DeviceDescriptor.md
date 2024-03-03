

# DeviceDescriptor { #WGPUDeviceDescriptor }

```C
struct WGPUDeviceDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t requiredFeatureCount;
    WGPUFeatureName const * requiredFeatures;
    WGPU_NULLABLE WGPURequiredLimits const * requiredLimits;
    WGPUQueueDescriptor defaultQueue;
    WGPUDeviceLostCallback deviceLostCallback;
    void * deviceLostUserdata;
};
```


TODO


**Members:**


 - `label` (`char const *`, **nullable**):


TODO


 - `requiredFeatures` (``):


TODO


 - `requiredLimits` (`WGPURequiredLimits const *`, **nullable**):


TODO


 - `defaultQueue` (`WGPUQueueDescriptor`):


TODO


 - `deviceLostCallback` (`WGPUDeviceLostCallback`):


TODO


 - `deviceLostUserdata` (`void *`):


TODO




