/**
 * Copyright 2019-2023 WebGPU-Native developers
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file */

/**
 * \mainpage
 *
 * **Important:** *This documentation is a Work In Progress.*
 *
 * This is the home of WebGPU C API specification. We define here the standard
 * `webgpu.h` header that all implementations should provide.
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

#define _wgpu_COMMA ,
#if defined(__cplusplus)
#  define _wgpu_ZERO_INIT {}
#  if __cplusplus >= 201103L
#    define _wgpu_MAKE_INIT_STRUCT(type, value) (type value)
#  else
#    define _wgpu_MAKE_INIT_STRUCT(type, value) value
#  endif
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#  define _wgpu_ZERO_INIT {0}
#  define _wgpu_MAKE_INIT_STRUCT(type, value) ((type) value)
#else
#  define _wgpu_ZERO_INIT {0}
#  define _wgpu_MAKE_INIT_STRUCT(type, value) value
#endif


/**
 * \defgroup Constants
 * \brief Constants.
 *
 * @{
 */
#define WGPU_ARRAY_LAYER_COUNT_UNDEFINED (UINT32_MAX)
#define WGPU_COPY_STRIDE_UNDEFINED (UINT32_MAX)
#define WGPU_DEPTH_SLICE_UNDEFINED (UINT32_MAX)
#define WGPU_LIMIT_U32_UNDEFINED (UINT32_MAX)
#define WGPU_LIMIT_U64_UNDEFINED (UINT64_MAX)
#define WGPU_MIP_LEVEL_COUNT_UNDEFINED (UINT32_MAX)
#define WGPU_QUERY_SET_INDEX_UNDEFINED (UINT32_MAX)
#define WGPU_WHOLE_MAP_SIZE (SIZE_MAX)
#define WGPU_WHOLE_SIZE (UINT64_MAX)


/** @} */

/**
 * \defgroup UtilityTypes Utility Types
 *
 * @{
 */
typedef uint64_t WGPUFlags;
typedef uint32_t WGPUBool;

/**
 * Nullable value defining a pointer+length view into a UTF-8 encoded string.
 *
 * Values passed into the API may use the special length value @ref WGPU_STRLEN
 * to indicate a null-terminated string.
 * Non-null values passed out of the API (for example as callback arguments)
 * always provide an explicit length and **may or may not be null-terminated**.
 *
 * Some inputs to the API accept null values. Those which do not accept null
 * values "default" to the empty string when null values are passed.
 *
 * Values are encoded as follows:
 * - `{NULL, WGPU_STRLEN}`: the null value.
 * - `{non_null_pointer, WGPU_STRLEN}`: a null-terminated string view.
 * - `{any, 0}`: the empty string.
 * - `{NULL, non_zero_length}`: not allowed (null dereference).
 * - `{non_null_pointer, non_zero_length}`: an explictly-sized string view with
 *   size `non_zero_length` (in bytes).
 *
 * For info on how this is used in various places, see \ref Strings.
 */
typedef struct WGPUStringView {
    char const * WGPU_NULLABLE data;
    size_t length;
} WGPUStringView;

/**
 * Sentinel value used in @ref WGPUStringView to indicate that the pointer
 * is to a null-terminated string, rather than an explicitly-sized string.
 */
#define WGPU_STRLEN SIZE_MAX

#define WGPU_STRING_VIEW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStringView, { \
    /*.data=*/NULL _wgpu_COMMA \
    /*.length=*/WGPU_STRLEN _wgpu_COMMA \
})


/** @} */

/**
 * \defgroup Objects
 * \brief Opaque, non-dispatchable handles to WebGPU objects.
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
/**
 * An object used to continuously present image data to the user, see @ref Surfaces for more details.
 */
typedef struct WGPUSurfaceImpl* WGPUSurface WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureImpl* WGPUTexture WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUTextureViewImpl* WGPUTextureView WGPU_OBJECT_ATTRIBUTE;


/** @} */
// Structure forward declarations
struct WGPUAdapterInfo;
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
struct WGPUFuture;
struct WGPUInstanceCapabilities;
struct WGPULimits;
struct WGPUMultisampleState;
struct WGPUOrigin3D;
struct WGPUPipelineLayoutDescriptor;
struct WGPUPrimitiveState;
struct WGPUQuerySetDescriptor;
struct WGPUQueueDescriptor;
struct WGPURenderBundleDescriptor;
struct WGPURenderBundleEncoderDescriptor;
struct WGPURenderPassDepthStencilAttachment;
struct WGPURenderPassMaxDrawCount;
struct WGPURenderPassTimestampWrites;
struct WGPURequestAdapterOptions;
struct WGPUSamplerBindingLayout;
struct WGPUSamplerDescriptor;
struct WGPUShaderModuleDescriptor;
struct WGPUShaderSourceSPIRV;
struct WGPUShaderSourceWGSL;
struct WGPUStencilFaceState;
struct WGPUStorageTextureBindingLayout;
struct WGPUSupportedFeatures;
struct WGPUSupportedWGSLLanguageFeatures;
struct WGPUSurfaceCapabilities;
struct WGPUSurfaceConfiguration;
struct WGPUSurfaceDescriptor;
struct WGPUSurfaceSourceAndroidNativeWindow;
struct WGPUSurfaceSourceMetalLayer;
struct WGPUSurfaceSourceWaylandSurface;
struct WGPUSurfaceSourceWindowsHWND;
struct WGPUSurfaceSourceXCBWindow;
struct WGPUSurfaceSourceXlibWindow;
struct WGPUSurfaceTexture;
struct WGPUTexelCopyBufferLayout;
struct WGPUTextureBindingLayout;
struct WGPUTextureViewDescriptor;
struct WGPUVertexAttribute;
struct WGPUBindGroupDescriptor;
struct WGPUBindGroupLayoutEntry;
struct WGPUBlendState;
struct WGPUCompilationInfo;
struct WGPUComputePassDescriptor;
struct WGPUComputeStage;
struct WGPUDepthStencilState;
struct WGPUDeviceDescriptor;
struct WGPUFutureWaitInfo;
struct WGPUInstanceDescriptor;
struct WGPURenderPassColorAttachment;
struct WGPUTexelCopyBufferInfo;
struct WGPUTexelCopyTextureInfo;
struct WGPUTextureDescriptor;
struct WGPUVertexBufferLayout;
struct WGPUBindGroupLayoutDescriptor;
struct WGPUColorTargetState;
struct WGPUComputePipelineDescriptor;
struct WGPURenderPassDescriptor;
struct WGPUVertexState;
struct WGPUFragmentState;
struct WGPURenderPipelineDescriptor;

// Callback info structure forward declarations
struct WGPUBufferMapCallbackInfo;
struct WGPUCompilationInfoCallbackInfo;
struct WGPUCreateComputePipelineAsyncCallbackInfo;
struct WGPUCreateRenderPipelineAsyncCallbackInfo;
struct WGPUDeviceLostCallbackInfo;
struct WGPUPopErrorScopeCallbackInfo;
struct WGPUQueueWorkDoneCallbackInfo;
struct WGPURequestAdapterCallbackInfo;
struct WGPURequestDeviceCallbackInfo;
struct WGPUUncapturedErrorCallbackInfo;


/**
 * \defgroup Enumerations
 * \brief Enums.
 *
 * @{
 */
