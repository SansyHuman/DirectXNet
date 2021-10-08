#pragma once

#include "../pch.h"
#include "D3D12Object.h"
#include "../Common/Result.h"
#include "../Common/CommonStructs.h"
#include "D3D12Structs.h"
#include "../Common/DXResourceHandle.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DirectX12
    {
        ref class D3D12CommandQueue;
        ref class D3D12CommandAllocator;
        ref class D3D12CommandList;
        ref class D3D12PipelineState;
        ref class D3D12DescriptorHeap;
        ref class D3D12RootSignature;
        ref class D3D12Fence;
        ref class D3D12Heap;
        ref class D3D12DeviceChild;
        ref class D3D12Pageable;
        ref class D3D12QueryHeap;
        ref class D3D12CommandSignature;

        /// <summary>
        /// Represents a virtual adapter; it is used to create command allocators, command lists,
        /// command queues, fences, resources, pipeline state objects, heaps, root signatures, samplers,
        /// and many resource views.
        /// </summary>
        public ref class D3D12Device : D3D12Object
        {
        private:
            ::ID3D12Device* pDevice;

        internal:
            D3D12Device(::ID3D12Device* pDevice);
            D3D12Device() : D3D12Object() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Device.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the number of physical adapters (nodes) that are associated with this device.
            /// </summary>
            property unsigned int NodeCount
            {
                unsigned int get();
            }

            /// <summary>
            /// Creates a command queue.
            /// </summary>
            /// <typeparam name="T">Type of the command queue.</typeparam>
            /// <param name="desc">Specifies a D3D12CommandQueueDesc that describes the command queue.
            /// </param>
            /// <returns>Command queue if succeeded.</returns>
            generic <typename T> where T : D3D12CommandQueue
            T CreateCommandQueue(
                [In][IsReadOnly] D3D12CommandQueueDesc% desc
            );

            /// <summary>
            /// Creates a command allocator object.
            /// </summary>
            /// <param name="type">A D3D12CommandListType-typed value that specifies the type of
            /// command allocator to create. The type of command allocator can be the type that
            /// records either direct command lists or bundles.</param>
            /// <returns>Command allocator if succeeded.</returns>
            D3D12CommandAllocator^ CreateCommandAllocator(
                D3D12CommandListType type
            );

            /// <summary>
            /// Creates a graphics pipeline state object.
            /// </summary>
            /// <param name="desc">A D3D12GraphicsPipelineStateDesc structure that describes
            /// graphics pipeline state.</param>
            /// <returns>Pipeline state object if succeeded.</returns>
            D3D12PipelineState^ CreateGraphicsPipelineState(
                [In][IsReadOnly] D3D12GraphicsPipelineStateDesc% desc
            );

            /// <summary>
            /// Creates a compute pipeline state object.
            /// </summary>
            /// <param name="desc">A D3D12ComputePipelineStateDesc structure that describes
            /// compute pipeline state.</param>
            /// <returns>Pipeline state object if succeeded.</returns>
            D3D12PipelineState^ CreateComputePipelineState(
                [In][IsReadOnly] D3D12ComputePipelineStateDesc% desc
            );

            /// <summary>
            /// Creates a command list.
            /// </summary>
            /// <typeparam name="T">Type of the command list.</typeparam>
            /// <param name="nodeMask">For single-GPU operation, set this to zero. If there are
            /// multiple GPU nodes, then set a bit to identify the node (the device's physical adapter)
            /// for which to create the command list. Each bit in the mask corresponds to a single node.
            /// Only one bit must be set.</param>
            /// <param name="type">Specifies the type of command list to create.</param>
            /// <param name="allocator">A command allocator object from which the device creates
            /// command lists.</param>
            /// <param name="initialState">An optional pipeline state object that contains the initial
            /// pipeline state for the command list. If it is null, then the runtime sets a dummy
            /// initial pipeline state, so that drivers don't have to deal with undefined state. The
            /// overhead for this is low, particularly for a command list, for which the overall cost of
            /// recording the command list likely dwarfs the cost of a single initial state setting. So
            /// there's little cost in not setting the initial pipeline state parameter, if doing so is
            /// inconvenient.</param>
            /// <returns>Command list if succeeded.</returns>
            generic <typename T> where T : D3D12CommandList
            T CreateCommandList(
                unsigned int nodeMask,
                D3D12CommandListType type,
                D3D12CommandAllocator^ allocator,
                [Optional] D3D12PipelineState^ initialState
            );

            /// <summary>
            /// Gets information about the features that are supported by the current graphics driver.
            /// </summary>
            /// <typeparam name="T">Structs that contain feature data.</typeparam>
            /// <param name="feature">A constant from the D3D12Feature enumeration describing the
            /// feature(s) that you want to query for support.</param>
            /// <param name="featureSupportData">A reference to a data structure that corresponds to
            /// the value of the Feature parameter.</param>
            /// <returns>Result code.</returns>
            generic <typename T> where T : value class, ID3D12FeatureData
            Result CheckFeatureSupport(D3D12Feature feature, T% featureSupportData);

            /// <summary>
            /// Creates a descriptor heap object.
            /// </summary>
            /// <param name="descriptorHeapDesc">A D3D12DescriptorHeapDesc structure that describes
            /// the heap.</param>
            /// <returns>Descriptor heap if succeeded.</returns>
            D3D12DescriptorHeap^ CreateDescriptorHeap(
                [In][IsReadOnlyAttribute] D3D12DescriptorHeapDesc% descriptorHeapDesc
            );

            /// <summary>
            /// Gets the size of the handle increment for the given type of descriptor heap. This
            /// value is typically used to increment a handle into a descriptor array by the
            /// correct amount.
            /// </summary>
            /// <param name="type">The D3D12DescriptorHeapType-typed value that specifies the type
            /// of descriptor heap to get the size of the handle increment for.</param>
            /// <returns>The descriptor size.</returns>
            unsigned int GetDescriptorHandleIncrementSize(D3D12DescriptorHeapType type);

            /// <summary>
            /// Creates a root signature layout.
            /// </summary>
            /// <param name="nodeMask">For single GPU operation, set this to zero. If there are multiple
            /// GPU nodes, set bits to identify the nodes (the device's physical adapters) to which the
            /// root signature is to apply. Each bit in the mask corresponds to a single node.</param>
            /// <param name="pBlobWithRootSignature">A pointer to the source data for the serialized
            /// signature.</param>
            /// <param name="blobLengthInBytes">The size, in bytes, of the block of memory that
            /// pBlobWithRootSignature points to.</param>
            /// <returns>Root signature if succeeded.</returns>
            D3D12RootSignature^ CreateRootSignature(
                unsigned int nodeMask,
                IntPtr pBlobWithRootSignature,
                SIZE_T blobLengthInBytes
            );

            /// <summary>
            /// Creates a constant-buffer view for accessing resource data.
            /// </summary>
            /// <param name="desc">A D3D12ConstantBufferViewDesc structure that describes the
            /// constant-buffer view.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents
            /// the start of the heap that holds the constant-buffer view.</param>
            void CreateConstantBufferView(
                D3D12ConstantBufferViewDesc desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Creates a shader-resource view for accessing data in a resource.
            /// </summary>
            /// <param name="resource">A D3D12Resource object that represents the shader resource. At
            /// least one of resource or desc must be provided. A null resource is used to initialize
            /// a null descriptor, which guarantees D3D11-like null binding behavior(reading 0s, writes
            /// are discarded), but must have a valid desc in order to determine the descriptor type.
            /// </param>
            /// <param name="desc">A D3D12ShaderResourceViewDesc structure that describes the
            /// shader-resource view. A null desc is used to initialize a default descriptor, if
            /// possible. This behavior is identical to the D3D11 null descriptor behavior, where
            /// defaults are filled in. This behavior inherits the resource formatand dimension(if not
            /// typeless) and for buffers SRVs target a full bufferand are typed(not raw or structured),
            /// and for textures SRVs target a full texture, all mipsand all array slices. Not all
            /// resources support null descriptor initialization.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents the
            /// shader-resource view. This handle can be created in a shader-visible or
            /// non-shader-visible descriptor heap.</param>
            void CreateShaderResourceView(
                D3D12Resource^ resource,
                Nullable<D3D12ShaderResourceViewDesc> desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Creates a view for unordered accessing.
            /// </summary>
            /// <param name="resource">A D3D12Resource object that represents the unordered access. At
            /// least one of resource or desc must be provided. A null resource is used to initialize a
            /// null descriptor, which guarantees Direct3D 11-like null binding behavior(reading 0s,
            /// writes are discarded), but must have a valid desc in order to determine the descriptor
            /// type.</param>
            /// <param name="counterResource">The D3D12Resource for the counter (if any) associated
            /// with the UAV. If counterResource is not specified, then the CounterOffsetInBytes member
            /// of the D3D12BufferUav structure must be 0. If dounterResource is specified, then there is
            /// a counter associated with the UAV, and the runtime performs validation of the following
            /// requirements :
            /// <para>The StructureByteStride member of the D3D12BufferUav structure must be greater
            /// than 0.</para>
            /// <para>The format must be FORMAT_UNKNOWN.</para>
            /// <para>The D3D12BufferUavFlags::Raw flag must not be set.</para>
            /// <para>Both of the resources(resource and counterResource) must be buffers.</para>
            /// <para>The CounterOffsetInBytes member of the D3D12BufferUav structure must be a multiple
            /// of 4096, and must be within the range of the counter resource.</para>
            /// <para>resource cannot be null.</para>
            /// <para>desc cannot be null.</para></param>
            /// <param name="desc">A D3D12UnorderedAccessViewDesc structure that describes the
            /// unordered-access view. A null desc is used to initialize a default descriptor, if
            /// possible. This behavior is identical to the D3D11 null descriptor behavior, where
            /// defaults are filled in. This behavior inherits the resource formatand dimension(if not
            /// typeless) and for buffers UAVs target a full bufferand are typed, and for textures UAVs
            /// target the first mipand all array slices. Not all resources support null descriptor
            /// initialization.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents the
            /// start of the heap that holds the unordered-access view.</param>
            void CreateUnorderedAccessView(
                D3D12Resource^ resource,
                D3D12Resource^ counterResource,
                Nullable<D3D12UnorderedAccessViewDesc> desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// D3D12_CPU_DESCRIPTOR_HANDLE
            /// </summary>
            /// <param name="resource">A D3D12Resource object that represents the render target. At
            /// least one of resource or resc must be provided. A null pResource is used to initialize a
            /// null descriptor, which guarantees D3D11-like null binding behavior(reading 0s, writes
            /// are discarded), but must have a valid desc in order to determine the descriptor type.
            /// </param>
            /// <param name="desc">A D3D12RenderTargetViewDesc structure that describes the render-target
            /// view. A null desc is used to initialize a default descriptor, if possible.This behavior
            /// is identical to the D3D11 null descriptor behavior, where defaults are filled in. This
            /// behavior inherits the resource formatand dimension(if not typeless) and RTVs target the
            /// first mipand all array slices. Not all resources support null descriptor
            /// initialization.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents the
            /// destination where the newly-created render target view will reside.</param>
            void CreateRenderTargetView(
                D3D12Resource^ resource,
                Nullable<D3D12RenderTargetViewDesc> desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Creates a depth-stencil view for accessing resource data.
            /// </summary>
            /// <param name="resource">A D3D12Resource object that represents the depth stencil. At least
            /// one of resource or desc must be provided .A null resource is used to initialize a null
            /// descriptor, which guarantees D3D11-like null binding behavior(reading 0s, writes are
            /// discarded), but must have a valid desc in order to determine the descriptor type.</param>
            /// <param name="desc">A D3D12DepthStencilViewDesc structure that describes the depth-stencil
            /// view. A null desc is used to initialize a default descriptor, if possible. This behavior
            /// is identical to the D3D11 null descriptor behavior, where defaults are filled in. This
            /// behavior inherits the resource formatand dimension(if not typeless) and DSVs target the
            /// first mipand all array slices. Not all resources support null descriptor
            /// initialization.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents the
            /// start of the heap that holds the depth-stencil view.</param>
            void CreateDepthStencilView(
                D3D12Resource^ resource,
                Nullable<D3D12DepthStencilViewDesc> desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Create a sampler object that encapsulates sampling information for a texture.
            /// </summary>
            /// <param name="desc">A D3D12SamplerDesc structure that describes the sampler.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents
            /// the start of the heap that holds the sampler.</param>
            void CreateSampler(
                [In][IsReadOnly] D3D12SamplerDesc% desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Copies descriptors from a source to a destination.
            /// </summary>
            /// <param name="destDescriptorRangeStarts">An array of D3D12CPUDescriptorHandle objects to
            /// copy to. All the destinationand source descriptors must be in heaps of the same
            /// D3D12DescriptorHeapType.</param>
            /// <param name="destDescriptorRangeSizes">An array of destination descriptor range sizes
            /// to copy to.</param>
            /// <param name="srcDescriptorRangeStarts">An array of D3D12CPUDescriptorHandle objects
            /// to copy from.</param>
            /// <param name="srcDescriptorRangeSizes">An array of source descriptor range sizes to
            /// copy from.</param>
            /// <param name="descriptorHeapsType">The D3D12DescriptorHeapType-typed value that specifies
            /// the type of descriptor heap to copy with. This is required as different descriptor types
            /// may have different sizes. Both the sourceand destination descriptor heaps must have the
            /// same type, else the debug layer will emit an error.</param>
            void CopyDescriptors(
                array<D3D12CPUDescriptorHandle>^ destDescriptorRangeStarts,
                array<unsigned int>^ destDescriptorRangeSizes,
                array<D3D12CPUDescriptorHandle>^ srcDescriptorRangeStarts,
                array<unsigned int>^ srcDescriptorRangeSizes,
                D3D12DescriptorHeapType descriptorHeapsType
            );

            /// <summary>
            /// Copies descriptors from a source to a destination.
            /// </summary>
            /// <param name="numDescriptors">The number of descriptors to copy.</param>
            /// <param name="destDescriptorRangeStart">A D3D12CPUDescriptorHandle that describes the
            /// destination descriptors to start to copy to. The destinationand source descriptors must
            /// be in heaps of the same D3D12DescriptorHeapType.</param>
            /// <param name="srcDescriptorRangeStart">A D3D12CPUDescriptorHandle that describes the
            /// source descriptors to start to copy from.</param>
            /// <param name="descriptorHeapsType">The D3D12DescriptorHeapType-typed value that specifies
            /// the type of descriptor heap to copy with. This is required as different descriptor types
            /// may have different sizes. Both the sourceand destination descriptor heaps must have the
            /// same type, else the debug layer will emit an error.</param>
            void CopyDescriptorsSimple(
                unsigned int numDescriptors,
                D3D12CPUDescriptorHandle destDescriptorRangeStart,
                D3D12CPUDescriptorHandle srcDescriptorRangeStart,
                D3D12DescriptorHeapType descriptorHeapsType
            );

            /// <summary>
            /// Gets the size and alignment of memory required for a collection of resources on
            /// this adapter.
            /// </summary>
            /// <param name="visibleMask">For single-GPU operation, set this to zero. If there are
            /// multiple GPU nodes, then set bits to identify the nodes (the device's physical adapters).
            /// Each bit in the mask corresponds to a single node.</param>
            /// <param name="resourceDescs">An array of D3D12ResourceDesc structures that described
            /// the resources to get info about.</param>
            /// <returns>A D3D12ResourceAllocationInfo structure that provides info about video memory
            /// allocated for the specified array of resources. If an error occurs, then
            /// D3D12ResourceAllocationInfo::SizeInBytes equals UInt64::MaxValue.</returns>
            D3D12ResourceAllocationInfo GetResourceAllocationInfo(
                unsigned int visibleMask,
                ...array<D3D12ResourceDesc>^ resourceDescs
            );

            /// <summary>
            /// Divulges the equivalent custom heap properties that are used for non-custom heap types,
            /// based on the adapter's architectural properties.
            /// </summary>
            /// <param name="nodeMask">For single-GPU operation, set this to zero. If there are multiple
            /// GPU nodes, set a bit to identify the node (the device's physical adapter). Each bit in
            /// the mask corresponds to a single node. Only 1 bit must be set.</param>
            /// <param name="heapType">A D3D12_HEAP_TYPE-typed value that specifies the heap to get
            /// properties for. D3D12_HEAP_TYPE_CUSTOM is not supported as a parameter value.</param>
            /// <returns>A D3D12HeapProperties structure that provides properties for the specified heap.
            /// The Type member of the returned D3D12HeapProperties is always D3D12HeapType::Custom.
            /// </returns>
            D3D12HeapProperties GetCustomHeapProperties(
                unsigned int nodeMask,
                D3D12HeapType heapType
            );

            /// <summary>
            /// Creates both a resource and an implicit heap, such that the heap is big enough to
            /// contain the entire resource, and the resource is mapped to the heap.
            /// </summary>
            /// <typeparam name="T">Type of the resource.</typeparam>
            /// <param name="heapProperties">A D3D12HeapProperties structure that provides properties
            /// for the resource's heap.</param>
            /// <param name="heapFlags">Heap options, as a bitwise-OR'd combination of D3D12HeapFlags
            /// enumeration constants.</param>
            /// <param name="desc">A D3D12ResourceDesc structure that describes the resource.</param>
            /// <param name="initialResourceState">The initial state of the resource, as a bitwise-OR'd
            /// combination of D3D12ResourceStates enumeration constants. When you create a resource
            /// together with a D3D12HeapType::Upload heap, you must set initialResourceState to
            /// D3D12ResourceStates::GenericRead.
            /// When you create a resource together with a D3D12HeapType::Readback heap, you must set
            /// initialResourceState to D3D12ResourceStates::CopyDest.</param>
            /// <param name="optimizedClearValue">Specifies a D3D12ClearValue structure that describes
            /// the default value for a clear color. optimizedClearValue specifies a value for which
            /// clear operations are most optimal.When the created resource is a texture with either the
            /// D3D12ResourceFlags::AllowRenderTarrget or D3D12ResourceFlags::AllowDepthStencil flags,
            /// you should choose the value with which the clear operation will most commonly be
            /// called. You can call the clear operation with other values, but those operations won't
            /// be as efficient as when the value matches the one passed in to resource creation.
            /// When you use D3D12ResourceDimension::Buffer, you must set pOptimizedClearValue to
            /// null.</param>
            /// <returns>Created resource if succeeded.</returns>
            generic <typename T> where T : D3D12Resource
            T CreateCommittedResource(
                [In][IsReadOnly] D3D12HeapProperties% heapProperties,
                D3D12HeapFlags heapFlags,
                [In][IsReadOnly] D3D12ResourceDesc% desc,
                D3D12ResourceStates initialResourceState,
                Nullable<D3D12ClearValue> optimizedClearValue
            );

            /// <summary>
            /// Creates a heap that can be used with placed resources and reserved resources.
            /// </summary>
            /// <typeparam name="T">Type of heap.</typeparam>
            /// <param name="desc">A D3D12HeapDesc structure that describes the heap.</param>
            /// <returns>Heap if succeeded.</returns>
            generic <typename T> where T : D3D12Heap
            T CreateHeap(
                [In][IsReadOnly] D3D12HeapDesc% desc
            );

            /// <summary>
            /// Creates a resource that is placed in a specific heap. Placed resources are the lightest
            /// weight resource objects available, and are the fastest to create and destroy.
            /// </summary>
            /// <typeparam name="T">Type of the resource.</typeparam>
            /// <param name="heap">A D3D12Heap object that represents the heap in which the resource
            /// is placed.</param>
            /// <param name="heapOffset">The offset, in bytes, to the resource. The HeapOffset must be a
            /// multiple of the resource's alignment, and heapOffset plus the resource size must be
            /// smaller than or equal to the heap size. GetResourceAllocationInfo must be used to
            /// understand the sizes of texture resources.</param>
            /// <param name="desc">A D3D12ResourceDesc structure that describes the resource.</param>
            /// <param name="initialState">The initial state of the resource, as a bitwise-OR'd
            /// combination of D3D12ResourceStates enumeration constants.
            /// When a resource is created together with a D3D12HeapType::Upload heap, initialState must
            /// be D3D12ResourceStates::GenericRead. When a resource is created together with a
            /// D3D12HeapType::Readback heap, InitialState must be D3D12ResourceStates::CopyDest.</param>
            /// <param name="optimizedClearValue">Specifies a D3D12ClearValue structure that describes
            /// the default value for a clear color. optimizedClearValue specifies a value for which
            /// clear operations are most optimal.When the created resource is a texture with either the
            /// D3D12ResourceFlags::AllowRenderTarrget or D3D12ResourceFlags::AllowDepthStencil flags,
            /// you should choose the value with which the clear operation will most commonly be
            /// called. You can call the clear operation with other values, but those operations won't
            /// be as efficient as when the value matches the one passed in to resource creation.
            /// When you use D3D12ResourceDimension::Buffer, you must set pOptimizedClearValue to
            /// null.</param>
            /// <returns>Resource if succeeded.</returns>
            generic <typename T> where T : D3D12Resource
            T CreatePlacedResource(
                D3D12Heap^ heap,
                unsigned long long heapOffset,
                [In][IsReadOnly] D3D12ResourceDesc% desc,
                D3D12ResourceStates initialState,
                Nullable<D3D12ClearValue> optimizedClearValue
            );

            /// <summary>
            /// Creates a resource that is reserved, and not yet mapped to any pages in a heap.
            /// </summary>
            /// <typeparam name="T">Type of the resource.</typeparam>
            /// <param name="desc">A D3D12ResourceDesc structure that describes the resource.</param>
            /// <param name="initialState">The initial state of the resource, as a bitwise-OR'd
            /// combination of D3D12ResourceStates enumeration constants.</param>
            /// <param name="optimizedClearValue">Specifies a D3D12ClearValue structure that describes
            /// the default value for a clear color. optimizedClearValue specifies a value for which
            /// clear operations are most optimal.When the created resource is a texture with either the
            /// D3D12ResourceFlags::AllowRenderTarrget or D3D12ResourceFlags::AllowDepthStencil flags,
            /// you should choose the value with which the clear operation will most commonly be
            /// called. You can call the clear operation with other values, but those operations won't
            /// be as efficient as when the value matches the one passed in to resource creation.
            /// When you use D3D12ResourceDimension::Buffer, you must set pOptimizedClearValue to
            /// null.</param>
            /// <returns>Resource if succeeded.</returns>
            generic <typename T> where T : D3D12Resource
            T CreateReservedResource(
                [In][IsReadOnly] D3D12ResourceDesc% desc,
                D3D12ResourceStates initialState,
                Nullable<D3D12ClearValue> optimizedClearValue
            );

            /// <summary>
            /// Creates a shared handle to a heap, resource, or fence object.
            /// </summary>
            /// <param name="object">A D3D12DeviceChild object that represents the heap, resource,
            /// or fence object to create for sharing. The following interfaces (derived from
            /// D3D12DeviceChild) are supported: D3D12Heap, D3D12Resource, D3D12Fence.</param>
            /// <param name="access">Currently the only value this parameter accepts is
            /// AccessRights::GenericAll</param>
            /// <param name="attributes">A SecurityAttributes structure that contains two separate but
            /// related data members: an optional security descriptor, and a Boolean value that
            /// determines whether child processes can inherit the returned handle.
            /// Set this parameter to null if you want child processes that the application might
            /// create to not inherit the handle returned by CreateSharedHandle, and if you want the
            /// resource that is associated with the returned handle to get a default security
            /// descriptor.
            /// The lpSecurityDescriptor member of the structure specifies a SECURITY_DESCRIPTOR for the
            /// resource. Set this member to null if you want the runtime to assign a default security
            /// descriptor to the resource that is associated with the returned handle. The ACLs in the
            /// default security descriptor for the resource come from the primary or impersonation
            /// token of the creator.</param>
            /// <param name="name">A string that contains the name to associate with the shared heap.
            /// The name is limited to MAX_PATH characters. Name comparison is case-sensitive. If name
            /// matches the name of an existing resource, CreateSharedHandle fails with
            /// DXGI_ERROR_NAME_ALREADY_EXISTS. This occurs because these objects share the same
            /// namespace. The name can have a "Global" or "Local" prefix to explicitly create the
            /// object in the global or session namespace.The remainder of the name can contain any
            /// character except the backslash character(\).</param>
            /// <returns>Handle if succeeded.</returns>
            DXResourceHandle^ CreateSharedHandle(
                D3D12DeviceChild^ object,
                AccessRights access,
                [Optional] Nullable<SecurityAttributes> attributes,
                [Optional] String^ name
            );

            /// <summary>
            /// Opens a handle for shared resources, shared heaps, and shared fences, by using handle.
            /// </summary>
            /// <typeparam name="T">Type of the object. It should be one of the D3D12Heap,
            /// D3D12Resource, and D3D12Fence.</typeparam>
            /// <param name="ntHandle">The handle that was output by the call to
            /// D3D12Device::CreateSharedHandle.</param>
            /// <returns>Object if succeeded.</returns>
            generic <typename T> where T : D3D12DeviceChild
            T OpenSharedHandle(
                DXResourceHandle^ ntHandle
            );

            /// <summary>
            /// Opens a handle for shared resources, shared heaps, and shared fences, by using Name
            /// and Access.
            /// </summary>
            /// <param name="name">The name that was optionally passed as the name parameter in the
            /// call to D3D12Device::CreateSharedHandle.</param>
            /// <param name="access">The access level that was specified in the access parameter in
            /// the call to D3D12Device::CreateSharedHandle.</param>
            /// <returns>Handle if succeeded.</returns>
            DXResourceHandle^ OpenSharedHandleByName(
                String^ name,
                AccessRights access
            );

            /// <summary>
            /// Makes objects resident for the device.
            /// </summary>
            /// <param name="objects">An array of D3D12Pageable objects. Even though most D3D12 objects
            /// inherit from D3D12Pageable, residency changes are only supported on the following
            /// objects : Descriptor Heaps, Heaps, Committed Resources, and Query Heaps.</param>
            /// <returns>Result code.</returns>
            Result MakeResident(
                ...array<D3D12Pageable^>^ objects
            );

            /// <summary>
            /// Enables the page-out of data, which precludes GPU access of that data.
            /// </summary>
            /// <param name="objects">An array of D3D12Pageable objects. Even though most D3D12 objects
            /// inherit from D3D12Pageable, residency changes are only supported on the following
            /// objects : Descriptor Heaps, Heaps, Committed Resources, and Query Heaps.</param>
            /// <returns>Result code.</returns>
            Result Evict(
                ...array<D3D12Pageable^>^ objects
            );

            /// <summary>
            /// Creates a fence object.
            /// </summary>
            /// <typeparam name="T">Type of the fence.</typeparam>
            /// <param name="initialValue">The initial value for the fence.</param>
            /// <param name="flags">A combination of D3D12FenceFlags-typed values that are combined by
            /// using a bitwise OR operation. The resulting value specifies options for the fence.
            /// </param>
            /// <returns>Fence if succeeded.</returns>
            generic <typename T> where T : D3D12Fence
            T CreateFence(
                unsigned long long initialValue,
                D3D12FenceFlags flags
            );

            /// <summary>
            /// Gets the reason that the device was removed.
            /// </summary>
            /// <returns>This method returns the reason that the device was removed.</returns>
            Result GetDeviceRemovedReason();

            /// <summary>
            /// Gets a resource layout that can be copied. Helps the app fill-in
            /// D3D12PlacedSubresourceFootprint and D3D12SubresourceFootprint when suballocating space
            /// in upload heaps.
            /// </summary>
            /// <param name="resourceDesc">A description of the resource.</param>
            /// <param name="firstSubresource">Index of the first subresource in the resource. The
            /// range of valid values is 0 to 30720.</param>
            /// <param name="numSubresources">The number of subresources in the resource. The range of
            /// valid values is 0 to (30720 - firstSubresource).</param>
            /// <param name="baseOffset">The offset, in bytes, to the resource.</param>
            /// <param name="totalBytes">An output integer variable, to be filled with the total size,
            /// in bytes.</param>
            /// <param name="layouts">A buffer array (of length numSubresources) of
            /// D3D12PlacedSubresourceFootprint structures, to be filled with the description and
            /// placement of each subresource. If you do not want this info, this parameter can
            /// be null.</param>
            /// <param name="numRows">A buffer array (of length numSubresources) of integer variables,
            /// to be filled with the number of rows for each subresource. If you do not want this info,
            /// this parameter can be null.</param>
            /// <param name="rowSizeInBytes">A buffer array (of length numSubresources) of integer
            /// variables, each entry to be filled with the unpadded size in bytes of a row, of each
            /// subresource. If you do not want this info, this parameter can be null.</param>
            void GetCopyableFootprints(
                [In][IsReadOnly] D3D12ResourceDesc% resourceDesc,
                unsigned int firstSubresource,
                unsigned int numSubresources,
                unsigned long long baseOffset,
                [Out] unsigned long long% totalBytes,
                [Optional] array<D3D12PlacedSubresourceFootprint>^ layouts,
                [Optional] array<unsigned int>^ numRows,
                [Optional] array<unsigned long long>^ rowSizeInBytes
            );

            /// <summary>
            /// Creates a query heap. A query heap contains an array of queries.
            /// </summary>
            /// <param name="desc">Specifies the query heap in a D3D12QueryHeapDesc structure.</param>
            /// <returns>Query heap if succeeded.</returns>
            D3D12QueryHeap^ CreateQueryHeap(
                [In][IsReadOnly] D3D12QueryHeapDesc% desc
            );

            /// <summary>
            /// A development-time aid for certain types of profiling and experimental prototyping.
            /// </summary>
            /// <param name="enable">Specifies a bool that turns the stable power state on or off.
            /// </param>
            /// <returns>Result code.</returns>
            [Obsolete("Do not call this method in normal execution for a shipped application. This method only works while the machine is in developer mode.")]
            Result SetStablePowerState(bool enable);

            /// <summary>
            /// This method creates a command signature.
            /// </summary>
            /// <param name="desc">Describes the command signature to be created with the
            /// D3D12CommandSignatureDesc structure.</param>
            /// <param name="rootSignature">Specifies the D3D12RootSignature that the command signature
            /// applies to. The root signature is required if any of the commands in the signature will
            /// update bindings on the pipeline. If the only command present is a draw or dispatch, the
            /// root signature parameter can be set to null.</param>
            /// <returns>Command signature if succeeded.</returns>
            D3D12CommandSignature^ CreateCommandSignature(
                [In][IsReadOnly] D3D12CommandSignatureDesc% desc,
                [Optional] D3D12RootSignature^ rootSignature
            );

            /// <summary>
            /// Gets info about how a tiled resource is broken into tiles.
            /// </summary>
            /// <param name="tiledResource">Specifies a tiled D3D12Resource to get info about.</param>
            /// <param name="numTilesForEntireResource">A variable that receives the number of tiles needed
            /// to store the entire tiled resource.</param>
            /// <param name="packedMipDesc">A D3D12PackedMipInfo structure that GetResourceTiling fills
            /// with info about how the tiled resource's mipmaps are packed.</param>
            /// <param name="standardTileShapeForNonPackedMips">Specifies a D3D12TileShape structure that
            /// GetResourceTiling fills with info about the tile shape. This is info about how pixels fit in
            /// the tiles, independent of tiled resource's dimensions, not including packed mipmaps. If the
            /// entire tiled resource is packed, this parameter is meaningless because the tiled resource has
            /// no defined layout for packed mipmaps. In this situation, GetResourceTiling sets the members
            /// of D3D12TileShape to zeros.</param>
            /// <param name="numSubresourceTilings">A variable that contains the number of tiles in the
            /// subresource. On input, this is the number of subresources to query tilings for; on output,
            /// this is the number that was actually retrieved at subresourceTilingsForNonPackedMips
            /// (clamped to what's available).</param>
            /// <param name="firstSubresourceTilingToGet">The number of the first subresource tile to get.
            /// GetResourceTiling ignores this parameter if the number that numSubresourceTilings points to
            /// is 0.</param>
            /// <param name="subresourceTilingsForNonPackedMips">Specifies a D3D12SubresourceTiling array
            /// that GetResourceTiling fills with info about subresource tiles. If subresource tiles are
            /// part of packed mipmaps, GetResourceTiling sets the members of D3D12SubresourceTiling to
            /// zeros, except the startTileIndexInOverallResource member, which GetResourceTiling sets to
            /// D3D12_PACKED_TILE (0xffffffff). The D3D12_PACKED_TILE constant indicates that the whole
            /// D3D12SubresourceTiling structure is meaningless for this situation, and the info that the
            /// packedMipDesc parameter points to applies.</param>
            void GetResourceTiling(
                D3D12Resource^ tiledResource,
                [Out] unsigned int% numTilesForEntireResource,
                [Out] D3D12PackedMipInfo% packedMipDesc,
                [Out] D3D12TileShape% standardTileShapeForNonPackedMips,
                unsigned int% numSubresourceTilings,
                unsigned int firstSubresourceTilingToGet,
                array<D3D12SubresourceTiling>^ subresourceTilingsForNonPackedMips
            );

            /// <summary>
            /// Gets a locally unique identifier for the current device (adapter).
            /// </summary>
            property Luid AdapterLuid
            {
                Luid get();
            }


        internal:
            void GetCopyableFootprints(
                D3D12ResourceDesc* resourceDesc,
                unsigned int firstSubresource,
                unsigned int numSubresources,
                unsigned long long baseOffset,
                D3D12PlacedSubresourceFootprint* layouts,
                unsigned int* numRows,
                unsigned long long* rowSizeInBytes,
                unsigned long long* totalBytes
            );
        };
    }
}