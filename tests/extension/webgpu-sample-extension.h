/**
 * Copyright 2019-2023 WebGPU-Native developers
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/** @file */

/**
 * \mainpage
 *
 * An example of WebGPU extension, inspired by wgpu-native's wgpu.h header.
 */

#ifndef WEBGPU_SAMPLE_EXTENSION_H_
#define WEBGPU_SAMPLE_EXTENSION_H_

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

#if !defined(_wgpu_EXTEND_ENUM)
#ifdef __cplusplus
#define _wgpu_EXTEND_ENUM(E, N, V) static const E N = E(V)
#else
#define _wgpu_EXTEND_ENUM(E, N, V) static const E N = (E)(V)
#endif
#endif // !defined(_wgpu_EXTEND_ENUM)

#include "webgpu.h"


/**
 * \defgroup Constants Constants
 * \brief Constants.
 *
 * @{
 */
/**
 * A constant that represent some undefined value for this extension.
 */
#define WGPU_EXAMPLE_TEST_VALUE_UNDEFINED (UINT32_MAX)


/** @} */

/**
 * \defgroup UtilityTypes Utility Types
 *
 * @{
 */
/**
 * A typedef added for this extension.
 */
typedef uint32_t WGPUExampleTest;


/** @} */

/**
 * \defgroup Objects Objects
 * \brief Opaque, non-dispatchable handles to WebGPU objects.
 *
 * @{
 */
typedef struct WGPUExampleComputePassEncoderImpl* WGPUExampleComputePassEncoder WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUExampleInstanceImpl* WGPUExampleInstance WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUExampleRenderPassEncoderImpl* WGPUExampleRenderPassEncoder WGPU_OBJECT_ATTRIBUTE;


/** @} */
// Structure forward declarations
struct WGPUExampleBindGroupEntryExtras;
struct WGPUExampleBindGroupLayoutEntryExtras;
struct WGPUExampleDeviceExtras;
struct WGPUExampleInstanceEnumerateAdapterOptions;
struct WGPUExampleInstanceExtras;
struct WGPUExampleNativeLimits;
struct WGPUExamplePushConstantRange;
struct WGPUExampleQuerySetDescriptorExtras;
struct WGPUExampleRegistryReport;
struct WGPUExampleShaderDefine;
struct WGPUExampleSurfaceConfigurationExtras;
struct WGPUExampleHubReport;
struct WGPUExamplePipelineLayoutExtras;
struct WGPUExampleRequiredLimitsExtras;
struct WGPUExampleShaderSourceGLSL;
struct WGPUExampleSupportedLimitsExtras;
struct WGPUExampleGlobalReport;

// Callback info structure forward declarations
struct WGPUExampleLogCallbackInfo;


/**
 * \defgroup Enumerations Enumerations
 * \brief Enums.
 *
 * @{
 */
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExamplePushConstants, 0x00060001);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTextureAdapterSpecificFormatFeatures, 0x00060002);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleMultiDrawIndirect, 0x00060003);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleMultiDrawIndirectCount, 0x00060004);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleVertexWritableStorage, 0x00060005);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTextureBindingArray, 0x00060006);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleSampledTextureAndStorageBufferArrayNonUniformIndexing, 0x00060007);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExamplePipelineStatisticsQuery, 0x00060008);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleStorageResourceBindingArray, 0x00060009);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExamplePartiallyBoundBindingArray, 0x0006000A);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTextureFormat16bitNorm, 0x0006000B);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTextureCompressionAstcHdr, 0x0006000C);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleMappablePrimaryBuffers, 0x0006000D);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleBufferBindingArray, 0x0006000E);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleUniformBufferAndStorageTextureArrayNonUniformIndexing, 0x0006000F);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleSpirvShaderPassthrough, 0x00060010);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleVertexAttribute64bit, 0x00060011);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTextureFormatNv12, 0x00060012);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleRayTracingAccelerationStructure, 0x00060013);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleRayQuery, 0x00060014);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleShaderF64, 0x00060015);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleShaderI16, 0x00060016);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleShaderPrimitiveIndex, 0x00060017);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleShaderEarlyDepthTest, 0x00060018);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleSubgroup, 0x00060019);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleSubgroupVertex, 0x0006001A);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleSubgroupBarrier, 0x0006001B);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTimestampQueryInsideEncoders, 0x0006001C);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ExampleTimestampQueryInsidePasses, 0x0006001D);

