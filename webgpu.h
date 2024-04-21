/**
 * Copyright 2019-2023 WebGPU-Native developers
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file */

/**
 * \mainpage
 * 
 * **NB** *This documentation is a Work In Progress.*
 *
 * This is the home of WebGPU Native specification. We define here the standard
 * `webgpu.h` header that all implementations of WebGPU should implement.
 */

#ifndef WEBGPU_H_
#define WEBGPU_H_

#if defined(WGPU_SHARED_LIBRARY)
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
#else       // defined(WGPU_SHARED_LIBRARY)
#    define WGPU_EXPORT
#endif  // defined(WGPU_SHARED_LIBRARY)

#if !defined(WGPU_OBJECT_ATTRIBUTE)
#define WGPU_OBJECT_ATTRIBUTE
#endif
#if !defined(WGPU_ENUM_ATTRIBUTE)
#define WGPU_ENUM_ATTRIBUTE
#endif
#if !defined(WGPU_STRUCTURE_ATTRIBUTE)
#define WGPU_STRUCTURE_ATTRIBUTE
#endif
#if !defined(WGPU_FUNCTION_ATTRIBUTE)
#define WGPU_FUNCTION_ATTRIBUTE
#endif
#if !defined(WGPU_NULLABLE)
#define WGPU_NULLABLE
#endif

#include <stdint.h>
#include <stddef.h>


/**
 * \defgroup Constants
 * \brief Constants.
 * 
 * @{
 */
#define WGPU_ARRAY_LAYER_COUNT_UNDEFINED (0xffffffffUL)
#define WGPU_COPY_STRIDE_UNDEFINED (0xffffffffUL)
#define WGPU_DEPTH_SLICE_UNDEFINED (0xffffffffUL)
#define WGPU_LIMIT_U32_UNDEFINED (0xffffffffUL)
#define WGPU_LIMIT_U64_UNDEFINED (0xffffffffffffffffULL)
#define WGPU_MIP_LEVEL_COUNT_UNDEFINED (0xffffffffUL)
#define WGPU_QUERY_SET_INDEX_UNDEFINED (0xffffffffUL)
#define WGPU_WHOLE_MAP_SIZE (SIZE_MAX)
#define WGPU_WHOLE_SIZE (0xffffffffffffffffULL)


/** @} */

/**
 * \defgroup Typedefs
 * \brief Utility typedefs.
 * 
 * @{
 */
typedef uint32_t WGPUFlags;
typedef uint32_t WGPUBool;


/** @} */

/**
 * \defgroup Objects
 * \brief Blind handles to WebGPU objects.
 * 
 * @{
 */
typedef struct WGPUAdapterImpl* WGPUAdapter WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBindGroupImpl* WGPUBindGroup WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBindGroupLayoutImpl* WGPUBindGroupLayout WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUBufferImpl* WGPUBuffer WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUCommandBufferImpl* WGPUCommandBuffer WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUCommandEncoderImpl* WGPUCommandEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUComputePassEncoderImpl* WGPUComputePassEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUComputePipelineImpl* WGPUComputePipeline WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUDeviceImpl* WGPUDevice WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUInstanceImpl* WGPUInstance WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUPipelineLayoutImpl* WGPUPipelineLayout WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUQuerySetImpl* WGPUQuerySet WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUQueueImpl* WGPUQueue WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderBundleImpl* WGPURenderBundle WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderBundleEncoderImpl* WGPURenderBundleEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderPassEncoderImpl* WGPURenderPassEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderPipelineImpl* WGPURenderPipeline WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSamplerImpl* WGPUSampler WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUShaderModuleImpl* WGPUShaderModule WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUSurfaceImpl* WGPUSurface WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureImpl* WGPUTexture WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureViewImpl* WGPUTextureView WGPU_OBJECT_ATTRIBUTE;


/** @} */
// Structure forward declarations
struct WGPUAdapterInfo;
struct WGPUAdapterProperties;
struct WGPUBindGroupEntry;
struct WGPUBlendComponent;
struct WGPUBufferBindingLayout;
struct WGPUBufferDescriptor;
struct WGPUColor;
struct WGPUCommandBufferDescriptor;
struct WGPUCommandEncoderDescriptor;
struct WGPUCompilationMessage;
struct WGPUComputePassTimestampWrites;
struct WGPUConstantEntry;
struct WGPUExtent3D;
struct WGPUInstanceDescriptor;
struct WGPULimits;
struct WGPUMultisampleState;
struct WGPUOrigin3D;
struct WGPUPipelineLayoutDescriptor;
struct WGPUPrimitiveDepthClipControl;
struct WGPUPrimitiveState;
struct WGPUQuerySetDescriptor;
struct WGPUQueueDescriptor;
struct WGPURenderBundleDescriptor;
struct WGPURenderBundleEncoderDescriptor;
struct WGPURenderPassDepthStencilAttachment;
struct WGPURenderPassDescriptorMaxDrawCount;
struct WGPURenderPassTimestampWrites;
struct WGPURequestAdapterOptions;
struct WGPUSamplerBindingLayout;
struct WGPUSamplerDescriptor;
struct WGPUShaderModuleCompilationHint;
struct WGPUShaderModuleSPIRVDescriptor;
struct WGPUShaderModuleWGSLDescriptor;
struct WGPUStencilFaceState;
struct WGPUStorageTextureBindingLayout;
struct WGPUSurfaceCapabilities;
struct WGPUSurfaceConfiguration;
struct WGPUSurfaceDescriptor;
struct WGPUSurfaceDescriptorFromAndroidNativeWindow;
struct WGPUSurfaceDescriptorFromCanvasHTMLSelector;
struct WGPUSurfaceDescriptorFromMetalLayer;
struct WGPUSurfaceDescriptorFromWaylandSurface;
struct WGPUSurfaceDescriptorFromWindowsHWND;
struct WGPUSurfaceDescriptorFromXcbWindow;
struct WGPUSurfaceDescriptorFromXlibWindow;
struct WGPUSurfaceTexture;
struct WGPUTextureBindingLayout;
struct WGPUTextureDataLayout;
struct WGPUTextureViewDescriptor;
struct WGPUVertexAttribute;
struct WGPUBindGroupDescriptor;
struct WGPUBindGroupLayoutEntry;
struct WGPUBlendState;
struct WGPUCompilationInfo;
struct WGPUComputePassDescriptor;
struct WGPUDepthStencilState;
struct WGPUImageCopyBuffer;
struct WGPUImageCopyTexture;
struct WGPUProgrammableStageDescriptor;
struct WGPURenderPassColorAttachment;
struct WGPURequiredLimits;
struct WGPUShaderModuleDescriptor;
struct WGPUSupportedLimits;
struct WGPUTextureDescriptor;
struct WGPUVertexBufferLayout;
struct WGPUBindGroupLayoutDescriptor;
struct WGPUColorTargetState;
struct WGPUComputePipelineDescriptor;
struct WGPUDeviceDescriptor;
struct WGPURenderPassDescriptor;
struct WGPUVertexState;
struct WGPUFragmentState;
struct WGPURenderPipelineDescriptor;


/**
 * \defgroup Enumerations
 * \brief Enums.
 * 
 * @{
 */
