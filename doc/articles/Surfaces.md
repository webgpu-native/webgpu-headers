# Surfaces {#Surfaces}

Surfaces are the used to continuously present color texture data to users in an OS Window, HTML `<canvas>` or other similar concepts.
The `webgpu.h` concept of @ref WGPUSurface is similar to WebGPU's [`GPUCanvasContext`](https://gpuweb.github.io/gpuweb/#canvas-context) but includes additional options to control behavior or query options that are specific to the environment the application runs in. In other GPU APIs similar concepts are called default framebuffer, swapchain or presentable.

Using a surface is done through a one-time set-up and per-frame operations.
The one time setyp is: environment-specific creation (to wrap a `<canvas>`, `HWND`, `Window` etc), querying capabilities of the surface and configuration of the surface.
Per-frame operations are getting a current @ref WGPUSurfaceTexture to render content to, presenting the surface, and when appropriate reconfiguring the surface (typically when the window is resized).

Sections below give more details about these operations, including the specification of their behavior.

## Surface Creation {#Surface-Creation}

A @ref WGPUSurface is child objects of a @ref WGPUInstance and created using `::wgpuInstanceCreateSurface`.
The description of a @ref WGPUSurface is a @ref WGPUSurfaceDescriptor with a sub-descriptor chained containing the environment-specific objects used to identify the surface.

Surfaces that can be presented to using webgpu.h (but not necessarily by all implementations) are:

 - `ANativeWindow` on Android with @ref WGPUSurfaceFromAndroidNativeWindow
 - `CAMetalLayer` on various Apple OSes like macOS and iOS with @ref WGPUSurfaceFromMetalLayer
 - `<canvas>` HTML elements in WebAssembly with @ref WGPUSurfaceFromCanvasHTMLSelector
 - `HWND` on Windows with @ref WGPUSurfaceFromWindowsHWND
 - `Window` using Xlib with @ref WGPUSurfaceFromXlibWindow
 - `wl_surface` on Wayland systems with @ref WGPUSurfaceFromWaylandSurface
 - `xcb_window_t` using XCB windows with @ref WGPUSurfaceFromXcbWindow

For example creating an @ref WGPUSurface from an `HWND` is done like so:

```c
WGPUSurfaceFromWindowsHWND hwndDesc = {
    .chain = { .sType = WGPUSType_SurfaceFromWindowsHWND, },
    .hinstance = GetModuleHandle(nullptr),
    .hwnd = myHWND,
};
WGPUSurfaceDescriptor desc {
    .nextInChain = &hwndDesc.chain,
    .label = "Main window",
};
WGPUSurface surface = wgpuInstanceCreateSurface(myInstance, &hwnd);
```

In addition @ref WGPUSurfaces have a bunch of internal fields that could be represented like this (in pseudo-C/Rust):

```cpp
struct WGPUSurface {
    // The parent object
    WGPUInstance instance;

    // The current configuration
    Option<WGPUSurfaceConfiguration> config = None;

    // The frame, if any.
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

 - A bit set of supported @ref WGPUTextureUsage that are guaranteed to contains @ref WGPUTextureUsage_RenderAttachment.
 - A list of supported @ref WGPUTextureFormat values, in order of preference.
 - A list of supported @ref WGPUPresentMode values that's guaranteed to contain @ref WGPUPresentMode_Fifo.
 - A list of supported @ref WGPUCompositeAlphaMode values (@ref WGPUCompositeAlphaMode_Auto is always supported but never listed in capabilities as it just lets the implementation decide what to use).

The call to `::wgpuSurfaceGetCapabilities` may allocate memory for pointers filled in the @ref WGPUSurfaceCapabilities structure so `::wgpuSurfaceCapabilitiesFreeMembers` must be called to avoid leaking memory once the capabilities are no longer needed.

This is an example of how to query the capabilities or a @ref WGPUSurface:

```c
// Get the capabilities
WGPUSurfaceCapabilities caps;
wgpuSurfaceGetCapabilities(mySurface, myAdapter, &caps);

// Do things with capabilities
bool canSampleSurface = caps.usages & WGPUTextureUsage_TextureBinding;
WGPUTextureFormat preferredFormat = caps.format[0];

bool supportsMailbox = false;
for (size_t i = 0; i < caps.presentModeCount; i++) {
    if (caps.presentModes[i] == WGPUPresentMode_Mailbox) supportsMailbox = true;
}

// Cleanup
wgpuSurfaceCapabilitiesFreeMembers(&caps);
```

TODO: Write the behavior of `::wgpuSurfaceGetCapabilities`, in particular validation that adapter and surface must be on the same instance, and what happens if rendering to the surface is not possible.

## Surface Configuration {#Surface-Configuration}

TODO

## Presenting to Surface {#Surface-Presenting}

TODO