typedef enum WGPUAdapterType {
    WGPUAdapterType_DiscreteGPU = 0x00000001,
    WGPUAdapterType_IntegratedGPU = 0x00000002,
    WGPUAdapterType_CPU = 0x00000003,
    WGPUAdapterType_Unknown = 0x00000004,
    WGPUAdapterType_Force32 = 0x7FFFFFFF
} WGPUAdapterType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUAddressMode {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUAddressMode_Undefined = 0x00000000,
    WGPUAddressMode_ClampToEdge = 0x00000001,
    WGPUAddressMode_Repeat = 0x00000002,
    WGPUAddressMode_MirrorRepeat = 0x00000003,
    WGPUAddressMode_Force32 = 0x7FFFFFFF
} WGPUAddressMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBackendType {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUBackendType_Undefined = 0x00000000,
    WGPUBackendType_Null = 0x00000001,
    WGPUBackendType_WebGPU = 0x00000002,
    WGPUBackendType_D3D11 = 0x00000003,
    WGPUBackendType_D3D12 = 0x00000004,
    WGPUBackendType_Metal = 0x00000005,
    WGPUBackendType_Vulkan = 0x00000006,
    WGPUBackendType_OpenGL = 0x00000007,
    WGPUBackendType_OpenGLES = 0x00000008,
    WGPUBackendType_Force32 = 0x7FFFFFFF
} WGPUBackendType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendFactor {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUBlendFactor_Undefined = 0x00000000,
    WGPUBlendFactor_Zero = 0x00000001,
    WGPUBlendFactor_One = 0x00000002,
    WGPUBlendFactor_Src = 0x00000003,
    WGPUBlendFactor_OneMinusSrc = 0x00000004,
    WGPUBlendFactor_SrcAlpha = 0x00000005,
    WGPUBlendFactor_OneMinusSrcAlpha = 0x00000006,
    WGPUBlendFactor_Dst = 0x00000007,
    WGPUBlendFactor_OneMinusDst = 0x00000008,
    WGPUBlendFactor_DstAlpha = 0x00000009,
    WGPUBlendFactor_OneMinusDstAlpha = 0x0000000A,
    WGPUBlendFactor_SrcAlphaSaturated = 0x0000000B,
    WGPUBlendFactor_Constant = 0x0000000C,
    WGPUBlendFactor_OneMinusConstant = 0x0000000D,
    WGPUBlendFactor_Src1 = 0x0000000E,
    WGPUBlendFactor_OneMinusSrc1 = 0x0000000F,
    WGPUBlendFactor_Src1Alpha = 0x00000010,
    WGPUBlendFactor_OneMinusSrc1Alpha = 0x00000011,
    WGPUBlendFactor_Force32 = 0x7FFFFFFF
} WGPUBlendFactor WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBlendOperation {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUBlendOperation_Undefined = 0x00000000,
    WGPUBlendOperation_Add = 0x00000001,
    WGPUBlendOperation_Subtract = 0x00000002,
    WGPUBlendOperation_ReverseSubtract = 0x00000003,
    WGPUBlendOperation_Min = 0x00000004,
    WGPUBlendOperation_Max = 0x00000005,
    WGPUBlendOperation_Force32 = 0x7FFFFFFF
} WGPUBlendOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferBindingType {
    /**
     * `0x00000000`.
     * Indicates that this @ref WGPUBufferBindingLayout member of
     * its parent @ref WGPUBindGroupLayoutEntry is not used.
     * (See also @ref SentinelValues.)
     */
    WGPUBufferBindingType_BindingNotUsed = 0x00000000,
    /**
     * `0x00000001`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUBufferBindingType_Undefined = 0x00000001,
    WGPUBufferBindingType_Uniform = 0x00000002,
    WGPUBufferBindingType_Storage = 0x00000003,
    WGPUBufferBindingType_ReadOnlyStorage = 0x00000004,
    WGPUBufferBindingType_Force32 = 0x7FFFFFFF
} WGPUBufferBindingType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUBufferMapState {
    WGPUBufferMapState_Unmapped = 0x00000001,
    WGPUBufferMapState_Pending = 0x00000002,
    WGPUBufferMapState_Mapped = 0x00000003,
    WGPUBufferMapState_Force32 = 0x7FFFFFFF
} WGPUBufferMapState WGPU_ENUM_ATTRIBUTE;

/**
 * The callback mode controls how a callback for an asynchronous operation may be fired. See @ref Asynchronous-Operations for how these are used.
 */
typedef enum WGPUCallbackMode {
    /**
     * `0x00000001`.
     * Callbacks created with `WGPUCallbackMode_WaitAnyOnly`:
     * - fire when the asynchronous operation's future is passed to a call to `::wgpuInstanceWaitAny`
     *   AND the operation has already completed or it completes inside the call to `::wgpuInstanceWaitAny`.
     */
    WGPUCallbackMode_WaitAnyOnly = 0x00000001,
    /**
     * `0x00000002`.
     * Callbacks created with `WGPUCallbackMode_AllowProcessEvents`:
     * - fire for the same reasons as callbacks created with `WGPUCallbackMode_WaitAnyOnly`
     * - fire inside a call to `::wgpuInstanceProcessEvents` if the asynchronous operation is complete.
     */
    WGPUCallbackMode_AllowProcessEvents = 0x00000002,
    /**
     * `0x00000003`.
     * Callbacks created with `WGPUCallbackMode_AllowSpontaneous`:
     * - fire for the same reasons as callbacks created with `WGPUCallbackMode_AllowProcessEvents`
     * - **may** fire spontaneously on an arbitrary or application thread, when the WebGPU implementations discovers that the asynchronous operation is complete.
     *
     *   Implementations _should_ fire spontaneous callbacks as soon as possible.
     *
     * @note Because spontaneous callbacks may fire at an arbitrary time on an arbitrary thread, applications should take extra care when acquiring locks or mutating state inside the callback. It undefined behavior to re-entrantly call into the webgpu.h API if the callback fires while inside the callstack of another webgpu.h function that is not `wgpuInstanceWaitAny` or `wgpuInstanceProcessEvents`.
     */
    WGPUCallbackMode_AllowSpontaneous = 0x00000003,
    WGPUCallbackMode_Force32 = 0x7FFFFFFF
} WGPUCallbackMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompareFunction {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUCompareFunction_Undefined = 0x00000000,
    WGPUCompareFunction_Never = 0x00000001,
    WGPUCompareFunction_Less = 0x00000002,
    WGPUCompareFunction_Equal = 0x00000003,
    WGPUCompareFunction_LessEqual = 0x00000004,
    WGPUCompareFunction_Greater = 0x00000005,
    WGPUCompareFunction_NotEqual = 0x00000006,
    WGPUCompareFunction_GreaterEqual = 0x00000007,
    WGPUCompareFunction_Always = 0x00000008,
    WGPUCompareFunction_Force32 = 0x7FFFFFFF
} WGPUCompareFunction WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationInfoRequestStatus {
    WGPUCompilationInfoRequestStatus_Success = 0x00000001,
    WGPUCompilationInfoRequestStatus_InstanceDropped = 0x00000002,
    WGPUCompilationInfoRequestStatus_Error = 0x00000003,
    WGPUCompilationInfoRequestStatus_Force32 = 0x7FFFFFFF
} WGPUCompilationInfoRequestStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCompilationMessageType {
    WGPUCompilationMessageType_Error = 0x00000001,
    WGPUCompilationMessageType_Warning = 0x00000002,
    WGPUCompilationMessageType_Info = 0x00000003,
    WGPUCompilationMessageType_Force32 = 0x7FFFFFFF
} WGPUCompilationMessageType WGPU_ENUM_ATTRIBUTE;

/**
 * Describes how frames are composited with other contents on the screen when `::wgpuSurfacePresent` is called.
 */
typedef enum WGPUCompositeAlphaMode {
    /**
     * `0x00000000`.
     * Lets the WebGPU implementation choose the best mode (supported, and with the best performance) between @ref WGPUCompositeAlphaMode_Opaque or @ref WGPUCompositeAlphaMode_Inherit.
     */
    WGPUCompositeAlphaMode_Auto = 0x00000000,
    /**
     * `0x00000001`.
     * The alpha component of the image is ignored and teated as if it is always 1.0.
     */
    WGPUCompositeAlphaMode_Opaque = 0x00000001,
    /**
     * `0x00000002`.
     * The alpha component is respected and non-alpha components are assumed to be already multiplied with the alpha component. For example, (0.5, 0, 0, 0.5) is semi-transparent bright red.
     */
    WGPUCompositeAlphaMode_Premultiplied = 0x00000002,
    /**
     * `0x00000003`.
     * The alpha component is respected and non-alpha components are assumed to NOT be already multiplied with the alpha component. For example, (1.0, 0, 0, 0.5) is semi-transparent bright red.
     */
    WGPUCompositeAlphaMode_Unpremultiplied = 0x00000003,
    /**
     * `0x00000004`.
     * The handling of the alpha component is unknown to WebGPU and should be handled by the application using system-specific APIs. This mode may be unavailable (for example on Wasm).
     */
    WGPUCompositeAlphaMode_Inherit = 0x00000004,
    WGPUCompositeAlphaMode_Force32 = 0x7FFFFFFF
} WGPUCompositeAlphaMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCreatePipelineAsyncStatus {
    WGPUCreatePipelineAsyncStatus_Success = 0x00000001,
    WGPUCreatePipelineAsyncStatus_InstanceDropped = 0x00000002,
    WGPUCreatePipelineAsyncStatus_ValidationError = 0x00000003,
    WGPUCreatePipelineAsyncStatus_InternalError = 0x00000004,
    WGPUCreatePipelineAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUCreatePipelineAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUCullMode {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUCullMode_Undefined = 0x00000000,
    WGPUCullMode_None = 0x00000001,
    WGPUCullMode_Front = 0x00000002,
    WGPUCullMode_Back = 0x00000003,
    WGPUCullMode_Force32 = 0x7FFFFFFF
} WGPUCullMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUDeviceLostReason {
    WGPUDeviceLostReason_Unknown = 0x00000001,
    WGPUDeviceLostReason_Destroyed = 0x00000002,
    WGPUDeviceLostReason_InstanceDropped = 0x00000003,
    WGPUDeviceLostReason_FailedCreation = 0x00000004,
    WGPUDeviceLostReason_Force32 = 0x7FFFFFFF
} WGPUDeviceLostReason WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorFilter {
    WGPUErrorFilter_Validation = 0x00000001,
    WGPUErrorFilter_OutOfMemory = 0x00000002,
    WGPUErrorFilter_Internal = 0x00000003,
    WGPUErrorFilter_Force32 = 0x7FFFFFFF
} WGPUErrorFilter WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUErrorType {
    WGPUErrorType_NoError = 0x00000001,
    WGPUErrorType_Validation = 0x00000002,
    WGPUErrorType_OutOfMemory = 0x00000003,
    WGPUErrorType_Internal = 0x00000004,
    WGPUErrorType_Unknown = 0x00000005,
    WGPUErrorType_Force32 = 0x7FFFFFFF
} WGPUErrorType WGPU_ENUM_ATTRIBUTE;

/**
 * See @ref WGPURequestAdapterOptions::featureLevel.
 */
typedef enum WGPUFeatureLevel {
    /**
     * `0x00000001`.
     * "Compatibility" profile which can be supported on OpenGL ES 3.1 and D3D11.
     */
    WGPUFeatureLevel_Compatibility = 0x00000001,
    /**
     * `0x00000002`.
     * "Core" profile which can be supported on Vulkan/Metal/D3D12 (at least).
     */
    WGPUFeatureLevel_Core = 0x00000002,
    WGPUFeatureLevel_Force32 = 0x7FFFFFFF
} WGPUFeatureLevel WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFeatureName {
    WGPUFeatureName_Undefined = 0x00000000,
    WGPUFeatureName_DepthClipControl = 0x00000001,
    WGPUFeatureName_Depth32FloatStencil8 = 0x00000002,
    WGPUFeatureName_TimestampQuery = 0x00000003,
    WGPUFeatureName_TextureCompressionBC = 0x00000004,
    WGPUFeatureName_TextureCompressionBCSliced3D = 0x00000005,
    WGPUFeatureName_TextureCompressionETC2 = 0x00000006,
    WGPUFeatureName_TextureCompressionASTC = 0x00000007,
    WGPUFeatureName_TextureCompressionASTCSliced3D = 0x00000008,
    WGPUFeatureName_IndirectFirstInstance = 0x00000009,
    WGPUFeatureName_ShaderF16 = 0x0000000A,
    WGPUFeatureName_RG11B10UfloatRenderable = 0x0000000B,
    WGPUFeatureName_BGRA8UnormStorage = 0x0000000C,
    WGPUFeatureName_Float32Filterable = 0x0000000D,
    WGPUFeatureName_Float32Blendable = 0x0000000E,
    WGPUFeatureName_ClipDistances = 0x0000000F,
    WGPUFeatureName_DualSourceBlending = 0x00000010,
    WGPUFeatureName_Force32 = 0x7FFFFFFF
} WGPUFeatureName WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFilterMode {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUFilterMode_Undefined = 0x00000000,
    WGPUFilterMode_Nearest = 0x00000001,
    WGPUFilterMode_Linear = 0x00000002,
    WGPUFilterMode_Force32 = 0x7FFFFFFF
} WGPUFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUFrontFace {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUFrontFace_Undefined = 0x00000000,
    WGPUFrontFace_CCW = 0x00000001,
    WGPUFrontFace_CW = 0x00000002,
    WGPUFrontFace_Force32 = 0x7FFFFFFF
} WGPUFrontFace WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUIndexFormat {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUIndexFormat_Undefined = 0x00000000,
    WGPUIndexFormat_Uint16 = 0x00000001,
    WGPUIndexFormat_Uint32 = 0x00000002,
    WGPUIndexFormat_Force32 = 0x7FFFFFFF
} WGPUIndexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPULoadOp {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPULoadOp_Undefined = 0x00000000,
    WGPULoadOp_Load = 0x00000001,
    WGPULoadOp_Clear = 0x00000002,
    WGPULoadOp_Force32 = 0x7FFFFFFF
} WGPULoadOp WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMapAsyncStatus {
    WGPUMapAsyncStatus_Success = 0x00000001,
    WGPUMapAsyncStatus_InstanceDropped = 0x00000002,
    WGPUMapAsyncStatus_Error = 0x00000003,
    WGPUMapAsyncStatus_Aborted = 0x00000004,
    WGPUMapAsyncStatus_Force32 = 0x7FFFFFFF
} WGPUMapAsyncStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUMipmapFilterMode {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUMipmapFilterMode_Undefined = 0x00000000,
    WGPUMipmapFilterMode_Nearest = 0x00000001,
    WGPUMipmapFilterMode_Linear = 0x00000002,
    WGPUMipmapFilterMode_Force32 = 0x7FFFFFFF
} WGPUMipmapFilterMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUOptionalBool {
    WGPUOptionalBool_False = 0x00000000,
    WGPUOptionalBool_True = 0x00000001,
    WGPUOptionalBool_Undefined = 0x00000002,
    WGPUOptionalBool_Force32 = 0x7FFFFFFF
} WGPUOptionalBool WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPopErrorScopeStatus {
    /**
     * `0x00000001`.
     * The error scope stack was successfully popped and a result was reported.
     */
    WGPUPopErrorScopeStatus_Success = 0x00000001,
    WGPUPopErrorScopeStatus_InstanceDropped = 0x00000002,
    /**
     * `0x00000003`.
     * The error scope stack could not be popped, because it was empty.
     */
    WGPUPopErrorScopeStatus_EmptyStack = 0x00000003,
    WGPUPopErrorScopeStatus_Force32 = 0x7FFFFFFF
} WGPUPopErrorScopeStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPowerPreference {
    /**
     * `0x00000000`.
     * No preference. (See also @ref SentinelValues.)
     */
    WGPUPowerPreference_Undefined = 0x00000000,
    WGPUPowerPreference_LowPower = 0x00000001,
    WGPUPowerPreference_HighPerformance = 0x00000002,
    WGPUPowerPreference_Force32 = 0x7FFFFFFF
} WGPUPowerPreference WGPU_ENUM_ATTRIBUTE;

/**
 * Describes when and in which order frames are presented on the screen when `::wgpuSurfacePresent` is called.
 */
typedef enum WGPUPresentMode {
    /**
     * `0x00000000`.
     * Present mode is not specified. Use the default.
     */
    WGPUPresentMode_Undefined = 0x00000000,
    /**
     * `0x00000001`.
     * The presentation of the image to the user waits for the next vertical blanking period to update in a first-in, first-out manner.
     * Tearing cannot be observed and frame-loop will be limited to the display's refresh rate.
     * This is the only mode that's always available.
     */
    WGPUPresentMode_Fifo = 0x00000001,
    /**
     * `0x00000002`.
     * The presentation of the image to the user tries to wait for the next vertical blanking period but may decide to not wait if a frame is presented late.
     * Tearing can sometimes be observed but late-frame don't produce a full-frame stutter in the presentation.
     * This is still a first-in, first-out mechanism so a frame-loop will be limited to the display's refresh rate.
     */
    WGPUPresentMode_FifoRelaxed = 0x00000002,
    /**
     * `0x00000003`.
     * The presentation of the image to the user is updated immediately without waiting for a vertical blank.
     * Tearing can be observed but latency is minimized.
     */
    WGPUPresentMode_Immediate = 0x00000003,
    /**
     * `0x00000004`.
     * The presentation of the image to the user waits for the next vertical blanking period to update to the latest provided image.
     * Tearing cannot be observed and a frame-loop is not limited to the display's refresh rate.
     */
    WGPUPresentMode_Mailbox = 0x00000004,
    WGPUPresentMode_Force32 = 0x7FFFFFFF
} WGPUPresentMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPrimitiveTopology {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUPrimitiveTopology_Undefined = 0x00000000,
    WGPUPrimitiveTopology_PointList = 0x00000001,
    WGPUPrimitiveTopology_LineList = 0x00000002,
    WGPUPrimitiveTopology_LineStrip = 0x00000003,
    WGPUPrimitiveTopology_TriangleList = 0x00000004,
    WGPUPrimitiveTopology_TriangleStrip = 0x00000005,
    WGPUPrimitiveTopology_Force32 = 0x7FFFFFFF
} WGPUPrimitiveTopology WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueryType {
    WGPUQueryType_Occlusion = 0x00000001,
    WGPUQueryType_Timestamp = 0x00000002,
    WGPUQueryType_Force32 = 0x7FFFFFFF
} WGPUQueryType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueueWorkDoneStatus {
    WGPUQueueWorkDoneStatus_Success = 0x00000001,
    WGPUQueueWorkDoneStatus_InstanceDropped = 0x00000002,
    WGPUQueueWorkDoneStatus_Error = 0x00000003,
    WGPUQueueWorkDoneStatus_Force32 = 0x7FFFFFFF
} WGPUQueueWorkDoneStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestAdapterStatus {
    WGPURequestAdapterStatus_Success = 0x00000001,
    WGPURequestAdapterStatus_InstanceDropped = 0x00000002,
    WGPURequestAdapterStatus_Unavailable = 0x00000003,
    WGPURequestAdapterStatus_Error = 0x00000004,
    WGPURequestAdapterStatus_Force32 = 0x7FFFFFFF
} WGPURequestAdapterStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPURequestDeviceStatus {
    WGPURequestDeviceStatus_Success = 0x00000001,
    WGPURequestDeviceStatus_InstanceDropped = 0x00000002,
    WGPURequestDeviceStatus_Error = 0x00000003,
    WGPURequestDeviceStatus_Force32 = 0x7FFFFFFF
} WGPURequestDeviceStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSType {
    WGPUSType_ShaderSourceSPIRV = 0x00000001,
    WGPUSType_ShaderSourceWGSL = 0x00000002,
    WGPUSType_RenderPassMaxDrawCount = 0x00000003,
    WGPUSType_SurfaceSourceMetalLayer = 0x00000004,
    WGPUSType_SurfaceSourceWindowsHWND = 0x00000005,
    WGPUSType_SurfaceSourceXlibWindow = 0x00000006,
    WGPUSType_SurfaceSourceWaylandSurface = 0x00000007,
    WGPUSType_SurfaceSourceAndroidNativeWindow = 0x00000008,
    WGPUSType_SurfaceSourceXCBWindow = 0x00000009,
    WGPUSType_Force32 = 0x7FFFFFFF
} WGPUSType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUSamplerBindingType {
    /**
     * `0x00000000`.
     * Indicates that this @ref WGPUSamplerBindingLayout member of
     * its parent @ref WGPUBindGroupLayoutEntry is not used.
     * (See also @ref SentinelValues.)
     */
    WGPUSamplerBindingType_BindingNotUsed = 0x00000000,
    /**
     * `0x00000001`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUSamplerBindingType_Undefined = 0x00000001,
    WGPUSamplerBindingType_Filtering = 0x00000002,
    WGPUSamplerBindingType_NonFiltering = 0x00000003,
    WGPUSamplerBindingType_Comparison = 0x00000004,
    WGPUSamplerBindingType_Force32 = 0x7FFFFFFF
} WGPUSamplerBindingType WGPU_ENUM_ATTRIBUTE;

/**
 * Status code returned (synchronously) from many operations. Generally
 * indicates an invalid input like an unknown enum value or @ref OutStructChainError.
 * Read the function's documentation for specific error conditions.
 */
typedef enum WGPUStatus {
    WGPUStatus_Success = 0x00000001,
    WGPUStatus_Error = 0x00000002,
    WGPUStatus_Force32 = 0x7FFFFFFF
} WGPUStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStencilOperation {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUStencilOperation_Undefined = 0x00000000,
    WGPUStencilOperation_Keep = 0x00000001,
    WGPUStencilOperation_Zero = 0x00000002,
    WGPUStencilOperation_Replace = 0x00000003,
    WGPUStencilOperation_Invert = 0x00000004,
    WGPUStencilOperation_IncrementClamp = 0x00000005,
    WGPUStencilOperation_DecrementClamp = 0x00000006,
    WGPUStencilOperation_IncrementWrap = 0x00000007,
    WGPUStencilOperation_DecrementWrap = 0x00000008,
    WGPUStencilOperation_Force32 = 0x7FFFFFFF
} WGPUStencilOperation WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStorageTextureAccess {
    /**
     * `0x00000000`.
     * Indicates that this @ref WGPUStorageTextureBindingLayout member of
     * its parent @ref WGPUBindGroupLayoutEntry is not used.
     * (See also @ref SentinelValues.)
     */
    WGPUStorageTextureAccess_BindingNotUsed = 0x00000000,
    /**
     * `0x00000001`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUStorageTextureAccess_Undefined = 0x00000001,
    WGPUStorageTextureAccess_WriteOnly = 0x00000002,
    WGPUStorageTextureAccess_ReadOnly = 0x00000003,
    WGPUStorageTextureAccess_ReadWrite = 0x00000004,
    WGPUStorageTextureAccess_Force32 = 0x7FFFFFFF
} WGPUStorageTextureAccess WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUStoreOp {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUStoreOp_Undefined = 0x00000000,
    WGPUStoreOp_Store = 0x00000001,
    WGPUStoreOp_Discard = 0x00000002,
    WGPUStoreOp_Force32 = 0x7FFFFFFF
} WGPUStoreOp WGPU_ENUM_ATTRIBUTE;

/**
 * The status enum for `::wgpuSurfaceGetCurrentTexture`.
 */
typedef enum WGPUSurfaceGetCurrentTextureStatus {
    /**
     * `0x00000001`.
     * Yay! Everything is good and we can render this frame.
     */
    WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal = 0x00000001,
    /**
     * `0x00000002`.
     * Still OK - the surface can present the frame, but in a suboptimal way. The surface may need reconfiguration.
     */
    WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal = 0x00000002,
    /**
     * `0x00000003`.
     * Some operation timed out while trying to acquire the frame.
     */
    WGPUSurfaceGetCurrentTextureStatus_Timeout = 0x00000003,
    /**
     * `0x00000004`.
     * The surface is too different to be used, compared to when it was originally created.
     */
    WGPUSurfaceGetCurrentTextureStatus_Outdated = 0x00000004,
    /**
     * `0x00000005`.
     * The connection to whatever owns the surface was lost.
     */
    WGPUSurfaceGetCurrentTextureStatus_Lost = 0x00000005,
    /**
     * `0x00000006`.
     * The system ran out of memory.
     */
    WGPUSurfaceGetCurrentTextureStatus_OutOfMemory = 0x00000006,
    /**
     * `0x00000007`.
     * The surface is not configured, or there was an @ref OutStructChainError.
     */
    WGPUSurfaceGetCurrentTextureStatus_Error = 0x00000007,
    WGPUSurfaceGetCurrentTextureStatus_Force32 = 0x7FFFFFFF
} WGPUSurfaceGetCurrentTextureStatus WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureAspect {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUTextureAspect_Undefined = 0x00000000,
    WGPUTextureAspect_All = 0x00000001,
    WGPUTextureAspect_StencilOnly = 0x00000002,
    WGPUTextureAspect_DepthOnly = 0x00000003,
    WGPUTextureAspect_Force32 = 0x7FFFFFFF
} WGPUTextureAspect WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureDimension {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUTextureDimension_Undefined = 0x00000000,
    WGPUTextureDimension_1D = 0x00000001,
    WGPUTextureDimension_2D = 0x00000002,
    WGPUTextureDimension_3D = 0x00000003,
    WGPUTextureDimension_Force32 = 0x7FFFFFFF
} WGPUTextureDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureFormat {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUTextureFormat_Undefined = 0x00000000,
    WGPUTextureFormat_R8Unorm = 0x00000001,
    WGPUTextureFormat_R8Snorm = 0x00000002,
    WGPUTextureFormat_R8Uint = 0x00000003,
    WGPUTextureFormat_R8Sint = 0x00000004,
    WGPUTextureFormat_R16Uint = 0x00000005,
    WGPUTextureFormat_R16Sint = 0x00000006,
    WGPUTextureFormat_R16Float = 0x00000007,
    WGPUTextureFormat_RG8Unorm = 0x00000008,
    WGPUTextureFormat_RG8Snorm = 0x00000009,
    WGPUTextureFormat_RG8Uint = 0x0000000A,
    WGPUTextureFormat_RG8Sint = 0x0000000B,
    WGPUTextureFormat_R32Float = 0x0000000C,
    WGPUTextureFormat_R32Uint = 0x0000000D,
    WGPUTextureFormat_R32Sint = 0x0000000E,
    WGPUTextureFormat_RG16Uint = 0x0000000F,
    WGPUTextureFormat_RG16Sint = 0x00000010,
    WGPUTextureFormat_RG16Float = 0x00000011,
    WGPUTextureFormat_RGBA8Unorm = 0x00000012,
    WGPUTextureFormat_RGBA8UnormSrgb = 0x00000013,
    WGPUTextureFormat_RGBA8Snorm = 0x00000014,
    WGPUTextureFormat_RGBA8Uint = 0x00000015,
    WGPUTextureFormat_RGBA8Sint = 0x00000016,
    WGPUTextureFormat_BGRA8Unorm = 0x00000017,
    WGPUTextureFormat_BGRA8UnormSrgb = 0x00000018,
    WGPUTextureFormat_RGB10A2Uint = 0x00000019,
    WGPUTextureFormat_RGB10A2Unorm = 0x0000001A,
    WGPUTextureFormat_RG11B10Ufloat = 0x0000001B,
    WGPUTextureFormat_RGB9E5Ufloat = 0x0000001C,
    WGPUTextureFormat_RG32Float = 0x0000001D,
    WGPUTextureFormat_RG32Uint = 0x0000001E,
    WGPUTextureFormat_RG32Sint = 0x0000001F,
    WGPUTextureFormat_RGBA16Uint = 0x00000020,
    WGPUTextureFormat_RGBA16Sint = 0x00000021,
    WGPUTextureFormat_RGBA16Float = 0x00000022,
    WGPUTextureFormat_RGBA32Float = 0x00000023,
    WGPUTextureFormat_RGBA32Uint = 0x00000024,
    WGPUTextureFormat_RGBA32Sint = 0x00000025,
    WGPUTextureFormat_Stencil8 = 0x00000026,
    WGPUTextureFormat_Depth16Unorm = 0x00000027,
    WGPUTextureFormat_Depth24Plus = 0x00000028,
    WGPUTextureFormat_Depth24PlusStencil8 = 0x00000029,
    WGPUTextureFormat_Depth32Float = 0x0000002A,
    WGPUTextureFormat_Depth32FloatStencil8 = 0x0000002B,
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
    WGPUTextureFormat_BC6HRGBFloat = 0x00000037,
    WGPUTextureFormat_BC7RGBAUnorm = 0x00000038,
    WGPUTextureFormat_BC7RGBAUnormSrgb = 0x00000039,
    WGPUTextureFormat_ETC2RGB8Unorm = 0x0000003A,
    WGPUTextureFormat_ETC2RGB8UnormSrgb = 0x0000003B,
    WGPUTextureFormat_ETC2RGB8A1Unorm = 0x0000003C,
    WGPUTextureFormat_ETC2RGB8A1UnormSrgb = 0x0000003D,
    WGPUTextureFormat_ETC2RGBA8Unorm = 0x0000003E,
    WGPUTextureFormat_ETC2RGBA8UnormSrgb = 0x0000003F,
    WGPUTextureFormat_EACR11Unorm = 0x00000040,
    WGPUTextureFormat_EACR11Snorm = 0x00000041,
    WGPUTextureFormat_EACRG11Unorm = 0x00000042,
    WGPUTextureFormat_EACRG11Snorm = 0x00000043,
    WGPUTextureFormat_ASTC4x4Unorm = 0x00000044,
    WGPUTextureFormat_ASTC4x4UnormSrgb = 0x00000045,
    WGPUTextureFormat_ASTC5x4Unorm = 0x00000046,
    WGPUTextureFormat_ASTC5x4UnormSrgb = 0x00000047,
    WGPUTextureFormat_ASTC5x5Unorm = 0x00000048,
    WGPUTextureFormat_ASTC5x5UnormSrgb = 0x00000049,
    WGPUTextureFormat_ASTC6x5Unorm = 0x0000004A,
    WGPUTextureFormat_ASTC6x5UnormSrgb = 0x0000004B,
    WGPUTextureFormat_ASTC6x6Unorm = 0x0000004C,
    WGPUTextureFormat_ASTC6x6UnormSrgb = 0x0000004D,
    WGPUTextureFormat_ASTC8x5Unorm = 0x0000004E,
    WGPUTextureFormat_ASTC8x5UnormSrgb = 0x0000004F,
    WGPUTextureFormat_ASTC8x6Unorm = 0x00000050,
    WGPUTextureFormat_ASTC8x6UnormSrgb = 0x00000051,
    WGPUTextureFormat_ASTC8x8Unorm = 0x00000052,
    WGPUTextureFormat_ASTC8x8UnormSrgb = 0x00000053,
    WGPUTextureFormat_ASTC10x5Unorm = 0x00000054,
    WGPUTextureFormat_ASTC10x5UnormSrgb = 0x00000055,
    WGPUTextureFormat_ASTC10x6Unorm = 0x00000056,
    WGPUTextureFormat_ASTC10x6UnormSrgb = 0x00000057,
    WGPUTextureFormat_ASTC10x8Unorm = 0x00000058,
    WGPUTextureFormat_ASTC10x8UnormSrgb = 0x00000059,
    WGPUTextureFormat_ASTC10x10Unorm = 0x0000005A,
    WGPUTextureFormat_ASTC10x10UnormSrgb = 0x0000005B,
    WGPUTextureFormat_ASTC12x10Unorm = 0x0000005C,
    WGPUTextureFormat_ASTC12x10UnormSrgb = 0x0000005D,
    WGPUTextureFormat_ASTC12x12Unorm = 0x0000005E,
    WGPUTextureFormat_ASTC12x12UnormSrgb = 0x0000005F,
    WGPUTextureFormat_Force32 = 0x7FFFFFFF
} WGPUTextureFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureSampleType {
    /**
     * `0x00000000`.
     * Indicates that this @ref WGPUTextureBindingLayout member of
     * its parent @ref WGPUBindGroupLayoutEntry is not used.
     * (See also @ref SentinelValues.)
     */
    WGPUTextureSampleType_BindingNotUsed = 0x00000000,
    /**
     * `0x00000001`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUTextureSampleType_Undefined = 0x00000001,
    WGPUTextureSampleType_Float = 0x00000002,
    WGPUTextureSampleType_UnfilterableFloat = 0x00000003,
    WGPUTextureSampleType_Depth = 0x00000004,
    WGPUTextureSampleType_Sint = 0x00000005,
    WGPUTextureSampleType_Uint = 0x00000006,
    WGPUTextureSampleType_Force32 = 0x7FFFFFFF
} WGPUTextureSampleType WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUTextureViewDimension {
    /**
     * `0x00000000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUTextureViewDimension_Undefined = 0x00000000,
    WGPUTextureViewDimension_1D = 0x00000001,
    WGPUTextureViewDimension_2D = 0x00000002,
    WGPUTextureViewDimension_2DArray = 0x00000003,
    WGPUTextureViewDimension_Cube = 0x00000004,
    WGPUTextureViewDimension_CubeArray = 0x00000005,
    WGPUTextureViewDimension_3D = 0x00000006,
    WGPUTextureViewDimension_Force32 = 0x7FFFFFFF
} WGPUTextureViewDimension WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexFormat {
    WGPUVertexFormat_Uint8 = 0x00000001,
    WGPUVertexFormat_Uint8x2 = 0x00000002,
    WGPUVertexFormat_Uint8x4 = 0x00000003,
    WGPUVertexFormat_Sint8 = 0x00000004,
    WGPUVertexFormat_Sint8x2 = 0x00000005,
    WGPUVertexFormat_Sint8x4 = 0x00000006,
    WGPUVertexFormat_Unorm8 = 0x00000007,
    WGPUVertexFormat_Unorm8x2 = 0x00000008,
    WGPUVertexFormat_Unorm8x4 = 0x00000009,
    WGPUVertexFormat_Snorm8 = 0x0000000A,
    WGPUVertexFormat_Snorm8x2 = 0x0000000B,
    WGPUVertexFormat_Snorm8x4 = 0x0000000C,
    WGPUVertexFormat_Uint16 = 0x0000000D,
    WGPUVertexFormat_Uint16x2 = 0x0000000E,
    WGPUVertexFormat_Uint16x4 = 0x0000000F,
    WGPUVertexFormat_Sint16 = 0x00000010,
    WGPUVertexFormat_Sint16x2 = 0x00000011,
    WGPUVertexFormat_Sint16x4 = 0x00000012,
    WGPUVertexFormat_Unorm16 = 0x00000013,
    WGPUVertexFormat_Unorm16x2 = 0x00000014,
    WGPUVertexFormat_Unorm16x4 = 0x00000015,
    WGPUVertexFormat_Snorm16 = 0x00000016,
    WGPUVertexFormat_Snorm16x2 = 0x00000017,
    WGPUVertexFormat_Snorm16x4 = 0x00000018,
    WGPUVertexFormat_Float16 = 0x00000019,
    WGPUVertexFormat_Float16x2 = 0x0000001A,
    WGPUVertexFormat_Float16x4 = 0x0000001B,
    WGPUVertexFormat_Float32 = 0x0000001C,
    WGPUVertexFormat_Float32x2 = 0x0000001D,
    WGPUVertexFormat_Float32x3 = 0x0000001E,
    WGPUVertexFormat_Float32x4 = 0x0000001F,
    WGPUVertexFormat_Uint32 = 0x00000020,
    WGPUVertexFormat_Uint32x2 = 0x00000021,
    WGPUVertexFormat_Uint32x3 = 0x00000022,
    WGPUVertexFormat_Uint32x4 = 0x00000023,
    WGPUVertexFormat_Sint32 = 0x00000024,
    WGPUVertexFormat_Sint32x2 = 0x00000025,
    WGPUVertexFormat_Sint32x3 = 0x00000026,
    WGPUVertexFormat_Sint32x4 = 0x00000027,
    WGPUVertexFormat_Unorm10_10_10_2 = 0x00000028,
    WGPUVertexFormat_Unorm8x4BGRA = 0x00000029,
    WGPUVertexFormat_Force32 = 0x7FFFFFFF
} WGPUVertexFormat WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUVertexStepMode {
    /**
     * `0x00000000`.
     * This @ref WGPUVertexBufferLayout is a "hole" in the @ref WGPUVertexState `buffers` array.
     * (See also @ref SentinelValues.)
     */
    WGPUVertexStepMode_VertexBufferNotUsed = 0x00000000,
    /**
     * `0x00000001`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUVertexStepMode_Undefined = 0x00000001,
    WGPUVertexStepMode_Vertex = 0x00000002,
    WGPUVertexStepMode_Instance = 0x00000003,
    WGPUVertexStepMode_Force32 = 0x7FFFFFFF
} WGPUVertexStepMode WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUWGSLLanguageFeatureName {
    WGPUWGSLLanguageFeatureName_ReadonlyAndReadwriteStorageTextures = 0x00000001,
    WGPUWGSLLanguageFeatureName_Packed4x8IntegerDotProduct = 0x00000002,
    WGPUWGSLLanguageFeatureName_UnrestrictedPointerParameters = 0x00000003,
    WGPUWGSLLanguageFeatureName_PointerCompositeAccess = 0x00000004,
    WGPUWGSLLanguageFeatureName_Force32 = 0x7FFFFFFF
} WGPUWGSLLanguageFeatureName WGPU_ENUM_ATTRIBUTE;

/**
 * Status returned from a call to ::wgpuInstanceWaitAny.
 */
typedef enum WGPUWaitStatus {
    /**
     * `0x00000001`.
     * At least one WGPUFuture completed successfully.
     */
    WGPUWaitStatus_Success = 0x00000001,
    /**
     * `0x00000002`.
     * No WGPUFutures completed within the timeout.
     */
    WGPUWaitStatus_TimedOut = 0x00000002,
    /**
     * `0x00000003`.
     * A @ref Timed-Wait was performed when WGPUInstanceFeatures::timedWaitAnyEnable is false.
     */
    WGPUWaitStatus_UnsupportedTimeout = 0x00000003,
    /**
     * `0x00000004`.
     * The number of futures waited on in a @ref Timed-Wait is greater than the supported WGPUInstanceFeatures::timedWaitAnyMaxCount.
     */
    WGPUWaitStatus_UnsupportedCount = 0x00000004,
    /**
     * `0x00000005`.
     * An invalid wait was performed with @ref Mixed-Sources.
     */
    WGPUWaitStatus_UnsupportedMixedSources = 0x00000005,
    WGPUWaitStatus_Force32 = 0x7FFFFFFF
} WGPUWaitStatus WGPU_ENUM_ATTRIBUTE;


/** @} */

/**
 * \defgroup Bitflags
 * \brief Type and constant definitions for bitflag types.
 *
 * @{
 */
typedef WGPUFlags WGPUBufferUsage;
static const WGPUBufferUsage WGPUBufferUsage_None = 0x0000000000000000;
static const WGPUBufferUsage WGPUBufferUsage_MapRead = 0x0000000000000001;
static const WGPUBufferUsage WGPUBufferUsage_MapWrite = 0x0000000000000002;
static const WGPUBufferUsage WGPUBufferUsage_CopySrc = 0x0000000000000004;
static const WGPUBufferUsage WGPUBufferUsage_CopyDst = 0x0000000000000008;
static const WGPUBufferUsage WGPUBufferUsage_Index = 0x0000000000000010;
static const WGPUBufferUsage WGPUBufferUsage_Vertex = 0x0000000000000020;
static const WGPUBufferUsage WGPUBufferUsage_Uniform = 0x0000000000000040;
static const WGPUBufferUsage WGPUBufferUsage_Storage = 0x0000000000000080;
static const WGPUBufferUsage WGPUBufferUsage_Indirect = 0x0000000000000100;
static const WGPUBufferUsage WGPUBufferUsage_QueryResolve = 0x0000000000000200;

typedef WGPUFlags WGPUColorWriteMask;
static const WGPUColorWriteMask WGPUColorWriteMask_None = 0x0000000000000000;
static const WGPUColorWriteMask WGPUColorWriteMask_Red = 0x0000000000000001;
static const WGPUColorWriteMask WGPUColorWriteMask_Green = 0x0000000000000002;
static const WGPUColorWriteMask WGPUColorWriteMask_Blue = 0x0000000000000004;
static const WGPUColorWriteMask WGPUColorWriteMask_Alpha = 0x0000000000000008;
static const WGPUColorWriteMask WGPUColorWriteMask_All = 0x000000000000000F /* Red | Green | Blue | Alpha */;

typedef WGPUFlags WGPUMapMode;
static const WGPUMapMode WGPUMapMode_None = 0x0000000000000000;
static const WGPUMapMode WGPUMapMode_Read = 0x0000000000000001;
static const WGPUMapMode WGPUMapMode_Write = 0x0000000000000002;

typedef WGPUFlags WGPUShaderStage;
static const WGPUShaderStage WGPUShaderStage_None = 0x0000000000000000;
static const WGPUShaderStage WGPUShaderStage_Vertex = 0x0000000000000001;
static const WGPUShaderStage WGPUShaderStage_Fragment = 0x0000000000000002;
static const WGPUShaderStage WGPUShaderStage_Compute = 0x0000000000000004;

typedef WGPUFlags WGPUTextureUsage;
static const WGPUTextureUsage WGPUTextureUsage_None = 0x0000000000000000;
static const WGPUTextureUsage WGPUTextureUsage_CopySrc = 0x0000000000000001;
static const WGPUTextureUsage WGPUTextureUsage_CopyDst = 0x0000000000000002;
static const WGPUTextureUsage WGPUTextureUsage_TextureBinding = 0x0000000000000004;
static const WGPUTextureUsage WGPUTextureUsage_StorageBinding = 0x0000000000000008;
static const WGPUTextureUsage WGPUTextureUsage_RenderAttachment = 0x0000000000000010;


/** @} */
typedef void (*WGPUProc)(void) WGPU_FUNCTION_ATTRIBUTE;


/**
 * \defgroup Callbacks
 * \brief Callbacks through which asynchronous functions return.
 *
 * @{
 */
/**
 * See also @ref CallbackError.
 *
 * @param message
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPUBufferMapCallback)(WGPUMapAsyncStatus status, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param compilationInfo
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPUCompilationInfoCallback)(WGPUCompilationInfoRequestStatus status, struct WGPUCompilationInfo const * compilationInfo, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param pipeline
 * This parameter is @ref PassedWithOwnership.
 */
typedef void (*WGPUCreateComputePipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPUComputePipeline pipeline, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param pipeline
 * This parameter is @ref PassedWithOwnership.
 */
typedef void (*WGPUCreateRenderPipelineAsyncCallback)(WGPUCreatePipelineAsyncStatus status, WGPURenderPipeline pipeline, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param device
 * Reference to the device which was lost. If, and only if, the `reason` is @ref WGPUDeviceLostReason_FailedCreation, this is a non-null pointer to a null @ref WGPUDevice.
 * This parameter is @ref PassedWithoutOwnership.
 *
 * @param message
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPUDeviceLostCallback)(WGPUDevice const * device, WGPUDeviceLostReason reason, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param status
 * See @ref WGPUPopErrorScopeStatus.
 *
 * @param type
 * The type of the error caught by the scope, or @ref WGPUErrorType_NoError if there was none.
 * If the `status` is not @ref WGPUPopErrorScopeStatus_Success, this is @ref WGPUErrorType_NoError.
 *
 * @param message
 * If the `type` is not @ref WGPUErrorType_NoError, this is a non-empty @ref LocalizableHumanReadableMessageString;
 * otherwise, this is an empty string.
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPUPopErrorScopeCallback)(WGPUPopErrorScopeStatus status, WGPUErrorType type, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 */
typedef void (*WGPUQueueWorkDoneCallback)(WGPUQueueWorkDoneStatus status, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param adapter
 * This parameter is @ref PassedWithOwnership.
 *
 * @param message
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPURequestAdapterCallback)(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param device
 * This parameter is @ref PassedWithOwnership.
 *
 * @param message
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPURequestDeviceCallback)(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;
/**
 * See also @ref CallbackError.
 *
 * @param device
 * This parameter is @ref PassedWithoutOwnership.
 *
 * @param message
 * This parameter is @ref PassedWithoutOwnership.
 */
typedef void (*WGPUUncapturedErrorCallback)(WGPUDevice const * device, WGPUErrorType type, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

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

 /**
 * \defgroup WGPUCallbackInfo
 * \brief Callback info structures that are used in asynchronous functions.
 *
 * @{
 */
typedef struct WGPUBufferMapCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUBufferMapCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUBufferMapCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_MAP_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferMapCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCompilationInfoCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUCompilationInfoCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCompilationInfoCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_INFO_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationInfoCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCreateComputePipelineAsyncCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUCreateComputePipelineAsyncCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCreateComputePipelineAsyncCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CREATE_COMPUTE_PIPELINE_ASYNC_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCreateComputePipelineAsyncCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUCreateRenderPipelineAsyncCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUCreateRenderPipelineAsyncCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUCreateRenderPipelineAsyncCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CREATE_RENDER_PIPELINE_ASYNC_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCreateRenderPipelineAsyncCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUDeviceLostCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUDeviceLostCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUDeviceLostCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEVICE_LOST_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDeviceLostCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUPopErrorScopeCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUPopErrorScopeCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUPopErrorScopeCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_POP_ERROR_SCOPE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPopErrorScopeCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUQueueWorkDoneCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUQueueWorkDoneCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUQueueWorkDoneCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUEUE_WORK_DONE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQueueWorkDoneCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPURequestAdapterCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPURequestAdapterCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPURequestAdapterCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPURequestDeviceCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPURequestDeviceCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPURequestDeviceCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestDeviceCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

typedef struct WGPUUncapturedErrorCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUUncapturedErrorCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUUncapturedErrorCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUUncapturedErrorCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

/** @} */

/**
 * Default values can be set using WGPU_ADAPTER_INFO_INIT as initializer.
 */
typedef struct WGPUAdapterInfo {
    WGPUChainedStructOut * nextInChain;
    /**
     * This is an \ref OutputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView vendor;
    /**
     * This is an \ref OutputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView architecture;
    /**
     * This is an \ref OutputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView device;
    /**
     * This is an \ref OutputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView description;
    /**
     * Defaults to @ref WGPUBackendType_Undefined
     */
    WGPUBackendType backendType;
    /**
     * Defaults to @ref WGPUAdapterType_Unknown
     */
    WGPUAdapterType adapterType;
    /**
     * Defaults to 0
     */
    uint32_t vendorID;
    /**
     * Defaults to 0
     */
    uint32_t deviceID;
} WGPUAdapterInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ADAPTER_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUAdapterInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.vendor=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.architecture=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.device=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.description=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.backendType=*/WGPUBackendType_Undefined _wgpu_COMMA \
    /*.adapterType=*/WGPUAdapterType_Unknown _wgpu_COMMA \
    /*.vendorID=*/0 _wgpu_COMMA \
    /*.deviceID=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BIND_GROUP_ENTRY_INIT as initializer.
 */
typedef struct WGPUBindGroupEntry {
    WGPUChainedStruct const * nextInChain;
    /**
     * Binding index in the bind group.
     *
     * Defaults to 0
     */
    uint32_t binding;
    /**
     * Set this if the binding is a buffer object.
     * Otherwise must be null.
     *
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUBuffer buffer;
    /**
     * If the binding is a buffer, this is the byte offset of the binding range.
     * Otherwise ignored.
     *
     * Defaults to 0
     */
    uint64_t offset;
    /**
     * If the binding is a buffer, this is the byte size of the binding range
     * (@ref WGPU_WHOLE_SIZE means the binding ends at the end of the buffer).
     * Otherwise ignored.
     *
     * Defaults to 0
     */
    uint64_t size;
    /**
     * Set this if the binding is a sampler object.
     * Otherwise must be null.
     *
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUSampler sampler;
    /**
     * Set this if the binding is a texture view object.
     * Otherwise must be null.
     *
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUTextureView textureView;
} WGPUBindGroupEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.binding=*/0 _wgpu_COMMA \
    /*.buffer=*/NULL _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
    /*.sampler=*/NULL _wgpu_COMMA \
    /*.textureView=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BLEND_COMPONENT_INIT as initializer.
 */
typedef struct WGPUBlendComponent {
    /**
     * Defaults to @ref WGPUBlendOperation_Add
     */
    WGPUBlendOperation operation;
    /**
     * Defaults to @ref WGPUBlendFactor_One
     */
    WGPUBlendFactor srcFactor;
    /**
     * Defaults to @ref WGPUBlendFactor_Zero
     */
    WGPUBlendFactor dstFactor;
} WGPUBlendComponent WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BLEND_COMPONENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBlendComponent, { \
    /*.operation=*/WGPUBlendOperation_Add _wgpu_COMMA \
    /*.srcFactor=*/WGPUBlendFactor_One _wgpu_COMMA \
    /*.dstFactor=*/WGPUBlendFactor_Zero _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BUFFER_BINDING_LAYOUT_INIT as initializer.
 */
typedef struct WGPUBufferBindingLayout {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUBufferBindingType_Uniform
     */
    WGPUBufferBindingType type;
    /**
     * Defaults to 0
     */
    WGPUBool hasDynamicOffset;
    /**
     * Defaults to 0
     */
    uint64_t minBindingSize;
} WGPUBufferBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.type=*/WGPUBufferBindingType_Uniform _wgpu_COMMA \
    /*.hasDynamicOffset=*/0 _wgpu_COMMA \
    /*.minBindingSize=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BUFFER_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUBufferDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPUBufferUsage_None
     */
    WGPUBufferUsage usage;
    /**
     * Defaults to 0
     */
    uint64_t size;
    /**
     * Defaults to 0
     */
    WGPUBool mappedAtCreation;
} WGPUBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BUFFER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBufferDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.usage=*/WGPUBufferUsage_None _wgpu_COMMA \
    /*.size=*/0 _wgpu_COMMA \
    /*.mappedAtCreation=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COLOR_INIT as initializer.
 */
typedef struct WGPUColor {
    /**
     * Defaults to 0.0
     */
    double r;
    /**
     * Defaults to 0.0
     */
    double g;
    /**
     * Defaults to 0.0
     */
    double b;
    /**
     * Defaults to 0.0
     */
    double a;
} WGPUColor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COLOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUColor, { \
    /*.r=*/0.0 _wgpu_COMMA \
    /*.g=*/0.0 _wgpu_COMMA \
    /*.b=*/0.0 _wgpu_COMMA \
    /*.a=*/0.0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUCommandBufferDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPUCommandBufferDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCommandBufferDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUCommandEncoderDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPUCommandEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCommandEncoderDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPILATION_MESSAGE_INIT as initializer.
 */
typedef struct WGPUCompilationMessage {
    WGPUChainedStruct const * nextInChain;
    /**
     * A @ref LocalizableHumanReadableMessageString.
     *
     * This is an \ref OutputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView message;
    /**
     * Severity level of the message.
     *
     * Defaults to @ref WGPUCompilationMessageType_Error
     */
    WGPUCompilationMessageType type;
    /**
     * Line number where the message is attached, starting at 1.
     *
     * Defaults to 0
     */
    uint64_t lineNum;
    /**
     * Offset in UTF-8 code units (bytes) from the beginning of the line, starting at 1.
     *
     * Defaults to 0
     */
    uint64_t linePos;
    /**
     * Offset in UTF-8 code units (bytes) from the beginning of the shader code, starting at 0.
     *
     * Defaults to 0
     */
    uint64_t offset;
    /**
     * Length in UTF-8 code units (bytes) of the span the message corresponds to.
     *
     * Defaults to 0
     */
    uint64_t length;
} WGPUCompilationMessage WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_MESSAGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationMessage, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.message=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.type=*/WGPUCompilationMessageType_Error _wgpu_COMMA \
    /*.lineNum=*/0 _wgpu_COMMA \
    /*.linePos=*/0 _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.length=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPUTE_PASS_TIMESTAMP_WRITES_INIT as initializer.
 */
typedef struct WGPUComputePassTimestampWrites {
    WGPUChainedStruct const * nextInChain;
    /**
     * Query set to write timestamps to. Null if timestamps should not be recorded.
     *
     * Defaults to NULL
     */
    WGPUQuerySet querySet;
    /**
     * Defaults to @ref WGPU_QUERY_SET_INDEX_UNDEFINED
     */
    uint32_t beginningOfPassWriteIndex;
    /**
     * Defaults to @ref WGPU_QUERY_SET_INDEX_UNDEFINED
     */
    uint32_t endOfPassWriteIndex;
} WGPUComputePassTimestampWrites WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_PASS_TIMESTAMP_WRITES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputePassTimestampWrites, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.querySet=*/NULL _wgpu_COMMA \
    /*.beginningOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
    /*.endOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_CONSTANT_ENTRY_INIT as initializer.
 */
typedef struct WGPUConstantEntry {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView key;
    /**
     * Defaults to 0.0
     */
    double value;
} WGPUConstantEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_CONSTANT_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUConstantEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.key=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.value=*/0.0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_EXTENT_3D_INIT as initializer.
 */
typedef struct WGPUExtent3D {
    /**
     * Defaults to 0
     */
    uint32_t width;
    /**
     * Defaults to 1
     */
    uint32_t height;
    /**
     * Defaults to 1
     */
    uint32_t depthOrArrayLayers;
} WGPUExtent3D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_EXTENT_3D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExtent3D, { \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/1 _wgpu_COMMA \
    /*.depthOrArrayLayers=*/1 _wgpu_COMMA \
})

/**
 * Opaque handle to an asynchronous operation. See @ref Asynchronous-Operations for more information.
 *
 * Default values can be set using WGPU_FUTURE_INIT as initializer.
 */
typedef struct WGPUFuture {
    /**
     * Opaque id of the @ref WGPUFuture
     *
     * Defaults to 0
     */
    uint64_t id;
} WGPUFuture WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FUTURE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFuture, { \
    /*.id=*/0 _wgpu_COMMA \
})

/**
 * Features enabled on the WGPUInstance
 *
 * Default values can be set using WGPU_INSTANCE_CAPABILITIES_INIT as initializer.
 */
typedef struct WGPUInstanceCapabilities {
    /** This struct chain is used as mutable in some places and immutable in others. */
    WGPUChainedStructOut * nextInChain;
    /**
     * Enable use of ::wgpuInstanceWaitAny with `timeoutNS > 0`.
     *
     * Defaults to 0
     */
    WGPUBool timedWaitAnyEnable;
    /**
     * The maximum number @ref WGPUFutureWaitInfo supported in a call to ::wgpuInstanceWaitAny with `timeoutNS > 0`.
     *
     * Defaults to 0
     */
    size_t timedWaitAnyMaxCount;
} WGPUInstanceCapabilities WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_INSTANCE_CAPABILITIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceCapabilities, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.timedWaitAnyEnable=*/0 _wgpu_COMMA \
    /*.timedWaitAnyMaxCount=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_LIMITS_INIT as initializer.
 */
typedef struct WGPULimits {
    /** This struct chain is used as mutable in some places and immutable in others. */
    WGPUChainedStructOut * nextInChain;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxTextureDimension1D;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxTextureDimension2D;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxTextureDimension3D;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxTextureArrayLayers;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxBindGroups;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxBindGroupsPlusVertexBuffers;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxBindingsPerBindGroup;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxDynamicUniformBuffersPerPipelineLayout;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxDynamicStorageBuffersPerPipelineLayout;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxSampledTexturesPerShaderStage;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxSamplersPerShaderStage;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxStorageBuffersPerShaderStage;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxStorageTexturesPerShaderStage;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxUniformBuffersPerShaderStage;
    /**
     * Defaults to @ref WGPU_LIMIT_U64_UNDEFINED
     */
    uint64_t maxUniformBufferBindingSize;
    /**
     * Defaults to @ref WGPU_LIMIT_U64_UNDEFINED
     */
    uint64_t maxStorageBufferBindingSize;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t minUniformBufferOffsetAlignment;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t minStorageBufferOffsetAlignment;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxVertexBuffers;
    /**
     * Defaults to @ref WGPU_LIMIT_U64_UNDEFINED
     */
    uint64_t maxBufferSize;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxVertexAttributes;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxVertexBufferArrayStride;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxInterStageShaderVariables;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxColorAttachments;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxColorAttachmentBytesPerSample;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeWorkgroupStorageSize;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeInvocationsPerWorkgroup;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeWorkgroupSizeX;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeWorkgroupSizeY;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeWorkgroupSizeZ;
    /**
     * Defaults to @ref WGPU_LIMIT_U32_UNDEFINED
     */
    uint32_t maxComputeWorkgroupsPerDimension;
} WGPULimits WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPULimits, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.maxTextureDimension1D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureDimension2D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureDimension3D=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxTextureArrayLayers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindGroups=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindGroupsPlusVertexBuffers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBindingsPerBindGroup=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxDynamicUniformBuffersPerPipelineLayout=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxDynamicStorageBuffersPerPipelineLayout=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxSampledTexturesPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxSamplersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageBuffersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxStorageTexturesPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxUniformBuffersPerShaderStage=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxUniformBufferBindingSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.maxStorageBufferBindingSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.minUniformBufferOffsetAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.minStorageBufferOffsetAlignment=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxVertexBuffers=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxBufferSize=*/WGPU_LIMIT_U64_UNDEFINED _wgpu_COMMA \
    /*.maxVertexAttributes=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxVertexBufferArrayStride=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxInterStageShaderVariables=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxColorAttachments=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxColorAttachmentBytesPerSample=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupStorageSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeInvocationsPerWorkgroup=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeX=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeY=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupSizeZ=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxComputeWorkgroupsPerDimension=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_MULTISAMPLE_STATE_INIT as initializer.
 */
typedef struct WGPUMultisampleState {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to 1
     */
    uint32_t count;
    /**
     * Defaults to 4294967295
     */
    uint32_t mask;
    /**
     * Defaults to 0
     */
    WGPUBool alphaToCoverageEnabled;
} WGPUMultisampleState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_MULTISAMPLE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUMultisampleState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.count=*/1 _wgpu_COMMA \
    /*.mask=*/4294967295 _wgpu_COMMA \
    /*.alphaToCoverageEnabled=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_ORIGIN_3D_INIT as initializer.
 */
typedef struct WGPUOrigin3D {
    /**
     * Defaults to 0
     */
    uint32_t x;
    /**
     * Defaults to 0
     */
    uint32_t y;
    /**
     * Defaults to 0
     */
    uint32_t z;
} WGPUOrigin3D WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_ORIGIN_3D_INIT _wgpu_MAKE_INIT_STRUCT(WGPUOrigin3D, { \
    /*.x=*/0 _wgpu_COMMA \
    /*.y=*/0 _wgpu_COMMA \
    /*.z=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUPipelineLayoutDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    size_t bindGroupLayoutCount;
    WGPUBindGroupLayout const * bindGroupLayouts;
} WGPUPipelineLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.bindGroupLayoutCount=*/0 _wgpu_COMMA \
    /*.bindGroupLayouts=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_PRIMITIVE_STATE_INIT as initializer.
 */
typedef struct WGPUPrimitiveState {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUPrimitiveTopology_TriangleList
     */
    WGPUPrimitiveTopology topology;
    /**
     * Defaults to @ref WGPUIndexFormat_Undefined
     */
    WGPUIndexFormat stripIndexFormat;
    /**
     * Defaults to @ref WGPUFrontFace_CCW
     */
    WGPUFrontFace frontFace;
    /**
     * Defaults to @ref WGPUCullMode_None
     */
    WGPUCullMode cullMode;
    /**
     * Defaults to 0
     */
    WGPUBool unclippedDepth;
} WGPUPrimitiveState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_PRIMITIVE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPrimitiveState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.topology=*/WGPUPrimitiveTopology_TriangleList _wgpu_COMMA \
    /*.stripIndexFormat=*/WGPUIndexFormat_Undefined _wgpu_COMMA \
    /*.frontFace=*/WGPUFrontFace_CCW _wgpu_COMMA \
    /*.cullMode=*/WGPUCullMode_None _wgpu_COMMA \
    /*.unclippedDepth=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_QUERY_SET_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUQuerySetDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPUQueryType_Occlusion
     */
    WGPUQueryType type;
    /**
     * Defaults to 0
     */
    uint32_t count;
} WGPUQuerySetDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUERY_SET_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQuerySetDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.type=*/WGPUQueryType_Occlusion _wgpu_COMMA \
    /*.count=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_QUEUE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUQueueDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPUQueueDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_QUEUE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQueueDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_BUNDLE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPURenderBundleDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPURenderBundleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_BUNDLE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderBundleDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_BUNDLE_ENCODER_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPURenderBundleEncoderDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    size_t colorFormatCount;
    WGPUTextureFormat const * colorFormats;
    /**
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat depthStencilFormat;
    /**
     * Defaults to 0
     */
    uint32_t sampleCount;
    /**
     * Defaults to 0
     */
    WGPUBool depthReadOnly;
    /**
     * Defaults to 0
     */
    WGPUBool stencilReadOnly;
} WGPURenderBundleEncoderDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_BUNDLE_ENCODER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderBundleEncoderDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.colorFormatCount=*/0 _wgpu_COMMA \
    /*.colorFormats=*/NULL _wgpu_COMMA \
    /*.depthStencilFormat=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.sampleCount=*/0 _wgpu_COMMA \
    /*.depthReadOnly=*/0 _wgpu_COMMA \
    /*.stencilReadOnly=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT as initializer.
 */
typedef struct WGPURenderPassDepthStencilAttachment {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    WGPUTextureView view;
    /**
     * Defaults to @ref WGPULoadOp_Undefined
     */
    WGPULoadOp depthLoadOp;
    /**
     * Defaults to @ref WGPUStoreOp_Undefined
     */
    WGPUStoreOp depthStoreOp;
    /**
     * Defaults to 0.0f
     */
    float depthClearValue;
    /**
     * Defaults to 0
     */
    WGPUBool depthReadOnly;
    /**
     * Defaults to @ref WGPULoadOp_Undefined
     */
    WGPULoadOp stencilLoadOp;
    /**
     * Defaults to @ref WGPUStoreOp_Undefined
     */
    WGPUStoreOp stencilStoreOp;
    /**
     * Defaults to 0
     */
    uint32_t stencilClearValue;
    /**
     * Defaults to 0
     */
    WGPUBool stencilReadOnly;
} WGPURenderPassDepthStencilAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDepthStencilAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.view=*/NULL _wgpu_COMMA \
    /*.depthLoadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.depthStoreOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.depthClearValue=*/0.0f _wgpu_COMMA \
    /*.depthReadOnly=*/0 _wgpu_COMMA \
    /*.stencilLoadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.stencilStoreOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.stencilClearValue=*/0 _wgpu_COMMA \
    /*.stencilReadOnly=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PASS_MAX_DRAW_COUNT_INIT as initializer.
 */
typedef struct WGPURenderPassMaxDrawCount {
    WGPUChainedStruct chain;
    /**
     * Defaults to 50000000
     */
    uint64_t maxDrawCount;
} WGPURenderPassMaxDrawCount WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_MAX_DRAW_COUNT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassMaxDrawCount, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RenderPassMaxDrawCount _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxDrawCount=*/50000000 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PASS_TIMESTAMP_WRITES_INIT as initializer.
 */
typedef struct WGPURenderPassTimestampWrites {
    WGPUChainedStruct const * nextInChain;
    /**
     * Query set to write timestamps to. Null if timestamps should not be recorded.
     *
     * Defaults to NULL
     */
    WGPUQuerySet querySet;
    /**
     * Defaults to @ref WGPU_QUERY_SET_INDEX_UNDEFINED
     */
    uint32_t beginningOfPassWriteIndex;
    /**
     * Defaults to @ref WGPU_QUERY_SET_INDEX_UNDEFINED
     */
    uint32_t endOfPassWriteIndex;
} WGPURenderPassTimestampWrites WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_TIMESTAMP_WRITES_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassTimestampWrites, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.querySet=*/NULL _wgpu_COMMA \
    /*.beginningOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
    /*.endOfPassWriteIndex=*/WGPU_QUERY_SET_INDEX_UNDEFINED _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_REQUEST_ADAPTER_OPTIONS_INIT as initializer.
 */
typedef struct WGPURequestAdapterOptions {
    WGPUChainedStruct const * nextInChain;
    /**
     * "Feature level" for the adapter request. If an adapter is returned, it must support the features and limits in the requested feature level.
     *
     * Implementations may ignore @ref WGPUFeatureLevel_Compatibility and provide @ref WGPUFeatureLevel_Core instead. @ref WGPUFeatureLevel_Core is the default in the JS API, but in C, this field is **required** (must not be undefined).
     *
     * Defaults to @ref WGPUFeatureLevel_Core
     */
    WGPUFeatureLevel featureLevel;
    /**
     * Defaults to @ref WGPUPowerPreference_Undefined
     */
    WGPUPowerPreference powerPreference;
    /**
     * If true, requires the adapter to be a "fallback" adapter as defined by the JS spec.
     * If this is not possible, the request returns null.
     *
     * Defaults to 0
     */
    WGPUBool forceFallbackAdapter;
    /**
     * If set, requires the adapter to have a particular backend type.
     * If this is not possible, the request returns null.
     *
     * Defaults to @ref WGPUBackendType_Undefined
     */
    WGPUBackendType backendType;
    /**
     * If set, requires the adapter to be able to output to a particular surface.
     * If this is not possible, the request returns null.
     *
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUSurface compatibleSurface;
} WGPURequestAdapterOptions WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_REQUEST_ADAPTER_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequestAdapterOptions, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.featureLevel=*/WGPUFeatureLevel_Core _wgpu_COMMA \
    /*.powerPreference=*/WGPUPowerPreference_Undefined _wgpu_COMMA \
    /*.forceFallbackAdapter=*/0 _wgpu_COMMA \
    /*.backendType=*/WGPUBackendType_Undefined _wgpu_COMMA \
    /*.compatibleSurface=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SAMPLER_BINDING_LAYOUT_INIT as initializer.
 */
typedef struct WGPUSamplerBindingLayout {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUSamplerBindingType_BindingNotUsed
     */
    WGPUSamplerBindingType type;
} WGPUSamplerBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SAMPLER_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSamplerBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.type=*/WGPUSamplerBindingType_BindingNotUsed _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SAMPLER_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUSamplerDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPUAddressMode_ClampToEdge
     */
    WGPUAddressMode addressModeU;
    /**
     * Defaults to @ref WGPUAddressMode_ClampToEdge
     */
    WGPUAddressMode addressModeV;
    /**
     * Defaults to @ref WGPUAddressMode_ClampToEdge
     */
    WGPUAddressMode addressModeW;
    /**
     * Defaults to @ref WGPUFilterMode_Nearest
     */
    WGPUFilterMode magFilter;
    /**
     * Defaults to @ref WGPUFilterMode_Nearest
     */
    WGPUFilterMode minFilter;
    /**
     * Defaults to @ref WGPUMipmapFilterMode_Nearest
     */
    WGPUMipmapFilterMode mipmapFilter;
    /**
     * Defaults to 0.f
     */
    float lodMinClamp;
    /**
     * Defaults to 32.f
     */
    float lodMaxClamp;
    /**
     * Defaults to @ref WGPUCompareFunction_Undefined
     */
    WGPUCompareFunction compare;
    /**
     * Defaults to 1
     */
    uint16_t maxAnisotropy;
} WGPUSamplerDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SAMPLER_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSamplerDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.addressModeU=*/WGPUAddressMode_ClampToEdge _wgpu_COMMA \
    /*.addressModeV=*/WGPUAddressMode_ClampToEdge _wgpu_COMMA \
    /*.addressModeW=*/WGPUAddressMode_ClampToEdge _wgpu_COMMA \
    /*.magFilter=*/WGPUFilterMode_Nearest _wgpu_COMMA \
    /*.minFilter=*/WGPUFilterMode_Nearest _wgpu_COMMA \
    /*.mipmapFilter=*/WGPUMipmapFilterMode_Nearest _wgpu_COMMA \
    /*.lodMinClamp=*/0.f _wgpu_COMMA \
    /*.lodMaxClamp=*/32.f _wgpu_COMMA \
    /*.compare=*/WGPUCompareFunction_Undefined _wgpu_COMMA \
    /*.maxAnisotropy=*/1 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SHADER_MODULE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUShaderModuleDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPUShaderModuleDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_MODULE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderModuleDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SHADER_SOURCE_SPIRV_INIT as initializer.
 */
typedef struct WGPUShaderSourceSPIRV {
    WGPUChainedStruct chain;
    /**
     * Defaults to 0
     */
    uint32_t codeSize;
    /**
     * Defaults to 0
     */
    uint32_t const * code;
} WGPUShaderSourceSPIRV WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_SOURCE_SPIRV_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderSourceSPIRV, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderSourceSPIRV _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.codeSize=*/0 _wgpu_COMMA \
    /*.code=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SHADER_SOURCE_WGSL_INIT as initializer.
 */
typedef struct WGPUShaderSourceWGSL {
    WGPUChainedStruct chain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView code;
} WGPUShaderSourceWGSL WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SHADER_SOURCE_WGSL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderSourceWGSL, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderSourceWGSL _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.code=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_STENCIL_FACE_STATE_INIT as initializer.
 */
typedef struct WGPUStencilFaceState {
    /**
     * Defaults to @ref WGPUCompareFunction_Always
     */
    WGPUCompareFunction compare;
    /**
     * Defaults to @ref WGPUStencilOperation_Keep
     */
    WGPUStencilOperation failOp;
    /**
     * Defaults to @ref WGPUStencilOperation_Keep
     */
    WGPUStencilOperation depthFailOp;
    /**
     * Defaults to @ref WGPUStencilOperation_Keep
     */
    WGPUStencilOperation passOp;
} WGPUStencilFaceState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STENCIL_FACE_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStencilFaceState, { \
    /*.compare=*/WGPUCompareFunction_Always _wgpu_COMMA \
    /*.failOp=*/WGPUStencilOperation_Keep _wgpu_COMMA \
    /*.depthFailOp=*/WGPUStencilOperation_Keep _wgpu_COMMA \
    /*.passOp=*/WGPUStencilOperation_Keep _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT as initializer.
 */
typedef struct WGPUStorageTextureBindingLayout {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUStorageTextureAccess_BindingNotUsed
     */
    WGPUStorageTextureAccess access;
    /**
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * Defaults to @ref WGPUTextureViewDimension_2D
     */
    WGPUTextureViewDimension viewDimension;
} WGPUStorageTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUStorageTextureBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.access=*/WGPUStorageTextureAccess_BindingNotUsed _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.viewDimension=*/WGPUTextureViewDimension_2D _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SUPPORTED_FEATURES_INIT as initializer.
 */
typedef struct WGPUSupportedFeatures {
    /**
     * Defaults to NULL
     */
    size_t featureCount;
    WGPUFeatureName const * features;
} WGPUSupportedFeatures WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUPPORTED_FEATURES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedFeatures, { \
    /*.featureCount=*/0 _wgpu_COMMA \
    /*.features=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_SUPPORTED_WGSL_LANGUAGE_FEATURES_INIT as initializer.
 */
typedef struct WGPUSupportedWGSLLanguageFeatures {
    /**
     * Defaults to NULL
     */
    size_t featureCount;
    WGPUWGSLLanguageFeatureName const * features;
} WGPUSupportedWGSLLanguageFeatures WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SUPPORTED_WGSL_LANGUAGE_FEATURES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedWGSLLanguageFeatures, { \
    /*.featureCount=*/0 _wgpu_COMMA \
    /*.features=*/NULL _wgpu_COMMA \
})

/**
 * Filled by `::wgpuSurfaceGetCapabilities` with what's supported for `::wgpuSurfaceConfigure` for a pair of @ref WGPUSurface and @ref WGPUAdapter.
 *
 * Default values can be set using WGPU_SURFACE_CAPABILITIES_INIT as initializer.
 */
typedef struct WGPUSurfaceCapabilities {
    WGPUChainedStructOut * nextInChain;
    /**
     * The bit set of supported @ref WGPUTextureUsage bits.
     * Guaranteed to contain @ref WGPUTextureUsage_RenderAttachment.
     *
     * Defaults to @ref WGPUTextureUsage_None
     */
    WGPUTextureUsage usages;
    /**
     * A list of supported @ref WGPUTextureFormat values, in order of preference.
     *
     * Defaults to NULL
     */
    size_t formatCount;
    WGPUTextureFormat const * formats;
    /**
     * A list of supported @ref WGPUPresentMode values.
     * Guaranteed to contain @ref WGPUPresentMode_Fifo.
     *
     * Defaults to NULL
     */
    size_t presentModeCount;
    WGPUPresentMode const * presentModes;
    /**
     * A list of supported @ref WGPUCompositeAlphaMode values.
     * @ref WGPUCompositeAlphaMode_Auto will be an alias for the first element and will never be present in this array.
     *
     * Defaults to NULL
     */
    size_t alphaModeCount;
    WGPUCompositeAlphaMode const * alphaModes;
} WGPUSurfaceCapabilities WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_CAPABILITIES_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceCapabilities, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.usages=*/WGPUTextureUsage_None _wgpu_COMMA \
    /*.formatCount=*/0 _wgpu_COMMA \
    /*.formats=*/NULL _wgpu_COMMA \
    /*.presentModeCount=*/0 _wgpu_COMMA \
    /*.presentModes=*/NULL _wgpu_COMMA \
    /*.alphaModeCount=*/0 _wgpu_COMMA \
    /*.alphaModes=*/NULL _wgpu_COMMA \
})

/**
 * Options to `::wgpuSurfaceConfigure` for defining how a @ref WGPUSurface will be rendered to and presented to the user.
 * See @ref Surface-Configuration for more details.
 *
 * Default values can be set using WGPU_SURFACE_CONFIGURATION_INIT as initializer.
 */
typedef struct WGPUSurfaceConfiguration {
    WGPUChainedStruct const * nextInChain;
    /**
     * The @ref WGPUDevice to use to render to surface's textures.
     *
     * Defaults to NULL
     */
    WGPUDevice device;
    /**
     * The @ref WGPUTextureFormat of the surface's textures.
     *
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * The @ref WGPUTextureUsage of the surface's textures.
     *
     * Defaults to @ref WGPUTextureUsage_RenderAttachment
     */
    WGPUTextureUsage usage;
    /**
     * The width of the surface's textures.
     *
     * Defaults to 0
     */
    uint32_t width;
    /**
     * The height of the surface's textures.
     *
     * Defaults to 0
     */
    uint32_t height;
    /**
     * The additional @ref WGPUTextureFormat for @ref WGPUTextureView format reinterpretation of the surface's textures.
     *
     * Defaults to NULL
     */
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
    /**
     * How the surface's frames will be composited on the screen.
     *
     * Defaults to @ref WGPUCompositeAlphaMode_Opaque
     */
    WGPUCompositeAlphaMode alphaMode;
    /**
     * When and in which order the surface's frames will be shown on the screen. Defaults to @ref WGPUPresentMode_Fifo.
     *
     * Defaults to @ref WGPUPresentMode_Fifo
     */
    WGPUPresentMode presentMode;
} WGPUSurfaceConfiguration WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_CONFIGURATION_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceConfiguration, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.device=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_RenderAttachment _wgpu_COMMA \
    /*.width=*/0 _wgpu_COMMA \
    /*.height=*/0 _wgpu_COMMA \
    /*.viewFormatCount=*/0 _wgpu_COMMA \
    /*.viewFormats=*/NULL _wgpu_COMMA \
    /*.alphaMode=*/WGPUCompositeAlphaMode_Opaque _wgpu_COMMA \
    /*.presentMode=*/WGPUPresentMode_Fifo _wgpu_COMMA \
})

/**
 * The root descriptor for the creation of an @ref WGPUSurface with `::wgpuInstanceCreateSurface`.
 * It isn't sufficient by itself and must have one of the `WGPUSurfaceSource*` in its chain.
 * See @ref Surface-Creation for more details.
 *
 * Default values can be set using WGPU_SURFACE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUSurfaceDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * Label used to refer to the object.
     *
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
} WGPUSurfaceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping an Android [`ANativeWindow`](https://developer.android.com/ndk/reference/group/a-native-window).
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_ANDROID_NATIVE_WINDOW_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceAndroidNativeWindow {
    WGPUChainedStruct chain;
    /**
     * The pointer to the [`ANativeWindow`](https://developer.android.com/ndk/reference/group/a-native-window) that will be wrapped by the @ref WGPUSurface.
     *
     * Defaults to NULL
     */
    void * window;
} WGPUSurfaceSourceAndroidNativeWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_ANDROID_NATIVE_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceAndroidNativeWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceAndroidNativeWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.window=*/NULL _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping a [`CAMetalLayer`](https://developer.apple.com/documentation/quartzcore/cametallayer?language=objc).
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_METAL_LAYER_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceMetalLayer {
    WGPUChainedStruct chain;
    /**
     * The pointer to the [`CAMetalLayer`](https://developer.apple.com/documentation/quartzcore/cametallayer?language=objc) that will be wrapped by the @ref WGPUSurface.
     *
     * Defaults to NULL
     */
    void * layer;
} WGPUSurfaceSourceMetalLayer WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_METAL_LAYER_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceMetalLayer, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceMetalLayer _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.layer=*/NULL _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping a [Wayland](https://wayland.freedesktop.org/) [`wl_surface`](https://wayland.freedesktop.org/docs/html/apa.html#protocol-spec-wl_surface).
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_WAYLAND_SURFACE_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceWaylandSurface {
    WGPUChainedStruct chain;
    /**
     * A [`wl_display`](https://wayland.freedesktop.org/docs/html/apa.html#protocol-spec-wl_display) for this Wayland instance.
     *
     * Defaults to NULL
     */
    void * display;
    /**
     * A [`wl_surface`](https://wayland.freedesktop.org/docs/html/apa.html#protocol-spec-wl_surface) that will be wrapped by the @ref WGPUSurface
     *
     * Defaults to NULL
     */
    void * surface;
} WGPUSurfaceSourceWaylandSurface WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_WAYLAND_SURFACE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceWaylandSurface, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceWaylandSurface _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.display=*/NULL _wgpu_COMMA \
    /*.surface=*/NULL _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping a Windows [`HWND`](https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd).
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceWindowsHWND {
    WGPUChainedStruct chain;
    /**
     * The [`HINSTANCE`](https://learn.microsoft.com/en-us/windows/win32/learnwin32/winmain--the-application-entry-point) for this application.
     * Most commonly `GetModuleHandle(nullptr)`.
     *
     * Defaults to NULL
     */
    void * hinstance;
    /**
     * The [`HWND`](https://learn.microsoft.com/en-us/windows/apps/develop/ui-input/retrieve-hwnd) that will be wrapped by the @ref WGPUSurface.
     *
     * Defaults to NULL
     */
    void * hwnd;
} WGPUSurfaceSourceWindowsHWND WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceWindowsHWND, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceWindowsHWND _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.hinstance=*/NULL _wgpu_COMMA \
    /*.hwnd=*/NULL _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping an [XCB](https://xcb.freedesktop.org/) `xcb_window_t`.
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_XCB_WINDOW_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceXCBWindow {
    WGPUChainedStruct chain;
    /**
     * The `xcb_connection_t` for the connection to the X server.
     *
     * Defaults to NULL
     */
    void * connection;
    /**
     * The `xcb_window_t` for the window that will be wrapped by the @ref WGPUSurface.
     *
     * Defaults to 0
     */
    uint32_t window;
} WGPUSurfaceSourceXCBWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_XCB_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceXCBWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceXCBWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.connection=*/NULL _wgpu_COMMA \
    /*.window=*/0 _wgpu_COMMA \
})

/**
 * Chained in @ref WGPUSurfaceDescriptor to make an @ref WGPUSurface wrapping an [Xlib](https://www.x.org/releases/current/doc/libX11/libX11/libX11.html) `Window`.
 *
 * Default values can be set using WGPU_SURFACE_SOURCE_XLIB_WINDOW_INIT as initializer.
 */
typedef struct WGPUSurfaceSourceXlibWindow {
    WGPUChainedStruct chain;
    /**
     * A pointer to the [`Display`](https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Opening_the_Display) connected to the X server.
     *
     * Defaults to NULL
     */
    void * display;
    /**
     * The [`Window`](https://www.x.org/releases/current/doc/libX11/libX11/libX11.html#Creating_Windows) that will be wrapped by the @ref WGPUSurface.
     *
     * Defaults to 0
     */
    uint64_t window;
} WGPUSurfaceSourceXlibWindow WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_SOURCE_XLIB_WINDOW_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceSourceXlibWindow, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceSourceXlibWindow _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.display=*/NULL _wgpu_COMMA \
    /*.window=*/0 _wgpu_COMMA \
})

/**
 * Queried each frame from a @ref WGPUSurface to get a @ref WGPUTexture to render to along with some metadata.
 * See @ref Surface-Presenting for more details.
 *
 * Default values can be set using WGPU_SURFACE_TEXTURE_INIT as initializer.
 */
typedef struct WGPUSurfaceTexture {
    WGPUChainedStructOut * nextInChain;
    /**
     * The @ref WGPUTexture representing the frame that will be shown on the surface.
     * It is @ref ReturnedWithOwnership from @ref wgpuSurfaceGetCurrentTexture.
     *
     * Defaults to NULL
     */
    WGPUTexture texture;
    /**
     * Whether the call to `::wgpuSurfaceGetCurrentTexture` succeeded and a hint as to why it might not have.
     *
     * Defaults to @ref WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal
     */
    WGPUSurfaceGetCurrentTextureStatus status;
} WGPUSurfaceTexture WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_SURFACE_TEXTURE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceTexture, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.texture=*/NULL _wgpu_COMMA \
    /*.status=*/WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT as initializer.
 */
typedef struct WGPUTexelCopyBufferLayout {
    /**
     * Defaults to 0
     */
    uint64_t offset;
    /**
     * Defaults to 0
     */
    uint32_t bytesPerRow;
    /**
     * Defaults to 0
     */
    uint32_t rowsPerImage;
} WGPUTexelCopyBufferLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyBufferLayout, { \
    /*.offset=*/0 _wgpu_COMMA \
    /*.bytesPerRow=*/0 _wgpu_COMMA \
    /*.rowsPerImage=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXTURE_BINDING_LAYOUT_INIT as initializer.
 */
typedef struct WGPUTextureBindingLayout {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUTextureSampleType_BindingNotUsed
     */
    WGPUTextureSampleType sampleType;
    /**
     * Defaults to @ref WGPUTextureViewDimension_2D
     */
    WGPUTextureViewDimension viewDimension;
    /**
     * Defaults to 0
     */
    WGPUBool multisampled;
} WGPUTextureBindingLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_BINDING_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureBindingLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.sampleType=*/WGPUTextureSampleType_BindingNotUsed _wgpu_COMMA \
    /*.viewDimension=*/WGPUTextureViewDimension_2D _wgpu_COMMA \
    /*.multisampled=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUTextureViewDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * Defaults to @ref WGPUTextureViewDimension_Undefined
     */
    WGPUTextureViewDimension dimension;
    /**
     * Defaults to 0
     */
    uint32_t baseMipLevel;
    /**
     * Defaults to 0
     */
    uint32_t mipLevelCount;
    /**
     * Defaults to 0
     */
    uint32_t baseArrayLayer;
    /**
     * Defaults to 0
     */
    uint32_t arrayLayerCount;
    /**
     * Defaults to @ref WGPUTextureAspect_All
     */
    WGPUTextureAspect aspect;
    /**
     * Defaults to @ref WGPUTextureUsage_None
     */
    WGPUTextureUsage usage;
} WGPUTextureViewDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureViewDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.dimension=*/WGPUTextureViewDimension_Undefined _wgpu_COMMA \
    /*.baseMipLevel=*/0 _wgpu_COMMA \
    /*.mipLevelCount=*/0 _wgpu_COMMA \
    /*.baseArrayLayer=*/0 _wgpu_COMMA \
    /*.arrayLayerCount=*/0 _wgpu_COMMA \
    /*.aspect=*/WGPUTextureAspect_All _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_None _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_VERTEX_ATTRIBUTE_INIT as initializer.
 */
typedef struct WGPUVertexAttribute {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUVertexFormat_Uint8
     */
    WGPUVertexFormat format;
    /**
     * Defaults to 0
     */
    uint64_t offset;
    /**
     * Defaults to 0
     */
    uint32_t shaderLocation;
} WGPUVertexAttribute WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_ATTRIBUTE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexAttribute, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUVertexFormat_Uint8 _wgpu_COMMA \
    /*.offset=*/0 _wgpu_COMMA \
    /*.shaderLocation=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BIND_GROUP_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUBindGroupDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    WGPUBindGroupLayout layout;
    /**
     * Defaults to NULL
     */
    size_t entryCount;
    WGPUBindGroupEntry const * entries;
} WGPUBindGroupDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.entryCount=*/0 _wgpu_COMMA \
    /*.entries=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT as initializer.
 */
typedef struct WGPUBindGroupLayoutEntry {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to 0
     */
    uint32_t binding;
    /**
     * Defaults to @ref WGPUShaderStage_None
     */
    WGPUShaderStage visibility;
    /**
     * Defaults to @ref WGPU_BUFFER_BINDING_LAYOUT_INIT
     */
    WGPUBufferBindingLayout buffer;
    /**
     * Defaults to @ref WGPU_SAMPLER_BINDING_LAYOUT_INIT
     */
    WGPUSamplerBindingLayout sampler;
    /**
     * Defaults to @ref WGPU_TEXTURE_BINDING_LAYOUT_INIT
     */
    WGPUTextureBindingLayout texture;
    /**
     * Defaults to @ref WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT
     */
    WGPUStorageTextureBindingLayout storageTexture;
} WGPUBindGroupLayoutEntry WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupLayoutEntry, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.binding=*/0 _wgpu_COMMA \
    /*.visibility=*/WGPUShaderStage_None _wgpu_COMMA \
    /*.buffer=*/WGPU_BUFFER_BINDING_LAYOUT_INIT _wgpu_COMMA \
    /*.sampler=*/WGPU_SAMPLER_BINDING_LAYOUT_INIT _wgpu_COMMA \
    /*.texture=*/WGPU_TEXTURE_BINDING_LAYOUT_INIT _wgpu_COMMA \
    /*.storageTexture=*/WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BLEND_STATE_INIT as initializer.
 */
typedef struct WGPUBlendState {
    /**
     * Defaults to @ref WGPU_BLEND_COMPONENT_INIT
     */
    WGPUBlendComponent color;
    /**
     * Defaults to @ref WGPU_BLEND_COMPONENT_INIT
     */
    WGPUBlendComponent alpha;
} WGPUBlendState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BLEND_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBlendState, { \
    /*.color=*/WGPU_BLEND_COMPONENT_INIT _wgpu_COMMA \
    /*.alpha=*/WGPU_BLEND_COMPONENT_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPILATION_INFO_INIT as initializer.
 */
typedef struct WGPUCompilationInfo {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    size_t messageCount;
    WGPUCompilationMessage const * messages;
} WGPUCompilationInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPILATION_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUCompilationInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.messageCount=*/0 _wgpu_COMMA \
    /*.messages=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPUTE_PASS_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUComputePassDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPU_COMPUTE_PASS_TIMESTAMP_WRITES_INIT
     */
    WGPUComputePassTimestampWrites timestampWrites;
} WGPUComputePassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_PASS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputePassDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.timestampWrites=*/WGPU_COMPUTE_PASS_TIMESTAMP_WRITES_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPUTE_STAGE_INIT as initializer.
 */
typedef struct WGPUComputeStage {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    WGPUShaderModule module;
    /**
     * This is a \ref NullableInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView entryPoint;
    /**
     * Defaults to NULL
     */
    size_t constantCount;
    WGPUConstantEntry const * constants;
} WGPUComputeStage WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_STAGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputeStage, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_DEPTH_STENCIL_STATE_INIT as initializer.
 */
typedef struct WGPUDepthStencilState {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * Defaults to @ref WGPUOptionalBool_Undefined
     */
    WGPUOptionalBool depthWriteEnabled;
    /**
     * Defaults to @ref WGPUCompareFunction_Undefined
     */
    WGPUCompareFunction depthCompare;
    /**
     * Defaults to @ref WGPU_STENCIL_FACE_STATE_INIT
     */
    WGPUStencilFaceState stencilFront;
    /**
     * Defaults to @ref WGPU_STENCIL_FACE_STATE_INIT
     */
    WGPUStencilFaceState stencilBack;
    /**
     * Defaults to 4294967295
     */
    uint32_t stencilReadMask;
    /**
     * Defaults to 4294967295
     */
    uint32_t stencilWriteMask;
    /**
     * Defaults to 0
     */
    int32_t depthBias;
    /**
     * Defaults to 0.f
     */
    float depthBiasSlopeScale;
    /**
     * Defaults to 0.f
     */
    float depthBiasClamp;
} WGPUDepthStencilState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEPTH_STENCIL_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDepthStencilState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.depthWriteEnabled=*/WGPUOptionalBool_Undefined _wgpu_COMMA \
    /*.depthCompare=*/WGPUCompareFunction_Undefined _wgpu_COMMA \
    /*.stencilFront=*/WGPU_STENCIL_FACE_STATE_INIT _wgpu_COMMA \
    /*.stencilBack=*/WGPU_STENCIL_FACE_STATE_INIT _wgpu_COMMA \
    /*.stencilReadMask=*/4294967295 _wgpu_COMMA \
    /*.stencilWriteMask=*/4294967295 _wgpu_COMMA \
    /*.depthBias=*/0 _wgpu_COMMA \
    /*.depthBiasSlopeScale=*/0.f _wgpu_COMMA \
    /*.depthBiasClamp=*/0.f _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_DEVICE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUDeviceDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    size_t requiredFeatureCount;
    WGPUFeatureName const * requiredFeatures;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPULimits const * requiredLimits;
    /**
     * Defaults to @ref WGPU_QUEUE_DESCRIPTOR_INIT
     */
    WGPUQueueDescriptor defaultQueue;
    /**
     * Defaults to @ref WGPU_DEVICE_LOST_CALLBACK_INFO_INIT
     */
    WGPUDeviceLostCallbackInfo deviceLostCallbackInfo;
    /**
     * Defaults to @ref WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT
     */
    WGPUUncapturedErrorCallbackInfo uncapturedErrorCallbackInfo;
} WGPUDeviceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_DEVICE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDeviceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.requiredFeatureCount=*/0 _wgpu_COMMA \
    /*.requiredFeatures=*/NULL _wgpu_COMMA \
    /*.requiredLimits=*/NULL _wgpu_COMMA \
    /*.defaultQueue=*/WGPU_QUEUE_DESCRIPTOR_INIT _wgpu_COMMA \
    /*.deviceLostCallbackInfo=*/WGPU_DEVICE_LOST_CALLBACK_INFO_INIT _wgpu_COMMA \
    /*.uncapturedErrorCallbackInfo=*/WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT _wgpu_COMMA \
})