typedef enum WGPUAdapterType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUAdapterType_DiscreteGPU = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUAdapterType_IntegratedGPU = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUAdapterType_CPU = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUAdapterType_Unknown = 0x00000003,
    WGPUAdapterType_Force32 = 0x7FFFFFFF
} WGPUAdapterType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUAddressMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUAddressMode_Repeat = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUAddressMode_MirrorRepeat = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUAddressMode_ClampToEdge = 0x00000002,
    WGPUAddressMode_Force32 = 0x7FFFFFFF
} WGPUAddressMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBackendType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBackendType_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBackendType_Null = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBackendType_WebGPU = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUBackendType_D3D11 = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUBackendType_D3D12 = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUBackendType_Metal = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUBackendType_Vulkan = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUBackendType_OpenGL = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUBackendType_OpenGLES = 0x00000008,
    WGPUBackendType_Force32 = 0x7FFFFFFF
} WGPUBackendType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendFactor {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBlendFactor_Zero = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBlendFactor_One = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBlendFactor_Src = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUBlendFactor_OneMinusSrc = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUBlendFactor_SrcAlpha = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUBlendFactor_OneMinusSrcAlpha = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUBlendFactor_Dst = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUBlendFactor_OneMinusDst = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUBlendFactor_DstAlpha = 0x00000008,
    /**
     * `0x00000009` 
     * TODO
     */
    WGPUBlendFactor_OneMinusDstAlpha = 0x00000009,
    /**
     * `0x0000000A` 
     * TODO
     */
    WGPUBlendFactor_SrcAlphaSaturated = 0x0000000A,
    /**
     * `0x0000000B` 
     * TODO
     */
    WGPUBlendFactor_Constant = 0x0000000B,
    /**
     * `0x0000000C` 
     * TODO
     */
    WGPUBlendFactor_OneMinusConstant = 0x0000000C,
    WGPUBlendFactor_Force32 = 0x7FFFFFFF
} WGPUBlendFactor WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendOperation {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBlendOperation_Add = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBlendOperation_Subtract = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBlendOperation_ReverseSubtract = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUBlendOperation_Min = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUBlendOperation_Max = 0x00000004,
    WGPUBlendOperation_Force32 = 0x7FFFFFFF
} WGPUBlendOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferBindingType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBufferBindingType_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBufferBindingType_Uniform = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBufferBindingType_Storage = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUBufferBindingType_ReadOnlyStorage = 0x00000003,
    WGPUBufferBindingType_Force32 = 0x7FFFFFFF
} WGPUBufferBindingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferMapAsyncStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_ValidationError = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_Unknown = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_DeviceLost = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_DestroyedBeforeCallback = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_UnmappedBeforeCallback = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_MappingAlreadyPending = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_OffsetOutOfRange = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUBufferMapAsyncStatus_SizeOutOfRange = 0x00000008,
    WGPUBufferMapAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUBufferMapAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferMapState {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBufferMapState_Unmapped = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBufferMapState_Pending = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBufferMapState_Mapped = 0x00000002,
    WGPUBufferMapState_Force32 = 0x7FFFFFFF
} WGPUBufferMapState WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompareFunction {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCompareFunction_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCompareFunction_Never = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCompareFunction_Less = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUCompareFunction_LessEqual = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUCompareFunction_Greater = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUCompareFunction_GreaterEqual = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUCompareFunction_Equal = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUCompareFunction_NotEqual = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUCompareFunction_Always = 0x00000008,
    WGPUCompareFunction_Force32 = 0x7FFFFFFF
} WGPUCompareFunction WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationInfoRequestStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCompilationInfoRequestStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCompilationInfoRequestStatus_Error = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCompilationInfoRequestStatus_DeviceLost = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUCompilationInfoRequestStatus_Unknown = 0x00000003,
    WGPUCompilationInfoRequestStatus_Force32 = 0x7FFFFFFF
} WGPUCompilationInfoRequestStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationMessageType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCompilationMessageType_Error = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCompilationMessageType_Warning = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCompilationMessageType_Info = 0x00000002,
    WGPUCompilationMessageType_Force32 = 0x7FFFFFFF
} WGPUCompilationMessageType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompositeAlphaMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCompositeAlphaMode_Auto = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCompositeAlphaMode_Opaque = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCompositeAlphaMode_Premultiplied = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUCompositeAlphaMode_Unpremultiplied = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUCompositeAlphaMode_Inherit = 0x00000004,
    WGPUCompositeAlphaMode_Force32 = 0x7FFFFFFF
} WGPUCompositeAlphaMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCreatePipelineAsyncStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_ValidationError = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_InternalError = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_DeviceLost = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_DeviceDestroyed = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUCreatePipelineAsyncStatus_Unknown = 0x00000005,
    WGPUCreatePipelineAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUCreatePipelineAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCullMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUCullMode_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUCullMode_Front = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUCullMode_Back = 0x00000002,
    WGPUCullMode_Force32 = 0x7FFFFFFF
} WGPUCullMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUDeviceLostReason {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUDeviceLostReason_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUDeviceLostReason_Destroyed = 0x00000001,
    WGPUDeviceLostReason_Force32 = 0x7FFFFFFF
} WGPUDeviceLostReason WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorFilter {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUErrorFilter_Validation = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUErrorFilter_OutOfMemory = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUErrorFilter_Internal = 0x00000002,
    WGPUErrorFilter_Force32 = 0x7FFFFFFF
} WGPUErrorFilter WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUErrorType_NoError = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUErrorType_Validation = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUErrorType_OutOfMemory = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUErrorType_Internal = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUErrorType_Unknown = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUErrorType_DeviceLost = 0x00000005,
    WGPUErrorType_Force32 = 0x7FFFFFFF
} WGPUErrorType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFeatureName {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUFeatureName_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUFeatureName_DepthClipControl = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUFeatureName_Depth32FloatStencil8 = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUFeatureName_TimestampQuery = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUFeatureName_TextureCompressionBC = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUFeatureName_TextureCompressionETC2 = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUFeatureName_TextureCompressionASTC = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUFeatureName_IndirectFirstInstance = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUFeatureName_ShaderF16 = 0x00000008,
    /**
     * `0x00000009` 
     * TODO
     */
    WGPUFeatureName_RG11B10UfloatRenderable = 0x00000009,
    /**
     * `0x0000000A` 
     * TODO
     */
    WGPUFeatureName_BGRA8UnormStorage = 0x0000000A,
    /**
     * `0x0000000B` 
     * TODO
     */
    WGPUFeatureName_Float32Filterable = 0x0000000B,
    WGPUFeatureName_Force32 = 0x7FFFFFFF
} WGPUFeatureName WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFilterMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUFilterMode_Nearest = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUFilterMode_Linear = 0x00000001,
    WGPUFilterMode_Force32 = 0x7FFFFFFF
} WGPUFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFrontFace {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUFrontFace_CCW = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUFrontFace_CW = 0x00000001,
    WGPUFrontFace_Force32 = 0x7FFFFFFF
} WGPUFrontFace WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUIndexFormat {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUIndexFormat_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUIndexFormat_Uint16 = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUIndexFormat_Uint32 = 0x00000002,
    WGPUIndexFormat_Force32 = 0x7FFFFFFF
} WGPUIndexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPULoadOp {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPULoadOp_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPULoadOp_Clear = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPULoadOp_Load = 0x00000002,
    WGPULoadOp_Force32 = 0x7FFFFFFF
} WGPULoadOp WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMipmapFilterMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUMipmapFilterMode_Nearest = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUMipmapFilterMode_Linear = 0x00000001,
    WGPUMipmapFilterMode_Force32 = 0x7FFFFFFF
} WGPUMipmapFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPowerPreference {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUPowerPreference_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUPowerPreference_LowPower = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUPowerPreference_HighPerformance = 0x00000002,
    WGPUPowerPreference_Force32 = 0x7FFFFFFF
} WGPUPowerPreference WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPresentMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUPresentMode_Fifo = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUPresentMode_FifoRelaxed = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUPresentMode_Immediate = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUPresentMode_Mailbox = 0x00000003,
    WGPUPresentMode_Force32 = 0x7FFFFFFF
} WGPUPresentMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPrimitiveTopology {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUPrimitiveTopology_PointList = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUPrimitiveTopology_LineList = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUPrimitiveTopology_LineStrip = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUPrimitiveTopology_TriangleList = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUPrimitiveTopology_TriangleStrip = 0x00000004,
    WGPUPrimitiveTopology_Force32 = 0x7FFFFFFF
} WGPUPrimitiveTopology WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueryType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUQueryType_Occlusion = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUQueryType_Timestamp = 0x00000001,
    WGPUQueryType_Force32 = 0x7FFFFFFF
} WGPUQueryType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueueWorkDoneStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUQueueWorkDoneStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUQueueWorkDoneStatus_Error = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUQueueWorkDoneStatus_Unknown = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUQueueWorkDoneStatus_DeviceLost = 0x00000003,
    WGPUQueueWorkDoneStatus_Force32 = 0x7FFFFFFF
} WGPUQueueWorkDoneStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestAdapterStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPURequestAdapterStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPURequestAdapterStatus_Unavailable = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPURequestAdapterStatus_Error = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPURequestAdapterStatus_Unknown = 0x00000003,
    WGPURequestAdapterStatus_Force32 = 0x7FFFFFFF
} WGPURequestAdapterStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestDeviceStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPURequestDeviceStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPURequestDeviceStatus_Error = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPURequestDeviceStatus_Unknown = 0x00000002,
    WGPURequestDeviceStatus_Force32 = 0x7FFFFFFF
} WGPURequestDeviceStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUSType_Invalid = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromMetalLayer = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromWindowsHWND = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromXlibWindow = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromCanvasHTMLSelector = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUSType_ShaderModuleSPIRVDescriptor = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUSType_ShaderModuleWGSLDescriptor = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUSType_PrimitiveDepthClipControl = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromWaylandSurface = 0x00000008,
    /**
     * `0x00000009` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromAndroidNativeWindow = 0x00000009,
    /**
     * `0x0000000A` 
     * TODO
     */
    WGPUSType_SurfaceDescriptorFromXcbWindow = 0x0000000A,
    /**
     * `0x0000000F` 
     * TODO
     */
    WGPUSType_RenderPassDescriptorMaxDrawCount = 0x0000000F,
    WGPUSType_Force32 = 0x7FFFFFFF
} WGPUSType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSamplerBindingType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUSamplerBindingType_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUSamplerBindingType_Filtering = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUSamplerBindingType_NonFiltering = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUSamplerBindingType_Comparison = 0x00000003,
    WGPUSamplerBindingType_Force32 = 0x7FFFFFFF
} WGPUSamplerBindingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStencilOperation {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUStencilOperation_Keep = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUStencilOperation_Zero = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUStencilOperation_Replace = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUStencilOperation_Invert = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUStencilOperation_IncrementClamp = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUStencilOperation_DecrementClamp = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUStencilOperation_IncrementWrap = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUStencilOperation_DecrementWrap = 0x00000007,
    WGPUStencilOperation_Force32 = 0x7FFFFFFF
} WGPUStencilOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStorageTextureAccess {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUStorageTextureAccess_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUStorageTextureAccess_WriteOnly = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUStorageTextureAccess_ReadOnly = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUStorageTextureAccess_ReadWrite = 0x00000003,
    WGPUStorageTextureAccess_Force32 = 0x7FFFFFFF
} WGPUStorageTextureAccess WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStoreOp {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUStoreOp_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUStoreOp_Store = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUStoreOp_Discard = 0x00000002,
    WGPUStoreOp_Force32 = 0x7FFFFFFF
} WGPUStoreOp WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSurfaceGetCurrentTextureStatus {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_Success = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_Timeout = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_Outdated = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_Lost = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_OutOfMemory = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUSurfaceGetCurrentTextureStatus_DeviceLost = 0x00000005,
    WGPUSurfaceGetCurrentTextureStatus_Force32 = 0x7FFFFFFF
} WGPUSurfaceGetCurrentTextureStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureAspect {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureAspect_All = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureAspect_StencilOnly = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureAspect_DepthOnly = 0x00000002,
    WGPUTextureAspect_Force32 = 0x7FFFFFFF
} WGPUTextureAspect WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureDimension {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureDimension_1D = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureDimension_2D = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureDimension_3D = 0x00000002,
    WGPUTextureDimension_Force32 = 0x7FFFFFFF
} WGPUTextureDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureFormat {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureFormat_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureFormat_R8Unorm = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureFormat_R8Snorm = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUTextureFormat_R8Uint = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUTextureFormat_R8Sint = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUTextureFormat_R16Uint = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUTextureFormat_R16Sint = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUTextureFormat_R16Float = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUTextureFormat_RG8Unorm = 0x00000008,
    /**
     * `0x00000009` 
     * TODO
     */
    WGPUTextureFormat_RG8Snorm = 0x00000009,
    /**
     * `0x0000000A` 
     * TODO
     */
    WGPUTextureFormat_RG8Uint = 0x0000000A,
    /**
     * `0x0000000B` 
     * TODO
     */
    WGPUTextureFormat_RG8Sint = 0x0000000B,
    /**
     * `0x0000000C` 
     * TODO
     */
    WGPUTextureFormat_R32Float = 0x0000000C,
    /**
     * `0x0000000D` 
     * TODO
     */
    WGPUTextureFormat_R32Uint = 0x0000000D,
    /**
     * `0x0000000E` 
     * TODO
     */
    WGPUTextureFormat_R32Sint = 0x0000000E,
    /**
     * `0x0000000F` 
     * TODO
     */
    WGPUTextureFormat_RG16Uint = 0x0000000F,
    /**
     * `0x00000010` 
     * TODO
     */
    WGPUTextureFormat_RG16Sint = 0x00000010,
    /**
     * `0x00000011` 
     * TODO
     */
    WGPUTextureFormat_RG16Float = 0x00000011,
    /**
     * `0x00000012` 
     * TODO
     */
    WGPUTextureFormat_RGBA8Unorm = 0x00000012,
    /**
     * `0x00000013` 
     * TODO
     */
    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000013,
    /**
     * `0x00000014` 
     * TODO
     */
    WGPUTextureFormat_RGBA8Snorm = 0x00000014,
    /**
     * `0x00000015` 
     * TODO
     */
    WGPUTextureFormat_RGBA8Uint = 0x00000015,
    /**
     * `0x00000016` 
     * TODO
     */
    WGPUTextureFormat_RGBA8Sint = 0x00000016,
    /**
     * `0x00000017` 
     * TODO
     */
    WGPUTextureFormat_BGRA8Unorm = 0x00000017,
    /**
     * `0x00000018` 
     * TODO
     */
    WGPUTextureFormat_BGRA8UnormSrgb = 0x00000018,
    /**
     * `0x00000019` 
     * TODO
     */
    WGPUTextureFormat_RGB10A2Uint = 0x00000019,
    /**
     * `0x0000001A` 
     * TODO
     */
    WGPUTextureFormat_RGB10A2Unorm = 0x0000001A,
    /**
     * `0x0000001B` 
     * TODO
     */
    WGPUTextureFormat_RG11B10Ufloat = 0x0000001B,
    /**
     * `0x0000001C` 
     * TODO
     */
    WGPUTextureFormat_RGB9E5Ufloat = 0x0000001C,
    /**
     * `0x0000001D` 
     * TODO
     */
    WGPUTextureFormat_RG32Float = 0x0000001D,
    /**
     * `0x0000001E` 
     * TODO
     */
    WGPUTextureFormat_RG32Uint = 0x0000001E,
    /**
     * `0x0000001F` 
     * TODO
     */
    WGPUTextureFormat_RG32Sint = 0x0000001F,
    /**
     * `0x00000020` 
     * TODO
     */
    WGPUTextureFormat_RGBA16Uint = 0x00000020,
    /**
     * `0x00000021` 
     * TODO
     */
    WGPUTextureFormat_RGBA16Sint = 0x00000021,
    /**
     * `0x00000022` 
     * TODO
     */
    WGPUTextureFormat_RGBA16Float = 0x00000022,
    /**
     * `0x00000023` 
     * TODO
     */
    WGPUTextureFormat_RGBA32Float = 0x00000023,
    /**
     * `0x00000024` 
     * TODO
     */
    WGPUTextureFormat_RGBA32Uint = 0x00000024,
    /**
     * `0x00000025` 
     * TODO
     */
    WGPUTextureFormat_RGBA32Sint = 0x00000025,
    /**
     * `0x00000026` 
     * TODO
     */
    WGPUTextureFormat_Stencil8 = 0x00000026,
    /**
     * `0x00000027` 
     * TODO
     */
    WGPUTextureFormat_Depth16Unorm = 0x00000027,
    /**
     * `0x00000028` 
     * TODO
     */
    WGPUTextureFormat_Depth24Plus = 0x00000028,
    /**
     * `0x00000029` 
     * TODO
     */
    WGPUTextureFormat_Depth24PlusStencil8 = 0x00000029,
    /**
     * `0x0000002A` 
     * TODO
     */
    WGPUTextureFormat_Depth32Float = 0x0000002A,
    /**
     * `0x0000002B` 
     * TODO
     */
    WGPUTextureFormat_Depth32FloatStencil8 = 0x0000002B,
    /**
     * `0x0000002C` 
     * TODO
     */
    WGPUTextureFormat_BC1RGBAUnorm = 0x0000002C,
    /**
     * `0x0000002D` 
     * TODO
     */
    WGPUTextureFormat_BC1RGBAUnormSrgb = 0x0000002D,
    /**
     * `0x0000002E` 
     * TODO
     */
    WGPUTextureFormat_BC2RGBAUnorm = 0x0000002E,
    /**
     * `0x0000002F` 
     * TODO
     */
    WGPUTextureFormat_BC2RGBAUnormSrgb = 0x0000002F,
    /**
     * `0x00000030` 
     * TODO
     */
    WGPUTextureFormat_BC3RGBAUnorm = 0x00000030,
    /**
     * `0x00000031` 
     * TODO
     */
    WGPUTextureFormat_BC3RGBAUnormSrgb = 0x00000031,
    /**
     * `0x00000032` 
     * TODO
     */
    WGPUTextureFormat_BC4RUnorm = 0x00000032,
    /**
     * `0x00000033` 
     * TODO
     */
    WGPUTextureFormat_BC4RSnorm = 0x00000033,
    /**
     * `0x00000034` 
     * TODO
     */
    WGPUTextureFormat_BC5RGUnorm = 0x00000034,
    /**
     * `0x00000035` 
     * TODO
     */
    WGPUTextureFormat_BC5RGSnorm = 0x00000035,
    /**
     * `0x00000036` 
     * TODO
     */
    WGPUTextureFormat_BC6HRGBUfloat = 0x00000036,
    /**
     * `0x00000037` 
     * TODO
     */
    WGPUTextureFormat_BC6HRGBFloat = 0x00000037,
    /**
     * `0x00000038` 
     * TODO
     */
    WGPUTextureFormat_BC7RGBAUnorm = 0x00000038,
    /**
     * `0x00000039` 
     * TODO
     */
    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x00000039,
    /**
     * `0x0000003A` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGB8Unorm = 0x0000003A,
    /**
     * `0x0000003B` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGB8UnormSrgb = 0x0000003B,
    /**
     * `0x0000003C` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGB8A1Unorm = 0x0000003C,
    /**
     * `0x0000003D` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGB8A1UnormSrgb = 0x0000003D,
    /**
     * `0x0000003E` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGBA8Unorm = 0x0000003E,
    /**
     * `0x0000003F` 
     * TODO
     */
    WGPUTextureFormat_ETC2RGBA8UnormSrgb = 0x0000003F,
    /**
     * `0x00000040` 
     * TODO
     */
    WGPUTextureFormat_EACR11Unorm = 0x00000040,
    /**
     * `0x00000041` 
     * TODO
     */
    WGPUTextureFormat_EACR11Snorm = 0x00000041,
    /**
     * `0x00000042` 
     * TODO
     */
    WGPUTextureFormat_EACRG11Unorm = 0x00000042,
    /**
     * `0x00000043` 
     * TODO
     */
    WGPUTextureFormat_EACRG11Snorm = 0x00000043,
    /**
     * `0x00000044` 
     * TODO
     */
    WGPUTextureFormat_ASTC4x4Unorm = 0x00000044,
    /**
     * `0x00000045` 
     * TODO
     */
    WGPUTextureFormat_ASTC4x4UnormSrgb = 0x00000045,
    /**
     * `0x00000046` 
     * TODO
     */
    WGPUTextureFormat_ASTC5x4Unorm = 0x00000046,
    /**
     * `0x00000047` 
     * TODO
     */
    WGPUTextureFormat_ASTC5x4UnormSrgb = 0x00000047,
    /**
     * `0x00000048` 
     * TODO
     */
    WGPUTextureFormat_ASTC5x5Unorm = 0x00000048,
    /**
     * `0x00000049` 
     * TODO
     */
    WGPUTextureFormat_ASTC5x5UnormSrgb = 0x00000049,
    /**
     * `0x0000004A` 
     * TODO
     */
    WGPUTextureFormat_ASTC6x5Unorm = 0x0000004A,
    /**
     * `0x0000004B` 
     * TODO
     */
    WGPUTextureFormat_ASTC6x5UnormSrgb = 0x0000004B,
    /**
     * `0x0000004C` 
     * TODO
     */
    WGPUTextureFormat_ASTC6x6Unorm = 0x0000004C,
    /**
     * `0x0000004D` 
     * TODO
     */
    WGPUTextureFormat_ASTC6x6UnormSrgb = 0x0000004D,
    /**
     * `0x0000004E` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x5Unorm = 0x0000004E,
    /**
     * `0x0000004F` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x5UnormSrgb = 0x0000004F,
    /**
     * `0x00000050` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x6Unorm = 0x00000050,
    /**
     * `0x00000051` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x6UnormSrgb = 0x00000051,
    /**
     * `0x00000052` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x8Unorm = 0x00000052,
    /**
     * `0x00000053` 
     * TODO
     */
    WGPUTextureFormat_ASTC8x8UnormSrgb = 0x00000053,
    /**
     * `0x00000054` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x5Unorm = 0x00000054,
    /**
     * `0x00000055` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x5UnormSrgb = 0x00000055,
    /**
     * `0x00000056` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x6Unorm = 0x00000056,
    /**
     * `0x00000057` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x6UnormSrgb = 0x00000057,
    /**
     * `0x00000058` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x8Unorm = 0x00000058,
    /**
     * `0x00000059` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x8UnormSrgb = 0x00000059,
    /**
     * `0x0000005A` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x10Unorm = 0x0000005A,
    /**
     * `0x0000005B` 
     * TODO
     */
    WGPUTextureFormat_ASTC10x10UnormSrgb = 0x0000005B,
    /**
     * `0x0000005C` 
     * TODO
     */
    WGPUTextureFormat_ASTC12x10Unorm = 0x0000005C,
    /**
     * `0x0000005D` 
     * TODO
     */
    WGPUTextureFormat_ASTC12x10UnormSrgb = 0x0000005D,
    /**
     * `0x0000005E` 
     * TODO
     */
    WGPUTextureFormat_ASTC12x12Unorm = 0x0000005E,
    /**
     * `0x0000005F` 
     * TODO
     */
    WGPUTextureFormat_ASTC12x12UnormSrgb = 0x0000005F,
    WGPUTextureFormat_Force32 = 0x7FFFFFFF
} WGPUTextureFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureSampleType {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureSampleType_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureSampleType_Float = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureSampleType_UnfilterableFloat = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUTextureSampleType_Depth = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUTextureSampleType_Sint = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUTextureSampleType_Uint = 0x00000005,
    WGPUTextureSampleType_Force32 = 0x7FFFFFFF
} WGPUTextureSampleType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureViewDimension {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureViewDimension_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureViewDimension_1D = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureViewDimension_2D = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUTextureViewDimension_2DArray = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUTextureViewDimension_Cube = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUTextureViewDimension_CubeArray = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUTextureViewDimension_3D = 0x00000006,
    WGPUTextureViewDimension_Force32 = 0x7FFFFFFF
} WGPUTextureViewDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexFormat {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUVertexFormat_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUVertexFormat_Uint8x2 = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUVertexFormat_Uint8x4 = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUVertexFormat_Sint8x2 = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUVertexFormat_Sint8x4 = 0x00000004,
    /**
     * `0x00000005` 
     * TODO
     */
    WGPUVertexFormat_Unorm8x2 = 0x00000005,
    /**
     * `0x00000006` 
     * TODO
     */
    WGPUVertexFormat_Unorm8x4 = 0x00000006,
    /**
     * `0x00000007` 
     * TODO
     */
    WGPUVertexFormat_Snorm8x2 = 0x00000007,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUVertexFormat_Snorm8x4 = 0x00000008,
    /**
     * `0x00000009` 
     * TODO
     */
    WGPUVertexFormat_Uint16x2 = 0x00000009,
    /**
     * `0x0000000A` 
     * TODO
     */
    WGPUVertexFormat_Uint16x4 = 0x0000000A,
    /**
     * `0x0000000B` 
     * TODO
     */
    WGPUVertexFormat_Sint16x2 = 0x0000000B,
    /**
     * `0x0000000C` 
     * TODO
     */
    WGPUVertexFormat_Sint16x4 = 0x0000000C,
    /**
     * `0x0000000D` 
     * TODO
     */
    WGPUVertexFormat_Unorm16x2 = 0x0000000D,
    /**
     * `0x0000000E` 
     * TODO
     */
    WGPUVertexFormat_Unorm16x4 = 0x0000000E,
    /**
     * `0x0000000F` 
     * TODO
     */
    WGPUVertexFormat_Snorm16x2 = 0x0000000F,
    /**
     * `0x00000010` 
     * TODO
     */
    WGPUVertexFormat_Snorm16x4 = 0x00000010,
    /**
     * `0x00000011` 
     * TODO
     */
    WGPUVertexFormat_Float16x2 = 0x00000011,
    /**
     * `0x00000012` 
     * TODO
     */
    WGPUVertexFormat_Float16x4 = 0x00000012,
    /**
     * `0x00000013` 
     * TODO
     */
    WGPUVertexFormat_Float32 = 0x00000013,
    /**
     * `0x00000014` 
     * TODO
     */
    WGPUVertexFormat_Float32x2 = 0x00000014,
    /**
     * `0x00000015` 
     * TODO
     */
    WGPUVertexFormat_Float32x3 = 0x00000015,
    /**
     * `0x00000016` 
     * TODO
     */
    WGPUVertexFormat_Float32x4 = 0x00000016,
    /**
     * `0x00000017` 
     * TODO
     */
    WGPUVertexFormat_Uint32 = 0x00000017,
    /**
     * `0x00000018` 
     * TODO
     */
    WGPUVertexFormat_Uint32x2 = 0x00000018,
    /**
     * `0x00000019` 
     * TODO
     */
    WGPUVertexFormat_Uint32x3 = 0x00000019,
    /**
     * `0x0000001A` 
     * TODO
     */
    WGPUVertexFormat_Uint32x4 = 0x0000001A,
    /**
     * `0x0000001B` 
     * TODO
     */
    WGPUVertexFormat_Sint32 = 0x0000001B,
    /**
     * `0x0000001C` 
     * TODO
     */
    WGPUVertexFormat_Sint32x2 = 0x0000001C,
    /**
     * `0x0000001D` 
     * TODO
     */
    WGPUVertexFormat_Sint32x3 = 0x0000001D,
    /**
     * `0x0000001E` 
     * TODO
     */
    WGPUVertexFormat_Sint32x4 = 0x0000001E,
    WGPUVertexFormat_Force32 = 0x7FFFFFFF
} WGPUVertexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexStepMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUVertexStepMode_Vertex = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUVertexStepMode_Instance = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUVertexStepMode_VertexBufferNotUsed = 0x00000002,
    WGPUVertexStepMode_Force32 = 0x7FFFFFFF
} WGPUVertexStepMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUWGSLFeatureName {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUWGSLFeatureName_Undefined = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUWGSLFeatureName_ReadonlyAndReadwriteStorageTextures = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUWGSLFeatureName_Packed4x8IntegerDotProduct = 0x00000002,
    /**
     * `0x00000003` 
     * TODO
     */
    WGPUWGSLFeatureName_UnrestrictedPointerParameters = 0x00000003,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUWGSLFeatureName_PointerCompositeAccess = 0x00000004,
    WGPUWGSLFeatureName_Force32 = 0x7FFFFFFF
} WGPUWGSLFeatureName WGPU_ENUM_ATTRIBUTE;