_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleR16Unorm, 0x00060001);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleR16Snorm, 0x00060002);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleRg16Unorm, 0x00060003);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleRg16Snorm, 0x00060004);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleRgba16Unorm, 0x00060005);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleRgba16Snorm, 0x00060006);
_wgpu_EXTEND_ENUM(WGPUTextureFormat, WGPUTextureFormat_ExampleClipperInvocations, 0x00060007);

/**
 * Compiler to use when compiling DirectX 12 shaders.
 */
typedef enum WGPUExampleDx12Compiler {
    /**
     * `0x00060000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUExampleDx12Compiler_Undefined = 0x00060000,
    WGPUExampleDx12Compiler_Fxc = 0x00060001,
    WGPUExampleDx12Compiler_Dxc = 0x00060002,
    WGPUExampleDx12Compiler_Force32 = 0x7FFFFFFF
} WGPUExampleDx12Compiler WGPU_ENUM_ATTRIBUTE;

/**
 * Minor version of OpenGL ES 3.x to use.
 */
typedef enum WGPUExampleGles3MinorVersion {
    WGPUExampleGles3MinorVersion_Automatic = 0x00060000,
    /**
     * `0x00060001`.
     * Use OpenGL ES 3.0
     */
    WGPUExampleGles3MinorVersion_Version0 = 0x00060001,
    /**
     * `0x00060002`.
     * Use OpenGL ES 3.1
     */
    WGPUExampleGles3MinorVersion_Version1 = 0x00060002,
    /**
     * `0x00060003`.
     * Use OpenGL ES 3.2
     */
    WGPUExampleGles3MinorVersion_Version2 = 0x00060003,
    WGPUExampleGles3MinorVersion_Force32 = 0x7FFFFFFF
} WGPUExampleGles3MinorVersion WGPU_ENUM_ATTRIBUTE;

/**
 * Verbosity of the log, used in @ref wgpuSetLogLevel.
 */
typedef enum WGPUExampleLogLevel {
    WGPUExampleLogLevel_Off = 0x00060000,
    WGPUExampleLogLevel_Error = 0x00060001,
    WGPUExampleLogLevel_Warn = 0x00060002,
    WGPUExampleLogLevel_Info = 0x00060003,
    WGPUExampleLogLevel_Debug = 0x00060004,
    WGPUExampleLogLevel_Trace = 0x00060005,
    WGPUExampleLogLevel_Force32 = 0x7FFFFFFF
} WGPUExampleLogLevel WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUExamplePipelineStatisticName {
    WGPUExamplePipelineStatisticName_VertexShaderInvocations = 0x00060001,
    WGPUExamplePipelineStatisticName_ClipperInvocations = 0x00060002,
    WGPUExamplePipelineStatisticName_ClipperPrimitivesOut = 0x00060003,
    WGPUExamplePipelineStatisticName_FragmentShaderInvocations = 0x00060004,
    WGPUExamplePipelineStatisticName_ComputeShaderInvocations = 0x00060005,
    WGPUExamplePipelineStatisticName_Force32 = 0x7FFFFFFF
} WGPUExamplePipelineStatisticName WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUExampleQueryType {
    WGPUExampleQueryType_PipelineStatistics = 0x00060001,
    WGPUExampleQueryType_Force32 = 0x7FFFFFFF
} WGPUExampleQueryType WGPU_ENUM_ATTRIBUTE;


/** @} */

/**
 * \defgroup Bitflags Bitflags
 * \brief Type and constant definitions for bitflag types.
 *
 * @{
 */
typedef WGPUFlags WGPUExampleInstanceBackend;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_All = 0x0000000000000000;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Vulkan = 0x0000000000000001;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Gl = 0x0000000000000002;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Metal = 0x0000000000000004;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Dx12 = 0x0000000000000008;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Dx11 = 0x0000000000000010;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_BrowserWebgpu = 0x0000000000000020;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Primary = 0x000000000000002D /* ExampleVulkan | ExampleMetal | ExampleDx12 | ExampleBrowserWebgpu */;
static const WGPUExampleInstanceBackend WGPUExampleInstanceBackend_Secondary = 0x0000000000000012 /* ExampleGl | ExampleDx11 */;

typedef WGPUFlags WGPUExampleInstanceOption;
static const WGPUExampleInstanceOption WGPUExampleInstanceOption_Default = 0x0000000000000000;
static const WGPUExampleInstanceOption WGPUExampleInstanceOption_Debug = 0x0000000000000001;
static const WGPUExampleInstanceOption WGPUExampleInstanceOption_Validation = 0x0000000000000002;
static const WGPUExampleInstanceOption WGPUExampleInstanceOption_DiscardHalLabels = 0x0000000000000004;


/** @} */

/**
 * \defgroup Callbacks Callbacks
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
typedef void (*WGPUExampleLogCallback)( level,  message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

/** @} */

/**
 * \defgroup Structures Structures
 * \brief Descriptors and other transparent structures.
 *
 * @{
 */

/**
 * \defgroup WGPUCallbackInfo Callback Info Structs
 * \brief Callback info structures that are used in asynchronous functions.
 *
 * @{
 */
typedef struct WGPUExampleLogCallbackInfo {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPUExampleLogCallback callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPUExampleLogCallbackInfo WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleLogCallbackInfo.
 */
#define WGPU_EXAMPLE_LOG_CALLBACK_INFO_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleLogCallbackInfo, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.mode=*/WGPUCallbackMode_WaitAnyOnly _wgpu_COMMA \
    /*.callback=*/NULL _wgpu_COMMA \
    /*.userdata1=*/NULL _wgpu_COMMA \
    /*.userdata2=*/NULL _wgpu_COMMA \
})

