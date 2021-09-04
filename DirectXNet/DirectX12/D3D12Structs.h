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
    namespace DirectX12
    {
        ref class D3D12Device;

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
            /// <param name="handle">Output of the initialized structure.</param>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetScaledByIncrementSize">Offset from the base address.</param>
            static void InitOffsetted(
                [Out] D3D12CPUDescriptorHandle% handle, [In][IsReadOnly] D3D12CPUDescriptorHandle% base,
                int offsetScaledByIncrementSize
            );

            /// <summary>
            /// Initializes a D3D12CPUDescriptorHandle structure with an offset, using the
            /// specified number of descriptors of the given size.
            /// </summary>
            /// <param name="handle">Output of the initialized structure.</param>
            /// <param name="base">Address used in initialization.</param>
            /// <param name="offsetInDescriptors">The number of descriptors by which to increment. from
            /// other address.</param>
            /// <param name="descriptorIncrementSize">The amount by which to increment for
            /// each descriptor, including padding.</param>
            static void InitOffsetted(
                [Out] D3D12CPUDescriptorHandle% handle, [In][IsReadOnly] D3D12CPUDescriptorHandle% base,
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
            /// Creates a new instance of a CD3DX12_RESOURCE_DESC
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
    }
}