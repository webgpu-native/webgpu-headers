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

typedef struct wgpuBindGroupImpl* wgpuBindGroup;
typedef struct wgpuBindGroupLayoutImpl* wgpuBindGroupLayout;
typedef struct wgpuBufferImpl* wgpuBuffer;
typedef struct wgpuCommandBufferImpl* wgpuCommandBuffer;
typedef struct wgpuCommandEncoderImpl* wgpuCommandEncoder;
typedef struct wgpuComputePassEncoderImpl* wgpuComputePassEncoder;
typedef struct wgpuComputePipelineImpl* wgpuComputePipeline;
typedef struct wgpuDeviceImpl* wgpuDevice;
typedef struct wgpuFenceImpl* wgpuFence;
typedef struct wgpuPipelineLayoutImpl* wgpuPipelineLayout;
typedef struct wgpuQueueImpl* wgpuQueue;
typedef struct wgpuRenderPassEncoderImpl* wgpuRenderPassEncoder;
typedef struct wgpuRenderPipelineImpl* wgpuRenderPipeline;
typedef struct wgpuSamplerImpl* wgpuSampler;
typedef struct wgpuShaderModuleImpl* wgpuShaderModule;
typedef struct wgpuTextureImpl* wgpuTexture;
typedef struct wgpuTextureViewImpl* wgpuTextureView;

typedef enum {
    WGPU_ADDRESS_MODE_REPEAT = 0x00000000,
    WGPU_ADDRESS_MODE_MIRROR_REPEAT = 0x00000001,
    WGPU_ADDRESS_MODE_CLAMP_TO_EDGE = 0x00000002,
    WGPU_ADDRESS_MODE_FORCE32 = 0x7FFFFFFF
} wgpuAddressMode;

typedef enum {
    WGPU_BINDING_TYPE_UNIFORM_BUFFER = 0x00000000,
    WGPU_BINDING_TYPE_STORAGE_BUFFER = 0x00000001,
    WGPU_BINDING_TYPE_READONLY_STORAGE_BUFFER = 0x00000002,
    WGPU_BINDING_TYPE_SAMPLER = 0x00000003,
    WGPU_BINDING_TYPE_SAMPLED_TEXTURE = 0x00000004,
    WGPU_BINDING_TYPE_STORAGE_TEXTURE = 0x00000005,
    WGPU_BINDING_TYPE_FORCE32 = 0x7FFFFFFF
} wgpuBindingType;

typedef enum {
    WGPU_BLEND_FACTOR_ZERO = 0x00000000,
    WGPU_BLEND_FACTOR_ONE = 0x00000001,
    WGPU_BLEND_FACTOR_SRC_COLOR = 0x00000002,
    WGPU_BLEND_FACTOR_ONE_MINUS_SRC_COLOR = 0x00000003,
    WGPU_BLEND_FACTOR_SRC_ALPHA = 0x00000004,
    WGPU_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA = 0x00000005,
    WGPU_BLEND_FACTOR_DST_COLOR = 0x00000006,
    WGPU_BLEND_FACTOR_ONE_MINUS_DST_COLOR = 0x00000007,
    WGPU_BLEND_FACTOR_DST_ALPHA = 0x00000008,
    WGPU_BLEND_FACTOR_ONE_MINUS_DST_ALPHA = 0x00000009,
    WGPU_BLEND_FACTOR_SRC_ALPHA_SATURATED = 0x0000000A,
    WGPU_BLEND_FACTOR_BLEND_COLOR = 0x0000000B,
    WGPU_BLEND_FACTOR_ONE_MINUS_BLEND_COLOR = 0x0000000C,
    WGPU_BLEND_FACTOR_FORCE32 = 0x7FFFFFFF
} wgpuBlendFactor;

typedef enum {
    WGPU_BLEND_OPERATION_ADD = 0x00000000,
    WGPU_BLEND_OPERATION_SUBTRACT = 0x00000001,
    WGPU_BLEND_OPERATION_REVERSE_SUBTRACT = 0x00000002,
    WGPU_BLEND_OPERATION_MIN = 0x00000003,
    WGPU_BLEND_OPERATION_MAX = 0x00000004,
    WGPU_BLEND_OPERATION_FORCE32 = 0x7FFFFFFF
} wgpuBlendOperation;

typedef enum {
    WGPU_BUFFER_MAP_ASYNC_STATUS_SUCCESS = 0x00000000,
    WGPU_BUFFER_MAP_ASYNC_STATUS_ERROR = 0x00000001,
    WGPU_BUFFER_MAP_ASYNC_STATUS_UNKNOWN = 0x00000002,
    WGPU_BUFFER_MAP_ASYNC_STATUS_CONTEXT_LOST = 0x00000003,
    WGPU_BUFFER_MAP_ASYNC_STATUS_FORCE32 = 0x7FFFFFFF
} wgpuBufferMapAsyncStatus;

typedef enum {
    WGPU_COMPARE_FUNCTION_NEVER = 0x00000000,
    WGPU_COMPARE_FUNCTION_LESS = 0x00000001,
    WGPU_COMPARE_FUNCTION_LESS_EQUAL = 0x00000002,
    WGPU_COMPARE_FUNCTION_GREATER = 0x00000003,
    WGPU_COMPARE_FUNCTION_GREATER_EQUAL = 0x00000004,
    WGPU_COMPARE_FUNCTION_EQUAL = 0x00000005,
    WGPU_COMPARE_FUNCTION_NOT_EQUAL = 0x00000006,
    WGPU_COMPARE_FUNCTION_ALWAYS = 0x00000007,
    WGPU_COMPARE_FUNCTION_FORCE32 = 0x7FFFFFFF
} wgpuCompareFunction;

typedef enum {
    WGPU_CULL_MODE_NONE = 0x00000000,
    WGPU_CULL_MODE_FRONT = 0x00000001,
    WGPU_CULL_MODE_BACK = 0x00000002,
    WGPU_CULL_MODE_FORCE32 = 0x7FFFFFFF
} wgpuCullMode;

typedef enum {
    WGPU_FENCE_COMPLETION_STATUS_SUCCESS = 0x00000000,
    WGPU_FENCE_COMPLETION_STATUS_ERROR = 0x00000001,
    WGPU_FENCE_COMPLETION_STATUS_UNKNOWN = 0x00000002,
    WGPU_FENCE_COMPLETION_STATUS_CONTEXT_LOST = 0x00000003,
    WGPU_FENCE_COMPLETION_STATUS_FORCE32 = 0x7FFFFFFF
} wgpuFenceCompletionStatus;

typedef enum {
    WGPU_FILTER_MODE_NEAREST = 0x00000000,
    WGPU_FILTER_MODE_LINEAR = 0x00000001,
    WGPU_FILTER_MODE_FORCE32 = 0x7FFFFFFF
} wgpuFilterMode;

typedef enum {
    WGPU_FRONT_FACE_CCW = 0x00000000,
    WGPU_FRONT_FACE_CW = 0x00000001,
    WGPU_FRONT_FACE_FORCE32 = 0x7FFFFFFF
} wgpuFrontFace;

typedef enum {
    WGPU_INDEX_FORMAT_UINT16 = 0x00000000,
    WGPU_INDEX_FORMAT_UINT32 = 0x00000001,
    WGPU_INDEX_FORMAT_FORCE32 = 0x7FFFFFFF
} wgpuIndexFormat;

typedef enum {
    WGPU_INPUT_STEP_MODE_VERTEX = 0x00000000,
    WGPU_INPUT_STEP_MODE_INSTANCE = 0x00000001,
    WGPU_INPUT_STEP_MODE_FORCE32 = 0x7FFFFFFF
} wgpuInputStepMode;

typedef enum {
    WGPU_LOAD_OP_CLEAR = 0x00000000,
    WGPU_LOAD_OP_LOAD = 0x00000001,
    WGPU_LOAD_OP_FORCE32 = 0x7FFFFFFF
} wgpuLoadOp;

