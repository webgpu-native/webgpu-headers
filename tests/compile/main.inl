#include "../../webgpu.h"

// Compile-test the instantiation of all of the macros, and spot-check types
int main(void) {
    {
        WGPUStringView s = WGPU_STRING_VIEW_INIT;
        s.length = WGPU_STRLEN;
    }
    {
        WGPUTextureViewDescriptor a;
        a.mipLevelCount = WGPU_MIP_LEVEL_COUNT_UNDEFINED;
        a.arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;
    }
    {
        WGPUTexelCopyBufferLayout a;
        uint32_t x = a.bytesPerRow = WGPU_COPY_STRIDE_UNDEFINED;
        uint32_t y = a.rowsPerImage = WGPU_COPY_STRIDE_UNDEFINED;
    }
    {
        WGPURenderPassColorAttachment a;
        a.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    }
    {
        WGPUBindGroupEntry a;
        uint64_t x = a.size = WGPU_WHOLE_SIZE;
    }
    {
        uint64_t x = WGPU_WHOLE_MAP_SIZE;
    }
    {
        WGPULimits a;
        uint32_t x = a.maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t y = a.maxBufferSize = WGPU_LIMIT_U64_UNDEFINED;
    }
    {
        WGPUPassTimestampWrites a;
        a.beginningOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        a.endOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
    }

    // Check that generated initializers are valid
    // TODO: Would be nice to autogenerate this so we don't forget to test any new structs.
    { WGPUBufferMapCallbackInfo x = WGPU_BUFFER_MAP_CALLBACK_INFO_INIT; }
    { WGPUCompilationInfoCallbackInfo x = WGPU_COMPILATION_INFO_CALLBACK_INFO_INIT; }
    { WGPUCreateComputePipelineAsyncCallbackInfo x = WGPU_CREATE_COMPUTE_PIPELINE_ASYNC_CALLBACK_INFO_INIT; }
    { WGPUCreateRenderPipelineAsyncCallbackInfo x = WGPU_CREATE_RENDER_PIPELINE_ASYNC_CALLBACK_INFO_INIT; }
    { WGPUDeviceLostCallbackInfo x = WGPU_DEVICE_LOST_CALLBACK_INFO_INIT; }
    { WGPUPopErrorScopeCallbackInfo x = WGPU_POP_ERROR_SCOPE_CALLBACK_INFO_INIT; }
    { WGPUQueueWorkDoneCallbackInfo x = WGPU_QUEUE_WORK_DONE_CALLBACK_INFO_INIT; }
    { WGPURequestAdapterCallbackInfo x = WGPU_REQUEST_ADAPTER_CALLBACK_INFO_INIT; }
    { WGPURequestDeviceCallbackInfo x = WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT; }
    { WGPUUncapturedErrorCallbackInfo x = WGPU_UNCAPTURED_ERROR_CALLBACK_INFO_INIT; }
    { WGPUAdapterInfo x = WGPU_ADAPTER_INFO_INIT; }
    { WGPUBindGroupEntry x = WGPU_BIND_GROUP_ENTRY_INIT; }
    { WGPUBlendComponent x = WGPU_BLEND_COMPONENT_INIT; }
    { WGPUBufferBindingLayout x = WGPU_BUFFER_BINDING_LAYOUT_INIT; }
    { WGPUBufferDescriptor x = WGPU_BUFFER_DESCRIPTOR_INIT; }
    { WGPUColor x = WGPU_COLOR_INIT; }
    { WGPUCommandBufferDescriptor x = WGPU_COMMAND_BUFFER_DESCRIPTOR_INIT; }
    { WGPUCommandEncoderDescriptor x = WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT; }
    { WGPUCompilationMessage x = WGPU_COMPILATION_MESSAGE_INIT; }
    { WGPUConstantEntry x = WGPU_CONSTANT_ENTRY_INIT; }
    { WGPUFuture x = WGPU_FUTURE_INIT; }
    { WGPUInstanceCapabilities x = WGPU_INSTANCE_CAPABILITIES_INIT; }
    { WGPULimits x = WGPU_LIMITS_INIT; }
    { WGPUMultisampleState x = WGPU_MULTISAMPLE_STATE_INIT; }
    { WGPUPassTimestampWrites x = WGPU_PASS_TIMESTAMP_WRITES_INIT; }
    { WGPUPipelineLayoutDescriptor x = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT; }
    { WGPUPrimitiveState x = WGPU_PRIMITIVE_STATE_INIT; }
    { WGPUQuerySetDescriptor x = WGPU_QUERY_SET_DESCRIPTOR_INIT; }
    { WGPUQueueDescriptor x = WGPU_QUEUE_DESCRIPTOR_INIT; }
    { WGPURenderBundleDescriptor x = WGPU_RENDER_BUNDLE_DESCRIPTOR_INIT; }
    { WGPURenderBundleEncoderDescriptor x = WGPU_RENDER_BUNDLE_ENCODER_DESCRIPTOR_INIT; }
    { WGPURenderPassDepthStencilAttachment x = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT; }
    { WGPURenderPassMaxDrawCount x = WGPU_RENDER_PASS_MAX_DRAW_COUNT_INIT; }
    { WGPURequestAdapterOptions x = WGPU_REQUEST_ADAPTER_OPTIONS_INIT; }
    { WGPUSamplerBindingLayout x = WGPU_SAMPLER_BINDING_LAYOUT_INIT; }
    { WGPUSamplerDescriptor x = WGPU_SAMPLER_DESCRIPTOR_INIT; }
    { WGPUShaderModuleDescriptor x = WGPU_SHADER_MODULE_DESCRIPTOR_INIT; }
    { WGPUShaderSourceSPIRV x = WGPU_SHADER_SOURCE_SPIRV_INIT; }
    { WGPUShaderSourceWGSL x = WGPU_SHADER_SOURCE_WGSL_INIT; }
    { WGPUStencilFaceState x = WGPU_STENCIL_FACE_STATE_INIT; }
    { WGPUStorageTextureBindingLayout x = WGPU_STORAGE_TEXTURE_BINDING_LAYOUT_INIT; }
    { WGPUSupportedFeatures x = WGPU_SUPPORTED_FEATURES_INIT; }
    { WGPUSupportedWGSLLanguageFeatures x = WGPU_SUPPORTED_WGSL_LANGUAGE_FEATURES_INIT; }
    { WGPUSurfaceCapabilities x = WGPU_SURFACE_CAPABILITIES_INIT; }
    { WGPUSurfaceConfiguration x = WGPU_SURFACE_CONFIGURATION_INIT; }
    { WGPUSurfaceDescriptor x = WGPU_SURFACE_DESCRIPTOR_INIT; }
    { WGPUSurfaceSourceAndroidNativeWindow x = WGPU_SURFACE_SOURCE_ANDROID_NATIVE_WINDOW_INIT; }
    { WGPUSurfaceSourceMetalLayer x = WGPU_SURFACE_SOURCE_METAL_LAYER_INIT; }
    { WGPUSurfaceSourceWaylandSurface x = WGPU_SURFACE_SOURCE_WAYLAND_SURFACE_INIT; }
    { WGPUSurfaceSourceWindowsHWND x = WGPU_SURFACE_SOURCE_WINDOWS_HWND_INIT; }
    { WGPUSurfaceSourceXCBWindow x = WGPU_SURFACE_SOURCE_XCB_WINDOW_INIT; }
    { WGPUSurfaceSourceXlibWindow x = WGPU_SURFACE_SOURCE_XLIB_WINDOW_INIT; }
    { WGPUSurfaceTexture x = WGPU_SURFACE_TEXTURE_INIT; }
    { WGPUTexelCopyBufferLayout x = WGPU_TEXEL_COPY_BUFFER_LAYOUT_INIT; }
    { WGPUTextureBindingLayout x = WGPU_TEXTURE_BINDING_LAYOUT_INIT; }
    { WGPUTextureViewDescriptor x = WGPU_TEXTURE_VIEW_DESCRIPTOR_INIT; }
    { WGPUVertexAttribute x = WGPU_VERTEX_ATTRIBUTE_INIT; }
    { WGPUBindGroupDescriptor x = WGPU_BIND_GROUP_DESCRIPTOR_INIT; }
    { WGPUBindGroupLayoutEntry x = WGPU_BIND_GROUP_LAYOUT_ENTRY_INIT; }
    { WGPUBlendState x = WGPU_BLEND_STATE_INIT; }
    { WGPUCompilationInfo x = WGPU_COMPILATION_INFO_INIT; }
    { WGPUComputePassDescriptor x = WGPU_COMPUTE_PASS_DESCRIPTOR_INIT; }
    { WGPUComputeStage x = WGPU_COMPUTE_STAGE_INIT; }
    { WGPUDepthStencilState x = WGPU_DEPTH_STENCIL_STATE_INIT; }
    { WGPUDeviceDescriptor x = WGPU_DEVICE_DESCRIPTOR_INIT; }
    { WGPUFutureWaitInfo x = WGPU_FUTURE_WAIT_INFO_INIT; }
    { WGPUInstanceDescriptor x = WGPU_INSTANCE_DESCRIPTOR_INIT; }
    { WGPURenderPassColorAttachment x = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT; }
    { WGPUTexelCopyBufferInfo x = WGPU_TEXEL_COPY_BUFFER_INFO_INIT; }
    { WGPUTexelCopyTextureInfo x = WGPU_TEXEL_COPY_TEXTURE_INFO_INIT; }
    { WGPUTextureDescriptor x = WGPU_TEXTURE_DESCRIPTOR_INIT; }
    { WGPUVertexBufferLayout x = WGPU_VERTEX_BUFFER_LAYOUT_INIT; }
    { WGPUBindGroupLayoutDescriptor x = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT; }
    { WGPUColorTargetState x = WGPU_COLOR_TARGET_STATE_INIT; }
    { WGPUComputePipelineDescriptor x = WGPU_COMPUTE_PIPELINE_DESCRIPTOR_INIT; }
    { WGPURenderPassDescriptor x = WGPU_RENDER_PASS_DESCRIPTOR_INIT; }
    { WGPUVertexState x = WGPU_VERTEX_STATE_INIT; }
    { WGPUFragmentState x = WGPU_FRAGMENT_STATE_INIT; }
    { WGPURenderPipelineDescriptor x = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT; }
}
