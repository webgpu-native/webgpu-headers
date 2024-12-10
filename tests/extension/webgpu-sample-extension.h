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
#define WGPU_TEST_VALUE_UNDEFINED_EXAMPLE (UINT32_MAX)


/** @} */

/**
 * \defgroup UtilityTypes Utility Types
 *
 * @{
 */
/**
 * A typedef added for this extension.
 */
typedef uint32_t WGPUTestEXAMPLE;


/** @} */

/**
 * \defgroup Objects Objects
 * \brief Opaque, non-dispatchable handles to WebGPU objects.
 *
 * @{
 */
typedef struct WGPUComputePassEncoderEXAMPLEImpl* WGPUComputePassEncoderEXAMPLE WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPUInstanceEXAMPLEImpl* WGPUInstanceEXAMPLE WGPU_OBJECT_ATTRIBUTE;
typedef struct WGPURenderPassEncoderEXAMPLEImpl* WGPURenderPassEncoderEXAMPLE WGPU_OBJECT_ATTRIBUTE;


/** @} */
// Structure forward declarations
struct WGPUBindGroupEntryExtrasEXAMPLE;
struct WGPUBindGroupLayoutEntryExtrasEXAMPLE;
struct WGPUDeviceExtrasEXAMPLE;
struct WGPUInstanceEnumerateAdapterOptionsEXAMPLE;
struct WGPUInstanceExtrasEXAMPLE;
struct WGPUNativeLimitsEXAMPLE;
struct WGPUPushConstantRangeEXAMPLE;
struct WGPUQuerySetDescriptorExtrasEXAMPLE;
struct WGPURegistryReportEXAMPLE;
struct WGPUShaderDefineEXAMPLE;
struct WGPUSurfaceConfigurationExtrasEXAMPLE;
struct WGPUHubReportEXAMPLE;
struct WGPUPipelineLayoutExtrasEXAMPLE;
struct WGPURequiredLimitsExtrasEXAMPLE;
struct WGPUShaderSourceGLSLEXAMPLE;
struct WGPUSupportedLimitsExtrasEXAMPLE;
struct WGPUGlobalReportEXAMPLE;

// Callback info structure forward declarations
struct WGPULogCallbackInfoEXAMPLE;


/**
 * \defgroup Enumerations Enumerations
 * \brief Enums.
 *
 * @{
 */
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_PushConstants_EXAMPLE, 0x00060001);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TextureAdapterSpecificFormatFeatures_EXAMPLE, 0x00060002);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_MultiDrawIndirect_EXAMPLE, 0x00060003);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_MultiDrawIndirectCount_EXAMPLE, 0x00060004);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_VertexWritableStorage_EXAMPLE, 0x00060005);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TextureBindingArray_EXAMPLE, 0x00060006);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_SampledTextureAndStorageBufferArrayNonUniformIndexing_EXAMPLE, 0x00060007);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_PipelineStatisticsQuery_EXAMPLE, 0x00060008);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_StorageResourceBindingArray_EXAMPLE, 0x00060009);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_PartiallyBoundBindingArray_EXAMPLE, 0x0006000A);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TextureFormat16bitNorm_EXAMPLE, 0x0006000B);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TextureCompressionAstcHdr_EXAMPLE, 0x0006000C);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_MappablePrimaryBuffers_EXAMPLE, 0x0006000D);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_BufferBindingArray_EXAMPLE, 0x0006000E);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_UniformBufferAndStorageTextureArrayNonUniformIndexing_EXAMPLE, 0x0006000F);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_SpirvShaderPassthrough_EXAMPLE, 0x00060010);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_VertexAttribute64bit_EXAMPLE, 0x00060011);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TextureFormatNv12_EXAMPLE, 0x00060012);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_RayTracingAccelerationStructure_EXAMPLE, 0x00060013);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_RayQuery_EXAMPLE, 0x00060014);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ShaderF64_EXAMPLE, 0x00060015);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ShaderI16_EXAMPLE, 0x00060016);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ShaderPrimitiveIndex_EXAMPLE, 0x00060017);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_ShaderEarlyDepthTest_EXAMPLE, 0x00060018);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_Subgroup_EXAMPLE, 0x00060019);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_SubgroupVertex_EXAMPLE, 0x0006001A);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_SubgroupBarrier_EXAMPLE, 0x0006001B);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TimestampQueryInsideEncoders_EXAMPLE, 0x0006001C);
_wgpu_EXTEND_ENUM(WGPUFeature, WGPUFeature_TimestampQueryInsidePasses_EXAMPLE, 0x0006001D);

