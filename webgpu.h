#ifndef WGPU_WGPU_H_
#define WGPU_WGPU_H_

#if !defined(WGPU_EXPORT)
#    if defined(_WIN32)
#        if defined(WGPU_IMPLEMENTATION)
#            define WGPU_EXPORT __declspec(dllexport)
#        else
#            define WGPU_EXPORT __declspec(dllimport)
#        endif
#    else  // defined(_WIN32)
#        if defined(WGPU_IMPLEMENTATION)
#            define WGPU_EXPORT __attribute__((visibility("default")))
#        else
#            define WGPU_EXPORT
#        endif
#    endif  // defined(_WIN32)
#endif  // defined(WGPU_EXPORT)

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

const uint64_t WGPU_WHOLE_SIZE = 0xffffffffffffffffULL; // UINT64_MAX

typedef struct WGPUBindGroupImpl* WGPUBindGroup;
typedef struct WGPUBindGroupLayoutImpl* WGPUBindGroupLayout;
typedef struct WGPUBufferImpl* WGPUBuffer;
typedef struct WGPUCommandBufferImpl* WGPUCommandBuffer;
typedef struct WGPUCommandEncoderImpl* WGPUCommandEncoder;
typedef struct WGPUComputePassEncoderImpl* WGPUComputePassEncoder;
typedef struct WGPUComputePipelineImpl* WGPUComputePipeline;
typedef struct WGPUDeviceImpl* WGPUDevice;
typedef struct WGPUFenceImpl* WGPUFence;
typedef struct WGPUPipelineLayoutImpl* WGPUPipelineLayout;
typedef struct WGPUQueueImpl* WGPUQueue;
typedef struct WGPURenderPassEncoderImpl* WGPURenderPassEncoder;
typedef struct WGPURenderPipelineImpl* WGPURenderPipeline;
typedef struct WGPUSamplerImpl* WGPUSampler;
typedef struct WGPUShaderModuleImpl* WGPUShaderModule;
typedef struct WGPUTextureImpl* WGPUTexture;
typedef struct WGPUTextureViewImpl* WGPUTextureView;

typedef enum {
    WGPUAddressMode_Repeat = 0x00000000,
    WGPUAddressMode_MirrorRepeat = 0x00000001,
    WGPUAddressMode_ClampToEdge = 0x00000002,
    WGPUAddressMode_Force32 = 0x7FFFFFFF
} WGPUAddressMode;

typedef enum {
    WGPUBindingType_UniformBuffer = 0x00000000,
    WGPUBindingType_StorageBuffer = 0x00000001,
    WGPUBindingType_ReadonlyStorageBuffer = 0x00000002,
    WGPUBindingType_Sampler = 0x00000003,
    WGPUBindingType_SampledTexture = 0x00000004,
    WGPUBindingType_StorageTexture = 0x00000005,
    WGPUBindingType_Force32 = 0x7FFFFFFF
} WGPUBindingType;

typedef enum {
    WGPUBlendFactor_Zero = 0x00000000,
    WGPUBlendFactor_One = 0x00000001,
    WGPUBlendFactor_SrcColor = 0x00000002,
    WGPUBlendFactor_OneMinusSrcColor = 0x00000003,
    WGPUBlendFactor_SrcAlpha = 0x00000004,
    WGPUBlendFactor_OneMinusSrcAlpha = 0x00000005,
    WGPUBlendFactor_DstColor = 0x00000006,
    WGPUBlendFactor_OneMinusDstColor = 0x00000007,
    WGPUBlendFactor_DstAlpha = 0x00000008,
    WGPUBlendFactor_OneMinusDstAlpha = 0x00000009,
    WGPUBlendFactor_SrcAlphaSaturated = 0x0000000A,
    WGPUBlendFactor_BlendColor = 0x0000000B,
    WGPUBlendFactor_OneMinusBlendColor = 0x0000000C,
    WGPUBlendFactor_Force32 = 0x7FFFFFFF
} WGPUBlendFactor;

typedef enum {
    WGPUBlendOperation_Add = 0x00000000,
    WGPUBlendOperation_Subtract = 0x00000001,
    WGPUBlendOperation_ReverseSubtract = 0x00000002,
    WGPUBlendOperation_Min = 0x00000003,
    WGPUBlendOperation_Max = 0x00000004,
    WGPUBlendOperation_Force32 = 0x7FFFFFFF
} WGPUBlendOperation;

