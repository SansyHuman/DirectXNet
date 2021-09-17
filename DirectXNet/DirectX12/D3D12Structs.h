#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../DXGI/DXGIStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

namespace DirectXNet
{
    namespace Common
    {
        ref class D3D10Blob;
    }

    namespace DirectX12
    {
        ref class D3D12Device;
        ref class D3D12Resource;

        /// <summary>
        /// Used to determine which kinds of command lists are capable of supporting various operations.
        /// For example, whether a command list supports immediate writes.
        /// </summary>
        [Flags]
        public enum class D3D12CommandListSupportFlags : UINT
        {
            /// <summary>
            /// Specifies that no command list supports the operation in question.
            /// </summary>
            None = D3D12_COMMAND_LIST_SUPPORT_FLAG_NONE,

            /// <summary>
            /// Specifies that direct command lists can support the operation in question.
            /// </summary>
            Direct = D3D12_COMMAND_LIST_SUPPORT_FLAG_DIRECT,

            /// <summary>
            /// Specifies that command list bundles can support the operation in question.
            /// </summary>
            Bundle = D3D12_COMMAND_LIST_SUPPORT_FLAG_BUNDLE,

            /// <summary>
            /// Specifies that compute command lists can support the operation in question.
            /// </summary>
            Compute = D3D12_COMMAND_LIST_SUPPORT_FLAG_COMPUTE,

            /// <summary>
            /// Specifies that copy command lists can support the operation in question.
            /// </summary>
            Copy = D3D12_COMMAND_LIST_SUPPORT_FLAG_COPY,

            /// <summary>
            /// Specifies that video-decode command lists can support the operation in question.
            /// </summary>
            VideoDecode = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_DECODE,

            /// <summary>
            /// Specifies that video-processing command lists can support the operation is question.
            /// </summary>
            VideoProcess = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_PROCESS,

            /// <summary>
            /// Specifies that video-encode command lists can support the operation is question.
            /// </summary>
            VideoEncode = D3D12_COMMAND_LIST_SUPPORT_FLAG_VIDEO_ENCODE
        };

        /// <summary>
        /// Specifies the type of a command list.
        /// </summary>
        public enum class D3D12CommandListType : UINT
        {
            /// <summary>
            /// Specifies a command buffer that the GPU can execute. A direct command list doesn't inherit
            /// any GPU state.
            /// </summary>
            Direct = D3D12_COMMAND_LIST_TYPE_DIRECT,

            /// <summary>
            /// Specifies a command buffer that can be executed only directly via a direct command list.
            /// A bundle command list inherits all GPU state (except for the currently set pipeline
            /// state object and primitive topology).
            /// </summary>
            Bundle = D3D12_COMMAND_LIST_TYPE_BUNDLE,

            /// <summary>
            /// Specifies a command buffer for computing.
            /// </summary>
            Compute = D3D12_COMMAND_LIST_TYPE_COMPUTE,

            /// <summary>
            /// Specifies a command buffer for copying.
            /// </summary>
            Copy = D3D12_COMMAND_LIST_TYPE_COPY,

            /// <summary>
            /// Specifies a command buffer for video decoding.
            /// </summary>
            VideoDecode = D3D12_COMMAND_LIST_TYPE_VIDEO_DECODE,

            /// <summary>
            /// Specifies a command buffer for video processing.
            /// </summary>
            VideoProcess = D3D12_COMMAND_LIST_TYPE_VIDEO_PROCESS,

            /// <summary>
            /// Specifies a command buffer for video encoding.
            /// </summary>
            VideoEncode = D3D12_COMMAND_LIST_TYPE_VIDEO_ENCODE
        };

        /// <summary>
        /// Identifies the tier level of conservative rasterization.
        /// </summary>
        public enum class D3D12ConservativeRasterizationTier : UINT
        {
            /// <summary>
            /// Conservative rasterization is not supported.
            /// </summary>
            NotSupported = D3D12_CONSERVATIVE_RASTERIZATION_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Tier 1 enforces a maximum 1/2 pixel uncertainty region and does not support post-snap
            /// degenerates. This is good for tiled rendering, a texture atlas, light map generation and
            /// sub-pixel shadow maps.
            /// </summary>
            Tier1 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_1,

            /// <summary>
            /// Tier 2 reduces the maximum uncertainty region to 1/256 and requires post-snap degenerates
            /// not be culled. This tier is helpful for CPU-based algorithm acceleration
            /// (such as voxelization).
            /// </summary>
            Tier2 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_2,

            /// <summary>
            /// Tier 3 maintains a maximum 1/256 uncertainty region and adds support for inner input
            /// coverage. Inner input coverage adds the new value SV_InnerCoverage to High Level Shading
            /// Language (HLSL). This is a 32-bit scalar integer that can be specified on input to a pixel
            /// shader, and represents the underestimated conservative rasterization information (that is,
            /// whether a pixel is guaranteed-to-be-fully covered). This tier is helpful for occlusion culling.
            /// </summary>
            Tier3 = D3D12_CONSERVATIVE_RASTERIZATION_TIER_3
        };

        /// <summary>
        /// Specifies the level of sharing across nodes of an adapter, such as Tier 1 Emulated, Tier 1,
        /// or Tier 2.
        /// </summary>
        public enum class D3D12CrossNodeSharingTier : UINT
        {
            /// <summary>
            /// If an adapter has only 1 node, then cross-node sharing doesn't apply
            /// </summary>
            NotSupported = D3D12_CROSS_NODE_SHARING_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Tier 1 Emulated. However, drivers stage these copy operations through a driver-internal
            /// system memory allocation. This will cause these copy operations to consume time on the
            /// destination GPU as well as the source.
            /// </summary>
            Tier1Emulated = D3D12_CROSS_NODE_SHARING_TIER_1_EMULATED,

            /// <summary>
            /// Tier 1. Devices that set the CrossNodeSharingTier member of the D3D12FeatureDataD3D12Options
            /// structure to Tier1 only support the following cross-node copy operations:
            /// <para>D3D12CommandList::CopyBufferRegion</para>
            /// <para>D3D12CommandList::CopyTextureRegion</para>
            /// <para>D3D12CommandList::CopyResource</para>
            /// <para>Additionally, the cross-node resource must be the destination of the copy operation.
            /// </para>
            /// </summary>
            Tier1 = D3D12_CROSS_NODE_SHARING_TIER_1,

            /// <summary>
            /// Tier 2. Devices that set the CrossNodeSharingTier member of the D3D12FeatureDataD3D12Options
            /// structure to Tier2 support all operations across nodes, except for the following:
            /// <para>Render target views.</para>
            /// <para>Depth stencil views.</para>
            /// <para>UAV atomic operations. Similar to CPU/GPU interop, shaders may perform UAV
            /// atomic operations; however, no atomicity across adapters is guaranteed.</para>
            /// <para>Applications can retrieve the node where a resource/heap exists from the D3D12HeapDesc
            /// structure. These values are retrievable for opened resources. The runtime performs the
            /// appropriate re-mapping in case the 2 devices are using different UMD-specified node
            /// re-mappings.</para>
            /// </summary>
            Tier2 = D3D12_CROSS_NODE_SHARING_TIER_2,

            /// <summary>
            /// Indicates support for D3D12HeapFlag::AllowShaderAtomics on heaps that are visible to
            /// multiple nodes.
            /// </summary>
            Tier3 = D3D12_CROSS_NODE_SHARING_TIER_3
        };

        /// <summary>
        /// Defines constants that specify a Direct3D 12 feature or feature set to query about. When you
        /// want to query for the level to which an adapter supports a feature, pass one of these values
        /// to D3D12Device::CheckFeatureSupport.
        /// </summary>
        public enum class D3D12Feature : UINT
        {
            /// <summary>
            /// Indicates a query for the level of support for basic Direct3D 12 feature options.
            /// </summary>
            D3D12Options = D3D12_FEATURE_D3D12_OPTIONS,

            /// <summary>
            /// Indicates a query for the adapter's architectural details, so that your application can
            /// better optimize for certain adapter properties.
            /// </summary>
            Architecture = D3D12_FEATURE_ARCHITECTURE,

            /// <summary>
            /// Indicates a query for info about the feature levels supported.
            /// </summary>
            FeatureLevels = D3D12_FEATURE_FEATURE_LEVELS,

            /// <summary>
            /// Indicates a query for the resources supported by the current graphics driver for a
            /// given format.
            /// </summary>
            FormatSupport = D3D12_FEATURE_FORMAT_SUPPORT,

            /// <summary>
            /// Indicates a query for the image quality levels for a given format and sample count.
            /// </summary>
            MultisampleQualityLevels = D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,

            /// <summary>
            /// Indicates a query for the DXGI data format.
            /// </summary>
            FormatInfo = D3D12_FEATURE_FORMAT_INFO,

            /// <summary>
            /// Indicates a query for the GPU's virtual address space limitations.
            /// </summary>
            GpuVirtualAddressSupport = D3D12_FEATURE_GPU_VIRTUAL_ADDRESS_SUPPORT,

            /// <summary>
            /// Indicates a query for the supported shader model.
            /// </summary>
            ShaderModel = D3D12_FEATURE_SHADER_MODEL,

            /// <summary>
            /// Indicates a query for the level of support for HLSL 6.0 wave operations.
            /// </summary>
            Options1 = D3D12_FEATURE_D3D12_OPTIONS1,

            /// <summary>
            /// Indicates a query for the level of support for protected resource sessions.
            /// </summary>
            ProtectedResourceSessionSupport = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_SUPPORT,

            /// <summary>
            /// Indicates a query for root signature version support.
            /// </summary>
            RootSignature = D3D12_FEATURE_ROOT_SIGNATURE,

            /// <summary>
            /// Indicates a query for each adapter's architectural details, so that your application can
            /// better optimize for certain adapter properties.
            /// </summary>
            Architecture1 = D3D12_FEATURE_ARCHITECTURE1,

            /// <summary>
            /// Indicates a query for the level of support for depth-bounds tests and programmable
            /// sample positions.
            /// </summary>
            Options2 = D3D12_FEATURE_D3D12_OPTIONS2,

            /// <summary>
            /// Indicates a query for the level of support for shader caching.
            /// </summary>
            ShaderCache = D3D12_FEATURE_SHADER_CACHE,

            /// <summary>
            /// Indicates a query for the adapter's support for prioritization of different command queue types.
            /// </summary>
            CommandQueuePriority = D3D12_FEATURE_COMMAND_QUEUE_PRIORITY,

            /// <summary>
            /// Indicates a query for the level of support for timestamp queries, format-casting,
            /// immediate write, view instancing, and barycentrics.
            /// </summary>
            Options3 = D3D12_FEATURE_D3D12_OPTIONS3,

            /// <summary>
            /// Indicates a query for whether or not the adapter supports creating heaps from existing
            /// system memory.
            /// </summary>
            ExistingHeaps = D3D12_FEATURE_EXISTING_HEAPS,

            /// <summary>
            /// Indicates a query for the level of support for 64KB-aligned MSAA textures, cross-API sharing,
            /// and native 16-bit shader operations.
            /// </summary>
            Options4 = D3D12_FEATURE_D3D12_OPTIONS4,

            /// <summary>
            /// Indicates a query for the level of support for heap serialization.
            /// </summary>
            Serialization = D3D12_FEATURE_SERIALIZATION,

            /// <summary>
            /// Indicates a query for the level of support for the sharing of resources between
            /// different adapters-for example, multiple GPUs.
            /// </summary>
            CrossNode = D3D12_FEATURE_CROSS_NODE,

            /// <summary>
            /// Starting with Windows 10, version 1809 (10.0; Build 17763), indicates a query for the level
            /// of support for render passes, ray tracing, and shader-resource view tier 3 tiled resources.
            /// </summary>
            Options5 = D3D12_FEATURE_D3D12_OPTIONS5,

            /// <summary>
            /// Starting with Windows 10, version 1903 (10.0; Build 18362), indicates a query for the level
            /// of support for variable-rate shading (VRS), and indicates whether or not background
            /// processing is supported.
            /// </summary>
            Options6 = D3D12_FEATURE_D3D12_OPTIONS6,

            /// <summary>
            /// Indicates a query for the level of support for metacommands.
            /// </summary>
            QueryMetaCommand = D3D12_FEATURE_QUERY_META_COMMAND,

            /// <summary>
            /// Starting with Windows 10, version 2004 (10.0; Build 19041), indicates a query for the level
            /// of support for mesh and amplification shaders, and for sampler feedback.
            /// </summary>
            Options7 = D3D12_FEATURE_D3D12_OPTIONS7,

            /// <summary>
            /// Starting with Windows 10, version 2004 (10.0; Build 19041), indicates a query to retrieve
            /// the count of protected resource session types.
            /// </summary>
            ProtectedResourceSessionTypeCount = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPE_COUNT,

            /// <summary>
            /// Starting with Windows 10, version 2004 (10.0; Build 19041), indicates a query to retrieve
            /// the list of protected resource session types.
            /// </summary>
            ProtectedResourceSessionTypes = D3D12_FEATURE_PROTECTED_RESOURCE_SESSION_TYPES,

            /// <summary>
            /// Starting with Windows SDK version 10.0.20348.0, indicates whether or not unaligned
            /// block-compressed textures are supported.
            /// </summary>
            Options8 = D3D12_FEATURE_D3D12_OPTIONS8,

            /// <summary>
            /// Starting with Windows SDK version 10.0.20348.0, indicates whether or not support exists
            /// for mesh shaders, values of SV_RenderTargetArrayIndex that are 8 or greater, typed resource
            /// 64-bit integer atomics, derivative and derivative-dependent texture sample operations, and
            /// the level of support for WaveMMA (wave_matrix) operations.
            /// </summary>
            Options9 = D3D12_FEATURE_D3D12_OPTIONS9,

            WaveMMA = D3D12_FEATURE_WAVE_MMA
        };

        /// <summary>
        /// Specifies the level of support for programmable sample positions that's offered by the adapter.
        /// </summary>
        public enum class D3D12ProgrammableSamplePositionsTier : UINT
        {
            /// <summary>
            /// Indicates that there's no support for programmable sample positions.
            /// </summary>
            NotSupported = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Indicates that there's tier 1 support for programmable sample positions. In tier 1,
            /// a single sample pattern can be specified to repeat for every pixel (SetSamplePosition
            /// parameter NumPixels = 1) and ResolveSubResource is supported.
            /// </summary>
            Tier1 = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_1,

            /// <summary>
            /// Indicates that there's tier 2 support for programmable sample positions. In tier 2,
            /// four separate sample patterns can be specified for each pixel in a 2x2 grid
            /// (SetSamplePosition parameter NumPixels = 1) that repeats over the render-target or
            /// viewport, aligned on even coordinates .
            /// </summary>
            Tier2 = D3D12_PROGRAMMABLE_SAMPLE_POSITIONS_TIER_2
        };

        /// <summary>
        /// Describes minimum precision support options for shaders in the current graphics driver.
        /// </summary>
        [Flags]
        public enum class D3D12ShaderMinPrecisionSupport : UINT
        {
            /// <summary>
            /// The driver supports only full 32-bit precision for all shader stages.
            /// </summary>
            None = D3D12_SHADER_MIN_PRECISION_SUPPORT_NONE,

            /// <summary>
            /// The driver supports 10-bit precision.
            /// </summary>
            Support10Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_10_BIT,

            /// <summary>
            /// The driver supports 16-bit precision.
            /// </summary>
            Support16Bit = D3D12_SHADER_MIN_PRECISION_SUPPORT_16_BIT
        };

        /// <summary>
        /// Defines constants that specify a cross-API sharing support tier.
        /// </summary>
        public enum class D3D12SharedResourceCompatibilityTier : UINT
        {
            /// <summary>
            /// Specifies that the most basic level of cross-API sharing is supported, including the
            /// following resource data formats.
            /// <para>* DXGI_FORMAT_R8G8B8A8_UNORM</para>
            /// <para>* DXGI_FORMAT_R8G8B8A8_UNORM_SRGB </para>
            /// <para>* DXGI_FORMAT_B8G8R8A8_UNORM     </para>
            /// <para>* DXGI_FORMAT_B8G8R8A8_UNORM_SRGB</para>
            /// <para>* DXGI_FORMAT_B8G8R8X8_UNORM     </para>
            /// <para>* DXGI_FORMAT_B8G8R8X8_UNORM_SRGB</para>
            /// <para>* DXGI_FORMAT_R10G10B10A2_UNORM  </para>
            /// <para>* DXGI_FORMAT_R16G16B16A16_FLOAT </para>
            /// </summary>
            Tier0 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_0,

            /// <summary>
            /// Specifies that cross-API sharing functionality of Tier 0 is supported, plus the
            /// following formats.
            /// <para>* DXGI_FORMAT_R16G16B16A16_TYPELESS</para>
            /// <para>* DXGI_FORMAT_R10G10B10A2_TYPELESS</para>
            /// <para>* DXGI_FORMAT_R8G8B8A8_TYPELESS   </para>
            /// <para>* DXGI_FORMAT_R8G8B8X8_TYPELESS   </para>
            /// <para>* DXGI_FORMAT_R16G16_TYPELESS     </para>
            /// <para>* DXGI_FORMAT_R8G8_TYPELESS       </para>
            /// <para>* DXGI_FORMAT_R32_TYPELESS        </para>
            /// <para>* DXGI_FORMAT_R16_TYPELESS        </para>
            /// <para>* DXGI_FORMAT_R8_TYPELESS         </para>
            /// </summary>
            Tier1 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_1,

            /// <summary>
            /// Specifies that cross-API sharing functionality of Tier 1 is supported, plus the
            /// following formats.
            /// <para>* DXGI_FORMAT_NV12 </para>
            /// </summary>
            Tier2 = D3D12_SHARED_RESOURCE_COMPATIBILITY_TIER_2
        };

        /// <summary>
        /// Identifies the tier of resource binding being used.
        /// </summary>
        public enum class D3D12ResourceBindingTier : UINT
        {
            /// <summary>
            /// Tier 1.
            /// </summary>
            Tier1 = D3D12_RESOURCE_BINDING_TIER_1,

            /// <summary>
            /// Tier 2.
            /// </summary>
            Tier2 = D3D12_RESOURCE_BINDING_TIER_2,

            /// <summary>
            /// Tier 3.
            /// </summary>
            Tier3 = D3D12_RESOURCE_BINDING_TIER_3
        };

        /// <summary>
        /// Specifies which resource heap tier the hardware and driver support.
        /// </summary>
        public enum class D3D12ResourceHeapTier : UINT
        {
            /// <summary>
            /// Indicates that heaps can only support resources from a single resource category.
            /// In tier 1, these resource categories are mutually exclusiveand cannot be used with the
            /// same heap.
            /// The resource category must be declared when creating a heap, using the correct
            /// D3D12HeapFlags enumeration constant.
            /// Applications cannot create heaps with flags that allow all three categories.
            /// </summary>
            Tier1 = D3D12_RESOURCE_HEAP_TIER_1,

            /// <summary>
            /// Indicates that heaps can support resources from all three categories.
            /// In tier 2, these resource categories can be mixed within the same heap.
            /// Applications may create heaps with flags that allow all three categories; but are not
            /// required to do so.
            /// Applications may be written to support tier 1 and seamlessly run on tier 2.
            /// </summary>
            Tier2 = D3D12_RESOURCE_HEAP_TIER_2
        };

        /// <summary>
        /// Identifies the tier level at which tiled resources are supported.
        /// </summary>
        public enum class D3D12TiledResourceTier : UINT
        {
            /// <summary>
            /// Indicates that textures cannot be created with the
            /// D3D12TextureLayout::Layout64KBUndefinedSwizzle layout.
            /// D3D12Device::CreateReservedResource cannot be used, not even for buffers.
            /// </summary>
            NotSupported = D3D12_TILED_RESOURCES_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Indicates that 2D textures can be created with the
            /// D3D12TextureLayout::Layout64KBUndefinedSwizzle layout.
            /// Limitations exist for certain resource formatsand properties.
            /// D3D12Device::CreateReservedResource can be used.
            /// </summary>
            Tier1 = D3D12_TILED_RESOURCES_TIER_1,

            /// <summary>
            /// Indicates that a superset of Tier_1 functionality is supported, including this additional
            /// support:
            /// <para>When the size of a texture mipmap level is at least one standard tile shape for
            /// its format, the mipmap level is guaranteed to be nonpacked.</para>
            /// <para>Shader instructions are available for clamping level-of-detail (LOD) and for
            /// obtaining status about the shader operation.</para>
            /// <para>Reading from NULL-mapped tiles treat that sampled value as zero.
            /// Writes to NULL - mapped tiles are discarded.</para>
            /// <para>Adapters that support feature level 12_0 all support TIER_2 or greater.</para>
            /// </summary>
            Tier2 = D3D12_TILED_RESOURCES_TIER_2,

            /// <summary>
            /// Indicates that a superset of Tier 2 is supported, with the addition that 3D textures
            /// (Volume Tiled Resources) are supported.
            /// </summary>
            Tier3 = D3D12_TILED_RESOURCES_TIER_3,
            Tier4 = D3D12_TILED_RESOURCES_TIER_4
        };

        /// <summary>
        /// Indicates the tier level at which view instancing is supported.
        /// </summary>
        public enum class D3D12ViewInstancingTier : UINT
        {
            /// <summary>
            /// View instancing is not supported.
            /// </summary>
            NotSupported = D3D12_VIEW_INSTANCING_TIER_NOT_SUPPORTED,

            /// <summary>
            /// View instancing is supported by draw-call level looping only.
            /// </summary>
            Tier1 = D3D12_VIEW_INSTANCING_TIER_1,

            /// <summary>
            /// View instancing is supported by draw-call level looping at worst, but the GPU can perform
            /// view instancing more efficiently in certain circumstances which are architecture-dependent.
            /// </summary>
            Tier2 = D3D12_VIEW_INSTANCING_TIER_2,

            /// <summary>
            /// View instancing is supported and instancing begins with the first shader stage that
            /// references SV_ViewID or with rasterization if no shader stage references SV_ViewID. This
            /// means that redundant work is eliminated across view instances when it's not dependent on
            /// SV_ViewID. Before rasterization, work that doesn't directly depend on SV_ViewID is
            /// shared across all views; only work that depends on SV_ViewID is repeated for each view.
            /// </summary>
            Tier3 = D3D12_VIEW_INSTANCING_TIER_3
        };

        /// <summary>
        /// Specifies the level of support for render passes on a graphics device.
        /// </summary>
        public enum class D3D12RenderPassTier : UINT
        {
            /// <summary>
            /// The user-mode display driver hasn't implemented render passes, and so the feature is
            /// provided only via software emulation. Render passes might not provide a performance
            /// advantage at this level of support.
            /// </summary>
            Tier0 = D3D12_RENDER_PASS_TIER_0,

            /// <summary>
            /// The render passes feature is implemented by the user-mode display driver, and render
            /// target/depth buffer writes may be accelerated. Unordered access view (UAV) writes are
            /// not efficiently supported within the render pass.
            /// </summary>
            Tier1 = D3D12_RENDER_PASS_TIER_1,

            /// <summary>
            /// The render passes feature is implemented by the user-mode display driver, render
            /// target/depth buffer writes may be accelerated, and unordered access view (UAV) writes
            /// (provided that writes in a render pass are not read until a subsequent render pass) are
            /// likely to be more efficient than issuing the same work without using a render pass.
            /// </summary>
            Tier2 = D3D12_RENDER_PASS_TIER_2
        };

        /// <summary>
        /// Specifies the level of ray tracing support on the graphics device.
        /// </summary>
        public enum class D3D12RaytracingTier : UINT
        {
            /// <summary>
            /// No support for ray tracing on the device. Attempts to create any ray tracing-related
            /// object will fail, and using ray tracing-related APIs on command lists results in
            /// undefined behavior.
            /// </summary>
            NotSupported = D3D12_RAYTRACING_TIER_NOT_SUPPORTED,

            /// <summary>
            /// The device supports tier 1 ray tracing functionality. In the current release, this
            /// tier represents all available ray tracing features.
            /// </summary>
            Tier1_0 = D3D12_RAYTRACING_TIER_1_0,
            Tier1_1 = D3D12_RAYTRACING_TIER_1_1
        };

        /// <summary>
        /// Defines constants that specify a shading rate tier (for variable-rate shading, or VRS).
        /// </summary>
        public enum class D3D12VariableShadingRateTier : UINT
        {
            /// <summary>
            /// Specifies that variable-rate shading is not supported.
            /// </summary>
            NotSupported = D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Specifies that variable-rate shading tier 1 is supported.
            /// </summary>
            Tier1 = D3D12_VARIABLE_SHADING_RATE_TIER_1,

            /// <summary>
            /// Specifies that variable-rate shading tier 2 is supported.
            /// </summary>
            Tier2 = D3D12_VARIABLE_SHADING_RATE_TIER_2
        };

        /// <summary>
        /// Defines constants that specify mesh and amplification shader support.
        /// </summary>
        public enum class D3D12MeshShaderTier : UINT
        {
            /// <summary>
            /// Specifies that mesh and amplification shaders are not supported.
            /// </summary>
            NotSupported = D3D12_MESH_SHADER_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Specifies that mesh and amplification shaders are supported.
            /// </summary>
            Tier1 = D3D12_MESH_SHADER_TIER_1
        };

        /// <summary>
        /// Defines constants that specify sampler feedback support.
        /// </summary>
        public enum class D3D12SamplerFeedbackTier : UINT
        {
            /// <summary>
            /// Specifies that mesh and amplification shaders are not supported.
            /// </summary>
            NotSupported = D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Specifies that mesh and amplification shaders are supported to tier 0.9.
            /// </summary>
            Tier0_9 = D3D12_SAMPLER_FEEDBACK_TIER_0_9,

            /// <summary>
            /// Specifies that mesh and amplification shaders are supported to tier 1.0.
            /// </summary>
            Tier1_0 = D3D12_SAMPLER_FEEDBACK_TIER_1_0
        };

        /// <summary>
        /// Defines constants that specify a level of support for WaveMMA (wave_matrix) operations.
        /// </summary>
        public enum class D3D12WaveMMATier : UINT
        {
            /// <summary>
            /// Specifies that WaveMMA (wave_matrix) operations are not supported.
            /// </summary>
            NotSupported = D3D12_WAVE_MMA_TIER_NOT_SUPPORTED,

            /// <summary>
            /// Specifies that WaveMMA (wave_matrix) operations are supported.
            /// </summary>
            Tier1_0 = D3D12_WAVE_MMA_TIER_1_0
        };

        public enum class D3D12WaveMMAInputDatatype : UINT
        {
            Invalid = D3D12_WAVE_MMA_INPUT_DATATYPE_INVALID,
            Byte = D3D12_WAVE_MMA_INPUT_DATATYPE_BYTE,
            Float16 = D3D12_WAVE_MMA_INPUT_DATATYPE_FLOAT16,
            Float = D3D12_WAVE_MMA_INPUT_DATATYPE_FLOAT
        };

        public enum class D3D12WaveMMADimension : UINT
        {
            Invalid = D3D12_WAVE_MMA_DIMENSION_INVALID,
            Dimension16 = D3D12_WAVE_MMA_DIMENSION_16,
            Dimension64 = D3D12_WAVE_MMA_DIMENSION_64
        };

        [Flags]
        public enum class D3D12WaveMMAAccumDatatype : UINT
        {
            None = D3D12_WAVE_MMA_ACCUM_DATATYPE_NONE,
            Int32 = D3D12_WAVE_MMA_ACCUM_DATATYPE_INT32,
            Float16 = D3D12_WAVE_MMA_ACCUM_DATATYPE_FLOAT16,
            Float = D3D12_WAVE_MMA_ACCUM_DATATYPE_FLOAT
        };