/**
 * Compiler to use when compiling DirectX 12 shaders.
 */
typedef enum WGPUDx12CompilerEXAMPLE {
    /**
     * `0x00060000`.
     * Indicates no value is passed for this argument. See @ref SentinelValues.
     */
    WGPUDx12Compiler_Undefined_EXAMPLE = 0x00060000,
    WGPUDx12Compiler_Fxc_EXAMPLE = 0x00060001,
    WGPUDx12Compiler_Dxc_EXAMPLE = 0x00060002,
    WGPUDx12Compiler_Force32_EXAMPLE = 0x7FFFFFFF
} WGPUDx12CompilerEXAMPLE WGPU_ENUM_ATTRIBUTE;

/**
 * Minor version of OpenGL ES 3.x to use.
 */
typedef enum WGPUGles3MinorVersionEXAMPLE {
    WGPUGles3MinorVersion_Automatic_EXAMPLE = 0x00060000,
    /**
     * `0x00060001`.
     * Use OpenGL ES 3.0
     */
    WGPUGles3MinorVersion_Version0_EXAMPLE = 0x00060001,
    /**
     * `0x00060002`.
     * Use OpenGL ES 3.1
     */
    WGPUGles3MinorVersion_Version1_EXAMPLE = 0x00060002,
    /**
     * `0x00060003`.
     * Use OpenGL ES 3.2
     */
    WGPUGles3MinorVersion_Version2_EXAMPLE = 0x00060003,
    WGPUGles3MinorVersion_Force32_EXAMPLE = 0x7FFFFFFF
} WGPUGles3MinorVersionEXAMPLE WGPU_ENUM_ATTRIBUTE;

/**
 * Verbosity of the log, used in @ref wgpuSetLogLevel.
 */
typedef enum WGPULogLevelEXAMPLE {
    WGPULogLevel_Off_EXAMPLE = 0x00060000,
    WGPULogLevel_Error_EXAMPLE = 0x00060001,
    WGPULogLevel_Warn_EXAMPLE = 0x00060002,
    WGPULogLevel_Info_EXAMPLE = 0x00060003,
    WGPULogLevel_Debug_EXAMPLE = 0x00060004,
    WGPULogLevel_Trace_EXAMPLE = 0x00060005,
    WGPULogLevel_Force32_EXAMPLE = 0x7FFFFFFF
} WGPULogLevelEXAMPLE WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUNativeTextureFormatEXAMPLE {
    /**
     * `0x00060001`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_R16Unorm_EXAMPLE = 0x00060001,
    /**
     * `0x00060002`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_R16Snorm_EXAMPLE = 0x00060002,
    /**
     * `0x00060003`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_Rg16Unorm_EXAMPLE = 0x00060003,
    /**
     * `0x00060004`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_Rg16Snorm_EXAMPLE = 0x00060004,
    /**
     * `0x00060005`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_Rgba16Unorm_EXAMPLE = 0x00060005,
    /**
     * `0x00060006`.
     * Available when Features::TextureFormat16bitNorm is enabled
     */
    WGPUNativeTextureFormat_Rgba16Snorm_EXAMPLE = 0x00060006,
    /**
     * `0x00060007`.
     * Available when Features::TextureFormatNv12 is enabled
     */
    WGPUNativeTextureFormat_ClipperInvocations_EXAMPLE = 0x00060007,
    WGPUNativeTextureFormat_Force32_EXAMPLE = 0x7FFFFFFF
} WGPUNativeTextureFormatEXAMPLE WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUPipelineStatisticNameEXAMPLE {
    WGPUPipelineStatisticName_VertexShaderInvocations_EXAMPLE = 0x00060001,
    WGPUPipelineStatisticName_ClipperInvocations_EXAMPLE = 0x00060002,
    WGPUPipelineStatisticName_ClipperPrimitivesOut_EXAMPLE = 0x00060003,
    WGPUPipelineStatisticName_FragmentShaderInvocations_EXAMPLE = 0x00060004,
    WGPUPipelineStatisticName_ComputeShaderInvocations_EXAMPLE = 0x00060005,
    WGPUPipelineStatisticName_Force32_EXAMPLE = 0x7FFFFFFF
} WGPUPipelineStatisticNameEXAMPLE WGPU_ENUM_ATTRIBUTE;