/**
 * Struct holding a future to wait on, and a `completed` boolean flag.
 *
 * Default values can be set using WGPU_FUTURE_WAIT_INFO_INIT as initializer.
 */
typedef struct WGPUFutureWaitInfo {
    /**
     * The future to wait on.
     *
     * Defaults to @ref WGPU_FUTURE_INIT
     */
    WGPUFuture future;
    /**
     * Whether or not the future completed.
     *
     * Defaults to 0
     */
    WGPUBool completed;
} WGPUFutureWaitInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FUTURE_WAIT_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFutureWaitInfo, { \
    /*.future=*/WGPU_FUTURE_INIT _wgpu_COMMA \
    /*.completed=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_INSTANCE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUInstanceDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * Instance features to enable
     *
     * Defaults to @ref WGPU_INSTANCE_CAPABILITIES_INIT
     */
    WGPUInstanceCapabilities features;
} WGPUInstanceDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_INSTANCE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.features=*/WGPU_INSTANCE_CAPABILITIES_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT as initializer.
 */
typedef struct WGPURenderPassColorAttachment {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUTextureView view;
    /**
     * Defaults to @ref WGPU_DEPTH_SLICE_UNDEFINED
     */
    uint32_t depthSlice;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUTextureView resolveTarget;
    /**
     * Defaults to @ref WGPULoadOp_Undefined
     */
    WGPULoadOp loadOp;
    /**
     * Defaults to @ref WGPUStoreOp_Undefined
     */
    WGPUStoreOp storeOp;
    /**
     * Defaults to @ref WGPU_COLOR_INIT
     */
    WGPUColor clearValue;
} WGPURenderPassColorAttachment WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassColorAttachment, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.view=*/NULL _wgpu_COMMA \
    /*.depthSlice=*/WGPU_DEPTH_SLICE_UNDEFINED _wgpu_COMMA \
    /*.resolveTarget=*/NULL _wgpu_COMMA \
    /*.loadOp=*/WGPULoadOp_Undefined _wgpu_COMMA \
    /*.storeOp=*/WGPUStoreOp_Undefined _wgpu_COMMA \
    /*.clearValue=*/WGPU_COLOR_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXEL_COPY_BUFFER_INFO_INIT as initializer.
 */