typedef enum {
    WGPUBufferMapAsyncStatus_Success = 0x00000000,
    WGPUBufferMapAsyncStatus_Error = 0x00000001,
    WGPUBufferMapAsyncStatus_Unknown = 0x00000002,
    WGPUBufferMapAsyncStatus_ContextLost = 0x00000003,
    WGPUBufferMapAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUBufferMapAsyncStatus;

typedef enum {
    WGPUCompareFunction_Never = 0x00000000,
    WGPUCompareFunction_Less = 0x00000001,
    WGPUCompareFunction_LessEqual = 0x00000002,
    WGPUCompareFunction_Greater = 0x00000003,
    WGPUCompareFunction_GreaterEqual = 0x00000004,
    WGPUCompareFunction_Equal = 0x00000005,
    WGPUCompareFunction_NotEqual = 0x00000006,
    WGPUCompareFunction_Always = 0x00000007,
    WGPUCompareFunction_Force32 = 0x7FFFFFFF
} WGPUCompareFunction;

typedef enum {
    WGPUCullMode_None = 0x00000000,
    WGPUCullMode_Front = 0x00000001,
    WGPUCullMode_Back = 0x00000002,
    WGPUCullMode_Force32 = 0x7FFFFFFF
} WGPUCullMode;

typedef enum {
    WGPUFenceCompletionStatus_Success = 0x00000000,
    WGPUFenceCompletionStatus_Error = 0x00000001,
    WGPUFenceCompletionStatus_Unknown = 0x00000002,
    WGPUFenceCompletionStatus_ContextLost = 0x00000003,
    WGPUFenceCompletionStatus_Force32 = 0x7FFFFFFF
} WGPUFenceCompletionStatus;

typedef enum {
    WGPUFilterMode_Nearest = 0x00000000,
    WGPUFilterMode_Linear = 0x00000001,
    WGPUFilterMode_Force32 = 0x7FFFFFFF
} WGPUFilterMode;

typedef enum {
    WGPUFrontFace_CCW = 0x00000000,
    WGPUFrontFace_CW = 0x00000001,
    WGPUFrontFace_Force32 = 0x7FFFFFFF
} WGPUFrontFace;

typedef enum {
    WGPUIndexFormat_Uint16 = 0x00000000,
    WGPUIndexFormat_Uint32 = 0x00000001,
    WGPUIndexFormat_Force32 = 0x7FFFFFFF
} WGPUIndexFormat;

typedef enum {
    WGPUInputStepMode_Vertex = 0x00000000,
    WGPUInputStepMode_Instance = 0x00000001,
    WGPUInputStepMode_Force32 = 0x7FFFFFFF
} WGPUInputStepMode;

typedef enum {
    WGPULoadOp_Clear = 0x00000000,
    WGPULoadOp_Load = 0x00000001,
    WGPULoadOp_Force32 = 0x7FFFFFFF
} WGPULoadOp;

typedef enum {
    WGPUPrimitiveTopology_PointList = 0x00000000,
    WGPUPrimitiveTopology_LineList = 0x00000001,
    WGPUPrimitiveTopology_LineStrip = 0x00000002,
    WGPUPrimitiveTopology_TriangleList = 0x00000003,
    WGPUPrimitiveTopology_TriangleStrip = 0x00000004,
    WGPUPrimitiveTopology_Force32 = 0x7FFFFFFF
} WGPUPrimitiveTopology;

typedef enum {
    WGPUStencilOperation_Keep = 0x00000000,
    WGPUStencilOperation_Zero = 0x00000001,
    WGPUStencilOperation_Replace = 0x00000002,
    WGPUStencilOperation_Invert = 0x00000003,
    WGPUStencilOperation_IncrementClamp = 0x00000004,
    WGPUStencilOperation_DecrementClamp = 0x00000005,
    WGPUStencilOperation_IncrementWrap = 0x00000006,
    WGPUStencilOperation_DecrementWrap = 0x00000007,
    WGPUStencilOperation_Force32 = 0x7FFFFFFF
} WGPUStencilOperation;

typedef enum {
    WGPUStoreOp_Store = 0x00000000,
    WGPUStoreOp_Force32 = 0x7FFFFFFF
} WGPUStoreOp;

typedef enum {
    WGPUStructureType_Default = 0x00000000,
    WGPUStructureType_TodoPutTheRest = 0x00000001,
    WGPUStructureType_Force32 = 0x7FFFFFFF
} WGPUStructureType;

typedef enum {
    WGPUTextureAspect_All = 0x00000000,
    WGPUTextureAspect_StencilOnly = 0x00000001,
    WGPUTextureAspect_DepthOnly = 0x00000002,
    WGPUTextureAspect_Force32 = 0x7FFFFFFF
} WGPUTextureAspect;

typedef enum {
    WGPUTextureDimension_1D = 0x00000000,
    WGPUTextureDimension_2D = 0x00000001,
    WGPUTextureDimension_3D = 0x00000002,
    WGPUTextureDimension_Force32 = 0x7FFFFFFF
} WGPUTextureDimension;

typedef enum {
    WGPUTextureFormat_R8Unorm = 0x00000000,
    WGPUTextureFormat_R8Snorm = 0x00000001,
    WGPUTextureFormat_R8Uint = 0x00000002,
    WGPUTextureFormat_R8Sint = 0x00000003,
    WGPUTextureFormat_R16Unorm = 0x00000004,
    WGPUTextureFormat_R16Snorm = 0x00000005,
    WGPUTextureFormat_R16Uint = 0x00000006,
    WGPUTextureFormat_R16Sint = 0x00000007,
    WGPUTextureFormat_R16Float = 0x00000008,
    WGPUTextureFormat_RG8Unorm = 0x00000009,
    WGPUTextureFormat_RG8Snorm = 0x0000000A,
    WGPUTextureFormat_RG8Uint = 0x0000000B,
    WGPUTextureFormat_RG8Sint = 0x0000000C,
    WGPUTextureFormat_R32Float = 0x0000000D,
    WGPUTextureFormat_R32Uint = 0x0000000E,
    WGPUTextureFormat_R32Sint = 0x0000000F,
    WGPUTextureFormat_RG16Unorm = 0x00000010,
    WGPUTextureFormat_RG16Snorm = 0x00000011,
    WGPUTextureFormat_RG16Uint = 0x00000012,
    WGPUTextureFormat_RG16Sint = 0x00000013,
    WGPUTextureFormat_RG16Float = 0x00000014,
    WGPUTextureFormat_RGBA8Unorm = 0x00000015,
    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000016,
    WGPUTextureFormat_RGBA8Snorm = 0x00000017,
    WGPUTextureFormat_RGBA8Uint = 0x00000018,
    WGPUTextureFormat_RGBA8Sint = 0x00000019,
    WGPUTextureFormat_BGRA8Unorm = 0x0000001A,
    WGPUTextureFormat_BGRA8UnormSrgb = 0x0000001B,
    WGPUTextureFormat_RGB10A2Unorm = 0x0000001C,
    WGPUTextureFormat_RG11B10Float = 0x0000001D,
    WGPUTextureFormat_RG32Float = 0x0000001E,
    WGPUTextureFormat_RG32Uint = 0x0000001F,
    WGPUTextureFormat_RG32Sint = 0x00000020,
    WGPUTextureFormat_RGBA16Unorm = 0x00000021,
    WGPUTextureFormat_RGBA16Snorm = 0x00000022,
    WGPUTextureFormat_RGBA16Uint = 0x00000023,
    WGPUTextureFormat_RGBA16Sint = 0x00000024,
    WGPUTextureFormat_RGBA16Float = 0x00000025,
    WGPUTextureFormat_RGBA32Float = 0x00000026,
    WGPUTextureFormat_RGBA32Uint = 0x00000027,
    WGPUTextureFormat_RGBA32Sint = 0x00000028,
    WGPUTextureFormat_Depth32Float = 0x00000029,
    WGPUTextureFormat_Depth24Plus = 0x0000002A,
    WGPUTextureFormat_Depth24PlusStencil8 = 0x0000002B,
    WGPUTextureFormat_BC1RGBAUnorm = 0x0000002C,
    WGPUTextureFormat_BC1RGBAUnormSrgb = 0x0000002D,
    WGPUTextureFormat_BC2RGBAUnorm = 0x0000002E,
    WGPUTextureFormat_BC2RGBAUnormSrgb = 0x0000002F,
    WGPUTextureFormat_BC3RGBAUnorm = 0x00000030,
    WGPUTextureFormat_BC3RGBAUnormSrgb = 0x00000031,
    WGPUTextureFormat_BC4RUnorm = 0x00000032,
    WGPUTextureFormat_BC4RSnorm = 0x00000033,
    WGPUTextureFormat_BC5RGUnorm = 0x00000034,
    WGPUTextureFormat_BC5RGSnorm = 0x00000035,
    WGPUTextureFormat_BC6HRGBUfloat = 0x00000036,
    WGPUTextureFormat_BC6HRGBSfloat = 0x00000037,
    WGPUTextureFormat_BC7RGBAUnorm = 0x00000038,
    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x00000039,
    WGPUTextureFormat_Force32 = 0x7FFFFFFF
} WGPUTextureFormat;

typedef enum {
    WGPUTextureViewDimension_1D = 0x00000000,
    WGPUTextureViewDimension_2D = 0x00000001,
    WGPUTextureViewDimension_2DArray = 0x00000002,
    WGPUTextureViewDimension_Cube = 0x00000003,
    WGPUTextureViewDimension_CubeArray = 0x00000004,
    WGPUTextureViewDimension_3D = 0x00000005,
    WGPUTextureViewDimension_Force32 = 0x7FFFFFFF
} WGPUTextureViewDimension;

typedef enum {
    WGPUVertexFormat_UChar2 = 0x00000000,
    WGPUVertexFormat_UChar4 = 0x00000001,
    WGPUVertexFormat_Char2 = 0x00000002,
    WGPUVertexFormat_Char4 = 0x00000003,
    WGPUVertexFormat_UChar2Norm = 0x00000004,
    WGPUVertexFormat_UChar4Norm = 0x00000005,
    WGPUVertexFormat_Char2Norm = 0x00000006,
    WGPUVertexFormat_Char4Norm = 0x00000007,
    WGPUVertexFormat_UShort2 = 0x00000008,
    WGPUVertexFormat_UShort4 = 0x00000009,
    WGPUVertexFormat_Short2 = 0x0000000A,
    WGPUVertexFormat_Short4 = 0x0000000B,
    WGPUVertexFormat_UShort2Norm = 0x0000000C,
    WGPUVertexFormat_UShort4Norm = 0x0000000D,
    WGPUVertexFormat_Short2Norm = 0x0000000E,
    WGPUVertexFormat_Short4Norm = 0x0000000F,
    WGPUVertexFormat_Half2 = 0x00000010,
    WGPUVertexFormat_Half4 = 0x00000011,
    WGPUVertexFormat_Float = 0x00000012,
    WGPUVertexFormat_Float2 = 0x00000013,
    WGPUVertexFormat_Float3 = 0x00000014,
    WGPUVertexFormat_Float4 = 0x00000015,
    WGPUVertexFormat_UInt = 0x00000016,
    WGPUVertexFormat_UInt2 = 0x00000017,
    WGPUVertexFormat_UInt3 = 0x00000018,
    WGPUVertexFormat_UInt4 = 0x00000019,
    WGPUVertexFormat_Int = 0x0000001A,
    WGPUVertexFormat_Int2 = 0x0000001B,
    WGPUVertexFormat_Int3 = 0x0000001C,
    WGPUVertexFormat_Int4 = 0x0000001D,
    WGPUVertexFormat_Force32 = 0x7FFFFFFF
} WGPUVertexFormat;

typedef enum {
    WGPUBufferUsageBit_None = 0x00000000,
    WGPUBufferUsageBit_MapRead = 0x00000001,
    WGPUBufferUsageBit_MapWrite = 0x00000002,
    WGPUBufferUsageBit_CopySrc = 0x00000004,
    WGPUBufferUsageBit_CopyDst = 0x00000008,
    WGPUBufferUsageBit_Index = 0x00000010,
    WGPUBufferUsageBit_Vertex = 0x00000020,
    WGPUBufferUsageBit_Uniform = 0x00000040,
    WGPUBufferUsageBit_Storage = 0x00000080,
    WGPUBufferUsageBit_Indirect = 0x00000100,
    WGPUBufferUsageBit_Force32 = 0x7FFFFFFF
} WGPUBufferUsageBit;

typedef enum {
    WGPUColorWriteMask_None = 0x00000000,
    WGPUColorWriteMask_Red = 0x00000001,
    WGPUColorWriteMask_Green = 0x00000002,
    WGPUColorWriteMask_Blue = 0x00000004,
    WGPUColorWriteMask_Alpha = 0x00000008,
    WGPUColorWriteMask_All = 0x0000000F,
    WGPUColorWriteMask_Force32 = 0x7FFFFFFF
} WGPUColorWriteMask;

typedef enum {
    WGPUFace_None = 0x00000000,
    WGPUFace_Back = 0x00000001,
    WGPUFace_Front = 0x00000002,
    WGPUFace_Both = 0x00000003,
    WGPUFace_Force32 = 0x7FFFFFFF
} WGPUFace;

typedef enum {
    WGPUShaderStageBit_None = 0x00000000,
    WGPUShaderStageBit_Vertex = 0x00000001,
    WGPUShaderStageBit_Fragment = 0x00000002,
    WGPUShaderStageBit_Compute = 0x00000004,
    WGPUShaderStageBit_Force32 = 0x7FFFFFFF
} WGPUShaderStageBit;

typedef enum {
    WGPUTextureUsageBit_None = 0x00000000,
    WGPUTextureUsageBit_CopySrc = 0x00000001,
    WGPUTextureUsageBit_CopyDst = 0x00000002,
    WGPUTextureUsageBit_Sampled = 0x00000004,
    WGPUTextureUsageBit_Storage = 0x00000008,
    WGPUTextureUsageBit_OutputAttachment = 0x00000010,
    WGPUTextureUsageBit_Force32 = 0x7FFFFFFF
} WGPUTextureUsageBit;


typedef struct WGPUBindGroupBinding {
    uint32_t binding;
    WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
    WGPUSampler sampler;
    WGPUTextureView textureView;
} WGPUBindGroupBinding;

typedef struct WGPUBindGroupLayoutBinding {
    uint32_t binding;
    WGPUShaderStageBit visibility;
    WGPUBindingType type;
    bool dynamic;
    bool multisampled;
    WGPUTextureViewDimension textureDimension;
} WGPUBindGroupLayoutBinding;

typedef struct WGPUBlendDescriptor {
    WGPUBlendOperation operation;
    WGPUBlendFactor srcFactor;
    WGPUBlendFactor dstFactor;
} WGPUBlendDescriptor;

typedef struct WGPUBufferCopyView {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUBuffer buffer;
    uint64_t offset;
    uint32_t rowPitch;
    uint32_t imageHeight;
} WGPUBufferCopyView;

typedef struct WGPUBufferDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUBufferUsageBit usage;
    uint64_t size;
} WGPUBufferDescriptor;