typedef enum WGPUQueryTypeEXAMPLE {
    WGPUQueryType_PipelineStatistics_EXAMPLE = 0x00060001,
    WGPUQueryType_Force32_EXAMPLE = 0x7FFFFFFF
} WGPUQueryTypeEXAMPLE WGPU_ENUM_ATTRIBUTE;


/** @} */

/**
 * \defgroup Bitflags Bitflags
 * \brief Type and constant definitions for bitflag types.
 *
 * @{
 */
typedef WGPUFlags WGPUInstanceBackend_EXAMPLE;
static const WGPUInstanceBackend WGPUInstanceBackend_All_EXAMPLE = 0x0000000000000000;
static const WGPUInstanceBackend WGPUInstanceBackend_Vulkan_EXAMPLE = 0x0000000000000001;
static const WGPUInstanceBackend WGPUInstanceBackend_Gl_EXAMPLE = 0x0000000000000002;
static const WGPUInstanceBackend WGPUInstanceBackend_Metal_EXAMPLE = 0x0000000000000004;
static const WGPUInstanceBackend WGPUInstanceBackend_Dx12_EXAMPLE = 0x0000000000000008;
static const WGPUInstanceBackend WGPUInstanceBackend_Dx11_EXAMPLE = 0x0000000000000010;
static const WGPUInstanceBackend WGPUInstanceBackend_BrowserWebgpu_EXAMPLE = 0x0000000000000020;
static const WGPUInstanceBackend WGPUInstanceBackend_Primary_EXAMPLE = 0x000000000000002D /* Vulkan_EXAMPLE | Metal_EXAMPLE | Dx12_EXAMPLE | BrowserWebgpu_EXAMPLE */;
static const WGPUInstanceBackend WGPUInstanceBackend_Secondary_EXAMPLE = 0x0000000000000012 /* Gl_EXAMPLE | Dx11_EXAMPLE */;

typedef WGPUFlags WGPUInstanceOption_EXAMPLE;
static const WGPUInstanceOption WGPUInstanceOption_Default_EXAMPLE = 0x0000000000000000;
static const WGPUInstanceOption WGPUInstanceOption_Debug_EXAMPLE = 0x0000000000000001;
static const WGPUInstanceOption WGPUInstanceOption_Validation_EXAMPLE = 0x0000000000000002;
static const WGPUInstanceOption WGPUInstanceOption_DiscardHalLabels_EXAMPLE = 0x0000000000000004;


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
typedef void (*WGPULogCallbackEXAMPLE)(WGPULogLevelEXAMPLE level, WGPUStringView message, WGPU_NULLABLE void* userdata1, WGPU_NULLABLE void* userdata2) WGPU_FUNCTION_ATTRIBUTE;

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
typedef struct WGPULogCallbackInfoEXAMPLE {
    WGPUChainedStruct const * nextInChain;
    WGPUCallbackMode mode;
    WGPULogCallbackEXAMPLE callback;
    WGPU_NULLABLE void* userdata1;
    WGPU_NULLABLE void* userdata2;
} WGPULogCallbackInfoEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPULogCallbackInfoEXAMPLE.
 */
#define WGPU_LOG_CALLBACK_INFO_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPULogCallbackInfoEXAMPLE, { \
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
typedef struct WGPUBindGroupEntryExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * Array count for `buffers`. The `INIT` macro sets this to 0.
     */
    size_t bufferCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUBufferEXAMPLE const * buffers;
    /**
     * Array count for `samplers`. The `INIT` macro sets this to 0.
     */
    size_t samplerCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUSamplerEXAMPLE const * samplers;
    /**
     * Array count for `textureViews`. The `INIT` macro sets this to 0.
     */
    size_t textureViewCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUTextureViewEXAMPLE const * textureViews;
} WGPUBindGroupEntryExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUBindGroupEntryExtrasEXAMPLE.
 */
