# Surfaces {#Surfaces}

Surfaces are used to continuously present color texture data to users in an OS Window, HTML `<canvas>`, or other similar outputs.
The `webgpu.h` concept of @ref WGPUSurface is similar to WebGPU's [`GPUCanvasContext`](https://gpuweb.github.io/gpuweb/#canvas-context) but includes additional options to control behavior or query options that are specific to the environment the application runs in. In other GPU APIs, similar concepts are called "default framebuffer", "swapchain" or "presentable".

To use a surface, there is a one-time setup, then additional per-frame operations.
The one time setup is: environment-specific creation (to wrap a `<canvas>`, `HWND`, `Window`, etc.), querying capabilities of the surface, and configuring the surface.
Per-frame operations are: getting a current @ref WGPUSurfaceTexture to render content to, rendering content, presenting the surface, and when appropriate reconfiguring the surface (typically when the window is resized).

Sections below give more details about these operations, including the specification of their behavior.

## Surface Creation {#Surface-Creation}

A @ref WGPUSurface is child object of a @ref WGPUInstance and created using `::wgpuInstanceCreateSurface`.
The description of a @ref WGPUSurface is a @ref WGPUSurfaceDescriptor with a sub-descriptor chained containing the environment-specific objects used to identify the surface.

Surfaces that can be presented to using `webgpu.h` (but not necessarily by all implementations) are:

 - `ANativeWindow` on Android with @ref WGPUSurfaceSourceAndroidNativeWindow
 - `CAMetalLayer` on various Apple OSes like macOS and iOS with @ref WGPUSurfaceSourceMetalLayer
 - `<canvas>` HTML elements in Emscripten (targeting WebAssembly) with `WGPUSurfaceSourceCanvasHTMLSelector_Emscripten`
 - `HWND` on Windows with @ref WGPUSurfaceSourceWindowsHWND
 - `Window` using Xlib with @ref WGPUSurfaceSourceXlibWindow
 - `wl_surface` on Wayland systems with @ref WGPUSurfaceSourceWaylandSurface
 - `xcb_window_t` using XCB windows with @ref WGPUSurfaceSourceXCBWindow

For example, creating an @ref WGPUSurface from an `HWND` is done like so:

```c
WGPUSurfaceSourceWindowsHWND hwndDesc = {
    .chain = { .sType = WGPUSType_SurfaceSourceWindowsHWND, },
    .hinstance = GetModuleHandle(nullptr),
    .hwnd = myHWND,
};
WGPUSurfaceDescriptor desc {
    .nextInChain = &hwndDesc.chain,
    .label = {.data = "Main window", .length = WGPU_STRLEN},
};
WGPUSurface surface = wgpuInstanceCreateSurface(myInstance, &desc);
```

In addition, a @ref WGPUSurface has a bunch of internal fields that could be represented like this (in C/Rust-like pseudocode):

```cpp
struct WGPUSurface {
    // The parent object
    WGPUInstance instance;

    // The current configuration
    Option<WGPUSurfaceConfiguration> config = None;

    // A reference to the frame's texture, if any.
    Option<WGPUTexture> currentFrame = None;
};
```

The behavior of `::wgpuInstanceCreateSurface``(instance, descriptor)` is:

 - If any of these validation steps fails, return an error @ref WGPUSurface:

    - Validate that all the sub-descriptors in the chain for `descriptor` are known to this implementation.
    - Validate that `descriptor` contains information about exactly one OS surface.
    - As best as possible, validate that the OS surface described in the descriptor is valid (for example a zero `HWND` doesn't exist and isn't valid).

 - Return a new @ref WGPUSurface with its `instance` member initialized with the `instance` parameter and other values defaulted.

## Querying Surface Capabilities {#Surface-Capabilities}

Depending on the OS, GPU used, backing API for WebGPU and other factors, different capabilities are available to render and present the @ref WGPUSurface.
For this reason, negotiation is done between the WebGPU implementation and the application to choose how to use the @ref WGPUSurface.
This first step of the negotiation is querying what capabilities are available using `::wgpuSurfaceGetCapabilities` that fills an @ref WGPUSurfaceCapabilities structure with the following information:

 - A bit set of supported @ref WGPUTextureUsage that are guaranteed to contain @ref WGPUTextureUsage_RenderAttachment.
 - A list of supported @ref WGPUTextureFormat values, in order of preference.
 - A list of supported @ref WGPUPresentMode values (guaranteed to contain @ref WGPUPresentMode_Fifo).
 - A list of supported @ref WGPUCompositeAlphaMode values (@ref WGPUCompositeAlphaMode_Auto is always supported but never listed in capabilities as it just lets the implementation decide what to use).