typedef struct WGPUColor {
    float r;
    float g;
    float b;
    float a;
} WGPUColor;

typedef struct WGPUCommandBufferDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
} WGPUCommandBufferDescriptor;

typedef struct WGPUCommandEncoderDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
} WGPUCommandEncoderDescriptor;

typedef struct WGPUComputePassDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
} WGPUComputePassDescriptor;

typedef struct WGPUCreateBufferMappedResult {
    WGPUBuffer buffer;
    uint64_t dataLength;
    void * data;
} WGPUCreateBufferMappedResult;

typedef struct WGPUExtent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} WGPUExtent3D;

typedef struct WGPUFenceDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    uint64_t initialValue;
} WGPUFenceDescriptor;

typedef struct WGPUOrigin3D {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} WGPUOrigin3D;

typedef struct WGPUPipelineLayoutDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    uint32_t bindGroupLayoutCount;
    WGPUBindGroupLayout const * bindGroupLayouts;
} WGPUPipelineLayoutDescriptor;

typedef struct WGPUPipelineStageDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUShaderModule module;
    char const * entryPoint;
} WGPUPipelineStageDescriptor;

typedef struct WGPURasterizationStateDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUFrontFace frontFace;
    WGPUCullMode cullMode;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
} WGPURasterizationStateDescriptor;