typedef enum {
    WGPU_PRIMITIVE_TOPOLOGY_POINT_LIST = 0x00000000,
    WGPU_PRIMITIVE_TOPOLOGY_LINE_LIST = 0x00000001,
    WGPU_PRIMITIVE_TOPOLOGY_LINE_STRIP = 0x00000002,
    WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST = 0x00000003,
    WGPU_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP = 0x00000004,
    WGPU_PRIMITIVE_TOPOLOGY_FORCE32 = 0x7FFFFFFF
} wgpuPrimitiveTopology;

typedef enum {
    WGPU_STENCIL_OPERATION_KEEP = 0x00000000,
    WGPU_STENCIL_OPERATION_ZERO = 0x00000001,
    WGPU_STENCIL_OPERATION_REPLACE = 0x00000002,
    WGPU_STENCIL_OPERATION_INVERT = 0x00000003,
    WGPU_STENCIL_OPERATION_INCREMENT_CLAMP = 0x00000004,
    WGPU_STENCIL_OPERATION_DECREMENT_CLAMP = 0x00000005,
    WGPU_STENCIL_OPERATION_INCREMENT_WRAP = 0x00000006,
    WGPU_STENCIL_OPERATION_DECREMENT_WRAP = 0x00000007,
    WGPU_STENCIL_OPERATION_FORCE32 = 0x7FFFFFFF
} wgpuStencilOperation;

typedef enum {
    WGPU_STORE_OP_STORE = 0x00000000,
    WGPU_STORE_OP_FORCE32 = 0x7FFFFFFF
} wgpuStoreOp;

typedef enum {
    WGPU_STRUCTURE_TYPE_DEFAULT = 0x00000000,
    WGPU_STRUCTURE_TYPE_TODO_PUT_THE_REST = 0x00000001,
    WGPU_STRUCTURE_TYPE_FORCE32 = 0x7FFFFFFF
} wgpuStructureType;

typedef enum {
    WGPU_TEXTURE_ASPECT_ALL = 0x00000000,
    WGPU_TEXTURE_ASPECT_STENCIL_ONLY = 0x00000001,
    WGPU_TEXTURE_ASPECT_DEPTH_ONLY = 0x00000002,
    WGPU_TEXTURE_ASPECT_FORCE32 = 0x7FFFFFFF
} wgpuTextureAspect;

typedef enum {
    WGPU_TEXTURE_DIMENSION_1D = 0x00000000,
    WGPU_TEXTURE_DIMENSION_2D = 0x00000001,
    WGPU_TEXTURE_DIMENSION_3D = 0x00000002,
    WGPU_TEXTURE_DIMENSION_FORCE32 = 0x7FFFFFFF
} wgpuTextureDimension;

typedef enum {
    WGPU_TEXTURE_FORMAT_R8_UNORM = 0x00000000,
    WGPU_TEXTURE_FORMAT_R8_SNORM = 0x00000001,
    WGPU_TEXTURE_FORMAT_R8_UINT = 0x00000002,
    WGPU_TEXTURE_FORMAT_R8_SINT = 0x00000003,
    WGPU_TEXTURE_FORMAT_R16_UNORM = 0x00000004,
    WGPU_TEXTURE_FORMAT_R16_SNORM = 0x00000005,
    WGPU_TEXTURE_FORMAT_R16_UINT = 0x00000006,
    WGPU_TEXTURE_FORMAT_R16_SINT = 0x00000007,
    WGPU_TEXTURE_FORMAT_R16_FLOAT = 0x00000008,
    WGPU_TEXTURE_FORMAT_RG8_UNORM = 0x00000009,
    WGPU_TEXTURE_FORMAT_RG8_SNORM = 0x0000000A,
    WGPU_TEXTURE_FORMAT_RG8_UINT = 0x0000000B,
    WGPU_TEXTURE_FORMAT_RG8_SINT = 0x0000000C,
    WGPU_TEXTURE_FORMAT_R32_FLOAT = 0x0000000D,
    WGPU_TEXTURE_FORMAT_R32_UINT = 0x0000000E,
    WGPU_TEXTURE_FORMAT_R32_SINT = 0x0000000F,
    WGPU_TEXTURE_FORMAT_RG16_UNORM = 0x00000010,
    WGPU_TEXTURE_FORMAT_RG16_SNORM = 0x00000011,
    WGPU_TEXTURE_FORMAT_RG16_UINT = 0x00000012,
    WGPU_TEXTURE_FORMAT_RG16_SINT = 0x00000013,
    WGPU_TEXTURE_FORMAT_RG16_FLOAT = 0x00000014,
    WGPU_TEXTURE_FORMAT_RGBA8_UNORM = 0x00000015,
    WGPU_TEXTURE_FORMAT_RGBA8_UNORM_SRGB = 0x00000016,
    WGPU_TEXTURE_FORMAT_RGBA8_SNORM = 0x00000017,
    WGPU_TEXTURE_FORMAT_RGBA8_UINT = 0x00000018,
    WGPU_TEXTURE_FORMAT_RGBA8_SINT = 0x00000019,
    WGPU_TEXTURE_FORMAT_BGRA8_UNORM = 0x0000001A,
    WGPU_TEXTURE_FORMAT_BGRA8_UNORM_SRGB = 0x0000001B,
    WGPU_TEXTURE_FORMAT_RGB10_A2_UNORM = 0x0000001C,
    WGPU_TEXTURE_FORMAT_RG11_B10_FLOAT = 0x0000001D,
    WGPU_TEXTURE_FORMAT_RG32_FLOAT = 0x0000001E,
    WGPU_TEXTURE_FORMAT_RG32_UINT = 0x0000001F,
    WGPU_TEXTURE_FORMAT_RG32_SINT = 0x00000020,
    WGPU_TEXTURE_FORMAT_RGBA16_UNORM = 0x00000021,
    WGPU_TEXTURE_FORMAT_RGBA16_SNORM = 0x00000022,
    WGPU_TEXTURE_FORMAT_RGBA16_UINT = 0x00000023,
    WGPU_TEXTURE_FORMAT_RGBA16_SINT = 0x00000024,
    WGPU_TEXTURE_FORMAT_RGBA16_FLOAT = 0x00000025,
    WGPU_TEXTURE_FORMAT_RGBA32_FLOAT = 0x00000026,
    WGPU_TEXTURE_FORMAT_RGBA32_UINT = 0x00000027,
    WGPU_TEXTURE_FORMAT_RGBA32_SINT = 0x00000028,
    WGPU_TEXTURE_FORMAT_DEPTH32_FLOAT = 0x00000029,
    WGPU_TEXTURE_FORMAT_DEPTH24_PLUS = 0x0000002A,
    WGPU_TEXTURE_FORMAT_DEPTH24_PLUS_STENCIL8 = 0x0000002B,
    WGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM = 0x0000002C,
    WGPU_TEXTURE_FORMAT_BC1_RGBA_UNORM_SRGB = 0x0000002D,
    WGPU_TEXTURE_FORMAT_BC2_RGBA_UNORM = 0x0000002E,
    WGPU_TEXTURE_FORMAT_BC2_RGBA_UNORM_SRGB = 0x0000002F,
    WGPU_TEXTURE_FORMAT_BC3_RGBA_UNORM = 0x00000030,
    WGPU_TEXTURE_FORMAT_BC3_RGBA_UNORM_SRGB = 0x00000031,
    WGPU_TEXTURE_FORMAT_BC4_R_UNORM = 0x00000032,
    WGPU_TEXTURE_FORMAT_BC4_R_SNORM = 0x00000033,
    WGPU_TEXTURE_FORMAT_BC5_RG_UNORM = 0x00000034,
    WGPU_TEXTURE_FORMAT_BC5_RG_SNORM = 0x00000035,
    WGPU_TEXTURE_FORMAT_BC6H_RGB_UFLOAT = 0x00000036,
    WGPU_TEXTURE_FORMAT_BC6H_RGB_SFLOAT = 0x00000037,
    WGPU_TEXTURE_FORMAT_BC7_RGBA_UNORM = 0x00000038,
    WGPU_TEXTURE_FORMAT_BC7_RGBA_UNORM_SRGB = 0x00000039,
    WGPU_TEXTURE_FORMAT_FORCE32 = 0x7FFFFFFF
} wgpuTextureFormat;

