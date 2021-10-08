#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace DirectXNet
{
    namespace DXGI
    {
        value struct D3DColorValue;
        value struct DXGIAdapterDesc;
        value struct DXGIAdapterDesc1;
        value struct DXGIFrameStatistics;
        value struct DXGIGammaControl;
        value struct DXGIGammaControlCapabilities;
        value struct DXGIMappedRect;
        value struct DXGIModeDesc;
        value struct DXGIOutputDesc;
        value struct DXGIRational;
        value struct DXGIRGB;
        value struct DXGISampleDesc;
        value struct DXGISharedResource;
        value struct DXGISurfaceDesc;
        value struct DXGISwapChainDesc;

        
        /// <summary>
        /// Identifies the type of DXGI adapter.
        /// </summary>
        [Flags]
        public enum class DXGIAdapterFlag : UINT
        {
            /// <summary>
            /// Specifies no flags.
            /// </summary>
            None = ::DXGI_ADAPTER_FLAG_NONE,

            /// <summary>
            /// Value always set to 0. This flag is reserved.
            /// </summary>
            Remote = ::DXGI_ADAPTER_FLAG_REMOTE,

            /// <summary>
            /// Specifies a software adapter.
            /// </summary>
            Software = ::DXGI_ADAPTER_FLAG_SOFTWARE,
        };
    
        /// <summary>
        /// Options for enumerating display modes.
        /// </summary>
        [Flags]
        public enum class DXGIEnumModes : UINT
        {
            /// <summary>
            /// Specifies no flags.
            /// </summary>
            None = 0,

            /// <summary>
            /// Include interlaced modes.
            /// </summary>
            Interlaced = DXGI_ENUM_MODES_INTERLACED,

            /// <summary>
            /// Include stretched-scaling modes.
            /// </summary>
            Scaling = DXGI_ENUM_MODES_SCALING,

            /// <summary>
            /// Include stereo modes.
            /// </summary>
            Stereo = DXGI_ENUM_MODES_STEREO,

            /// <summary>
            /// Include stereo modes that are hidden because the user has disabled
            /// stereo. Control panel applications can use this option to show stereo
            /// capabilities that have been disabled as part of a user interface that
            /// enables and disables stereo.
            /// </summary>
            DisabledStereo = DXGI_ENUM_MODES_DISABLED_STEREO
        };

        /// <summary>
        /// Resource data formats, including fully-typed and typeless formats.
        /// </summary>
        public enum class DXGIFormat : UINT
        {
            FORMAT_UNKNOWN                                =::DXGI_FORMAT_UNKNOWN,
            FORMAT_R32G32B32A32_TYPELESS                  =::DXGI_FORMAT_R32G32B32A32_TYPELESS,
            FORMAT_R32G32B32A32_FLOAT                     =::DXGI_FORMAT_R32G32B32A32_FLOAT,
            FORMAT_R32G32B32A32_UINT                      =::DXGI_FORMAT_R32G32B32A32_UINT,
            FORMAT_R32G32B32A32_SINT                      =::DXGI_FORMAT_R32G32B32A32_SINT,
            FORMAT_R32G32B32_TYPELESS                     =::DXGI_FORMAT_R32G32B32_TYPELESS,
            FORMAT_R32G32B32_FLOAT                        =::DXGI_FORMAT_R32G32B32_FLOAT,
            FORMAT_R32G32B32_UINT                         =::DXGI_FORMAT_R32G32B32_UINT,
            FORMAT_R32G32B32_SINT                         =::DXGI_FORMAT_R32G32B32_SINT,
            FORMAT_R16G16B16A16_TYPELESS                  =::DXGI_FORMAT_R16G16B16A16_TYPELESS,
            FORMAT_R16G16B16A16_FLOAT                     =::DXGI_FORMAT_R16G16B16A16_FLOAT,
            FORMAT_R16G16B16A16_UNORM                     =::DXGI_FORMAT_R16G16B16A16_UNORM,
            FORMAT_R16G16B16A16_UINT                      =::DXGI_FORMAT_R16G16B16A16_UINT,
            FORMAT_R16G16B16A16_SNORM                     =::DXGI_FORMAT_R16G16B16A16_SNORM,
            FORMAT_R16G16B16A16_SINT                      =::DXGI_FORMAT_R16G16B16A16_SINT,
            FORMAT_R32G32_TYPELESS                        =::DXGI_FORMAT_R32G32_TYPELESS,
            FORMAT_R32G32_FLOAT                           =::DXGI_FORMAT_R32G32_FLOAT,
            FORMAT_R32G32_UINT                            =::DXGI_FORMAT_R32G32_UINT,
            FORMAT_R32G32_SINT                            =::DXGI_FORMAT_R32G32_SINT,
            FORMAT_R32G8X24_TYPELESS                      =::DXGI_FORMAT_R32G8X24_TYPELESS,
            FORMAT_D32_FLOAT_S8X24_UINT                   =::DXGI_FORMAT_D32_FLOAT_S8X24_UINT,
            FORMAT_R32_FLOAT_X8X24_TYPELESS               =::DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS,
            FORMAT_X32_TYPELESS_G8X24_UINT                =::DXGI_FORMAT_X32_TYPELESS_G8X24_UINT,
            FORMAT_R10G10B10A2_TYPELESS                   =::DXGI_FORMAT_R10G10B10A2_TYPELESS,
            FORMAT_R10G10B10A2_UNORM                      =::DXGI_FORMAT_R10G10B10A2_UNORM,
            FORMAT_R10G10B10A2_UINT                       =::DXGI_FORMAT_R10G10B10A2_UINT,
            FORMAT_R11G11B10_FLOAT                        =::DXGI_FORMAT_R11G11B10_FLOAT,
            FORMAT_R8G8B8A8_TYPELESS                      =::DXGI_FORMAT_R8G8B8A8_TYPELESS,
            FORMAT_R8G8B8A8_UNORM                         =::DXGI_FORMAT_R8G8B8A8_UNORM,
            FORMAT_R8G8B8A8_UNORM_SRGB                    =::DXGI_FORMAT_R8G8B8A8_UNORM_SRGB,
            FORMAT_R8G8B8A8_UINT                          =::DXGI_FORMAT_R8G8B8A8_UINT,
            FORMAT_R8G8B8A8_SNORM                         =::DXGI_FORMAT_R8G8B8A8_SNORM,
            FORMAT_R8G8B8A8_SINT                          =::DXGI_FORMAT_R8G8B8A8_SINT,
            FORMAT_R16G16_TYPELESS                        =::DXGI_FORMAT_R16G16_TYPELESS,
            FORMAT_R16G16_FLOAT                           =::DXGI_FORMAT_R16G16_FLOAT,
            FORMAT_R16G16_UNORM                           =::DXGI_FORMAT_R16G16_UNORM,
            FORMAT_R16G16_UINT                            =::DXGI_FORMAT_R16G16_UINT,
            FORMAT_R16G16_SNORM                           =::DXGI_FORMAT_R16G16_SNORM,
            FORMAT_R16G16_SINT                            =::DXGI_FORMAT_R16G16_SINT,
            FORMAT_R32_TYPELESS                           =::DXGI_FORMAT_R32_TYPELESS,
            FORMAT_D32_FLOAT                              =::DXGI_FORMAT_D32_FLOAT,
            FORMAT_R32_FLOAT                              =::DXGI_FORMAT_R32_FLOAT,
            FORMAT_R32_UINT                               =::DXGI_FORMAT_R32_UINT,
            FORMAT_R32_SINT                               =::DXGI_FORMAT_R32_SINT,
            FORMAT_R24G8_TYPELESS                         =::DXGI_FORMAT_R24G8_TYPELESS,
            FORMAT_D24_UNORM_S8_UINT                      =::DXGI_FORMAT_D24_UNORM_S8_UINT,
            FORMAT_R24_UNORM_X8_TYPELESS                  =::DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
            FORMAT_X24_TYPELESS_G8_UINT                   =::DXGI_FORMAT_X24_TYPELESS_G8_UINT,
            FORMAT_R8G8_TYPELESS                          =::DXGI_FORMAT_R8G8_TYPELESS,
            FORMAT_R8G8_UNORM                             =::DXGI_FORMAT_R8G8_UNORM,
            FORMAT_R8G8_UINT                              =::DXGI_FORMAT_R8G8_UINT,
            FORMAT_R8G8_SNORM                             =::DXGI_FORMAT_R8G8_SNORM,
            FORMAT_R8G8_SINT                              =::DXGI_FORMAT_R8G8_SINT,
            FORMAT_R16_TYPELESS                           =::DXGI_FORMAT_R16_TYPELESS,
            FORMAT_R16_FLOAT                              =::DXGI_FORMAT_R16_FLOAT,
            FORMAT_D16_UNORM                              =::DXGI_FORMAT_D16_UNORM,
            FORMAT_R16_UNORM                              =::DXGI_FORMAT_R16_UNORM,
            FORMAT_R16_UINT                               =::DXGI_FORMAT_R16_UINT,
            FORMAT_R16_SNORM                              =::DXGI_FORMAT_R16_SNORM,
            FORMAT_R16_SINT                               =::DXGI_FORMAT_R16_SINT,
            FORMAT_R8_TYPELESS                            =::DXGI_FORMAT_R8_TYPELESS,
            FORMAT_R8_UNORM                               =::DXGI_FORMAT_R8_UNORM,
            FORMAT_R8_UINT                                =::DXGI_FORMAT_R8_UINT,
            FORMAT_R8_SNORM                               =::DXGI_FORMAT_R8_SNORM,
            FORMAT_R8_SINT                                =::DXGI_FORMAT_R8_SINT,
            FORMAT_A8_UNORM                               =::DXGI_FORMAT_A8_UNORM,
            FORMAT_R1_UNORM                               =::DXGI_FORMAT_R1_UNORM,
            FORMAT_R9G9B9E5_SHAREDEXP                     =::DXGI_FORMAT_R9G9B9E5_SHAREDEXP,
            FORMAT_R8G8_B8G8_UNORM                        =::DXGI_FORMAT_R8G8_B8G8_UNORM,
            FORMAT_G8R8_G8B8_UNORM                        =::DXGI_FORMAT_G8R8_G8B8_UNORM,
            FORMAT_BC1_TYPELESS                           =::DXGI_FORMAT_BC1_TYPELESS,
            FORMAT_BC1_UNORM                              =::DXGI_FORMAT_BC1_UNORM,
            FORMAT_BC1_UNORM_SRGB                         =::DXGI_FORMAT_BC1_UNORM_SRGB,
            FORMAT_BC2_TYPELESS                           =::DXGI_FORMAT_BC2_TYPELESS,
            FORMAT_BC2_UNORM                              =::DXGI_FORMAT_BC2_UNORM,
            FORMAT_BC2_UNORM_SRGB                         =::DXGI_FORMAT_BC2_UNORM_SRGB,
            FORMAT_BC3_TYPELESS                           =::DXGI_FORMAT_BC3_TYPELESS,
            FORMAT_BC3_UNORM                              =::DXGI_FORMAT_BC3_UNORM,
            FORMAT_BC3_UNORM_SRGB                         =::DXGI_FORMAT_BC3_UNORM_SRGB,
            FORMAT_BC4_TYPELESS                           =::DXGI_FORMAT_BC4_TYPELESS,
            FORMAT_BC4_UNORM                              =::DXGI_FORMAT_BC4_UNORM,
            FORMAT_BC4_SNORM                              =::DXGI_FORMAT_BC4_SNORM,
            FORMAT_BC5_TYPELESS                           =::DXGI_FORMAT_BC5_TYPELESS,
            FORMAT_BC5_UNORM                              =::DXGI_FORMAT_BC5_UNORM,
            FORMAT_BC5_SNORM                              =::DXGI_FORMAT_BC5_SNORM,
            FORMAT_B5G6R5_UNORM                           =::DXGI_FORMAT_B5G6R5_UNORM,
            FORMAT_B5G5R5A1_UNORM                         =::DXGI_FORMAT_B5G5R5A1_UNORM,
            FORMAT_B8G8R8A8_UNORM                         =::DXGI_FORMAT_B8G8R8A8_UNORM,
            FORMAT_B8G8R8X8_UNORM                         =::DXGI_FORMAT_B8G8R8X8_UNORM,
            FORMAT_R10G10B10_XR_BIAS_A2_UNORM             =::DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM,
            FORMAT_B8G8R8A8_TYPELESS                      =::DXGI_FORMAT_B8G8R8A8_TYPELESS,
            FORMAT_B8G8R8A8_UNORM_SRGB                    =::DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
            FORMAT_B8G8R8X8_TYPELESS                      =::DXGI_FORMAT_B8G8R8X8_TYPELESS,
            FORMAT_B8G8R8X8_UNORM_SRGB                    =::DXGI_FORMAT_B8G8R8X8_UNORM_SRGB,
            FORMAT_BC6H_TYPELESS                          =::DXGI_FORMAT_BC6H_TYPELESS,
            FORMAT_BC6H_UF16                              =::DXGI_FORMAT_BC6H_UF16,
            FORMAT_BC6H_SF16                              =::DXGI_FORMAT_BC6H_SF16,
            FORMAT_BC7_TYPELESS                           =::DXGI_FORMAT_BC7_TYPELESS,
            FORMAT_BC7_UNORM                              =::DXGI_FORMAT_BC7_UNORM,
            FORMAT_BC7_UNORM_SRGB                         =::DXGI_FORMAT_BC7_UNORM_SRGB,
            FORMAT_AYUV                                   =::DXGI_FORMAT_AYUV,
            FORMAT_Y410                                   =::DXGI_FORMAT_Y410,
            FORMAT_Y416                                   =::DXGI_FORMAT_Y416,
            FORMAT_NV12                                   =::DXGI_FORMAT_NV12,
            FORMAT_P010                                   =::DXGI_FORMAT_P010,
            FORMAT_P016                                   =::DXGI_FORMAT_P016,
            FORMAT_420_OPAQUE                             =::DXGI_FORMAT_420_OPAQUE,
            FORMAT_YUY2                                   =::DXGI_FORMAT_YUY2,
            FORMAT_Y210                                   =::DXGI_FORMAT_Y210,
            FORMAT_Y216                                   =::DXGI_FORMAT_Y216,
            FORMAT_NV11                                   =::DXGI_FORMAT_NV11,
            FORMAT_AI44                                   =::DXGI_FORMAT_AI44,
            FORMAT_IA44                                   =::DXGI_FORMAT_IA44,
            FORMAT_P8                                     =::DXGI_FORMAT_P8,
            FORMAT_A8P8                                   =::DXGI_FORMAT_A8P8,
            FORMAT_B4G4R4A4_UNORM                         =::DXGI_FORMAT_B4G4R4A4_UNORM,                
            FORMAT_P208                                   =::DXGI_FORMAT_P208,
            FORMAT_V208                                   =::DXGI_FORMAT_V208,
            FORMAT_V408                                   =::DXGI_FORMAT_V408,                             
            FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE        =::DXGI_FORMAT_SAMPLER_FEEDBACK_MIN_MIP_OPAQUE,
            FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE=::DXGI_FORMAT_SAMPLER_FEEDBACK_MIP_REGION_USED_OPAQUE,
        };
  
        /// <summary>
        /// CPU read-write flags.
        /// </summary>
        [Flags]
        public enum class DXGIMapFlag : UINT
        {
            /// <summary>
            /// Specifies no flags.
            /// </summary>
            None = 0,

            /// <summary>
            /// Allow CPU read access.
            /// </summary>
            Read = DXGI_MAP_READ,

            /// <summary>
            /// Allow CPU write access.
            /// </summary>
            Write = DXGI_MAP_WRITE,

            /// <summary>
            /// Discard the previous contents of a resource when it is mapped.
            /// </summary>
            Discard = DXGI_MAP_DISCARD
        };

        /// <summary>
        /// Flags that indicate how the back buffers should be rotated to fit
        /// the physical rotation of a monitor.
        /// </summary>
        public enum class DXGIModeRotation : UINT
        {
            /// <summary>
            /// Unspecified rotation.
            /// </summary>
            Unspecified = ::DXGI_MODE_ROTATION_UNSPECIFIED,

            /// <summary>
            /// Specifies no rotation.
            /// </summary>
            Identity = ::DXGI_MODE_ROTATION_IDENTITY,

            /// <summary>
            /// Specifies 90 degrees of rotation.
            /// </summary>
            Rotate90 = ::DXGI_MODE_ROTATION_ROTATE90,

            /// <summary>
            /// Specifies 180 degrees of rotation.
            /// </summary>
            Rotate180 = ::DXGI_MODE_ROTATION_ROTATE180,

            /// <summary>
            /// Specifies 270 degrees of rotation.
            /// </summary>
            Rotate270 = ::DXGI_MODE_ROTATION_ROTATE270
        };

        /// <summary>
        /// Flags indicating how an image is stretched to fit a given monitor's
        /// resolution.
        /// </summary>
        public enum class DXGIModeScaling : UINT
        {
            /// <summary>
            /// Unspecified scaling.
            /// </summary>
            Unspecified = ::DXGI_MODE_SCALING_UNSPECIFIED,

            /// <summary>
            /// Specifies no scaling. The image is centered on the display. This flag is
            /// typically used for a fixed-dot-pitch display (such as an LED display).
            /// </summary>
            Centered = ::DXGI_MODE_SCALING_CENTERED,

            /// <summary>
            /// Specifies stretched scaling.
            /// </summary>
            Stretched = ::DXGI_MODE_SCALING_STRETCHED
        };

        /// <summary>
        /// Flags indicating the method the raster uses to create an image on a surface.
        /// </summary>
        public enum class DXGIModeScanlineOrder : UINT
        {
            /// <summary>
            /// Scanline order is unspecified.
            /// </summary>
            Unspecified = ::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,

            /// <summary>
            /// The image is created from the first scanline to the last without skipping
            /// any.
            /// </summary>
            Progressive = ::DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE,

            /// <summary>
            /// The image is created beginning with the upper field.
            /// </summary>
            UpperFieldFirst = ::DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST,

            /// <summary>
            /// The image is created beginning with the lower field.
            /// </summary>
            LowerFieldFirst = ::DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST
        };
        
        /// <summary>
        /// Flags specify options for presenting frames to the output.
        /// </summary>
        [Flags]
        public enum class DXGIPresent : UINT
        {
            /// <summary>
            /// Present a frame from each buffer (starting with the current buffer)
            /// to the output.
            /// </summary>
            None = 0,

            /// <summary>
            /// Do not present the frame to the output. The status of the swap chain
            /// will be tested and appropriate errors returned. DXGI_PRESENT_TEST is
            /// intended for use only when switching from the idle state; do not use
            /// it to determine when to switch to the idle state because doing so
            /// can leave the swap chain unable to exit full-screen mode.
            /// </summary>
            Test = DXGI_PRESENT_TEST,

            /// <summary>
            /// Present a frame from the current buffer to the output. Use this flag
            /// so that the presentation can use vertical-blank synchronization
            /// instead of sequencing buffers in the chain in the usual manner.
            /// </summary>
            DoNotSequence = DXGI_PRESENT_DO_NOT_SEQUENCE,

            /// <summary>
            /// Specifies that the runtime will discard outstanding queued presents.
            /// </summary>
            Restart = DXGI_PRESENT_RESTART,

            /// <summary>
            /// Specifies that the runtime will fail the presentation (that is, fail
            /// a call to DXGISwapChain1::Present1) with the
            /// DXGI_ERROR_WAS_STILL_DRAWING error code if the calling thread is
            /// blocked; the runtime returns DXGI_ERROR_WAS_STILL_DRAWING instead
            /// of sleeping until the dependency is resolved.
            /// </summary>
            DoNotWait = DXGI_PRESENT_DO_NOT_WAIT,

            /// <summary>
            /// Indicates that if the stereo present must be reduced to mono,
            /// right-eye viewing is used rather than left-eye viewing.
            /// </summary>
            StereoPreferRight = DXGI_PRESENT_STEREO_PREFER_RIGHT,

            /// <summary>
            /// Indicates that the presentation should use the left buffer as a
            /// mono buffer. An application calls the
            /// DXGISwapChain1::IsTemporaryMonoSupported method to determine whether
            /// a swap chain supports "temporary mono".
            /// </summary>
            StereoTemporaryMono = DXGI_PRESENT_STEREO_TEMPORARY_MONO,

            /// <summary>
            /// Indicates that presentation content will be shown only on the
            /// particular output. The content will not be visible on other outputs.
            /// For example, if the user tries to relocate video content on
            /// another output, the video content will not be visible.
            /// </summary>
            RestrictToOutput = DXGI_PRESENT_RESTRICT_TO_OUTPUT,

            /// <summary>
            /// This flag must be set by media apps that are currently using a
            /// custom present duration (custom refresh rate). See DXGISwapChainMedia.
            /// </summary>
            UseDuration = DXGI_PRESENT_USE_DURATION,

            /// <summary>
            /// Allowing tearing is a requirement of variable refresh rate displays.
            /// The conditions for using AllowTearing during Present are as follows :
            /// <para>The swap chain must be created with the
            /// DXGISwapChainFlag::AllowTearing flag.</para>
            /// <para>The sync interval passed in to Present (or Present1) must be 0.
            /// </para>
            /// <para>The DXGI_PRESENT_ALLOW_TEARING flag cannot be used in an
            /// application that is currently in full screen exclusive mode
            /// (set by calling SetFullscreenState(true)). It can only be used in
            /// windowed mode. To use this flag in full screen Win32 apps, the
            /// application should present to a fullscreen borderless window and disable
            /// automatic ALT+ENTER fullscreen switching using
            /// DXGIFactory::MakeWindowAssociation. UWP apps that enter fullscreen
            /// mode by calling
            /// Windows::UI::ViewManagement::ApplicationView::TryEnterFullscreen()
            /// are fullscreen borderless windows and may use the flag.</para>
            /// </summary>
            AllowTearing = DXGI_PRESENT_ALLOW_TEARING
        };

        /// <summary>
        /// Flags indicating the memory location of a resource.
        /// </summary>
        public enum class DXGIResidency : UINT
        {
            /// <summary>
            /// The resource is located in video memory.
            /// </summary>
            FullyResident = ::DXGI_RESIDENCY_FULLY_RESIDENT,

            /// <summary>
            /// At least some of the resource is located in CPU memory.
            /// </summary>
            ResidentInSharedMemory = ::DXGI_RESIDENCY_RESIDENT_IN_SHARED_MEMORY,

            /// <summary>
            /// At least some of the resource has been paged out to the hard drive.
            /// </summary>
            EvictedToDisk = ::DXGI_RESIDENCY_EVICTED_TO_DISK
        };
     
        /// <summary>
        /// Options for swap-chain behavior.
        /// </summary>
        [Flags]
        public enum class DXGISwapChainFlag : UINT
        {
            /// <summary>
            /// Specifies no flags.
            /// </summary>
            None = 0,

            /// <summary>
            /// Set this flag to turn off automatic image rotation; that is, do
            /// not perform a rotation when transferring the contents of the front
            /// buffer to the monitor.
            /// Use this flag to avoid a bandwidth penalty when an application expects
            /// to handle rotation.This option is valid only during full - screen mode.
            /// </summary>
            NonPrerotated = ::DXGI_SWAP_CHAIN_FLAG_NONPREROTATED,

            /// <summary>
            /// Set this flag to enable an application to switch modes by calling
            /// IDXGISwapChain::ResizeTarget.
            /// When switching from windowed to full - screen mode, the display mode
            /// (or monitor resolution) will be changed to match the dimensions of
            /// the application window.
            /// </summary>
            AllowModeSwitch = ::DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH,

            /// <summary>
            /// Set this flag to enable an application to render using GDI on a
            /// swap chain or a surface.
            /// This will allow the application to call DXGISurface1::GetDC on the
            /// 0th back buffer or a surface.
            /// </summary>
            GDICompatible = ::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE,

            /// <summary>
            /// Set this flag to indicate that the swap chain might contain protected
            /// content; therefore, the operating system supports the creation of the
            /// swap chain only when driver and hardware protection is used. If the
            /// driver and hardware do not support content protection, the call to
            /// create a resource for the swap chain fails.
            /// </summary>
            RestrictedContent = ::DXGI_SWAP_CHAIN_FLAG_RESTRICTED_CONTENT,

            /// <summary>
            /// Set this flag to indicate that shared resources that are created within
            /// the swap chain must be protected by using the driver¡¯s mechanism for
            /// restricting access to shared surfaces.
            /// </summary>
            RestrictSharedResourceDriver = ::DXGI_SWAP_CHAIN_FLAG_RESTRICT_SHARED_RESOURCE_DRIVER,

            /// <summary>
            /// Set this flag to restrict presented content to the local displays.
            /// This flag supports the window content protection features of Windows.
            /// Applications can use this flag to protect their own onscreen window
            /// content from being captured or copied through a specific set of public
            /// operating system features and APIs.
            /// If you use this flag with windowed (HWND or IWindow) swap chains
            /// where another process created the HWND, the owner of the HWND must
            /// use the SetWindowDisplayAffinity function appropriately in order to
            /// allow calls to DXGISwapChain::Present or DXGISwapChain1::Present1
            /// to succeed.
            /// </summary>
            DisplayOnly = ::DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY,

            /// <summary>
            /// Set this flag to create a waitable object you can use to ensure
            /// rendering does not begin while a frame is still being presented.
            /// When this flag is used, the swapchain's latency must be set with
            /// the DXGISwapChain2::SetMaximumFrameLatency API instead of
            /// DXGIDevice1::SetMaximumFrameLatency.
            /// </summary>
            FrameLatencyWaitableObject = ::DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT,

            /// <summary>
            /// Set this flag to create a swap chain in the foreground layer for
            /// multi-plane rendering. This flag can only be used with CoreWindow
            /// swap chains, which are created with CreateSwapChainForCoreWindow.
            /// Apps should not create foreground swap chains if
            /// DXGIOutput2::SupportsOverlays indicates that hardware support
            /// for overlays is not available.
            /// </summary>
            ForegroundLayer = ::DXGI_SWAP_CHAIN_FLAG_FOREGROUND_LAYER,

            /// <summary>
            /// Set this flag to create a swap chain for full-screen video.
            /// </summary>
            FullscreenVideo = ::DXGI_SWAP_CHAIN_FLAG_FULLSCREEN_VIDEO,

            /// <summary>
            /// Set this flag to create a swap chain for YUV video.
            /// </summary>
            YUVVideo = ::DXGI_SWAP_CHAIN_FLAG_YUV_VIDEO,

            /// <summary>
            /// Indicates that the swap chain should be created such that all underlying
            /// resources can be protected by the hardware. Resource creation will fail
            /// if hardware content protection is not supported.
            /// This flag has the following restrictions:
            /// <para>his flag can only be used with swap effect 
            /// DXGISwapEffect::FlipSequential.</para>
            /// </summary>
            HardwareProtected = ::DXGI_SWAP_CHAIN_FLAG_HW_PROTECTED,

            /// <summary>
            /// Tearing support is a requirement to enable displays that support
            /// variable refresh rates to function properly when the application
            /// presents a swap chain tied to a full screen borderless window. Win32
            /// apps can already achieve tearing in fullscreen exclusive mode by
            /// calling SetFullscreenState(true), but the recommended approach for
            /// Win32 developers is to use this tearing flag instead. This flag
            /// requires the use of a DXGISwapEffect::Flip* swap effect.
            /// </summary>
            AllowTearing = ::DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING,

            RestrictedToAllHolographicDisplays = ::DXGI_SWAP_CHAIN_FLAG_RESTRICTED_TO_ALL_HOLOGRAPHIC_DISPLAYS
        };

        /// <summary>
        /// Options for handling pixels in a display surface.
        /// </summary>
        public enum class DXGISwapEffect : UINT
        {
            /// <summary>
            /// Use this flag to specify the bit-block transfer (bitblt) model and to
            /// specify that DXGI discard the contents of the back buffer.
            /// This flag is valid for a swap chain with more than one back buffer,
            /// although, applications only have read and write access to buffer 0.
            /// Use this flag to enable the display driver to select the most efficient
            /// presentation technique for the swap chain.
            /// </summary>
            Discard = ::DXGI_SWAP_EFFECT_DISCARD,

            /// <summary>
            /// Use this flag to specify the bitblt model and to specify that DXGI
            /// persist the contents of the back buffer.
            /// Use this option to present the contents of the swap chain in order,
            /// from the first buffer (buffer 0) to the last buffer.
            /// This flag cannot be used with multisampling.
            /// </summary>
            Sequential = ::DXGI_SWAP_EFFECT_SEQUENTIAL,

            /// <summary>
            /// Use this flag to specify the flip presentation model and to specify
            /// that DXGI persist the contents of the back buffer.
            /// This flag cannot be used with multisampling.
            /// </summary>
            FlipSequential = ::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,

            /// <summary>
            /// Use this flag to specify the flip presentation model and to specify
            /// that DXGI discard the contents of the back buffer.
            /// This flag cannot be used with multisampling and partial presentation.
            /// </summary>
            FlipDiscard = ::DXGI_SWAP_EFFECT_FLIP_DISCARD
        };

        /// <summary>
        /// Flags for surface and resource creation options.
        /// </summary>
        [Flags]
        public enum class DXGIUsage : UINT
        {
            CPUAccessNone = DXGI_CPU_ACCESS_NONE,
            CPUAccessDynamic = DXGI_CPU_ACCESS_DYNAMIC,
            CPUAccessReadWrite = DXGI_CPU_ACCESS_READ_WRITE,
            CPUAccessScratch = DXGI_CPU_ACCESS_SCRATCH,

            /// <summary>
            /// Use the surface or resource as an input to a shader.
            /// </summary>
            ShaderInput = DXGI_USAGE_SHADER_INPUT,

            /// <summary>
            /// Use the surface or resource as an output render target.
            /// </summary>
            RenderTargetOutput = DXGI_USAGE_RENDER_TARGET_OUTPUT,

            /// <summary>
            /// The surface or resource is used as a back buffer. You don¡¯t need to
            /// pass BackBuffer when you create a swap chain. But you can determine
            /// whether a resource belongs to a swap chain when you call
            /// DXGIResource::GetUsage and get BackBuffer.
            /// </summary>
            BackBuffer = DXGI_USAGE_BACK_BUFFER,

            /// <summary>
            /// Share the surface or resource.
            /// </summary>
            Shared = DXGI_USAGE_SHARED,

            /// <summary>
            /// Use the surface or resource for reading only.
            /// </summary>
            ReadOnly = DXGI_USAGE_READ_ONLY,

            /// <summary>
            /// This flag is for internal use only.
            /// </summary>
            DiscardOnPresent = DXGI_USAGE_DISCARD_ON_PRESENT,

            /// <summary>
            /// Use the surface or resource for unordered access.
            /// </summary>
            UnorderedAccess = DXGI_USAGE_UNORDERED_ACCESS
        };
        
        
        /// <summary>
        /// Represents a color value with alpha, which is used for transparency.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3DColorValue : IEquatable<D3DColorValue>
        {
            /// <summary>
            /// Floating-point value that specifies the red component of a color. This
            /// value generally is in the range from 0.0 through 1.0. A value of 0.0
            /// indicates the complete absence of the red component, while a value of 1.0
            /// indicates that red is fully present.
            /// </summary>
            float r;

            /// <summary>
            /// Floating-point value that specifies the green component of a color. This
            /// value generally is in the range from 0.0 through 1.0. A value of 0.0
            /// indicates the complete absence of the green component, while a value of
            /// 1.0 indicates that green is fully present.
            /// </summary>
            float g;

            /// <summary>
            /// Floating-point value that specifies the blue component of a color. This
            /// value generally is in the range from 0.0 through 1.0. A value of 0.0
            /// indicates the complete absence of the blue component, while a value of
            /// 1.0 indicates that blue is fully present.
            /// </summary>
            float b;

            /// <summary>
            /// Floating-point value that specifies the alpha component of a color. This
            /// value generally is in the range from 0.0 through 1.0. A value of 0.0
            /// indicates fully transparent, while a value of 1.0 indicates fully opaque.
            /// </summary>
            float a;

            D3DColorValue(float r, float g, float b, float a);

            property float default[int]
            {
                float get(int index);
                void set(int index, float value);
            }

            static bool operator==(
                [In][IsReadOnly] D3DColorValue% lhs, [In][IsReadOnly] D3DColorValue% rhs);

            static bool operator!=(
                [In][IsReadOnly] D3DColorValue% lhs, [In][IsReadOnly] D3DColorValue% rhs);

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3DColorValue other);
        };

        /// <summary>
        /// Describes an adapter (or video card) by using DXGI 1.0.
        /// </summary>
        public value struct DXGIAdapterDesc
        {
            /// <summary>
            /// A string that contains the adapter description. On feature level 9
            /// graphics hardware, GetDesc returns ¡°Software Adapter¡± for the
            /// description string.
            /// </summary>
            String^ Description;

            /// <summary>
            /// The PCI ID of the hardware vendor. On feature level 9 graphics hardware,
            /// GetDesc returns zeros for the PCI ID of the hardware vendor.
            /// </summary>
            unsigned int VendorId;

            /// <summary>
            /// The PCI ID of the hardware device. On feature level 9 graphics hardware,
            /// GetDesc returns zeros for the PCI ID of the hardware device.
            /// </summary>
            unsigned int DeviceId;

            /// <summary>
            /// The PCI ID of the sub system. On feature level 9 graphics hardware,
            /// GetDesc returns zeros for the PCI ID of the sub system.
            /// </summary>
            unsigned int SubSysId;

            /// <summary>
            /// The PCI ID of the revision number of the adapter. On feature level 9
            /// graphics hardware, GetDesc returns zeros for the PCI ID of the revision
            /// number of the adapter.
            /// </summary>
            unsigned int Revision;

            /// <summary>
            /// The number of bytes of dedicated video memory that are not shared with
            /// the CPU.
            /// </summary>
            unsigned long long DedicatedVideoMemory;

            /// <summary>
            /// The number of bytes of dedicated system memory that are not shared with
            /// the CPU. This memory is allocated from available system memory at
            /// boot time.
            /// </summary>
            unsigned long long DedicatedSystemMemory;

            /// <summary>
            /// The number of bytes of shared system memory. This is the maximum value
            /// of system memory that may be consumed by the adapter during operation.
            /// Any incidental memory consumed by the driver as it manages and uses
            /// video memory is additional.
            /// </summary>
            unsigned long long SharedSystemMemory;

            /// <summary>
            /// A unique value that identifies the adapter.
            /// </summary>
            Common::Luid AdapterLuid;
        };


        /// <summary>
        /// Describes an adapter (or video card) using DXGI 1.1.
        /// </summary>
        public value struct DXGIAdapterDesc1
        {
            /// <summary>
            /// A string that contains the adapter description. On feature level 9
            /// graphics hardware, GetDesc1 returns ¡°Software Adapter¡± for the
            /// description string.
            /// </summary>
            String^ Description;

            /// <summary>
            /// The PCI ID of the hardware vendor. On feature level 9 graphics hardware,
            /// GetDesc1 returns zeros for the PCI ID of the hardware vendor.
            /// </summary>
            unsigned int VendorId;

            /// <summary>
            /// The PCI ID of the hardware device. On feature level 9 graphics hardware,
            /// GetDesc1 returns zeros for the PCI ID of the hardware device.
            /// </summary>
            unsigned int DeviceId;

            /// <summary>
            /// The PCI ID of the sub system. On feature level 9 graphics hardware,
            /// GetDesc1 returns zeros for the PCI ID of the sub system.
            /// </summary>
            unsigned int SubSysId;

            /// <summary>
            /// The PCI ID of the revision number of the adapter. On feature level 9
            /// graphics hardware, GetDesc1 returns zeros for the PCI ID of the revision
            /// number of the adapter.
            /// </summary>
            unsigned int Revision;

            /// <summary>
            /// The number of bytes of dedicated video memory that are not shared with
            /// the CPU.
            /// </summary>
            unsigned long long DedicatedVideoMemory;

            /// <summary>
            /// The number of bytes of dedicated system memory that are not shared with
            /// the CPU. This memory is allocated from available system memory at boot
            /// time.
            /// </summary>
            unsigned long long DedicatedSystemMemory;

            /// <summary>
            /// The number of bytes of shared system memory. This is the maximum value of
            /// system memory that may be consumed by the adapter during operation. Any
            /// incidental memory consumed by the driver as it manages and uses video
            /// memory is additional.
            /// </summary>
            unsigned long long SharedSystemMemory;

            /// <summary>
            /// A unique value that identifies the adapter.
            /// </summary>
            Common::Luid AdapterLuid;

            /// <summary>
            /// A value of the DXGIAdapterFlag enumerated type that describes the
            /// adapter type.
            /// </summary>
            DXGIAdapterFlag Flags;
        };
     
        /// <summary>
        /// Describes timing and presentation statistics for a frame.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGIFrameStatistics
        {
            /// <summary>
            /// A value that represents the running total count of times that an image
            /// was presented to the monitor since the computer booted.
            /// </summary>
            unsigned int PresentCount;

            /// <summary>
            /// A value that represents the running total count of v-blanks at which the
            /// last image was presented to the monitor and that have happened since the
            /// computer booted (for windowed mode, since the swap chain was created).
            /// </summary>
            unsigned int PresentRefreshCount;

            /// <summary>
            /// A value that represents the running total count of v-blanks when the
            /// scheduler last sampled the machine time by calling
            /// QueryPerformanceCounter and that have happened since the computer booted
            /// (for windowed mode, since the swap chain was created).
            /// </summary>
            unsigned int SyncRefreshCount;

            /// <summary>
            /// A value that represents the high-resolution performance counter timer.
            /// This value is the same as the value returned by the
            /// QueryPerformanceCounter function.
            /// </summary>
            long long SyncQPCTime;

            /// <summary>
            /// Reserved. Always returns 0.
            /// </summary>
            long long SyncGPUTime;
        };
        
        /// <summary>
        /// Represents an RGB color.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGIRGB
        {
            /// <summary>
            /// A value representing the color of the red component. The range of this
            /// value is between 0 and 1.
            /// </summary>
            float Red;

            /// <summary>
            /// A value representing the color of the green component. The range of this
            /// value is between 0 and 1.
            /// </summary>
            float Green;

            /// <summary>
            /// A value representing the color of the blue component. The range of this
            /// value is between 0 and 1.
            /// </summary>
            float Blue;

            DXGIRGB(float r, float g, float b);
        };

        /// <summary>
        /// Controls the settings of a gamma curve.
        /// </summary>
        public value struct DXGIGammaControl
        {
            /// <summary>
            /// A DXGIRGB structure with scalar values that are applied to rgb values
            /// before being sent to the gamma look up table.
            /// </summary>
            DXGIRGB Scale;

            /// <summary>
            /// A DXGI_RGB structure with offset values that are applied to the rgb
            /// values before being sent to the gamma look up table.
            /// </summary>
            DXGIRGB Offset;

            /// <summary>
            /// An array of DXGI_RGB structures that control the points of a gamma curve.
            /// </summary>
            array<DXGIRGB>^ GammaCurve;

            DXGIGammaControl(DXGIRGB scale, DXGIRGB offset, array<DXGIRGB>^ gammaCurve);
        };

        /// <summary>
        /// Controls the gamma capabilities of an adapter.
        /// </summary>
        public value struct DXGIGammaControlCapabilities
        {
            /// <summary>
            /// True if scaling and offset operations are supported during gamma
            /// correction; otherwise, false.
            /// </summary>
            Common::CBool ScaleAndOffsetSupported;

            /// <summary>
            /// A value describing the maximum range of the control-point positions.
            /// </summary>
            float MaxConvertedValue;

            /// <summary>
            /// A value describing the minimum range of the control-point positions.
            /// </summary>
            float MinConvertedValue;

            /// <summary>
            /// A value describing the number of control points in the array.
            /// </summary>
            unsigned int NumGammaControlPoints;

            /// <summary>
            /// An array of values describing control points; the maximum length of
            /// control points is 1025.
            /// </summary>
            array<float>^ ControlPointPositions;
        };
        
        /// <summary>
        /// Represents a rational number.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGIRational
        {
            /// <summary>
            /// An unsigned integer value representing the top of the rational number.
            /// </summary>
            unsigned int Numerator;

            /// <summary>
            /// An unsigned integer value representing the bottom of the rational number.
            /// </summary>
            unsigned int Denominator;

            DXGIRational(unsigned int numerator, unsigned int denominator);
        };
        
        /// <summary>
        /// Describes a mapped rectangle that is used to access a surface.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGIMappedRect
        {
            /// <summary>
            /// A value that describes the width, in bytes, of the surface.
            /// </summary>
            int Pitch;

            /// <summary>
            /// A pointer to the image buffer of the surface.
            /// </summary>
            IntPtr pBits;
        };
        
        /// <summary>
        /// Describes a display mode.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGIModeDesc
        {
            /// <summary>
            /// A value that describes the resolution width. If you specify the width
            /// as zero when you call the DXGIFactory::CreateSwapChain method to create
            /// a swap chain, the runtime obtains the width from the output window
            /// and assigns this width value to the swap-chain description. You]
            /// can subsequently call the DXGISwapChain::GetDesc method to retrieve
            /// the assigned width value.
            /// </summary>
            unsigned int Width;

            /// <summary>
            /// A value describing the resolution height. If you specify the height as
            /// zero when you call the DXGIFactory::CreateSwapChain method to create
            /// a swap chain, the runtime obtains the height from the output window
            /// and assigns this height value to the swap-chain description. You can
            /// subsequently call the DXGISwapChain::GetDesc method to retrieve
            /// the assigned height value.
            /// </summary>
            unsigned int Height;

            /// <summary>
            /// A DXGIRational structure describing the refresh rate in hertz.
            /// </summary>
            DXGIRational RefreshRate;

            /// <summary>
            /// A DXGIFormat describing the display format.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// A member of the DXGIModeScanlineOrder enumerated type describing
            /// the scanline drawing mode.
            /// </summary>
            DXGIModeScanlineOrder ScanlineOrdering;

            /// <summary>
            /// A member of the DXGIModeScaling enumerated type describing the
            /// scaling mode.
            /// </summary>
            DXGIModeScaling Scaling;
        };

        /// <summary>
        /// Describes an output or physical connection between the adapter (video card)
        /// and a device.
        /// </summary>
        public value struct DXGIOutputDesc
        {
            /// <summary>
            /// A string that contains the name of the output device.
            /// </summary>
            String^ DeviceName;

            /// <summary>
            /// A Rect structure containing the bounds of the output in desktop
            /// coordinates. Desktop coordinates depend on the dots per inch (DPI)
            /// of the desktop.
            /// </summary>
            Common::Rect DesktopCoordinates;

            /// <summary>
            /// True if the output is attached to the desktop; otherwise, false.
            /// </summary>
            Common::CBool AttachedToDesktop;

            /// <summary>
            /// A member of the DXGIModeRotation enumerated type describing on how
            /// an image is rotated by the output.
            /// </summary>
            DXGIModeRotation Rotation;

            /// <summary>
            /// An handle that represents the display monitor.
            /// </summary>
            IntPtr Monitor;
        };
         
        /// <summary>
        /// Describes multi-sampling parameters for a resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGISampleDesc
        {
            /// <summary>
            /// The number of multisamples per pixel.
            /// </summary>
            unsigned int Count;

            /// <summary>
            /// The image quality level. The higher the quality, the lower
            /// the performance.
            /// </summary>
            unsigned int Quality;

            DXGISampleDesc(unsigned int sampleCount, unsigned int quality);
        };

        /// <summary>
        /// Represents a handle to a shared resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGISharedResource
        {
            /// <summary>
            /// A handle to a shared resource.
            /// </summary>
            IntPtr Handle;
        };
        
        /// <summary>
        /// Describes a surface.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGISurfaceDesc
        {
            /// <summary>
            /// A value describing the surface width.
            /// </summary>
            unsigned int Width;

            /// <summary>
            /// A value describing the surface height.
            /// </summary>
            unsigned int Height;

            /// <summary>
            /// A member of the DXGIFormat enumerated type that describes the surface
            /// format.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// A DXGISampleDesc structure that describes multi-sampling
            /// parameters for the surface.
            /// </summary>
            DXGISampleDesc SampleDesc;
        };
        
        /// <summary>
        /// Describes a swap chain.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct DXGISwapChainDesc
        {
            /// <summary>
            /// A DXGIModeDesc structure that describes the backbuffer display mode.
            /// </summary>
            DXGIModeDesc BufferDesc;

            /// <summary>
            /// A DXGISampleDesc structure that describes multi-sampling parameters.
            /// </summary>
            DXGISampleDesc SampleDesc;

            /// <summary>
            /// A member of the DXGI_USAGE enumerated type that describes the surface
            /// usage and CPU access options for the back buffer. The back buffer can
            /// be used for shader input or render-target output.
            /// </summary>
            DXGIUsage BufferUsage;

            /// <summary>
            /// A value that describes the number of buffers in the swap chain. When you
            /// call IDXGIFactory::CreateSwapChain to create a full-screen swap chain,
            /// you typically include the front buffer in this value.
            /// </summary>
            unsigned int BufferCount;

            /// <summary>
            /// An handle to the output window. This member must not be null.
            /// </summary>
            IntPtr OutputWindow;

            /// <summary>
            /// A Boolean value that specifies whether the output is in windowed mode.
            /// TRUE if the output is in windowed mode; otherwise, FALSE.
            /// </summary>
            Common::CBool Windowed;

            /// <summary>
            /// A member of the DXGISwapEffect enumerated type that describes
            /// options for handling the contents of the presentation buffer after
            /// presenting a surface.
            /// </summary>
            DXGISwapEffect SwapEffect;

            /// <summary>
            /// A member of the DXGISwapChainFlag enumerated type that describes
            /// options for swap-chain behavior.
            /// </summary>
            DXGISwapChainFlag Flags;
        };
    }
}