#define WGPU_BIND_GROUP_ENTRY_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupEntryExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_BindGroupEntryExtrasEXAMPLE _wgpu_COMMA \
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
typedef struct WGPUBindGroupLayoutEntryExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to `0`.
     */
    uint32_t count;
} WGPUBindGroupLayoutEntryExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUBindGroupLayoutEntryExtrasEXAMPLE.
 */
#define WGPU_BIND_GROUP_LAYOUT_ENTRY_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUBindGroupLayoutEntryExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_BindGroupLayoutEntryExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.count=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_DEVICE_EXTRAS_INIT as initializer.
 */
typedef struct WGPUDeviceExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView tracePath;
} WGPUDeviceExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUDeviceExtrasEXAMPLE.
 */
#define WGPU_DEVICE_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUDeviceExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_DeviceExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.tracePath=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_INSTANCE_ENUMERATE_ADAPTER_OPTIONS_INIT as initializer.
 */
typedef struct WGPUInstanceEnumerateAdapterOptionsEXAMPLE {
    WGPUChainedStructOut * nextInChain;
    /**
     * The `INIT` macro sets this to (@ref WGPUInstanceBackend)0.
     */
    WGPUInstanceBackendEXAMPLE backends;
} WGPUInstanceEnumerateAdapterOptionsEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUInstanceEnumerateAdapterOptionsEXAMPLE.
 */
#define WGPU_INSTANCE_ENUMERATE_ADAPTER_OPTIONS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceEnumerateAdapterOptionsEXAMPLE, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.backends=*/_wgpu_ENUM_ZERO_INIT(WGPUInstanceBackend) _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_INSTANCE_EXTRAS_INIT as initializer.
 */
typedef struct WGPUInstanceExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to @ref WGPUInstanceBackend_None.
     */
    WGPUInstanceBackendEXAMPLE backends;
    /**
     * The `INIT` macro sets this to @ref WGPUInstanceOption_None.
     */
    WGPUInstanceOptionEXAMPLE options;
    /**
     * The `INIT` macro sets this to (@ref WGPUDx12Compiler)0.
     */
    WGPUDx12CompilerEXAMPLE dx12ShaderCompiler;
    /**
     * The `INIT` macro sets this to (@ref WGPUGles3MinorVersion)0.
     */
    WGPUGles3MinorVersionEXAMPLE gles3MinorVersion;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView dxilPath;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView dxcPath;
} WGPUInstanceExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUInstanceExtrasEXAMPLE.
 */
#define WGPU_INSTANCE_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUInstanceExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_InstanceExtrasEXAMPLE _wgpu_COMMA \
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
typedef struct WGPUNativeLimitsEXAMPLE {
    /** This struct chain is used as mutable in some places and immutable in others. */
    WGPUChainedStructOut chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_LIMIT_U32_UNDEFINED.
     */
    uint32_t maxPushConstantSize;
    /**
     * The `INIT` macro sets this to @ref WGPU_LIMIT_U32_UNDEFINED.
     */
    uint32_t maxNonSamplerBindings;
} WGPUNativeLimitsEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUNativeLimitsEXAMPLE.
 */
#define WGPU_NATIVE_LIMITS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUNativeLimitsEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStructOut, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_NativeLimitsEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.maxPushConstantSize=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
    /*.maxNonSamplerBindings=*/WGPU_LIMIT_U32_UNDEFINED _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_PUSH_CONSTANT_RANGE_INIT as initializer.
 */
typedef struct WGPUPushConstantRangeEXAMPLE {
    WGPUChainedStruct const * nextInChain;
    /**
     * The `INIT` macro sets this to @ref WGPUShaderStageFlags_None.
     */
    WGPUShaderStageFlagsEXAMPLE stages;
    /**
     * The `INIT` macro sets this to `0`.
     */
    uint32_t start;
    /**
     * The `INIT` macro sets this to `0`.
     */
    uint32_t end;
} WGPUPushConstantRangeEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUPushConstantRangeEXAMPLE.
 */