        /// <summary>
        /// Specifies resources that are supported for a provided format.
        /// </summary>
        [Flags]
        public enum class D3D12FormatSupport1 : UINT
        {
            None = D3D12_FORMAT_SUPPORT1_NONE,
            Buffer = D3D12_FORMAT_SUPPORT1_BUFFER,
            IAVertexBuffer = D3D12_FORMAT_SUPPORT1_IA_VERTEX_BUFFER,
            IAIndexBuffer = D3D12_FORMAT_SUPPORT1_IA_INDEX_BUFFER,
            SOBuffer = D3D12_FORMAT_SUPPORT1_SO_BUFFER,
            Texture1D = D3D12_FORMAT_SUPPORT1_TEXTURE1D,
            Texture2D = D3D12_FORMAT_SUPPORT1_TEXTURE2D,
            Texture3D = D3D12_FORMAT_SUPPORT1_TEXTURE3D,
            TextureCube = D3D12_FORMAT_SUPPORT1_TEXTURECUBE,
            ShaderLoad = D3D12_FORMAT_SUPPORT1_SHADER_LOAD,
            ShaderSample = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE,
            ShaderSampleComparison = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_COMPARISON,
            ShaderSampleMonoText = D3D12_FORMAT_SUPPORT1_SHADER_SAMPLE_MONO_TEXT,
            Mip = D3D12_FORMAT_SUPPORT1_MIP,
            RenderTarget = D3D12_FORMAT_SUPPORT1_RENDER_TARGET,
            Blendable = D3D12_FORMAT_SUPPORT1_BLENDABLE,
            DepthStencil = D3D12_FORMAT_SUPPORT1_DEPTH_STENCIL,
            MultisampleResolve = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RESOLVE,
            Display = D3D12_FORMAT_SUPPORT1_DISPLAY,
            CastWithinBitLayout = D3D12_FORMAT_SUPPORT1_CAST_WITHIN_BIT_LAYOUT,
            MultisampleRendertarget = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_RENDERTARGET,
            MultisampleLoad = D3D12_FORMAT_SUPPORT1_MULTISAMPLE_LOAD,
            ShaderGather = D3D12_FORMAT_SUPPORT1_SHADER_GATHER,
            BackBufferCast = D3D12_FORMAT_SUPPORT1_BACK_BUFFER_CAST,
            TypedUnorderedAccessView = D3D12_FORMAT_SUPPORT1_TYPED_UNORDERED_ACCESS_VIEW,
            ShaderGatherComparison = D3D12_FORMAT_SUPPORT1_SHADER_GATHER_COMPARISON,
            DecoderOutput = D3D12_FORMAT_SUPPORT1_DECODER_OUTPUT,
            VideoProcessorOutput = D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_OUTPUT,
            VideoProcessorInput = D3D12_FORMAT_SUPPORT1_VIDEO_PROCESSOR_INPUT,
            VideoEncoder = D3D12_FORMAT_SUPPORT1_VIDEO_ENCODER
        };

        /// <summary>
        /// Specifies which unordered resource options are supported for a provided format.
        /// </summary>
        [Flags]
        public enum class D3D12FormatSupport2 : UINT
        {
            None = D3D12_FORMAT_SUPPORT2_NONE,
            UAVAtomicAdd = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_ADD,
            UAVAtomicBitwiseOps = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_BITWISE_OPS,
            UAVAtomicCompareStoreOrCompareExchange = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_COMPARE_STORE_OR_COMPARE_EXCHANGE,
            UAVAtomicExchange = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_EXCHANGE,
            UAVAtomicSignedMinOrMax = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_SIGNED_MIN_OR_MAX,
            UAVAtomicUnsignedMinOrMax = D3D12_FORMAT_SUPPORT2_UAV_ATOMIC_UNSIGNED_MIN_OR_MAX,
            UAVTypedLoad = D3D12_FORMAT_SUPPORT2_UAV_TYPED_LOAD,
            UAVTypedStore = D3D12_FORMAT_SUPPORT2_UAV_TYPED_STORE,
            OutputMergerLogicOp = D3D12_FORMAT_SUPPORT2_OUTPUT_MERGER_LOGIC_OP,
            Tiled = D3D12_FORMAT_SUPPORT2_TILED,
            MultiplaneOverlay = D3D12_FORMAT_SUPPORT2_MULTIPLANE_OVERLAY,
            SamplerFeedback = D3D12_FORMAT_SUPPORT2_SAMPLER_FEEDBACK
        };

        /// <summary>
        /// Specifies options for determining quality levels.
        /// </summary>
        [Flags]
        public enum class D3D12MultisampleQualityLevelFlags : UINT
        {
            /// <summary>
            /// No options are supported.
            /// </summary>
            None = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE,

            /// <summary>
            /// The number of quality levels can be determined for tiled resources.
            /// </summary>
            TiledResource = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE
        };

        /// <summary>
        /// Defines constants that specify protected resource session support.
        /// </summary>
        [Flags]
        public enum class D3D12ProtectedResourceSessionSupportFlags : UINT
        {
            /// <summary>
            /// Indicates that protected resource sessions are not supported.
            /// </summary>
            None = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_NONE,

            /// <summary>
            /// Indicates that protected resource sessions are supported.
            /// </summary>
            Supported = D3D12_PROTECTED_RESOURCE_SESSION_SUPPORT_FLAG_SUPPORTED
        };

        /// <summary>
        /// Specifies the version of root signature layout.
        /// </summary>
        public enum class D3DRootSignatureVersion : UINT
        {
            /// <summary>
            /// Version one of root signature layout.
            /// </summary>
            Version1 = D3D_ROOT_SIGNATURE_VERSION_1,

            /// <summary>
            /// Version one of root signature layout.
            /// </summary>
            Version1_0 = D3D_ROOT_SIGNATURE_VERSION_1_0,

            /// <summary>
            /// Version 1.1 of root signature layout.
            /// </summary>
            Version1_1 = D3D_ROOT_SIGNATURE_VERSION_1_1
        };

        public enum class D3D12HeapSerializationTier : UINT
        {
            Tier0 = D3D12_HEAP_SERIALIZATION_TIER_0,
            Tier10 = D3D12_HEAP_SERIALIZATION_TIER_10
        };

        /// <summary>
        /// Describes the level of support for shader caching in the current graphics driver.
        /// </summary>
        [Flags]
        public enum class D3D12ShaderCacheSupportFlags : UINT
        {
            /// <summary>
            /// Indicates that the driver does not support shader caching.
            /// </summary>
            None = D3D12_SHADER_CACHE_SUPPORT_NONE,

            /// <summary>
            /// Indicates that the driver supports the CachedPSO member of the
            /// D3D12GraphicsPipelineStateDesc and D3D12ComputePipelineStateDesc structures.
            /// This is always supported.
            /// </summary>
            SinglePSO = D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO,

            /// <summary>
            /// Indicates that the driver supports the ID3D12PipelineLibrary interface, which
            /// provides application-controlled PSO grouping and caching. This is supported by
            /// drivers targetting the Windows 10 Anniversary Update.
            /// </summary>
            Library = D3D12_SHADER_CACHE_SUPPORT_LIBRARY,

            /// <summary>
            /// Indicates that the driver supports an OS-managed shader cache that stores compiled
            /// shaders in memory during the current run of the application.
            /// </summary>
            AutomaticInprocCache = D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE,

            /// <summary>
            /// Indicates that the driver supports an OS-managed shader cache that stores compiled
            /// shaders on disk to accelerate future runs of the application.
            /// </summary>
            AutomaticDiskCache = D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_DISK_CACHE,
            DriverManagedCache = D3D12_SHADER_CACHE_SUPPORT_DRIVER_MANAGED_CACHE
        };

        /// <summary>
        /// Specifies a shader model.
        /// </summary>
        public enum class D3DShaderModel : UINT
        {
            ShaderModel5_1 = D3D_SHADER_MODEL_5_1,
            ShaderModel6_0 = D3D_SHADER_MODEL_6_0,
            ShaderModel6_1 = D3D_SHADER_MODEL_6_1,
            ShaderModel6_2 = D3D_SHADER_MODEL_6_2,
            ShaderModel6_3 = D3D_SHADER_MODEL_6_3,
            ShaderModel6_4 = D3D_SHADER_MODEL_6_4,
            ShaderModel6_5 = D3D_SHADER_MODEL_6_5,
            ShaderModel6_6 = D3D_SHADER_MODEL_6_6,
            ShaderModel6_7 = D3D_SHADER_MODEL_6_7
        };

        /// <summary>
        /// Specifies a type of descriptor heap.
        /// </summary>
        public enum class D3D12DescriptorHeapType : UINT
        {
            /// <summary>
            /// The descriptor heap for the combination of constant-buffer, shader-resource,
            /// and unordered-access views.
            /// </summary>
            CbvSrvUav = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV,

            /// <summary>
            /// The descriptor heap for the sampler.
            /// </summary>
            Sampler = D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER,

            /// <summary>
            /// The descriptor heap for the render-target view.
            /// </summary>
            Rtv = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,

            /// <summary>
            /// The descriptor heap for the depth-stencil view.
            /// </summary>
            Dsv = D3D12_DESCRIPTOR_HEAP_TYPE_DSV
        };

        /// <summary>
        /// Specifies flags to be used when creating a command queue.
        /// </summary>
        [Flags]
        public enum class D3D12CommandQueueFlags : UINT
        {
            /// <summary>
            /// Indicates a default command queue.
            /// </summary>
            None = D3D12_COMMAND_QUEUE_FLAG_NONE,

            /// <summary>
            /// Indicates that the GPU timeout should be disabled for this command queue.
            /// </summary>
            DisableGPUTimeout = D3D12_COMMAND_QUEUE_FLAG_DISABLE_GPU_TIMEOUT
        };

        /// <summary>
        /// Defines priority levels for a command queue. You can use one of the members in
        /// D3D12CommandQueueDesc::Priority field.
        /// </summary>
        public enum class D3D12CommandQueuePriority : int
        {
            /// <summary>
            /// Normal priority.
            /// </summary>
            Normal = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,

            /// <summary>
            /// High priority.
            /// </summary>
            High = D3D12_COMMAND_QUEUE_PRIORITY_HIGH,

            /// <summary>
            /// Global realtime priority.
            /// </summary>
            GlobalRealtime = D3D12_COMMAND_QUEUE_PRIORITY_GLOBAL_REALTIME
        };

        /// <summary>
        /// Identifies the type of resource being used.
        /// </summary>
        public enum class D3D12ResourceDimension : UINT
        {
            /// <summary>
            /// Resource is of unknown type.
            /// </summary>
            Unknown = D3D12_RESOURCE_DIMENSION_UNKNOWN,

            /// <summary>
            /// Resource is a buffer.
            /// </summary>
            Buffer = D3D12_RESOURCE_DIMENSION_BUFFER,

            /// <summary>
            /// Resource is a 1D texture.
            /// </summary>
            Texture1D = D3D12_RESOURCE_DIMENSION_TEXTURE1D,

            /// <summary>
            /// Resource is a 2D texture.
            /// </summary>
            Texture2D = D3D12_RESOURCE_DIMENSION_TEXTURE2D,

            /// <summary>
            /// Resource is a 3D texture.
            /// </summary>
            Texture3D = D3D12_RESOURCE_DIMENSION_TEXTURE3D
        };

        /// <summary>
        /// Specifies texture layout options.
        /// </summary>
        public enum class D3D12TextureLayout : UINT
        {
            /// <summary>
            /// Indicates that the layout is unknown, and is likely adapter-dependent.
            /// </summary>
            Unknown = D3D12_TEXTURE_LAYOUT_UNKNOWN,

            /// <summary>
            /// Indicates that data for the texture is stored in row-major order (sometimes called
            /// "pitch-linear order").
            /// </summary>
            RowMajor = D3D12_TEXTURE_LAYOUT_ROW_MAJOR,

            /// <summary>
            /// Indicates that the layout within 64KB tiles and tail mip packing is up to the driver.
            /// </summary>
            Layout64KBUndefinedSwizzle = D3D12_TEXTURE_LAYOUT_64KB_UNDEFINED_SWIZZLE,

            /// <summary>
            /// Indicates that a default texture uses the standardized swizzle pattern.
            /// </summary>
            Layout64KBStandardSwizzle = D3D12_TEXTURE_LAYOUT_64KB_STANDARD_SWIZZLE
        };

        /// <summary>
        /// Specifies options for working with resources.
        /// </summary>
        [Flags]
        public enum class D3D12ResourceFlags : UINT
        {
            /// <summary>
            /// No options are specified.
            /// </summary>
            None = D3D12_RESOURCE_FLAG_NONE,

            /// <summary>
            /// Allows a render target view to be created for the resource, as well as enables the
            /// resource to transition into the state of D3D12ResourceState::RenderTarget. Some adapter
            /// architectures allocate extra memory for textures with this flag to reduce the effective
            /// bandwidth during common rendering. This characteristic may not be beneficial for textures
            /// that are never rendered to, nor is it available for textures compressed with BC formats.
            /// Applications should avoid setting this flag when rendering will never occur.
            /// </summary>
            AllowRenderTarget = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET,

            /// <summary>
            /// Allows a depth stencil view to be created for the resource, as well as enables the
            /// resource to transition into the state of D3D12ResourceState::DepthWrite and/or
            /// D3D12ResourceState::DepthRead. Most adapter architectures allocate extra memory for
            /// textures with this flag to reduce the effective bandwidth and maximize optimizations for
            /// early depth-test. Applications should avoid setting this flag when depth operations will
            /// never occur.
            /// </summary>
            AllowDepthStencil = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL,

            /// <summary>
            /// Allows an unordered access view to be created for the resource, as well as enables the
            /// resource to transition into the state of D3D12ResourceState::UnorderedAccess. Some
            /// adapter architectures must resort to less efficient texture layouts in order to provide
            /// this functionality. If a texture is rarely used for unordered access, it may be worth
            /// having two textures around and copying between them. One texture would have this flag,
            /// while the other wouldn't. Applications should avoid setting this flag when unordered
            /// access operations will never occur.
            /// </summary>
            AllowUnorderedAccess = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS,

            /// <summary>
            /// Disallows a shader resource view to be created for the resource, as well as disables the
            /// resource to transition into the state of D3D12ResourceState::NonPixelShaderResource or
            /// D3D12ResourceStatePixelShaderResource. Some adapter architectures experience
            /// increased bandwidth for depth stencil textures when shader resource views are precluded.
            /// If a texture is rarely used for shader resource, it may be worth having two textures
            /// around and copying between them. One texture would have this flag and the other wouldn't.
            /// Applications should set this flag when depth stencil textures will never be used from
            /// shader resource views.
            /// </summary>
            DenyShaderResource = D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE,

            /// <summary>
            /// Allows the resource to be used for cross-adapter data, as well as the same features
            /// enabled by AllowSimultaneousAccess. Cross adapter resources commonly preclude techniques
            /// that reduce effective texture bandwidth during usage, and some adapter architectures may
            /// require different caching behavior. Applications should avoid setting this flag when the
            /// resource data will never be used with another adapter.
            /// </summary>
            AllowCrossAdapter = D3D12_RESOURCE_FLAG_ALLOW_CROSS_ADAPTER,

            /// <summary>
            /// Allows a resource to be simultaneously accessed by multiple different queues, devices or
            /// processes (for example, allows a resource to be used with ResourceBarrier transitions
            /// performed in more than one command list executing at the same time).
            /// </summary>
            AllowSimultaneousAccess = D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS,

            /// <summary>
            /// This resource may only be used as a decode reference frame. It may only be written to or
            /// read by the video decode operation.
            /// </summary>
            VideoDecodeReferenceOnly = D3D12_RESOURCE_FLAG_VIDEO_DECODE_REFERENCE_ONLY,
            VideoEncodeReferenceOnly = D3D12_RESOURCE_FLAG_VIDEO_ENCODE_REFERENCE_ONLY
        };

        /// <summary>
        /// Specifies the type of heap. When resident, heaps reside in a particular physical memory
        /// pool with certain CPU cache properties.
        /// </summary>
        public enum class D3D12HeapType : UINT
        {
            /// <summary>
            /// This heap type experiences the most bandwidth for the GPU, but cannot provide CPU access.
            /// The GPU can readand write to the memory from this pool, and resource transition
            /// barriers may be changed.
            /// The majority of heapsand resources are expected to be located here, and are
            /// typically populated through resources in upload heaps.
            /// </summary>
            Default = D3D12_HEAP_TYPE_DEFAULT,

            /// <summary>
            /// Specifies a heap used for uploading.
            /// This heap type has CPU access optimized for uploading to the GPU, but does not
            /// experience the maximum amount of bandwidth for the GPU.
            /// This heap type is best for CPU-write-once, GPU-read-once data; but GPU-read-
            /// once is stricter than necessary.
            /// GPU-read-once-or-from-cache is an acceptable use-case for the data; but such
            /// usages are hard to judge due to differing GPU cache designsand sizes.
            /// Resources in this heap must be created with D3D12ResourceState::GenericRead and cannot
            /// be changed away from this.
            /// The CPU address for such heaps is commonly not efficient for CPU reads.
            /// </summary>
            Upload = D3D12_HEAP_TYPE_UPLOAD,

            /// <summary>
            /// Specifies a heap used for reading back.
            /// This heap type has CPU access optimized for reading data back from the GPU, but does
            /// not experience the maximum amount of bandwidth for the GPU.
            /// This heap type is best for GPU-write-once, CPU-readable data.
            /// The CPU cache behavior is write-back, which is conducive for multiple sub-cache-line
            /// CPU reads.
            /// Resources in this heap must be created with D3D12ResourceState::CopyDest, and cannot
            /// be changed away from this.
            /// </summary>
            Readback = D3D12_HEAP_TYPE_READBACK,

            /// <summary>
            /// Specifies a custom heap.
            /// The application may specify the memory pooland CPU cache properties directly, which can
            /// be useful for UMA optimizations, multi-engine, multi-adapter, or other special cases.
            /// To do so, the application is expected to understand the adapter architecture to make
            /// the right choice.
            /// </summary>
            Custom = D3D12_HEAP_TYPE_CUSTOM
        };

        /// <summary>
        /// Specifies the CPU-page properties for the heap.
        /// </summary>
        public enum class D3D12CPUPageProperty : UINT
        {
            /// <summary>
            /// The CPU-page property is unknown.
            /// </summary>
            Unknown = D3D12_CPU_PAGE_PROPERTY_UNKNOWN,

            /// <summary>
            /// The CPU cannot access the heap, therefore no page properties are available.
            /// </summary>
            NotAvailable = D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE,

            /// <summary>
            /// The CPU-page property is write-combined.
            /// </summary>
            WriteCombine = D3D12_CPU_PAGE_PROPERTY_WRITE_COMBINE,

            /// <summary>
            /// The CPU-page property is write-back.
            /// </summary>
            WriteBack = D3D12_CPU_PAGE_PROPERTY_WRITE_BACK
        };

        /// <summary>
        /// Specifies the memory pool for the heap.
        /// </summary>
        public enum class D3D12MemoryPool : UINT
        {
            /// <summary>
            /// The memory pool is unknown.
            /// </summary>
            Unknown = D3D12_MEMORY_POOL_UNKNOWN,

            /// <summary>
            /// The memory pool is L0.
            /// L0 is the physical system memory pool.
            /// When the adapter is discrete / NUMA, this pool has greater bandwidth for the CPU and
            /// less bandwidth for the GPU.
            /// When the adapter is UMA, this pool is the only one which is valid.
            /// </summary>
            L0 = D3D12_MEMORY_POOL_L0,

            /// <summary>
            /// The memory pool is L1.
            /// L1 is typically known as the physical video memory pool.
            /// L1 is only available when the adapter is discrete / NUMA, and has greater bandwidth
            /// for the GPU and cannot even be accessed by the CPU.
            /// When the adapter is UMA, this pool is not available.
            /// </summary>
            L1 = D3D12_MEMORY_POOL_L1
        };

        /// <summary>
        /// Specifies heap options, such as whether the heap can contain textures, and whether
        /// resources are shared across adapters.
        /// </summary>
        [Flags]
        public enum class D3D12HeapFlags : UINT
        {
            /// <summary>
            /// No options are specified.
            /// </summary>
            None = D3D12_HEAP_FLAG_NONE,

            /// <summary>
            /// The heap is shared.
            /// </summary>
            Shared = D3D12_HEAP_FLAG_SHARED,

            /// <summary>
            /// The heap isn't allowed to contain buffers.
            /// </summary>
            DenyBuffers = D3D12_HEAP_FLAG_DENY_BUFFERS,

            /// <summary>
            /// The heap is allowed to contain swap-chain surfaces.
            /// </summary>
            AllowDisplay = D3D12_HEAP_FLAG_ALLOW_DISPLAY,

            /// <summary>
            /// The heap is allowed to share resources across adapters.
            /// </summary>
            SharedCrossAdapter = D3D12_HEAP_FLAG_SHARED_CROSS_ADAPTER,

            /// <summary>
            /// The heap is not allowed to store Render Target (RT) and/or Depth-Stencil (DS) textures.
            /// </summary>
            DenyRtDsTextures = D3D12_HEAP_FLAG_DENY_RT_DS_TEXTURES,

            /// <summary>
            /// The heap is not allowed to contain resources with D3D12ResourceDimension::Texture1D,
            /// D3D12ResourceDimension::Texture2D, or D3D12ResourceDimension::Texture3D unless either
            /// D3D12ResourceFlags::AllowRenderTarget or D3D12ResourceFlags::AllowDepthStencil are
            /// present.
            /// </summary>
            DenyNonRtDsTextures = D3D12_HEAP_FLAG_DENY_NON_RT_DS_TEXTURES,

            /// <summary>
            /// Unsupported. Do not use.
            /// </summary>
            HardwareProtected = D3D12_HEAP_FLAG_HARDWARE_PROTECTED,

            /// <summary>
            /// The heap supports MEM_WRITE_WATCH functionality, which causes the system to track
            /// the pages that are written to in the committed memory region. This flag can't be
            /// combined with the D3D12HeapType::Default or D3D12CPUPageProperty::Unknown flags.
            /// Applications are discouraged from using this flag themselves because it prevents
            /// tools from using this functionality.
            /// </summary>
            AllowWriteWatch = D3D12_HEAP_FLAG_ALLOW_WRITE_WATCH,

            /// <summary>
            /// Ensures that atomic operations will be atomic on this heap's memory, according
            /// to components able to see the memory.
            /// Creating a heap with this flag will fail under either of these conditions.
            /// <para>- The heap type is D3D12_HEAP_TYPE_DEFAULT, and the heap can be visible on
            /// multiple nodes, but the device does not support D3D12CrossNodeSharingTier::Tier3.</para>
            /// <para>- The heap is CPU-visible, but the heap type is not D3D12HeapType::Custom.</para>
            /// Note that heaps with this flag might be a limited resource on some systems.
            /// </summary>
            AllowShaderAtomics = D3D12_HEAP_FLAG_ALLOW_SHADER_ATOMICS,

            /// <summary>
            /// The heap is created in a non-resident state and must be made resident
            /// using D3D12Device::MakeResident or D3D12Device3::EnqueueMakeResident.
            /// By default, the final step of heap creation is to make the heap resident, so this
            /// flag skips this stepand allows the application to decide when to do so.
            /// </summary>
            CreateNotResident = D3D12_HEAP_FLAG_CREATE_NOT_RESIDENT,

            /// <summary>
            /// Allows the OS to not zero the heap created. By default, committed resources and heaps
            /// are almost always zeroed upon creation. This flag allows this to be elided in some
            /// scenarios. However, it doesn't guarantee it. For example, memory coming from other
            /// processes still needs to be zeroed for data protection and process isolation. This can
            /// lower the overhead of creating the heap.
            /// </summary>
            CreateNotZeroed = D3D12_HEAP_FLAG_CREATE_NOT_ZEROED,

            /// <summary>
            /// The heap is allowed to store all types of buffers and/or textures.
            /// </summary>
            AllowAllBuffersAndTextures = D3D12_HEAP_FLAG_ALLOW_ALL_BUFFERS_AND_TEXTURES,

            /// <summary>
            /// The heap is only allowed to store buffers.
            /// </summary>
            AllowOnlyBuffers = D3D12_HEAP_FLAG_ALLOW_ONLY_BUFFERS,

            /// <summary>
            /// The heap is only allowed to store non-RT, non-DS textures.
            /// </summary>
            AllowOnlyNonRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES,

            /// <summary>
            /// The heap is only allowed to store RT and/or DS textures.
            /// </summary>
            AllowOnlyRtDsTextures = D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES
        };

        /// <summary>
        /// Specifies a range of tile mappings.
        /// </summary>
        public enum class D3D12TileRangeFlags : UINT
        {
            /// <summary>
            /// No tile-mapping flags are specified.
            /// </summary>
            None = D3D12_TILE_RANGE_FLAG_NONE,

            /// <summary>
            /// The tile range is NULL.
            /// </summary>
            Null = D3D12_TILE_RANGE_FLAG_NULL,

            /// <summary>
            /// Skip the tile range.
            /// </summary>
            Skip = D3D12_TILE_RANGE_FLAG_SKIP,

            /// <summary>
            /// Reuse a single tile in the tile range.
            /// </summary>
            ReuseSingleTile = D3D12_TILE_RANGE_FLAG_REUSE_SINGLE_TILE
        };

        /// <summary>
        /// Specifies how to perform a tile-mapping operation.
        /// </summary>
        [Flags]
        public enum class D3D12TileMappingFlags : UINT
        {
            /// <summary>
            /// No tile-mapping flags are specified.
            /// </summary>
            None = D3D12_TILE_MAPPING_FLAG_NONE,

            /// <summary>
            /// Unsupported, do not use.
            /// </summary>
            NoHazard = D3D12_TILE_MAPPING_FLAG_NO_HAZARD
        };

        /// <summary>
        /// Specifies blend factors, which modulate values for the pixel shader and render target.
        /// </summary>
        public enum class D3D12Blend : UINT
        {
            /// <summary>
            /// The blend factor is (0, 0, 0, 0). No pre-blend operation.
            /// </summary>
            Zero = D3D12_BLEND_ZERO,

            /// <summary>
            /// The blend factor is (1, 1, 1, 1). No pre-blend operation.
            /// </summary>
            One = D3D12_BLEND_ONE,

            /// <summary>
            /// The blend factor is (Rₛ, Gₛ, Bₛ, Aₛ), that is color data (RGB) from a pixel shader.
            /// No pre-blend operation.
            /// </summary>
            SrcColor = D3D12_BLEND_SRC_COLOR,

            /// <summary>
            /// The blend factor is (1 - Rₛ, 1 - Gₛ, 1 - Bₛ, 1 - Aₛ), that is color data (RGB) from a
            /// pixel shader. The pre-blend operation inverts the data, generating 1 - RGB.
            /// </summary>
            InvSrcColor = D3D12_BLEND_INV_SRC_COLOR,

            /// <summary>
            /// The blend factor is (Aₛ, Aₛ, Aₛ, Aₛ), that is alpha data (A) from a pixel shader. No
            /// pre-blend operation.
            /// </summary>
            SrcAlpha = D3D12_BLEND_SRC_ALPHA,

            /// <summary>
            /// The blend factor is (1 - Aₛ, 1 - Aₛ, 1 - Aₛ, 1 - Aₛ), that is alpha data (A) from a
            /// pixel shader. The pre-blend operation inverts the data, generating 1 - A.
            /// </summary>
            InvSrcAlpha = D3D12_BLEND_INV_SRC_ALPHA,

            /// <summary>
            /// The blend factor is (Ad Ad Ad Ad), that is alpha data from a render target.
            /// No pre-blend operation.
            /// </summary>
            DestAlpha = D3D12_BLEND_DEST_ALPHA,

            /// <summary>
            /// The blend factor is (1 - Ad 1 - Ad 1 - Ad 1 - Ad), that is alpha data from a
            /// render target. The pre-blend operation inverts the data, generating 1 - A.
            /// </summary>
            InvDestAlpha = D3D12_BLEND_INV_DEST_ALPHA,

            /// <summary>
            /// The blend factor is (Rd, Gd, Bd, Ad), that is color data from a render target.
            /// No pre-blend operation.
            /// </summary>
            DestColor = D3D12_BLEND_DEST_COLOR,

            /// <summary>
            /// The blend factor is (1 - Rd, 1 - Gd, 1 - Bd, 1 - Ad), that is color data from a
            /// render target. The pre-blend operation inverts the data, generating 1 - RGB.
            /// </summary>
            InvDestColor = D3D12_BLEND_INV_DEST_COLOR,

            /// <summary>
            /// The blend factor is (f, f, f, 1); where f = min(Aₛ, 1 - Ad).The pre-blend operation
            /// clamps the data to 1 or less.
            /// </summary>
            SrcAlphaSat = D3D12_BLEND_SRC_ALPHA_SAT,

            /// <summary>
            /// The blend factor is the blend factor set with D3D12GraphicsCommandList::OMSetBlendFactor.
            /// No pre-blend operation.
            /// </summary>
            BlendFactor = D3D12_BLEND_BLEND_FACTOR,

            /// <summary>
            /// The blend factor is the blend factor set with D3D12GraphicsCommandList::OMSetBlendFactor.
            /// The pre-blend operation inverts the blend factor, generating 1 - blend_factor.
            /// </summary>
            InvBlendFactor = D3D12_BLEND_INV_BLEND_FACTOR,

            /// <summary>
            /// The blend factor is data sources both as color data output by a pixel shader.
            /// There is no pre-blend operation. This blend factor supports dual-source color blending.
            /// </summary>
            Src1Color = D3D12_BLEND_SRC1_COLOR,

            /// <summary>
            /// The blend factor is data sources both as color data output by a pixel shader.
            /// The pre-blend operation inverts the data, generating 1 - RGB. This blend factor
            /// supports dual-source color blending.
            /// </summary>
            InvSrc1Color = D3D12_BLEND_INV_SRC1_COLOR,

            /// <summary>
            /// The blend factor is data sources as alpha data output by a pixel shader. There is no
            /// pre-blend operation. This blend factor supports dual-source color blending.
            /// </summary>
            Src1Alpha = D3D12_BLEND_SRC1_ALPHA,