/** @} */

/**
 * \defgroup Bitflags
 * \brief Enum used as bit flags.
 * 
 * @{
 */
typedef enum WGPUBufferUsage {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUBufferUsage_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUBufferUsage_MapRead = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUBufferUsage_MapWrite = 0x00000002,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUBufferUsage_CopySrc = 0x00000004,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUBufferUsage_CopyDst = 0x00000008,
    /**
     * `0x00000010` 
     * TODO
     */
    WGPUBufferUsage_Index = 0x00000010,
    /**
     * `0x00000020` 
     * TODO
     */
    WGPUBufferUsage_Vertex = 0x00000020,
    /**
     * `0x00000040` 
     * TODO
     */
    WGPUBufferUsage_Uniform = 0x00000040,
    /**
     * `0x00000080` 
     * TODO
     */
    WGPUBufferUsage_Storage = 0x00000080,
    /**
     * `0x00000100` 
     * TODO
     */
    WGPUBufferUsage_Indirect = 0x00000100,
    /**
     * `0x00000200` 
     * TODO
     */
    WGPUBufferUsage_QueryResolve = 0x00000200,
    WGPUBufferUsage_Force32 = 0x7FFFFFFF
} WGPUBufferUsage WGPU_ENUM_ATTRIBUTE;
typedef WGPUFlags WGPUBufferUsageFlags WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUColorWriteMask {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUColorWriteMask_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUColorWriteMask_Red = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUColorWriteMask_Green = 0x00000002,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUColorWriteMask_Blue = 0x00000004,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUColorWriteMask_Alpha = 0x00000008,
    /**
     * `WGPUColorWriteMask_None | WGPUColorWriteMask_Red | WGPUColorWriteMask_Green | WGPUColorWriteMask_Blue | WGPUColorWriteMask_Alpha` 
     * TODO
     */
    WGPUColorWriteMask_All = WGPUColorWriteMask_None | WGPUColorWriteMask_Red | WGPUColorWriteMask_Green | WGPUColorWriteMask_Blue | WGPUColorWriteMask_Alpha,
    WGPUColorWriteMask_Force32 = 0x7FFFFFFF
} WGPUColorWriteMask WGPU_ENUM_ATTRIBUTE;
typedef WGPUFlags WGPUColorWriteMaskFlags WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMapMode {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUMapMode_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUMapMode_Read = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUMapMode_Write = 0x00000002,
    WGPUMapMode_Force32 = 0x7FFFFFFF
} WGPUMapMode WGPU_ENUM_ATTRIBUTE;
typedef WGPUFlags WGPUMapModeFlags WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUShaderStage {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUShaderStage_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUShaderStage_Vertex = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUShaderStage_Fragment = 0x00000002,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUShaderStage_Compute = 0x00000004,
    WGPUShaderStage_Force32 = 0x7FFFFFFF
} WGPUShaderStage WGPU_ENUM_ATTRIBUTE;
typedef WGPUFlags WGPUShaderStageFlags WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureUsage {
    /**
     * `0x00000000` 
     * TODO
     */
    WGPUTextureUsage_None = 0x00000000,
    /**
     * `0x00000001` 
     * TODO
     */
    WGPUTextureUsage_CopySrc = 0x00000001,
    /**
     * `0x00000002` 
     * TODO
     */
    WGPUTextureUsage_CopyDst = 0x00000002,
    /**
     * `0x00000004` 
     * TODO
     */
    WGPUTextureUsage_TextureBinding = 0x00000004,
    /**
     * `0x00000008` 
     * TODO
     */
    WGPUTextureUsage_StorageBinding = 0x00000008,
    /**
     * `0x00000010` 
     * TODO
     */
    WGPUTextureUsage_RenderAttachment = 0x00000010,
    WGPUTextureUsage_Force32 = 0x7FFFFFFF
} WGPUTextureUsage WGPU_ENUM_ATTRIBUTE;
typedef WGPUFlags WGPUTextureUsageFlags WGPU_ENUM_ATTRIBUTE;