#define WGPU_PUSH_CONSTANT_RANGE_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPushConstantRangeEXAMPLE, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.stages=*/WGPUShaderStageFlags_None _wgpu_COMMA \
    /*.start=*/0 _wgpu_COMMA \
    /*.end=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_QUERY_SET_DESCRIPTOR_EXTRAS_INIT as initializer.
 */
typedef struct WGPUQuerySetDescriptorExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * Array count for `pipelineStatistics`. The `INIT` macro sets this to 0.
     */
    size_t pipelineStatisticCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUPipelineStatisticNameEXAMPLE const * pipelineStatistics;
} WGPUQuerySetDescriptorExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUQuerySetDescriptorExtrasEXAMPLE.
 */
#define WGPU_QUERY_SET_DESCRIPTOR_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUQuerySetDescriptorExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_QuerySetDescriptorExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.pipelineStatisticCount=*/0 _wgpu_COMMA \
    /*.pipelineStatistics=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_REGISTRY_REPORT_INIT as initializer.
 */
typedef struct WGPURegistryReportEXAMPLE {
    /**
     * The `INIT` macro sets this to `0`.
     */
    size_t numAllocated;
    /**
     * The `INIT` macro sets this to `0`.
     */
    size_t numKeptFromUser;
    /**
     * The `INIT` macro sets this to `0`.
     */
    size_t numReleasedFromUser;
    /**
     * The `INIT` macro sets this to `0`.
     */
    size_t elementSize;
} WGPURegistryReportEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPURegistryReportEXAMPLE.
 */
#define WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPURegistryReportEXAMPLE, { \
    /*.numAllocated=*/0 _wgpu_COMMA \
    /*.numKeptFromUser=*/0 _wgpu_COMMA \
    /*.numReleasedFromUser=*/0 _wgpu_COMMA \
    /*.elementSize=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SHADER_DEFINE_INIT as initializer.
 */
typedef struct WGPUShaderDefineEXAMPLE {
    WGPUChainedStruct const * nextInChain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView name;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView value;
} WGPUShaderDefineEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUShaderDefineEXAMPLE.
 */
#define WGPU_SHADER_DEFINE_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderDefineEXAMPLE, { \
    /*.nextInChain=*/NULL _wgpu_COMMA \
    /*.name=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.value=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SURFACE_CONFIGURATION_EXTRAS_INIT as initializer.
 */
typedef struct WGPUSurfaceConfigurationExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to `0`.
     */
    uint32_t desiredMaximumFrameLatency;
} WGPUSurfaceConfigurationExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUSurfaceConfigurationExtrasEXAMPLE.
 */
#define WGPU_SURFACE_CONFIGURATION_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSurfaceConfigurationExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SurfaceConfigurationExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.desiredMaximumFrameLatency=*/0 _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_HUB_REPORT_INIT as initializer.
 */
typedef struct WGPUHubReportEXAMPLE {
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE adapters;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE devices;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE queues;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE pipelineLayouts;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE shaderModules;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE bindGroupLayouts;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE bindGroups;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE commandBuffers;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE renderBundles;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE renderPipelines;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE computePipelines;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE pipelineCaches;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE querySets;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE buffers;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE textures;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE textureViews;
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE samplers;
} WGPUHubReportEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUHubReportEXAMPLE.
 */
#define WGPU_HUB_REPORT_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUHubReportEXAMPLE, { \
    /*.adapters=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.devices=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.queues=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.pipelineLayouts=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.shaderModules=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.bindGroupLayouts=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.bindGroups=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.commandBuffers=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.renderBundles=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.renderPipelines=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.computePipelines=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.pipelineCaches=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.querySets=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.buffers=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.textures=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.textureViews=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.samplers=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_PIPELINE_LAYOUT_EXTRAS_INIT as initializer.
 */
typedef struct WGPUPipelineLayoutExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * Array count for `pushConstantRanges`. The `INIT` macro sets this to 0.
     */
    size_t pushConstantRangeCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUPushConstantRangeEXAMPLE pushConstantRanges;
} WGPUPipelineLayoutExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUPipelineLayoutExtrasEXAMPLE.
 */