            /// <summary>
            /// The blend factor is data sources as alpha data output by a pixel shader. The
            /// pre-blend operation inverts the data, generating 1 - A. This blend factor supports
            /// dual-source color blending.
            /// </summary>
            InvSrc1Alpha = D3D12_BLEND_INV_SRC1_ALPHA
        };

        /// <summary>
        /// Specifies RGB or alpha blending operations.
        /// </summary>
        public enum class D3D12BlendOp : UINT
        {
            /// <summary>
            /// Add source 1 and source 2.
            /// </summary>
            Add = D3D12_BLEND_OP_ADD,

            /// <summary>
            /// Subtract source 1 from source 2.
            /// </summary>
            Subtract = D3D12_BLEND_OP_SUBTRACT,

            /// <summary>
            /// Subtract source 2 from source 1.
            /// </summary>
            RevSubtract = D3D12_BLEND_OP_REV_SUBTRACT,

            /// <summary>
            /// Find the minimum of source 1 and source 2.
            /// </summary>
            Min = D3D12_BLEND_OP_MIN,

            /// <summary>
            /// Find the maximum of source 1 and source 2.
            /// </summary>
            Max = D3D12_BLEND_OP_MAX
        };

        /// <summary>
        /// Defines constants that specify logical operations to configure for a render target.
        /// </summary>
        public enum class D3D12LogicOp : UINT
        {
            /// <summary>
            /// Clears the render target (0).
            /// </summary>
            Clear = D3D12_LOGIC_OP_CLEAR,

            /// <summary>
            /// Sets the render target ( 1).
            /// </summary>
            Set = D3D12_LOGIC_OP_SET,

            /// <summary>
            /// Copys the render target (s source from Pixel Shader output).
            /// </summary>
            Copy = D3D12_LOGIC_OP_COPY,

            /// <summary>
            /// Performs an inverted-copy of the render target (~s).
            /// </summary>
            CopyInverted = D3D12_LOGIC_OP_COPY_INVERTED,

            /// <summary>
            /// No operation is performed on the render target (d destination in the Render Target View).
            /// </summary>
            Noop = D3D12_LOGIC_OP_NOOP,

            /// <summary>
            /// Inverts the render target (~d).
            /// </summary>
            Invert = D3D12_LOGIC_OP_INVERT,

            /// <summary>
            /// Performs a logical AND operation on the render target (s & d).
            /// </summary>
            And = D3D12_LOGIC_OP_AND,

            /// <summary>
            /// Performs a logical NAND operation on the render target (~(s & d)).
            /// </summary>
            Nand = D3D12_LOGIC_OP_NAND,

            /// <summary>
            /// Performs a logical OR operation on the render target (s | d).
            /// </summary>
            Or = D3D12_LOGIC_OP_OR,

            /// <summary>
            /// Performs a logical NOR operation on the render target (~(s | d)).
            /// </summary>
            Nor = D3D12_LOGIC_OP_NOR,

            /// <summary>
            /// Performs a logical XOR operation on the render target (s ^ d).
            /// </summary>
            Xor = D3D12_LOGIC_OP_XOR,

            /// <summary>
            /// Performs a logical equal operation on the render target (~(s ^ d)).
            /// </summary>
            Equiv = D3D12_LOGIC_OP_EQUIV,

            /// <summary>
            /// Performs a logical AND and reverse operation on the render target (s & ~d).
            /// </summary>
            AndReverse = D3D12_LOGIC_OP_AND_REVERSE,

            /// <summary>
            /// Performs a logical AND and invert operation on the render target (~s & d).
            /// </summary>
            AndInverted = D3D12_LOGIC_OP_AND_INVERTED,

            /// <summary>
            /// Performs a logical OR and reverse operation on the render target (s | ~d).
            /// </summary>
            OrReverse = D3D12_LOGIC_OP_OR_REVERSE,

            /// <summary>
            /// Performs a logical OR and invert operation on the render target (~s | d).
            /// </summary>
            OrInverted = D3D12_LOGIC_OP_OR_INVERTED
        };

        /// <summary>
        /// Identifies which components of each pixel of a render target are writable during blending.
        /// </summary>
        [Flags]
        public enum class D3D12ColorWriteEnable : UINT8
        {
            None = 0,

            /// <summary>
            /// Allow data to be stored in the red component.
            /// </summary>
            Red = D3D12_COLOR_WRITE_ENABLE_RED,

            /// <summary>
            /// Allow data to be stored in the green component.
            /// </summary>
            Green = D3D12_COLOR_WRITE_ENABLE_GREEN,

            /// <summary>
            /// Allow data to be stored in the blue component.
            /// </summary>
            Blue = D3D12_COLOR_WRITE_ENABLE_BLUE,

            /// <summary>
            /// Allow data to be stored in the alpha component.
            /// </summary>
            Alpha = D3D12_COLOR_WRITE_ENABLE_ALPHA,

            /// <summary>
            /// Allow data to be stored in all components.
            /// </summary>
            All = D3D12_COLOR_WRITE_ENABLE_ALL
        };

        /// <summary>
        /// Specifies the fill mode to use when rendering triangles.
        /// </summary>
        public enum class D3D12FillMode : UINT
        {
            /// <summary>
            /// Draw lines connecting the vertices. Adjacent vertices are not drawn.
            /// </summary>
            Wireframe = D3D12_FILL_MODE_WIREFRAME,

            /// <summary>
            /// Fill the triangles formed by the vertices. Adjacent vertices are not drawn.
            /// </summary>
            Solid = D3D12_FILL_MODE_SOLID
        };

        /// <summary>
        /// Specifies triangles facing a particular direction are not drawn.
        /// </summary>
        public enum class D3D12CullMode : UINT
        {
            /// <summary>
            /// Always draw all triangles.
            /// </summary>
            None = D3D12_CULL_MODE_NONE,

            /// <summary>
            /// Do not draw triangles that are front-facing.
            /// </summary>
            Front = D3D12_CULL_MODE_FRONT,

            /// <summary>
            /// Do not draw triangles that are back-facing.
            /// </summary>
            Back = D3D12_CULL_MODE_BACK
        };

        /// <summary>
        /// Identifies whether conservative rasterization is on or off.
        /// </summary>
        public enum class D3D12ConservativeRasterizationMode : UINT
        {
            /// <summary>
            /// Conservative rasterization is off.
            /// </summary>
            Off = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF,

            /// <summary>
            /// Conservative rasterization is on.
            /// </summary>
            On = D3D12_CONSERVATIVE_RASTERIZATION_MODE_ON
        };

        /// <summary>
        /// Identifies the portion of a depth-stencil buffer for writing depth data.
        /// </summary>
        public enum class D3D12DepthWriteMask : UINT
        {
            /// <summary>
            /// Turn off writes to the depth-stencil buffer.
            /// </summary>
            Zero = D3D12_DEPTH_WRITE_MASK_ZERO,

            /// <summary>
            /// Turn on writes to the depth-stencil buffer.
            /// </summary>
            All = D3D12_DEPTH_WRITE_MASK_ALL
        };

        /// <summary>
        /// Specifies comparison options.
        /// </summary>
        public enum class D3D12ComparisonFunc : UINT
        {
            /// <summary>
            /// Never pass the comparison.
            /// </summary>
            Never = D3D12_COMPARISON_FUNC_NEVER,

            /// <summary>
            /// If the source data is less than the destination data, the comparison passes.
            /// </summary>
            Less = D3D12_COMPARISON_FUNC_LESS,

            /// <summary>
            /// If the source data is equal to the destination data, the comparison passes.
            /// </summary>
            Equal = D3D12_COMPARISON_FUNC_EQUAL,

            /// <summary>
            /// If the source data is less than or equal to the destination data, the comparison passes.
            /// </summary>
            LessEqual = D3D12_COMPARISON_FUNC_LESS_EQUAL,

            /// <summary>
            /// If the source data is greater than the destination data, the comparison passes.
            /// </summary>
            Greater = D3D12_COMPARISON_FUNC_GREATER,

            /// <summary>
            /// If the source data is not equal to the destination data, the comparison passes.
            /// </summary>
            NotEqual = D3D12_COMPARISON_FUNC_NOT_EQUAL,

            /// <summary>
            /// If the source data is greater than or equal to the destination data, the
            /// comparison passes.
            /// </summary>
            GreaterEqual = D3D12_COMPARISON_FUNC_GREATER_EQUAL,

            /// <summary>
            /// Always pass the comparison.
            /// </summary>
            Always = D3D12_COMPARISON_FUNC_ALWAYS
        };

        /// <summary>
        /// Identifies the stencil operations that can be performed during depth-stencil testing.
        /// </summary>
        public enum class D3D12StencilOp : UINT
        {
            /// <summary>
            /// Keep the existing stencil data.
            /// </summary>
            Keep = D3D12_STENCIL_OP_KEEP,

            /// <summary>
            /// Set the stencil data to 0.
            /// </summary>
            Zero = D3D12_STENCIL_OP_ZERO,

            /// <summary>
            /// Set the stencil data to the reference value set by calling
            /// D3D12GraphicsCommandList::OMSetStencilRef.
            /// </summary>
            Replace = D3D12_STENCIL_OP_REPLACE,

            /// <summary>
            /// Increment the stencil value by 1, and clamp the result.
            /// </summary>
            IncrSat = D3D12_STENCIL_OP_INCR_SAT,

            /// <summary>
            /// Decrement the stencil value by 1, and clamp the result.
            /// </summary>
            DecrSat = D3D12_STENCIL_OP_DECR_SAT,

            /// <summary>
            /// Invert the stencil data.
            /// </summary>
            Invert = D3D12_STENCIL_OP_INVERT,

            /// <summary>
            /// Increment the stencil value by 1, and wrap the result if necessary.
            /// </summary>
            Incr = D3D12_STENCIL_OP_INCR,

            /// <summary>
            /// Decrement the stencil value by 1, and wrap the result if necessary.
            /// </summary>
            Decr = D3D12_STENCIL_OP_DECR
        };

        /// <summary>
        /// Identifies the type of data contained in an input slot.
        /// </summary>
        public enum class D3D12InputClassification : UINT
        {
            /// <summary>
            /// Input data is per-vertex data.
            /// </summary>
            PerVertexData = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,

            /// <summary>
            /// Input data is per-instance data.
            /// </summary>
            PerInstanceData = D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA
        };

        /// <summary>
        /// When using triangle strip primitive topology, vertex positions are interpreted as vertices
        /// of a continuous triangle “strip”. There is a special index value that represents the desire
        /// to have a discontinuity in the strip, the cut index value. This enum lists the supported
        /// cut values.
        /// </summary>
        public enum class D3D12IndexBufferStripCutValue : UINT
        {
            /// <summary>
            /// Indicates that there is no cut value.
            /// </summary>
            Disabled = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED,

            /// <summary>
            /// Indicates that 0xFFFF should be used as the cut value.
            /// </summary>
            Value0xFFFF = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFF,

            /// <summary>
            /// Indicates that 0xFFFFFFFF should be used as the cut value.
            /// </summary>
            Value0xFFFFFFFF = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_0xFFFFFFFF
        };

        /// <summary>
        /// Specifies how the pipeline interprets geometry or hull shader input primitives.
        /// </summary>
        public enum class D3D12PrimitiveTopologyType : UINT
        {
            /// <summary>
            /// The shader has not been initialized with an input primitive type.
            /// </summary>
            Undefined = D3D12_PRIMITIVE_TOPOLOGY_TYPE_UNDEFINED,

            /// <summary>
            /// Interpret the input primitive as a point.
            /// </summary>
            Point = D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT,

            /// <summary>
            /// Interpret the input primitive as a line.
            /// </summary>
            Line = D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE,

            /// <summary>
            /// Interpret the input primitive as a triangle.
            /// </summary>
            Triangle = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE,

            /// <summary>
            /// Interpret the input primitive as a control point patch.
            /// </summary>
            Patch = D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH
        };

        /// <summary>
        /// Flags to control pipeline state.
        /// </summary>
        [Flags]
        public enum class D3D12PipelineStateFlags : UINT
        {
            /// <summary>
            /// Indicates no flags.
            /// </summary>
            None = D3D12_PIPELINE_STATE_FLAG_NONE,

            /// <summary>
            /// Indicates that the pipeline state should be compiled with additional information to
            /// assist debugging.
            /// This can only be set on WARP devices.
            /// </summary>
            ToolDebug = D3D12_PIPELINE_STATE_FLAG_TOOL_DEBUG
        };

        /// <summary>
        /// Specifies what type of texture copy is to take place.
        /// </summary>
        public enum class D3D12TextureCopyType : UINT
        {
            /// <summary>
            /// Indicates a subresource, identified by an index, is to be copied.
            /// </summary>
            SubresourceIndex = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX,

            /// <summary>
            /// Indicates a place footprint, identified by a D3D12PlacedSubresourceFootprint
            /// structure, is to be copied.
            /// </summary>
            PlacedFootprint = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT
        };

        /// <summary>
        /// Specifies how to copy a tile.
        /// </summary>
        [Flags]
        public enum class D3D12TileCopyFlags : UINT
        {
            /// <summary>
            /// No tile-copy flags are specified.
            /// </summary>
            None = D3D12_TILE_COPY_FLAG_NONE,

            /// <summary>
            /// Indicates that the GPU isn't currently referencing any of the portions of destination
            /// memory being written.
            /// </summary>
            NoHazard = D3D12_TILE_COPY_FLAG_NO_HAZARD,

            /// <summary>
            /// Indicates that the D3D12GraphicsCommandList::CopyTiles operation involves copying a
            /// linear buffer to a swizzled tiled resource. This means to copy tile data from the
            /// specified buffer location, reading tiles sequentially, to the specified tile region
            /// (in x, y, z order if the region is a box), swizzling to optimal hardware memory layout
            /// as needed. In this D3D12GraphicsCommandList::CopyTiles call, you specify the source data
            /// with the buffer parameter and the destination with the tiledResource parameter.
            /// </summary>
            LinearBufferToSwizzledTiledResource = D3D12_TILE_COPY_FLAG_LINEAR_BUFFER_TO_SWIZZLED_TILED_RESOURCE,

            /// <summary>
            /// Indicates that the D3D12GraphicsCommandList::CopyTiles operation involves copying a
            /// swizzled tiled resource to a linear buffer. This means to copy tile data from the tile
            /// region, reading tiles sequentially (in x,y,z order if the region is a box),
            /// to the specified buffer location, deswizzling to linear memory layout as needed.
            /// In this D3D12GraphicsCommandList::CopyTiles call, you specify the source data with
            /// the tiledResource parameterand the destination with the buffer parameter.
            /// </summary>
            SwizzledTiledResourceToLinearBuffer = D3D12_TILE_COPY_FLAG_SWIZZLED_TILED_RESOURCE_TO_LINEAR_BUFFER
        };

        /// <summary>
        /// Specifies a type of resource barrier (transition in resource use) description.
        /// </summary>
        public enum class D3D12ResourceBarrierType : UINT
        {
            /// <summary>
            /// A transition barrier that indicates a transition of a set of subresources between
            /// different usages. The caller must specify the before and after usages of the subresources.
            /// </summary>
            Transition = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,

            /// <summary>
            /// An aliasing barrier that indicates a transition between usages of 2 different resources
            /// that have mappings into the same tile pool. The caller can specify both the before and
            /// the after resource. Note that one or both resources can be NULL, which indicates that
            /// any tiled resource could cause aliasing.
            /// </summary>
            Aliasing = D3D12_RESOURCE_BARRIER_TYPE_ALIASING,

            /// <summary>
            /// An unordered access view (UAV) barrier that indicates all UAV accesses (reads or writes)
            /// to a particular resource must complete before any future UAV accesses (read or write)
            /// can begin.
            /// </summary>
            Uav = D3D12_RESOURCE_BARRIER_TYPE_UAV
        };

        /// <summary>
        /// Flags for setting split resource barriers.
        /// </summary>
        [Flags]
        public enum class D3D12ResourceBarrierFlags : UINT
        {
            /// <summary>
            /// No flags.
            /// </summary>
            None = D3D12_RESOURCE_BARRIER_FLAG_NONE,

            /// <summary>
            /// This starts a barrier transition in a new state, putting a resource in a temporary
            /// no-access condition.
            /// </summary>
            BeginOnly = D3D12_RESOURCE_BARRIER_FLAG_BEGIN_ONLY,

            /// <summary>
            /// This barrier completes a transition, setting a new state and restoring active access to
            /// a resource.
            /// </summary>
            EndOnly = D3D12_RESOURCE_BARRIER_FLAG_END_ONLY
        };

        /// <summary>
        /// Defines constants that specify the state of a resource regarding how the resource is
        /// being used.
        /// </summary>
        [Flags]
        public enum class D3D12ResourceStates : UINT
        {
            /// <summary>
            /// Your application should transition to this state only for accessing a resource across
            /// different graphics engine types.
            /// Specifically, a resource must be in the COMMON state before being used on a COPY queu
            /// (when previous used on DIRECT / COMPUTE), and before being used on DIRECT / COMPUTE
            /// (when previously used on COPY).This restriction does not exist when accessing data
            /// between DIRECT and COMPUTE queues.
            /// Additionally, textures must be in the COMMON state for CPU access to be legal,
            /// assuming the texture was created in a CPU-visible heap in the first place.
            /// </summary>
            Common = D3D12_RESOURCE_STATE_COMMON,

            /// <summary>
            /// A subresource must be in this state when it is accessed by the GPU as a vertex buffer
            /// or constant buffer. This is a read-only state.
            /// </summary>
            VertexAndConstantBuffer = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER,

            /// <summary>
            /// A subresource must be in this state when it is accessed by the 3D pipeline as an
            /// index buffer. This is a read-only state.
            /// </summary>
            IndexBuffer = D3D12_RESOURCE_STATE_INDEX_BUFFER,

            /// <summary>
            /// The resource is used as a render target. A subresource must be in this state when it is
            /// rendered to or when it is cleared with D3D12GraphicsCommandList::ClearRenderTargetView.
            /// This is a write-only state. To read from a render target as a shader resource the
            /// resource must be in either D3D12ResourceStates::NonPixelShaderResource or
            /// D3D12ResourceStates::PixelShaderResource.
            /// </summary>
            RenderTarget = D3D12_RESOURCE_STATE_RENDER_TARGET,

            /// <summary>
            /// The resource is used for unordered access. A subresource must be in this state when it is
            /// accessed by the GPU via an unordered access view. A subresource must also be in this
            /// state when it is cleared with D3D12GraphicsCommandList::ClearUnorderedAccessViewInt or
            /// D3D12GraphicsCommandList::ClearUnorderedAccessViewFloat. This is a read/write state.
            /// </summary>
            UnorderedAccess = D3D12_RESOURCE_STATE_UNORDERED_ACCESS,

            /// <summary>
            /// DepthWrite is a state that is mutually exclusive with other states.
            /// You should use it for ID3D12GraphicsCommandList::ClearDepthStencilView when the flags
            /// indicate a given subresource should be cleared (otherwise the subresource state doesn't
            /// matter), or when using it in a writable depth stencil view when the PSO has depth write
            /// enabled.
            /// </summary>
            DepthWrite = D3D12_RESOURCE_STATE_DEPTH_WRITE,

            /// <summary>
            /// DepthRead is a state which can be combined with other states. It should be used when
            /// the subresource is in a read-only depth stencil view, or when the DepthEnable parameter
            /// of D3D12DepthStencilDesc is false. It can be combined with other read states (for
            /// example, PixelShaderResource), such that the resource can be used for the depth or
            /// stencil test, and accessed by a shader within the same draw call. Using it when depth
            /// will be written by a draw call or clear command is invalid.
            /// </summary>
            DepthRead = D3D12_RESOURCE_STATE_DEPTH_READ,

            /// <summary>
            /// The resource is used with a shader other than the pixel shader. A subresource must be
            /// in this state before being read by any stage (except for the pixel shader stage) via a
            /// shader resource view. You can still use the resource in a pixel shader with this flag as
            /// long as it also has the flag PixelShaderResource set. This is a read-only state.
            /// </summary>
            NonPixelShaderResource = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE,

            /// <summary>
            /// The resource is used with a pixel shader. A subresource must be in this state before
            /// being read by the pixel shader via a shader resource view. This is a read-only state.
            /// </summary>
            PixelShaderResource = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE,

            /// <summary>
            /// The resource is used with stream output. A subresource must be in this state when it
            /// is accessed by the 3D pipeline as a stream-out target. This is a write-only state.
            /// </summary>
            StreamOut = D3D12_RESOURCE_STATE_STREAM_OUT,

            /// <summary>
            /// The resource is used as an indirect argument.
            /// Subresources must be in this state when they are used as the argument buffer passed to
            /// the indirect drawing method D3D12GraphicsCommandList::ExecuteIndirect.
            /// This is a read-only state.
            /// </summary>
            IndirectArgument = D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT,

            /// <summary>
            /// The resource is used as the destination in a copy operation.
            /// Subresources must be in this state when they are used as the destination of copy
            /// operation, or a blt operation.
            /// This is a write-only state.
            /// </summary>
            CopyDest = D3D12_RESOURCE_STATE_COPY_DEST,

            /// <summary>
            /// The resource is used as the source in a copy operation.
            /// Subresources must be in this state when they are used as the source of copy operation,
            /// or a blt operation.
            /// This is a read-only state.
            /// </summary>
            CopySource = D3D12_RESOURCE_STATE_COPY_SOURCE,

            /// <summary>
            /// The resource is used as the destination in a resolve operation.
            /// </summary>
            ResolveDest = D3D12_RESOURCE_STATE_RESOLVE_DEST,

            /// <summary>
            /// The resource is used as the source in a resolve operation.
            /// </summary>
            ResolveSource = D3D12_RESOURCE_STATE_RESOLVE_SOURCE,

            /// <summary>
            /// When a buffer is created with this as its initial state, it indicates that the resource
            /// is a raytracing acceleration structure, for use in
            /// D3D12GraphicsCommandList4::BuildRaytracingAccelerationStructure,
            /// D3D12GraphicsCommandList4::CopyRaytracingAccelerationStructure, or
            /// D3D12Device::CreateShaderResourceView for the
            /// D3D12SrvDimensionRaytracingAccelerationStreucture dimension.
            /// </summary>
            RaytracingAccelerationStructure = D3D12_RESOURCE_STATE_RAYTRACING_ACCELERATION_STRUCTURE,

            /// <summary>
            /// Starting with Windows 10, version 1903 (10.0; Build 18362), indicates that the resource
            /// is a screen-space shading-rate image for variable-rate shading (VRS).
            /// </summary>
            ShadingRateSource = D3D12_RESOURCE_STATE_SHADING_RATE_SOURCE,

            /// <summary>
            /// D3D12_RESOURCE_STATE_GENERIC_READ is a logically OR'd combination of other read-state
            /// bits. This is the required starting state for an upload heap. Your application should
            /// generally avoid transitioning to GenericRead when possible, since that can result in
            /// premature cache flushes, or resource layout changes (for example, compress/decompress),
            /// causing unnecessary pipeline stalls. You should instead transition resources only to the
            /// actually-used states.
            /// </summary>
            GenericRead = D3D12_RESOURCE_STATE_GENERIC_READ,
            AllShaderResource = D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE,

            /// <summary>
            /// Synonymous with D3D12_RESOURCE_STATE_COMMON.
            /// </summary>
            Present = D3D12_RESOURCE_STATE_PRESENT,

            /// <summary>
            /// The resource is used for Predication.
            /// </summary>
            Predication = D3D12_RESOURCE_STATE_PREDICATION,

            /// <summary>
            /// The resource is used as a source in a decode operation. Examples include reading the
            /// compressed bitstream and reading from decode references.
            /// </summary>
            VideoDecodeRead = D3D12_RESOURCE_STATE_VIDEO_DECODE_READ,

            /// <summary>
            /// The resource is used as a destination in the decode operation. This state is used
            /// for decode output and histograms.
            /// </summary>
            VideoDecodeWrite = D3D12_RESOURCE_STATE_VIDEO_DECODE_WRITE,

            /// <summary>
            /// The resource is used to read video data during video processing; that is, the resource
            /// is used as the source in a processing operation such as video encoding (compression).
            /// </summary>
            VideoProcessRead = D3D12_RESOURCE_STATE_VIDEO_PROCESS_READ,

            /// <summary>
            /// The resource is used to write video data during video processing; that is, the resource
            /// is used as the destination in a processing operation such as video encoding (compression).
            /// </summary>
            VideoProcessWrite = D3D12_RESOURCE_STATE_VIDEO_PROCESS_WRITE,

            /// <summary>
            /// The resource is used as the source in an encode operation. This state is used for
            /// the input and reference of motion estimation.
            /// </summary>
            VideoEncodeRead = D3D12_RESOURCE_STATE_VIDEO_ENCODE_READ,

            /// <summary>
            /// This resource is used as the destination in an encode operation. This state is used
            /// for the destination texture of a resolve motion vector heap operation.
            /// </summary>
            VideoEncodeWrite = D3D12_RESOURCE_STATE_VIDEO_ENCODE_WRITE
        };

        /// <summary>
        /// Specifies options for a heap.
        /// </summary>
        [Flags]
        public enum class D3D12DescriptorHeapFlags : UINT
        {
            /// <summary>
            /// Indicates default usage of a heap.
            /// </summary>
            None = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,

            /// <summary>
            /// The flag ShaderVisible can optionally be set on a descriptor heap to indicate it is be
            /// bound on a command list for reference by shaders. Descriptor heaps created without this
            /// flag allow applications the option to stage descriptors in CPU memory before copying them
            /// to a shader visible descriptor heap, as a convenience. But it is also fine for
            /// applications to directly create descriptors into shader visible descriptor heaps with no
            /// requirement to stage anything on the CPU.
            /// Descriptor heaps bound via D3D12GraphicsCommandList::SetDescriptorHeaps must have the
            /// ShaderVisible flag set, else the debug layer will produce an error.
            /// Descriptor heaps with the ShaderVisible flag can't be used as the source heaps in calls
            /// to D3D12Device::CopyDescriptors or D3D12Device::CopyDescriptorsSimple, because they
            /// could be resident in WRITE_COMBINE memory or GPU-local memory, which is very inefficient
            /// to read from.
            /// This flag only applies to CBV / SRV / UAV descriptor heaps, and sampler descriptor
            /// heaps.It does not apply to other descriptor heap types since shaders do not directly
            /// reference the other types.Attempting to create an RTV / DSV heap with
            /// ShaderVisible results in a debug layer error.
            /// </summary>
            ShaderVisible = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE
        };

        /// <summary>
        /// Specifies what to clear from the depth stencil view.
        /// </summary>
        [Flags]
        public enum class D3D12ClearFlags : UINT
        {
            None = 0,

            /// <summary>
            /// Indicates the depth buffer should be cleared.
            /// </summary>
            Depth = D3D12_CLEAR_FLAG_DEPTH,

            /// <summary>
            /// Indicates the stencil buffer should be cleared.
            /// </summary>
            Stencil = D3D12_CLEAR_FLAG_STENCIL
        };

        /// <summary>
        /// Specifies the type of query.
        /// </summary>
        public enum class D3D12QueryType : UINT
        {
            /// <summary>
            /// Indicates the query is for depth/stencil occlusion counts.
            /// </summary>
            Occlusion = D3D12_QUERY_TYPE_OCCLUSION,

            /// <summary>
            /// Indicates the query is for a binary depth/stencil occlusion statistics.
            /// </summary>
            BinaryOcclusion = D3D12_QUERY_TYPE_BINARY_OCCLUSION,

            /// <summary>
            /// Indicates the query is for high definition GPU and CPU timestamps.
            /// </summary>
            Timestamp = D3D12_QUERY_TYPE_TIMESTAMP,

            /// <summary>
            /// Indicates the query type is for graphics pipeline statistics.
            /// </summary>
            PipelineStatistics = D3D12_QUERY_TYPE_PIPELINE_STATISTICS,

            /// <summary>
            /// Stream 0 output statistics. In Direct3D 12 there is no single stream output (SO)
            /// overflow query for all the output streams. Apps need to issue multiple single-stream
            /// queries, and then correlate the results. Stream output is the ability of the GPU to write
            /// vertices to a buffer. The stream output counters monitor progress.
            /// </summary>
            SOStatisticsStream0 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM0,

            /// <summary>
            /// Stream 1 output statistics.
            /// </summary>
            SOStatisticsStream1 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM1,

            /// <summary>
            /// Stream 2 output statistics.
            /// </summary>
            SOStatisticsStream2 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM2,

            /// <summary>
            /// Stream 3 output statistics.
            /// </summary>
            SOStatisticsStream3 = D3D12_QUERY_TYPE_SO_STATISTICS_STREAM3,