typedef enum {
    WGPU_TEXTURE_VIEW_DIMENSION_1D = 0x00000000,
    WGPU_TEXTURE_VIEW_DIMENSION_2D = 0x00000001,
    WGPU_TEXTURE_VIEW_DIMENSION_2D_ARRAY = 0x00000002,
    WGPU_TEXTURE_VIEW_DIMENSION_CUBE = 0x00000003,
    WGPU_TEXTURE_VIEW_DIMENSION_CUBE_ARRAY = 0x00000004,
    WGPU_TEXTURE_VIEW_DIMENSION_3D = 0x00000005,
    WGPU_TEXTURE_VIEW_DIMENSION_FORCE32 = 0x7FFFFFFF
} wgpuTextureViewDimension;

typedef enum {
    WGPU_VERTEX_FORMAT_UCHAR2 = 0x00000000,
    WGPU_VERTEX_FORMAT_UCHAR4 = 0x00000001,
    WGPU_VERTEX_FORMAT_CHAR2 = 0x00000002,
    WGPU_VERTEX_FORMAT_CHAR4 = 0x00000003,
    WGPU_VERTEX_FORMAT_UCHAR2_NORM = 0x00000004,
    WGPU_VERTEX_FORMAT_UCHAR4_NORM = 0x00000005,
    WGPU_VERTEX_FORMAT_CHAR2_NORM = 0x00000006,
    WGPU_VERTEX_FORMAT_CHAR4_NORM = 0x00000007,
    WGPU_VERTEX_FORMAT_USHORT2 = 0x00000008,
    WGPU_VERTEX_FORMAT_USHORT4 = 0x00000009,
    WGPU_VERTEX_FORMAT_SHORT2 = 0x0000000A,
    WGPU_VERTEX_FORMAT_SHORT4 = 0x0000000B,
    WGPU_VERTEX_FORMAT_USHORT2_NORM = 0x0000000C,
    WGPU_VERTEX_FORMAT_USHORT4_NORM = 0x0000000D,
    WGPU_VERTEX_FORMAT_SHORT2_NORM = 0x0000000E,
    WGPU_VERTEX_FORMAT_SHORT4_NORM = 0x0000000F,
    WGPU_VERTEX_FORMAT_HALF2 = 0x00000010,
    WGPU_VERTEX_FORMAT_HALF4 = 0x00000011,
    WGPU_VERTEX_FORMAT_FLOAT = 0x00000012,
    WGPU_VERTEX_FORMAT_FLOAT2 = 0x00000013,
    WGPU_VERTEX_FORMAT_FLOAT3 = 0x00000014,
    WGPU_VERTEX_FORMAT_FLOAT4 = 0x00000015,
    WGPU_VERTEX_FORMAT_UINT = 0x00000016,
    WGPU_VERTEX_FORMAT_UINT2 = 0x00000017,
    WGPU_VERTEX_FORMAT_UINT3 = 0x00000018,
    WGPU_VERTEX_FORMAT_UINT4 = 0x00000019,
    WGPU_VERTEX_FORMAT_INT = 0x0000001A,
    WGPU_VERTEX_FORMAT_INT2 = 0x0000001B,
    WGPU_VERTEX_FORMAT_INT3 = 0x0000001C,
    WGPU_VERTEX_FORMAT_INT4 = 0x0000001D,
    WGPU_VERTEX_FORMAT_FORCE32 = 0x7FFFFFFF
} wgpuVertexFormat;

typedef enum {
    WGPU_BUFFER_USAGE_BIT_NONE = 0x00000000,
    WGPU_BUFFER_USAGE_BIT_MAP_READ = 0x00000001,
    WGPU_BUFFER_USAGE_BIT_MAP_WRITE = 0x00000002,
    WGPU_BUFFER_USAGE_BIT_COPY_SRC = 0x00000004,
    WGPU_BUFFER_USAGE_BIT_COPY_DST = 0x00000008,
    WGPU_BUFFER_USAGE_BIT_INDEX = 0x00000010,
    WGPU_BUFFER_USAGE_BIT_VERTEX = 0x00000020,
    WGPU_BUFFER_USAGE_BIT_UNIFORM = 0x00000040,
    WGPU_BUFFER_USAGE_BIT_STORAGE = 0x00000080,
    WGPU_BUFFER_USAGE_BIT_INDIRECT = 0x00000100,
    WGPU_BUFFER_USAGE_BIT_FORCE32 = 0x7FFFFFFF
} wgpuBufferUsageBit;

typedef enum {
    WGPU_COLOR_WRITE_MASK_NONE = 0x00000000,
    WGPU_COLOR_WRITE_MASK_RED = 0x00000001,
    WGPU_COLOR_WRITE_MASK_GREEN = 0x00000002,
    WGPU_COLOR_WRITE_MASK_BLUE = 0x00000004,
    WGPU_COLOR_WRITE_MASK_ALPHA = 0x00000008,
    WGPU_COLOR_WRITE_MASK_ALL = 0x0000000F,
    WGPU_COLOR_WRITE_MASK_FORCE32 = 0x7FFFFFFF
} wgpuColorWriteMask;

typedef enum {
    WGPU_FACE_NONE = 0x00000000,
    WGPU_FACE_BACK = 0x00000001,
    WGPU_FACE_FRONT = 0x00000002,
    WGPU_FACE_BOTH = 0x00000003,
    WGPU_FACE_FORCE32 = 0x7FFFFFFF
} wgpuFace;

typedef enum {
    WGPU_SHADER_STAGE_BIT_NONE = 0x00000000,
    WGPU_SHADER_STAGE_BIT_VERTEX = 0x00000001,
    WGPU_SHADER_STAGE_BIT_FRAGMENT = 0x00000002,
    WGPU_SHADER_STAGE_BIT_COMPUTE = 0x00000004,
    WGPU_SHADER_STAGE_BIT_FORCE32 = 0x7FFFFFFF
} wgpuShaderStageBit;

typedef enum {
    WGPU_TEXTURE_USAGE_BIT_NONE = 0x00000000,
    WGPU_TEXTURE_USAGE_BIT_COPY_SRC = 0x00000001,
    WGPU_TEXTURE_USAGE_BIT_COPY_DST = 0x00000002,
    WGPU_TEXTURE_USAGE_BIT_SAMPLED = 0x00000004,
    WGPU_TEXTURE_USAGE_BIT_STORAGE = 0x00000008,
    WGPU_TEXTURE_USAGE_BIT_OUTPUT_ATTACHMENT = 0x00000010,
    WGPU_TEXTURE_USAGE_BIT_FORCE32 = 0x7FFFFFFF
} wgpuTextureUsageBit;


typedef struct wgpuBindGroupBinding {
    uint32_t binding;
    wgpuBuffer buffer;
    uint64_t offset;
    uint64_t size;
    wgpuSampler sampler;
    wgpuTextureView textureView;
} wgpuBindGroupBinding;

typedef struct wgpuBindGroupLayoutBinding {
    uint32_t binding;
    wgpuShaderStageBit visibility;
    wgpuBindingType type;
    bool dynamic;
    bool multisampled;
    wgpuTextureViewDimension textureDimension;
} wgpuBindGroupLayoutBinding;

typedef struct wgpuBlendDescriptor {
    wgpuBlendOperation operation;
    wgpuBlendFactor srcFactor;
    wgpuBlendFactor dstFactor;
} wgpuBlendDescriptor;