The call to `::wgpuSurfaceGetCapabilities` may allocate memory for pointers filled in the @ref WGPUSurfaceCapabilities structure so `::wgpuSurfaceCapabilitiesFreeMembers` must be called to avoid leaking memory once the capabilities are no longer needed.

This is an example of how to query the capabilities or a @ref WGPUSurface:

```c
// Get the capabilities
WGPUSurfaceCapabilities caps;
if (!wgpuSurfaceGetCapabilities(mySurface, myAdapter, &caps)) {
    // Either a validation error happened or the adapter doesn't support the surface.
    // TODO: This should be a WGPUStatus.
    return;
}

// Do things with capabilities
bool canSampleSurface = caps.usages & WGPUTextureUsage_TextureBinding;
WGPUTextureFormat preferredFormat = caps.format[0];

bool supportsMailbox = false;
for (size_t i = 0; i < caps.presentModeCount; i++) {
    if (caps.presentModes[i] == WGPUPresentMode_Mailbox) supportsMailbox = true;
}

// Cleanup
wgpuSurfaceCapabilitiesFreeMembers(caps);
```

The behavior of `::wgpuSurfaceGetCapabilities``(surface, adapter, caps)` is:

 - If any of these validation steps fails, return false. (TODO return an error WGPUStatus):

   - Validate that all the sub-descriptors in the chain for `caps` are known to this implementation.
   - Validate that `surface` and `adapter` are created from the same @ref WGPUInstance.

 - Fill `caps` with `adapter`'s capabilities to render to `surface`.
 - Return true. (TODO return WGPUStatus_Success)

## Surface Configuration {#Surface-Configuration}

Before it can use it for rendering, the application must configure the surface.
The configuration is the second step of the negotiation, done after analyzing the results of `::wgpuSurfaceGetCapabilities`.
It contains the following kinds of parameters:

 - The @ref WGPUDevice that will be used to render to the surface.
 - Parameters for the textures returned by `::wgpuSurfaceGetCurrentTexture`.
 - @ref WGPUPresentMode and @ref WGPUCompositeAlphaMode parameters for how and when the surface will be presented to the user.

This is an example of how to configure a @ref WGPUSurface:

```c
WGPUSurfaceConfiguration config = {
    nextInChain = nullptr,
    device = myDevice,
    format = preferredFormat,
    width = 640, // Depending on the window size.
    height = 480,
    usage = WGPUTextureUsage_RenderAttachment,
    presentMode = supportsMailbox ? WGPUPresentMode_Mailbox : WGPUPresentMode_Fifo,
    alphaMode = WGPUCompositeAlphaMode_Auto,
};
wgpuSurfaceConfigure(mySurface, &config);
```

The parameters for the texture are used to create the texture each frame (see @ref Surface-Presenting) with the equivalent @ref WGPUTextureDescriptor computed like this:

```c
WGPUTextureDescriptor GetSurfaceEquivalentTextureDescriptor(const WGPUSurfaceConfiguration* config) {
    return {
        // Parameters controlled by the surface configuration.
        .size = {config->width, config->height, 1},
        .usage = config->usage,
        .format = config->format,
        .viewFormatCount = config->viewFormatCount,
        .viewFormats = config->viewFormats,

        // Parameters that cannot be changed.
        .nextInChain = nullptr,
        .label = {.data = "", .length = WGPU_STRLEN},
        .dimension = WGPUTextureDimension_2D,
        .sampleCount = 1,
        .mipLevelCount = 1,
    };
}
```

When a surface is successfully configured, the new configuration overrides any previous configuration and destroys the previous current texture (if any) so it can no longer be used.

The behavior of `::wgpuSurfaceConfigure``(surface, config)` is:

 - If any of these validation steps fails, TODO: what should happen on failure?

   - Validate that `surface` is not an error.
   - Let `adapter` be the adapter used to create `device`.
   - Let `caps` be the @ref WGPUSurfaceCapabilities filled with `::wgpuSurfaceGetCapabilities``(surface, adapter, &caps)`.
   - Validate that all the sub-descriptors in the chain for `caps` are known to this implementation.
   - Validate that `device` is alive.
   - Validate that `config->presentMode` is in `caps->presentModes`.
   - Validate that `config->alphaMode` is either `WGPUCompositeAlphaMode_Auto` or in `caps->alphaModes`.
   - Validate that `config->format` if in `caps->formats`.
   - Validate that `config->usage` is a subset of `caps->usages`.
   - Let `textureDesc` be `GetSurfaceEquivalentTextureDescriptor(config)`.
   - Validate that `wgpuDeviceCreateTexture(device, &textureDesc)` would succeed.

 - Set `surface.config` to a deep copy of `config`.
 - If `surface.currentFrame` is not `None`:

   - Do as if `::wgpuTextureDestroy``(surface.currentFrame)` was called.
   - Set `surface.currentFrame` to `None`.