            /// <summary>
            /// Video decode statistics.
            /// </summary>
            VideoDecodeStatistics = D3D12_QUERY_TYPE_VIDEO_DECODE_STATISTICS,
            PipelineStatistics1 = D3D12_QUERY_TYPE_PIPELINE_STATISTICS1
        };

        /// <summary>
        /// Specifies the predication operation to apply.
        /// </summary>
        public enum class D3D12PredicationOp : UINT
        {
            /// <summary>
            /// Enables predication if all 64-bits are zero.
            /// </summary>
            EqualZero = D3D12_PREDICATION_OP_EQUAL_ZERO,

            /// <summary>
            /// Enables predication if at least one of the 64-bits are not zero.
            /// </summary>
            NotEqualZero = D3D12_PREDICATION_OP_NOT_EQUAL_ZERO
        };

        /// <summary>
        /// Identifies the type of resource that will be viewed as a shader resource.
        /// </summary>
        public enum class D3D12SrvDimension : UINT
        {
            Unknown = D3D12_SRV_DIMENSION_UNKNOWN,
            Buffer = D3D12_SRV_DIMENSION_BUFFER,
            Texture1D = D3D12_SRV_DIMENSION_TEXTURE1D,
            Texture1DArray = D3D12_SRV_DIMENSION_TEXTURE1DARRAY,
            Texture2D = D3D12_SRV_DIMENSION_TEXTURE2D,
            Texture2DArray = D3D12_SRV_DIMENSION_TEXTURE2DARRAY,
            Texture2DMS = D3D12_SRV_DIMENSION_TEXTURE2DMS,
            Texture2DMSArray = D3D12_SRV_DIMENSION_TEXTURE2DMSARRAY,
            Texture3D = D3D12_SRV_DIMENSION_TEXTURE3D,
            TextureCube = D3D12_SRV_DIMENSION_TEXTURECUBE,
            TextureCubeArray = D3D12_SRV_DIMENSION_TEXTURECUBEARRAY,
            RaytracingAccelerationStructure = D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE
        };

        /// <summary>
        /// Identifies how to view a buffer resource.
        /// </summary>
        [Flags]
        public enum class D3D12BufferSrvFlags : UINT
        {
            /// <summary>
            /// Indicates a default view.
            /// </summary>
            None = D3D12_BUFFER_SRV_FLAG_NONE,

            /// <summary>
            /// View the buffer as raw.
            /// </summary>
            Raw = D3D12_BUFFER_SRV_FLAG_RAW
        };

        /// <summary>
        /// Specifies how memory gets routed by a shader resource view (SRV).
        /// </summary>
        public enum class D3D12ShaderComponentMapping : UINT
        {
            /// <summary>
            /// Indicates return component 0 (red).
            /// </summary>
            FromMemoryComponent0 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_0,

            /// <summary>
            /// Indicates return component 1 (green).
            /// </summary>
            FromMemoryComponent1 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_1,

            /// <summary>
            /// Indicates return component 2 (blue).
            /// </summary>
            FromMemoryComponent2 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_2,

            /// <summary>
            /// Indicates return component 3 (alpha).
            /// </summary>
            FromMemoryComponent3 = D3D12_SHADER_COMPONENT_MAPPING_FROM_MEMORY_COMPONENT_3,

            /// <summary>
            /// Indicates forcing the resulting value to 0.
            /// </summary>
            ForceValue0 = D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_0,

            /// <summary>
            /// Indicates forcing the resulting value 1. The value of forcing 1 is either 0x1 or 1.0f
            /// depending on the format type for that component in the source format.
            /// </summary>
            ForceValue1 = D3D12_SHADER_COMPONENT_MAPPING_FORCE_VALUE_1
        };

        /// <summary>
        /// Identifies unordered-access view options.
        /// </summary>
        public enum class D3D12UavDimension : UINT
        {
            Unknown = D3D12_UAV_DIMENSION_UNKNOWN,
            Buffer = D3D12_UAV_DIMENSION_BUFFER,
            Texture1D = D3D12_UAV_DIMENSION_TEXTURE1D,
            Texture1DArray = D3D12_UAV_DIMENSION_TEXTURE1DARRAY,
            Texture2D = D3D12_UAV_DIMENSION_TEXTURE2D,
            Texture2DArray = D3D12_UAV_DIMENSION_TEXTURE2DARRAY,
            Texture3D = D3D12_UAV_DIMENSION_TEXTURE3D
        };

        /// <summary>
        /// Identifies how to view a buffer resource.
        /// </summary>
        [Flags]
        public enum class D3D12BufferUavFlags : UINT
        {
            /// <summary>
            /// Indicates a default view.
            /// </summary>
            None = D3D12_BUFFER_UAV_FLAG_NONE,

            /// <summary>
            /// Resource contains raw, unstructured data.
            /// </summary>
            Raw = D3D12_BUFFER_UAV_FLAG_RAW
        };

        /// <summary>
        /// Describes the subresources from a resource that are accessible by using a render-target view.
        /// </summary>
        public enum class D3D12RtvDimension : UINT
        {
            Unknown = D3D12_RTV_DIMENSION_UNKNOWN,
            Buffer = D3D12_RTV_DIMENSION_BUFFER,
            Texture1D = D3D12_RTV_DIMENSION_TEXTURE1D,
            Texture1DArray = D3D12_RTV_DIMENSION_TEXTURE1DARRAY,
            Texture2D = D3D12_RTV_DIMENSION_TEXTURE2D,
            Texture2DArray = D3D12_RTV_DIMENSION_TEXTURE2DARRAY,
            Texture2DMS = D3D12_RTV_DIMENSION_TEXTURE2DMS,
            Texture2DMSArray = D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY,
            Texture3D = D3D12_RTV_DIMENSION_TEXTURE3D
        };

        /// <summary>
        /// Specifies how to access a resource used in a depth-stencil view.
        /// </summary>
        public enum class D3D12DsvDimension : UINT
        {
            Unknown = D3D12_DSV_DIMENSION_UNKNOWN,
            Texture1D = D3D12_DSV_DIMENSION_TEXTURE1D,
            Texture1DArray = D3D12_DSV_DIMENSION_TEXTURE1DARRAY,
            Texture2D = D3D12_DSV_DIMENSION_TEXTURE2D,
            Texture2DArray = D3D12_DSV_DIMENSION_TEXTURE2DARRAY,
            Texture2DMS = D3D12_DSV_DIMENSION_TEXTURE2DMS,
            Texture2DMSArray = D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY,
        };

        /// <summary>
        /// Specifies depth-stencil view options.
        /// </summary>
        [Flags]
        public enum class D3D12DsvFlags : UINT
        {
            /// <summary>
            /// Indicates a default view.
            /// </summary>
            None = D3D12_DSV_FLAG_NONE,

            /// <summary>
            /// Indicates that depth values are read only.
            /// </summary>
            ReadOnlyDepth = D3D12_DSV_FLAG_READ_ONLY_DEPTH,

            /// <summary>
            /// Indicates that stencil values are read only.
            /// </summary>
            ReadOnlyStencil = D3D12_DSV_FLAG_READ_ONLY_STENCIL
        };

        /// <summary>
        /// Specifies fence options.
        /// </summary>
        [Flags]
        public enum class D3D12FenceFlags : UINT
        {
            /// <summary>
            /// No options are specified.
            /// </summary>
            None = D3D12_FENCE_FLAG_NONE,

            /// <summary>
            /// The fence is shared.
            /// </summary>
            Shared = D3D12_FENCE_FLAG_SHARED,

            /// <summary>
            /// The fence is shared with another GPU adapter.
            /// </summary>
            SharedCrossAdapter = D3D12_FENCE_FLAG_SHARED_CROSS_ADAPTER,

            /// <summary>
            /// The fence is of the non-monitored type. Non-monitored fences should only be used when
            /// the adapter doesn't support monitored fences, or when a fence is shared with an adapter
            /// that doesn't support monitored fences.
            /// </summary>
            NonMonitored = D3D12_FENCE_FLAG_NON_MONITORED
        };

        /// <summary>
        /// Specifies filtering options during texture sampling.
        /// </summary>
        public enum class D3D12Filter : UINT
        {
            MinMagMipPoint             = D3D12_FILTER_MIN_MAG_MIP_POINT,
            MinMagPointMipLinear       = D3D12_FILTER_MIN_MAG_POINT_MIP_LINEAR,
            MinPointMagLinearMipPoint  = D3D12_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,
            MinPointMagMipLinear       = D3D12_FILTER_MIN_POINT_MAG_MIP_LINEAR,
            MinLinearMagMipPoint       = D3D12_FILTER_MIN_LINEAR_MAG_MIP_POINT,
            MinLinearMagPointMipLinear = D3D12_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
            MinMagLinearMipPoint       = D3D12_FILTER_MIN_MAG_LINEAR_MIP_POINT,
            MinMagMipLinear            = D3D12_FILTER_MIN_MAG_MIP_LINEAR,
            Anisotropic                = D3D12_FILTER_ANISOTROPIC,
            ComparisonMinMagMipPoint              = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_POINT,
            ComparisionMinMagPointMipLinear       = D3D12_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR,
            ComparisionMinPointMagLinearMipPoint  = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,
            ComparisionMinPointMagMipLinear       = D3D12_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR,
            ComparisionMinLinearMagMipPoint       = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT,
            ComparisionMinLinearMagPointMipLinear = D3D12_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
            ComparisionMinMagLinearMipPoint       = D3D12_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT,
            ComparisionMinMagMipLinear            = D3D12_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR,
            ComparisionAnisotropic                = D3D12_FILTER_COMPARISON_ANISOTROPIC,
            MinimumMinMagMipPoint             = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT,
            MinimumMinMagPointMipLinear       = D3D12_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR,
            MinimumMinPointMagLinearMipPoint  = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
            MinimumMinPointMagMipLinear       = D3D12_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR,
            MinimumMinLinearMagMipPoint       = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT,
            MinimumMinLinearMagPointMipLinear = D3D12_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
            MinimumMinMagLinearMipPoint       = D3D12_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT,
            MinimumMinMagMipLinear            = D3D12_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR,
            MinimumAnisotropic                = D3D12_FILTER_MINIMUM_ANISOTROPIC,
            MaximumMinMagMipPoint             = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_POINT,
            MaximumMinMagPointMipLinear       = D3D12_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR,
            MaximumMinPointMagLinearMipPoint  = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT,
            MaximumMinPointMagMipLinear       = D3D12_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR,
            MaximumMinLinearMagMipPoint       = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT,
            MaximumMinLinearMagPointMipLinear = D3D12_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR,
            MaximumMinMagLinearMipPoint       = D3D12_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT,
            MaximumMinMagMipLinear            = D3D12_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR,
            MaximumAnisotropic                = D3D12_FILTER_MAXIMUM_ANISOTROPIC
        };

        /// <summary>
        /// Identifies a technique for resolving texture coordinates that are outside of the boundaries
        /// of a texture.
        /// </summary>
        public enum class D3D12TextureAddressMode : UINT
        {
            /// <summary>
            /// Tile the texture at every (u,v) integer junction.
            /// For example, for u values between 0 and 3, the texture is repeated three times.
            /// </summary>
            Wrap = D3D12_TEXTURE_ADDRESS_MODE_WRAP,

            /// <summary>
            /// Flip the texture at every (u,v) integer junction.
            ///For u values between 0 and 1, for example, the texture is addressed normally; between 1
            /// and 2, the texture is flipped(mirrored); between 2 and 3, the texture is normal again;
            /// and so on.
            /// </summary>
            Mirror = D3D12_TEXTURE_ADDRESS_MODE_MIRROR,

            /// <summary>
            /// Texture coordinates outside the range [0.0, 1.0] are set to the texture color at 0.0
            /// or 1.0, respectively.
            /// </summary>
            Clamp = D3D12_TEXTURE_ADDRESS_MODE_CLAMP,

            /// <summary>
            /// Texture coordinates outside the range [0.0, 1.0] are set to the border color specified
            /// in D3D12SamplerDesc or HLSL code.
            /// </summary>
            Border = D3D12_TEXTURE_ADDRESS_MODE_BORDER,

            /// <summary>
            /// Similar to Mirror and Clamp.
            /// Takes the absolute value of the texture coordinate(thus, mirroring around 0), and
            /// then clamps to the maximum value.
            /// </summary>
            MirrorOnce = D3D12_TEXTURE_ADDRESS_MODE_MIRROR_ONCE
        };

        /// <summary>
        /// Specifies the type of query heap to create.
        /// </summary>
        public enum class D3D12QueryHeapType : UINT
        {
            /// <summary>
            /// This returns a binary 0/1 result: 0 indicates that no samples passed depth and stencil
            /// testing, 1 indicates that at least one sample passed depth and stencil testing. This
            /// enables occlusion queries to not interfere with any GPU performance optimization
            /// associated with depth/stencil testing.
            /// </summary>
            Occlusion = D3D12_QUERY_HEAP_TYPE_OCCLUSION,

            /// <summary>
            /// Indicates that the heap is for high-performance timing data.
            /// </summary>
            Timestamp = D3D12_QUERY_HEAP_TYPE_TIMESTAMP,

            /// <summary>
            /// Indicates the heap is to contain pipeline data.
            /// </summary>
            PipelineStatistics = D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS,

            /// <summary>
            /// Indicates the heap is to contain stream output data.
            /// </summary>
            SOStatistics = D3D12_QUERY_HEAP_TYPE_SO_STATISTICS,

            /// <summary>
            /// Indicates the heap is to contain video decode statistics data.
            /// </summary>
            VideoDecodeStatistics = D3D12_QUERY_HEAP_TYPE_VIDEO_DECODE_STATISTICS,

            /// <summary>
            /// Indicates the heap is to contain timestamp queries emitted exclusively by copy command
            /// lists. Copy queue timestamps can only be queried from a copy command list, and a copy
            /// command list can not emit to a regular timestamp query Heap.
            /// </summary>
            CopyQueueTimestamp = D3D12_QUERY_HEAP_TYPE_COPY_QUEUE_TIMESTAMP,
            PipelineStatistics1 = D3D12_QUERY_HEAP_TYPE_PIPELINE_STATISTICS1
        };

        /// <summary>
        /// Specifies the type of root signature slot.
        /// </summary>
        public enum class D3D12RootParameterType : UINT
        {
            /// <summary>
            /// The slot is for a descriptor table.
            /// </summary>
            DescriptorTable = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE,

            /// <summary>
            /// The slot is for root constants.
            /// </summary>
            Constants = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS,

            /// <summary>
            /// The slot is for a constant-buffer view (CBV).
            /// </summary>
            Cbv = D3D12_ROOT_PARAMETER_TYPE_CBV,

            /// <summary>
            /// The slot is for a shader-resource view (SRV).
            /// </summary>
            Srv = D3D12_ROOT_PARAMETER_TYPE_SRV,

            /// <summary>
            /// The slot is for a unordered-access view (UAV).
            /// </summary>
            Uav = D3D12_ROOT_PARAMETER_TYPE_UAV
        };

        /// <summary>
        /// Specifies a range so that, for example, if part of a descriptor table has 100
        /// shader-resource views (SRVs) that range can be declared in one entry rather than 100.
        /// </summary>
        public enum class D3D12DescriptorRangeType : UINT
        {
            /// <summary>
            /// Specifies a range of SRVs.
            /// </summary>
            Srv = D3D12_DESCRIPTOR_RANGE_TYPE_SRV,

            /// <summary>
            /// Specifies a range of unordered-access views (UAVs).
            /// </summary>
            Uav = D3D12_DESCRIPTOR_RANGE_TYPE_UAV,

            /// <summary>
            /// Specifies a range of constant-buffer views (CBVs).
            /// </summary>
            Cbv = D3D12_DESCRIPTOR_RANGE_TYPE_CBV,

            /// <summary>
            /// Specifies a range of samplers.
            /// </summary>
            Sampler = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER
        };

        /// <summary>
        /// Specifies the shaders that can access the contents of a given root signature slot.
        /// </summary>
        public enum class D3D12ShaderVisibility : UINT
        {
            /// <summary>
            /// Specifies that all shader stages can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            All = D3D12_SHADER_VISIBILITY_ALL,

            /// <summary>
            /// Specifies that the vertex shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Vertex = D3D12_SHADER_VISIBILITY_VERTEX,

            /// <summary>
            /// Specifies that the hull shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Hull = D3D12_SHADER_VISIBILITY_HULL,

            /// <summary>
            /// Specifies that the domain shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Domain = D3D12_SHADER_VISIBILITY_DOMAIN,

            /// <summary>
            /// Specifies that the geometry shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Geometry = D3D12_SHADER_VISIBILITY_GEOMETRY,

            /// <summary>
            /// Specifies that the pixel shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Pixel = D3D12_SHADER_VISIBILITY_PIXEL,

            /// <summary>
            /// Specifies that the amplification shader stage can access whatever is bound at the
            /// root signature slot.
            /// </summary>
            Amplification = D3D12_SHADER_VISIBILITY_AMPLIFICATION,

            /// <summary>
            /// Specifies that the mesh shader stage can access whatever is bound at the root
            /// signature slot.
            /// </summary>
            Mesh = D3D12_SHADER_VISIBILITY_MESH
        };

        /// <summary>
        /// Specifies the border color for a static sampler.
        /// </summary>
        public enum class D3D12StaticBorderColor : UINT
        {
            /// <summary>
            /// Indicates black, with the alpha component as fully transparent.
            /// </summary>
            TransparentBlack = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK,

            /// <summary>
            /// Indicates black, with the alpha component as fully opaque.
            /// </summary>
            OpaqueBlack = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK,

            /// <summary>
            /// Indicates white, with the alpha component as fully opaque.
            /// </summary>
            OpaqueWhite = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE
        };



        /// <summary>
        /// This structure is simply used as a mechanism to set default parameters on the other
        /// helper structures. Use D3D12::Default to initialize some structs to default values.
        /// </summary>
        public value struct D3DDefault
        {

        };

        /// <summary>
        /// Interface that indicates the struct is for receiving DirectX12 feature data.
        /// </summary>
        public interface class ID3D12FeatureData
        {

        };

        /// <summary>
        /// Interface that indicates the struct is for receiving DirectX12 query data.
        /// </summary>
        public interface class ID3D12QueryData
        {

        };

        /// <summary>
        /// Provides detail about the adapter architecture, so that your application can better optimize
        /// for certain adapter properties.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataArchitecture : ID3D12FeatureData
        {
            /// <summary>
            /// In multi-adapter operation, this indicates which physical adapter of the device is relevant.
            /// See Multi-adapter systems. NodeIndex is filled out by the application before calling
            /// CheckFeatureSupport, as the application can retrieve details about the architecture of
            /// each adapter.
            /// </summary>
            unsigned int NodeIndex;

            /// <summary>
            /// Specifies whether the hardware and driver support a tile-based renderer. The runtime sets
            /// this member to True if the hardware and driver support a tile-based renderer.
            /// </summary>
            CBool TileBasedRenderer;

            /// <summary>
            /// Specifies whether the hardware and driver support UMA. The runtime sets this member to True
            /// if the hardware and driver support UMA.
            /// </summary>
            CBool UMA;

            /// <summary>
            /// Specifies whether the hardware and driver support cache-coherent UMA. The runtime sets
            /// this member to True if the hardware and driver support cache-coherent UMA.
            /// </summary>
            CBool CacheCoherentUMA;

            D3D12FeatureDataArchitecture(unsigned int nodeIndex);
        };

        /// <summary>
        /// Provides detail about the adapter architecture, so that your application can better optimize
        /// for certain adapter properties.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataArchitecture1 : ID3D12FeatureData
        {
            /// <summary>
            /// In multi-adapter operation, this indicates which physical adapter of the device is relevant.
            /// See Multi-adapter systems. NodeIndex is filled out by the application before calling
            /// CheckFeatureSupport, as the application can retrieve details about the architecture of
            /// each adapter.
            /// </summary>
            unsigned int NodeIndex;

            /// <summary>
            /// Specifies whether the hardware and driver support a tile-based renderer. The runtime sets
            /// this member to True if the hardware and driver support a tile-based renderer.
            /// </summary>
            CBool TileBasedRenderer;

            /// <summary>
            /// Specifies whether the hardware and driver support UMA. The runtime sets this member to True
            /// if the hardware and driver support UMA.
            /// </summary>
            CBool UMA;

            /// <summary>
            /// Specifies whether the hardware and driver support cache-coherent UMA. The runtime sets
            /// this member to True if the hardware and driver support cache-coherent UMA.
            /// </summary>
            CBool CacheCoherentUMA;

            /// <summary>
            /// Specifies whether the hardware and driver support isolated Memory Management Unit (MMU).
            /// The runtime sets this member to TRUE if the GPU honors CPU page table properties like
            /// MEM_WRITE_WATCH (for more information, see VirtualAlloc) and PAGE_READONLY
            /// (for more information, see Memory Protection Constants).
            /// </summary>
            CBool IsolatedMMU;

            D3D12FeatureDataArchitecture1(unsigned int nodeIndex);
        };

        /// <summary>
        /// Details the adapter's support for prioritization of different command queue types.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataCommandQueuePriority : ID3D12FeatureData
        {
            /// <summary>
            /// The type of the command list you're interested in.
            /// </summary>
            D3D12CommandListType CommandListType;

            /// <summary>
            /// The priority level you're interested in.
            /// </summary>
            unsigned int Priority;

            /// <summary>
            /// On return, contains true if the specfied command list type supports the specified
            /// priority level; otherwise, false.
            /// </summary>
            CBool PriorityForTypeIsSupported;

            D3D12FeatureDataCommandQueuePriority(D3D12CommandListType type, unsigned int priority);
        };

        /// <summary>
        /// Indicates the level of support for the sharing of resources between different adapters—for
        /// example, multiple GPUs.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataCrossNode : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates the tier of cross-adapter sharing support.
            /// </summary>
            D3D12CrossNodeSharingTier SharingTier;

            /// <summary>
            /// Indicates there is support for shader instructions which operate across adapters.
            /// </summary>
            CBool AtomicShaderInstructions;
        };

        /// <summary>
        /// Describes Direct3D 12 feature options in the current graphics driver.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options : ID3D12FeatureData
        {
            /// <summary>
            /// Specifies whether double types are allowed for shader operations. If True, double types are
            /// allowed; otherwise False.
            /// </summary>
            CBool DoublePrecisionFloatShaderOps;

            /// <summary>
            /// Specifies whether logic operations are available in blend state. The runtime sets this
            /// member to True if logic operations are available in blend state and False otherwise.
            /// This member is FALSE for feature level 9.1, 9.2, and 9.3. This member is optional for
            /// feature level 10, 10.1, and 11. This member is TRUE for feature level 11.1 and 12.
            /// </summary>
            CBool OutputMergerLogicOp;

            /// <summary>
            /// A combination of D3D12ShaderMinPrecisionSupport-typed values that are combined by using
            /// a bitwise OR operation. The resulting value specifies minimum precision levels that the
            /// driver supports for shader stages. A value of zero indicates that the driver supports only
            /// full 32-bit precision for all shader stages.
            /// </summary>
            D3D12ShaderMinPrecisionSupport MinPrecisionSupport;

            /// <summary>
            /// Specifies whether the hardware and driver support tiled resources. The runtime sets this
            /// member to a D3D12TiledResourceTier-typed value that indicates if the hardware and driver
            /// support tiled resources and at what tier level.
            /// </summary>
            D3D12TiledResourceTier TiledResourcesTier;

            /// <summary>
            /// Specifies the level at which the hardware and driver support resource binding. The runtime
            /// sets this member to a D3D12ResourceBindingTier-typed value that indicates the tier level.
            /// </summary>
            D3D12ResourceBindingTier ResourceBindingTier;

            /// <summary>
            /// Specifies whether pixel shader stencil ref is supported. If True, it's supported;
            /// otherwise False.
            /// </summary>
            CBool PSSpecifiedStencilRefSupported;

            /// <summary>
            /// Specifies whether the loading of additional formats for typed unordered-access views
            /// (UAVs) is supported. If True, it's supported; otherwise False.
            /// </summary>
            CBool TypedUAVLoadAdditionalFormats;

            /// <summary>
            /// Specifies whether Rasterizer Order Views (ROVs) are supported. If True, they're supported;
            /// otherwise False.
            /// </summary>
            CBool ROVsSupported;

            /// <summary>
            /// Specifies the level at which the hardware and driver support conservative rasterization.
            /// The runtime sets this member to a D3D12ConservativeRasterizationTier-typed value that
            /// indicates the tier level.
            /// </summary>
            D3D12ConservativeRasterizationTier ConservativeRasterizationTier;

            /// <summary>
            /// Don't use this field; instead, use the D3D12FeatureDataGPUVirtualAddressSupport query
            /// (a structure with a MaxGPUVirtualAddressBitsPerResource member), which is more accurate.
            /// </summary>
            unsigned int MaxGPUVirtualAddressBitsPerResource;

            /// <summary>
            /// True if the hardware supports textures with the 64KB standard swizzle pattern. Support for
            /// this pattern enables zero-copy texture optimizations while providing near-equilateral
            /// locality for each dimension within the texture.
            /// </summary>
            CBool StandardSwizzle64KBSupported;

            /// <summary>
            /// A D3D12CrossNodeSharingTier enumeration constant that specifies the level of sharing
            /// across nodes of an adapter that has multiple nodes, such as Tier 1 Emulated, Tier 1, or Tier 2.
            /// </summary>
            D3D12CrossNodeSharingTier CrossNodeSharingTier;

            /// <summary>
            /// False means the device only supports copy operations to and from cross-adapter row-major
            /// textures. True means the device supports shader resource views, unordered access views,
            /// and render target views of cross-adapter row-major textures. "Cross-adapter" means
            /// between multiple adapters (even from different IHVs).
            /// </summary>
            CBool CrossAdapterRowMajorTextureSupported;

            /// <summary>
            /// Whether the viewport (VP) and Render Target (RT) array index from any shader feeding
            /// the rasterizer are supported without geometry shader emulation.
            /// </summary>
            CBool VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation;

            /// <summary>
            /// Specifies the level at which the hardware and driver require heap attribution related
            /// to resource type. The runtime sets this member to a D3D12ResourceHeapTier enumeration constant.
            /// </summary>
            D3D12ResourceHeapTier ResourceHeapTier;
        };