/** @} */
typedef void (*WGPUProc)(void) WGPU_FUNCTION_ATTRIBUTE;

typedef void (*WGPUDeviceLostCallback)(WGPUDeviceLostReason reason, char const * message, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUErrorCallback)(WGPUErrorType type, char const * message, void * userdata) WGPU_FUNCTION_ATTRIBUTE;

/**
 * \defgroup Callbacks
 * \brief Callbacks through which asynchronous functions return.
 * 
 * @{
 */

typedef void (*WGPUAdapterRequestAdapterInfoCallback)(struct WGPUAdapterInfo adapterInfo, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUAdapterRequestDeviceCallback)(WGPURequestDeviceStatus status, WGPUDevice device, char const * message, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUBufferMapAsyncCallback)(WGPUBufferMapAsyncStatus status, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUDeviceCreateComputePipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPUComputePipeline pipeline, char const * message, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUDeviceCreateRenderPipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPURenderPipeline pipeline, char const * message, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUInstanceRequestAdapterCallback)(WGPURequestAdapterStatus status, WGPUAdapter adapter, char const * message, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUQueueOnSubmittedWorkDoneCallback)(WGPUQueueWorkDoneStatus status, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUShaderModuleGetCompilationInfoCallback)(WGPUCompilationInfoRequestStatus status, struct WGPUCompilationInfo const * compilationInfo, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;


/** @} */
/**
 * \defgroup ChainedStructures Chained Structures
 * \brief Structures used to extend descriptors.
 * 
 * @{
 */

typedef struct WGPUChainedStruct {
    struct WGPUChainedStruct const * next;
    WGPUSType sType;
} WGPUChainedStruct WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUChainedStructOut {
    struct WGPUChainedStructOut * next;
    WGPUSType sType;
} WGPUChainedStructOut WGPU_STRUCTURE_ATTRIBUTE;

/** @} */


/**
 * \defgroup Structures
 * \brief Descriptors and other transparent structures.
 * 
 * @{
 */
typedef struct WGPUAdapterInfo {
    char const * vendor;
    char const * architecture;
    char const * device;
    char const * description;
} WGPUAdapterInfo WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUAdapterProperties {
    WGPUChainedStructOut * nextInChain;
    uint32_t vendorID;
    char const * vendorName;
    char const * architecture;
    uint32_t deviceID;
    char const * name;
    char const * driverDescription;
    WGPUAdapterType adapterType;
    WGPUBackendType backendType;
} WGPUAdapterProperties WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBindGroupEntry {
    WGPUChainedStruct const * nextInChain;
    uint32_t binding;
    WGPU_NULLABLE WGPUBuffer buffer;
    uint64_t offset;
    uint64_t size;
    WGPU_NULLABLE WGPUSampler sampler;
    WGPU_NULLABLE WGPUTextureView textureView;
} WGPUBindGroupEntry WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBlendComponent {
    WGPUBlendOperation operation;
    WGPUBlendFactor srcFactor;
    WGPUBlendFactor dstFactor;
} WGPUBlendComponent WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBufferBindingLayout {
    WGPUChainedStruct const * nextInChain;
    WGPUBufferBindingType type;
    WGPUBool hasDynamicOffset;
    uint64_t minBindingSize;
} WGPUBufferBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBufferDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUBufferUsageFlags usage;
    uint64_t size;
    WGPUBool mappedAtCreation;
} WGPUBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUColor {
    double r;
    double g;
    double b;
    double a;
} WGPUColor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUCommandBufferDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
} WGPUCommandBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUCommandEncoderDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
} WGPUCommandEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUCompilationMessage {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * message;
    WGPUCompilationMessageType type;
    uint64_t lineNum;
    uint64_t linePos;
    uint64_t offset;
    uint64_t length;
    uint64_t utf16LinePos;
    uint64_t utf16Offset;
    uint64_t utf16Length;
} WGPUCompilationMessage WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUComputePassTimestampWrites {
    WGPUQuerySet querySet;
    uint32_t beginningOfPassWriteIndex;
    uint32_t endOfPassWriteIndex;
} WGPUComputePassTimestampWrites WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUConstantEntry {
    WGPUChainedStruct const * nextInChain;
    char const * key;
    double value;
} WGPUConstantEntry WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUExtent3D {
    uint32_t width;
    uint32_t height;
    uint32_t depthOrArrayLayers;
} WGPUExtent3D WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUInstanceDescriptor {
    WGPUChainedStruct const * nextInChain;
} WGPUInstanceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPULimits {
    uint32_t maxTextureDimension1D;
    uint32_t maxTextureDimension2D;
    uint32_t maxTextureDimension3D;
    uint32_t maxTextureArrayLayers;
    uint32_t maxBindGroups;
    uint32_t maxBindGroupsPlusVertexBuffers;
    uint32_t maxBindingsPerBindGroup;
    uint32_t maxDynamicUniformBuffersPerPipelineLayout;
    uint32_t maxDynamicStorageBuffersPerPipelineLayout;
    uint32_t maxSampledTexturesPerShaderStage;
    uint32_t maxSamplersPerShaderStage;
    uint32_t maxStorageBuffersPerShaderStage;
    uint32_t maxStorageTexturesPerShaderStage;
    uint32_t maxUniformBuffersPerShaderStage;
    uint64_t maxUniformBufferBindingSize;
    uint64_t maxStorageBufferBindingSize;
    uint32_t minUniformBufferOffsetAlignment;
    uint32_t minStorageBufferOffsetAlignment;
    uint32_t maxVertexBuffers;
    uint64_t maxBufferSize;
    uint32_t maxVertexAttributes;
    uint32_t maxVertexBufferArrayStride;
    uint32_t maxInterStageShaderComponents;
    uint32_t maxInterStageShaderVariables;
    uint32_t maxColorAttachments;
    uint32_t maxColorAttachmentBytesPerSample;
    uint32_t maxComputeWorkgroupStorageSize;
    uint32_t maxComputeInvocationsPerWorkgroup;
    uint32_t maxComputeWorkgroupSizeX;
    uint32_t maxComputeWorkgroupSizeY;
    uint32_t maxComputeWorkgroupSizeZ;
    uint32_t maxComputeWorkgroupsPerDimension;
} WGPULimits WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUMultisampleState {
    WGPUChainedStruct const * nextInChain;
    uint32_t count;
    uint32_t mask;
    WGPUBool alphaToCoverageEnabled;
} WGPUMultisampleState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUOrigin3D {
    uint32_t x;
    uint32_t y;
    uint32_t z;
} WGPUOrigin3D WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUPipelineLayoutDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t bindGroupLayoutCount;
    WGPUBindGroupLayout const * bindGroupLayouts;
} WGPUPipelineLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUPrimitiveDepthClipControl {
    WGPUChainedStruct chain;
    WGPUBool unclippedDepth;
} WGPUPrimitiveDepthClipControl WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUPrimitiveState {
    WGPUChainedStruct const * nextInChain;
    WGPUPrimitiveTopology topology;
    WGPUIndexFormat stripIndexFormat;
    WGPUFrontFace frontFace;
    WGPUCullMode cullMode;
} WGPUPrimitiveState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUQuerySetDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUQueryType type;
    uint32_t count;
} WGPUQuerySetDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUQueueDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
} WGPUQueueDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderBundleDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
} WGPURenderBundleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderBundleEncoderDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t colorFormatCount;
    WGPUTextureFormat const * colorFormats;
    WGPUTextureFormat depthStencilFormat;
    uint32_t sampleCount;
    WGPUBool depthReadOnly;
    WGPUBool stencilReadOnly;
} WGPURenderBundleEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPassDepthStencilAttachment {
    WGPUTextureView view;
    WGPULoadOp depthLoadOp;
    WGPUStoreOp depthStoreOp;
    float depthClearValue;
    WGPUBool depthReadOnly;
    WGPULoadOp stencilLoadOp;
    WGPUStoreOp stencilStoreOp;
    uint32_t stencilClearValue;
    WGPUBool stencilReadOnly;
} WGPURenderPassDepthStencilAttachment WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPassDescriptorMaxDrawCount {
    WGPUChainedStruct chain;
    uint64_t maxDrawCount;
} WGPURenderPassDescriptorMaxDrawCount WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPassTimestampWrites {
    WGPUQuerySet querySet;
    uint32_t beginningOfPassWriteIndex;
    uint32_t endOfPassWriteIndex;
} WGPURenderPassTimestampWrites WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURequestAdapterOptions {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE WGPUSurface compatibleSurface;
    WGPUPowerPreference powerPreference;
    WGPUBackendType backendType;
    WGPUBool forceFallbackAdapter;
} WGPURequestAdapterOptions WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSamplerBindingLayout {
    WGPUChainedStruct const * nextInChain;
    WGPUSamplerBindingType type;
} WGPUSamplerBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSamplerDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUAddressMode addressModeU;
    WGPUAddressMode addressModeV;
    WGPUAddressMode addressModeW;
    WGPUFilterMode magFilter;
    WGPUFilterMode minFilter;
    WGPUMipmapFilterMode mipmapFilter;
    float lodMinClamp;
    float lodMaxClamp;
    WGPUCompareFunction compare;
    uint16_t maxAnisotropy;
} WGPUSamplerDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUShaderModuleCompilationHint {
    WGPUChainedStruct const * nextInChain;
    char const * entryPoint;
    WGPUPipelineLayout layout;
} WGPUShaderModuleCompilationHint WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUShaderModuleSPIRVDescriptor {
    WGPUChainedStruct chain;
    uint32_t codeSize;
    uint32_t const * code;
} WGPUShaderModuleSPIRVDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUShaderModuleWGSLDescriptor {
    WGPUChainedStruct chain;
    char const * code;
} WGPUShaderModuleWGSLDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUStencilFaceState {
    WGPUCompareFunction compare;
    WGPUStencilOperation failOp;
    WGPUStencilOperation depthFailOp;
    WGPUStencilOperation passOp;
} WGPUStencilFaceState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUStorageTextureBindingLayout {
    WGPUChainedStruct const * nextInChain;
    WGPUStorageTextureAccess access;
    WGPUTextureFormat format;
    WGPUTextureViewDimension viewDimension;
} WGPUStorageTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceCapabilities {
    WGPUChainedStructOut * nextInChain;
    size_t formatCount;
    WGPUTextureFormat const * formats;
    size_t presentModeCount;
    WGPUPresentMode const * presentModes;
    size_t alphaModeCount;
    WGPUCompositeAlphaMode const * alphaModes;
} WGPUSurfaceCapabilities WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceConfiguration {
    WGPUChainedStruct const * nextInChain;
    WGPUDevice device;
    WGPUTextureFormat format;
    WGPUTextureUsageFlags usage;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
    WGPUCompositeAlphaMode alphaMode;
    uint32_t width;
    uint32_t height;
    WGPUPresentMode presentMode;
} WGPUSurfaceConfiguration WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
} WGPUSurfaceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromAndroidNativeWindow {
    WGPUChainedStruct chain;
    void * window;
} WGPUSurfaceDescriptorFromAndroidNativeWindow WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromCanvasHTMLSelector {
    WGPUChainedStruct chain;
    char const * selector;
} WGPUSurfaceDescriptorFromCanvasHTMLSelector WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromMetalLayer {
    WGPUChainedStruct chain;
    void * layer;
} WGPUSurfaceDescriptorFromMetalLayer WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromWaylandSurface {
    WGPUChainedStruct chain;
    void * display;
    void * surface;
} WGPUSurfaceDescriptorFromWaylandSurface WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromWindowsHWND {
    WGPUChainedStruct chain;
    void * hinstance;
    void * hwnd;
} WGPUSurfaceDescriptorFromWindowsHWND WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromXcbWindow {
    WGPUChainedStruct chain;
    void * connection;
    uint32_t window;
} WGPUSurfaceDescriptorFromXcbWindow WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceDescriptorFromXlibWindow {
    WGPUChainedStruct chain;
    void * display;
    uint64_t window;
} WGPUSurfaceDescriptorFromXlibWindow WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSurfaceTexture {
    WGPUTexture texture;
    WGPUBool suboptimal;
    WGPUSurfaceGetCurrentTextureStatus status;
} WGPUSurfaceTexture WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUTextureBindingLayout {
    WGPUChainedStruct const * nextInChain;
    WGPUTextureSampleType sampleType;
    WGPUTextureViewDimension viewDimension;
    WGPUBool multisampled;
} WGPUTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUTextureDataLayout {
    WGPUChainedStruct const * nextInChain;
    uint64_t offset;
    uint32_t bytesPerRow;
    uint32_t rowsPerImage;
} WGPUTextureDataLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUTextureViewDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUTextureFormat format;
    WGPUTextureViewDimension dimension;
    uint32_t baseMipLevel;
    uint32_t mipLevelCount;
    uint32_t baseArrayLayer;
    uint32_t arrayLayerCount;
    WGPUTextureAspect aspect;
} WGPUTextureViewDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUVertexAttribute {
    WGPUVertexFormat format;
    uint64_t offset;
    uint32_t shaderLocation;
} WGPUVertexAttribute WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBindGroupDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUBindGroupLayout layout;
    size_t entryCount;
    WGPUBindGroupEntry const * entries;
} WGPUBindGroupDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBindGroupLayoutEntry {
    WGPUChainedStruct const * nextInChain;
    uint32_t binding;
    WGPUShaderStageFlags visibility;
    WGPUBufferBindingLayout buffer;
    WGPUSamplerBindingLayout sampler;
    WGPUTextureBindingLayout texture;
    WGPUStorageTextureBindingLayout storageTexture;
} WGPUBindGroupLayoutEntry WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBlendState {
    WGPUBlendComponent color;
    WGPUBlendComponent alpha;
} WGPUBlendState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUCompilationInfo {
    WGPUChainedStruct const * nextInChain;
    size_t messageCount;
    WGPUCompilationMessage const * messages;
} WGPUCompilationInfo WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUComputePassDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPU_NULLABLE WGPUComputePassTimestampWrites const * timestampWrites;
} WGPUComputePassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUDepthStencilState {
    WGPUChainedStruct const * nextInChain;
    WGPUTextureFormat format;
    WGPUBool depthWriteEnabled;
    WGPUCompareFunction depthCompare;
    WGPUStencilFaceState stencilFront;
    WGPUStencilFaceState stencilBack;
    uint32_t stencilReadMask;
    uint32_t stencilWriteMask;
    int32_t depthBias;
    float depthBiasSlopeScale;
    float depthBiasClamp;
} WGPUDepthStencilState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUImageCopyBuffer {
    WGPUChainedStruct const * nextInChain;
    WGPUTextureDataLayout layout;
    WGPUBuffer buffer;
} WGPUImageCopyBuffer WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUImageCopyTexture {
    WGPUChainedStruct const * nextInChain;
    WGPUTexture texture;
    uint32_t mipLevel;
    WGPUOrigin3D origin;
    WGPUTextureAspect aspect;
} WGPUImageCopyTexture WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUProgrammableStageDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPUShaderModule module;
    WGPU_NULLABLE char const * entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
} WGPUProgrammableStageDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPassColorAttachment {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE WGPUTextureView view;
    uint32_t depthSlice;
    WGPU_NULLABLE WGPUTextureView resolveTarget;
    WGPULoadOp loadOp;
    WGPUStoreOp storeOp;
    WGPUColor clearValue;
} WGPURenderPassColorAttachment WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURequiredLimits {
    WGPUChainedStruct const * nextInChain;
    WGPULimits limits;
} WGPURequiredLimits WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUShaderModuleDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t hintCount;
    WGPUShaderModuleCompilationHint const * hints;
} WGPUShaderModuleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUSupportedLimits {
    WGPUChainedStructOut * nextInChain;
    WGPULimits limits;
} WGPUSupportedLimits WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUTextureDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPUTextureUsageFlags usage;
    WGPUTextureDimension dimension;
    WGPUExtent3D size;
    WGPUTextureFormat format;
    uint32_t mipLevelCount;
    uint32_t sampleCount;
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
} WGPUTextureDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUVertexBufferLayout {
    uint64_t arrayStride;
    WGPUVertexStepMode stepMode;
    size_t attributeCount;
    WGPUVertexAttribute const * attributes;
} WGPUVertexBufferLayout WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUBindGroupLayoutDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t entryCount;
    WGPUBindGroupLayoutEntry const * entries;
} WGPUBindGroupLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUColorTargetState {
    WGPUChainedStruct const * nextInChain;
    WGPUTextureFormat format;
    WGPU_NULLABLE WGPUBlendState const * blend;
    WGPUColorWriteMaskFlags writeMask;
} WGPUColorTargetState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUComputePipelineDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPU_NULLABLE WGPUPipelineLayout layout;
    WGPUProgrammableStageDescriptor compute;
} WGPUComputePipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUDeviceDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t requiredFeatureCount;
    WGPUFeatureName const * requiredFeatures;
    WGPU_NULLABLE WGPURequiredLimits const * requiredLimits;
    WGPUQueueDescriptor defaultQueue;
    WGPUDeviceLostCallback deviceLostCallback;
    void * deviceLostUserdata;
} WGPUDeviceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPassDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    size_t colorAttachmentCount;
    WGPURenderPassColorAttachment const * colorAttachments;
    WGPU_NULLABLE WGPURenderPassDepthStencilAttachment const * depthStencilAttachment;
    WGPU_NULLABLE WGPUQuerySet occlusionQuerySet;
    WGPU_NULLABLE WGPURenderPassTimestampWrites const * timestampWrites;
} WGPURenderPassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUVertexState {
    WGPUChainedStruct const * nextInChain;
    WGPUShaderModule module;
    WGPU_NULLABLE char const * entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
    size_t bufferCount;
    WGPUVertexBufferLayout const * buffers;
} WGPUVertexState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPUFragmentState {
    WGPUChainedStruct const * nextInChain;
    WGPUShaderModule module;
    WGPU_NULLABLE char const * entryPoint;
    size_t constantCount;
    WGPUConstantEntry const * constants;
    size_t targetCount;
    WGPUColorTargetState const * targets;
} WGPUFragmentState WGPU_STRUCTURE_ATTRIBUTE;