#define WGPU_PIPELINE_LAYOUT_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUPipelineLayoutExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_PipelineLayoutExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.pushConstantRangeCount=*/0 _wgpu_COMMA \
    /*.pushConstantRanges=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_REQUIRED_LIMITS_EXTRAS_INIT as initializer.
 */
typedef struct WGPURequiredLimitsExtrasEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_NATIVE_LIMITS_EXAMPLE_INIT.
     */
    WGPUNativeLimitsEXAMPLE limits;
} WGPURequiredLimitsExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPURequiredLimitsExtrasEXAMPLE.
 */
#define WGPU_REQUIRED_LIMITS_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPURequiredLimitsExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_RequiredLimitsExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.limits=*/WGPU_NATIVE_LIMITS_EXAMPLE_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SHADER_SOURCE_GLSL_INIT as initializer.
 */
typedef struct WGPUShaderSourceGLSLEXAMPLE {
    WGPUChainedStruct chain;
    /**
     * This is a \ref NonNullInputString.
     *
     * The `INIT` macro sets this to @ref WGPU_STRING_VIEW_INIT.
     */
    WGPUStringView code;
    /**
     * The `INIT` macro sets this to @ref WGPUShaderStage_None.
     */
    WGPUShaderStageEXAMPLE stage;
    /**
     * Array count for `defines`. The `INIT` macro sets this to 0.
     */
    size_t defineCount;
    /**
     * The `INIT` macro sets this to `NULL`.
     */
    WGPUShaderDefineEXAMPLE defines;
} WGPUShaderSourceGLSLEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUShaderSourceGLSLEXAMPLE.
 */
#define WGPU_SHADER_SOURCE_GLSL_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUShaderSourceGLSLEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStruct, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_ShaderSourceGLSLEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.code=*/WGPU_STRING_VIEW_INIT _wgpu_COMMA \
    /*.stage=*/WGPUShaderStage_None _wgpu_COMMA \
    /*.defineCount=*/0 _wgpu_COMMA \
    /*.defines=*/NULL _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_SUPPORTED_LIMITS_EXTRAS_INIT as initializer.
 */
typedef struct WGPUSupportedLimitsExtrasEXAMPLE {
    WGPUChainedStructOut chain;
    /**
     * The `INIT` macro sets this to @ref WGPU_NATIVE_LIMITS_EXAMPLE_INIT.
     */
    WGPUNativeLimitsEXAMPLE limits;
} WGPUSupportedLimitsExtrasEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUSupportedLimitsExtrasEXAMPLE.
 */
#define WGPU_SUPPORTED_LIMITS_EXTRAS_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUSupportedLimitsExtrasEXAMPLE, { \
    /*.chain=*/_wgpu_MAKE_INIT_STRUCT(WGPUChainedStructOut, { \
        /*.next=*/NULL _wgpu_COMMA \
        /*.sType=*/WGPUSType_SupportedLimitsExtrasEXAMPLE _wgpu_COMMA \
    }) _wgpu_COMMA \
    /*.limits=*/WGPU_NATIVE_LIMITS_EXAMPLE_INIT _wgpu_COMMA \
})

/**
 * Default values can be set using @ref WGPU_GLOBAL_REPORT_INIT as initializer.
 */
typedef struct WGPUGlobalReportEXAMPLE {
    /**
     * The `INIT` macro sets this to @ref WGPU_REGISTRY_REPORT_EXAMPLE_INIT.
     */
    WGPURegistryReportEXAMPLE surfaces;
    /**
     * The `INIT` macro sets this to @ref WGPU_HUB_REPORT_EXAMPLE_INIT.
     */
    WGPUHubReportEXAMPLE hub;
} WGPUGlobalReportEXAMPLE WGPU_STRUCTURE_ATTRIBUTE;

/**
 * Initializer for @ref WGPUGlobalReportEXAMPLE.
 */