It can also be useful to remove the configuration of a @ref WGPUSurface without replacing it with a valid one.
Without removing the configuration, the @ref WGPUSurface will keep referencing the @ref WGPUDevice that cannot be totally reclaimed.

The behavior of `::wgpuSurfaceUnconfigure``()` is:

 - Set `surface.config` to `None`.
 - If `surface.currentFrame` is not `None`:

   - Do as if `::wgpuTextureDestroy``(surface.currentFrame)` was called.
   - Set `surface.currentFrame` to `None`.

## Presenting to Surface {#Surface-Presenting}

Each frame, the application retrieves the @ref WGPUTexture for the frame with `::wgpuSurfaceGetCurrentTexture`, renders to it and then presents it on the screen with `::wgpuSurfacePresent`.

Issues can happen when trying to retrieve the frame's @ref WGPUTexture, so the application must check @ref WGPUSurfaceTexture `.status` to see if the surface or the device was lost, or some other windowing system issue caused a timeout.
The environment can also change the surface without breaking it, but making the current configuration suboptimal. 
In this case, @ref WGPUSurfaceTexture `.status` will be @ref WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal and the application should (but isn't required to) handle it.
Surfaces often become suboptimal when the window is resized (so presenting requires resizing a texture, which is both performance overhead, and a visual quality degradation).

This is an example of how to render to a @ref WGPUSurface each frame:

```c
// Get the texture and handle exceptional cases.
WGPUSurfaceTexture surfaceTexture;
wgpuSurfaceGetCurrentTexture(mySurface, &surfaceTexture);

if (surfaceTexture.texture == NULL) {
    // Recover if possible.
    return;
}
// Since the texture is not null, the status is some kind of success.
// We can optionally handle the "SuccessSuboptimal" case.
if (surfaceTexture.status == WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
    HandleResize();
    return;
}

// The application renders to the texture.
RenderTo(surfaceTexture.texture);

// Present the texture, it is no longer accessible after that point.
wgpuSurfacePresent(mySurface);

// Release the reference we got to the now presented texture. (it can safely be done before present as well)
wgpuTextureRelease(surfaceTexture.texture);

```

The behavior of `::wgpuSurfaceGetCurrentTexture``(surface, surfaceTexture)` is:

 - Set `surfaceTexture->texture` to `NULL`.

 - If any of these validation steps fails, set `surfaceTexture->status` to `WGPUSurfaceGetCurrentTextureStatus_Error` and return (TODO send error to device?).

   - Validate that `surface` is not an error.
   - Validate that `surface.config` is not `None`.
   - Validate that `surface.currentFrame` is `None`.

 - If `surface.config.device` is not alive, set `surfaceTexture->status` to `WGPUSurfaceGetCurrentTextureStatus_Lost` and return.
 - If the implementation detects any other problem preventing use of the surface, set `surfaceTexture->status` to an appropriate status (something other than `SuccessOptimal`, `SuccessSuboptimal`, or `Error`) and return.
 - Let `textureDesc` be `GetSurfaceEquivalentTextureDescriptor(surface.config)`.
 - Create a new @ref WGPUTexture `t`, as if calling `wgpuDeviceCreateTexture(surface.config.device, &textureDesc)`, but wrapping the appropriate backing resource.
 - Set `surface.currentFrame` to `t`.
 - If the implementation detects a reason why the current configuration is suboptimal, set `surfaceTexture->status` to `WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal`.
   Otherwise, set it to `WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal`.
 - Add a new reference to `t`.
 - Set `surfaceTexture->texture` to a new reference to `t`.

The behavior of `::wgpuSurfacePresent``(surface)` is:

 - If any of these validation steps fails, TODO send error to device?

   - Validate that `surface` is not an error.
   - Validate that `surface.currentFrame` is not `None`.

 - Do as if `::wgpuTextureDestroy``(surface.currentFrame)` was called.
 - Present `surface.currentFrame` to the `surface`.
 - Set `surface.currentFrame` to `None`.