/** @} */

/**
 * Default values can be set using @ref WGPU_BIND_GROUP_ENTRY_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleBindGroupEntryExtras {
    WGPUChainedStruct chain;
    /**
     * Array count for `buffers`. The `INIT` macro sets this to 0.
     */
    size_t bufferCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     buffers;
    /**
     * Array count for `samplers`. The `INIT` macro sets this to 0.
     */
    size_t samplerCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     samplers;
    /**
     * Array count for `textureViews`. The `INIT` macro sets this to 0.
     */
    size_t textureViewCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     textureViews;
} WGPUExampleBindGroupEntryExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleBindGroupEntryExtras.
 */
#define WGPU_EXAMPLE_BIND_GROUP_ENTRY_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleBindGroupEntryExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleBindGroupEntryExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.bufferCount=*/0 _wgpu_COMMA \
    /*.buffers=*/NULL _wgpu_COMMA \
    /*.samplerCount=*/0 _wgpu_COMMA \
    /*.samplers=*/NULL _wgpu_COMMA \
    /*.textureViewCount=*/0 _wgpu_COMMA \
    /*.textureViews=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_BIND_GROUP_LAYOUT_ENTRY_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleBindGroupLayoutEntryExtras {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to `0`.
     */
     count;
} WGPUExampleBindGroupLayoutEntryExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleBindGroupLayoutEntryExtras.
 */
#define WGPU_EXAMPLE_BIND_GROUP_LAYOUT_ENTRY_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleBindGroupLayoutEntryExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleBindGroupLayoutEntryExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.count=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_DEVICE_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleDeviceExtras {
    WGPUChainedStruct chain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     tracePath;
} WGPUExampleDeviceExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleDeviceExtras.
 */
#define WGPU_EXAMPLE_DEVICE_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleDeviceExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleDeviceExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.tracePath=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_INSTANCE_ENUMERATE_ADAPTER_OPTIONS_INIT as initializer.
 */
typedef struct WGPUExampleInstanceEnumerateAdapterOptions {
    WGPUChainedStructOut * nextInChain;
    /**
     * The `INIT` macro sets this to (@ref WGPUInstanceBackend)0.
     */
     backends;
} WGPUExampleInstanceEnumerateAdapterOptions WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleInstanceEnumerateAdapterOptions.
 */