        /// <summary>
        /// Describes the level of support for HLSL 6.0 wave operations.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options1 : ID3D12FeatureData
        {
            /// <summary>
            /// True if the driver supports HLSL 6.0 wave operations.
            /// </summary>
            CBool WaveOps;

            /// <summary>
            /// Specifies the baseline number of lanes in the SIMD wave that this implementation can support.
            /// This term is sometimes known as "wavefront size" or "warp width". Currently apps should
            /// rely only on this minimum value for sizing workloads.
            /// </summary>
            unsigned int WaveLaneCountMin;

            /// <summary>
            /// Specifies the maximum number of lanes in the SIMD wave that this implementation can support.
            /// This capability is reserved for future expansion, and is not expected to be used by
            /// current applications.
            /// </summary>
            unsigned int WaveLaneCountMax;

            /// <summary>
            /// Specifies the total number of SIMD lanes on the hardware.
            /// </summary>
            unsigned int TotalLaneCount;

            /// <summary>
            /// Indicates transitions are possible in and out of the CBV, and indirect argument states,
            /// on compute command lists. If CheckFeatureSupport succeeds this value will always be true.
            /// </summary>
            CBool ExpandedComputeResourceStates;

            /// <summary>
            /// Indicates that 64bit integer operations are supported.
            /// </summary>
            CBool Int64ShaderOps;
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for depth-bounds tests and
        /// programmable sample positions.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options2 : ID3D12FeatureData
        {
            /// <summary>
            /// On return, contains true if depth-bounds tests are supported; otherwise, false.
            /// </summary>
            CBool DepthBoundsTestSupported;

            /// <summary>
            /// On return, contains a value that indicates the level of support offered for programmable
            /// sample positions.
            /// </summary>
            D3D12ProgrammableSamplePositionsTier ProgrammableSamplePositionsTier;
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for timestamp queries,
        /// format-casting, immediate write, view instancing, and barycentrics.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options3 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates whether timestamp queries are supported on copy queues.
            /// </summary>
            CBool CopyQueueTimestampQueriesSupported;

            /// <summary>
            /// Indicates whether casting from one fully typed format to another, compatible, format
            /// is supported.
            /// </summary>
            CBool CastingFullyTypedFormatSupported;

            /// <summary>
            /// Indicates the kinds of command lists that support the ability to write an immediate
            /// value directly from the command stream into a specified buffer.
            /// </summary>
            D3D12CommandListSupportFlags WriteBufferImmediateSupportFlags;

            /// <summary>
            /// Indicates the level of support the adapter has for view instancing.
            /// </summary>
            D3D12ViewInstancingTier ViewInstancingTier;

            /// <summary>
            /// Indicates whether barycentrics are supported.
            /// </summary>
            CBool BarycentricsSupported;
        };

        /// <summary>
        /// Indicates the level of support for 64KB-aligned MSAA textures, cross-API sharing, and native
        /// 16-bit shader operations.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options4 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates whether 64KB-aligned MSAA textures are supported.
            /// </summary>
            CBool MSAA64KBAlignedTextureSupported;

            /// <summary>
            /// Indicates the tier of cross-API sharing support.
            /// </summary>
            D3D12SharedResourceCompatibilityTier SharedResourceCompatibilityTier;

            /// <summary>
            /// Indicates native 16-bit shader operations are supported. These operations require shader
            /// model 6_2.
            /// </summary>
            CBool Native16BitShaderOpsSupported;
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for render passes, ray tracing,
        /// and shader-resource view tier 3 tiled resources.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options5 : ID3D12FeatureData
        {
            /// <summary>
            /// A boolean value indicating whether the options require shader-resource view tier 3
            /// tiled resource support.
            /// </summary>
            CBool SRVOnlyTiledResourceTier3;

            /// <summary>
            /// The extent to which a device driver and/or the hardware efficiently supports
            /// render passes.
            /// </summary>
            D3D12RenderPassTier RenderPassesTier;

            /// <summary>
            /// Specifies the level of ray tracing support on the graphics device.
            /// </summary>
            D3D12RaytracingTier RaytracingTier;
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for variable-rate shading (VRS),
        /// and indicates whether or not background processing is supported.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options6 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates whether 2x4, 4x2, and 4x4 coarse pixel sizes are supported for
            /// single-sampled rendering; and whether coarse pixel size 2x4 is supported for 2x MSAA.
            /// true if those sizes are supported, otherwise false.
            /// </summary>
            CBool AdditionalShadingRatesSupported;

            /// <summary>
            /// Indicates whether the per-provoking-vertex (also known as per-primitive) rate can be
            /// used with more than one viewport. If so, then, in that case, that rate can be used
            /// when SV_ViewportIndex is written to. true if that rate can be used with more than
            /// one viewport, otherwise false.
            /// </summary>
            CBool PerPrimitiveShadingRateSupportedWithViewportIndexing;

            /// <summary>
            /// Indicates the shading rate tier.
            /// </summary>
            D3D12VariableShadingRateTier VariableShadingRateTier;

            /// <summary>
            /// Indicates the tile size of the screen-space image.
            /// </summary>
            unsigned int ShadingRateImageTileSize;

            /// <summary>
            /// Indicates whether or not background processing is supported. true if background
            /// processing is supported, otherwise false.
            /// </summary>
            CBool BackgroundProcessingSupported;
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for mesh and amplification
        /// shaders, and for sampler feedback.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options7 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates the level of support for mesh and amplification shaders.
            /// </summary>
            D3D12MeshShaderTier MeshShaderTier;

            /// <summary>
            /// Indicates the level of support for sampler feedback.
            /// </summary>
            D3D12SamplerFeedbackTier SamplerFeedbackTier;
        };

        /// <summary>
        /// Indicates whether or not unaligned block-compressed textures are supported.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options8 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates whether or not unaligned block-compressed textures are supported.
            /// If false, then Direct3D 12 requires that the dimensions of the top - level mip of a
            /// block - compressed texture are aligned to multiples of 4 (such alignment requirements
            /// do not apply to less - detailed mips). If true, then no such alignment requirement
            /// applies to any mip level of a block - compressed texture.
            /// </summary>
            CBool UnalignedBlockTexturesSupported;
        };

        /// <summary>
        /// Indicates whether or not support exists for mesh shaders, values of
        /// SV_RenderTargetArrayIndex that are 8 or greater, typed resource 64-bit integer atomics,
        /// derivative and derivative-dependent texture sample operations, and the level of support
        /// for WaveMMA (wave_matrix) operations.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataD3D12Options9 : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates whether or not mesh shaders are supported. true if supported, otherwise false.
            /// </summary>
            CBool MeshShaderPipelineStatsSupported;

            /// <summary>
            /// Indicates whether or not values of SV_RenderTargetArrayIndex that are 8 or greater
            /// are supported. true if supported, otherwise false.
            /// </summary>
            CBool MeshShaderSupportsFullRangeRenderTargetArrayIndex;

            /// <summary>
            /// Indicates whether or not typed resource 64-bit integer atomics are supported. true
            /// if supported, otherwise false.
            /// </summary>
            CBool AtomicInt64OnTypedResourceSupported;

            /// <summary>
            /// Indicates whether or not typed resource 64-bit integer atomics are supported. true
            /// if supported, otherwise false.
            /// </summary>
            CBool AtomicInt64OnGroupSharedSupported;

            /// <summary>
            /// Indicates whether or not derivative and derivative-dependent texture sample operations
            /// are supported. true if supported, otherwise false.
            /// </summary>
            CBool DerivativesInMeshAndAmplificationShadersSupported;