typedef struct WGPURenderPassDepthStencilAttachmentDescriptor {
    WGPUTextureView attachment;
    WGPULoadOp depthLoadOp;
    WGPUStoreOp depthStoreOp;
    float clearDepth;
    WGPULoadOp stencilLoadOp;
    WGPUStoreOp stencilStoreOp;
    uint32_t clearStencil;
} WGPURenderPassDepthStencilAttachmentDescriptor;

typedef struct WGPUSamplerDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;
} WGPUSamplerDescriptor;

typedef struct WGPUShaderModuleDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    uint32_t codeSize;
    uint32_t const * code;
} WGPUShaderModuleDescriptor;

typedef struct WGPUStencilStateFaceDescriptor {
    WGPUCompareFunction compare;
    WGPUStencilOperation failOp;
    WGPUStencilOperation depthFailOp;
    WGPUStencilOperation passOp;
} WGPUStencilStateFaceDescriptor;

typedef struct WGPUTextureViewDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUTextureFormat format;
    WGPUTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    WGPUTextureAspect aspect;
} WGPUTextureViewDescriptor;

typedef struct WGPUVertexAttributeDescriptor {
    uint32_t shaderLocation;
    uint64_t offset;
    WGPUVertexFormat format;
} WGPUVertexAttributeDescriptor;

typedef struct WGPUBindGroupDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUBindGroupLayout layout;
    uint32_t bindingCount;
    WGPUBindGroupBinding const * bindings;
} WGPUBindGroupDescriptor;

typedef struct WGPUBindGroupLayoutDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    uint32_t bindingCount;
    WGPUBindGroupLayoutBinding const * bindings;
} WGPUBindGroupLayoutDescriptor;

typedef struct WGPUColorStateDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUTextureFormat format;
    WGPUBlendDescriptor alphaBlend;
    WGPUBlendDescriptor colorBlend;
    WGPUColorWriteMask writeMask;
} WGPUColorStateDescriptor;

typedef struct WGPUComputePipelineDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUPipelineLayout layout;
    WGPUPipelineStageDescriptor const * computeStage;
} WGPUComputePipelineDescriptor;

typedef struct WGPUDepthStencilStateDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUTextureFormat format;
    bool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilStateFaceDescriptor stencilFront;
    WGPUStencilStateFaceDescriptor stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
} WGPUDepthStencilStateDescriptor;

typedef struct WGPURenderPassColorAttachmentDescriptor {
    WGPUTextureView attachment;
    WGPUTextureView resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColor clearColor;
} WGPURenderPassColorAttachmentDescriptor;

typedef struct WGPUTextureCopyView {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUTexture texture;
    uint32_t mipLevel;
    uint32_t arrayLayer;
    WGPUOrigin3D origin;
} WGPUTextureCopyView;

typedef struct WGPUTextureDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUTextureUsageBit usage;
    WGPUTextureDimension dimension;
    WGPUExtent3D size;
    uint32_t arrayLayerCount;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
} WGPUTextureDescriptor;

typedef struct WGPUVertexBufferDescriptor {
    uint64_t stride;
    WGPUInputStepMode stepMode;
    uint32_t attributeCount;
    WGPUVertexAttributeDescriptor const * attributes;
} WGPUVertexBufferDescriptor;

typedef struct WGPURenderPassDescriptor {
    uint32_t colorAttachmentCount;
    const WGPURenderPassColorAttachmentDescriptor* const * colorAttachments;
    WGPURenderPassDepthStencilAttachmentDescriptor const * depthStencilAttachment;
} WGPURenderPassDescriptor;

typedef struct WGPUVertexInputDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUIndexFormat indexFormat;
    uint32_t bufferCount;
    WGPUVertexBufferDescriptor const * buffers;
} WGPUVertexInputDescriptor;

typedef struct WGPURenderPipelineDescriptor {
    void const * nextInChain;
    WGPUStructureType structureType;
    WGPUPipelineLayout layout;
    WGPUPipelineStageDescriptor const * vertexStage;
    WGPUPipelineStageDescriptor const * fragmentStage;
    WGPUVertexInputDescriptor const * vertexInput;
    WGPUPrimitiveTopology primitiveTopology;
    WGPURasterizationStateDescriptor const * rasterizationState;
    uint32_t sampleCount;
    WGPUDepthStencilStateDescriptor const * depthStencilState;
    uint32_t colorStateCount;
    const WGPUColorStateDescriptor* const * colorStates;
    uint32_t sampleMask;
    bool alphaToCoverageEnabled;
} WGPURenderPipelineDescriptor;