#define WGPU_EXAMPLE_INSTANCE_ENUMERATE_ADAPTER_OPTIONS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleInstanceEnumerateAdapterOptions, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.backends=*/_wgpu_ENUM_ZERO_INIT(WGPUInstanceBackend) _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_INSTANCE_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleInstanceExtras {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to @ref WGPUInstanceBackend_None.
     */
     backends;
    /**
     * The `INIT` macro sets this to @ref WGPUInstanceOption_None.
     */
     options;
    /**
     * The `INIT` macro sets this to (@ref WGPUDx12Compiler)0.
     */
     dx12ShaderCompiler;
    /**
     * The `INIT` macro sets this to (@ref WGPUGles3MinorVersion)0.
     */
     gles3MinorVersion;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     dxilPath;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     dxcPath;
} WGPUExampleInstanceExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleInstanceExtras.
 */
#define WGPU_EXAMPLE_INSTANCE_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleInstanceExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleInstanceExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.backends=*/WGPUInstanceBackend_None _wgpu_COMMA \
    /*.options=*/WGPUInstanceOption_None _wgpu_COMMA \
    /*.dx12ShaderCompiler=*/_wgpu_ENUM_ZERO_INIT(WGPUDx12Compiler) _wgpu_COMMA \
    /*.gles3MinorVersion=*/_wgpu_ENUM_ZERO_INIT(WGPUGles3MinorVersion) _wgpu_COMMA \
    /*.dxilPath=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.dxcPath=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_NATIVE_LIMITS_INIT as initializer.
 */
typedef struct WGPUExampleNativeLimits {
    /** This struct chain is used as mutable in some places and immutable in others. */
    WGPUChainedStructOut chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_LIMIT_U32_UNDEFINED.
     */
     maxPushConstantSize;
    /**
     * The `INIT` macro sets this to @ref WGPU_LIMIT_U32_UNDEFINED.
     */
     maxNonSamplerBindings;
} WGPUExampleNativeLimits WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleNativeLimits.
 */
#define WGPU_EXAMPLE_NATIVE_LIMITS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleNativeLimits, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStructOut, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleNativeLimits _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxPushConstantSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxNonSamplerBindings=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_PUSH_CONSTANT_RANGE_INIT as initializer.
 */
typedef struct WGPUExamplePushConstantRange {
    WGPUChainedStruct const * nextInChain;
    /**
     * The `INIT` macro sets this to @ref WGPUShaderStageFlags_None.
     */
     stages;
    /**
     * The `INIT` macro sets this to `0`.
     */
     start;
    /**
     * The `INIT` macro sets this to `0`.
     */
     end;
} WGPUExamplePushConstantRange WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExamplePushConstantRange.
 */
#define WGPU_EXAMPLE_PUSH_CONSTANT_RANGE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExamplePushConstantRange, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.stages=*/WGPUShaderStageFlags_None _wgpu_COMMA \
    /*.start=*/0 _wgpu_COMMA \
    /*.end=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_QUERY_SET_DESCRIPTOR_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleQuerySetDescriptorExtras {
    WGPUChainedStruct chain;
    /**
     * Array count for `pipelineStatistics`. The `INIT` macro sets this to 0.
     */
    size_t pipelineStatisticCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     pipelineStatistics;
} WGPUExampleQuerySetDescriptorExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleQuerySetDescriptorExtras.
 */
#define WGPU_EXAMPLE_QUERY_SET_DESCRIPTOR_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleQuerySetDescriptorExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleQuerySetDescriptorExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.pipelineStatisticCount=*/0 _wgpu_COMMA \
    /*.pipelineStatistics=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_REGISTRY_REPORT_INIT as initializer.
 */
typedef struct WGPUExampleRegistryReport {
    /**
     * The `INIT` macro sets this to `0`.
     */
     numAllocated;
    /**
     * The `INIT` macro sets this to `0`.
     */
     numKeptFromUser;
    /**
     * The `INIT` macro sets this to `0`.
     */
     numReleasedFromUser;
    /**
     * The `INIT` macro sets this to `0`.
     */
     elementSize;
} WGPUExampleRegistryReport WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleRegistryReport.
 */
