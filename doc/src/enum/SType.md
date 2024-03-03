

# SType

**NB** All enumerations also have an extra values ending with `_Force32` that is here to ensure that all compilers use the same underlying representation for the enum values. This value must never be used.


TODO

```C
enum WGPUSType {
        
TODO

    WGPUSType_Invalid = 0x00000000,
        
TODO

    WGPUSType_SurfaceDescriptorFromMetalLayer = 0x00000001,
        
TODO

    WGPUSType_SurfaceDescriptorFromWindowsHWND = 0x00000002,
        
TODO

    WGPUSType_SurfaceDescriptorFromXlibWindow = 0x00000003,
        
TODO

    WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector = 0x00000004,
        
TODO

    WGPUSType_ShaderModuleSPIRVDescriptor = 0x00000005,
        
TODO

    WGPUSType_ShaderModuleWGSLDescriptor = 0x00000006,
        
TODO

    WGPUSType_PrimitiveDepthClipControl = 0x00000007,
        
TODO

    WGPUSType_SurfaceDescriptorFromWaylandSurface = 0x00000008,
        
TODO

    WGPUSType_SurfaceDescriptorFromAndroidNativeWindow = 0x00000009,
        
TODO

    WGPUSType_SurfaceDescriptorFromXcbWindow = 0x0000000A,
        
TODO


    WGPUSType_RenderPassDescriptorMaxDrawCount = 0x0000000F,
}
```