typedef struct WGPUTexelCopyBufferInfo {
    /**
     * Defaults to @ref WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT
     */
    WGPUTexelCopyBufferLayout layout;
    /**
     * Defaults to NULL
     */
    WGPUBuffer buffer;
} WGPUTexelCopyBufferInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_BUFFER_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyBufferInfo, { \
    /*.layout=*/WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT _wgpu_COMMA \
    /*.buffer=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXEL_COPY_TEXTURE_INFO_INIT as initializer.
 */
typedef struct WGPUTexelCopyTextureInfo {
    /**
     * Defaults to NULL
     */
    WGPUTexture texture;
    /**
     * Defaults to 0
     */
    uint32_t mipLevel;
    /**
     * Defaults to @ref WGPU_ORIGIN_3D_INIT
     */
    WGPUOrigin3D origin;
    /**
     * Defaults to @ref WGPUTextureAspect_All
     */
    WGPUTextureAspect aspect;
} WGPUTexelCopyTextureInfo WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXEL_COPY_TEXTURE_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTexelCopyTextureInfo, { \
    /*.texture=*/NULL _wgpu_COMMA \
    /*.mipLevel=*/0 _wgpu_COMMA \
    /*.origin=*/WGPU_ORIGIN_3D_INIT _wgpu_COMMA \
    /*.aspect=*/WGPUTextureAspect_All _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_TEXTURE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUTextureDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to @ref WGPUTextureUsage_None
     */
    WGPUTextureUsage usage;
    /**
     * Defaults to @ref WGPUTextureDimension_2D
     */
    WGPUTextureDimension dimension;
    /**
     * Defaults to @ref WGPU_EXTENT_3D_INIT
     */
    WGPUExtent3D size;
    /**
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * Defaults to 1
     */
    uint32_t mipLevelCount;
    /**
     * Defaults to 1
     */
    uint32_t sampleCount;
    /**
     * Defaults to NULL
     */
    size_t viewFormatCount;
    WGPUTextureFormat const * viewFormats;
} WGPUTextureDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_TEXTURE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUTextureDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.usage=*/WGPUTextureUsage_None _wgpu_COMMA \
    /*.dimension=*/WGPUTextureDimension_2D _wgpu_COMMA \
    /*.size=*/WGPU_EXTENT_3D_INIT _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.mipLevelCount=*/1 _wgpu_COMMA \
    /*.sampleCount=*/1 _wgpu_COMMA \
    /*.viewFormatCount=*/0 _wgpu_COMMA \
    /*.viewFormats=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_VERTEX_BUFFER_LAYOUT_INIT as initializer.
 */
typedef struct WGPUVertexBufferLayout {
    WGPUChainedStruct const * nextInChain;
    /**
     * The step mode for the vertex buffer. If @ref WGPUVertexStepMode_VertexBufferNotUsed,
     * indicates a "hole" in the parent @ref WGPUVertexState `buffers` array:
     * the pipeline does not use a vertex buffer at this `location`.
     *
     * Defaults to @ref WGPUVertexStepMode_VertexBufferNotUsed
     */
    WGPUVertexStepMode stepMode;
    /**
     * Defaults to 0
     */
    uint64_t arrayStride;
    /**
     * Defaults to NULL
     */
    size_t attributeCount;
    WGPUVertexAttribute const * attributes;
} WGPUVertexBufferLayout WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_BUFFER_LAYOUT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexBufferLayout, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.stepMode=*/WGPUVertexStepMode_VertexBufferNotUsed _wgpu_COMMA \
    /*.arrayStride=*/0 _wgpu_COMMA \
    /*.attributeCount=*/0 _wgpu_COMMA \
    /*.attributes=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUBindGroupLayoutDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    size_t entryCount;
    WGPUBindGroupLayoutEntry const * entries;
} WGPUBindGroupLayoutDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupLayoutDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.entryCount=*/0 _wgpu_COMMA \
    /*.entries=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COLOR_TARGET_STATE_INIT as initializer.
 */
typedef struct WGPUColorTargetState {
    WGPUChainedStruct const * nextInChain;
    /**
     * The texture format of the target. If @ref WGPUTextureFormat_Undefined,
     * indicates a "hole" in the parent @ref WGPUFragmentState `targets` array:
     * the pipeline does not output a value at this `location`.
     *
     * Defaults to @ref WGPUTextureFormat_Undefined
     */
    WGPUTextureFormat format;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUBlendState const * blend;
    /**
     * Defaults to @ref WGPUColorWriteMask_None
     */
    WGPUColorWriteMask writeMask;
} WGPUColorTargetState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COLOR_TARGET_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUColorTargetState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.format=*/WGPUTextureFormat_Undefined _wgpu_COMMA \
    /*.blend=*/NULL _wgpu_COMMA \
    /*.writeMask=*/WGPUColorWriteMask_None _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_COMPUTE_PIPELINE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPUComputePipelineDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUPipelineLayout layout;
    /**
     * Defaults to @ref WGPU_COMPUTE_STAGE_INIT
     */
    WGPUComputeStage compute;
} WGPUComputePipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_COMPUTE_PIPELINE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPUComputePipelineDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.compute=*/WGPU_COMPUTE_STAGE_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PASS_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPURenderPassDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    size_t colorAttachmentCount;
    WGPURenderPassColorAttachment const * colorAttachments;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPURenderPassDepthStencilAttachment const * depthStencilAttachment;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUQuerySet occlusionQuerySet;
    /**
     * Defaults to @ref WGPU_RENDER_PASS_TIMESTAMP_WRITES_INIT
     */
    WGPURenderPassTimestampWrites timestampWrites;
} WGPURenderPassDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PASS_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPassDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.colorAttachmentCount=*/0 _wgpu_COMMA \
    /*.colorAttachments=*/NULL _wgpu_COMMA \
    /*.depthStencilAttachment=*/NULL _wgpu_COMMA \
    /*.occlusionQuerySet=*/NULL _wgpu_COMMA \
    /*.timestampWrites=*/WGPU_RENDER_PASS_TIMESTAMP_WRITES_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_VERTEX_STATE_INIT as initializer.
 */