#define WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleRegistryReport, { \
    /*.numAllocated=*/0 _wgpu_COMMA \
    /*.numKeptFromUser=*/0 _wgpu_COMMA \
    /*.numReleasedFromUser=*/0 _wgpu_COMMA \
    /*.elementSize=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SHADER_DEFINE_INIT as initializer.
 */
typedef struct WGPUExampleShaderDefine {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     name;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     value;
} WGPUExampleShaderDefine WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleShaderDefine.
 */
#define WGPU_EXAMPLE_SHADER_DEFINE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleShaderDefine, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.name=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.value=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SURFACE_CONFIGURATION_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleSurfaceConfigurationExtras {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to `0`.
     */
     desiredMaximumFrameLatency;
} WGPUExampleSurfaceConfigurationExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleSurfaceConfigurationExtras.
 */
#define WGPU_EXAMPLE_SURFACE_CONFIGURATION_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleSurfaceConfigurationExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleSurfaceConfigurationExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.desiredMaximumFrameLatency=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_HUB_REPORT_INIT as initializer.
 */
typedef struct WGPUExampleHubReport {
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     adapters;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     devices;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     queues;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     pipelineLayouts;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     shaderModules;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     bindGroupLayouts;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     bindGroups;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     commandBuffers;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     renderBundles;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     renderPipelines;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     computePipelines;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     pipelineCaches;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     querySets;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     buffers;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     textures;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     textureViews;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     samplers;
} WGPUExampleHubReport WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleHubReport.
 */
#define WGPU_EXAMPLE_HUB_REPORT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleHubReport, { \
    /*.adapters=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.devices=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.queues=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.pipelineLayouts=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.shaderModules=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.bindGroupLayouts=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.bindGroups=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.commandBuffers=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.renderBundles=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.renderPipelines=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.computePipelines=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.pipelineCaches=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.querySets=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.buffers=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.textures=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.textureViews=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.samplers=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_PIPELINE_LAYOUT_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExamplePipelineLayoutExtras {
    WGPUChainedStruct chain;
    /**
     * Array count for `pushConstantRanges`. The `INIT` macro sets this to 0.
     */
    size_t pushConstantRangeCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     pushConstantRanges;
} WGPUExamplePipelineLayoutExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExamplePipelineLayoutExtras.
 */
#define WGPU_EXAMPLE_PIPELINE_LAYOUT_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExamplePipelineLayoutExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExamplePipelineLayoutExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.pushConstantRangeCount=*/0 _wgpu_COMMA \
    /*.pushConstantRanges=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_REQUIRED_LIMITS_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleRequiredLimitsExtras {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_NATIVE_LIMITS_INIT.
     */
     limits;
} WGPUExampleRequiredLimitsExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleRequiredLimitsExtras.
 */
#define WGPU_EXAMPLE_REQUIRED_LIMITS_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleRequiredLimitsExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleRequiredLimitsExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.limits=*/WGPU_EXAMPLE_NATIVE_LIMITS_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SHADER_SOURCE_GLSL_INIT as initializer.
 */
typedef struct WGPUExampleShaderSourceGLSL {
    WGPUChainedStruct chain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
     code;
    /**
     * The `INIT` macro sets this to @ref WGPUShaderStage_None.
     */
     stage;
    /**
     * Array count for `defines`. The `INIT` macro sets this to 0.
     */
    size_t defineCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
     defines;
} WGPUExampleShaderSourceGLSL WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleShaderSourceGLSL.
 */
#define WGPU_EXAMPLE_SHADER_SOURCE_GLSL_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleShaderSourceGLSL, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleShaderSourceGLSL _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.code=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.stage=*/WGPUShaderStage_None _wgpu_COMMA \
    /*.defineCount=*/0 _wgpu_COMMA \
    /*.defines=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SUPPORTED_LIMITS_EXTRAS_INIT as initializer.
 */
typedef struct WGPUExampleSupportedLimitsExtras {
    WGPUChainedStructOut chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_NATIVE_LIMITS_INIT.
     */
     limits;
} WGPUExampleSupportedLimitsExtras WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleSupportedLimitsExtras.
 */
