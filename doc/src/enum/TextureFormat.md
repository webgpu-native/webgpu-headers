

# TextureFormat

**NB** All enumerations also have an extra values ending with `_Force32` that is here to ensure that all compilers use the same underlying representation for the enum values. This value must never be used.


TODO

```C
enum WGPUTextureFormat {
        
TODO

    WGPUTextureFormat_Undefined = 0x00000000,
        
TODO

    WGPUTextureFormat_R8Unorm = 0x00000001,
        
TODO

    WGPUTextureFormat_R8Snorm = 0x00000002,
        
TODO

    WGPUTextureFormat_R8Uint = 0x00000003,
        
TODO

    WGPUTextureFormat_R8Sint = 0x00000004,
        
TODO

    WGPUTextureFormat_R16Uint = 0x00000005,
        
TODO

    WGPUTextureFormat_R16Sint = 0x00000006,
        
TODO

    WGPUTextureFormat_R16Float = 0x00000007,
        
TODO

    WGPUTextureFormat_RG8Unorm = 0x00000008,
        
TODO

    WGPUTextureFormat_RG8Snorm = 0x00000009,
        
TODO

    WGPUTextureFormat_RG8Uint = 0x0000000A,
        
TODO

    WGPUTextureFormat_RG8Sint = 0x0000000B,
        
TODO

    WGPUTextureFormat_R32Float = 0x0000000C,
        
TODO

    WGPUTextureFormat_R32Uint = 0x0000000D,
        
TODO

    WGPUTextureFormat_R32Sint = 0x0000000E,
        
TODO

    WGPUTextureFormat_RG16Uint = 0x0000000F,
        
TODO

    WGPUTextureFormat_RG16Sint = 0x00000010,
        
TODO

    WGPUTextureFormat_RG16Float = 0x00000011,
        
TODO

    WGPUTextureFormat_RGBA8Unorm = 0x00000012,
        
TODO

    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000013,
        
TODO

    WGPUTextureFormat_RGBA8Snorm = 0x00000014,
        
TODO

    WGPUTextureFormat_RGBA8Uint = 0x00000015,
        
TODO

    WGPUTextureFormat_RGBA8Sint = 0x00000016,
        
TODO

    WGPUTextureFormat_BGRA8Unorm = 0x00000017,
        
TODO

    WGPUTextureFormat_BGRA8UnormSrgb = 0x00000018,
        
TODO

    WGPUTextureFormat_RGB10A2Uint = 0x00000019,
        
TODO

    WGPUTextureFormat_RGB10A2Unorm = 0x0000001A,
        
TODO

    WGPUTextureFormat_RG11B10Ufloat = 0x0000001B,
        
TODO

    WGPUTextureFormat_RGB9E5Ufloat = 0x0000001C,
        
TODO

    WGPUTextureFormat_RG32Float = 0x0000001D,
        
TODO

    WGPUTextureFormat_RG32Uint = 0x0000001E,
        
TODO

    WGPUTextureFormat_RG32Sint = 0x0000001F,
        
TODO

    WGPUTextureFormat_RGBA16Uint = 0x00000020,
        
TODO

    WGPUTextureFormat_RGBA16Sint = 0x00000021,
        
TODO

    WGPUTextureFormat_RGBA16Float = 0x00000022,
        
TODO

    WGPUTextureFormat_RGBA32Float = 0x00000023,
        
TODO

    WGPUTextureFormat_RGBA32Uint = 0x00000024,
        
TODO

    WGPUTextureFormat_RGBA32Sint = 0x00000025,
        
TODO

    WGPUTextureFormat_Stencil8 = 0x00000026,
        
TODO

    WGPUTextureFormat_Depth16Unorm = 0x00000027,
        
TODO

    WGPUTextureFormat_Depth24Plus = 0x00000028,
        
TODO

    WGPUTextureFormat_Depth24PlusStencil8 = 0x00000029,
        
TODO

    WGPUTextureFormat_Depth32Float = 0x0000002A,
        
TODO

    WGPUTextureFormat_Depth32FloatStencil8 = 0x0000002B,
        
TODO

    WGPUTextureFormat_BC1RGBAUnorm = 0x0000002C,
        
TODO

    WGPUTextureFormat_BC1RGBAUnormSrgb = 0x0000002D,
        
TODO

    WGPUTextureFormat_BC2RGBAUnorm = 0x0000002E,
        
TODO

    WGPUTextureFormat_BC2RGBAUnormSrgb = 0x0000002F,
        
TODO

    WGPUTextureFormat_BC3RGBAUnorm = 0x00000030,
        
TODO

    WGPUTextureFormat_BC3RGBAUnormSrgb = 0x00000031,
        
TODO

    WGPUTextureFormat_BC4RUnorm = 0x00000032,
        
TODO

    WGPUTextureFormat_BC4RSnorm = 0x00000033,
        
TODO

    WGPUTextureFormat_BC5RGUnorm = 0x00000034,
        
TODO

    WGPUTextureFormat_BC5RGSnorm = 0x00000035,
        
TODO

    WGPUTextureFormat_BC6HRGBUfloat = 0x00000036,
        
TODO

    WGPUTextureFormat_BC6HRGBFloat = 0x00000037,
        
TODO

    WGPUTextureFormat_BC7RGBAUnorm = 0x00000038,
        
TODO

    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x00000039,
        
TODO

    WGPUTextureFormat_ETC2RGB8Unorm = 0x0000003A,
        
TODO

    WGPUTextureFormat_ETC2RGB8UnormSrgb = 0x0000003B,
        
TODO

    WGPUTextureFormat_ETC2RGB8A1Unorm = 0x0000003C,
        
TODO

    WGPUTextureFormat_ETC2RGB8A1UnormSrgb = 0x0000003D,
        
TODO

    WGPUTextureFormat_ETC2RGBA8Unorm = 0x0000003E,
        
TODO

    WGPUTextureFormat_ETC2RGBA8UnormSrgb = 0x0000003F,
        
TODO

    WGPUTextureFormat_EACR11Unorm = 0x00000040,
        
TODO

    WGPUTextureFormat_EACR11Snorm = 0x00000041,
        
TODO

    WGPUTextureFormat_EACRG11Unorm = 0x00000042,
        
TODO

    WGPUTextureFormat_EACRG11Snorm = 0x00000043,
        
TODO

    WGPUTextureFormat_ASTC4x4Unorm = 0x00000044,
        
TODO

    WGPUTextureFormat_ASTC4x4UnormSrgb = 0x00000045,
        
TODO

    WGPUTextureFormat_ASTC5x4Unorm = 0x00000046,
        
TODO

    WGPUTextureFormat_ASTC5x4UnormSrgb = 0x00000047,
        
TODO

    WGPUTextureFormat_ASTC5x5Unorm = 0x00000048,
        
TODO

    WGPUTextureFormat_ASTC5x5UnormSrgb = 0x00000049,
        
TODO

    WGPUTextureFormat_ASTC6x5Unorm = 0x0000004A,
        
TODO

    WGPUTextureFormat_ASTC6x5UnormSrgb = 0x0000004B,
        
TODO

    WGPUTextureFormat_ASTC6x6Unorm = 0x0000004C,
        
TODO

    WGPUTextureFormat_ASTC6x6UnormSrgb = 0x0000004D,
        
TODO

    WGPUTextureFormat_ASTC8x5Unorm = 0x0000004E,
        
TODO

    WGPUTextureFormat_ASTC8x5UnormSrgb = 0x0000004F,
        
TODO

    WGPUTextureFormat_ASTC8x6Unorm = 0x00000050,
        
TODO

    WGPUTextureFormat_ASTC8x6UnormSrgb = 0x00000051,
        
TODO

    WGPUTextureFormat_ASTC8x8Unorm = 0x00000052,
        
TODO

    WGPUTextureFormat_ASTC8x8UnormSrgb = 0x00000053,
        
TODO

    WGPUTextureFormat_ASTC10x5Unorm = 0x00000054,
        
TODO

    WGPUTextureFormat_ASTC10x5UnormSrgb = 0x00000055,
        
TODO

    WGPUTextureFormat_ASTC10x6Unorm = 0x00000056,
        
TODO

    WGPUTextureFormat_ASTC10x6UnormSrgb = 0x00000057,
        
TODO

    WGPUTextureFormat_ASTC10x8Unorm = 0x00000058,
        
TODO

    WGPUTextureFormat_ASTC10x8UnormSrgb = 0x00000059,
        
TODO

    WGPUTextureFormat_ASTC10x10Unorm = 0x0000005A,
        
TODO

    WGPUTextureFormat_ASTC10x10UnormSrgb = 0x0000005B,
        
TODO

    WGPUTextureFormat_ASTC12x10Unorm = 0x0000005C,
        
TODO

    WGPUTextureFormat_ASTC12x10UnormSrgb = 0x0000005D,
        
TODO

    WGPUTextureFormat_ASTC12x12Unorm = 0x0000005E,
        
TODO


    WGPUTextureFormat_ASTC12x12UnormSrgb = 0x0000005F,
}
```