typedef struct WGPUVertexState {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    WGPUShaderModule module;
    /**
     * This is a \ref NullableInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView entryPoint;
    /**
     * Defaults to NULL
     */
    size_t constantCount;
    WGPUConstantEntry const * constants;
    /**
     * Defaults to NULL
     */
    size_t bufferCount;
    WGPUVertexBufferLayout const * buffers;
} WGPUVertexState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_VERTEX_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUVertexState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
    /*.bufferCount=*/0 _wgpu_COMMA \
    /*.buffers=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_FRAGMENT_STATE_INIT as initializer.
 */
typedef struct WGPUFragmentState {
    WGPUChainedStruct const * nextInChain;
    /**
     * Defaults to NULL
     */
    WGPUShaderModule module;
    /**
     * This is a \ref NullableInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView entryPoint;
    /**
     * Defaults to NULL
     */
    size_t constantCount;
    WGPUConstantEntry const * constants;
    /**
     * Defaults to NULL
     */
    size_t targetCount;
    WGPUColorTargetState const * targets;
} WGPUFragmentState WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_FRAGMENT_STATE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUFragmentState, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.module=*/NULL _wgpu_COMMA \
    /*.entryPoint=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.constantCount=*/0 _wgpu_COMMA \
    /*.constants=*/NULL _wgpu_COMMA \
    /*.targetCount=*/0 _wgpu_COMMA \
    /*.targets=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT as initializer.
 */