#define WGPU_EXAMPLE_SUPPORTED_LIMITS_EXTRAS_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleSupportedLimitsExtras, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStructOut, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ExampleSupportedLimitsExtras _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.limits=*/WGPU_EXAMPLE_NATIVE_LIMITS_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_GLOBAL_REPORT_INIT as initializer.
 */
typedef struct WGPUExampleGlobalReport {
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_REGISTRY_REPORT_INIT.
     */
     surfaces;
    /**
     * The `INIT` macro sets this to @ref WGPU_EXAMPLE_HUB_REPORT_INIT.
     */
     hub;
} WGPUExampleGlobalReport WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUExampleGlobalReport.
 */
#define WGPU_EXAMPLE_GLOBAL_REPORT_INIT _wgpu_MAKE_INIT_STRUCT(WGPUExampleGlobalReport, { \
    /*.surfaces=*/WGPU_EXAMPLE_REGISTRY_REPORT_INIT _wgpu_COMMA \
    /*.hub=*/WGPU_EXAMPLE_HUB_REPORT_INIT _wgpu_COMMA \
})

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WGPU_SKIP_PROCS)

/**
 * Proc pointer type for @ref wgpuExampleSetLogCallback:
 * > @copydoc wgpuExampleSetLogCallback
 */
typedef void (*WGPUProcExampleSetLogCallback)( callback) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuExampleSetLogLevel:
 * > @copydoc wgpuExampleSetLogLevel
 */
typedef void (*WGPUProcExampleSetLogLevel)( level) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuExampleGetVersion:
 * > @copydoc wgpuExampleGetVersion
 */
typedef uint32_t (*WGPUProcExampleGetVersion)() WGPU_FUNCTION_ATTRIBUTE;
// Procs of ComputePassEncoder
/**
 * Proc pointer type for @ref wgpuComputePassEncoderExampleBeginPipelineStatisticsQuery:
 * > @copydoc wgpuComputePassEncoderBeginPipelineStatisticsQuery
 */