#define WGPU_GLOBAL_REPORT_EXAMPLE_INIT _wgpu_MAKE_INIT_STRUCT(WGPUGlobalReportEXAMPLE, { \
    /*.surfaces=*/WGPU_REGISTRY_REPORT_EXAMPLE_INIT _wgpu_COMMA \
    /*.hub=*/WGPU_HUB_REPORT_EXAMPLE_INIT _wgpu_COMMA \
})

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

#if !defined(WGPU_SKIP_PROCS)

/**
 * Proc pointer type for @ref wgpuSetLogCallbackEXAMPLE:
 * > @copydoc wgpuSetLogCallbackEXAMPLE
 */
typedef void (*WGPUProcSetLogCallbackEXAMPLE)(WGPULogCallbackEXAMPLE callback) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuSetLogLevelEXAMPLE:
 * > @copydoc wgpuSetLogLevelEXAMPLE
 */
typedef void (*WGPUProcSetLogLevelEXAMPLE)(WGPULogLevelEXAMPLE level) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuGetVersionEXAMPLE:
 * > @copydoc wgpuGetVersionEXAMPLE
 */
typedef uint32_t (*WGPUProcGetVersionEXAMPLE)() WGPU_FUNCTION_ATTRIBUTE;
// Procs of ComputePassEncoder
/**
 * Proc pointer type for @ref wgpuComputePassEncoderBeginPipelineStatisticsQueryEXAMPLE:
 * > @copydoc wgpuComputePassEncoderBeginPipelineStatisticsQueryEXAMPLE
 */
typedef void (*WGPUProcComputePassEncoderBeginPipelineStatisticsQueryEXAMPLE)(WGPUComputePassEncoderEXAMPLE computePassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderEndPipelineStatisticsQueryEXAMPLE:
 * > @copydoc wgpuComputePassEncoderEndPipelineStatisticsQueryEXAMPLE
 */
typedef void (*WGPUProcComputePassEncoderEndPipelineStatisticsQueryEXAMPLE)(WGPUComputePassEncoderEXAMPLE computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderSetPushConstantsEXAMPLE:
 * > @copydoc wgpuComputePassEncoderSetPushConstantsEXAMPLE
 */
typedef void (*WGPUProcComputePassEncoderSetPushConstantsEXAMPLE)(WGPUComputePassEncoderEXAMPLE computePassEncoder, uint32_t offset, size_t byteSize, void const * code) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuComputePassEncoderWriteTimestampEXAMPLE:
 * > @copydoc wgpuComputePassEncoderWriteTimestampEXAMPLE
 */
typedef void (*WGPUProcComputePassEncoderWriteTimestampEXAMPLE)(WGPUComputePassEncoderEXAMPLE computePassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;

// Procs of Instance
/**
 * Proc pointer type for @ref wgpuInstanceEnumerateAdaptersEXAMPLE:
 * > @copydoc wgpuInstanceEnumerateAdaptersEXAMPLE
 */
typedef void (*WGPUProcInstanceEnumerateAdaptersEXAMPLE)(WGPUInstanceEXAMPLE instance, WGPU_NULLABLE WGPUInstanceEnumerateAdapterOptionsEXAMPLE const * options, WGPUAdapterEXAMPLE * adapters) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuInstanceGenerateReportEXAMPLE:
 * > @copydoc wgpuInstanceGenerateReportEXAMPLE
 */
typedef void (*WGPUProcInstanceGenerateReportEXAMPLE)(WGPUInstanceEXAMPLE instance, WGPUGlobalReportEXAMPLE * report) WGPU_FUNCTION_ATTRIBUTE;

// Procs of RenderPassEncoder
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderBeginPipelineStatisticsQueryEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderBeginPipelineStatisticsQueryEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderBeginPipelineStatisticsQueryEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderEndPipelineStatisticsQueryEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderEndPipelineStatisticsQueryEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderEndPipelineStatisticsQueryEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderMultiDrawIndexedIndirectEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndexedIndirectEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndexedIndirectEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, uint32_t count) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderMultiDrawIndexedIndirectCountEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndexedIndirectCountEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndexedIndirectCountEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, WGPUBufferEXAMPLE countBuffer, uint64_t countBufferOffset, uint32_t maxCount) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderMultiDrawIndirectEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndirectEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndirectEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, uint32_t count) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderMultiDrawIndirectCountEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderMultiDrawIndirectCountEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderMultiDrawIndirectCountEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, WGPUBufferEXAMPLE countBuffer, uint64_t countBufferOffset, uint32_t maxCount) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderSetPushConstantsEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderSetPushConstantsEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderSetPushConstantsEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, uint32_t offset, WGPUShaderStageEXAMPLE stages, size_t byteSize, void const * code) WGPU_FUNCTION_ATTRIBUTE;
/**
 * Proc pointer type for @ref wgpuRenderPassEncoderWriteTimestampEXAMPLE:
 * > @copydoc wgpuRenderPassEncoderWriteTimestampEXAMPLE
 */