typedef void (*WGPUBufferCreateMappedCallback)(WGPUBufferMapAsyncStatus status,
                                               WGPUCreateBufferMappedResult result,
                                               void* userdata);
typedef void (*WGPUBufferMapReadCallback)(WGPUBufferMapAsyncStatus status,
                                          const void* data,
                                          uint64_t dataLength,
                                          void* userdata);
typedef void (*WGPUBufferMapWriteCallback)(WGPUBufferMapAsyncStatus status,
                                           void* data,
                                           uint64_t dataLength,
                                           void* userdata);
typedef void (*WGPUFenceOnCompletionCallback)(WGPUFenceCompletionStatus status, void* userdata);

#ifdef __cplusplus
extern "C" {
#endif

// Procs of BindGroup
typedef void (*WGPUProcBindGroupReference)(WGPUBindGroup bindGroup);
typedef void (*WGPUProcBindGroupRelease)(WGPUBindGroup bindGroup);

// Procs of BindGroupLayout
typedef void (*WGPUProcBindGroupLayoutReference)(WGPUBindGroupLayout bindGroupLayout);
typedef void (*WGPUProcBindGroupLayoutRelease)(WGPUBindGroupLayout bindGroupLayout);

// Procs of Buffer
typedef void (*WGPUProcBufferUnmap)(WGPUBuffer buffer);
typedef void (*WGPUProcBufferDestroy)(WGPUBuffer buffer);
typedef void (*WGPUProcBufferMapReadAsync)(WGPUBuffer buffer, WGPUBufferMapReadCallback callback, void * userdata);
typedef void (*WGPUProcBufferMapWriteAsync)(WGPUBuffer buffer, WGPUBufferMapWriteCallback callback, void * userdata);
typedef void (*WGPUProcBufferReference)(WGPUBuffer buffer);
typedef void (*WGPUProcBufferRelease)(WGPUBuffer buffer);

// Procs of CommandBuffer
typedef void (*WGPUProcCommandBufferReference)(WGPUCommandBuffer commandBuffer);
typedef void (*WGPUProcCommandBufferRelease)(WGPUCommandBuffer commandBuffer);

// Procs of CommandEncoder
typedef WGPUCommandBuffer (*WGPUProcCommandEncoderFinish)(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor);
typedef WGPUComputePassEncoder (*WGPUProcCommandEncoderBeginComputePass)(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor);
typedef WGPURenderPassEncoder (*WGPUProcCommandEncoderBeginRenderPass)(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor);
typedef void (*WGPUProcCommandEncoderCopyBufferToBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
typedef void (*WGPUProcCommandEncoderCopyBufferToTexture)(WGPUCommandEncoder commandEncoder, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
typedef void (*WGPUProcCommandEncoderCopyTextureToBuffer)(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize);
typedef void (*WGPUProcCommandEncoderCopyTextureToTexture)(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
typedef void (*WGPUProcCommandEncoderInsertDebugMarker)(WGPUCommandEncoder commandEncoder, char const * groupLabel);
typedef void (*WGPUProcCommandEncoderPopDebugGroup)(WGPUCommandEncoder commandEncoder);
typedef void (*WGPUProcCommandEncoderPushDebugGroup)(WGPUCommandEncoder commandEncoder, char const * groupLabel);
typedef void (*WGPUProcCommandEncoderReference)(WGPUCommandEncoder commandEncoder);
typedef void (*WGPUProcCommandEncoderRelease)(WGPUCommandEncoder commandEncoder);

// Procs of ComputePassEncoder
typedef void (*WGPUProcComputePassEncoderInsertDebugMarker)(WGPUComputePassEncoder computePassEncoder, char const * groupLabel);
typedef void (*WGPUProcComputePassEncoderPopDebugGroup)(WGPUComputePassEncoder computePassEncoder);
typedef void (*WGPUProcComputePassEncoderPushDebugGroup)(WGPUComputePassEncoder computePassEncoder, char const * groupLabel);
typedef void (*WGPUProcComputePassEncoderSetPipeline)(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline);
typedef void (*WGPUProcComputePassEncoderSetBindGroup)(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
typedef void (*WGPUProcComputePassEncoderDispatch)(WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z);
typedef void (*WGPUProcComputePassEncoderDispatchIndirect)(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*WGPUProcComputePassEncoderEndPass)(WGPUComputePassEncoder computePassEncoder);
typedef void (*WGPUProcComputePassEncoderReference)(WGPUComputePassEncoder computePassEncoder);
typedef void (*WGPUProcComputePassEncoderRelease)(WGPUComputePassEncoder computePassEncoder);

// Procs of ComputePipeline
typedef void (*WGPUProcComputePipelineReference)(WGPUComputePipeline computePipeline);
typedef void (*WGPUProcComputePipelineRelease)(WGPUComputePipeline computePipeline);

// Procs of Device
typedef WGPUBindGroup (*WGPUProcDeviceCreateBindGroup)(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor);
typedef WGPUBindGroupLayout (*WGPUProcDeviceCreateBindGroupLayout)(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor);
typedef WGPUBuffer (*WGPUProcDeviceCreateBuffer)(WGPUDevice device, WGPUBufferDescriptor const * descriptor);
typedef WGPUCreateBufferMappedResult (*WGPUProcDeviceCreateBufferMapped)(WGPUDevice device, WGPUBufferDescriptor const * descriptor);
typedef WGPUCommandEncoder (*WGPUProcDeviceCreateCommandEncoder)(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor);
typedef WGPUComputePipeline (*WGPUProcDeviceCreateComputePipeline)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor);
typedef WGPURenderPipeline (*WGPUProcDeviceCreateRenderPipeline)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor);
typedef WGPUPipelineLayout (*WGPUProcDeviceCreatePipelineLayout)(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor);
typedef WGPUQueue (*WGPUProcDeviceCreateQueue)(WGPUDevice device);
typedef WGPUSampler (*WGPUProcDeviceCreateSampler)(WGPUDevice device, WGPUSamplerDescriptor const * descriptor);
typedef WGPUShaderModule (*WGPUProcDeviceCreateShaderModule)(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor);
typedef WGPUTexture (*WGPUProcDeviceCreateTexture)(WGPUDevice device, WGPUTextureDescriptor const * descriptor);
typedef void (*WGPUProcDeviceCreateBufferMappedAsync)(WGPUDevice device, WGPUBufferDescriptor const * descriptor, WGPUBufferCreateMappedCallback callback, void * userdata);
typedef void (*WGPUProcDeviceReference)(WGPUDevice device);
typedef void (*WGPUProcDeviceRelease)(WGPUDevice device);

// Procs of Fence
typedef uint64_t (*WGPUProcFenceGetCompletedValue)(WGPUFence fence);
typedef void (*WGPUProcFenceOnCompletion)(WGPUFence fence, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata);
typedef void (*WGPUProcFenceReference)(WGPUFence fence);
typedef void (*WGPUProcFenceRelease)(WGPUFence fence);

// Procs of PipelineLayout
typedef void (*WGPUProcPipelineLayoutReference)(WGPUPipelineLayout pipelineLayout);
typedef void (*WGPUProcPipelineLayoutRelease)(WGPUPipelineLayout pipelineLayout);

// Procs of Queue
typedef void (*WGPUProcQueueSubmit)(WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands);
typedef void (*WGPUProcQueueSignal)(WGPUQueue queue, WGPUFence fence, uint64_t signalValue);
typedef WGPUFence (*WGPUProcQueueCreateFence)(WGPUQueue queue, WGPUFenceDescriptor const * descriptor);
typedef void (*WGPUProcQueueReference)(WGPUQueue queue);
typedef void (*WGPUProcQueueRelease)(WGPUQueue queue);

// Procs of RenderPassEncoder
typedef void (*WGPUProcRenderPassEncoderSetPipeline)(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline);
typedef void (*WGPUProcRenderPassEncoderSetBindGroup)(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
typedef void (*WGPUProcRenderPassEncoderDraw)(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
typedef void (*WGPUProcRenderPassEncoderDrawIndexed)(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
typedef void (*WGPUProcRenderPassEncoderDrawIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*WGPUProcRenderPassEncoderDrawIndexedIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*WGPUProcRenderPassEncoderInsertDebugMarker)(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel);
typedef void (*WGPUProcRenderPassEncoderPopDebugGroup)(WGPURenderPassEncoder renderPassEncoder);
typedef void (*WGPUProcRenderPassEncoderPushDebugGroup)(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel);
typedef void (*WGPUProcRenderPassEncoderSetStencilReference)(WGPURenderPassEncoder renderPassEncoder, uint32_t reference);
typedef void (*WGPUProcRenderPassEncoderSetBlendColor)(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color);
typedef void (*WGPUProcRenderPassEncoderSetViewport)(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth);
typedef void (*WGPUProcRenderPassEncoderSetScissorRect)(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
typedef void (*WGPUProcRenderPassEncoderSetVertexBuffers)(WGPURenderPassEncoder renderPassEncoder, uint32_t startSlot, uint32_t count, WGPUBuffer const * buffers, uint64_t const * offsets);
typedef void (*WGPUProcRenderPassEncoderSetIndexBuffer)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, uint64_t offset);
typedef void (*WGPUProcRenderPassEncoderEndPass)(WGPURenderPassEncoder renderPassEncoder);
typedef void (*WGPUProcRenderPassEncoderReference)(WGPURenderPassEncoder renderPassEncoder);
typedef void (*WGPUProcRenderPassEncoderRelease)(WGPURenderPassEncoder renderPassEncoder);

// Procs of RenderPipeline
typedef void (*WGPUProcRenderPipelineReference)(WGPURenderPipeline renderPipeline);
typedef void (*WGPUProcRenderPipelineRelease)(WGPURenderPipeline renderPipeline);

// Procs of Sampler
typedef void (*WGPUProcSamplerReference)(WGPUSampler sampler);
typedef void (*WGPUProcSamplerRelease)(WGPUSampler sampler);

// Procs of ShaderModule
typedef void (*WGPUProcShaderModuleReference)(WGPUShaderModule shaderModule);
typedef void (*WGPUProcShaderModuleRelease)(WGPUShaderModule shaderModule);

// Procs of Texture
typedef WGPUTextureView (*WGPUProcTextureCreateDefaultView)(WGPUTexture texture);
typedef WGPUTextureView (*WGPUProcTextureCreateView)(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor);
typedef void (*WGPUProcTextureDestroy)(WGPUTexture texture);
typedef void (*WGPUProcTextureReference)(WGPUTexture texture);
typedef void (*WGPUProcTextureRelease)(WGPUTexture texture);

// Procs of TextureView
typedef void (*WGPUProcTextureViewReference)(WGPUTextureView textureView);
typedef void (*WGPUProcTextureViewRelease)(WGPUTextureView textureView);


struct WGPUProcTable_s {
    WGPUProcBindGroupReference bindGroupReference;
    WGPUProcBindGroupRelease bindGroupRelease;

    WGPUProcBindGroupLayoutReference bindGroupLayoutReference;
    WGPUProcBindGroupLayoutRelease bindGroupLayoutRelease;

    WGPUProcBufferUnmap bufferUnmap;
    WGPUProcBufferDestroy bufferDestroy;
    WGPUProcBufferMapReadAsync bufferMapReadAsync;
    WGPUProcBufferMapWriteAsync bufferMapWriteAsync;
    WGPUProcBufferReference bufferReference;
    WGPUProcBufferRelease bufferRelease;

    WGPUProcCommandBufferReference commandBufferReference;
    WGPUProcCommandBufferRelease commandBufferRelease;

    WGPUProcCommandEncoderFinish commandEncoderFinish;
    WGPUProcCommandEncoderBeginComputePass commandEncoderBeginComputePass;
    WGPUProcCommandEncoderBeginRenderPass commandEncoderBeginRenderPass;
    WGPUProcCommandEncoderCopyBufferToBuffer commandEncoderCopyBufferToBuffer;
    WGPUProcCommandEncoderCopyBufferToTexture commandEncoderCopyBufferToTexture;
    WGPUProcCommandEncoderCopyTextureToBuffer commandEncoderCopyTextureToBuffer;
    WGPUProcCommandEncoderCopyTextureToTexture commandEncoderCopyTextureToTexture;
    WGPUProcCommandEncoderInsertDebugMarker commandEncoderInsertDebugMarker;
    WGPUProcCommandEncoderPopDebugGroup commandEncoderPopDebugGroup;
    WGPUProcCommandEncoderPushDebugGroup commandEncoderPushDebugGroup;
    WGPUProcCommandEncoderReference commandEncoderReference;
    WGPUProcCommandEncoderRelease commandEncoderRelease;

    WGPUProcComputePassEncoderInsertDebugMarker computePassEncoderInsertDebugMarker;
    WGPUProcComputePassEncoderPopDebugGroup computePassEncoderPopDebugGroup;
    WGPUProcComputePassEncoderPushDebugGroup computePassEncoderPushDebugGroup;
    WGPUProcComputePassEncoderSetPipeline computePassEncoderSetPipeline;
    WGPUProcComputePassEncoderSetBindGroup computePassEncoderSetBindGroup;
    WGPUProcComputePassEncoderDispatch computePassEncoderDispatch;
    WGPUProcComputePassEncoderDispatchIndirect computePassEncoderDispatchIndirect;
    WGPUProcComputePassEncoderEndPass computePassEncoderEndPass;
    WGPUProcComputePassEncoderReference computePassEncoderReference;
    WGPUProcComputePassEncoderRelease computePassEncoderRelease;

    WGPUProcComputePipelineReference computePipelineReference;
    WGPUProcComputePipelineRelease computePipelineRelease;

    WGPUProcDeviceCreateBindGroup deviceCreateBindGroup;
    WGPUProcDeviceCreateBindGroupLayout deviceCreateBindGroupLayout;
    WGPUProcDeviceCreateBuffer deviceCreateBuffer;
    WGPUProcDeviceCreateBufferMapped deviceCreateBufferMapped;
    WGPUProcDeviceCreateCommandEncoder deviceCreateCommandEncoder;
    WGPUProcDeviceCreateComputePipeline deviceCreateComputePipeline;
    WGPUProcDeviceCreateRenderPipeline deviceCreateRenderPipeline;
    WGPUProcDeviceCreatePipelineLayout deviceCreatePipelineLayout;
    WGPUProcDeviceCreateQueue deviceCreateQueue;
    WGPUProcDeviceCreateSampler deviceCreateSampler;
    WGPUProcDeviceCreateShaderModule deviceCreateShaderModule;
    WGPUProcDeviceCreateTexture deviceCreateTexture;
    WGPUProcDeviceCreateBufferMappedAsync deviceCreateBufferMappedAsync;
    WGPUProcDeviceReference deviceReference;
    WGPUProcDeviceRelease deviceRelease;

    WGPUProcFenceGetCompletedValue fenceGetCompletedValue;
    WGPUProcFenceOnCompletion fenceOnCompletion;
    WGPUProcFenceReference fenceReference;
    WGPUProcFenceRelease fenceRelease;

    WGPUProcPipelineLayoutReference pipelineLayoutReference;
    WGPUProcPipelineLayoutRelease pipelineLayoutRelease;

    WGPUProcQueueSubmit queueSubmit;
    WGPUProcQueueSignal queueSignal;
    WGPUProcQueueCreateFence queueCreateFence;
    WGPUProcQueueReference queueReference;
    WGPUProcQueueRelease queueRelease;

    WGPUProcRenderPassEncoderSetPipeline renderPassEncoderSetPipeline;
    WGPUProcRenderPassEncoderSetBindGroup renderPassEncoderSetBindGroup;
    WGPUProcRenderPassEncoderDraw renderPassEncoderDraw;
    WGPUProcRenderPassEncoderDrawIndexed renderPassEncoderDrawIndexed;
    WGPUProcRenderPassEncoderDrawIndirect renderPassEncoderDrawIndirect;
    WGPUProcRenderPassEncoderDrawIndexedIndirect renderPassEncoderDrawIndexedIndirect;
    WGPUProcRenderPassEncoderInsertDebugMarker renderPassEncoderInsertDebugMarker;
    WGPUProcRenderPassEncoderPopDebugGroup renderPassEncoderPopDebugGroup;
    WGPUProcRenderPassEncoderPushDebugGroup renderPassEncoderPushDebugGroup;
    WGPUProcRenderPassEncoderSetStencilReference renderPassEncoderSetStencilReference;
    WGPUProcRenderPassEncoderSetBlendColor renderPassEncoderSetBlendColor;
    WGPUProcRenderPassEncoderSetViewport renderPassEncoderSetViewport;
    WGPUProcRenderPassEncoderSetScissorRect renderPassEncoderSetScissorRect;
    WGPUProcRenderPassEncoderSetVertexBuffers renderPassEncoderSetVertexBuffers;
    WGPUProcRenderPassEncoderSetIndexBuffer renderPassEncoderSetIndexBuffer;
    WGPUProcRenderPassEncoderEndPass renderPassEncoderEndPass;
    WGPUProcRenderPassEncoderReference renderPassEncoderReference;
    WGPUProcRenderPassEncoderRelease renderPassEncoderRelease;

    WGPUProcRenderPipelineReference renderPipelineReference;
    WGPUProcRenderPipelineRelease renderPipelineRelease;

    WGPUProcSamplerReference samplerReference;
    WGPUProcSamplerRelease samplerRelease;

    WGPUProcShaderModuleReference shaderModuleReference;
    WGPUProcShaderModuleRelease shaderModuleRelease;

    WGPUProcTextureCreateDefaultView textureCreateDefaultView;
    WGPUProcTextureCreateView textureCreateView;
    WGPUProcTextureDestroy textureDestroy;
    WGPUProcTextureReference textureReference;
    WGPUProcTextureRelease textureRelease;

    WGPUProcTextureViewReference textureViewReference;
    WGPUProcTextureViewRelease textureViewRelease;

};
typedef struct WGPUProcTable_s WGPUProcTable;

// Stuff below is for convenience and will forward calls to a static WGPUProcTable.

// Set which WGPUProcTable will be used
WGPU_EXPORT void WGPUSetProcs(const WGPUProcTable* procs);

// Methods of BindGroup
WGPU_EXPORT void wgpuBindGroupReference(WGPUBindGroup bindGroup);
WGPU_EXPORT void wgpuBindGroupRelease(WGPUBindGroup bindGroup);

// Methods of BindGroupLayout
WGPU_EXPORT void wgpuBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout);
WGPU_EXPORT void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout);

// Methods of Buffer
WGPU_EXPORT void wgpuBufferUnmap(WGPUBuffer buffer);
WGPU_EXPORT void wgpuBufferDestroy(WGPUBuffer buffer);
WGPU_EXPORT void wgpuBufferMapReadAsync(WGPUBuffer buffer, WGPUBufferMapReadCallback callback, void * userdata);
WGPU_EXPORT void wgpuBufferMapWriteAsync(WGPUBuffer buffer, WGPUBufferMapWriteCallback callback, void * userdata);
WGPU_EXPORT void wgpuBufferReference(WGPUBuffer buffer);
WGPU_EXPORT void wgpuBufferRelease(WGPUBuffer buffer);

// Methods of CommandBuffer
WGPU_EXPORT void wgpuCommandBufferReference(WGPUCommandBuffer commandBuffer);
WGPU_EXPORT void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer);

// Methods of CommandEncoder
WGPU_EXPORT WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPUCommandBufferDescriptor const * descriptor);
WGPU_EXPORT WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPUComputePassDescriptor const * descriptor);
WGPU_EXPORT WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor);
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size);
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUBufferCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUBufferCopyView const * destination, WGPUExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTextureCopyView const * source, WGPUTextureCopyView const * destination, WGPUExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder);
WGPU_EXPORT void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuCommandEncoderReference(WGPUCommandEncoder commandEncoder);
WGPU_EXPORT void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder);