typedef void (*WGPUProcComputePassEncoderExampleBeginPipelineStatisticsQuery)(WGPUExampleComputePassEncoder computePassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderExampleEndPipelineStatisticsQuery:
 * > @copydoc wgpuComputePassEncoderEndPipelineStatisticsQuery
 */
typedef void (*WGPUProcComputePassEncoderExampleEndPipelineStatisticsQuery)(WGPUExampleComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderExampleSetPushConstants:
 * > @copydoc wgpuComputePassEncoderSetPushConstants
 */
typedef void (*WGPUProcComputePassEncoderExampleSetPushConstants)(WGPUExampleComputePassEncoder computePassEncoder,  offset,  byteSize,  code) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderExampleWriteTimestamp:
 * > @copydoc wgpuComputePassEncoderWriteTimestamp
 */
typedef void (*WGPUProcComputePassEncoderExampleWriteTimestamp)(WGPUExampleComputePassEncoder computePassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Instance
/**
 * Proc pointer type for @ref wgpuInstanceExampleEnumerateAdapters:
 * > @copydoc wgpuInstanceEnumerateAdapters
 */
typedef void (*WGPUProcInstanceExampleEnumerateAdapters)(WGPUExampleInstance instance, WGPU_NULLABLE  options,  adapters) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceExampleGenerateReport:
 * > @copydoc wgpuInstanceGenerateReport
 */
typedef void (*WGPUProcInstanceExampleGenerateReport)(WGPUExampleInstance instance,  report) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPassEncoder
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleBeginPipelineStatisticsQuery:
 * > @copydoc wgpuRenderPassEncoderBeginPipelineStatisticsQuery
 */
typedef void (*WGPUProcRenderPassEncoderExampleBeginPipelineStatisticsQuery)(WGPUExampleRenderPassEncoder renderPassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleEndPipelineStatisticsQuery:
 * > @copydoc wgpuRenderPassEncoderEndPipelineStatisticsQuery
 */
typedef void (*WGPUProcRenderPassEncoderExampleEndPipelineStatisticsQuery)(WGPUExampleRenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleMultiDrawIndexedIndirect:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndexedIndirect
 */
typedef void (*WGPUProcRenderPassEncoderExampleMultiDrawIndexedIndirect)(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  count) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleMultiDrawIndexedIndirectCount:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndexedIndirectCount
 */
typedef void (*WGPUProcRenderPassEncoderExampleMultiDrawIndexedIndirectCount)(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  countBuffer,  countBufferOffset,  maxCount) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleMultiDrawIndirect:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndirect
 */
typedef void (*WGPUProcRenderPassEncoderExampleMultiDrawIndirect)(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  count) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleMultiDrawIndirectCount:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndirectCount
 */
typedef void (*WGPUProcRenderPassEncoderExampleMultiDrawIndirectCount)(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  countBuffer,  countBufferOffset,  maxCount) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleSetPushConstants:
 * > @copydoc wgpuRenderPassEncoderSetPushConstants
 */
typedef void (*WGPUProcRenderPassEncoderExampleSetPushConstants)(WGPUExampleRenderPassEncoder renderPassEncoder,  offset,  stages,  byteSize,  code) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderExampleWriteTimestamp:
 * > @copydoc wgpuRenderPassEncoderWriteTimestamp
 */
typedef void (*WGPUProcRenderPassEncoderExampleWriteTimestamp)(WGPUExampleRenderPassEncoder renderPassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_PROCS)

#if !defined(WGPU_SKIP_DECLARATIONS)
/**
 * \defgroup GlobalFunctions Global Functions
 * \brief Functions that are not specific to an object.
 *
 * @{
 */
WGPU_EXPORT void wgpuExampleSetLogCallback( callback) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuExampleSetLogLevel( level) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuExampleGetVersion() WGPU_FUNCTION_ATTRIBUTE;

/** @} */

/**
 * \defgroup Methods Methods
 * \brief Functions that are relative to a specific object.
 *
 * @{
 */

/**
 * \defgroup WGPUComputePassEncoderMethods WGPUComputePassEncoder methods
 * \brief Functions whose first argument has type WGPUComputePassEncoder.
 *
 * @{
 */
WGPU_EXPORT void wgpuComputePassEncoderExampleBeginPipelineStatisticsQuery(WGPUExampleComputePassEncoder computePassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderExampleEndPipelineStatisticsQuery(WGPUExampleComputePassEncoder computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderExampleSetPushConstants(WGPUExampleComputePassEncoder computePassEncoder,  offset,  byteSize,  code) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderExampleWriteTimestamp(WGPUExampleComputePassEncoder computePassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPUInstanceMethods WGPUInstance methods
 * \brief Functions whose first argument has type WGPUInstance.
 *
 * @{
 */
/**
 * @param options
 * This parameter is @ref ReturnedWithOwnership.
 *
 * @param adapters
 * This parameter is @ref ReturnedWithOwnership.
 */
WGPU_EXPORT void wgpuInstanceExampleEnumerateAdapters(WGPUExampleInstance instance, WGPU_NULLABLE  options,  adapters) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param report
 * This parameter is @ref ReturnedWithOwnership.
 */
WGPU_EXPORT void wgpuInstanceExampleGenerateReport(WGPUExampleInstance instance,  report) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderPassEncoderMethods WGPURenderPassEncoder methods
 * \brief Functions whose first argument has type WGPURenderPassEncoder.
 *
 * @{
 */
WGPU_EXPORT void wgpuRenderPassEncoderExampleBeginPipelineStatisticsQuery(WGPUExampleRenderPassEncoder renderPassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleEndPipelineStatisticsQuery(WGPUExampleRenderPassEncoder renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleMultiDrawIndexedIndirect(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  count) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleMultiDrawIndexedIndirectCount(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  countBuffer,  countBufferOffset,  maxCount) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleMultiDrawIndirect(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  count) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleMultiDrawIndirectCount(WGPUExampleRenderPassEncoder renderPassEncoder,  buffer,  offset,  countBuffer,  countBufferOffset,  maxCount) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleSetPushConstants(WGPUExampleRenderPassEncoder renderPassEncoder,  offset,  stages,  byteSize,  code) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderExampleWriteTimestamp(WGPUExampleRenderPassEncoder renderPassEncoder,  querySet,  queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/** @} */


/** @} */

#endif  // !defined(WGPU_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBGPU_SAMPLE_EXTENSION_H_