typedef struct WGPURenderPipelineDescriptor {
    WGPUChainedStruct const * nextInChain;
    WGPU_NULLABLE char const * label;
    WGPU_NULLABLE WGPUPipelineLayout layout;
    WGPUVertexState vertex;
    WGPUPrimitiveState primitive;
    WGPU_NULLABLE WGPUDepthStencilState const * depthStencil;
    WGPUMultisampleState multisample;
    WGPU_NULLABLE WGPUFragmentState const * fragment;
} WGPURenderPipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WGPU_SKIP_PROCS)

typedef WGPUInstance (*WGPUProcCreateInstance)(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUProc (*WGPUProcGetProcAddress)(WGPUDevice device, char const * procName) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Adapter
typedef size_t (*WGPUProcAdapterEnumerateFeatures)(WGPUAdapter adapter, WGPUFeatureName * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcAdapterGetLimits)(WGPUAdapter adapter, WGPUSupportedLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterGetProperties)(WGPUAdapter adapter, WGPUAdapterProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcAdapterHasFeature)(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterRequestAdapterInfo)(WGPUAdapter adapter, WGPUAdapterRequestAdapterInfoCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterRequestDevice)(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPUAdapterRequestDeviceCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterReference)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcAdapterRelease)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroup
typedef void (*WGPUProcBindGroupSetLabel)(WGPUBindGroup bindGroup, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupReference)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupRelease)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroupLayout
typedef void (*WGPUProcBindGroupLayoutSetLabel)(WGPUBindGroupLayout bindGroupLayout, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupLayoutReference)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBindGroupLayoutRelease)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Buffer
typedef void (*WGPUProcBufferDestroy)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void const * (*WGPUProcBufferGetConstMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBufferMapState (*WGPUProcBufferGetMapState)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void * (*WGPUProcBufferGetMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef uint64_t (*WGPUProcBufferGetSize)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBufferUsageFlags (*WGPUProcBufferGetUsage)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferMapAsync)(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferSetLabel)(WGPUBuffer buffer, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferUnmap)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferReference)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcBufferRelease)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandBuffer
typedef void (*WGPUProcCommandBufferSetLabel)(WGPUCommandBuffer commandBuffer, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandBufferReference)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandBufferRelease)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandEncoder
typedef WGPUComputePassEncoder (*WGPUProcCommandEncoderBeginComputePass)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderPassEncoder (*WGPUProcCommandEncoderBeginRenderPass)(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderClearBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyBufferToBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyBufferToTexture)(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyTextureToBuffer)(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderCopyTextureToTexture)(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUCommandBuffer (*WGPUProcCommandEncoderFinish)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderInsertDebugMarker)(WGPUCommandEncoder commandEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderPopDebugGroup)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderPushDebugGroup)(WGPUCommandEncoder commandEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderResolveQuerySet)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderSetLabel)(WGPUCommandEncoder commandEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderWriteTimestamp)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderReference)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcCommandEncoderRelease)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePassEncoder
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroups)(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroupsIndirect)(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderEnd)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderInsertDebugMarker)(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderPopDebugGroup)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderPushDebugGroup)(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetBindGroup)(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetLabel)(WGPUComputePassEncoder computePassEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderSetPipeline)(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderReference)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePassEncoderRelease)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePipeline
typedef WGPUBindGroupLayout (*WGPUProcComputePipelineGetBindGroupLayout)(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineSetLabel)(WGPUComputePipeline computePipeline, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineReference)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcComputePipelineRelease)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Device
typedef WGPUBindGroup (*WGPUProcDeviceCreateBindGroup)(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBindGroupLayout (*WGPUProcDeviceCreateBindGroupLayout)(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBuffer (*WGPUProcDeviceCreateBuffer)(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUCommandEncoder (*WGPUProcDeviceCreateCommandEncoder)(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUComputePipeline (*WGPUProcDeviceCreateComputePipeline)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceCreateComputePipelineAsync)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUDeviceCreateComputePipelineAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUPipelineLayout (*WGPUProcDeviceCreatePipelineLayout)(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQuerySet (*WGPUProcDeviceCreateQuerySet)(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderBundleEncoder (*WGPUProcDeviceCreateRenderBundleEncoder)(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderPipeline (*WGPUProcDeviceCreateRenderPipeline)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceCreateRenderPipelineAsync)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUDeviceCreateRenderPipelineAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUSampler (*WGPUProcDeviceCreateSampler)(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUShaderModule (*WGPUProcDeviceCreateShaderModule)(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTexture (*WGPUProcDeviceCreateTexture)(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceDestroy)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef size_t (*WGPUProcDeviceEnumerateFeatures)(WGPUDevice device, WGPUFeatureName * features) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcDeviceGetLimits)(WGPUDevice device, WGPUSupportedLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQueue (*WGPUProcDeviceGetQueue)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcDeviceHasFeature)(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDevicePopErrorScope)(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDevicePushErrorScope)(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceSetLabel)(WGPUDevice device, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceSetUncapturedErrorCallback)(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceReference)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcDeviceRelease)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Instance
typedef WGPUSurface (*WGPUProcInstanceCreateSurface)(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUBool (*WGPUProcInstanceHasWGSLLanguageFeature)(WGPUInstance instance, WGPUWGSLFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceProcessEvents)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceRequestAdapter)(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPUInstanceRequestAdapterCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceReference)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcInstanceRelease)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;

// Procs of PipelineLayout
typedef void (*WGPUProcPipelineLayoutSetLabel)(WGPUPipelineLayout pipelineLayout, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcPipelineLayoutReference)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcPipelineLayoutRelease)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of QuerySet
typedef void (*WGPUProcQuerySetDestroy)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcQuerySetGetCount)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUQueryType (*WGPUProcQuerySetGetType)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetSetLabel)(WGPUQuerySet querySet, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetReference)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQuerySetRelease)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Queue
typedef void (*WGPUProcQueueOnSubmittedWorkDone)(WGPUQueue queue, WGPUQueueOnSubmittedWorkDoneCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueSetLabel)(WGPUQueue queue, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueSubmit)(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueWriteBuffer)(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueWriteTexture)(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueReference)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcQueueRelease)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundle
typedef void (*WGPUProcRenderBundleSetLabel)(WGPURenderBundle renderBundle, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleReference)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleRelease)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundleEncoder
typedef void (*WGPUProcRenderBundleEncoderDraw)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndexed)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndexedIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderDrawIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPURenderBundle (*WGPUProcRenderBundleEncoderFinish)(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderInsertDebugMarker)(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderPopDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderPushDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetBindGroup)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetIndexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetLabel)(WGPURenderBundleEncoder renderBundleEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetPipeline)(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderSetVertexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderReference)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderBundleEncoderRelease)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPassEncoder
typedef void (*WGPUProcRenderPassEncoderBeginOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDraw)(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndexed)(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndexedIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderDrawIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderEnd)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderEndOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderExecuteBundles)(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderInsertDebugMarker)(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderPopDebugGroup)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderPushDebugGroup)(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetBindGroup)(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetBlendConstant)(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetIndexBuffer)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetLabel)(WGPURenderPassEncoder renderPassEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetPipeline)(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetScissorRect)(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetStencilReference)(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetVertexBuffer)(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderSetViewport)(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderReference)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPassEncoderRelease)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPipeline
typedef WGPUBindGroupLayout (*WGPUProcRenderPipelineGetBindGroupLayout)(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineSetLabel)(WGPURenderPipeline renderPipeline, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineReference)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcRenderPipelineRelease)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Sampler
typedef void (*WGPUProcSamplerSetLabel)(WGPUSampler sampler, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSamplerReference)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSamplerRelease)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ShaderModule
typedef void (*WGPUProcShaderModuleGetCompilationInfo)(WGPUShaderModule shaderModule, WGPUShaderModuleGetCompilationInfoCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleSetLabel)(WGPUShaderModule shaderModule, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleReference)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcShaderModuleRelease)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Surface
typedef void (*WGPUProcSurfaceConfigure)(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceGetCapabilities)(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceGetCurrentTexture)(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureFormat (*WGPUProcSurfaceGetPreferredFormat)(WGPUSurface surface, WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfacePresent)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceSetLabel)(WGPUSurface surface, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceUnconfigure)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceReference)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcSurfaceRelease)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SurfaceCapabilities
typedef void (*WGPUProcSurfaceCapabilitiesFreeMembers)(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Texture
typedef WGPUTextureView (*WGPUProcTextureCreateView)(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureDestroy)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetDepthOrArrayLayers)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureDimension (*WGPUProcTextureGetDimension)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureFormat (*WGPUProcTextureGetFormat)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetHeight)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetMipLevelCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetSampleCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef WGPUTextureUsageFlags (*WGPUProcTextureGetUsage)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef uint32_t (*WGPUProcTextureGetWidth)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureSetLabel)(WGPUTexture texture, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureReference)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureRelease)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;