// Methods of ComputePassEncoder
WGPU_EXPORT void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline);
WGPU_EXPORT void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
WGPU_EXPORT void wgpuComputePassEncoderDispatch(WGPUComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z);
WGPU_EXPORT void wgpuComputePassEncoderDispatchIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuComputePassEncoderEndPass(WGPUComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder);

// Methods of ComputePipeline
WGPU_EXPORT void wgpuComputePipelineReference(WGPUComputePipeline computePipeline);
WGPU_EXPORT void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline);

// Methods of Device
WGPU_EXPORT WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor);
WGPU_EXPORT WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor);
WGPU_EXPORT WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor);
WGPU_EXPORT WGPUCreateBufferMappedResult wgpuDeviceCreateBufferMapped(WGPUDevice device, WGPUBufferDescriptor const * descriptor);
WGPU_EXPORT WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPUCommandEncoderDescriptor const * descriptor);
WGPU_EXPORT WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor);
WGPU_EXPORT WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor);
WGPU_EXPORT WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor);
WGPU_EXPORT WGPUQueue wgpuDeviceCreateQueue(WGPUDevice device);
WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPUSamplerDescriptor const * descriptor);
WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor);
WGPU_EXPORT WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor);
WGPU_EXPORT void wgpuDeviceCreateBufferMappedAsync(WGPUDevice device, WGPUBufferDescriptor const * descriptor, WGPUBufferCreateMappedCallback callback, void * userdata);
WGPU_EXPORT void wgpuDeviceReference(WGPUDevice device);
WGPU_EXPORT void wgpuDeviceRelease(WGPUDevice device);