typedef struct WGPURenderPipelineDescriptor {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * Defaults to @ref WGPU_STRING_VIEW_INIT
     */
    WGPUStringView label;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUPipelineLayout layout;
    /**
     * Defaults to @ref WGPU_VERTEX_STATE_INIT
     */
    WGPUVertexState vertex;
    /**
     * Defaults to @ref WGPU_PRIMITIVE_STATE_INIT
     */
    WGPUPrimitiveState primitive;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUDepthStencilState const * depthStencil;
    /**
     * Defaults to @ref WGPU_MULTISAMPLE_STATE_INIT
     */
    WGPUMultisampleState multisample;
    /**
     * Defaults to NULL
     */
    WGPU_NULLABLE WGPUFragmentState const * fragment;
} WGPURenderPipelineDescriptor WGPU_STRUCTURE_ATTRIBUTE;

#define WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT _wgpu_MAKE_INIT_STRUCT(WGPURenderPipelineDescriptor, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.label=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.layout=*/NULL _wgpu_COMMA \
    /*.vertex=*/WGPU_VERTEX_STATE_INIT _wgpu_COMMA \
    /*.primitive=*/WGPU_PRIMITIVE_STATE_INIT _wgpu_COMMA \
    /*.depthStencil=*/NULL _wgpu_COMMA \
    /*.multisample=*/WGPU_MULTISAMPLE_STATE_INIT _wgpu_COMMA \
    /*.fragment=*/NULL _wgpu_COMMA \
})

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WGPU_SKIP_PROCS)

/**
 * Proc pointer type for @ref wgpuCreateInstance:
 * > @copydoc wgpuCreateInstance
 */