typedef struct wgpuBufferCopyView {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuBuffer buffer;
    uint64_t offset;
    uint32_t rowPitch;
    uint32_t imageHeight;
} wgpuBufferCopyView;

typedef struct wgpuBufferDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuBufferUsageBit usage;
    uint64_t size;
} wgpuBufferDescriptor;

typedef struct wgpuColor {
    float r;
    float g;
    float b;
    float a;
} wgpuColor;

typedef struct wgpuCommandBufferDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
} wgpuCommandBufferDescriptor;

typedef struct wgpuCommandEncoderDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
} wgpuCommandEncoderDescriptor;

typedef struct wgpuComputePassDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
} wgpuComputePassDescriptor;

typedef struct wgpuCreateBufferMappedResult {
    wgpuBuffer buffer;
    uint64_t dataLength;
    void * data;
} wgpuCreateBufferMappedResult;

typedef struct wgpuExtent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depth;
} wgpuExtent3D;

typedef struct wgpuFenceDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    uint64_t initialValue;
} wgpuFenceDescriptor;

typedef struct wgpuOrigin3D {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} wgpuOrigin3D;

typedef struct wgpuPipelineLayoutDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    uint32_t bindGroupLayoutCount;
    wgpuBindGroupLayout const * bindGroupLayouts;
} wgpuPipelineLayoutDescriptor;

typedef struct wgpuPipelineStageDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuShaderModule module;
    char const * entryPoint;
} wgpuPipelineStageDescriptor;

typedef struct wgpuRasterizationStateDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuFrontFace frontFace;
    wgpuCullMode cullMode;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
} wgpuRasterizationStateDescriptor;

typedef struct wgpuRenderPassDepthStencilAttachmentDescriptor {
    wgpuTextureView attachment;
    wgpuLoadOp depthLoadOp;
    wgpuStoreOp depthStoreOp;
    float clearDepth;
    wgpuLoadOp stencilLoadOp;
    wgpuStoreOp stencilStoreOp;
    uint32_t clearStencil;
} wgpuRenderPassDepthStencilAttachmentDescriptor;

typedef struct wgpuSamplerDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuAddressMode addressModeU;
    wgpuAddressMode addressModeV;
    wgpuAddressMode addressModeW;
    wgpuFilterMode magFilter;
    wgpuFilterMode minFilter;
    wgpuFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    wgpuCompareFunction compare;
} wgpuSamplerDescriptor;

typedef struct wgpuShaderModuleDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    uint32_t codeSize;
    uint32_t const * code;
} wgpuShaderModuleDescriptor;

typedef struct wgpuStencilStateFaceDescriptor {
    wgpuCompareFunction compare;
    wgpuStencilOperation failOp;
    wgpuStencilOperation depthFailOp;
    wgpuStencilOperation passOp;
} wgpuStencilStateFaceDescriptor;

typedef struct wgpuTextureViewDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuTextureFormat format;
    wgpuTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    wgpuTextureAspect aspect;
} wgpuTextureViewDescriptor;

typedef struct wgpuVertexAttributeDescriptor {
    uint32_t shaderLocation;
    uint64_t offset;
    wgpuVertexFormat format;
} wgpuVertexAttributeDescriptor;

typedef struct wgpuBindGroupDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuBindGroupLayout layout;
    uint32_t bindingCount;
    wgpuBindGroupBinding const * bindings;
} wgpuBindGroupDescriptor;

typedef struct wgpuBindGroupLayoutDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    uint32_t bindingCount;
    wgpuBindGroupLayoutBinding const * bindings;
} wgpuBindGroupLayoutDescriptor;

typedef struct wgpuColorStateDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuTextureFormat format;
    wgpuBlendDescriptor alphaBlend;
    wgpuBlendDescriptor colorBlend;
    wgpuColorWriteMask writeMask;
} wgpuColorStateDescriptor;

typedef struct wgpuComputePipelineDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuPipelineLayout layout;
    wgpuPipelineStageDescriptor const * computeStage;
} wgpuComputePipelineDescriptor;

typedef struct wgpuDepthStencilStateDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuTextureFormat format;
    bool depthWriteEnabled;
    wgpuCompareFunction depthCompare;
    wgpuStencilStateFaceDescriptor stencilFront;
    wgpuStencilStateFaceDescriptor stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
} wgpuDepthStencilStateDescriptor;

typedef struct wgpuRenderPassColorAttachmentDescriptor {
    wgpuTextureView attachment;
    wgpuTextureView resolveTarget;
    wgpuLoadOp loadOp;
    wgpuStoreOp storeOp;
    wgpuColor clearColor;
} wgpuRenderPassColorAttachmentDescriptor;

typedef struct wgpuTextureCopyView {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuTexture texture;
    uint32_t mipLevel;
    uint32_t arrayLayer;
    wgpuOrigin3D origin;
} wgpuTextureCopyView;

typedef struct wgpuTextureDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuTextureUsageBit usage;
    wgpuTextureDimension dimension;
    wgpuExtent3D size;
    uint32_t arrayLayerCount;
    wgpuTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
} wgpuTextureDescriptor;

typedef struct wgpuVertexBufferDescriptor {
    uint64_t stride;
    wgpuInputStepMode stepMode;
    uint32_t attributeCount;
    wgpuVertexAttributeDescriptor const * attributes;
} wgpuVertexBufferDescriptor;

typedef struct wgpuRenderPassDescriptor {
    uint32_t colorAttachmentCount;
    const wgpuRenderPassColorAttachmentDescriptor* const * colorAttachments;
    wgpuRenderPassDepthStencilAttachmentDescriptor const * depthStencilAttachment;
} wgpuRenderPassDescriptor;

typedef struct wgpuVertexInputDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuIndexFormat indexFormat;
    uint32_t bufferCount;
    wgpuVertexBufferDescriptor const * buffers;
} wgpuVertexInputDescriptor;

typedef struct wgpuRenderPipelineDescriptor {
    void const * nextInChain;
    wgpuStructureType structureType;
    wgpuPipelineLayout layout;
    wgpuPipelineStageDescriptor const * vertexStage;
    wgpuPipelineStageDescriptor const * fragmentStage;
    wgpuVertexInputDescriptor const * vertexInput;
    wgpuPrimitiveTopology primitiveTopology;
    wgpuRasterizationStateDescriptor const * rasterizationState;
    uint32_t sampleCount;
    wgpuDepthStencilStateDescriptor const * depthStencilState;
    uint32_t colorStateCount;
    const wgpuColorStateDescriptor* const * colorStates;
    uint32_t sampleMask;
    bool alphaToCoverageEnabled;
} wgpuRenderPipelineDescriptor;


typedef void (*wgpuBufferCreateMappedCallback)(wgpuBufferMapAsyncStatus status,
                                               wgpuCreateBufferMappedResult result,
                                               void* userdata);
typedef void (*wgpuBufferMapReadCallback)(wgpuBufferMapAsyncStatus status,
                                          const void* data,
                                          uint64_t dataLength,
                                          void* userdata);
typedef void (*wgpuBufferMapWriteCallback)(wgpuBufferMapAsyncStatus status,
                                           void* data,
                                           uint64_t dataLength,
                                           void* userdata);
typedef void (*wgpuFenceOnCompletionCallback)(wgpuFenceCompletionStatus status, void* userdata);