// Methods of Fence
WGPU_EXPORT uint64_t wgpuFenceGetCompletedValue(WGPUFence fence);
WGPU_EXPORT void wgpuFenceOnCompletion(WGPUFence fence, uint64_t value, WGPUFenceOnCompletionCallback callback, void * userdata);
WGPU_EXPORT void wgpuFenceReference(WGPUFence fence);
WGPU_EXPORT void wgpuFenceRelease(WGPUFence fence);

// Methods of PipelineLayout
WGPU_EXPORT void wgpuPipelineLayoutReference(WGPUPipelineLayout pipelineLayout);
WGPU_EXPORT void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout);

// Methods of Queue
WGPU_EXPORT void wgpuQueueSubmit(WGPUQueue queue, uint32_t commandCount, WGPUCommandBuffer const * commands);
WGPU_EXPORT void wgpuQueueSignal(WGPUQueue queue, WGPUFence fence, uint64_t signalValue);
WGPU_EXPORT WGPUFence wgpuQueueCreateFence(WGPUQueue queue, WGPUFenceDescriptor const * descriptor);
WGPU_EXPORT void wgpuQueueReference(WGPUQueue queue);
WGPU_EXPORT void wgpuQueueRelease(WGPUQueue queue);

// Methods of RenderPassEncoder
WGPU_EXPORT void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline);
WGPU_EXPORT void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPUBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
WGPU_EXPORT void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference);
WGPU_EXPORT void wgpuRenderPassEncoderSetBlendColor(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color);
WGPU_EXPORT void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth);
WGPU_EXPORT void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
WGPU_EXPORT void wgpuRenderPassEncoderSetVertexBuffers(WGPURenderPassEncoder renderPassEncoder, uint32_t startSlot, uint32_t count, WGPUBuffer const * buffers, uint64_t const * offsets);
WGPU_EXPORT void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, uint64_t offset);
WGPU_EXPORT void wgpuRenderPassEncoderEndPass(WGPURenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder);

