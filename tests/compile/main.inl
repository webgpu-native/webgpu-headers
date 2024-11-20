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
        WGPUComputePassTimestampWrites a;
        a.beginningOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        a.endOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
    }
}