            /// <summary>
            /// Indicates the level of support for WaveMMA (wave_matrix) operations.
            /// </summary>
            D3D12WaveMMATier WaveMMATier;
        };

        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataWaveMMA : ID3D12FeatureData
        {
            D3D12WaveMMAInputDatatype InputDataType;
            D3D12WaveMMADimension M;
            D3D12WaveMMADimension N;
            CBool Supported;
            unsigned int K;
            D3D12WaveMMAAccumDatatype AccumDataTypes;
            unsigned int RequiredWaveLaneCountMin;
            unsigned int RequiredWaveLaneCountMax;

            D3D12FeatureDataWaveMMA(
                D3D12WaveMMAInputDatatype inputDataType,
                D3D12WaveMMADimension m,
                D3D12WaveMMADimension n
            );
        };

        /// <summary>
        /// Provides detail about whether the adapter supports creating heaps from existing system
        /// memory. Such heaps are not intended for general use, but are exceptionally useful for
        /// diagnostic purposes, because they are guaranteed to persist even after the adapter faults
        /// or experiences a device-removal event. Persistence is not guaranteed for heaps returned by
        /// D3D12Device::CreateHeap or D3D12Device::CreateCommittedResource, even when the heap resides
        /// in system memory.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataExistingHeaps : ID3D12FeatureData
        {
            /// <summary>
            /// True if the adapter can create a heap from existing system memory. Otherwise, False.
            /// </summary>
            CBool Supported;
        };

        /// <summary>
        /// Describes info about the feature levels supported by the current graphics driver.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataFeatureLevels : ID3D12FeatureData
        {
            /// <summary>
            /// The number of feature levels in the array at pFeatureLevelsRequested.
            /// </summary>
            unsigned int NumFeatureLevels;

            /// <summary>
            /// A pointer to an array of D3DFeatureLevel that the application is requesting for the
            /// driver and hardware to evaluate.
            /// </summary>
            D3D::D3DFeatureLevel* pFeatureLevelsRequested;

            /// <summary>
            /// The maximum feature level that the driver and hardware support.
            /// </summary>
            D3D::D3DFeatureLevel MaxSupportedFeatureLevel;

            /// <summary>
            /// Initializes the feature level check struct
            /// </summary>
            /// <param name="featureLevelsRequested">Array of feature levels to request.</param>
            /// <param name="featureLevelArrayPinPtr">Returns pin pointer to the first element of the
            /// feature level array. If you are done with this struct, then you should free the
            /// GCHandle.</param>
            D3D12FeatureDataFeatureLevels(
                array<D3D::D3DFeatureLevel>^ featureLevelsRequested,
                [Out] GCHandle% featureLevelArrayPinPtr
            );
        };

        /// <summary>
        /// Describes a DXGI data format and plane count.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataFormatInfo : ID3D12FeatureData
        {
            /// <summary>
            /// A DXGIFormat-typed value for the format to return info about.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// The number of planes to provide information about.
            /// </summary>
            unsigned char PlaneCount;

            D3D12FeatureDataFormatInfo(DXGIFormat format);
        };

        /// <summary>
        /// Describes a DXGI data format and plane count.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataFormatSupport : ID3D12FeatureData
        {
            /// <summary>
            /// A DXGIFormat-typed value for the format to return info about.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// A combination of D3D12FormatSupport1-typed values that are combined by using a bitwise
            /// OR operation. The resulting value specifies which resources are supported.
            /// </summary>
            D3D12FormatSupport1 Support1;

            /// <summary>
            /// A combination of D3D12FormatSupport2-typed values that are combined by using a
            /// bitwise OR operation. The resulting value specifies which unordered resource options
            /// are supported.
            /// </summary>
            D3D12FormatSupport2 Support2;

            D3D12FeatureDataFormatSupport(DXGIFormat format);
        };

        /// <summary>
        /// Details the adapter's GPU virtual address space limitations, including maximum address
        /// bits per resource and per process.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataGPUVirtualAddressSupport : ID3D12FeatureData
        {
            /// <summary>
            /// The maximum GPU virtual address bits per resource.
            /// </summary>
            unsigned int MaxGPUVirtualAddressBitsPerResource;

            /// <summary>
            /// The maximum GPU virtual address bits per process.
            /// </summary>
            unsigned int MaxGPUVirtualAddressBitsPerProcess;
        };

        /// <summary>
        /// Describes the multi-sampling image quality levels for a given format and sample count.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataMultisampleQualityLevels : ID3D12FeatureData
        {
            /// <summary>
            /// A DXGIFormat-typed value for the format to return info about.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// The number of multi-samples per pixel to return info about.
            /// </summary>
            unsigned int SampleCount;

            /// <summary>
            /// Flags to control quality levels, as a bitwise-OR'd combination of
            /// D3D12MultisampleQualityLevelFlags enumeration constants. The resulting value
            /// specifies options for determining quality levels.
            /// </summary>
            D3D12MultisampleQualityLevelFlags Flags;

            /// <summary>
            /// The number of quality levels.
            /// </summary>
            unsigned int NumQualityLevels;

            D3D12FeatureDataMultisampleQualityLevels(
                DXGIFormat format, unsigned int sampleCount, D3D12MultisampleQualityLevelFlags flags);
        };

        /// <summary>
        /// Indicates the level of support for protected resource sessions.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataProtectedResourceSessionSupport : ID3D12FeatureData
        {
            /// <summary>
            /// An input field, indicating the adapter index to query.
            /// </summary>
            unsigned int NodeIndex;
            D3D12ProtectedResourceSessionSupportFlags Support;

            D3D12FeatureDataProtectedResourceSessionSupport(unsigned int nodeIndex);
        };

        /// <summary>
        /// Indicates a count of protected resource session types.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataProtectedResourceSessionTypeCount : ID3D12FeatureData
        {
            /// <summary>
            /// An input parameter which, in multi-adapter operation, indicates which physical adapter
            /// of the device this operation applies to.
            /// </summary>
            unsigned int NodeIndex;

            /// <summary>
            /// An output parameter containing the number of protected resource session types supported
            /// by the driver.
            /// </summary>
            unsigned int Count;

            D3D12FeatureDataProtectedResourceSessionTypeCount(unsigned int nodeIndex);
        };

        /// <summary>
        /// Indicates a list of protected resource session types.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataProtectedResourceSessionTypes : ID3D12FeatureData
        {
            /// <summary>
            /// An input parameter which, in multi-adapter operation, indicates which physical adapter
            /// of the device this operation applies to.
            /// </summary>
            unsigned int NodeIndex;

            /// <summary>
            /// An input parameter indicating the size of the pTypes array. This must match the
            /// count returned through the D3D12FeatureDataProtectedResourceSessionTypeCount query.
            /// </summary>
            unsigned int Count;

            /// <summary>
            /// An output parameter containing an array populated with the supported protected
            /// resource session types.
            /// </summary>
            Guid* pTypes;

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="nodeIndex">An input parameter which, in multi-adapter operation,
            /// indicates which physical adapter of the device this operation applies to.</param>
            /// <param name="buffer">A buffer array that will contain the supported protected resource
            /// session types.</param>
            /// <param name="bufferPtr">Returns pin pointer to the first element of the buffer.
            /// If you finish to use the struct, you must free the handle.</param>
            D3D12FeatureDataProtectedResourceSessionTypes(
                unsigned int nodeIndex, array<Guid>^ buffer, [Out] GCHandle% bufferPtr);
        };

        /// <summary>
        /// Indicates the level of support that the adapter provides for metacommands.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataQueryMetaCommand : ID3D12FeatureData
        {
            /// <summary>
            /// The fixed GUID that identifies the metacommand to query about.
            /// </summary>
            Guid CommandId;

            /// <summary>
            /// For single GPU operation, this is zero. If there are multiple GPU nodes, a bit is set
            /// to identify a node (the device's physical adapter). Each bit in the mask corresponds to
            /// a single node.
            /// </summary>
            unsigned int NodeMask;

            /// <summary>
            /// A pointer to a buffer containing the query input data. Allocate
            /// QueryInputDataSizeInBytes bytes.
            /// </summary>
            void* pQueryInputData;

            /// <summary>
            /// The size of the buffer pointed to by pQueryInputData, in bytes.
            /// </summary>
            SIZE_T QueryInputDataSizeInBytes;

            /// <summary>
            /// A pointer to a buffer containing the query output data.
            /// </summary>
            void* pQueryOutputData;

            /// <summary>
            /// The size of the buffer pointed to by pQueryOutputData, in bytes.
            /// </summary>
            SIZE_T QueryOutputDataSizeInBytes;
        };

        /// <summary>
        /// Indicates root signature version support.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataRootSignature : ID3D12FeatureData
        {
            /// <summary>
            /// On input, specifies the highest version D3DRootSignatureVersion to check for. On
            /// output specifies the highest version, up to the input version specified, actually
            /// available.
            /// </summary>
            D3DRootSignatureVersion HighestVersion;

            D3D12FeatureDataRootSignature(D3DRootSignatureVersion highestVersion);
        };

        /// <summary>
        /// Indicates the level of support for heap serialization.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataSerialization : ID3D12FeatureData
        {
            /// <summary>
            /// An input field, indicating the adapter index to query.
            /// </summary>
            unsigned int NodeIndex;

            /// <summary>
            /// An output field, indicating the tier of heap serialization support.
            /// </summary>
            D3D12HeapSerializationTier HeapSerializationTier;

            D3D12FeatureDataSerialization(unsigned int nodeIndex);
        };

        /// <summary>
        /// Describes the level of shader caching supported in the current graphics driver.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataShaderCache : ID3D12FeatureData
        {
            /// <summary>
            /// Indicates the level of caching supported.
            /// </summary>
            D3D12ShaderCacheSupportFlags SupportFlags;
        };

        /// <summary>
        /// Contains the supported shader model.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12FeatureDataShaderModel : ID3D12FeatureData
        {
            /// <summary>
            /// Specifies one member of D3DShaderModel that indicates the maximum supported
            /// shader model.
            /// </summary>
            D3DShaderModel HighestShaderModel;

            D3D12FeatureDataShaderModel(D3DShaderModel highestShaderModel);
        };

        /// <summary>
        /// Describes a constant buffer to view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ConstantBufferViewDesc
        {
            /// <summary>
            /// The D3D12_GPU_VIRTUAL_ADDRESS of the constant buffer.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;

            /// <summary>
            /// The size in bytes of the constant buffer.
            /// </summary>
            unsigned int SizeInBytes;
        };

        /// <summary>
        /// Describes a CPU descriptor handle.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12CPUDescriptorHandle : IEquatable<D3D12CPUDescriptorHandle>
        {
            /// <summary>
            /// The address of the descriptor.
            /// </summary>
            SIZE_T ptr;

            /// <summary>
            /// Creates a new instance of a D3D12CPUDescriptorHandle, initialized with default
            /// parameters (pointer set to zero).
            /// </summary>
            /// <param name="">Use D3D12::Default</param>
            D3D12CPUDescriptorHandle(D3DDefault);

            /// <summary>
            /// Creates a new instance of a D3D12CPUDescriptorHandle.
            /// </summary>
            /// <param name="other">Address used in initialization.</param>
            /// <param name="offsetScaledByIncrementSize">Offset from the other address.</param>
            D3D12CPUDescriptorHandle(D3D12CPUDescriptorHandle other, int offsetScaledByIncrementSize);

            /// <summary>
            /// Creates a new instance of a D3D12CPUDescriptorHandle.
            /// </summary>
            /// <param name="other">Address used in initialization.</param>
            /// <param name="offsetInDescriptors">The number of descriptors by which to increment. from
            /// other address.</param>
            /// <param name="descriptorIncrementSize">The amount by which to increment for
            /// each descriptor, including padding.</param>
            D3D12CPUDescriptorHandle(
                D3D12CPUDescriptorHandle other, int offsetInDescriptors,
                unsigned int descriptorIncrementSize
            );

            /// <summary>
            /// Sets the offset based on the specified number of descriptors and how much to increment
            /// for each descriptor.
            /// </summary>
            /// <param name="offsetInDescriptors">The number of descriptors by which to increment.</param>
            /// <param name="descriptorIncrementSize">The amount by which to increment for each
            /// descriptor, including padding.</param>
            void Offset(int offsetInDescriptors, unsigned int descriptorIncrementSize);

            /// <summary>
            /// Sets the offset based on the specified number of increments.
            /// </summary>
            /// <param name="offsetScaledByIncrementSize">The number of increments by which to offset.
            /// </param>
            void Offset(int offsetScaledByIncrementSize);

            static bool operator==(D3D12CPUDescriptorHandle lhs, D3D12CPUDescriptorHandle rhs);

            static bool operator!=(D3D12CPUDescriptorHandle lhs, D3D12CPUDescriptorHandle rhs);

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3D12CPUDescriptorHandle other);

            /// <summary>
            /// Initializes a D3D12CPUDescriptorHandle structure
            /// </summary>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetScaledByIncrementSize">Offset from the base address.</param>
            void InitOffsetted(
                [In][IsReadOnly] D3D12CPUDescriptorHandle% base, int offsetScaledByIncrementSize
            );

            /// <summary>
            /// Initializes a D3D12CPUDescriptorHandle structure with an offset, using the
            /// specified number of descriptors of the given size.
            /// </summary>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetInDescriptors">The number of descriptors by which to increment. from
            /// other address.</param>
            /// <param name="descriptorIncrementSize">The amount by which to increment for
            /// each descriptor, including padding.</param>
            void InitOffsetted(
                [In][IsReadOnly] D3D12CPUDescriptorHandle% base, int offsetInDescriptors,
                unsigned int descriptorIncrementSize
            );

            /// <summary>
            /// Initializes a D3D12CPUDescriptorHandle structure with an offset, using the
            /// specified number of descriptors of the given size.
            /// </summary>
            /// <param name="handle">Structure to initialize.</param>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetScaledByIncrementSize">Offset from the base address.</param>
            static void InitOffsetted(
                D3D12CPUDescriptorHandle% handle, [In][IsReadOnly] D3D12CPUDescriptorHandle% base,
                int offsetScaledByIncrementSize
            );

            /// <summary>
            /// Initializes a D3D12CPUDescriptorHandle structure with an offset, using the
            /// specified number of descriptors of the given size.
            /// </summary>
            /// <param name="handle">Structure to initialize.</param>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetInDescriptors">The number of descriptors by which to increment. from
            /// other address.</param>
            /// <param name="descriptorIncrementSize">The amount by which to increment for
            /// each descriptor, including padding.</param>
            static void InitOffsetted(
                D3D12CPUDescriptorHandle% handle, [In][IsReadOnly] D3D12CPUDescriptorHandle% base,
                int offsetInDescriptors, unsigned int descriptorIncrementSize
            );
        };

        /// <summary>
        /// Describes a command queue.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12CommandQueueDesc
        {
            /// <summary>
            /// Specifies one member of D3D12CommandListType.
            /// </summary>
            D3D12CommandListType Type;

            /// <summary>
            /// The priority for the command queue, as a D3D12CommandQueuePriority enumeration
            /// constant to select normal or high priority.
            /// </summary>
            int Priority;

            /// <summary>
            /// Specifies any flags from the D3D12CommandQueueFlags enumeration.
            /// </summary>
            D3D12CommandQueueFlags Flags;

            /// <summary>
            /// For single GPU operation, set this to zero. If there are multiple GPU nodes, set a bit
            /// to identify the node (the device's physical adapter) to which the command queue applies.
            /// Each bit in the mask corresponds to a single node. Only 1 bit must be set.
            /// </summary>
            unsigned int NodeMask;
        };

        /// <summary>
        /// Describes a memory range.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Range
        {
            /// <summary>
            /// The offset, in bytes, denoting the beginning of a memory range.
            /// </summary>
            SIZE_T Begin;

            /// <summary>
            /// The offset, in bytes, denoting the end of a memory range. End is one-past-the-end.
            /// </summary>
            SIZE_T End;

            D3D12Range(SIZE_T begin, SIZE_T end);
        };

        /// <summary>
        /// Describes parameters needed to allocate resources.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ResourceAllocationInfo
        {
            /// <summary>
            /// The size, in bytes, of the resource.
            /// </summary>
            unsigned long long SizeInBytes;

            /// <summary>
            /// The alignment value for the resource; one of 4KB (4096), 64KB (65536), or 4MB
            /// (4194304) alignment.
            /// </summary>
            unsigned long long Alignment;
        };

        /// <summary>
        /// Describes a resource, such as a texture. This structure is used extensively.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ResourceDesc : IEquatable<D3D12ResourceDesc>
        {
            /// <summary>
            /// One member of D3D12ResourceDimension, specifying the dimensions of the resource
            /// (for example, Texture1D), or whether it is a buffer (Buffer).
            /// </summary>
            D3D12ResourceDimension Dimension;

            /// <summary>
            /// Specifies the alignment.
            /// </summary>
            unsigned long long Alignment;

            /// <summary>
            /// Specifies the width of the resource.
            /// </summary>
            unsigned long long Width;

            /// <summary>
            /// Specifies the height of the resource.
            /// </summary>
            unsigned int Height;

            /// <summary>
            /// Specifies the depth of the resource, if it is 3D, or the array size if it is an array
            /// of 1D or 2D resources.
            /// </summary>
            unsigned short DepthOrArraySize;

            /// <summary>
            /// Specifies the number of MIP levels.
            /// </summary>
            unsigned short MipLevels;

            /// <summary>
            /// Specifies one member of DXGIFormat.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// Specifies a DXGISampleDesc structure.
            /// </summary>
            DXGISampleDesc SampleDesc;

            /// <summary>
            /// Specifies one member of D3D12TextureLayout.
            /// </summary>
            D3D12TextureLayout Layout;

            /// <summary>
            /// Bitwise-OR'd flags, as D3D12ResourceFlags enumeration constants.
            /// </summary>
            D3D12ResourceFlags Flags;

            /// <summary>
            /// Creates a new instance of a D3D12ResourceDesc
            /// </summary>
            D3D12ResourceDesc(
                D3D12ResourceDimension dimension,
                unsigned long long alignment,
                unsigned long long width,
                unsigned int height,
                unsigned short depthOrArraySize,
                unsigned short mipLevels,
                DXGIFormat format,
                unsigned int sampleCount,
                unsigned int sampleQuality,
                D3D12TextureLayout layout,
                D3D12ResourceFlags flags
            );

            /// <summary>
            /// Initialize the desc as a buffer.
            /// </summary>
            /// <param name="resAllocInfo">Allignment and width of the buffer.</param>
            /// <param name="flags">Optional flags of the desc.</param>
            /// <returns>Buffer description structure.</returns>
            static D3D12ResourceDesc Buffer(
                D3D12ResourceAllocationInfo resAllocInfo,
                [Optional] Nullable<D3D12ResourceFlags> flags
            );

            /// <summary>
            /// Initialize the desc as a buffer.
            /// </summary>
            /// <param name="width">Width of the buffer.</param>
            /// <param name="flags">Optional flags of the desc.</param>
            /// <param name="alignment">Optional alignment of the buffer.</param>
            /// <returns>Buffer description structure.</returns>
            static D3D12ResourceDesc Buffer(
                unsigned long long width,
                [Optional] Nullable<D3D12ResourceFlags> flags,
                [Optional] Nullable<unsigned long long> alignment
            );

            /// <summary>
            /// Initialize the desc as a 1D-texture.
            /// </summary>
            /// <returns>Texture1D description structure.</returns>
            static D3D12ResourceDesc Tex1D(
                DXGIFormat format,
                unsigned long long width,
                [Optional] Nullable<unsigned short> arraySize,
                [Optional] Nullable<unsigned short> mipLevels,
                [Optional] Nullable<D3D12ResourceFlags> flags,
                [Optional] Nullable<D3D12TextureLayout> layout,
                [Optional] Nullable<unsigned long long> alignment
            );

            /// <summary>
            /// Initialize the desc as a 2D-texture.
            /// </summary>
            /// <returns>Texture2D description structure.</returns>
            static D3D12ResourceDesc Tex2D(
                DXGIFormat format,
                unsigned long long width,
                unsigned int height,
                [Optional] Nullable<unsigned short> arraySize,
                [Optional] Nullable<unsigned short> mipLevels,
                [Optional] Nullable<unsigned int> sampleCount,
                [Optional] Nullable<unsigned int> sampleQuality,
                [Optional] Nullable<D3D12ResourceFlags> flags,
                [Optional] Nullable<D3D12TextureLayout> layout,
                [Optional] Nullable<unsigned long long> alignment
            );

            /// <summary>
            /// Initialize the desc as a 3D-texture.
            /// </summary>
            /// <returns>Texture3D description structure.</returns>
            static D3D12ResourceDesc Tex3D(
                DXGIFormat format,
                unsigned long long width,
                unsigned int height,
                unsigned short depth,
                [Optional] Nullable<unsigned short> mipLevels,
                [Optional] Nullable<D3D12ResourceFlags> flags,
                [Optional] Nullable<D3D12TextureLayout> layout,
                [Optional] Nullable<unsigned long long> alignment
            );

            /// <summary>
            /// If Dimension is Texture3D, returns DepthOrArraySize. Else, returns 1.
            /// </summary>
            property unsigned short Depth
            {
                unsigned short get();
            }

            /// <summary>
            /// If Dimension is not Texture3D, returns DepthOrArraySize. Else, returns 1.
            /// </summary>
            property unsigned short ArraySize
            {
                unsigned short get();
            }

            /// <summary>
            /// Returns D3D12::GetFormatPlaneCount(device, Format).
            /// </summary>
            /// <returns>Plane count.</returns>
            unsigned char PlaneCount(D3D12Device^ device);

            /// <summary>
            /// Returns the number of subresources.
            /// </summary>
            /// <param name="device">The virtual adapter (an ID3D12Device) for which to get the number
            /// of subresources.</param>
            /// <returns>The number of subresources.</returns>
            unsigned int Subresources(D3D12Device^ device);

            /// <summary>
            /// Calculates a subresource index by using D3D12::CalcSubresource.
            /// </summary>
            /// <returns>Subresource index</returns>
            unsigned int CalcSubresource(
                unsigned int mipSlice, unsigned int arraySlice, unsigned int planeSlice);

            static bool operator==(
                [In][IsReadOnly] D3D12ResourceDesc% l,
                [In][IsReadOnly] D3D12ResourceDesc% r
                );

            static bool operator!=(
                [In][IsReadOnly] D3D12ResourceDesc% l,
                [In][IsReadOnly] D3D12ResourceDesc% r
                );

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3D12ResourceDesc other);
        };

        /// <summary>
        /// Describes a 3D box.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Box : IEquatable<D3D12Box>
        {
            /// <summary>
            /// The x position of the left hand side of the box.
            /// </summary>
            unsigned int left;

            /// <summary>
            /// The y position of the top of the box.
            /// </summary>
            unsigned int top;

            /// <summary>
            /// The z position of the front of the box.
            /// </summary>
            unsigned int front;

            /// <summary>
            /// The x position of the right hand side of the box, plus 1. This means that
            /// right - left equals the width of the box.
            /// </summary>
            unsigned int right;

            /// <summary>
            /// The y position of the bottom of the box, plus 1. This means that bottom - top equals
            /// the height of the box.
            /// </summary>
            unsigned int bottom;

            /// <summary>
            /// The z position of the back of the box, plus 1. This means that back - front equals
            /// the depth of the box.
            /// </summary>
            unsigned int back;

            /// <summary>
            /// Creates a box with left and right coordinates and top and front are 0 with bottom and
            /// back are 1.
            /// </summary>
            D3D12Box(unsigned int left, unsigned int right);

            /// <summary>
            /// Creates a box with left, top, right, and bottom coordinates and front is 0 with back is 1.
            /// </summary>
            D3D12Box(unsigned int left, unsigned int top, unsigned int right, unsigned int bottom);

            /// <summary>
            /// Creates a box.
            /// </summary>
            D3D12Box(unsigned int left, unsigned int top, unsigned int front,
                     unsigned int right, unsigned int bottom, unsigned int back);

            static bool operator==(
                [In][IsReadOnly] D3D12Box% l,
                [In][IsReadOnly] D3D12Box% r
                );

            static bool operator!=(
                [In][IsReadOnly] D3D12Box% l,
                [In][IsReadOnly] D3D12Box% r
                );

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3D12Box other);
        };

        /// <summary>
        /// Describes heap properties.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12HeapProperties : IEquatable<D3D12HeapProperties>
        {
            /// <summary>
            /// A D3D12HeapType-typed value that specifies the type of heap.
            /// </summary>
            D3D12HeapType Type;

            /// <summary>
            /// A D3D12CPUPageProperty-typed value that specifies the CPU-page properties for the heap.
            /// </summary>
            D3D12CPUPageProperty CPUPageProperty;

            /// <summary>
            /// A D3D12MemoryPool-typed value that specifies the memory pool for the heap.
            /// </summary>
            D3D12MemoryPool MemoryPoolPreference;

            /// <summary>
            /// For multi-adapter operation, this indicates the node where the resource should be created.
            /// </summary>
            unsigned int CreationNodeMask;

            /// <summary>
            /// For multi-adapter operation, this indicates the set of nodes where the resource
            /// is visible.
            /// </summary>
            unsigned int VisibleNodeMask;

            /// <summary>
            /// Creates a custom heap property.
            /// </summary>
            /// <param name="cpuPageProperty">CPU page property</param>
            /// <param name="memoryPoolPreference">Memory pool preference</param>
            /// <param name="creationNodeMask">Creation node mask. Default value is 1.</param>
            /// <param name="nodeMask">Visible node mask. Default value is 1.</param>
            D3D12HeapProperties(
                D3D12CPUPageProperty cpuPageProperty,
                D3D12MemoryPool memoryPoolPreference,
                [Optional] Nullable<unsigned int> creationNodeMask,
                [Optional] Nullable<unsigned int> nodeMask
            );

            /// <summary>
            /// Creates a heap property with unknown page property and memory pool.
            /// </summary>
            /// <param name="type">Type of the heap</param>
            /// <param name="creationNodeMask">Creation node mask. Default value is 1.</param>
            /// <param name="nodeMask">Visible node mask. Default value is 1.</param>
            D3D12HeapProperties(
                D3D12HeapType type,
                [Optional] Nullable<unsigned int> creationNodeMask,
                [Optional] Nullable<unsigned int> nodeMask
            );

            /// <summary>
            /// Gets whether the heap can be accessed by CPU.
            /// </summary>
            property bool IsCPUAccessible
            {
                bool get();
            }

            static bool operator==(
                [In][IsReadOnly] D3D12HeapProperties% l,
                [In][IsReadOnly] D3D12HeapProperties% r
                );

            static bool operator!=(
                [In][IsReadOnly] D3D12HeapProperties% l,
                [In][IsReadOnly] D3D12HeapProperties% r
                );

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3D12HeapProperties other);
        };

        /// <summary>
        /// Describes a heap.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12HeapDesc : IEquatable<D3D12HeapDesc>
        {
            /// <summary>
            /// Defined as 64KB.
            /// </summary>
            literal unsigned long long DefaultResourcePlacementAlignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;

            /// <summary>
            /// Defined as 4MB. An application must decide whether the heap will contain
            /// multi-sample anti-aliasing (MSAA), in which case, the application must choose
            /// DefaultMSAAResourcePlacementAlignment.
            /// </summary>
            literal unsigned long long DefaultMSAAResourcePlacementAlignment = D3D12_DEFAULT_MSAA_RESOURCE_PLACEMENT_ALIGNMENT;

            /// <summary>
            /// The size, in bytes, of the heap. To avoid wasting memory, applications should pass
            /// SizeInBytes values which are multiples of the effective Alignment; but non-aligned
            /// SizeInBytes is also supported, for convenience. To find out how large a heap must be
            /// to support textures with undefined layouts and adapter-specific sizes, call
            /// D3D12Device::GetResourceAllocationInfo.
            /// </summary>
            unsigned long long SizeInBytes;

            /// <summary>
            /// A D3D12HeapProperties structure that describes the heap properties.
            /// </summary>
            D3D12HeapProperties Properties;

            /// <summary>
            /// The alignment value for the heap.
            /// </summary>
            unsigned long long Alignment;

            /// <summary>
            /// A combination of D3D12HeapFlags-typed values that are combined by using a bitwise-OR
            /// operation. The resulting value identifies heap options. When creating heaps to
            /// support adapters with resource heap tier 1, an application must choose some flags.
            /// </summary>
            D3D12HeapFlags Flags;

            /// <summary>
            /// Initialize heap description with given size and properties.
            /// </summary>
            /// <param name="size">Size of the heap.</param>
            /// <param name="properties">Properties of the heap.</param>
            /// <param name="alignment">Optional alignment. The default value is 0.</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                unsigned long long size,
                [In][IsReadOnly] D3D12HeapProperties% properties,
                [Optional] Nullable<unsigned long long> alignment,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Initialize heap description with given size and type.
            /// </summary>
            /// <param name="size">Size of the heap.</param>
            /// <param name="type">Type of the heap.</param>
            /// <param name="alignment">Optional alignment. The default value is 0.</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                unsigned long long size,
                D3D12HeapType type,
                [Optional] Nullable<unsigned long long> alignment,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Initialize heap description with given size and cpu page property and memory pool.
            /// </summary>
            /// <param name="size">Size of the heap.</param>
            /// <param name="cpuPageProperty">CPU page property.</param>
            /// <param name="memoryPoolPreference">Memory pool preference.</param>
            /// <param name="alignment">Optional alignment. The default value is 0.</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                unsigned long long size,
                D3D12CPUPageProperty cpuPageProperty,
                D3D12MemoryPool memoryPoolPreference,
                [Optional] Nullable<unsigned long long> alignment,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Initialize heap description with given resource allocation info and heap properties.
            /// </summary>
            /// <param name="resAllocInfo">Resource allocation info</param>
            /// <param name="properties">Heap properties</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                [In][IsReadOnly] D3D12ResourceAllocationInfo% resAllocInfo,
                [In][IsReadOnly] D3D12HeapProperties% properties,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Initialize heap description with given resource allocation info and heap type.
            /// </summary>
            /// <param name="resAllocInfo">Resource allocation info</param>
            /// <param name="type">Type of the heap.</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                [In][IsReadOnly] D3D12ResourceAllocationInfo% resAllocInfo,
                D3D12HeapType type,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Initialize heap description with given resource allocation info and cpu page property
            /// and memory pool.
            /// </summary>
            /// <param name="resAllocInfo">Resource allocation info</param>
            /// <param name="cpuPageProperty">CPU page property.</param>
            /// <param name="memoryPoolPreference">Memory pool preference.</param>
            /// <param name="flags">Optional flags. The default value is D3D12HeapFlags::None.</param>
            D3D12HeapDesc(
                [In][IsReadOnly] D3D12ResourceAllocationInfo% resAllocInfo,
                D3D12CPUPageProperty cpuPageProperty,
                D3D12MemoryPool memoryPoolPreference,
                [Optional] Nullable<D3D12HeapFlags> flags
            );

            /// <summary>
            /// Gets whether the heap can be accessed by CPU.
            /// </summary>
            property bool IsCPUAccessible
            {
                bool get();
            }

            static bool operator==(
                [In][IsReadOnly] D3D12HeapDesc% l,
                [In][IsReadOnly] D3D12HeapDesc% r
                );

            static bool operator!=(
                [In][IsReadOnly] D3D12HeapDesc% l,
                [In][IsReadOnly] D3D12HeapDesc% r
                );

            virtual bool Equals(Object^ obj) override;

            virtual bool Equals(D3D12HeapDesc other);
        };

        /// <summary>
        /// Describes the coordinates of a tiled resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12TiledResourceCoordinate
        {
            /// <summary>
            /// The x-coordinate of the tiled resource.
            /// </summary>
            unsigned int X;

            /// <summary>
            /// The y-coordinate of the tiled resource.
            /// </summary>
            unsigned int Y;

            /// <summary>
            /// The z-coordinate of the tiled resource.
            /// </summary>
            unsigned int Z;

            /// <summary>
            /// The index of the subresource for the tiled resource.
            /// For mipmaps that use nonstandard tiling, or are packed, or both use nonstandard tiling
            /// and are packed, any subresource value that indicates any of the packed mipmaps all refer
            /// to the same tile.Additionally, the X coordinate is used to indicate a tile within the
            /// packed mip region, rather than a logical region of a single subresource.The Yand Z
            /// coordinates must be zero.
            /// </summary>
            unsigned int Subresource;

            D3D12TiledResourceCoordinate(
                unsigned int x, unsigned int y, unsigned int z, unsigned int subresource);
        };

        /// <summary>
        /// Describes the size of a tiled region.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12TileRegionSize
        {
            /// <summary>
            /// The number of tiles in the tiled region.
            /// </summary>
            unsigned int NumTiles;

            /// <summary>
            /// Specifies whether the runtime uses the Width, Height, and Depth members to define
            /// the region.
            /// If True, the runtime uses the Width, Height, and Depth members to define the region.
            /// In this case, NumTiles should be equal to Width * Height * Depth.
            /// If False, the runtime ignores the Width, Height, and Depth membersand uses the NumTiles
            /// member to traverse tiles in the resource linearly across x, then y, then z(as applicable)
            /// and then spills over mipmaps / arrays in subresource order.For example, use this technique
            /// to map an entire resource at once.
            /// Regardless of whether you specify True or False for UseBox, you use a
            /// D3D12TiledResourceCoordinate structure to specify the starting location for the
            /// region within the resource as a separate parameter outside of this structure by using
            /// x, y, and z coordinates.
            /// When the region includes mipmaps that are packed with nonstandard tiling, UseBox must
            /// be False because tile dimensions are not standard and the app only knows a count of
            /// how many tiles are consumed by the packed area, which is per array slice. The
            /// corresponding(separate) starting location parameter uses x to offset into the flat
            /// range of tiles in this case, and yand z coordinates must each be 0.
            /// </summary>
            CBool UseBox;

            /// <summary>
            /// The width of the tiled region, in tiles. Used for buffer and 1D, 2D, and 3D textures.
            /// </summary>
            unsigned int Width;

            /// <summary>
            /// The height of the tiled region, in tiles. Used for 2D and 3D textures.
            /// </summary>
            unsigned short Height;

            /// <summary>
            /// The depth of the tiled region, in tiles. Used for 3D textures or arrays. For arrays,
            /// used for advancing in depth jumps to next slice of same mipmap size, which isn't
            /// contiguous in the subresource counting space if there are multiple mipmaps.
            /// </summary>
            unsigned short Depth;

            D3D12TileRegionSize(
                unsigned int numTiles,
                bool useBox,
                unsigned int width,
                unsigned short height,
                unsigned short depth
            );
        };

        /// <summary>
        /// Describes shader data.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ShaderBytecode
        {
            /// <summary>
            /// A pointer to a memory block that contains the shader data.
            /// </summary>
            IntPtr pShaderBytecode;

            /// <summary>
            /// The size, in bytes, of the shader data that the pShaderBytecode member points to.
            /// </summary>
            SIZE_T BytecodeLength;

            /// <summary>
            /// Initializes the structure with shader blob.
            /// </summary>
            /// <param name="shaderBlob">Blob that contains the shader byte code.</param>
            D3D12ShaderBytecode(D3D10Blob^ shaderBlob);

            D3D12ShaderBytecode(IntPtr pShaderBytecode, SIZE_T bytecodeLength);
        };

        /// <summary>
        /// Describes a vertex element in a vertex buffer in an output slot.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12SODeclarationEntry
        {
            /// <summary>
            /// Zero-based, stream number.
            /// </summary>
            unsigned int Stream;

            /// <summary>
            /// Type of output element; possible values include: "POSITION", "NORMAL", or "TEXCOORD0".
            /// Note that if SemanticName is null then ComponentCount can be greater than 4 and the
            /// described entry will be a gap in the stream out where no data will be written.
            /// </summary>
            LPSTR SemanticName;

            /// <summary>
            /// Output element's zero-based index. Use, for example, if you have more than one
            /// texture coordinate stored in each vertex.
            /// </summary>
            unsigned int SemanticIndex;

            /// <summary>
            /// The component of the entry to begin writing out to. Valid values are 0 to 3. For
            /// example, if you only wish to output to the y and z components of a position,
            /// StartComponent is 1 and ComponentCount is 2.
            /// </summary>
            BYTE StartComponent;

            /// <summary>
            /// The number of components of the entry to write out to. Valid values are 1 to 4. For
            /// example, if you only wish to output to the y and z components of a position,
            /// StartComponent is 1 and ComponentCount is 2. Note that if SemanticName is null then
            /// ComponentCount can be greater than 4 and the described entry will be a gap in the stream
            /// out where no data will be written.
            /// </summary>
            BYTE ComponentCount;

            /// <summary>
            /// The associated stream output buffer that is bound to the pipeline. The valid range
            /// for OutputSlot is 0 to 3.
            /// </summary>
            BYTE OutputSlot;

            /// <summary>
            /// Initialize the structure.
            /// </summary>
            /// <param name="semanticNameHandle">Handle to the marshal context that is needed
            /// for SemanticName. Free the handle after finishing using this structure.</param>
            D3D12SODeclarationEntry(
                unsigned int stream,
                String^ semanticName,
                unsigned int semanticIndex,
                BYTE startComponent,
                BYTE componentCount,
                BYTE outputSlot,
                [Out] GCHandle% semanticNameHandle
            );
        };

        /// <summary>
        /// Describes a streaming output buffer.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12StreamOutputDesc
        {
            /// <summary>
            /// A pointer to an array of D3D12SODeclarationEntry structures. Can't be null if
            /// NumEntries > 0.
            /// </summary>
            D3D12SODeclarationEntry* pSODeclaration;

            /// <summary>
            /// The number of entries in the stream output declaration array that the
            /// pSODeclaration member points to.
            /// </summary>
            unsigned int NumEntries;

            /// <summary>
            /// A pointer to an array of buffer strides; each stride is the size of an element for
            /// that buffer.
            /// </summary>
            unsigned int* pBufferStrides;

            /// <summary>
            /// The number of strides (or buffers) that the pBufferStrides member points to.
            /// </summary>
            unsigned int NumStrides;

            /// <summary>
            /// The index number of the stream to be sent to the rasterizer stage.
            /// </summary>
            unsigned int RasterizedStream;

            /// <summary>
            /// Initializes the structure.
            /// </summary>
            /// <param name="soDeclaration">An array of D3D12SODeclarationEntry structures. If not
            /// needed, this can be null.</param>
            /// <param name="bufferStrides">An array of buffer strides. If not needed, this can be null.
            /// </param>
            /// <param name="rasterizedStream">The index number of the stream to be sent to the
            /// rasterizer stage.</param>
            /// <param name="soDeclarationPinPtr">The pin pointer to soDeclaration. If soDeclaration is
            /// null, the handle is not allocated. Else, free the handle after using the structure.
            /// </param>
            /// <param name="bufferStridesPinPtr">The pin pointer to bufferStrides. If bufferStrides is
            /// null, the handle is not allocated. Else, free the handle after using the structure.
            /// </param>
            D3D12StreamOutputDesc(
                array<D3D12SODeclarationEntry>^ soDeclaration,
                array<unsigned int>^ bufferStrides,
                unsigned int rasterizedStream,
                [Out] GCHandle% soDeclarationPinPtr,
                [Out] GCHandle% bufferStridesPinPtr
            );
        };

        /// <summary>
        /// Describes the blend state for a render target.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RenderTargetBlendDesc
        {
            /// <summary>
            /// Specifies whether to enable (or disable) blending. Set to True to enable blending.
            /// </summary>
            CBool BlendEnable;

            /// <summary>
            /// Specifies whether to enable (or disable) a logical operation. Set to True to enable
            /// a logical operation.
            /// It's not valid for LogicOpEnable and BlendEnable to both be True.
            /// </summary>
            CBool LogicOpEnable;

            /// <summary>
            /// A D3D12Blend-typed value that specifies the operation to perform on the RGB value that
            /// the pixel shader outputs. The BlendOp member defines how to combine the SrcBlend
            /// and DestBlend operations.
            /// </summary>
            D3D12Blend SrcBlend;

            /// <summary>
            /// A D3D12Blend-typed value that specifies the operation to perform on the current RGB
            /// value in the render target. The BlendOp member defines how to combine the SrcBlend
            /// and DestBlend operations.
            /// </summary>
            D3D12Blend DestBlend;

            /// <summary>
            /// A D3D12BlendOp-typed value that defines how to combine the SrcBlend and
            /// DestBlend operations.
            /// </summary>
            D3D12BlendOp BlendOp;

            /// <summary>
            /// A D3D12Blend-typed value that specifies the operation to perform on the alpha value
            /// that the pixel shader outputs. Blend options that end in _COLOR are not allowed.
            /// The BlendOpAlpha member defines how to combine the SrcBlendAlpha and
            /// DestBlendAlpha operations.
            /// </summary>
            D3D12Blend SrcBlendAlpha;

            /// <summary>
            /// A D3D12Blend-typed value that specifies the operation to perform on the current
            /// alpha value in the render target. Blend options that end in _COLOR are not allowed.
            /// The BlendOpAlpha member defines how to combine the SrcBlendAlpha and DestBlendAlpha
            /// operations.
            /// </summary>
            D3D12Blend DestBlendAlpha;

            /// <summary>
            /// A D3D12BlendOp-typed value that defines how to combine the SrcBlendAlpha
            /// and DestBlendAlpha operations.
            /// </summary>
            D3D12BlendOp BlendOpAlpha;

            /// <summary>
            /// A D3D12LogicOp-typed value that specifies the logical operation to configure for
            /// the render target.
            /// </summary>
            D3D12LogicOp LogicOp;

            /// <summary>
            /// A combination of D3D12_COLOR_WRITE_ENABLE-typed values that are combined by using
            /// a bitwise OR operation. The resulting value specifies a write mask.
            /// </summary>
            D3D12ColorWriteEnable RenderTargetWriteMask;

            /// <summary>
            /// Initializes the structure to default value(disable blend and logic operaions.
            /// </summary>
            D3D12RenderTargetBlendDesc(D3DDefault);
        };

        /// <summary>
        /// Describes the blend state.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12BlendDesc
        {
            /// <summary>
            /// Specifies whether to use alpha-to-coverage as a multisampling technique when setting
            /// a pixel to a render target.
            /// </summary>
            CBool AlphaToCoverageEnable;

            /// <summary>
            /// Specifies whether to enable independent blending in simultaneous render targets.
            /// Set to True to enable independent blending. If set to False, only the RenderTarget0
            /// members are used; RenderTarget1...7 are ignored.
            /// </summary>
            CBool IndependentBlendEnable;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 0.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget0;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 1.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget1;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 2.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget2;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 3.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget3;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 4.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget4;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 5.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget5;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 6.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget6;

            /// <summary>
            /// An D3D12RenderTargetBlendDesc structure that describe the blend state for render
            /// target 7.
            /// </summary>
            D3D12RenderTargetBlendDesc RenderTarget7;

            /// <summary>
            /// Gets and sets the render target blend description at specified index. The index is
            /// from 0 to 7.
            /// </summary>
            property D3D12RenderTargetBlendDesc default[int]
            {
                D3D12RenderTargetBlendDesc get(int index);
                void set(int index, D3D12RenderTargetBlendDesc value);
            }

                /// <summary>
                /// Creates a new instance of a D3D12BlendDesc, initialized with default parameters.
                /// </summary>
            D3D12BlendDesc(D3DDefault);
        };

        /// <summary>
        /// Describes rasterizer state.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RasterizerDesc
        {
            /// <summary>
            /// A D3D12FillMode-typed value that specifies the fill mode to use when rendering.
            /// </summary>
            D3D12FillMode FillMode;

            /// <summary>
            /// A D3D12CullMode-typed value that specifies that triangles facing the specified
            /// direction are not drawn.
            /// </summary>
            D3D12CullMode CullMode;

            /// <summary>
            /// Determines if a triangle is front- or back-facing. If this member is True, a triangle
            /// will be considered front-facing if its vertices are counter-clockwise on the render
            /// target and considered back-facing if they are clockwise. If this parameter is False,
            /// the opposite is true.
            /// </summary>
            CBool FrontCounterClockwise;

            /// <summary>
            /// Depth value added to a given pixel.
            /// </summary>
            int DepthBias;

            /// <summary>
            /// Maximum depth bias of a pixel.
            /// </summary>
            float DepthBiasClamp;

            /// <summary>
            /// Scalar on a given pixel's slope.
            /// </summary>
            float SlopeScaledDepthBias;

            /// <summary>
            /// Specifies whether to enable clipping based on distance. The hardware always performs x
            /// and y clipping of rasterized coordinates. When DepthClipEnable is set to the
            /// default–True, the hardware also clips the z value.
            /// </summary>
            CBool DepthClipEnable;

            /// <summary>
            /// Specifies whether to use the quadrilateral or alpha line anti-aliasing algorithm
            /// on multisample antialiasing (MSAA) render targets. Set to True to use the
            /// quadrilateral line anti-aliasing algorithm and to False to use the alpha line
            /// anti-aliasing algorithm.
            /// </summary>
            CBool MultisampleEnable;

            /// <summary>
            /// Specifies whether to enable line antialiasing; only applies if doing line drawing
            /// and MultisampleEnable is False.
            /// </summary>
            CBool AntialiasedLineEnable;

            /// <summary>
            /// The sample count that is forced while UAV rendering or rasterizing. Valid values are
            /// 0, 1, 2, 4, 8, and optionally 16. 0 indicates that the sample count is not forced.
            /// </summary>
            unsigned int ForcedSampleCount;

            /// <summary>
            /// A D3D12ConservativeRasterizationMode-typed value that identifies whether
            /// conservative rasterization is on or off.
            /// </summary>
            D3D12ConservativeRasterizationMode ConservativeRaster;

            /// <summary>
            /// Creates a new instance of a D3D12RasterizerDesc, initialized with default parameters.
            /// </summary>
            D3D12RasterizerDesc(D3DDefault);
        };

        /// <summary>
        /// Describes stencil operations that can be performed based on the results of stencil test.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DepthStencilOpDesc
        {
            /// <summary>
            /// A D3D12StencilOp-typed value that identifies the stencil operation to perform when
            /// stencil testing fails.
            /// </summary>
            D3D12StencilOp StencilFailOp;

            /// <summary>
            /// A D3D12StencilOp-typed value that identifies the stencil operation to perform when
            /// stencil testing passes and depth testing fails.
            /// </summary>
            D3D12StencilOp StencilDepthFailOp;

            /// <summary>
            /// A D3D12StencilOp-typed value that identifies the stencil operation to perform when
            /// stencil testing and depth testing both pass.
            /// </summary>
            D3D12StencilOp StencilPassOp;

            /// <summary>
            /// A D3D12ComparisonFunc-typed value that identifies the function that compares stencil
            /// data against existing stencil data.
            /// </summary>
            D3D12ComparisonFunc StencilFunc;

            /// <summary>
            /// Creates a new instance of a D3D12DepthStencilopDesc, initialized with default parameters.
            /// </summary>
            D3D12DepthStencilOpDesc(D3DDefault);
        };

        /// <summary>
        /// Describes depth-stencil state.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DepthStencilDesc
        {
            /// <summary>
            /// Specifies whether to enable depth testing. Set this member to True to enable
            /// depth testing.
            /// </summary>
            CBool DepthEnable;

            /// <summary>
            /// A D3D12DepthWriteMask-typed value that identifies a portion of the depth-stencil
            /// buffer that can be modified by depth data.
            /// </summary>
            D3D12DepthWriteMask DepthWriteMask;

            /// <summary>
            /// A D3D12ComparisonFunc-typed value that identifies a function that compares depth
            /// data against existing depth data.
            /// </summary>
            D3D12ComparisonFunc DepthFunc;

            /// <summary>
            /// Specifies whether to enable stencil testing. Set this member to True to enable
            /// stencil testing.
            /// </summary>
            CBool StencilEnable;

            /// <summary>
            /// Identify a portion of the depth-stencil buffer for reading stencil data.
            /// </summary>
            unsigned char StencilReadMask;

            /// <summary>
            /// Identify a portion of the depth-stencil buffer for writing stencil data.
            /// </summary>
            unsigned char StencilWriteMask;

            /// <summary>
            /// A D3D12DepthStencilOpDesc structure that describes how to use the results of the
            /// depth test and the stencil test for pixels whose surface normal is facing towards
            /// the camera.
            /// </summary>
            D3D12DepthStencilOpDesc FrontFace;

            /// <summary>
            /// A D3D12DepthStencilOpDesc structure that describes how to use the results of the
            /// depth test and the stencil test for pixels whose surface normal is facing away from
            /// the camera.
            /// </summary>
            D3D12DepthStencilOpDesc BackFace;

            /// <summary>
            /// Creates a new instance of a D3D12DepthStencilDesc, initialized with default
            /// parameters.
            /// </summary>
            D3D12DepthStencilDesc(D3DDefault);
        };

        /// <summary>
        /// Describes a single element for the input-assembler stage of the graphics pipeline.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12InputElementDesc
        {
            /// <summary>
            /// The HLSL semantic associated with this element in a shader input-signature.
            /// </summary>
            LPSTR SemanticName;

            /// <summary>
            /// The semantic index for the element. A semantic index modifies a semantic, with an integer
            /// index number. A semantic index is only needed in a case where there is more than one
            /// element with the same semantic. For example, a 4x4 matrix would have four components each
            /// with the semantic name matrix, however each of the four component would have different
            /// semantic indices (0, 1, 2, and 3).
            /// </summary>
            unsigned int SemanticIndex;

            /// <summary>
            /// A DXGIFormat-typed value that specifies the format of the element data.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// An integer value that identifies the input-assembler. Valid values are between 0 and 15.
            /// </summary>
            unsigned int InputSlot;

            /// <summary>
            /// Optional. Offset, in bytes, to this element from the start of the vertex.
            /// Use 0xffffffff for convenience to define the current element directly after the
            /// previous one, including any packing if necessary.
            /// </summary>
            unsigned int AlignedByteOffset;

            /// <summary>
            /// A value that identifies the input data class for a single input slot.
            /// </summary>
            D3D12InputClassification InputSlotClass;

            /// <summary>
            /// The number of instances to draw using the same per-instance data before advancing in
            /// the buffer by one element. This value must be 0 for an element that contains
            /// per-vertex data (the slot class is set to the PerVertexData member
            /// of D3D12InputClassification).
            /// </summary>
            unsigned int InstanceDataStepRate;

            /// <summary>
            /// Initialize the structure.
            /// </summary>
            /// <param name="semanticNameHandle">Handle to the marshal context that is needed
            /// for SemanticName. Free the handle after using this structure.</param>
            D3D12InputElementDesc(
                String^ semanticName,
                unsigned int semanticIndex,
                DXGIFormat format,
                unsigned int inputSlot,
                unsigned int alignedByteOffset,
                D3D12InputClassification inputSlotClass,
                unsigned int instanceDataStepRate,
                [Out] GCHandle% semanticNameHandle
            );
        };

        /// <summary>
        /// Describes the input-buffer data for the input-assembler stage.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12InputLayoutDesc
        {
            /// <summary>
            /// A pointer to an array of D3D12InputElementDesc structures that describe the data types
            /// of the input-assembler stage.
            /// </summary>
            D3D12InputElementDesc* pInputElementDescs;

            /// <summary>
            /// The number of input-data types in the array of input elements that the
            /// pInputElementDescs member points to.
            /// </summary>
            unsigned int NumElements;

            /// <summary>
            /// Initializes the structure.
            /// </summary>
            /// <param name="inputElementDescs">An array of D3D12InputElementDesc structures that
            /// describe the data types of the input-assembler stage.</param>
            /// <param name="inputElementDescsPinPtr">Pin pointer to the inputElementDescs array.
            /// Free the handle after using this structure.</param>
            D3D12InputLayoutDesc(
                array<D3D12InputElementDesc>^ inputElementDescs,
                [Out] GCHandle% inputElementDescsPinPtr
            );
        };

        /// <summary>
        /// Stores a pipeline state.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12CachedPipelineState
        {
            /// <summary>
            /// Specifies pointer that references the memory location of the cache.
            /// </summary>
            IntPtr pCachedBlob;

            /// <summary>
            /// Specifies the size of the cache in bytes.
            /// </summary>
            SIZE_T CachedBlobSizeInBytes;

            /// <summary>
            /// Initializes the structure with the blob from D3D12PipelineState::CachedBlob
            /// </summary>
            /// <param name="cachedBlob">Cached blob</param>
            D3D12CachedPipelineState(D3D10Blob^ cachedBlob);
        };

        /// <summary>
        /// Describes a graphics pipeline state object.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12GraphicsPipelineStateDesc
        {
            /// <summary>
            /// A pointer to the native ID3D12RootSignature object. This can be obtained by
            /// D3D12RootSignature::NativeRootSignature property.
            /// </summary>
            IntPtr pRootSignature;

            /// <summary>
            /// A D3D12ShaderBytecode structure that describes the vertex shader.
            /// </summary>
            D3D12ShaderBytecode VS;

            /// <summary>
            /// A D3D12ShaderBytecode structure that describes the pixel shader.
            /// </summary>
            D3D12ShaderBytecode PS;

            /// <summary>
            /// A D3D12ShaderBytecode structure that describes the domain shader.
            /// </summary>
            D3D12ShaderBytecode DS;

            /// <summary>
            /// A D3D12ShaderBytecode structure that describes the hull shader.
            /// </summary>
            D3D12ShaderBytecode HS;

            /// <summary>
            /// A D3D12ShaderBytecode structure that describes the geometry shader.
            /// </summary>
            D3D12ShaderBytecode GS;

            /// <summary>
            /// A D3D12StreamOutputDesc structure that describes a streaming output buffer.
            /// </summary>
            D3D12StreamOutputDesc StreamOutput;

            /// <summary>
            /// A D3D12BlendDesc structure that describes the blend state.
            /// </summary>
            D3D12BlendDesc BlendState;

            /// <summary>
            /// The sample mask for the blend state.
            /// </summary>
            unsigned int SampleMask;

            /// <summary>
            /// A D3D12RasterizerDesc structure that describes the rasterizer state.
            /// </summary>
            D3D12RasterizerDesc RasterizerState;

            /// <summary>
            /// A D3D12DepthStencilDesc structure that describes the depth-stencil state.
            /// </summary>
            D3D12DepthStencilDesc DepthStencilState;

            /// <summary>
            /// A D3D12InputLayoutDesc structure that describes the input-buffer data for the
            /// input-assembler stage.
            /// </summary>
            D3D12InputLayoutDesc InputLayout;

            /// <summary>
            /// Specifies the properties of the index buffer in a D3D12IndexBufferStripCutValue.
            /// </summary>
            D3D12IndexBufferStripCutValue IBStripCutValue;

            /// <summary>
            /// A D3D12PrimitiveTopologyType-typed value for the type of primitive, and ordering of
            /// the primitive data.
            /// </summary>
            D3D12PrimitiveTopologyType PrimitiveTopologyType;

            /// <summary>
            /// The number of render target formats in the RTVFormat0...7 member.
            /// </summary>
            unsigned int NumRenderTargets;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 0 format.
            /// </summary>
            DXGIFormat RTVFormat0;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 1 format.
            /// </summary>
            DXGIFormat RTVFormat1;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 2 format.
            /// </summary>
            DXGIFormat RTVFormat2;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 3 format.
            /// </summary>
            DXGIFormat RTVFormat3;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 4 format.
            /// </summary>
            DXGIFormat RTVFormat4;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 5 format.
            /// </summary>
            DXGIFormat RTVFormat5;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 6 format.
            /// </summary>
            DXGIFormat RTVFormat6;

            /// <summary>
            /// An DXGIFormat-typed value for the render target 7 format.
            /// </summary>
            DXGIFormat RTVFormat7;

            /// <summary>
            /// A DXGIFormat-typed value for the depth-stencil format.
            /// </summary>
            DXGIFormat DSVFormat;

            /// <summary>
            /// A DXGISampleDesc structure that specifies multisampling parameters.
            /// </summary>
            DXGISampleDesc SampleDesc;

            /// <summary>
            /// For single GPU operation, set this to zero. If there are multiple GPU nodes, set bits
            /// to identify the nodes (the device's physical adapters) for which the graphics
            /// pipeline state is to apply. Each bit in the mask corresponds to a single node.
            /// </summary>
            unsigned int NodeMask;

            /// <summary>
            /// A cached pipeline state object, as a D3D12CachedPipelineState structure. pCachedBlob
            /// and CachedBlobSizeInBytes may be set to null and 0 respectively.
            /// </summary>
            D3D12CachedPipelineState CachedPSO;

            /// <summary>
            /// A D3D12PipelineStateFlags enumeration constant such as for "tool debug".
            /// </summary>
            D3D12PipelineStateFlags Flags;
        };

        /// <summary>
        /// Describes a compute pipeline state object.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ComputePipelineStateDesc
        {
            /// <summary>
            /// A pointer to the native ID3D12RootSignature object. This can be obtained by
            /// D3D12RootSignature::NativeRootSignature property.
            /// </summary>
            IntPtr pRootSignature;

            /// <summary>
            /// A D3D12_SHADER_BYTECODE structure that describes the compute shader.
            /// </summary>
            D3D12ShaderBytecode CS;

            /// <summary>
            /// For single GPU operation, set this to zero. If there are multiple GPU nodes, set
            /// bits to identify the nodes (the device's physical adapters) for which the compute
            /// pipeline state is to apply. Each bit in the mask corresponds to a single node.
            /// </summary>
            unsigned int NodeMask;

            /// <summary>
            /// A cached pipeline state object, as a D3D12CachedPipelineState structure. pCachedBlob
            /// and CachedBlobSizeInBytes may be set to null and 0 respectively.
            /// </summary>
            D3D12CachedPipelineState CachedPSO;

            /// <summary>
            /// A D3D12PipelineStateFlags enumeration constant such as for "tool debug".
            /// </summary>
            D3D12PipelineStateFlags Flags;
        };

        /// <summary>
        /// Describes the format, width, height, depth, and row-pitch of the subresource into the
        /// parent resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12SubresourceFootprint
        {
            /// <summary>
            /// A DXGIFormat-typed value that specifies the viewing format.
            /// </summary>
            DXGIFormat Format;

            /// <summary>
            /// The width of the subresource.
            /// </summary>
            unsigned int Width;

            /// <summary>
            /// The height of the subresource.
            /// </summary>
            unsigned int Height;

            /// <summary>
            /// The depth of the subresource.
            /// </summary>
            unsigned int Depth;

            /// <summary>
            /// The row pitch, or width, or physical size, in bytes, of the subresource data. This must
            /// be a multiple of 256, and must be greater than or equal to the size of the data within
            /// a row.
            /// </summary>
            unsigned int RowPitch;

            D3D12SubresourceFootprint(
                DXGIFormat format,
                unsigned int width,
                unsigned int height,
                unsigned int depth,
                unsigned int rowPitch
            );

            /// <summary>
            /// Initializes the structure.
            /// </summary>
            /// <param name="resDesc">The parent resource description.</param>
            /// <param name="rowPitch">Row pitch.</param>
            D3D12SubresourceFootprint(
                [In][IsReadOnly] D3D12ResourceDesc% resDesc,
                unsigned int rowPitch
            );
        };

        /// <summary>
        /// Describes the footprint of a placed subresource, including the offset and the
        /// D3D12SubresourceFootprint.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12PlacedSubresourceFootprint
        {
            /// <summary>
            /// The offset of the subresource within the parent resource, in bytes. The offset between the
            /// start of the parent resource and this subresource.
            /// </summary>
            unsigned long long Offset;

            /// <summary>
            /// The format, width, height, depth, and row-pitch of the subresource, as a
            /// D3D12SubresourceFootprint structure.
            /// </summary>
            D3D12SubresourceFootprint Footprint;
        };

        /// <summary>
        /// Describes a portion of a texture for the purpose of texture copies.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 48)]
        public value struct D3D12TextureCopyLocation
        {
            /// <summary>
            /// Specifies the resource which will be used for the copy operation.
            /// This can be obtained with D3D12Resource::NativeResource property.
            /// When Type is D3D12TextureCopyType::PlacedFootprint, pResource must point to a
            /// buffer resource.
            /// When Type is D3D12TextureCopyType::SubresourceIndex, pResource must point to a
            /// texture resource.
            /// </summary>
            [FieldOffset(0)] IntPtr pResource;

            /// <summary>
            /// Specifies which type of resource location this is: a subresource of a texture,
            /// or a description of a texture layout which can be applied to a buffer. This
            /// D3D12TextureCopyType enum indicates which field to use.
            /// </summary>
            [FieldOffset(8)] D3D12TextureCopyType Type;

            /// <summary>
            /// Specifies a texture layout, with offset, dimensions, and pitches, for the hardware
            /// to understand how to treat a section of a buffer resource as a multi-dimensional
            /// texture. To fill-in the correct data for a CopyTextureRegion call, see
            /// D3D12PlacedSubresourceFootprint.
            /// </summary>
            [FieldOffset(16)] D3D12PlacedSubresourceFootprint PlacedFootprint;

            /// <summary>
            /// Specifies the index of the subresource of an arrayed, mip-mapped, or planar texture
            /// should be used for the copy operation.
            /// </summary>
            [FieldOffset(16)] unsigned int SubresourceIndex;

            /// <summary>
            /// Creates a new instance of a D3D12TextureCopyLocation with the resource and uses
            /// subresource index 0.
            /// </summary>
            /// <param name="res">Resource.</param>
            D3D12TextureCopyLocation(D3D12Resource^ res);

            /// <summary>
            /// Creates a new instance of a D3D12TextureCopyLocation with the resource and uses
            /// footprint.
            /// </summary>
            /// <param name="res">Resource.</param>
            /// <param name="footprint">Footprint/</param>
            D3D12TextureCopyLocation(
                D3D12Resource^ res,
                [In][IsReadOnly] D3D12PlacedSubresourceFootprint% footprint
            );

            /// <summary>
            /// Creates a new instance of a D3D12TextureCopyLocation with the resource and uses
            /// subresource index.
            /// </summary>
            /// <param name="res">Resource.</param>
            /// <param name="sub">Subresource index.</param>
            D3D12TextureCopyLocation(D3D12Resource^ res, unsigned int sub);
        };

        /// <summary>
        /// Describes the dimensions of a viewport.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Viewport
        {
            /// <summary>
            /// X position of the left hand side of the viewport.
            /// </summary>
            float TopLeftX;

            /// <summary>
            /// Y position of the top of the viewport.
            /// </summary>
            float TopLeftY;

            /// <summary>
            /// Width of the viewport.
            /// </summary>
            float Width;

            /// <summary>
            /// Height of the viewport.
            /// </summary>
            float Height;

            /// <summary>
            /// Minimum depth of the viewport. Ranges between 0 and 1.
            /// </summary>
            float MinDepth;

            /// <summary>
            /// Maximum depth of the viewport. Ranges between 0 and 1.
            /// </summary>
            float MaxDepth;

            /// <summary>
            /// Initializes the viewport.
            /// </summary>
            /// <param name="minDepth">Optional min depth. The default value is 0.</param>
            /// <param name="maxDepth">Optional max depth. The default value is 1.</param>
            D3D12Viewport(
                float topLeftX,
                float topLeftY,
                float width,
                float height,
                [Optional] Nullable<float> minDepth,
                [Optional] Nullable<float> maxDepth
            );

            /// <summary>
            /// Initializes the viewport with given resource.
            /// </summary>
            /// <param name="resource">Resource used to initialize the viewport.</param>
            /// <param name="mipSlice">The number of mip slice. The default value is 0.</param>
            /// <param name="topLeftX">The default value is 0.</param>
            /// <param name="topLeftY">The default value is 0.</param>
            /// <param name="minDepth">The default value is 0.</param>
            /// <param name="maxDepth">The default value is 1.</param>
            D3D12Viewport(
                D3D12Resource^ resource,
                [Optional] Nullable<unsigned int> mipSlice,
                [Optional] Nullable<float> topLeftX,
                [Optional] Nullable<float> topLeftY,
                [Optional] Nullable<float> minDepth,
                [Optional] Nullable<float> maxDepth
            );
        };

        /// <summary>
        /// Describes the transition of subresources between different usages.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ResourceTransitionBarrier
        {
            /// <summary>
            /// A pointer to the ID3D12Resource object that represents the resource used in
            /// the transition. This can be obtained with D3D12Resource::NativeResource property.
            /// </summary>
            IntPtr pResource;

            /// <summary>
            /// The index of the subresource for the transition. Use 0xffffffff to transition all
            /// subresources in a resource at the same time.
            /// </summary>
            unsigned int Subresource;

            /// <summary>
            /// The "before" usages of the subresources, as a bitwise-OR'd combination of
            /// D3D12ResourceStates enumeration constants.
            /// </summary>
            D3D12ResourceStates StateBefore;

            /// <summary>
            /// The "after" usages of the subresources, as a bitwise-OR'd combination of
            /// D3D12ResourceStates enumeration constants.
            /// </summary>
            D3D12ResourceStates StateAfter;

            D3D12ResourceTransitionBarrier(
                D3D12Resource^ resource,
                unsigned int subresource,
                D3D12ResourceStates stateBefore,
                D3D12ResourceStates stateAfter
            );
        };

        /// <summary>
        /// Describes the transition between usages of two different resources that have mappings into
        /// the same heap.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ResourceAliasingBarrier
        {
            /// <summary>
            /// A pointer to the ID3D12Resource object that represents the before resource used in
            /// the transition. This can be obtained with D3D12Resource::NativeResource property.
            /// </summary>
            IntPtr pResourceBefore;

            /// <summary>
            /// A pointer to the ID3D12Resource object that represents the after resource used in
            /// the transition. This can be obtained with D3D12Resource::NativeResource property.
            /// </summary>
            IntPtr pResourceAfter;

            D3D12ResourceAliasingBarrier(
                D3D12Resource^ before,
                D3D12Resource^ after
            );
        };

        /// <summary>
        /// Represents a resource in which all UAV accesses must complete before any future UAV
        /// accesses can begin.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12ResourceUavBarrier
        {
            /// <summary>
            /// The resource used in the transition, as a pointer to ID3D12Resource.
            /// This can be obtained with D3D12Resource::NativeResource property.
            /// </summary>
            IntPtr pResource;

            D3D12ResourceUavBarrier(D3D12Resource^ resource);
        };

        /// <summary>
        /// Describes a resource barrier (transition in resource use).
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 32)]
        public value struct D3D12ResourceBarrier
        {
            /// <summary>
            /// A D3D12ResourceBarrierType-typed value that specifies the type of resource barrier.
            /// This member determines which type to use in the union below.
            /// </summary>
            [FieldOffset(0)] D3D12ResourceBarrierType Type;

            /// <summary>
            /// Specifies a D3D12ResourceBarrierFlags enumeration constant such as for "begin only" or
            /// "end only".
            /// </summary>
            [FieldOffset(4)] D3D12ResourceBarrierFlags Flags;

            /// <summary>
            /// A D3D12ResourceTransitionBarrier structure that describes the transition of subresources
            /// between different usages.
            /// Members specify the beforeand after usages of the subresources.
            /// </summary>
            [FieldOffset(8)] D3D12ResourceTransitionBarrier _Transition;

            /// <summary>
            /// A D3D12ResourceAliasingBarrier structure that describes the transition between usages of
            /// two different resources that have mappings into the same heap.
            /// </summary>
            [FieldOffset(8)] D3D12ResourceAliasingBarrier _Aliasing;

            /// <summary>
            /// A D3D12ResourceUavBarrier structure that describes a resource in which all UAV accesses
            /// (reads or writes) must complete before any future UAV accesses (read or write) can begin.
            /// </summary>
            [FieldOffset(8)] D3D12ResourceUavBarrier _UAV;

            /// <summary>
            /// Make a transition barrier.
            /// </summary>
            /// <param name="resource">Resource to make a barrier.</param>
            /// <param name="stateBefore">Before state.</param>
            /// <param name="stateAfter">After state.</param>
            /// <param name="subresource">The index of the subresource for the transition.
            /// The default value is 0xffffffff.</param>
            /// <param name="flags">Additional flags. The default value is
            /// D3D12ResourceBarrierFlags::None.</param>
            /// <returns>Resource barrier structure.</returns>
            static D3D12ResourceBarrier Transition(
                D3D12Resource^ resource,
                D3D12ResourceStates stateBefore,
                D3D12ResourceStates stateAfter,
                [Optional] Nullable<unsigned int> subresource,
                [Optional] Nullable<D3D12ResourceBarrierFlags> flags
            );

            /// <summary>
            /// Make a aliasing barrier.
            /// </summary>
            /// <param name="resourceBefore">Before resource.</param>
            /// <param name="resourceAfter">After resource.</param>
            /// <returns>Resource barrier structure.</returns>
            static D3D12ResourceBarrier Aliasing(
                D3D12Resource^ resourceBefore,
                D3D12Resource^ resourceAfter
            );

            /// <summary>
            /// Make a UAV barrier.
            /// </summary>
            /// <param name="resource">Resource to make a barrier.</param>
            /// <returns>Resource barrier structure.</returns>
            static D3D12ResourceBarrier UAV(D3D12Resource^ resource);
        };

        /// <summary>
        /// Describes the descriptor heap.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DescriptorHeapDesc
        {
            /// <summary>
            /// A D3D12DescriptorHeapType-typed value that specifies the types of descriptors in the heap.
            /// </summary>
            D3D12DescriptorHeapType Type;

            /// <summary>
            /// The number of descriptors in the heap.
            /// </summary>
            unsigned int NumDescriptors;

            /// <summary>
            /// A combination of D3D12DescriptorHeapFlags-typed values that are combined by using a
            /// bitwise OR operation. The resulting value specifies options for the heap.
            /// </summary>
            D3D12DescriptorHeapFlags Flags;

            /// <summary>
            /// For single-adapter operation, set this to zero. If there are multiple adapter nodes,
            /// set a bit to identify the node (one of the device's physical adapters) to which the
            /// descriptor heap applies. Each bit in the mask corresponds to a single node. Only one bit
            /// must be set.
            /// </summary>
            unsigned int NodeMask;
        };

        /// <summary>
        /// Describes a GPU descriptor handle. All the methods can be used similarly with
        /// D3D12CPUDescriptorHandle.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12GPUDescriptorHandle : IEquatable<D3D12GPUDescriptorHandle>
        {
            /// <summary>
            /// The address of the descriptor.
            /// </summary>
            unsigned long long ptr;

            /// <summary>
            /// Creates a new instance of a D3D12GPUDescriptorHandle, initialized with default
            /// parameters (sets the pointer to zero).
            /// </summary>
            D3D12GPUDescriptorHandle(D3DDefault);

            D3D12GPUDescriptorHandle(D3D12GPUDescriptorHandle other, int offsetScaledByIncrementSize);

            D3D12GPUDescriptorHandle(
                D3D12GPUDescriptorHandle other,
                int offsetInDescriptors,
                unsigned int descriptorIncrementSize
            );

            void Offset(int offsetInDescriptors, unsigned int descriptorIncrementSize);

            void Offset(int offsetScaledByIncrementSize);

            static bool operator==(
                D3D12GPUDescriptorHandle lhs, D3D12GPUDescriptorHandle rhs
                );

            static bool operator!=(
                D3D12GPUDescriptorHandle lhs, D3D12GPUDescriptorHandle rhs
                );

            virtual bool Equals(Object^ other) override;

            virtual bool Equals(D3D12GPUDescriptorHandle other);

            void InitOffsetted(
                [In][IsReadOnly] D3D12GPUDescriptorHandle% base,
                int offsetScaledByIncrementSize
            );

            void InitOffsetted(
                [In][IsReadOnly] D3D12GPUDescriptorHandle% base,
                int offsetInDescriptors,
                unsigned int descriptorIncrementSize
            );

            static void InitOffsetted(
                D3D12GPUDescriptorHandle% handle,
                [In][IsReadOnly] D3D12GPUDescriptorHandle% base,
                int offsetScaledByIncrementSize
            );

            static void InitOffsetted(
                D3D12GPUDescriptorHandle% handle,
                [In][IsReadOnly] D3D12GPUDescriptorHandle% base,
                int offsetInDescriptors,
                unsigned int descriptorIncrementSize
            );
        };

        /// <summary>
        /// Describes the index buffer to view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12IndexBufferView
        {
            /// <summary>
            /// The GPU virtual address of the index buffer.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;

            /// <summary>
            /// The size in bytes of the index buffer.
            /// </summary>
            unsigned int SizeInBytes;

            /// <summary>
            /// A DXGIFormat-typed value for the index-buffer format.
            /// </summary>
            DXGIFormat Format;
        };

        /// <summary>
        /// Describes a vertex buffer view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12VertexBufferView
        {
            /// <summary>
            /// Specifies a D3D12_GPU_VIRTUAL_ADDRESS that identifies the address of the buffer.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;

            /// <summary>
            /// Specifies the size in bytes of the buffer.
            /// </summary>
            unsigned int SizeInBytes;

            /// <summary>
            /// Specifies the size in bytes of each vertex entry.
            /// </summary>
            unsigned int StrideInBytes;
        };

        /// <summary>
        /// Describes a stream output buffer.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12StreamOutputBufferView
        {
            /// <summary>
            /// A D3D12_GPU_VIRTUAL_ADDRESS (a UINT64) that points to the stream output buffer.
            /// If SizeInBytes is 0, this member isn't used and can be any value.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS BufferLocation;

            /// <summary>
            /// The size of the stream output buffer in bytes.
            /// </summary>
            unsigned long long SizeInBytes;

            /// <summary>
            /// The location of the value of how much data has been filled into the buffer, as a
            /// D3D12_GPU_VIRTUAL_ADDRESS (a UINT64). This member can't be 0; a filled size location
            /// must be supplied (which the hardware will increment as data is output). If SizeInBytes
            /// is 0, this member isn't used and can be any value.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS BufferFilledSizeLocation;
        };

        /// <summary>
        /// Describes details for the discard-resource operation.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DiscardRegion
        {
            /// <summary>
            /// The number of rectangles in the array that the pRects member specifies.
            /// </summary>
            unsigned int NumRects;

            /// <summary>
            /// A pointer to an array of Rect structures for the rectangles in the resource to discard.
            /// If null, DiscardResource discards the entire resource.
            /// </summary>
            Rect* pRects;

            /// <summary>
            /// Index of the first subresource in the resource to discard.
            /// </summary>
            unsigned int FirstSubresource;

            /// <summary>
            /// The number of subresources in the resource to discard.
            /// </summary>
            unsigned int NumSubresources;

            /// <summary>
            /// Initializes the structure with rect array.
            /// </summary>
            /// <param name="rects">Rect structures for the rectangles in the resource to discard.
            /// This can not be null.</param>
            /// <param name="firstSubresource">Index of the first subresource in the resource to
            /// discard.</param>
            /// <param name="numSubresource">The number of subresources in the resource to discard.
            /// </param>
            /// <param name="rectsPinPtr">Pin pointer to the rects array. Free the handle after
            /// using this structure.</param>
            D3D12DiscardRegion(
                array<Rect>^ rects,
                unsigned int firstSubresource,
                unsigned int numSubresource,
                [Out] GCHandle% rectsPinPtr
            );

            /// <summary>
            /// Initializes the structure without rectangles.
            /// </summary>
            /// <param name="firstSubresource">Index of the first subresource in the resource to
            /// discard.</param>
            /// <param name="numSubresource">The number of subresources in the resource to discard.
            /// </param>
            D3D12DiscardRegion(
                unsigned int firstSubresource,
                unsigned int numSubresource
            );
        };

        /// <summary>
        /// Query information about graphics-pipeline activity in between calls to BeginQuery
        /// and EndQuery.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12QueryDataPipelineStatistics : ID3D12QueryData
        {
            /// <summary>
            /// Number of vertices read by input assembler.
            /// </summary>
            unsigned long long IAVertices;

            /// <summary>
            /// Number of primitives read by the input assembler. This number can be different depending
            /// on the primitive topology used. For example, a triangle strip with 6 vertices will
            /// produce 4 triangles, however a triangle list with 6 vertices will produce 2 triangles.
            /// </summary>
            unsigned long long IAPrimitives;

            /// <summary>
            /// Specifies the number of vertex shader invocations. Direct3D invokes the vertex shader
            /// once per vertex.
            /// </summary>
            unsigned long long VSInvocations;

            /// <summary>
            /// Specifies the number of geometry shader invocations. When the geometry shader is set to
            /// null, this statistic may or may not increment depending on the graphics adapter.
            /// </summary>
            unsigned long long GSInvocations;

            /// <summary>
            /// Specifies the number of geometry shader output primitives.
            /// </summary>
            unsigned long long GSPrimitives;

            /// <summary>
            /// Number of primitives that were sent to the rasterizer. When the rasterizer is disabled,
            /// this will not increment.
            /// </summary>
            unsigned long long CInvocations;

            /// <summary>
            /// Number of primitives that were rendered. This may be larger or smaller than CInvocations
            /// because after a primitive is clipped sometimes it is either broken up into more than one
            /// primitive or completely culled.
            /// </summary>
            unsigned long long CPrimitives;

            /// <summary>
            /// Specifies the number of pixel shader invocations.
            /// </summary>
            unsigned long long PSInvocations;

            /// <summary>
            /// Specifies the number of hull shader invocations.
            /// </summary>
            unsigned long long HSInvocations;

            /// <summary>
            /// Specifies the number of domain shader invocations.
            /// </summary>
            unsigned long long DSInvocations;

            /// <summary>
            /// Specifies the number of compute shader invocations.
            /// </summary>
            unsigned long long CSInvocations;
        };

        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12QueryDataPipelineStatistics1 : ID3D12QueryData
        {
            unsigned long long IAVertices;
            unsigned long long IAPrimitives;
            unsigned long long VSInvocations;
            unsigned long long GSInvocations;
            unsigned long long GSPrimitives;
            unsigned long long CInvocations;
            unsigned long long CPrimitives;
            unsigned long long PSInvocations;
            unsigned long long HSInvocations;
            unsigned long long DSInvocations;
            unsigned long long CSInvocations;
            unsigned long long ASInvocations;
            unsigned long long MSInvocations;
            unsigned long long MSPrimitives;
        };

        /// <summary>
        /// Describes query data about the amount of data streamed out to the stream-output buffers.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12QueryDataSOStatistics : ID3D12QueryData
        {
            /// <summary>
            /// The number of primitives (that is, points, lines, and triangles) that were actually
            /// written to the stream output resource.
            /// </summary>
            unsigned long long NumPrimitivesWritten;

            /// <summary>
            /// If the stream output resource is large enough, then PrimitivesStorageNeeded represents
            /// the total number of primitives written to the stream output resource. Otherwise, it
            /// represents the total number of primitives that would have been written to the
            /// stream-output resource had there been enough space for them all.
            /// </summary>
            unsigned long long PrimitivesStorageNeeded;
        };

        /// <summary>
        /// Describes the elements in a buffer resource to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12BufferSrv
        {
            /// <summary>
            /// The index of the first element to be accessed by the view.
            /// </summary>
            unsigned long long FirstElement;

            /// <summary>
            /// The number of elements in the resource.
            /// </summary>
            unsigned int NumElements;

            /// <summary>
            /// The size of each element in the buffer structure (in bytes) when the buffer represents
            /// a structured buffer.
            /// </summary>
            unsigned int StructureByteStride;

            /// <summary>
            /// A D3D12BufferSrvFlags-typed value that identifies view options for the buffer. Currently,
            /// the only option is to identify a raw view of the buffer.
            /// </summary>
            D3D12BufferSrvFlags Flags;
        };

        /// <summary>
        /// Specifies the subresource from a 1D texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DSrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a 1D texture array to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DArraySrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures in the array.
            /// </summary>
            unsigned int ArraySize;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a 2D texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DSrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a 2D texture array to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DArraySrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures in the array.
            /// </summary>
            unsigned int ArraySize;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a 3D texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex3DSrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a cube texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12TexCubeSrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Specifies the subresource from a cube texture array to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12TexCubeArraySrv
        {
            /// <summary>
            /// Index of the most detailed mipmap level to use; this number is between 0 and MipLevels
            /// (from the original Texture1D for which D3D12Device::CreateShaderResourceView creates
            /// a view) -1.
            /// </summary>
            unsigned int MostDetailedMip;

            /// <summary>
            /// The maximum number of mipmap levels for the view of the texture. See the remarks. Set
            /// to -1 to indicate all the mipmap levels from MostDetailedMip on down to least detailed.
            /// </summary>
            unsigned int MipLevels;

            /// <summary>
            /// Index of the first 2D texture to use.
            /// </summary>
            unsigned int First2DArrayFace;

            /// <summary>
            /// Number of cube textures in the array.
            /// </summary>
            unsigned int NumCubes;

            /// <summary>
            /// A value to clamp sample LOD values to. For example, if you specify 2.0f for the clamp
            /// value, you ensure that no individual sample accesses a mip level less than 2.0f.
            /// </summary>
            float ResourceMinLODClamp;
        };

        /// <summary>
        /// Describes the subresources from a multi sampled 2D texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 4)]
        public value struct D3D12Tex2DMSSrv
        {

        };

        /// <summary>
        /// Describes the subresources from an array of multi sampled 2D textures to use in a
        /// shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DMSArraySrv
        {
            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// A shader resource view (SRV) structure for storing a raytracing acceleration structure.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RaytracingAccelerationStructureSrv
        {
            /// <summary>
            /// The GPU virtual address of the SRV.
            /// </summary>
            D3D12_GPU_VIRTUAL_ADDRESS Location;
        };

        /// <summary>
        /// Describes the subresources from a multi sampled 2D texture to use in a shader-resource view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 40)]
        public value struct D3D12ShaderResourceViewDesc
        {
            /// <summary>
            /// A DXGIFormat-typed value that specifies the viewing format.
            /// </summary>
            [FieldOffset(0)] DXGIFormat Format;

            /// <summary>
            /// A D3D12SrvDimension-typed value that specifies the resource type of the view. This type
            /// is the same as the resource type of the underlying resource. This member also determines
            /// which Srv to use in the union below.
            /// </summary>
            [FieldOffset(4)] D3D12SrvDimension ViewDimension;

            /// <summary>
            /// A value, constructed using the D3D12::EncodeShader4ComponentMapping method.
            /// The D3D12ShaderComponentMapping enumeration specifies what values from memory should
            /// be returned when the texture is accessed in a shader via this shader resource view (SRV).
            /// For example, it can route component 1 (green) from memory, or the constant 0, into
            /// component 2 (.b) of the value given to the shader. Use
            /// D3D12::DefaultShader4ComponentMapping for default value.
            /// </summary>
            [FieldOffset(8)] unsigned int Shader4ComponentMapping;

            [FieldOffset(16)] D3D12BufferSrv Buffer;
            [FieldOffset(16)] D3D12Tex1DSrv Texture1D;
            [FieldOffset(16)] D3D12Tex1DArraySrv Texture1DArray;
            [FieldOffset(16)] D3D12Tex2DSrv Texture2D;
            [FieldOffset(16)] D3D12Tex2DArraySrv Texture2DArray;
            [FieldOffset(16)] D3D12Tex2DMSSrv Texture2DMS;
            [FieldOffset(16)] D3D12Tex2DMSArraySrv Texture2DMSArray;
            [FieldOffset(16)] D3D12Tex3DSrv Texture3D;
            [FieldOffset(16)] D3D12TexCubeSrv TextureCube;
            [FieldOffset(16)] D3D12TexCubeArraySrv TextureCubeArray;
            [FieldOffset(16)] D3D12RaytracingAccelerationStructureSrv RaytracingAccelerationStructure;
        };

        /// <summary>
        /// Describes the elements in a buffer to use in a unordered-access view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12BufferUav
        {
            /// <summary>
            /// The zero-based index of the first element to be accessed.
            /// </summary>
            unsigned long long FirstElement;

            /// <summary>
            /// The number of elements in the resource. For structured buffers, this is the number
            /// of structures in the buffer.
            /// </summary>
            unsigned int NumElements;

            /// <summary>
            /// The size of each element in the buffer structure (in bytes) when the buffer represents
            /// a structured buffer.
            /// </summary>
            unsigned int StructureByteStride;

            /// <summary>
            /// The counter offset, in bytes.
            /// </summary>
            unsigned long long CounterOffsetInBytes;

            /// <summary>
            /// A D3D12BufferUavFlags-typed value that specifies the view options for the resource.
            /// </summary>
            D3D12BufferUavFlags Flags;
        };

        /// <summary>
        /// Describes a unordered-access 1D texture resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DUav
        {
            /// <summary>
            /// The mipmap slice index.
            /// </summary>
            unsigned int MipSlice;
        };

        /// <summary>
        /// Describes an array of unordered-access 1D texture resources.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DArrayUav
        {
            /// <summary>
            /// The mipmap slice index.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The zero-based index of the first array slice to be accessed.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// The number of slices in the array.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes a unordered-access 2D texture resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DUav
        {
            /// <summary>
            /// The mipmap slice index.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;
        };

        /// <summary>
        /// Describes an array of unordered-access 2D texture resources.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DArrayUav
        {
            /// <summary>
            /// The mipmap slice index.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The zero-based index of the first array slice to be accessed.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// The number of slices in the array.
            /// </summary>
            unsigned int ArraySize;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;
        };

        /// <summary>
        /// Describes a unordered-access 3D texture resource.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex3DUav
        {
            /// <summary>
            /// The mipmap slice index.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The zero-based index of the first depth slice to be accessed.
            /// </summary>
            unsigned int FirstWSlice;

            /// <summary>
            /// The number of depth slices.
            /// </summary>
            unsigned int WSize;
        };

        /// <summary>
        /// Describes the subresources from a resource that are accessible by using an
        /// unordered-access view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 40)]
        public value struct D3D12UnorderedAccessViewDesc
        {
            /// <summary>
            /// A DXGIFormat-typed value that specifies the viewing format.
            /// </summary>
            [FieldOffset(0)] DXGIFormat Format;

            /// <summary>
            /// A D3D12UavDimension-typed value that specifies the resource type of the view. This type
            /// specifies how the resource will be accessed. This member also determines which Uav to
            /// use in the union below.
            /// </summary>
            [FieldOffset(4)] D3D12UavDimension ViewDimension;

            [FieldOffset(8)] D3D12BufferUav Buffer;
            [FieldOffset(8)] D3D12Tex1DUav Texture1D;
            [FieldOffset(8)] D3D12Tex1DArrayUav Texture1DArray;
            [FieldOffset(8)] D3D12Tex2DUav Texture2D;
            [FieldOffset(8)] D3D12Tex2DArrayUav Texture2DArray;
            [FieldOffset(8)] D3D12Tex3DUav Texture3D;
        };

        /// <summary>
        /// Describes the elements in a buffer resource to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12BufferRtv
        {
            /// <summary>
            /// Number of bytes between the beginning of the buffer and the first element to access.
            /// </summary>
            unsigned long long FirstElement;

            /// <summary>
            /// The total number of elements in the view.
            /// </summary>
            unsigned int NumElements;
        };

        /// <summary>
        /// Describes the subresource from a 1D texture to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DRtv
        {
            /// <summary>
            /// The index of the mipmap level to use mip slice.
            /// </summary>
            unsigned int MipSlice;
        };

        /// <summary>
        /// Describes the subresources from an array of 1D textures to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DArrayRtv
        {
            /// <summary>
            /// The index of the mipmap level to use mip slice.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes the subresource from a 2D texture to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DRtv
        {
            /// <summary>
            /// The index of the mipmap level to use mip slice.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;
        };

        /// <summary>
        /// Describes the subresource from a multi sampled 2D texture to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 4)]
        public value struct D3D12Tex2DMSRtv
        {

        };

        /// <summary>
        /// Describes the subresources from an array of 2D textures to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DArrayRtv
        {
            /// <summary>
            /// The index of the mipmap level to use mip slice.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures in the array to use in the render target view, starting
            /// from FirstArraySlice.
            /// </summary>
            unsigned int ArraySize;

            /// <summary>
            /// The index (plane slice number) of the plane to use in the texture.
            /// </summary>
            unsigned int PlaneSlice;
        };

        /// <summary>
        /// Describes the subresources from an array of multi sampled 2D textures to use in a
        /// render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DMSArrayRtv
        {
            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes the subresources from a 3D texture to use in a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex3DRtv
        {
            /// <summary>
            /// The index of the mipmap level to use mip slice.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// First depth level to use.
            /// </summary>
            unsigned int FirstWSlice;

            /// <summary>
            /// Number of depth levels to use in the render-target view, starting from FirstWSlice.
            /// A value of -1 indicates all of the slices along the w axis, starting from FirstWSlice.
            /// </summary>
            unsigned int WSize;
        };

        /// <summary>
        /// Describes the subresources from a resource that are accessible by using a render-target view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 24)]
        public value struct D3D12RenderTargetViewDesc
        {
            /// <summary>
            /// A DXGIFormat-typed value that specifies the viewing format.
            /// </summary>
            [FieldOffset(0)] DXGIFormat Format;

            /// <summary>
            /// A D3D12RtvDimension-typed value that specifies how the render-target resource will be
            /// accessed. This type specifies how the resource will be accessed. This member also
            /// determines which Rtv to use in the following union.
            /// </summary>
            [FieldOffset(4)] D3D12RtvDimension ViewDimension;

            [FieldOffset(8)] D3D12BufferRtv Buffer;
            [FieldOffset(8)] D3D12Tex1DRtv Texture1D;
            [FieldOffset(8)] D3D12Tex1DArrayRtv Texture1DArray;
            [FieldOffset(8)] D3D12Tex2DRtv Texture2D;
            [FieldOffset(8)] D3D12Tex2DArrayRtv Texture2DArray;
            [FieldOffset(8)] D3D12Tex2DMSRtv Texture2DMS;
            [FieldOffset(8)] D3D12Tex2DMSArrayRtv Texture2DMSArray;
            [FieldOffset(8)] D3D12Tex3DRtv Texture3D;
        };

        /// <summary>
        /// Describes the subresource from a 1D texture that is accessible to a depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DDsv
        {
            /// <summary>
            /// The index of the first mipmap level to use.
            /// </summary>
            unsigned int MipSlice;
        };

        /// <summary>
        /// Describes the subresources from an array of 1D textures to use in a depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex1DArrayDsv
        {
            /// <summary>
            /// The index of the first mipmap level to use.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes the subresource from a 2D texture that is accessible to a depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DDsv
        {
            /// <summary>
            /// The index of the first mipmap level to use.
            /// </summary>
            unsigned int MipSlice;
        };

        /// <summary>
        /// Describes the subresources from an array of 2D textures that are accessible to a
        /// depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DArrayDsv
        {
            /// <summary>
            /// The index of the first mipmap level to use.
            /// </summary>
            unsigned int MipSlice;

            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes the subresource from a multi sampled 2D texture that is accessible to a
        /// depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 4)]
        public value struct D3D12Tex2DMSDsv
        {

        };

        /// <summary>
        /// Describes the subresources from an array of multi sampled 2D textures for a
        /// depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12Tex2DMSArrayDsv
        {
            /// <summary>
            /// The index of the first texture to use in an array of textures.
            /// </summary>
            unsigned int FirstArraySlice;

            /// <summary>
            /// Number of textures to use.
            /// </summary>
            unsigned int ArraySize;
        };

        /// <summary>
        /// Describes the subresources of a texture that are accessible from a depth-stencil view.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 24)]
        public value struct D3D12DepthStencilViewDesc
        {
            /// <summary>
            /// A DXGIFormat-typed value that specifies the viewing format.
            /// These are valid formats for a depth-stencil view:
            /// <para>FORMAT_D16_UNORM</para>
            /// <para>FORMAT_D24_UNORM_S8_UINT</para>
            /// <para>FORMAT_D32_FLOAT</para>
            /// <para>FORMAT_D32_FLOAT_S8X24_UINT</para>
            /// <para>FORMAT_UNKNOWN</para>
            /// <para>A depth-stencil view can't use a typeless format. If the format chosen is
            /// FORMAT_UNKNOWN, the format of the parent resource is used.</para>
            /// </summary>
            [FieldOffset(0)] DXGIFormat Format;

            /// <summary>
            /// A D3D12DsvDimension-typed value that specifies how the depth-stencil resource will be
            /// accessed. This member also determines which Dsv to use in the following union.
            /// </summary>
            [FieldOffset(4)] D3D12DsvDimension ViewDimension;

            /// <summary>
            /// A combination of D3D12_DSV_FLAGS enumeration constants that are combined by using a
            /// bitwise OR operation. The resulting value specifies whether the texture is read only.
            /// Pass 0 to specify that it isn't read only; otherwise, pass one or more of the members of
            /// the D3D12DsvFlags enumerated type.
            /// </summary>
            [FieldOffset(8)] D3D12DsvFlags Flags;

            [FieldOffset(12)] D3D12Tex1DDsv Texture1D;
            [FieldOffset(12)] D3D12Tex1DArrayDsv Texture1DArray;
            [FieldOffset(12)] D3D12Tex2DDsv Texture2D;
            [FieldOffset(12)] D3D12Tex2DArrayDsv Texture2DArray;
            [FieldOffset(12)] D3D12Tex2DMSDsv Texture2DMS;
            [FieldOffset(12)] D3D12Tex2DMSArrayDsv Texture2DMSArray;
        };

        /// <summary>
        /// Specifies a depth and stencil value.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DepthStencilValue
        {
            /// <summary>
            /// Specifies the depth value.
            /// </summary>
            float Depth;

            /// <summary>
            /// Specifies the stencil value.
            /// </summary>
            unsigned char Stencil;
        };

        /// <summary>
        /// Describes a value used to optimize clear operations for a particular resource.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 20)]
        public value struct D3D12ClearValue
        {
            /// <summary>
            /// Specifies one member of the DXGI_FORMAT enum.
            /// The format of the commonly cleared color follows the same validation rules as a
            /// view / descriptor creation. In general, the format of the clear color can be any format
            /// in the same typeless group that the resource format belongs to. 
            /// This Format must match the format of the view used during the clear operation. It
            /// indicates whether the Color or the DepthStencil member is valid and how to convert the
            /// values for usage with the resource.
            /// </summary>
            [FieldOffset(0)] DXGIFormat Format;

            /// <summary>
            /// Specifies RGBA value.
            /// </summary>
            [FieldOffset(4)] D3DColorValue Color;

            /// <summary>
            /// Specifies one member of D3D12DepthStencilValue. These values match the semantics of
            /// Depth and Stencil in ClearDepthStencilView.
            /// </summary>
            [FieldOffset(4)] D3D12DepthStencilValue DepthStencil;

            /// <summary>
            /// Initializes the structure with a color.
            /// </summary>
            D3D12ClearValue(DXGIFormat format, D3DColorValue color);

            /// <summary>
            /// Initializes the structure with depth and stencil.
            /// </summary>
            D3D12ClearValue(DXGIFormat format, float depth, unsigned char stencil);
        };

        /// <summary>
        /// Describes a sampler state.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12SamplerDesc
        {
            /// <summary>
            /// A D3D12_FILTER-typed value that specifies the filtering method to use when sampling
            /// a texture.
            /// </summary>
            D3D12Filter Filter;

            /// <summary>
            /// A D3D12TextureAddressMode-typed value that specifies the method to use for resolving
            /// a u texture coordinate that is outside the 0 to 1 range.
            /// </summary>
            D3D12TextureAddressMode AddressU;

            /// <summary>
            /// A D3D12TextureAddressMode-typed value that specifies the method to use for resolving
            /// a v texture coordinate that is outside the 0 to 1 range.
            /// </summary>
            D3D12TextureAddressMode AddressV;

            /// <summary>
            /// A D3D12TextureAddressMode-typed value that specifies the method to use for resolving
            /// a w texture coordinate that is outside the 0 to 1 range.
            /// </summary>
            D3D12TextureAddressMode AddressW;

            /// <summary>
            /// Offset from the calculated mipmap level. For example, if the runtime calculates that
            /// a texture should be sampled at mipmap level 3 and MipLODBias is 2, the texture will be
            /// sampled at mipmap level 5.
            /// </summary>
            float MipLODBias;

            /// <summary>
            /// Clamping value used if D3D12Filter::Anisotropic or D3D12Filter::ComparisonAnisotropic
            /// is specified in Filter. Valid values are between 1 and 16.
            /// </summary>
            unsigned int MaxAnisotropy;

            /// <summary>
            /// A D3D12ComparisonFunc-typed value that specifies a function that compares sampled
            /// data against existing sampled data.
            /// </summary>
            D3D12ComparisonFunc ComparisonFunc;

            /// <summary>
            /// Border color to use if D3D12TextureAddressMode::Border is specified for AddressU,
            /// AddressV, or AddressW. Range must be between 0.0 and 1.0 inclusive.
            /// </summary>
            D3DColorValue BorderColor;

            /// <summary>
            /// Lower end of the mipmap range to clamp access to, where 0 is the largest and most
            /// detailed mipmap level and any level higher than that is less detailed.
            /// </summary>
            float MinLOD;

            /// <summary>
            /// Upper end of the mipmap range to clamp access to, where 0 is the largest and most
            /// detailed mipmap level and any level higher than that is less detailed. This value must
            /// be greater than or equal to MinLOD. To have no upper limit on LOD, set this member to
            /// a large value.
            /// </summary>
            float MaxLOD;
        };

        /// <summary>
        /// Describes the purpose of a query heap. A query heap contains an array of individual
        /// queries.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12QueryHeapDesc
        {
            /// <summary>
            /// Specifies one member of D3D12QueryHeapType.
            /// </summary>
            D3D12QueryHeapType Type;

            /// <summary>
            /// Specifies the number of queries the heap should contain.
            /// </summary>
            unsigned int Count;

            /// <summary>
            /// For single GPU operation, set this to zero. If there are multiple GPU nodes, set a bit
            /// to identify the node (the device's physical adapter) to which the query heap applies.
            /// Each bit in the mask corresponds to a single node. Only 1 bit must be set.
            /// </summary>
            unsigned int NodeMask;
        };

        /// <summary>
        /// Describes a descriptor range.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12DescriptorRange
        {
            /// <summary>
            /// A D3D12DescriptorRangeType-typed value that specifies the type of descriptor range.
            /// </summary>
            D3D12DescriptorRangeType RangeType;

            /// <summary>
            /// The number of descriptors in the range. Use -1 or UInt32::MaxValue to specify an
            /// unbounded size. If a given descriptor range is unbounded, then it must either be the
            /// last range in the table definition, or else the following range in the table
            /// definition must have a value for OffsetInDescriptorsFromTableStart that is not
            /// D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND(0xffffffff).
            /// </summary>
            unsigned int NumDescriptors;

            /// <summary>
            /// The base shader register in the range. For example, for shader-resource views
            /// (SRVs), 3 maps to ": register(t3);" in HLSL.
            /// </summary>
            unsigned int BaseShaderRegister;

            /// <summary>
            /// The register space. Can typically be 0, but allows multiple descriptor arrays of
            /// unknown size to not appear to overlap. For example, for SRVs, by extending the
            /// example in the BaseShaderRegister member description, 5 maps to ": register
            /// (t3,space5);" in HLSL.
            /// </summary>
            unsigned int RegisterSpace;

            /// <summary>
            /// The offset in descriptors, from the start of the descriptor table which was set as
            /// the root argument value for this parameter slot. This value can be
            /// D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND(0xffffffff), which indicates this range should
            /// immediately follow the preceding range.
            /// </summary>
            unsigned int OffsetInDescriptorsFromTableStart;

            /// <summary>
            /// Initializes the descriptor range.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            /// <param name="offsetInDescriptorsFromTableStart">The default value is
            /// D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND.</param>
            D3D12DescriptorRange(
                D3D12DescriptorRangeType rangeType,
                unsigned int numDescriptors,
                unsigned int baseShaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<unsigned int> offsetInDescriptorsFromTableStart
            );

            /// <summary>
            /// Initializes the descriptor range.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            /// <param name="offsetInDescriptorsFromTableStart">The default value is
            /// D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND.</param>
            void Init(
                D3D12DescriptorRangeType rangeType,
                unsigned int numDescriptors,
                unsigned int baseShaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<unsigned int> offsetInDescriptorsFromTableStart
            );

            /// <summary>
            /// Initializes the descriptor range.
            /// </summary>
            /// <param name="range">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">The default value is 0.</param>
            /// <param name="offsetInDescriptorsFromTableStart">The default value is
            /// D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND.</param>
            static void Init(
                D3D12DescriptorRange% range,
                D3D12DescriptorRangeType rangeType,
                unsigned int numDescriptors,
                unsigned int baseShaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<unsigned int> offsetInDescriptorsFromTableStart
            );
        };

        /// <summary>
        /// Describes the root signature 1.0 layout of a descriptor table as a collection of
        /// descriptor ranges that are all relative to a single base descriptor handle.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RootDescriptorTable
        {
            /// <summary>
            /// The number of descriptor ranges in the table layout.
            /// </summary>
            unsigned int NumDescriptorRanges;

            /// <summary>
            /// A pointer to the array of D3D12DescriptorRange structures that describe the
            /// descriptor ranges.
            /// </summary>
            D3D12DescriptorRange* pDescriptorRanges;

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="descriptorRanges">Array of descriptor ranges.</param>
            /// <param name="pinPtrToRange">Pin pointer to the range array. If you finished using
            /// the struct, then free it.</param>
            D3D12RootDescriptorTable(
                array<D3D12DescriptorRange>^ descriptorRanges,
                [Out] GCHandle% pinPtrToRange
            );

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="descriptorRanges">Array of descriptor ranges.</param>
            /// <param name="pinPtrToRange">Pin pointer to the range array. If you finished using
            /// the struct, then free it.</param>
            void Init(
                array<D3D12DescriptorRange>^ descriptorRanges,
                [Out] GCHandle% pinPtrToRange
            );

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="rootDescriptorTable">Reference to the struct to initialize.</param>
            /// <param name="descriptorRanges">Array of descriptor ranges.</param>
            /// <param name="pinPtrToRange">Pin pointer to the range array. If you finished using
            /// the struct, then free it.</param>
            static void Init(
                D3D12RootDescriptorTable% rootDescriptorTable,
                array<D3D12DescriptorRange>^ descriptorRanges,
                [Out] GCHandle% pinPtrToRange
            );
        };

        /// <summary>
        /// Describes constants inline in the root signature that appear in shaders as one
        /// constant buffer.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RootConstants
        {
            /// <summary>
            /// The shader register.
            /// </summary>
            unsigned int ShaderRegister;

            /// <summary>
            /// The register space.
            /// </summary>
            unsigned int RegisterSpace;

            /// <summary>
            /// The number of constants that occupy a single shader slot (these constants appear
            /// like a single constant buffer). All constants occupy a single root signature bind
            /// slot.
            /// </summary>
            unsigned int Num32BitValues;

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            D3D12RootConstants(
                unsigned int num32BitValues,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            void Init(
                unsigned int num32BitValues,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );
            
            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="rootConstants">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">The default value is 0.</param>
            static void Init(
                D3D12RootConstants% rootConstants,
                unsigned int num32BitValues,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );
        };

        /// <summary>
        /// Describes descriptors inline in the root signature version 1.0 that appear in shaders.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12RootDescriptor
        {
            /// <summary>
            /// The shader register.
            /// </summary>
            unsigned int ShaderRegister;

            /// <summary>
            /// The register space.
            /// </summary>
            unsigned int RegisterSpace;

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            D3D12RootDescriptor(
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="registerSpace">The default value is 0.</param>
            void Init(
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );

            /// <summary>
            /// Initializes the struct.
            /// </summary>
            /// <param name="table">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">The default value is 0.</param>
            static void Init(
                D3D12RootDescriptor% table,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace
            );
        };

        /// <summary>
        /// Describes the slot of a root signature version 1.0.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 32)]
        public value struct D3D12RootParameter
        {
            /// <summary>
            /// A D3D12RootParameterType-typed value that specifies the type of root signature slot.
            /// This member determines which type to use in the union below.
            /// </summary>
            [FieldOffset(0)] D3D12RootParameterType ParameterType;

            /// <summary>
            /// A D3D12RootDescriptorTable structure that describes the layout of a descriptor
            /// table as a collection of descriptor ranges that appear one after the other in a
            /// descriptor heap.
            /// </summary>
            [FieldOffset(8)] D3D12RootDescriptorTable DescriptorTable;

            /// <summary>
            /// A D3D12RootConstants structure that describes constants inline in the root signature
            /// that appear in shaders as one constant buffer.
            /// </summary>
            [FieldOffset(8)] D3D12RootConstants Constants;

            /// <summary>
            /// A D3D12RootDescriptor structure that describes descriptors inline in the root
            /// signature that appear in shaders.
            /// </summary>
            [FieldOffset(8)] D3D12RootDescriptor Descriptor;

            /// <summary>
            /// A D3D12ShaderVisibility-typed value that specifies the shaders that can access the
            /// contents of the root signature slot.
            /// </summary>
            [FieldOffset(24)] D3D12ShaderVisibility ShaderVisibility;

            /// <summary>
            /// Initializes the root parameter as a descriptor table.
            /// </summary>
            /// <param name="rootParam">Reference to the struct to initialize.</param>
            /// <param name="pinPtrToRange">Pin pointer to the descriptorRanges. Free it if
            /// you finished to use the struct.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            static void InitAsDescriptorTable(
                D3D12RootParameter% rootParam,
                array<D3D12DescriptorRange>^ descriptorRanges,
                [Out] GCHandle% pinPtrToRange,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a root constant.
            /// </summary>
            /// <param name="rootParam">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            static void InitAsConstants(
                D3D12RootParameter% rootParam,
                unsigned int num32BitValues,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a constant buffer view.
            /// </summary>
            /// <param name="rootParam">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            static void InitAsConstantBufferView(
                D3D12RootParameter% rootParam,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a shader resource view.
            /// </summary>
            /// <param name="rootParam">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            static void InitAsShaderResourceView(
                D3D12RootParameter% rootParam,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as an unordered access view.
            /// </summary>
            /// <param name="rootParam">Reference to the struct to initialize.</param>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            static void InitAsUnorderedAccessView(
                D3D12RootParameter% rootParam,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a descriptor table.
            /// </summary>
            /// <param name="pinPtrToRange">Pin pointer to the descriptorRanges. Free it if
            /// you finished to use the struct.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            void InitAsDescriptorTable(
                array<D3D12DescriptorRange>^ descriptorRanges,
                [Out] GCHandle% pinPtrToRange,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a root constant.
            /// </summary>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            void InitAsConstants(
                unsigned int num32BitValues,
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a constant buffer view.
            /// </summary>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            void InitAsConstantBufferView(
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as a shader resource view.
            /// </summary>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            void InitAsShaderResourceView(
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );

            /// <summary>
            /// Initializes the root parameter as an unordered access view.
            /// </summary>
            /// <param name="registerSpace">Optional register space. The default value is 0.</param>
            /// <param name="visibility">Optional shader visibility. The default value is All.</param>
            void InitAsUnorderedAccessView(
                unsigned int shaderRegister,
                [Optional] Nullable<unsigned int> registerSpace,
                [Optional] Nullable<D3D12ShaderVisibility> visibility
            );
        };

        /// <summary>
        /// Describes a static sampler.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D3D12StaticSamplerDesc
        {
            D3D12Filter Filter;
            D3D12TextureAddressMode AddressU;
            D3D12TextureAddressMode AddressV;
            D3D12TextureAddressMode AddressW;
            float MipLODBias;
            unsigned int MaxAnisotropy;
            D3D12ComparisonFunc ComparisonFunc;
            D3D12StaticBorderColor BorderColor;
            float MinLOD;
            float MaxLOD;
            unsigned int ShaderRegister;
            unsigned int RegisterSpace;
            D3D12ShaderVisibility ShaderVisibility;

            D3D12StaticSamplerDesc(
                unsigned int shaderRegister,
                [Optional] Nullable<D3D12Filter> filter,
                [Optional] Nullable<D3D12TextureAddressMode> addressU,
                [Optional] Nullable<D3D12TextureAddressMode> addressV,
                [Optional] Nullable<D3D12TextureAddressMode> addressW,
                [Optional] Nullable<float> mipLODBias,
                [Optional] Nullable<unsigned int> maxAnisotropy,
                [Optional] Nullable<D3D12ComparisonFunc> comparisonFunc,
                [Optional] Nullable<D3D12StaticBorderColor> borderColor,
                [Optional] Nullable<float> minLOD,
                [Optional] Nullable<float> maxLOD,
                [Optional] Nullable<D3D12ShaderVisibility> shaderVisibility,
                [Optional] Nullable<unsigned int> registerSpace
            );

            static void Init(
                D3D12StaticSamplerDesc% samplerDesc,
                unsigned int shaderRegister,
                [Optional] Nullable<D3D12Filter> filter,
                [Optional] Nullable<D3D12TextureAddressMode> addressU,
                [Optional] Nullable<D3D12TextureAddressMode> addressV,
                [Optional] Nullable<D3D12TextureAddressMode> addressW,
                [Optional] Nullable<float> mipLODBias,
                [Optional] Nullable<unsigned int> maxAnisotropy,
                [Optional] Nullable<D3D12ComparisonFunc> comparisonFunc,
                [Optional] Nullable<D3D12StaticBorderColor> borderColor,
                [Optional] Nullable<float> minLOD,
                [Optional] Nullable<float> maxLOD,
                [Optional] Nullable<D3D12ShaderVisibility> shaderVisibility,
                [Optional] Nullable<unsigned int> registerSpace
            );

            void Init(
                unsigned int shaderRegister,
                [Optional] Nullable<D3D12Filter> filter,
                [Optional] Nullable<D3D12TextureAddressMode> addressU,
                [Optional] Nullable<D3D12TextureAddressMode> addressV,
                [Optional] Nullable<D3D12TextureAddressMode> addressW,
                [Optional] Nullable<float> mipLODBias,
                [Optional] Nullable<unsigned int> maxAnisotropy,
                [Optional] Nullable<D3D12ComparisonFunc> comparisonFunc,
                [Optional] Nullable<D3D12StaticBorderColor> borderColor,
                [Optional] Nullable<float> minLOD,
                [Optional] Nullable<float> maxLOD,
                [Optional] Nullable<D3D12ShaderVisibility> shaderVisibility,
                [Optional] Nullable<unsigned int> registerSpace
            );
        };
    }
}
