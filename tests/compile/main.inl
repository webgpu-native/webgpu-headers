#include "../../webgpu.h"

// Compile-test the instantiation of all of the macros, and spot-check types
int main(void) {
    {
        WGPUTextureViewDescriptor a;
        a.mipLevelCount = WGPU_MIP_LEVEL_COUNT_UNDEFINED;
        a.arrayLayerCount = WGPU_ARRAY_LAYER_COUNT_UNDEFINED;
        (void) a;
    }
    {
        WGPUTextureDataLayout a;
        uint32_t x = a.bytesPerRow = WGPU_COPY_STRIDE_UNDEFINED;
        uint32_t y = a.rowsPerImage = WGPU_COPY_STRIDE_UNDEFINED;
        (void) a;
        (void) x;
        (void) y;
    }
    {
        WGPUBindGroupEntry a;
        uint64_t x = a.size = WGPU_WHOLE_SIZE;
        (void) a;
        (void) x;
    }
    {
        uint64_t x = WGPU_WHOLE_MAP_SIZE;
        (void) x;
    }
    {
        WGPULimits a;
        uint32_t x = a.maxTextureDimension2D = WGPU_LIMIT_U32_UNDEFINED;
        uint64_t y = a.maxBufferSize = WGPU_LIMIT_U64_UNDEFINED;
        (void) a;
        (void) x;
        (void) y;
    }
    {
        WGPUComputePassTimestampWrites a;
        a.beginningOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        a.endOfPassWriteIndex = WGPU_QUERY_SET_INDEX_UNDEFINED;
        (void) a;
    }
}