// Methods of RenderPipeline
WGPU_EXPORT void wgpuRenderPipelineReference(WGPURenderPipeline renderPipeline);
WGPU_EXPORT void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline);

// Methods of Sampler
WGPU_EXPORT void wgpuSamplerReference(WGPUSampler sampler);
WGPU_EXPORT void wgpuSamplerRelease(WGPUSampler sampler);

// Methods of ShaderModule
WGPU_EXPORT void wgpuShaderModuleReference(WGPUShaderModule shaderModule);
WGPU_EXPORT void wgpuShaderModuleRelease(WGPUShaderModule shaderModule);

// Methods of Texture
WGPU_EXPORT WGPUTextureView wgpuTextureCreateDefaultView(WGPUTexture texture);
WGPU_EXPORT WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPUTextureViewDescriptor const * descriptor);
WGPU_EXPORT void wgpuTextureDestroy(WGPUTexture texture);
WGPU_EXPORT void wgpuTextureReference(WGPUTexture texture);
WGPU_EXPORT void wgpuTextureRelease(WGPUTexture texture);

// Methods of TextureView
WGPU_EXPORT void wgpuTextureViewReference(WGPUTextureView textureView);
WGPU_EXPORT void wgpuTextureViewRelease(WGPUTextureView textureView);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WGPU_WGPU_H_
