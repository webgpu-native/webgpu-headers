

# BufferMapAsyncStatus

**NB** All enumerations also have an extra values ending with `_Force32` that is here to ensure that all compilers use the same underlying representation for the enum values. This value must never be used.


TODO

```C
enum WGPUBufferMapAsyncStatus {
        
TODO

    WGPUBufferMapAsyncStatus_Success = 0x00000000,
        
TODO

    WGPUBufferMapAsyncStatus_ValidationError = 0x00000001,
        
TODO

    WGPUBufferMapAsyncStatus_Unknown = 0x00000002,
        
TODO

    WGPUBufferMapAsyncStatus_DeviceLost = 0x00000003,
        
TODO

    WGPUBufferMapAsyncStatus_DestroyedBeforeCallback = 0x00000004,
        
TODO

    WGPUBufferMapAsyncStatus_UnmappedBeforeCallback = 0x00000005,
        
TODO

    WGPUBufferMapAsyncStatus_MappingAlreadyPending = 0x00000006,
        
TODO

    WGPUBufferMapAsyncStatus_OffsetOutOfRange = 0x00000007,
        
TODO


    WGPUBufferMapAsyncStatus_SizeOutOfRange = 0x00000008,
}
```