// Procs of TextureView
typedef void (*WGPUProcTextureViewSetLabel)(WGPUTextureView textureView, char const * label) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureViewReference)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
typedef void (*WGPUProcTextureViewRelease)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_PROCS)

#if !defined(WGPU_SKIP_DECLARATIONS)
/**
 * \defgroup GlobalFunctions Global Functions
 * \brief Functions that are not specific to an object.
 * 
 * @{
 */
WGPU_EXPORT WGPUInstance wgpuCreateInstance(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUProc wgpuGetProcAddress(WGPUDevice device, char const * procName) WGPU_FUNCTION_ATTRIBUTE;


/** @} */

/**
 * \defgroup Methods
 * \brief Functions that are relative to a specific object.
 * 
 * @{
 */

/**
 * \defgroup AdapterMethods Adapter methods
 * \brief Functions whose first argument has type Adapter.
 * 
 * @{
 */
WGPU_EXPORT size_t wgpuAdapterEnumerateFeatures(WGPUAdapter adapter, WGPUFeatureName * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuAdapterGetLimits(WGPUAdapter adapter, WGPUSupportedLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterGetProperties(WGPUAdapter adapter, WGPUAdapterProperties * properties) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterRequestAdapterInfo(WGPUAdapter adapter, WGPUAdapterRequestAdapterInfoCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPUAdapterRequestDeviceCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterReference(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterRelease(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup BindGroupMethods BindGroup methods
 * \brief Functions whose first argument has type BindGroup.
 * 
 * @{
 */
WGPU_EXPORT void wgpuBindGroupSetLabel(WGPUBindGroup bindGroup, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupReference(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupRelease(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup BindGroupLayoutMethods BindGroupLayout methods
 * \brief Functions whose first argument has type BindGroupLayout.
 * 
 * @{
 */
WGPU_EXPORT void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutReference(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup BufferMethods Buffer methods
 * \brief Functions whose first argument has type Buffer.
 * 
 * @{
 */
WGPU_EXPORT void wgpuBufferDestroy(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void const * wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void * wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint64_t wgpuBufferGetSize(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferUsageFlags wgpuBufferGetUsage(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapModeFlags mode, size_t offset, size_t size, WGPUBufferMapAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferSetLabel(WGPUBuffer buffer, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferUnmap(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferReference(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferRelease(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup CommandBufferMethods CommandBuffer methods
 * \brief Functions whose first argument has type CommandBuffer.
 * 
 * @{
 */
WGPU_EXPORT void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferReference(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup CommandEncoderMethods CommandEncoder methods
 * \brief Functions whose first argument has type CommandEncoder.
 * 
 * @{
 */
WGPU_EXPORT WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyBuffer const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyBuffer const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUImageCopyTexture const * source, WGPUImageCopyTexture const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderReference(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup ComputePassEncoderMethods ComputePassEncoder methods
 * \brief Functions whose first argument has type ComputePassEncoder.
 * 
 * @{
 */
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderReference(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup ComputePipelineMethods ComputePipeline methods
 * \brief Functions whose first argument has type ComputePipeline.
 * 
 * @{
 */
WGPU_EXPORT WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineReference(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup DeviceMethods Device methods
 * \brief Functions whose first argument has type Device.
 * 
 * @{
 */
WGPU_EXPORT WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUDeviceCreateComputePipelineAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUDeviceCreateRenderPipelineAsyncCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceDestroy(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT size_t wgpuDeviceEnumerateFeatures(WGPUDevice device, WGPUFeatureName * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuDeviceGetLimits(WGPUDevice device, WGPUSupportedLimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueue wgpuDeviceGetQueue(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDevicePopErrorScope(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceSetLabel(WGPUDevice device, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceSetUncapturedErrorCallback(WGPUDevice device, WGPUErrorCallback callback, void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceReference(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceRelease(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup InstanceMethods Instance methods
 * \brief Functions whose first argument has type Instance.
 * 
 * @{
 */
WGPU_EXPORT WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance instance, WGPUWGSLFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceProcessEvents(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceRequestAdapter(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPUInstanceRequestAdapterCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceReference(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceRelease(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup PipelineLayoutMethods PipelineLayout methods
 * \brief Functions whose first argument has type PipelineLayout.
 * 
 * @{
 */
WGPU_EXPORT void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutReference(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup QuerySetMethods QuerySet methods
 * \brief Functions whose first argument has type QuerySet.
 * 
 * @{
 */
WGPU_EXPORT void wgpuQuerySetDestroy(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetSetLabel(WGPUQuerySet querySet, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetReference(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetRelease(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup QueueMethods Queue methods
 * \brief Functions whose first argument has type Queue.
 * 
 * @{
 */
WGPU_EXPORT void wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueOnSubmittedWorkDoneCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSetLabel(WGPUQueue queue, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueWriteTexture(WGPUQueue queue, WGPUImageCopyTexture const * destination, void const * data, size_t dataSize, WGPUTextureDataLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueReference(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueRelease(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup RenderBundleMethods RenderBundle methods
 * \brief Functions whose first argument has type RenderBundle.
 * 
 * @{
 */
WGPU_EXPORT void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleReference(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleRelease(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup RenderBundleEncoderMethods RenderBundleEncoder methods
 * \brief Functions whose first argument has type RenderBundleEncoder.
 * 
 * @{
 */
WGPU_EXPORT void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderReference(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup RenderPassEncoderMethods RenderPassEncoder methods
 * \brief Functions whose first argument has type RenderPassEncoder.
 * 
 * @{
 */
WGPU_EXPORT void wgpuRenderPassEncoderBeginOcclusionQuery(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDraw(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexed(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndexedIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderDrawIndirect(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderEnd(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderEndOcclusionQuery(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExecuteBundles(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, char const * markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, char const * groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderReference(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup RenderPipelineMethods RenderPipeline methods
 * \brief Functions whose first argument has type RenderPipeline.
 * 
 * @{
 */
WGPU_EXPORT WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineReference(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup SamplerMethods Sampler methods
 * \brief Functions whose first argument has type Sampler.
 * 
 * @{
 */
WGPU_EXPORT void wgpuSamplerSetLabel(WGPUSampler sampler, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerReference(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerRelease(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup ShaderModuleMethods ShaderModule methods
 * \brief Functions whose first argument has type ShaderModule.
 * 
 * @{
 */
WGPU_EXPORT void wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUShaderModuleGetCompilationInfoCallback callback, WGPU_NULLABLE void * userdata) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleReference(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleRelease(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup SurfaceMethods Surface methods
 * \brief Functions whose first argument has type Surface.
 * 
 * @{
 */
WGPU_EXPORT void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureFormat wgpuSurfaceGetPreferredFormat(WGPUSurface surface, WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfacePresent(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceSetLabel(WGPUSurface surface, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceUnconfigure(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceReference(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceRelease(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup SurfaceCapabilitiesMethods SurfaceCapabilities methods
 * \brief Functions whose first argument has type SurfaceCapabilities.
 * 
 * @{
 */
WGPU_EXPORT void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup TextureMethods Texture methods
 * \brief Functions whose first argument has type Texture.
 * 
 * @{
 */
WGPU_EXPORT WGPUTextureView wgpuTextureCreateView(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureDestroy(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetDepthOrArrayLayers(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureDimension wgpuTextureGetDimension(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureFormat wgpuTextureGetFormat(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetHeight(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetMipLevelCount(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetSampleCount(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTextureUsageFlags wgpuTextureGetUsage(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetWidth(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureSetLabel(WGPUTexture texture, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureReference(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureRelease(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup TextureViewMethods TextureView methods
 * \brief Functions whose first argument has type TextureView.
 * 
 * @{
 */
WGPU_EXPORT void wgpuTextureViewSetLabel(WGPUTextureView textureView, char const * label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewReference(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewRelease(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
/** @} */


/** @} */

#endif  // !defined(WGPU_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBGPU_H_