typedef WGPUInstance (*WGPUProcCreateInstance)(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuGetInstanceCapabilities:
 * > @copydoc wgpuGetInstanceCapabilities
 */
typedef WGPUStatus (*WGPUProcGetInstanceCapabilities)(WGPUInstanceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuGetProcAddress:
 * > @copydoc wgpuGetProcAddress
 */
typedef WGPUProc (*WGPUProcGetProcAddress)(WGPUStringView procName) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Adapter
/**
 * Proc pointer type for @ref wgpuAdapterGetFeatures:
 * > @copydoc wgpuAdapterGetFeatures
 */
typedef void (*WGPUProcAdapterGetFeatures)(WGPUAdapter adapter, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterGetInfo:
 * > @copydoc wgpuAdapterGetInfo
 */
typedef WGPUStatus (*WGPUProcAdapterGetInfo)(WGPUAdapter adapter, WGPUAdapterInfo * info) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterGetLimits:
 * > @copydoc wgpuAdapterGetLimits
 */
typedef WGPUStatus (*WGPUProcAdapterGetLimits)(WGPUAdapter adapter, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterHasFeature:
 * > @copydoc wgpuAdapterHasFeature
 */
typedef WGPUBool (*WGPUProcAdapterHasFeature)(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterRequestDevice:
 * > @copydoc wgpuAdapterRequestDevice
 */
typedef WGPUFuture (*WGPUProcAdapterRequestDevice)(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterAddRef.
 * > @copydoc wgpuAdapterAddRef
 */
typedef void (*WGPUProcAdapterAddRef)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuAdapterRelease.
 * > @copydoc wgpuAdapterRelease
 */
typedef void (*WGPUProcAdapterRelease)(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;

// Procs of AdapterInfo
/**
 * Proc pointer type for @ref wgpuAdapterInfoFreeMembers:
 * > @copydoc wgpuAdapterInfoFreeMembers
 */
typedef void (*WGPUProcAdapterInfoFreeMembers)(WGPUAdapterInfo adapterInfo) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroup
/**
 * Proc pointer type for @ref wgpuBindGroupSetLabel:
 * > @copydoc wgpuBindGroupSetLabel
 */
typedef void (*WGPUProcBindGroupSetLabel)(WGPUBindGroup bindGroup, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBindGroupAddRef.
 * > @copydoc wgpuBindGroupAddRef
 */
typedef void (*WGPUProcBindGroupAddRef)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBindGroupRelease.
 * > @copydoc wgpuBindGroupRelease
 */
typedef void (*WGPUProcBindGroupRelease)(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;

// Procs of BindGroupLayout
/**
 * Proc pointer type for @ref wgpuBindGroupLayoutSetLabel:
 * > @copydoc wgpuBindGroupLayoutSetLabel
 */
typedef void (*WGPUProcBindGroupLayoutSetLabel)(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBindGroupLayoutAddRef.
 * > @copydoc wgpuBindGroupLayoutAddRef
 */
typedef void (*WGPUProcBindGroupLayoutAddRef)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBindGroupLayoutRelease.
 * > @copydoc wgpuBindGroupLayoutRelease
 */
typedef void (*WGPUProcBindGroupLayoutRelease)(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Buffer
/**
 * Proc pointer type for @ref wgpuBufferDestroy:
 * > @copydoc wgpuBufferDestroy
 */
typedef void (*WGPUProcBufferDestroy)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferGetConstMappedRange:
 * > @copydoc wgpuBufferGetConstMappedRange
 */
typedef void const * (*WGPUProcBufferGetConstMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferGetMapState:
 * > @copydoc wgpuBufferGetMapState
 */
typedef WGPUBufferMapState (*WGPUProcBufferGetMapState)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferGetMappedRange:
 * > @copydoc wgpuBufferGetMappedRange
 */
typedef void * (*WGPUProcBufferGetMappedRange)(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferGetSize:
 * > @copydoc wgpuBufferGetSize
 */
typedef uint64_t (*WGPUProcBufferGetSize)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferGetUsage:
 * > @copydoc wgpuBufferGetUsage
 */
typedef WGPUBufferUsage (*WGPUProcBufferGetUsage)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferMapAsync:
 * > @copydoc wgpuBufferMapAsync
 */
typedef WGPUFuture (*WGPUProcBufferMapAsync)(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferSetLabel:
 * > @copydoc wgpuBufferSetLabel
 */
typedef void (*WGPUProcBufferSetLabel)(WGPUBuffer buffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferUnmap:
 * > @copydoc wgpuBufferUnmap
 */
typedef void (*WGPUProcBufferUnmap)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferAddRef.
 * > @copydoc wgpuBufferAddRef
 */
typedef void (*WGPUProcBufferAddRef)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuBufferRelease.
 * > @copydoc wgpuBufferRelease
 */
typedef void (*WGPUProcBufferRelease)(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandBuffer
/**
 * Proc pointer type for @ref wgpuCommandBufferSetLabel:
 * > @copydoc wgpuCommandBufferSetLabel
 */
typedef void (*WGPUProcCommandBufferSetLabel)(WGPUCommandBuffer commandBuffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandBufferAddRef.
 * > @copydoc wgpuCommandBufferAddRef
 */
typedef void (*WGPUProcCommandBufferAddRef)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandBufferRelease.
 * > @copydoc wgpuCommandBufferRelease
 */
typedef void (*WGPUProcCommandBufferRelease)(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;

// Procs of CommandEncoder
/**
 * Proc pointer type for @ref wgpuCommandEncoderBeginComputePass:
 * > @copydoc wgpuCommandEncoderBeginComputePass
 */
typedef WGPUComputePassEncoder (*WGPUProcCommandEncoderBeginComputePass)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderBeginRenderPass:
 * > @copydoc wgpuCommandEncoderBeginRenderPass
 */
typedef WGPURenderPassEncoder (*WGPUProcCommandEncoderBeginRenderPass)(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderClearBuffer:
 * > @copydoc wgpuCommandEncoderClearBuffer
 */
typedef void (*WGPUProcCommandEncoderClearBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderCopyBufferToBuffer:
 * > @copydoc wgpuCommandEncoderCopyBufferToBuffer
 */
typedef void (*WGPUProcCommandEncoderCopyBufferToBuffer)(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderCopyBufferToTexture:
 * > @copydoc wgpuCommandEncoderCopyBufferToTexture
 */
typedef void (*WGPUProcCommandEncoderCopyBufferToTexture)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderCopyTextureToBuffer:
 * > @copydoc wgpuCommandEncoderCopyTextureToBuffer
 */
typedef void (*WGPUProcCommandEncoderCopyTextureToBuffer)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderCopyTextureToTexture:
 * > @copydoc wgpuCommandEncoderCopyTextureToTexture
 */
typedef void (*WGPUProcCommandEncoderCopyTextureToTexture)(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderFinish:
 * > @copydoc wgpuCommandEncoderFinish
 */
typedef WGPUCommandBuffer (*WGPUProcCommandEncoderFinish)(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderInsertDebugMarker:
 * > @copydoc wgpuCommandEncoderInsertDebugMarker
 */
typedef void (*WGPUProcCommandEncoderInsertDebugMarker)(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderPopDebugGroup:
 * > @copydoc wgpuCommandEncoderPopDebugGroup
 */
typedef void (*WGPUProcCommandEncoderPopDebugGroup)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderPushDebugGroup:
 * > @copydoc wgpuCommandEncoderPushDebugGroup
 */
typedef void (*WGPUProcCommandEncoderPushDebugGroup)(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderResolveQuerySet:
 * > @copydoc wgpuCommandEncoderResolveQuerySet
 */
typedef void (*WGPUProcCommandEncoderResolveQuerySet)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderSetLabel:
 * > @copydoc wgpuCommandEncoderSetLabel
 */
typedef void (*WGPUProcCommandEncoderSetLabel)(WGPUCommandEncoder commandEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderWriteTimestamp:
 * > @copydoc wgpuCommandEncoderWriteTimestamp
 */
typedef void (*WGPUProcCommandEncoderWriteTimestamp)(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderAddRef.
 * > @copydoc wgpuCommandEncoderAddRef
 */
typedef void (*WGPUProcCommandEncoderAddRef)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuCommandEncoderRelease.
 * > @copydoc wgpuCommandEncoderRelease
 */
typedef void (*WGPUProcCommandEncoderRelease)(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePassEncoder
/**
 * Proc pointer type for @ref wgpuComputePassEncoderDispatchWorkgroups:
 * > @copydoc wgpuComputePassEncoderDispatchWorkgroups
 */
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroups)(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderDispatchWorkgroupsIndirect:
 * > @copydoc wgpuComputePassEncoderDispatchWorkgroupsIndirect
 */
typedef void (*WGPUProcComputePassEncoderDispatchWorkgroupsIndirect)(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderEnd:
 * > @copydoc wgpuComputePassEncoderEnd
 */
typedef void (*WGPUProcComputePassEncoderEnd)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderInsertDebugMarker:
 * > @copydoc wgpuComputePassEncoderInsertDebugMarker
 */
typedef void (*WGPUProcComputePassEncoderInsertDebugMarker)(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderPopDebugGroup:
 * > @copydoc wgpuComputePassEncoderPopDebugGroup
 */
typedef void (*WGPUProcComputePassEncoderPopDebugGroup)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderPushDebugGroup:
 * > @copydoc wgpuComputePassEncoderPushDebugGroup
 */
typedef void (*WGPUProcComputePassEncoderPushDebugGroup)(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderSetBindGroup:
 * > @copydoc wgpuComputePassEncoderSetBindGroup
 */
typedef void (*WGPUProcComputePassEncoderSetBindGroup)(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderSetLabel:
 * > @copydoc wgpuComputePassEncoderSetLabel
 */
typedef void (*WGPUProcComputePassEncoderSetLabel)(WGPUComputePassEncoder computePassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderSetPipeline:
 * > @copydoc wgpuComputePassEncoderSetPipeline
 */
typedef void (*WGPUProcComputePassEncoderSetPipeline)(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderAddRef.
 * > @copydoc wgpuComputePassEncoderAddRef
 */
typedef void (*WGPUProcComputePassEncoderAddRef)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderRelease.
 * > @copydoc wgpuComputePassEncoderRelease
 */
typedef void (*WGPUProcComputePassEncoderRelease)(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ComputePipeline
/**
 * Proc pointer type for @ref wgpuComputePipelineGetBindGroupLayout:
 * > @copydoc wgpuComputePipelineGetBindGroupLayout
 */
typedef WGPUBindGroupLayout (*WGPUProcComputePipelineGetBindGroupLayout)(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePipelineSetLabel:
 * > @copydoc wgpuComputePipelineSetLabel
 */
typedef void (*WGPUProcComputePipelineSetLabel)(WGPUComputePipeline computePipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePipelineAddRef.
 * > @copydoc wgpuComputePipelineAddRef
 */
typedef void (*WGPUProcComputePipelineAddRef)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePipelineRelease.
 * > @copydoc wgpuComputePipelineRelease
 */
typedef void (*WGPUProcComputePipelineRelease)(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Device
/**
 * Proc pointer type for @ref wgpuDeviceCreateBindGroup:
 * > @copydoc wgpuDeviceCreateBindGroup
 */
typedef WGPUBindGroup (*WGPUProcDeviceCreateBindGroup)(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateBindGroupLayout:
 * > @copydoc wgpuDeviceCreateBindGroupLayout
 */
typedef WGPUBindGroupLayout (*WGPUProcDeviceCreateBindGroupLayout)(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateBuffer:
 * > @copydoc wgpuDeviceCreateBuffer
 */
typedef WGPUBuffer (*WGPUProcDeviceCreateBuffer)(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateCommandEncoder:
 * > @copydoc wgpuDeviceCreateCommandEncoder
 */
typedef WGPUCommandEncoder (*WGPUProcDeviceCreateCommandEncoder)(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateComputePipeline:
 * > @copydoc wgpuDeviceCreateComputePipeline
 */
typedef WGPUComputePipeline (*WGPUProcDeviceCreateComputePipeline)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateComputePipelineAsync:
 * > @copydoc wgpuDeviceCreateComputePipelineAsync
 */
typedef WGPUFuture (*WGPUProcDeviceCreateComputePipelineAsync)(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreatePipelineLayout:
 * > @copydoc wgpuDeviceCreatePipelineLayout
 */
typedef WGPUPipelineLayout (*WGPUProcDeviceCreatePipelineLayout)(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateQuerySet:
 * > @copydoc wgpuDeviceCreateQuerySet
 */
typedef WGPUQuerySet (*WGPUProcDeviceCreateQuerySet)(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateRenderBundleEncoder:
 * > @copydoc wgpuDeviceCreateRenderBundleEncoder
 */
typedef WGPURenderBundleEncoder (*WGPUProcDeviceCreateRenderBundleEncoder)(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateRenderPipeline:
 * > @copydoc wgpuDeviceCreateRenderPipeline
 */
typedef WGPURenderPipeline (*WGPUProcDeviceCreateRenderPipeline)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateRenderPipelineAsync:
 * > @copydoc wgpuDeviceCreateRenderPipelineAsync
 */
typedef WGPUFuture (*WGPUProcDeviceCreateRenderPipelineAsync)(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateSampler:
 * > @copydoc wgpuDeviceCreateSampler
 */
typedef WGPUSampler (*WGPUProcDeviceCreateSampler)(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateShaderModule:
 * > @copydoc wgpuDeviceCreateShaderModule
 */
typedef WGPUShaderModule (*WGPUProcDeviceCreateShaderModule)(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceCreateTexture:
 * > @copydoc wgpuDeviceCreateTexture
 */
typedef WGPUTexture (*WGPUProcDeviceCreateTexture)(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceDestroy:
 * > @copydoc wgpuDeviceDestroy
 */
typedef void (*WGPUProcDeviceDestroy)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceGetAdapterInfo:
 * > @copydoc wgpuDeviceGetAdapterInfo
 */
typedef WGPUStatus (*WGPUProcDeviceGetAdapterInfo)(WGPUDevice device, WGPUAdapterInfo * adapterInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceGetFeatures:
 * > @copydoc wgpuDeviceGetFeatures
 */
typedef void (*WGPUProcDeviceGetFeatures)(WGPUDevice device, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceGetLimits:
 * > @copydoc wgpuDeviceGetLimits
 */
typedef WGPUStatus (*WGPUProcDeviceGetLimits)(WGPUDevice device, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceGetLostFuture:
 * > @copydoc wgpuDeviceGetLostFuture
 */
typedef WGPUFuture (*WGPUProcDeviceGetLostFuture)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceGetQueue:
 * > @copydoc wgpuDeviceGetQueue
 */
typedef WGPUQueue (*WGPUProcDeviceGetQueue)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceHasFeature:
 * > @copydoc wgpuDeviceHasFeature
 */
typedef WGPUBool (*WGPUProcDeviceHasFeature)(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDevicePopErrorScope:
 * > @copydoc wgpuDevicePopErrorScope
 */
typedef WGPUFuture (*WGPUProcDevicePopErrorScope)(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDevicePushErrorScope:
 * > @copydoc wgpuDevicePushErrorScope
 */
typedef void (*WGPUProcDevicePushErrorScope)(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceSetLabel:
 * > @copydoc wgpuDeviceSetLabel
 */
typedef void (*WGPUProcDeviceSetLabel)(WGPUDevice device, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceAddRef.
 * > @copydoc wgpuDeviceAddRef
 */
typedef void (*WGPUProcDeviceAddRef)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuDeviceRelease.
 * > @copydoc wgpuDeviceRelease
 */
typedef void (*WGPUProcDeviceRelease)(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Instance
/**
 * Proc pointer type for @ref wgpuInstanceCreateSurface:
 * > @copydoc wgpuInstanceCreateSurface
 */
typedef WGPUSurface (*WGPUProcInstanceCreateSurface)(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceGetWGSLLanguageFeatures:
 * > @copydoc wgpuInstanceGetWGSLLanguageFeatures
 */
typedef WGPUStatus (*WGPUProcInstanceGetWGSLLanguageFeatures)(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceHasWGSLLanguageFeature:
 * > @copydoc wgpuInstanceHasWGSLLanguageFeature
 */
typedef WGPUBool (*WGPUProcInstanceHasWGSLLanguageFeature)(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceProcessEvents:
 * > @copydoc wgpuInstanceProcessEvents
 */
typedef void (*WGPUProcInstanceProcessEvents)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceRequestAdapter:
 * > @copydoc wgpuInstanceRequestAdapter
 */
typedef WGPUFuture (*WGPUProcInstanceRequestAdapter)(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceWaitAny:
 * > @copydoc wgpuInstanceWaitAny
 */
typedef WGPUWaitStatus (*WGPUProcInstanceWaitAny)(WGPUInstance instance, size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo * futures, uint64_t timeoutNS) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceAddRef.
 * > @copydoc wgpuInstanceAddRef
 */
typedef void (*WGPUProcInstanceAddRef)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceRelease.
 * > @copydoc wgpuInstanceRelease
 */
typedef void (*WGPUProcInstanceRelease)(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;

// Procs of PipelineLayout
/**
 * Proc pointer type for @ref wgpuPipelineLayoutSetLabel:
 * > @copydoc wgpuPipelineLayoutSetLabel
 */
typedef void (*WGPUProcPipelineLayoutSetLabel)(WGPUPipelineLayout pipelineLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuPipelineLayoutAddRef.
 * > @copydoc wgpuPipelineLayoutAddRef
 */
typedef void (*WGPUProcPipelineLayoutAddRef)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuPipelineLayoutRelease.
 * > @copydoc wgpuPipelineLayoutRelease
 */
typedef void (*WGPUProcPipelineLayoutRelease)(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;

// Procs of QuerySet
/**
 * Proc pointer type for @ref wgpuQuerySetDestroy:
 * > @copydoc wgpuQuerySetDestroy
 */
typedef void (*WGPUProcQuerySetDestroy)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQuerySetGetCount:
 * > @copydoc wgpuQuerySetGetCount
 */
typedef uint32_t (*WGPUProcQuerySetGetCount)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQuerySetGetType:
 * > @copydoc wgpuQuerySetGetType
 */
typedef WGPUQueryType (*WGPUProcQuerySetGetType)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQuerySetSetLabel:
 * > @copydoc wgpuQuerySetSetLabel
 */
typedef void (*WGPUProcQuerySetSetLabel)(WGPUQuerySet querySet, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQuerySetAddRef.
 * > @copydoc wgpuQuerySetAddRef
 */
typedef void (*WGPUProcQuerySetAddRef)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQuerySetRelease.
 * > @copydoc wgpuQuerySetRelease
 */
typedef void (*WGPUProcQuerySetRelease)(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Queue
/**
 * Proc pointer type for @ref wgpuQueueOnSubmittedWorkDone:
 * > @copydoc wgpuQueueOnSubmittedWorkDone
 */
typedef WGPUFuture (*WGPUProcQueueOnSubmittedWorkDone)(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueSetLabel:
 * > @copydoc wgpuQueueSetLabel
 */
typedef void (*WGPUProcQueueSetLabel)(WGPUQueue queue, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueSubmit:
 * > @copydoc wgpuQueueSubmit
 */
typedef void (*WGPUProcQueueSubmit)(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueWriteBuffer:
 * > @copydoc wgpuQueueWriteBuffer
 */
typedef void (*WGPUProcQueueWriteBuffer)(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueWriteTexture:
 * > @copydoc wgpuQueueWriteTexture
 */
typedef void (*WGPUProcQueueWriteTexture)(WGPUQueue queue, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueAddRef.
 * > @copydoc wgpuQueueAddRef
 */
typedef void (*WGPUProcQueueAddRef)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuQueueRelease.
 * > @copydoc wgpuQueueRelease
 */
typedef void (*WGPUProcQueueRelease)(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundle
/**
 * Proc pointer type for @ref wgpuRenderBundleSetLabel:
 * > @copydoc wgpuRenderBundleSetLabel
 */
typedef void (*WGPUProcRenderBundleSetLabel)(WGPURenderBundle renderBundle, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleAddRef.
 * > @copydoc wgpuRenderBundleAddRef
 */
typedef void (*WGPUProcRenderBundleAddRef)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleRelease.
 * > @copydoc wgpuRenderBundleRelease
 */
typedef void (*WGPUProcRenderBundleRelease)(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderBundleEncoder
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderDraw:
 * > @copydoc wgpuRenderBundleEncoderDraw
 */
typedef void (*WGPUProcRenderBundleEncoderDraw)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderDrawIndexed:
 * > @copydoc wgpuRenderBundleEncoderDrawIndexed
 */
typedef void (*WGPUProcRenderBundleEncoderDrawIndexed)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderDrawIndexedIndirect:
 * > @copydoc wgpuRenderBundleEncoderDrawIndexedIndirect
 */
typedef void (*WGPUProcRenderBundleEncoderDrawIndexedIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderDrawIndirect:
 * > @copydoc wgpuRenderBundleEncoderDrawIndirect
 */
typedef void (*WGPUProcRenderBundleEncoderDrawIndirect)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderFinish:
 * > @copydoc wgpuRenderBundleEncoderFinish
 */
typedef WGPURenderBundle (*WGPUProcRenderBundleEncoderFinish)(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderInsertDebugMarker:
 * > @copydoc wgpuRenderBundleEncoderInsertDebugMarker
 */
typedef void (*WGPUProcRenderBundleEncoderInsertDebugMarker)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderPopDebugGroup:
 * > @copydoc wgpuRenderBundleEncoderPopDebugGroup
 */
typedef void (*WGPUProcRenderBundleEncoderPopDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderPushDebugGroup:
 * > @copydoc wgpuRenderBundleEncoderPushDebugGroup
 */
typedef void (*WGPUProcRenderBundleEncoderPushDebugGroup)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderSetBindGroup:
 * > @copydoc wgpuRenderBundleEncoderSetBindGroup
 */
typedef void (*WGPUProcRenderBundleEncoderSetBindGroup)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderSetIndexBuffer:
 * > @copydoc wgpuRenderBundleEncoderSetIndexBuffer
 */
typedef void (*WGPUProcRenderBundleEncoderSetIndexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderSetLabel:
 * > @copydoc wgpuRenderBundleEncoderSetLabel
 */
typedef void (*WGPUProcRenderBundleEncoderSetLabel)(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderSetPipeline:
 * > @copydoc wgpuRenderBundleEncoderSetPipeline
 */
typedef void (*WGPUProcRenderBundleEncoderSetPipeline)(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderSetVertexBuffer:
 * > @copydoc wgpuRenderBundleEncoderSetVertexBuffer
 */
typedef void (*WGPUProcRenderBundleEncoderSetVertexBuffer)(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderAddRef.
 * > @copydoc wgpuRenderBundleEncoderAddRef
 */
typedef void (*WGPUProcRenderBundleEncoderAddRef)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderBundleEncoderRelease.
 * > @copydoc wgpuRenderBundleEncoderRelease
 */
typedef void (*WGPUProcRenderBundleEncoderRelease)(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPassEncoder
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderBeginOcclusionQuery:
 * > @copydoc wgpuRenderPassEncoderBeginOcclusionQuery
 */
typedef void (*WGPUProcRenderPassEncoderBeginOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderDraw:
 * > @copydoc wgpuRenderPassEncoderDraw
 */
typedef void (*WGPUProcRenderPassEncoderDraw)(WGPURenderPassEncoder renderPassEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderDrawIndexed:
 * > @copydoc wgpuRenderPassEncoderDrawIndexed
 */
typedef void (*WGPUProcRenderPassEncoderDrawIndexed)(WGPURenderPassEncoder renderPassEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderDrawIndexedIndirect:
 * > @copydoc wgpuRenderPassEncoderDrawIndexedIndirect
 */
typedef void (*WGPUProcRenderPassEncoderDrawIndexedIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderDrawIndirect:
 * > @copydoc wgpuRenderPassEncoderDrawIndirect
 */
typedef void (*WGPUProcRenderPassEncoderDrawIndirect)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderEnd:
 * > @copydoc wgpuRenderPassEncoderEnd
 */
typedef void (*WGPUProcRenderPassEncoderEnd)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderEndOcclusionQuery:
 * > @copydoc wgpuRenderPassEncoderEndOcclusionQuery
 */
typedef void (*WGPUProcRenderPassEncoderEndOcclusionQuery)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExecuteBundles:
 * > @copydoc wgpuRenderPassEncoderExecuteBundles
 */
typedef void (*WGPUProcRenderPassEncoderExecuteBundles)(WGPURenderPassEncoder renderPassEncoder, size_t bundleCount, WGPURenderBundle const * bundles) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderInsertDebugMarker:
 * > @copydoc wgpuRenderPassEncoderInsertDebugMarker
 */
typedef void (*WGPUProcRenderPassEncoderInsertDebugMarker)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderPopDebugGroup:
 * > @copydoc wgpuRenderPassEncoderPopDebugGroup
 */
typedef void (*WGPUProcRenderPassEncoderPopDebugGroup)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderPushDebugGroup:
 * > @copydoc wgpuRenderPassEncoderPushDebugGroup
 */
typedef void (*WGPUProcRenderPassEncoderPushDebugGroup)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetBindGroup:
 * > @copydoc wgpuRenderPassEncoderSetBindGroup
 */
typedef void (*WGPUProcRenderPassEncoderSetBindGroup)(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetBlendConstant:
 * > @copydoc wgpuRenderPassEncoderSetBlendConstant
 */
typedef void (*WGPUProcRenderPassEncoderSetBlendConstant)(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetIndexBuffer:
 * > @copydoc wgpuRenderPassEncoderSetIndexBuffer
 */
typedef void (*WGPUProcRenderPassEncoderSetIndexBuffer)(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetLabel:
 * > @copydoc wgpuRenderPassEncoderSetLabel
 */
typedef void (*WGPUProcRenderPassEncoderSetLabel)(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetPipeline:
 * > @copydoc wgpuRenderPassEncoderSetPipeline
 */
typedef void (*WGPUProcRenderPassEncoderSetPipeline)(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetScissorRect:
 * > @copydoc wgpuRenderPassEncoderSetScissorRect
 */
typedef void (*WGPUProcRenderPassEncoderSetScissorRect)(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetStencilReference:
 * > @copydoc wgpuRenderPassEncoderSetStencilReference
 */
typedef void (*WGPUProcRenderPassEncoderSetStencilReference)(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetVertexBuffer:
 * > @copydoc wgpuRenderPassEncoderSetVertexBuffer
 */
typedef void (*WGPUProcRenderPassEncoderSetVertexBuffer)(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetViewport:
 * > @copydoc wgpuRenderPassEncoderSetViewport
 */
typedef void (*WGPUProcRenderPassEncoderSetViewport)(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderAddRef.
 * > @copydoc wgpuRenderPassEncoderAddRef
 */
typedef void (*WGPUProcRenderPassEncoderAddRef)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderRelease.
 * > @copydoc wgpuRenderPassEncoderRelease
 */
typedef void (*WGPUProcRenderPassEncoderRelease)(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPipeline
/**
 * Proc pointer type for @ref wgpuRenderPipelineGetBindGroupLayout:
 * > @copydoc wgpuRenderPipelineGetBindGroupLayout
 */
typedef WGPUBindGroupLayout (*WGPUProcRenderPipelineGetBindGroupLayout)(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPipelineSetLabel:
 * > @copydoc wgpuRenderPipelineSetLabel
 */
typedef void (*WGPUProcRenderPipelineSetLabel)(WGPURenderPipeline renderPipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPipelineAddRef.
 * > @copydoc wgpuRenderPipelineAddRef
 */
typedef void (*WGPUProcRenderPipelineAddRef)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPipelineRelease.
 * > @copydoc wgpuRenderPipelineRelease
 */
typedef void (*WGPUProcRenderPipelineRelease)(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Sampler
/**
 * Proc pointer type for @ref wgpuSamplerSetLabel:
 * > @copydoc wgpuSamplerSetLabel
 */
typedef void (*WGPUProcSamplerSetLabel)(WGPUSampler sampler, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSamplerAddRef.
 * > @copydoc wgpuSamplerAddRef
 */
typedef void (*WGPUProcSamplerAddRef)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSamplerRelease.
 * > @copydoc wgpuSamplerRelease
 */
typedef void (*WGPUProcSamplerRelease)(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;

// Procs of ShaderModule
/**
 * Proc pointer type for @ref wgpuShaderModuleGetCompilationInfo:
 * > @copydoc wgpuShaderModuleGetCompilationInfo
 */
typedef WGPUFuture (*WGPUProcShaderModuleGetCompilationInfo)(WGPUShaderModule shaderModule, WGPUCompilationInfoCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuShaderModuleSetLabel:
 * > @copydoc wgpuShaderModuleSetLabel
 */
typedef void (*WGPUProcShaderModuleSetLabel)(WGPUShaderModule shaderModule, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuShaderModuleAddRef.
 * > @copydoc wgpuShaderModuleAddRef
 */
typedef void (*WGPUProcShaderModuleAddRef)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuShaderModuleRelease.
 * > @copydoc wgpuShaderModuleRelease
 */
typedef void (*WGPUProcShaderModuleRelease)(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SupportedFeatures
/**
 * Proc pointer type for @ref wgpuSupportedFeaturesFreeMembers:
 * > @copydoc wgpuSupportedFeaturesFreeMembers
 */
typedef void (*WGPUProcSupportedFeaturesFreeMembers)(WGPUSupportedFeatures supportedFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SupportedWGSLLanguageFeatures
/**
 * Proc pointer type for @ref wgpuSupportedWGSLLanguageFeaturesFreeMembers:
 * > @copydoc wgpuSupportedWGSLLanguageFeaturesFreeMembers
 */
typedef void (*WGPUProcSupportedWGSLLanguageFeaturesFreeMembers)(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Surface
/**
 * Proc pointer type for @ref wgpuSurfaceConfigure:
 * > @copydoc wgpuSurfaceConfigure
 */
typedef void (*WGPUProcSurfaceConfigure)(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceGetCapabilities:
 * > @copydoc wgpuSurfaceGetCapabilities
 */
typedef WGPUStatus (*WGPUProcSurfaceGetCapabilities)(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceGetCurrentTexture:
 * > @copydoc wgpuSurfaceGetCurrentTexture
 */
typedef void (*WGPUProcSurfaceGetCurrentTexture)(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfacePresent:
 * > @copydoc wgpuSurfacePresent
 */
typedef WGPUStatus (*WGPUProcSurfacePresent)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceSetLabel:
 * > @copydoc wgpuSurfaceSetLabel
 */
typedef void (*WGPUProcSurfaceSetLabel)(WGPUSurface surface, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceUnconfigure:
 * > @copydoc wgpuSurfaceUnconfigure
 */
typedef void (*WGPUProcSurfaceUnconfigure)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceAddRef.
 * > @copydoc wgpuSurfaceAddRef
 */
typedef void (*WGPUProcSurfaceAddRef)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSurfaceRelease.
 * > @copydoc wgpuSurfaceRelease
 */
typedef void (*WGPUProcSurfaceRelease)(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;

// Procs of SurfaceCapabilities
/**
 * Proc pointer type for @ref wgpuSurfaceCapabilitiesFreeMembers:
 * > @copydoc wgpuSurfaceCapabilitiesFreeMembers
 */
typedef void (*WGPUProcSurfaceCapabilitiesFreeMembers)(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Texture
/**
 * Proc pointer type for @ref wgpuTextureCreateView:
 * > @copydoc wgpuTextureCreateView
 */
typedef WGPUTextureView (*WGPUProcTextureCreateView)(WGPUTexture texture, WGPU_NULLABLE WGPUTextureViewDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureDestroy:
 * > @copydoc wgpuTextureDestroy
 */
typedef void (*WGPUProcTextureDestroy)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetDepthOrArrayLayers:
 * > @copydoc wgpuTextureGetDepthOrArrayLayers
 */
typedef uint32_t (*WGPUProcTextureGetDepthOrArrayLayers)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetDimension:
 * > @copydoc wgpuTextureGetDimension
 */
typedef WGPUTextureDimension (*WGPUProcTextureGetDimension)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetFormat:
 * > @copydoc wgpuTextureGetFormat
 */
typedef WGPUTextureFormat (*WGPUProcTextureGetFormat)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetHeight:
 * > @copydoc wgpuTextureGetHeight
 */
typedef uint32_t (*WGPUProcTextureGetHeight)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetMipLevelCount:
 * > @copydoc wgpuTextureGetMipLevelCount
 */
typedef uint32_t (*WGPUProcTextureGetMipLevelCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetSampleCount:
 * > @copydoc wgpuTextureGetSampleCount
 */
typedef uint32_t (*WGPUProcTextureGetSampleCount)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetUsage:
 * > @copydoc wgpuTextureGetUsage
 */
typedef WGPUTextureUsage (*WGPUProcTextureGetUsage)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureGetWidth:
 * > @copydoc wgpuTextureGetWidth
 */
typedef uint32_t (*WGPUProcTextureGetWidth)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureSetLabel:
 * > @copydoc wgpuTextureSetLabel
 */
typedef void (*WGPUProcTextureSetLabel)(WGPUTexture texture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureAddRef.
 * > @copydoc wgpuTextureAddRef
 */
typedef void (*WGPUProcTextureAddRef)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureRelease.
 * > @copydoc wgpuTextureRelease
 */
typedef void (*WGPUProcTextureRelease)(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;

// Procs of TextureView
/**
 * Proc pointer type for @ref wgpuTextureViewSetLabel:
 * > @copydoc wgpuTextureViewSetLabel
 */
typedef void (*WGPUProcTextureViewSetLabel)(WGPUTextureView textureView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureViewAddRef.
 * > @copydoc wgpuTextureViewAddRef
 */
typedef void (*WGPUProcTextureViewAddRef)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuTextureViewRelease.
 * > @copydoc wgpuTextureViewRelease
 */
typedef void (*WGPUProcTextureViewRelease)(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_PROCS)

#if !defined(WGPU_SKIP_DECLARATIONS)
/**
 * \defgroup GlobalFunctions Global Functions
 * \brief Functions that are not specific to an object.
 *
 * @{
 */
/**
 * Create a WGPUInstance
 */
WGPU_EXPORT WGPUInstance wgpuCreateInstance(WGPU_NULLABLE WGPUInstanceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Query the supported instance capabilities.
 *
 * @param capabilities
 * The supported instance capabilities
 *
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuGetInstanceCapabilities(WGPUInstanceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Returns the "procedure address" (function pointer) of the named function.
 * The result must be cast to the appropriate proc pointer type.
 */
WGPU_EXPORT WGPUProc wgpuGetProcAddress(WGPUStringView procName) WGPU_FUNCTION_ATTRIBUTE;


/** @} */

/**
 * \defgroup Methods
 * \brief Functions that are relative to a specific object.
 *
 * @{
 */

/**
 * \defgroup WGPUAdapterMethods WGPUAdapter methods
 * \brief Functions whose first argument has type WGPUAdapter.
 *
 * @{
 */
/**
 * Get the list of @ref WGPUFeatureName values supported by the adapter.
 *
 * @param features
 * This parameter is @ref ReturnedWithOwnership.
 */
WGPU_EXPORT void wgpuAdapterGetFeatures(WGPUAdapter adapter, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param info
 * This parameter is @ref ReturnedWithOwnership.
 *
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuAdapterGetInfo(WGPUAdapter adapter, WGPUAdapterInfo * info) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuAdapterGetLimits(WGPUAdapter adapter, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuAdapterHasFeature(WGPUAdapter adapter, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuAdapterRequestDevice(WGPUAdapter adapter, WGPU_NULLABLE WGPUDeviceDescriptor const * descriptor, WGPURequestDeviceCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterAddRef(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuAdapterRelease(WGPUAdapter adapter) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUAdapterInfoMethods WGPUAdapterInfo methods
 * \brief Functions whose first argument has type WGPUAdapterInfo.
 *
 * @{
 */
/**
 * Frees array members of WGPUAdapterInfo which were allocated by the API.
 */
WGPU_EXPORT void wgpuAdapterInfoFreeMembers(WGPUAdapterInfo adapterInfo) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUBindGroupMethods WGPUBindGroup methods
 * \brief Functions whose first argument has type WGPUBindGroup.
 *
 * @{
 */
WGPU_EXPORT void wgpuBindGroupSetLabel(WGPUBindGroup bindGroup, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupAddRef(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupRelease(WGPUBindGroup bindGroup) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUBindGroupLayoutMethods WGPUBindGroupLayout methods
 * \brief Functions whose first argument has type WGPUBindGroupLayout.
 *
 * @{
 */
WGPU_EXPORT void wgpuBindGroupLayoutSetLabel(WGPUBindGroupLayout bindGroupLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutAddRef(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBindGroupLayoutRelease(WGPUBindGroupLayout bindGroupLayout) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUBufferMethods WGPUBuffer methods
 * \brief Functions whose first argument has type WGPUBuffer.
 *
 * @{
 */
WGPU_EXPORT void wgpuBufferDestroy(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param offset
 * Byte offset relative to the beginning of the buffer.
 *
 * @param size
 * Byte size of the range to get. The returned pointer is valid for exactly this many bytes.
 *
 * @returns
 * Returns a const pointer to beginning of the mapped range.
 * It must not be written; writing to this range causes undefined behavior.
 * Returns `NULL` with @ref ImplementationDefinedLogging if:
 *
 * - There is any content-timeline error as defined in the WebGPU specification for `getMappedRange()` (alignments, overlaps, etc.)
 *   **except** for overlaps with other *const* ranges, which are allowed in C.
 *   (JS does not allow this because const ranges do not exist.)
 */
WGPU_EXPORT void const * wgpuBufferGetConstMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferMapState wgpuBufferGetMapState(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param offset
 * Byte offset relative to the beginning of the buffer.
 *
 * @param size
 * Byte size of the range to get. The returned pointer is valid for exactly this many bytes.
 *
 * @returns
 * Returns a mutable pointer to beginning of the mapped range.
 * Returns `NULL` with @ref ImplementationDefinedLogging if:
 *
 * - There is any content-timeline error as defined in the WebGPU specification for `getMappedRange()` (alignments, overlaps, etc.)
 * - The buffer is not mapped with @ref WGPUMapMode_Write.
 */
WGPU_EXPORT void * wgpuBufferGetMappedRange(WGPUBuffer buffer, size_t offset, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint64_t wgpuBufferGetSize(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBufferUsage wgpuBufferGetUsage(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuBufferMapAsync(WGPUBuffer buffer, WGPUMapMode mode, size_t offset, size_t size, WGPUBufferMapCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferSetLabel(WGPUBuffer buffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferUnmap(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferAddRef(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuBufferRelease(WGPUBuffer buffer) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUCommandBufferMethods WGPUCommandBuffer methods
 * \brief Functions whose first argument has type WGPUCommandBuffer.
 *
 * @{
 */
WGPU_EXPORT void wgpuCommandBufferSetLabel(WGPUCommandBuffer commandBuffer, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferAddRef(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandBufferRelease(WGPUCommandBuffer commandBuffer) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUCommandEncoderMethods WGPUCommandEncoder methods
 * \brief Functions whose first argument has type WGPUCommandEncoder.
 *
 * @{
 */
WGPU_EXPORT WGPUComputePassEncoder wgpuCommandEncoderBeginComputePass(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUComputePassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPassEncoder wgpuCommandEncoderBeginRenderPass(WGPUCommandEncoder commandEncoder, WGPURenderPassDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderClearBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToBuffer(WGPUCommandEncoder commandEncoder, WGPUBuffer source, uint64_t sourceOffset, WGPUBuffer destination, uint64_t destinationOffset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyBufferToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyBufferInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToBuffer(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyBufferInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderCopyTextureToTexture(WGPUCommandEncoder commandEncoder, WGPUTexelCopyTextureInfo const * source, WGPUTexelCopyTextureInfo const * destination, WGPUExtent3D const * copySize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandBuffer wgpuCommandEncoderFinish(WGPUCommandEncoder commandEncoder, WGPU_NULLABLE WGPUCommandBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderInsertDebugMarker(WGPUCommandEncoder commandEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPopDebugGroup(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderPushDebugGroup(WGPUCommandEncoder commandEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderResolveQuerySet(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t firstQuery, uint32_t queryCount, WGPUBuffer destination, uint64_t destinationOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderSetLabel(WGPUCommandEncoder commandEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderWriteTimestamp(WGPUCommandEncoder commandEncoder, WGPUQuerySet querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderAddRef(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuCommandEncoderRelease(WGPUCommandEncoder commandEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUComputePassEncoderMethods WGPUComputePassEncoder methods
 * \brief Functions whose first argument has type WGPUComputePassEncoder.
 *
 * @{
 */
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroups(WGPUComputePassEncoder computePassEncoder, uint32_t workgroupCountX, uint32_t workgroupCountY, uint32_t workgroupCountZ) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderDispatchWorkgroupsIndirect(WGPUComputePassEncoder computePassEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderEnd(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderInsertDebugMarker(WGPUComputePassEncoder computePassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPopDebugGroup(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderPushDebugGroup(WGPUComputePassEncoder computePassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetBindGroup(WGPUComputePassEncoder computePassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetLabel(WGPUComputePassEncoder computePassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetPipeline(WGPUComputePassEncoder computePassEncoder, WGPUComputePipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderAddRef(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderRelease(WGPUComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUComputePipelineMethods WGPUComputePipeline methods
 * \brief Functions whose first argument has type WGPUComputePipeline.
 *
 * @{
 */
WGPU_EXPORT WGPUBindGroupLayout wgpuComputePipelineGetBindGroupLayout(WGPUComputePipeline computePipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineSetLabel(WGPUComputePipeline computePipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineAddRef(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePipelineRelease(WGPUComputePipeline computePipeline) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUDeviceMethods WGPUDevice methods
 * \brief Functions whose first argument has type WGPUDevice.
 *
 * @{
 */
WGPU_EXPORT WGPUBindGroup wgpuDeviceCreateBindGroup(WGPUDevice device, WGPUBindGroupDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBindGroupLayout wgpuDeviceCreateBindGroupLayout(WGPUDevice device, WGPUBindGroupLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBuffer wgpuDeviceCreateBuffer(WGPUDevice device, WGPUBufferDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUCommandEncoder wgpuDeviceCreateCommandEncoder(WGPUDevice device, WGPU_NULLABLE WGPUCommandEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUComputePipeline wgpuDeviceCreateComputePipeline(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDeviceCreateComputePipelineAsync(WGPUDevice device, WGPUComputePipelineDescriptor const * descriptor, WGPUCreateComputePipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUPipelineLayout wgpuDeviceCreatePipelineLayout(WGPUDevice device, WGPUPipelineLayoutDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQuerySet wgpuDeviceCreateQuerySet(WGPUDevice device, WGPUQuerySetDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundleEncoder wgpuDeviceCreateRenderBundleEncoder(WGPUDevice device, WGPURenderBundleEncoderDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderPipeline wgpuDeviceCreateRenderPipeline(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDeviceCreateRenderPipelineAsync(WGPUDevice device, WGPURenderPipelineDescriptor const * descriptor, WGPUCreateRenderPipelineAsyncCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUSampler wgpuDeviceCreateSampler(WGPUDevice device, WGPU_NULLABLE WGPUSamplerDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUShaderModule wgpuDeviceCreateShaderModule(WGPUDevice device, WGPUShaderModuleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUTexture wgpuDeviceCreateTexture(WGPUDevice device, WGPUTextureDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceDestroy(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param adapterInfo
 * This parameter is @ref ReturnedWithOwnership.
 *
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuDeviceGetAdapterInfo(WGPUDevice device, WGPUAdapterInfo * adapterInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Get the list of @ref WGPUFeatureName values supported by the device.
 *
 * @param features
 * This parameter is @ref ReturnedWithOwnership.
 */
WGPU_EXPORT void wgpuDeviceGetFeatures(WGPUDevice device, WGPUSupportedFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuDeviceGetLimits(WGPUDevice device, WGPULimits * limits) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @returns
 * The @ref WGPUFuture for the device-lost event of the device.
 */
WGPU_EXPORT WGPUFuture wgpuDeviceGetLostFuture(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueue wgpuDeviceGetQueue(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuDeviceHasFeature(WGPUDevice device, WGPUFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuDevicePopErrorScope(WGPUDevice device, WGPUPopErrorScopeCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDevicePushErrorScope(WGPUDevice device, WGPUErrorFilter filter) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceSetLabel(WGPUDevice device, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceAddRef(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuDeviceRelease(WGPUDevice device) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUInstanceMethods WGPUInstance methods
 * \brief Functions whose first argument has type WGPUInstance.
 *
 * @{
 */
/**
 * Creates a @ref WGPUSurface, see @ref Surface-Creation for more details.
 *
 * @param descriptor
 * The description of the @ref WGPUSurface to create.
 *
 * @returns
 * A new @ref WGPUSurface for this descriptor (or an error @ref WGPUSurface).
 */
WGPU_EXPORT WGPUSurface wgpuInstanceCreateSurface(WGPUInstance instance, WGPUSurfaceDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Get the list of @ref WGPUWGSLLanguageFeatureName values supported by the instance.
 */
WGPU_EXPORT WGPUStatus wgpuInstanceGetWGSLLanguageFeatures(WGPUInstance instance, WGPUSupportedWGSLLanguageFeatures * features) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUBool wgpuInstanceHasWGSLLanguageFeature(WGPUInstance instance, WGPUWGSLLanguageFeatureName feature) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Processes asynchronous events on this `WGPUInstance`, calling any callbacks for asynchronous operations created with `::WGPUCallbackMode_AllowProcessEvents`.
 *
 * See @ref Process-Events for more information.
 */
WGPU_EXPORT void wgpuInstanceProcessEvents(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUFuture wgpuInstanceRequestAdapter(WGPUInstance instance, WGPU_NULLABLE WGPURequestAdapterOptions const * options, WGPURequestAdapterCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Wait for at least one WGPUFuture in `futures` to complete, and call callbacks of the respective completed asynchronous operations.
 *
 * See @ref Wait-Any for more information.
 */
WGPU_EXPORT WGPUWaitStatus wgpuInstanceWaitAny(WGPUInstance instance, size_t futureCount, WGPU_NULLABLE WGPUFutureWaitInfo * futures, uint64_t timeoutNS) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceAddRef(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuInstanceRelease(WGPUInstance instance) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUPipelineLayoutMethods WGPUPipelineLayout methods
 * \brief Functions whose first argument has type WGPUPipelineLayout.
 *
 * @{
 */
WGPU_EXPORT void wgpuPipelineLayoutSetLabel(WGPUPipelineLayout pipelineLayout, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutAddRef(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuPipelineLayoutRelease(WGPUPipelineLayout pipelineLayout) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUQuerySetMethods WGPUQuerySet methods
 * \brief Functions whose first argument has type WGPUQuerySet.
 *
 * @{
 */
WGPU_EXPORT void wgpuQuerySetDestroy(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuQuerySetGetCount(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPUQueryType wgpuQuerySetGetType(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetSetLabel(WGPUQuerySet querySet, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetAddRef(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQuerySetRelease(WGPUQuerySet querySet) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUQueueMethods WGPUQueue methods
 * \brief Functions whose first argument has type WGPUQueue.
 *
 * @{
 */
WGPU_EXPORT WGPUFuture wgpuQueueOnSubmittedWorkDone(WGPUQueue queue, WGPUQueueWorkDoneCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSetLabel(WGPUQueue queue, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueSubmit(WGPUQueue queue, size_t commandCount, WGPUCommandBuffer const * commands) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Produces a @ref DeviceError both content-timeline (`size` alignment) and device-timeline
 * errors defined by the WebGPU specification.
 */
WGPU_EXPORT void wgpuQueueWriteBuffer(WGPUQueue queue, WGPUBuffer buffer, uint64_t bufferOffset, void const * data, size_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueWriteTexture(WGPUQueue queue, WGPUTexelCopyTextureInfo const * destination, void const * data, size_t dataSize, WGPUTexelCopyBufferLayout const * dataLayout, WGPUExtent3D const * writeSize) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueAddRef(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuQueueRelease(WGPUQueue queue) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderBundleMethods WGPURenderBundle methods
 * \brief Functions whose first argument has type WGPURenderBundle.
 *
 * @{
 */
WGPU_EXPORT void wgpuRenderBundleSetLabel(WGPURenderBundle renderBundle, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleAddRef(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleRelease(WGPURenderBundle renderBundle) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderBundleEncoderMethods WGPURenderBundleEncoder methods
 * \brief Functions whose first argument has type WGPURenderBundleEncoder.
 *
 * @{
 */
WGPU_EXPORT void wgpuRenderBundleEncoderDraw(WGPURenderBundleEncoder renderBundleEncoder, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexed(WGPURenderBundleEncoder renderBundleEncoder, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t baseVertex, uint32_t firstInstance) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndexedIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderDrawIndirect(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer indirectBuffer, uint64_t indirectOffset) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT WGPURenderBundle wgpuRenderBundleEncoderFinish(WGPURenderBundleEncoder renderBundleEncoder, WGPU_NULLABLE WGPURenderBundleDescriptor const * descriptor) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderInsertDebugMarker(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPopDebugGroup(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderPushDebugGroup(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetBindGroup(WGPURenderBundleEncoder renderBundleEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetIndexBuffer(WGPURenderBundleEncoder renderBundleEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetLabel(WGPURenderBundleEncoder renderBundleEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetPipeline(WGPURenderBundleEncoder renderBundleEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderSetVertexBuffer(WGPURenderBundleEncoder renderBundleEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderAddRef(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderBundleEncoderRelease(WGPURenderBundleEncoder renderBundleEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderPassEncoderMethods WGPURenderPassEncoder methods
 * \brief Functions whose first argument has type WGPURenderPassEncoder.
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
WGPU_EXPORT void wgpuRenderPassEncoderInsertDebugMarker(WGPURenderPassEncoder renderPassEncoder, WGPUStringView markerLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPopDebugGroup(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderPushDebugGroup(WGPURenderPassEncoder renderPassEncoder, WGPUStringView groupLabel) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBindGroup(WGPURenderPassEncoder renderPassEncoder, uint32_t groupIndex, WGPU_NULLABLE WGPUBindGroup group, size_t dynamicOffsetCount, uint32_t const * dynamicOffsets) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetBlendConstant(WGPURenderPassEncoder renderPassEncoder, WGPUColor const * color) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetIndexBuffer(WGPURenderPassEncoder renderPassEncoder, WGPUBuffer buffer, WGPUIndexFormat format, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetLabel(WGPURenderPassEncoder renderPassEncoder, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetPipeline(WGPURenderPassEncoder renderPassEncoder, WGPURenderPipeline pipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetScissorRect(WGPURenderPassEncoder renderPassEncoder, uint32_t x, uint32_t y, uint32_t width, uint32_t height) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetStencilReference(WGPURenderPassEncoder renderPassEncoder, uint32_t reference) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetVertexBuffer(WGPURenderPassEncoder renderPassEncoder, uint32_t slot, WGPU_NULLABLE WGPUBuffer buffer, uint64_t offset, uint64_t size) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetViewport(WGPURenderPassEncoder renderPassEncoder, float x, float y, float width, float height, float minDepth, float maxDepth) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderAddRef(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderRelease(WGPURenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderPipelineMethods WGPURenderPipeline methods
 * \brief Functions whose first argument has type WGPURenderPipeline.
 *
 * @{
 */
WGPU_EXPORT WGPUBindGroupLayout wgpuRenderPipelineGetBindGroupLayout(WGPURenderPipeline renderPipeline, uint32_t groupIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineSetLabel(WGPURenderPipeline renderPipeline, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineAddRef(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPipelineRelease(WGPURenderPipeline renderPipeline) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUSamplerMethods WGPUSampler methods
 * \brief Functions whose first argument has type WGPUSampler.
 *
 * @{
 */
WGPU_EXPORT void wgpuSamplerSetLabel(WGPUSampler sampler, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerAddRef(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSamplerRelease(WGPUSampler sampler) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUShaderModuleMethods WGPUShaderModule methods
 * \brief Functions whose first argument has type WGPUShaderModule.
 *
 * @{
 */
WGPU_EXPORT WGPUFuture wgpuShaderModuleGetCompilationInfo(WGPUShaderModule shaderModule, WGPUCompilationInfoCallbackInfo callbackInfo) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleSetLabel(WGPUShaderModule shaderModule, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleAddRef(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuShaderModuleRelease(WGPUShaderModule shaderModule) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUSupportedFeaturesMethods WGPUSupportedFeatures methods
 * \brief Functions whose first argument has type WGPUSupportedFeatures.
 *
 * @{
 */
/**
 * Frees array members of WGPUSupportedFeatures which were allocated by the API.
 */
WGPU_EXPORT void wgpuSupportedFeaturesFreeMembers(WGPUSupportedFeatures supportedFeatures) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUSupportedWGSLLanguageFeaturesMethods WGPUSupportedWGSLLanguageFeatures methods
 * \brief Functions whose first argument has type WGPUSupportedWGSLLanguageFeatures.
 *
 * @{
 */
/**
 * Frees array members of WGPUSupportedWGSLLanguageFeatures which were allocated by the API.
 */
WGPU_EXPORT void wgpuSupportedWGSLLanguageFeaturesFreeMembers(WGPUSupportedWGSLLanguageFeatures supportedWGSLLanguageFeatures) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUSurfaceMethods WGPUSurface methods
 * \brief Functions whose first argument has type WGPUSurface.
 *
 * @{
 */
/**
 * Configures parameters for rendering to `surface`.
 * Produces a @ref DeviceError for all content-timeline errors defined by the WebGPU specification.
 *
 * See @ref Surface-Configuration for more details.
 *
 * @param config
 * The new configuration to use.
 */
WGPU_EXPORT void wgpuSurfaceConfigure(WGPUSurface surface, WGPUSurfaceConfiguration const * config) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Provides information on how `adapter` is able to use `surface`.
 * See @ref Surface-Capabilities for more details.
 *
 * @param adapter
 * The @ref WGPUAdapter to get capabilities for presenting to this @ref WGPUSurface.
 *
 * @param capabilities
 * The structure to fill capabilities in.
 * It may contain memory allocations so `::wgpuSurfaceCapabilitiesFreeMembers` must be called to avoid memory leaks.
 * This parameter is @ref ReturnedWithOwnership.
 *
 * @returns
 * Indicates if there was an @ref OutStructChainError.
 */
WGPU_EXPORT WGPUStatus wgpuSurfaceGetCapabilities(WGPUSurface surface, WGPUAdapter adapter, WGPUSurfaceCapabilities * capabilities) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Returns the @ref WGPUTexture to render to `surface` this frame along with metadata on the frame.
 * Returns `NULL` and @ref WGPUSurfaceGetCurrentTextureStatus_Error if the surface is not configured.
 *
 * See @ref Surface-Presenting for more details.
 *
 * @param surfaceTexture
 * The structure to fill the @ref WGPUTexture and metadata in.
 */
WGPU_EXPORT void wgpuSurfaceGetCurrentTexture(WGPUSurface surface, WGPUSurfaceTexture * surfaceTexture) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Shows `surface`'s current texture to the user.
 * See @ref Surface-Presenting for more details.
 *
 * @returns
 * Returns @ref WGPUStatus_Error if the surface doesn't have a current texture.
 */
WGPU_EXPORT WGPUStatus wgpuSurfacePresent(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Modifies the label used to refer to `surface`.
 *
 * @param label
 * The new label.
 */
WGPU_EXPORT void wgpuSurfaceSetLabel(WGPUSurface surface, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Removes the configuration for `surface`.
 * See @ref Surface-Configuration for more details.
 */
WGPU_EXPORT void wgpuSurfaceUnconfigure(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceAddRef(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSurfaceRelease(WGPUSurface surface) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUSurfaceCapabilitiesMethods WGPUSurfaceCapabilities methods
 * \brief Functions whose first argument has type WGPUSurfaceCapabilities.
 *
 * @{
 */
/**
 * Frees array members of WGPUSurfaceCapabilities which were allocated by the API.
 */
WGPU_EXPORT void wgpuSurfaceCapabilitiesFreeMembers(WGPUSurfaceCapabilities surfaceCapabilities) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUTextureMethods WGPUTexture methods
 * \brief Functions whose first argument has type WGPUTexture.
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
WGPU_EXPORT WGPUTextureUsage wgpuTextureGetUsage(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuTextureGetWidth(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureSetLabel(WGPUTexture texture, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureAddRef(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureRelease(WGPUTexture texture) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUTextureViewMethods WGPUTextureView methods
 * \brief Functions whose first argument has type WGPUTextureView.
 *
 * @{
 */
WGPU_EXPORT void wgpuTextureViewSetLabel(WGPUTextureView textureView, WGPUStringView label) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewAddRef(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuTextureViewRelease(WGPUTextureView textureView) WGPU_FUNCTION_ATTRIBUTE;
/** @} */


/** @} */

#endif  // !defined(WGPU_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBGPU_H_