#ifdef __cplusplus
extern "C" {
#endif

// Procs of BindGroup
typedef void (*wgpuProcBindGroupReference)(wgpuBindGroup bindGroup);
typedef void (*wgpuProcBindGroupRelease)(wgpuBindGroup bindGroup);

// Procs of BindGroupLayout
typedef void (*wgpuProcBindGroupLayoutReference)(wgpuBindGroupLayout bindGroupLayout);
typedef void (*wgpuProcBindGroupLayoutRelease)(wgpuBindGroupLayout bindGroupLayout);

// Procs of Buffer
typedef void (*wgpuProcBufferUnmap)(wgpuBuffer buffer);
typedef void (*wgpuProcBufferDestroy)(wgpuBuffer buffer);
typedef void (*wgpuProcBufferMapReadAsync)(wgpuBuffer buffer, wgpuBufferMapReadCallback callback, void * userdata);
typedef void (*wgpuProcBufferMapWriteAsync)(wgpuBuffer buffer, wgpuBufferMapWriteCallback callback, void * userdata);
typedef void (*wgpuProcBufferReference)(wgpuBuffer buffer);
typedef void (*wgpuProcBufferRelease)(wgpuBuffer buffer);

// Procs of CommandBuffer
typedef void (*wgpuProcCommandBufferReference)(wgpuCommandBuffer commandBuffer);
typedef void (*wgpuProcCommandBufferRelease)(wgpuCommandBuffer commandBuffer);

// Procs of CommandEncoder
typedef wgpuCommandBuffer (*wgpuProcCommandEncoderFinish)(wgpuCommandEncoder commandEncoder, wgpuCommandBufferDescriptor const * descriptor);
typedef wgpuComputePassEncoder (*wgpuProcCommandEncoderBeginComputePass)(wgpuCommandEncoder commandEncoder, wgpuComputePassDescriptor const * descriptor);
typedef wgpuRenderPassEncoder (*wgpuProcCommandEncoderBeginRenderPass)(wgpuCommandEncoder commandEncoder, wgpuRenderPassDescriptor const * descriptor);
typedef void (*wgpuProcCommandEncoderCopyBufferToBuffer)(wgpuCommandEncoder commandEncoder, wgpuBuffer source, uint64_t sourceOffset, wgpuBuffer destination, uint64_t destinationOffset, uint64_t size);
typedef void (*wgpuProcCommandEncoderCopyBufferToTexture)(wgpuCommandEncoder commandEncoder, wgpuBufferCopyView const * source, wgpuTextureCopyView const * destination, wgpuExtent3D const * copySize);
typedef void (*wgpuProcCommandEncoderCopyTextureToBuffer)(wgpuCommandEncoder commandEncoder, wgpuTextureCopyView const * source, wgpuBufferCopyView const * destination, wgpuExtent3D const * copySize);
typedef void (*wgpuProcCommandEncoderCopyTextureToTexture)(wgpuCommandEncoder commandEncoder, wgpuTextureCopyView const * source, wgpuTextureCopyView const * destination, wgpuExtent3D const * copySize);
typedef void (*wgpuProcCommandEncoderInsertDebugMarker)(wgpuCommandEncoder commandEncoder, char const * groupLabel);
typedef void (*wgpuProcCommandEncoderPopDebugGroup)(wgpuCommandEncoder commandEncoder);
typedef void (*wgpuProcCommandEncoderPushDebugGroup)(wgpuCommandEncoder commandEncoder, char const * groupLabel);
typedef void (*wgpuProcCommandEncoderReference)(wgpuCommandEncoder commandEncoder);
typedef void (*wgpuProcCommandEncoderRelease)(wgpuCommandEncoder commandEncoder);

// Procs of ComputePassEncoder
typedef void (*wgpuProcComputePassEncoderInsertDebugMarker)(wgpuComputePassEncoder computePassEncoder, char const * groupLabel);
typedef void (*wgpuProcComputePassEncoderPopDebugGroup)(wgpuComputePassEncoder computePassEncoder);
typedef void (*wgpuProcComputePassEncoderPushDebugGroup)(wgpuComputePassEncoder computePassEncoder, char const * groupLabel);
typedef void (*wgpuProcComputePassEncoderSetPipeline)(wgpuComputePassEncoder computePassEncoder, wgpuComputePipeline pipeline);
typedef void (*wgpuProcComputePassEncoderSetBindGroup)(wgpuComputePassEncoder computePassEncoder, uint32_t groupIndex, wgpuBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
typedef void (*wgpuProcComputePassEncoderDispatch)(wgpuComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z);
typedef void (*wgpuProcComputePassEncoderDispatchIndirect)(wgpuComputePassEncoder computePassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*wgpuProcComputePassEncoderEndPass)(wgpuComputePassEncoder computePassEncoder);
typedef void (*wgpuProcComputePassEncoderReference)(wgpuComputePassEncoder computePassEncoder);
typedef void (*wgpuProcComputePassEncoderRelease)(wgpuComputePassEncoder computePassEncoder);

// Procs of ComputePipeline
typedef void (*wgpuProcComputePipelineReference)(wgpuComputePipeline computePipeline);
typedef void (*wgpuProcComputePipelineRelease)(wgpuComputePipeline computePipeline);

// Procs of Device
typedef wgpuBindGroup (*wgpuProcDeviceCreateBindGroup)(wgpuDevice device, wgpuBindGroupDescriptor const * descriptor);
typedef wgpuBindGroupLayout (*wgpuProcDeviceCreateBindGroupLayout)(wgpuDevice device, wgpuBindGroupLayoutDescriptor const * descriptor);
typedef wgpuBuffer (*wgpuProcDeviceCreateBuffer)(wgpuDevice device, wgpuBufferDescriptor const * descriptor);
typedef wgpuCreateBufferMappedResult (*wgpuProcDeviceCreateBufferMapped)(wgpuDevice device, wgpuBufferDescriptor const * descriptor);
typedef wgpuCommandEncoder (*wgpuProcDeviceCreateCommandEncoder)(wgpuDevice device, wgpuCommandEncoderDescriptor const * descriptor);
typedef wgpuComputePipeline (*wgpuProcDeviceCreateComputePipeline)(wgpuDevice device, wgpuComputePipelineDescriptor const * descriptor);
typedef wgpuRenderPipeline (*wgpuProcDeviceCreateRenderPipeline)(wgpuDevice device, wgpuRenderPipelineDescriptor const * descriptor);
typedef wgpuPipelineLayout (*wgpuProcDeviceCreatePipelineLayout)(wgpuDevice device, wgpuPipelineLayoutDescriptor const * descriptor);
typedef wgpuQueue (*wgpuProcDeviceCreateQueue)(wgpuDevice device);
typedef wgpuSampler (*wgpuProcDeviceCreateSampler)(wgpuDevice device, wgpuSamplerDescriptor const * descriptor);
typedef wgpuShaderModule (*wgpuProcDeviceCreateShaderModule)(wgpuDevice device, wgpuShaderModuleDescriptor const * descriptor);
typedef wgpuTexture (*wgpuProcDeviceCreateTexture)(wgpuDevice device, wgpuTextureDescriptor const * descriptor);
typedef void (*wgpuProcDeviceCreateBufferMappedAsync)(wgpuDevice device, wgpuBufferDescriptor const * descriptor, wgpuBufferCreateMappedCallback callback, void * userdata);
typedef void (*wgpuProcDeviceReference)(wgpuDevice device);
typedef void (*wgpuProcDeviceRelease)(wgpuDevice device);

// Procs of Fence
typedef uint64_t (*wgpuProcFenceGetCompletedValue)(wgpuFence fence);
typedef void (*wgpuProcFenceOnCompletion)(wgpuFence fence, uint64_t value, wgpuFenceOnCompletionCallback callback, void * userdata);
typedef void (*wgpuProcFenceReference)(wgpuFence fence);
typedef void (*wgpuProcFenceRelease)(wgpuFence fence);

// Procs of PipelineLayout
typedef void (*wgpuProcPipelineLayoutReference)(wgpuPipelineLayout pipelineLayout);
typedef void (*wgpuProcPipelineLayoutRelease)(wgpuPipelineLayout pipelineLayout);

// Procs of Queue
typedef void (*wgpuProcQueueSubmit)(wgpuQueue queue, uint32_t commandCount, wgpuCommandBuffer const * commands);
typedef void (*wgpuProcQueueSignal)(wgpuQueue queue, wgpuFence fence, uint64_t signalValue);
typedef wgpuFence (*wgpuProcQueueCreateFence)(wgpuQueue queue, wgpuFenceDescriptor const * descriptor);
typedef void (*wgpuProcQueueReference)(wgpuQueue queue);
typedef void (*wgpuProcQueueRelease)(wgpuQueue queue);

// Procs of RenderPassEncoder
typedef void (*wgpuProcRenderPassEncoderSetPipeline)(wgpuRenderPassEncoder renderPassEncoder, wgpuRenderPipeline pipeline);
typedef void (*wgpuProcRenderPassEncoderSetBindGroup)(wgpuRenderPassEncoder renderPassEncoder, uint32_t groupIndex, wgpuBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
typedef void (*wgpuProcRenderPassEncoderDraw)(wgpuRenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
typedef void (*wgpuProcRenderPassEncoderDrawIndexed)(wgpuRenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
typedef void (*wgpuProcRenderPassEncoderDrawIndirect)(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*wgpuProcRenderPassEncoderDrawIndexedIndirect)(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
typedef void (*wgpuProcRenderPassEncoderInsertDebugMarker)(wgpuRenderPassEncoder renderPassEncoder, char const * groupLabel);
typedef void (*wgpuProcRenderPassEncoderPopDebugGroup)(wgpuRenderPassEncoder renderPassEncoder);
typedef void (*wgpuProcRenderPassEncoderPushDebugGroup)(wgpuRenderPassEncoder renderPassEncoder, char const * groupLabel);
typedef void (*wgpuProcRenderPassEncoderSetStencilReference)(wgpuRenderPassEncoder renderPassEncoder, uint32_t reference);
typedef void (*wgpuProcRenderPassEncoderSetBlendColor)(wgpuRenderPassEncoder renderPassEncoder, wgpuColor const * color);
typedef void (*wgpuProcRenderPassEncoderSetViewport)(wgpuRenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth);
typedef void (*wgpuProcRenderPassEncoderSetScissorRect)(wgpuRenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
typedef void (*wgpuProcRenderPassEncoderSetVertexBuffers)(wgpuRenderPassEncoder renderPassEncoder, uint32_t startSlot, uint32_t count, wgpuBuffer const * buffers, uint64_t const * offsets);
typedef void (*wgpuProcRenderPassEncoderSetIndexBuffer)(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer buffer, uint64_t offset);
typedef void (*wgpuProcRenderPassEncoderEndPass)(wgpuRenderPassEncoder renderPassEncoder);
typedef void (*wgpuProcRenderPassEncoderReference)(wgpuRenderPassEncoder renderPassEncoder);
typedef void (*wgpuProcRenderPassEncoderRelease)(wgpuRenderPassEncoder renderPassEncoder);

// Procs of RenderPipeline
typedef void (*wgpuProcRenderPipelineReference)(wgpuRenderPipeline renderPipeline);
typedef void (*wgpuProcRenderPipelineRelease)(wgpuRenderPipeline renderPipeline);

// Procs of Sampler
typedef void (*wgpuProcSamplerReference)(wgpuSampler sampler);
typedef void (*wgpuProcSamplerRelease)(wgpuSampler sampler);

// Procs of ShaderModule
typedef void (*wgpuProcShaderModuleReference)(wgpuShaderModule shaderModule);
typedef void (*wgpuProcShaderModuleRelease)(wgpuShaderModule shaderModule);

// Procs of Texture
typedef wgpuTextureView (*wgpuProcTextureCreateDefaultView)(wgpuTexture texture);
typedef wgpuTextureView (*wgpuProcTextureCreateView)(wgpuTexture texture, wgpuTextureViewDescriptor const * descriptor);
typedef void (*wgpuProcTextureDestroy)(wgpuTexture texture);
typedef void (*wgpuProcTextureReference)(wgpuTexture texture);
typedef void (*wgpuProcTextureRelease)(wgpuTexture texture);

// Procs of TextureView
typedef void (*wgpuProcTextureViewReference)(wgpuTextureView textureView);
typedef void (*wgpuProcTextureViewRelease)(wgpuTextureView textureView);


struct wgpuProcTable_s {
    wgpuProcBindGroupReference bindGroupReference;
    wgpuProcBindGroupRelease bindGroupRelease;

    wgpuProcBindGroupLayoutReference bindGroupLayoutReference;
    wgpuProcBindGroupLayoutRelease bindGroupLayoutRelease;

    wgpuProcBufferUnmap bufferUnmap;
    wgpuProcBufferDestroy bufferDestroy;
    wgpuProcBufferMapReadAsync bufferMapReadAsync;
    wgpuProcBufferMapWriteAsync bufferMapWriteAsync;
    wgpuProcBufferReference bufferReference;
    wgpuProcBufferRelease bufferRelease;

    wgpuProcCommandBufferReference commandBufferReference;
    wgpuProcCommandBufferRelease commandBufferRelease;

    wgpuProcCommandEncoderFinish commandEncoderFinish;
    wgpuProcCommandEncoderBeginComputePass commandEncoderBeginComputePass;
    wgpuProcCommandEncoderBeginRenderPass commandEncoderBeginRenderPass;
    wgpuProcCommandEncoderCopyBufferToBuffer commandEncoderCopyBufferToBuffer;
    wgpuProcCommandEncoderCopyBufferToTexture commandEncoderCopyBufferToTexture;
    wgpuProcCommandEncoderCopyTextureToBuffer commandEncoderCopyTextureToBuffer;
    wgpuProcCommandEncoderCopyTextureToTexture commandEncoderCopyTextureToTexture;
    wgpuProcCommandEncoderInsertDebugMarker commandEncoderInsertDebugMarker;
    wgpuProcCommandEncoderPopDebugGroup commandEncoderPopDebugGroup;
    wgpuProcCommandEncoderPushDebugGroup commandEncoderPushDebugGroup;
    wgpuProcCommandEncoderReference commandEncoderReference;
    wgpuProcCommandEncoderRelease commandEncoderRelease;

    wgpuProcComputePassEncoderInsertDebugMarker computePassEncoderInsertDebugMarker;
    wgpuProcComputePassEncoderPopDebugGroup computePassEncoderPopDebugGroup;
    wgpuProcComputePassEncoderPushDebugGroup computePassEncoderPushDebugGroup;
    wgpuProcComputePassEncoderSetPipeline computePassEncoderSetPipeline;
    wgpuProcComputePassEncoderSetBindGroup computePassEncoderSetBindGroup;
    wgpuProcComputePassEncoderDispatch computePassEncoderDispatch;
    wgpuProcComputePassEncoderDispatchIndirect computePassEncoderDispatchIndirect;
    wgpuProcComputePassEncoderEndPass computePassEncoderEndPass;
    wgpuProcComputePassEncoderReference computePassEncoderReference;
    wgpuProcComputePassEncoderRelease computePassEncoderRelease;

    wgpuProcComputePipelineReference computePipelineReference;
    wgpuProcComputePipelineRelease computePipelineRelease;

    wgpuProcDeviceCreateBindGroup deviceCreateBindGroup;
    wgpuProcDeviceCreateBindGroupLayout deviceCreateBindGroupLayout;
    wgpuProcDeviceCreateBuffer deviceCreateBuffer;
    wgpuProcDeviceCreateBufferMapped deviceCreateBufferMapped;
    wgpuProcDeviceCreateCommandEncoder deviceCreateCommandEncoder;
    wgpuProcDeviceCreateComputePipeline deviceCreateComputePipeline;
    wgpuProcDeviceCreateRenderPipeline deviceCreateRenderPipeline;
    wgpuProcDeviceCreatePipelineLayout deviceCreatePipelineLayout;
    wgpuProcDeviceCreateQueue deviceCreateQueue;
    wgpuProcDeviceCreateSampler deviceCreateSampler;
    wgpuProcDeviceCreateShaderModule deviceCreateShaderModule;
    wgpuProcDeviceCreateTexture deviceCreateTexture;
    wgpuProcDeviceCreateBufferMappedAsync deviceCreateBufferMappedAsync;
    wgpuProcDeviceReference deviceReference;
    wgpuProcDeviceRelease deviceRelease;

    wgpuProcFenceGetCompletedValue fenceGetCompletedValue;
    wgpuProcFenceOnCompletion fenceOnCompletion;
    wgpuProcFenceReference fenceReference;
    wgpuProcFenceRelease fenceRelease;

    wgpuProcPipelineLayoutReference pipelineLayoutReference;
    wgpuProcPipelineLayoutRelease pipelineLayoutRelease;

    wgpuProcQueueSubmit queueSubmit;
    wgpuProcQueueSignal queueSignal;
    wgpuProcQueueCreateFence queueCreateFence;
    wgpuProcQueueReference queueReference;
    wgpuProcQueueRelease queueRelease;

    wgpuProcRenderPassEncoderSetPipeline renderPassEncoderSetPipeline;
    wgpuProcRenderPassEncoderSetBindGroup renderPassEncoderSetBindGroup;
    wgpuProcRenderPassEncoderDraw renderPassEncoderDraw;
    wgpuProcRenderPassEncoderDrawIndexed renderPassEncoderDrawIndexed;
    wgpuProcRenderPassEncoderDrawIndirect renderPassEncoderDrawIndirect;
    wgpuProcRenderPassEncoderDrawIndexedIndirect renderPassEncoderDrawIndexedIndirect;
    wgpuProcRenderPassEncoderInsertDebugMarker renderPassEncoderInsertDebugMarker;
    wgpuProcRenderPassEncoderPopDebugGroup renderPassEncoderPopDebugGroup;
    wgpuProcRenderPassEncoderPushDebugGroup renderPassEncoderPushDebugGroup;
    wgpuProcRenderPassEncoderSetStencilReference renderPassEncoderSetStencilReference;
    wgpuProcRenderPassEncoderSetBlendColor renderPassEncoderSetBlendColor;
    wgpuProcRenderPassEncoderSetViewport renderPassEncoderSetViewport;
    wgpuProcRenderPassEncoderSetScissorRect renderPassEncoderSetScissorRect;
    wgpuProcRenderPassEncoderSetVertexBuffers renderPassEncoderSetVertexBuffers;
    wgpuProcRenderPassEncoderSetIndexBuffer renderPassEncoderSetIndexBuffer;
    wgpuProcRenderPassEncoderEndPass renderPassEncoderEndPass;
    wgpuProcRenderPassEncoderReference renderPassEncoderReference;
    wgpuProcRenderPassEncoderRelease renderPassEncoderRelease;

    wgpuProcRenderPipelineReference renderPipelineReference;
    wgpuProcRenderPipelineRelease renderPipelineRelease;

    wgpuProcSamplerReference samplerReference;
    wgpuProcSamplerRelease samplerRelease;

    wgpuProcShaderModuleReference shaderModuleReference;
    wgpuProcShaderModuleRelease shaderModuleRelease;

    wgpuProcTextureCreateDefaultView textureCreateDefaultView;
    wgpuProcTextureCreateView textureCreateView;
    wgpuProcTextureDestroy textureDestroy;
    wgpuProcTextureReference textureReference;
    wgpuProcTextureRelease textureRelease;

    wgpuProcTextureViewReference textureViewReference;
    wgpuProcTextureViewRelease textureViewRelease;

};
typedef struct wgpuProcTable_s wgpuProcTable;

// Stuff below is for convenience and will forward calls to a static wgpuProcTable.

// Set which wgpuProcTable will be used
WGPU_EXPORT void wgpuSetProcs(const wgpuProcTable* procs);

// Methods of BindGroup
WGPU_EXPORT void wgpuBindGroupReference(wgpuBindGroup bindGroup);
WGPU_EXPORT void wgpuBindGroupRelease(wgpuBindGroup bindGroup);

// Methods of BindGroupLayout
WGPU_EXPORT void wgpuBindGroupLayoutReference(wgpuBindGroupLayout bindGroupLayout);
WGPU_EXPORT void wgpuBindGroupLayoutRelease(wgpuBindGroupLayout bindGroupLayout);

// Methods of Buffer
WGPU_EXPORT void wgpuBufferUnmap(wgpuBuffer buffer);
WGPU_EXPORT void wgpuBufferDestroy(wgpuBuffer buffer);
WGPU_EXPORT void wgpuBufferMapReadAsync(wgpuBuffer buffer, wgpuBufferMapReadCallback callback, void * userdata);
WGPU_EXPORT void wgpuBufferMapWriteAsync(wgpuBuffer buffer, wgpuBufferMapWriteCallback callback, void * userdata);
WGPU_EXPORT void wgpuBufferReference(wgpuBuffer buffer);
WGPU_EXPORT void wgpuBufferRelease(wgpuBuffer buffer);

// Methods of CommandBuffer
WGPU_EXPORT void wgpuCommandBufferReference(wgpuCommandBuffer commandBuffer);
WGPU_EXPORT void wgpuCommandBufferRelease(wgpuCommandBuffer commandBuffer);

// Methods of CommandEncoder
WGPU_EXPORT wgpuCommandBuffer wgpuCommandEncoderFinish(wgpuCommandEncoder commandEncoder, wgpuCommandBufferDescriptor const * descriptor);
WGPU_EXPORT wgpuComputePassEncoder wgpuCommandEncoderBeginComputePass(wgpuCommandEncoder commandEncoder, wgpuComputePassDescriptor const * descriptor);
WGPU_EXPORT wgpuRenderPassEncoder wgpuCommandEncoderBeginRenderPass(wgpuCommandEncoder commandEncoder, wgpuRenderPassDescriptor const * descriptor);
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToBuffer(wgpuCommandEncoder commandEncoder, wgpuBuffer source, uint64_t sourceOffset, wgpuBuffer destination, uint64_t destinationOffset, uint64_t size);
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(wgpuCommandEncoder commandEncoder, wgpuBufferCopyView const * source, wgpuTextureCopyView const * destination, wgpuExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(wgpuCommandEncoder commandEncoder, wgpuTextureCopyView const * source, wgpuBufferCopyView const * destination, wgpuExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(wgpuCommandEncoder commandEncoder, wgpuTextureCopyView const * source, wgpuTextureCopyView const * destination, wgpuExtent3D const * copySize);
WGPU_EXPORT void wgpuCommandEncoderInsertDebugMarker(wgpuCommandEncoder commandEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuCommandEncoderPopDebugGroup(wgpuCommandEncoder commandEncoder);
WGPU_EXPORT void wgpuCommandEncoderPushDebugGroup(wgpuCommandEncoder commandEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuCommandEncoderReference(wgpuCommandEncoder commandEncoder);
WGPU_EXPORT void wgpuCommandEncoderRelease(wgpuCommandEncoder commandEncoder);

// Methods of ComputePassEncoder
WGPU_EXPORT void wgpuComputePassEncoderInsertDebugMarker(wgpuComputePassEncoder computePassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuComputePassEncoderPopDebugGroup(wgpuComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderPushDebugGroup(wgpuComputePassEncoder computePassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuComputePassEncoderSetPipeline(wgpuComputePassEncoder computePassEncoder, wgpuComputePipeline pipeline);
WGPU_EXPORT void wgpuComputePassEncoderSetBindGroup(wgpuComputePassEncoder computePassEncoder, uint32_t groupIndex, wgpuBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
WGPU_EXPORT void wgpuComputePassEncoderDispatch(wgpuComputePassEncoder computePassEncoder, uint32_t x, uint32_t y, uint32_t z);
WGPU_EXPORT void wgpuComputePassEncoderDispatchIndirect(wgpuComputePassEncoder computePassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuComputePassEncoderEndPass(wgpuComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderReference(wgpuComputePassEncoder computePassEncoder);
WGPU_EXPORT void wgpuComputePassEncoderRelease(wgpuComputePassEncoder computePassEncoder);

// Methods of ComputePipeline
WGPU_EXPORT void wgpuComputePipelineReference(wgpuComputePipeline computePipeline);
WGPU_EXPORT void wgpuComputePipelineRelease(wgpuComputePipeline computePipeline);

// Methods of Device
WGPU_EXPORT wgpuBindGroup wgpuDeviceCreateBindGroup(wgpuDevice device, wgpuBindGroupDescriptor const * descriptor);
WGPU_EXPORT wgpuBindGroupLayout wgpuDeviceCreateBindGroupLayout(wgpuDevice device, wgpuBindGroupLayoutDescriptor const * descriptor);
WGPU_EXPORT wgpuBuffer wgpuDeviceCreateBuffer(wgpuDevice device, wgpuBufferDescriptor const * descriptor);
WGPU_EXPORT wgpuCreateBufferMappedResult wgpuDeviceCreateBufferMapped(wgpuDevice device, wgpuBufferDescriptor const * descriptor);
WGPU_EXPORT wgpuCommandEncoder wgpuDeviceCreateCommandEncoder(wgpuDevice device, wgpuCommandEncoderDescriptor const * descriptor);
WGPU_EXPORT wgpuComputePipeline wgpuDeviceCreateComputePipeline(wgpuDevice device, wgpuComputePipelineDescriptor const * descriptor);
WGPU_EXPORT wgpuRenderPipeline wgpuDeviceCreateRenderPipeline(wgpuDevice device, wgpuRenderPipelineDescriptor const * descriptor);
WGPU_EXPORT wgpuPipelineLayout wgpuDeviceCreatePipelineLayout(wgpuDevice device, wgpuPipelineLayoutDescriptor const * descriptor);
WGPU_EXPORT wgpuQueue wgpuDeviceCreateQueue(wgpuDevice device);
WGPU_EXPORT wgpuSampler wgpuDeviceCreateSampler(wgpuDevice device, wgpuSamplerDescriptor const * descriptor);
WGPU_EXPORT wgpuShaderModule wgpuDeviceCreateShaderModule(wgpuDevice device, wgpuShaderModuleDescriptor const * descriptor);
WGPU_EXPORT wgpuTexture wgpuDeviceCreateTexture(wgpuDevice device, wgpuTextureDescriptor const * descriptor);
WGPU_EXPORT void wgpuDeviceCreateBufferMappedAsync(wgpuDevice device, wgpuBufferDescriptor const * descriptor, wgpuBufferCreateMappedCallback callback, void * userdata);
WGPU_EXPORT void wgpuDeviceReference(wgpuDevice device);
WGPU_EXPORT void wgpuDeviceRelease(wgpuDevice device);

// Methods of Fence
WGPU_EXPORT uint64_t wgpuFenceGetCompletedValue(wgpuFence fence);
WGPU_EXPORT void wgpuFenceOnCompletion(wgpuFence fence, uint64_t value, wgpuFenceOnCompletionCallback callback, void * userdata);
WGPU_EXPORT void wgpuFenceReference(wgpuFence fence);
WGPU_EXPORT void wgpuFenceRelease(wgpuFence fence);

// Methods of PipelineLayout
WGPU_EXPORT void wgpuPipelineLayoutReference(wgpuPipelineLayout pipelineLayout);
WGPU_EXPORT void wgpuPipelineLayoutRelease(wgpuPipelineLayout pipelineLayout);

// Methods of Queue
WGPU_EXPORT void wgpuQueueSubmit(wgpuQueue queue, uint32_t commandCount, wgpuCommandBuffer const * commands);
WGPU_EXPORT void wgpuQueueSignal(wgpuQueue queue, wgpuFence fence, uint64_t signalValue);
WGPU_EXPORT wgpuFence wgpuQueueCreateFence(wgpuQueue queue, wgpuFenceDescriptor const * descriptor);
WGPU_EXPORT void wgpuQueueReference(wgpuQueue queue);
WGPU_EXPORT void wgpuQueueRelease(wgpuQueue queue);

// Methods of RenderPassEncoder
WGPU_EXPORT void wgpuRenderPassEncoderSetPipeline(wgpuRenderPassEncoder renderPassEncoder, wgpuRenderPipeline pipeline);
WGPU_EXPORT void wgpuRenderPassEncoderSetBindGroup(wgpuRenderPassEncoder renderPassEncoder, uint32_t groupIndex, wgpuBindGroup group, uint32_t dynamicOffsetCount, uint64_t const * dynamicOffsets);
WGPU_EXPORT void wgpuRenderPassEncoderDraw(wgpuRenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexed(wgpuRenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndirect(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexedIndirect(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer indirectBuffer, uint64_t indirectOffset);
WGPU_EXPORT void wgpuRenderPassEncoderInsertDebugMarker(wgpuRenderPassEncoder renderPassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuRenderPassEncoderPopDebugGroup(wgpuRenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderPushDebugGroup(wgpuRenderPassEncoder renderPassEncoder, char const * groupLabel);
WGPU_EXPORT void wgpuRenderPassEncoderSetStencilReference(wgpuRenderPassEncoder renderPassEncoder, uint32_t reference);
WGPU_EXPORT void wgpuRenderPassEncoderSetBlendColor(wgpuRenderPassEncoder renderPassEncoder, wgpuColor const * color);
WGPU_EXPORT void wgpuRenderPassEncoderSetViewport(wgpuRenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth);
WGPU_EXPORT void wgpuRenderPassEncoderSetScissorRect(wgpuRenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height);
WGPU_EXPORT void wgpuRenderPassEncoderSetVertexBuffers(wgpuRenderPassEncoder renderPassEncoder, uint32_t startSlot, uint32_t count, wgpuBuffer const * buffers, uint64_t const * offsets);
WGPU_EXPORT void wgpuRenderPassEncoderSetIndexBuffer(wgpuRenderPassEncoder renderPassEncoder, wgpuBuffer buffer, uint64_t offset);
WGPU_EXPORT void wgpuRenderPassEncoderEndPass(wgpuRenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderReference(wgpuRenderPassEncoder renderPassEncoder);
WGPU_EXPORT void wgpuRenderPassEncoderRelease(wgpuRenderPassEncoder renderPassEncoder);

// Methods of RenderPipeline
WGPU_EXPORT void wgpuRenderPipelineReference(wgpuRenderPipeline renderPipeline);
WGPU_EXPORT void wgpuRenderPipelineRelease(wgpuRenderPipeline renderPipeline);

// Methods of Sampler
WGPU_EXPORT void wgpuSamplerReference(wgpuSampler sampler);
WGPU_EXPORT void wgpuSamplerRelease(wgpuSampler sampler);

// Methods of ShaderModule
WGPU_EXPORT void wgpuShaderModuleReference(wgpuShaderModule shaderModule);
WGPU_EXPORT void wgpuShaderModuleRelease(wgpuShaderModule shaderModule);

// Methods of Texture
WGPU_EXPORT wgpuTextureView wgpuTextureCreateDefaultView(wgpuTexture texture);
WGPU_EXPORT wgpuTextureView wgpuTextureCreateView(wgpuTexture texture, wgpuTextureViewDescriptor const * descriptor);
WGPU_EXPORT void wgpuTextureDestroy(wgpuTexture texture);
WGPU_EXPORT void wgpuTextureReference(wgpuTexture texture);
WGPU_EXPORT void wgpuTextureRelease(wgpuTexture texture);

// Methods of TextureView
WGPU_EXPORT void wgpuTextureViewReference(wgpuTextureView textureView);
WGPU_EXPORT void wgpuTextureViewRelease(wgpuTextureView textureView);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WGPU_WGPU_H_