typedef void (*WGPUProcRenderPassEncoderWriteTimestampEXAMPLE)(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;

#endif  // !defined(WGPU_SKIP_PROCS)

#if !defined(WGPU_SKIP_DECLARATIONS)
/**
 * \defgroup GlobalFunctions Global Functions
 * \brief Functions that are not specific to an object.
 *
 * @{
 */
WGPU_EXPORT void wgpuSetLogCallbackEXAMPLE(WGPULogCallbackEXAMPLE callback) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuSetLogLevelEXAMPLE(WGPULogLevelEXAMPLE level) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT uint32_t wgpuGetVersionEXAMPLE() WGPU_FUNCTION_ATTRIBUTE;

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
WGPU_EXPORT void wgpuComputePassEncoderBeginPipelineStatisticsQueryEXAMPLE(WGPUComputePassEncoderEXAMPLE computePassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderEndPipelineStatisticsQueryEXAMPLE(WGPUComputePassEncoderEXAMPLE computePassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderSetPushConstantsEXAMPLE(WGPUComputePassEncoderEXAMPLE computePassEncoder, uint32_t offset, size_t byteSize, void const * code) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuComputePassEncoderWriteTimestampEXAMPLE(WGPUComputePassEncoderEXAMPLE computePassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
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
WGPU_EXPORT void wgpuInstanceEnumerateAdaptersEXAMPLE(WGPUInstanceEXAMPLE instance, WGPU_NULLABLE WGPUInstanceEnumerateAdapterOptionsEXAMPLE const * options, WGPUAdapterEXAMPLE * adapters) WGPU_FUNCTION_ATTRIBUTE;
/**
 * @param report
 * This parameter is @ref ReturnedWithOwnership.
 */
WGPU_EXPORT void wgpuInstanceGenerateReportEXAMPLE(WGPUInstanceEXAMPLE instance, WGPUGlobalReportEXAMPLE * report) WGPU_FUNCTION_ATTRIBUTE;
/** @} */



/**
 * \defgroup WGPURenderPassEncoderMethods WGPURenderPassEncoder methods
 * \brief Functions whose first argument has type WGPURenderPassEncoder.
 *
 * @{
 */
WGPU_EXPORT void wgpuRenderPassEncoderBeginPipelineStatisticsQueryEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderEndPipelineStatisticsQueryEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndexedIndirectEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, uint32_t count) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndexedIndirectCountEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, WGPUBufferEXAMPLE countBuffer, uint64_t countBufferOffset, uint32_t maxCount) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndirectEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, uint32_t count) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderMultiDrawIndirectCountEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUBufferEXAMPLE buffer, uint64_t offset, WGPUBufferEXAMPLE countBuffer, uint64_t countBufferOffset, uint32_t maxCount) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderSetPushConstantsEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, uint32_t offset, WGPUShaderStageEXAMPLE stages, size_t byteSize, void const * code) WGPU_FUNCTION_ATTRIBUTE;
WGPU_EXPORT void wgpuRenderPassEncoderWriteTimestampEXAMPLE(WGPURenderPassEncoderEXAMPLE renderPassEncoder, WGPUQuerySetEXAMPLE querySet, uint32_t queryIndex) WGPU_FUNCTION_ATTRIBUTE;
/** @} */


/** @} */

#endif  // !defined(WGPU_SKIP_DECLARATIONS)

#ifdef __cplusplus
} // extern "C"
#endif

#endif // WEBGPU_SAMPLE_EXTENSION_H_
