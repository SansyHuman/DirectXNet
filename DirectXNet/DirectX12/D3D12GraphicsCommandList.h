#pragma once

#include "../pch.h"
#include "D3D12CommandList.h"
#include "../Common/Result.h"
#include "../Common/CommonStructs.h"
#include "../DXGI/DXGIStructs.h"
#include "D3D12Structs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D3D;
using namespace DirectXNet::DXGI;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DirectX12
    {
        ref class D3D12CommandAllocator;
        ref class D3D12PipelineState;
        ref class D3D12Resource;
        ref class D3D12DescriptorHeap;
        ref class D3D12RootSignature;
        ref class D3D12QueryHeap;
        ref class D3D12CommandSignature;

        /// <summary>
        /// Encapsulates a list of graphics commands for rendering. Includes APIs for instrumenting
        /// the command list execution, and for setting and clearing the pipeline state.
        /// </summary>
        public ref class D3D12GraphicsCommandList : D3D12CommandList
        {
        private:
            ::ID3D12GraphicsCommandList* pGraphicsList;

        internal:
            D3D12GraphicsCommandList(::ID3D12GraphicsCommandList* pGraphicsList);
            D3D12GraphicsCommandList() : D3D12CommandList() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12GraphicsCommandList.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Indicates that recording to the command list has finished.
            /// </summary>
            /// <returns>Result code.</returns>
            Result Close();

            /// <summary>
            /// Resets a command list back to its initial state as if a new command list was
            /// just created.
            /// </summary>
            /// <param name="allocator">A D3D12CommandAllocator object that the device creates
            /// command lists from.</param>
            /// <param name="initialState">A D3D12PipelineState object that contains the initial
            /// pipeline state for the command list. This is optional and can be null. If null, the
            /// runtime sets a dummy initial pipeline state so that drivers don't have to deal with
            /// undefined state. The overhead for this is low, particularly for a command list, for
            /// which the overall cost of recording the command list likely dwarfs the cost of one
            /// initial state setting. So there is little cost in not setting the initial pipeline
            /// state parameter if it isn't convenient.</param>
            /// <returns>Result code.</returns>
            Result Reset(
                D3D12CommandAllocator^ allocator,
                [Optional] D3D12PipelineState^ initialState
            );

            /// <summary>
            /// Resets the state of a direct command list back to the state it was in when the
            /// command list was created.
            /// </summary>
            /// <param name="pipelineState">A D3D12PipelineState object that contains the
            /// initial pipeline state for the command list.</param>
            void ClearState(
                [Optional] D3D12PipelineState^ pipelineState
            );

            /// <summary>
            /// Draws non-indexed, instanced primitives.
            /// </summary>
            /// <param name="vertexCountPerInstance">Number of vertices to draw.</param>
            /// <param name="instanceCount">Number of instances to draw.</param>
            /// <param name="startVertexLocation">Index of the first vertex.</param>
            /// <param name="startInstanceLocation">A value added to each index before reading
            /// per-instance data from a vertex buffer.</param>
            void DrawInstanced(
                unsigned int vertexCountPerInstance,
                unsigned int instanceCount,
                unsigned int startVertexLocation,
                unsigned int startInstanceLocation
            );

            /// <summary>
            /// Draws indexed, instanced primitives.
            /// </summary>
            /// <param name="indexCountPerInstance">Number of indices read from the index buffer for
            /// each instance.</param>
            /// <param name="instanceCount">Number of instances to draw.</param>
            /// <param name="startIndexLocation">The location of the first index read by the GPU from
            /// the index buffer.</param>
            /// <param name="baseVertexLocation">A value added to each index before reading a vertex
            /// from the vertex buffer.</param>
            /// <param name="startInstanceLocation">A value added to each index before reading
            /// per-instance data from a vertex buffer.</param>
            void DrawIndexedInstanced(
                unsigned int indexCountPerInstance,
                unsigned int instanceCount,
                unsigned int startIndexLocation,
                int baseVertexLocation,
                unsigned int startInstanceLocation
            );

            /// <summary>
            /// Executes a command list from a thread group.
            /// </summary>
            /// <param name="threadGroupCountX">The number of groups dispatched in the x direction.
            /// threadGroupCountX must be less than or equal to 65535.</param>
            /// <param name="threadGroupCountY">The number of groups dispatched in the y direction.
            /// threadGroupCountY must be less than or equal to 65535.</param>
            /// <param name="threadGroupCountZ">The number of groups dispatched in the z direction.
            /// threadGroupCountY must be less than or equal to 65535. In feature level 10 the value
            /// for threadGroupCountZ must be 1.</param>
            void Dispatch(
                unsigned int threadGroupCountX,
                unsigned int threadGroupCountY,
                unsigned int threadGroupCountZ
            );

            /// <summary>
            /// Copies a region of a buffer from one resource to another.
            /// </summary>
            /// <param name="dstBuffer">Specifies the destination D3D12Resource.</param>
            /// <param name="dstOffset">Specifies a offset (in bytes) into the destination resource.
            /// </param>
            /// <param name="srcBuffer">Specifies the source D3D12Resource.</param>
            /// <param name="srcOffset">Specifies a offset (in bytes) into the source resource, to start
            /// the copy from.</param>
            /// <param name="numBytes">Specifies the number of bytes to copy.</param>
            void CopyBufferRegion(
                D3D12Resource^ dstBuffer,
                unsigned long long dstOffset,
                D3D12Resource^ srcBuffer,
                unsigned long long srcOffset,
                unsigned long long numBytes
            );

            /// <summary>
            /// This method uses the GPU to copy texture data between two locations. Both the source
            /// and the destination may reference texture data located within either a buffer resource
            /// or a texture resource.
            /// </summary>
            /// <param name="dst">Specifies the destination D3D12TextureCopyLocation.
            /// The subresource referred to must be in the D3D12ResourceState::CopyDest state.</param>
            /// <param name="dstX">The x-coordinate of the upper left corner of the destination region.
            /// </param>
            /// <param name="dstY">The y-coordinate of the upper left corner of the destination region.
            /// For a 1D subresource, this must be zero.</param>
            /// <param name="dstZ">The z-coordinate of the upper left corner of the destination region.
            /// For a 1D or 2D subresource, this must be zero.</param>
            /// <param name="src">Specifies the source D3D12TextureCopyLocation. The subresource
            /// referred to must be in the D3D12ResourceState::CopySource state.</param>
            /// <param name="srcBox">Specifies an optional D3D12Box that sets the size of the
            /// source texture to copy.</param>
            void CopyTextureRegion(
                [In][IsReadOnly] D3D12TextureCopyLocation% dst,
                unsigned int dstX,
                unsigned int dstY,
                unsigned int dstZ,
                [In][IsReadOnly] D3D12TextureCopyLocation% src,
                [Optional] Nullable<D3D12Box> srcBox
            );

            /// <summary>
            /// Copies the entire contents of the source resource to the destination resource.
            /// </summary>
            /// <param name="dstResource">A D3D12Resource interface that represents the
            /// destination resource.</param>
            /// <param name="srcResource">A D3D12Resource interface that represents the
            /// source resource.</param>
            void CopyResource(
                D3D12Resource^ dstResource,
                D3D12Resource^ srcResource
            );

            /// <summary>
            /// Copies tiles from buffer to tiled resource or vice versa.
            /// </summary>
            /// <param name="tiledResource">A tiled resource.</param>
            /// <param name="tileRegionStartCoordinate">A D3D12TiledResourceCoordinate structure that
            /// describes the starting coordinates of the tiled resource.</param>
            /// <param name="tileRegionSize">A D3D12TileRegionSize structure that describes the size of
            /// the tiled region.</param>
            /// <param name="buffer">A D3D12Resource that represents a default, dynamic, or staging
            /// buffer.</param>
            /// <param name="bufferStartOffsetInBytes">The offset in bytes into the buffer at buffer
            /// to start the operation.</param>
            /// <param name="flags">A combination of D3D12TileCopyFlags-typed values that are combined
            /// by using a bitwise OR operation and that identifies how to copy tiles.</param>
            void CopyTiles(
                D3D12Resource^ tiledResource,
                [In][IsReadOnly] D3D12TiledResourceCoordinate% tileRegionStartCoordinate,
                [In][IsReadOnly] D3D12TileRegionSize% tileRegionSize,
                D3D12Resource^ buffer,
                unsigned long long bufferStartOffsetInBytes,
                D3D12TileCopyFlags flags
            );

            /// <summary>
            /// Copy a multi-sampled resource into a non-multi-sampled resource.
            /// </summary>
            /// <param name="dstResource">Destination resource. Must be a created on a
            /// D3D12HeapType::Default heap and be single-sampled.</param>
            /// <param name="dstSubresource">A zero-based index, that identifies the destination
            /// subresource. Use D3D12::CalcSubresource to calculate the subresource index if the
            /// parent resource is complex.</param>
            /// <param name="srcResource">Source resource. Must be multisampled.</param>
            /// <param name="srcSubresource">The source subresource of the source resource.</param>
            /// <param name="format">A DXGIFormat that indicates how the multisampled resource will
            /// be resolved to a single-sampled resource.</param>
            void ResolveSubresource(
                D3D12Resource^ dstResource,
                unsigned int dstSubresource,
                D3D12Resource^ srcResource,
                unsigned int srcSubresource,
                DXGIFormat format
            );

            /// <summary>
            /// Bind information about the primitive type, and data order that describes input data
            /// for the input assembler stage.
            /// </summary>
            /// <param name="primitiveTopology">The type of primitive and ordering of the
            /// primitive data.</param>
            void IASetPrimitiveTopology(
                D3DPrimitiveTopology primitiveTopology
            );

            /// <summary>
            /// Bind an array of viewports to the rasterizer stage of the pipeline.
            /// </summary>
            /// <param name="viewports">An array of D3D12Viewport structures to bind to the device.
            /// </param>
            void RSSetViewports(
                ...array<D3D12Viewport>^ viewports
            );

            /// <summary>
            /// Binds an array of scissor rectangles to the rasterizer stage.
            /// </summary>
            /// <param name="rects">An array of scissor rectangles.</param>
            void RSSetScissorRects(
                ...array<Rect>^ rects
            );

            /// <summary>
            /// Sets the blend factor that modulate values for a pixel shader, render target, or both.
            /// </summary>
            /// <param name="blendFactor">Blend factors for each RGBA component.
            /// If you pass null, then the runtime uses or stores a blend factor equal to { 1, 1, 1, 1 }.
            /// </param>
            void OMSetBlendFactor(
                [Optional] Nullable<D3DColorValue> blendFactor
            );

            /// <summary>
            /// Sets the reference value for depth stencil tests.
            /// </summary>
            /// <param name="stencilRef">Reference value to perform against when doing a depth-stencil
            /// test.</param>
            void OMSetStencilRef(unsigned int stencilRef);

            /// <summary>
            /// Sets all shaders and programs most of the fixed-function state of the graphics
            /// processing unit (GPU) pipeline.
            /// </summary>
            /// <param name="pipelineState">A D3D12PipelineState containing the pipeline state data.
            /// </param>
            void SetPipelineState(D3D12PipelineState^ pipelineState);

            /// <summary>
            /// Notifies the driver that it needs to synchronize multiple accesses to resources.
            /// </summary>
            /// <param name="barriers">An array of barrier descriptions.</param>
            void ResourceBarrier(
                ...array<D3D12ResourceBarrier>^ barriers
            );

            /// <summary>
            /// Executes a bundle.
            /// </summary>
            /// <param name="commandList">Specifies the D3D12GraphicsCommandList that determines
            /// the bundle to be executed.</param>
            void ExecuteBundle(D3D12GraphicsCommandList^ commandList);

            /// <summary>
            /// Changes the currently bound descriptor heaps that are associated with a command list.
            /// </summary>
            /// <param name="descriptorHeaps">An array of ID3D12DescriptorHeap objects for the heaps
            /// to set on the command list. You can only bind descriptor heaps of type
            /// D3D12DescriptorHeapType::CbvSrvUav and D3D12DescriptorHeapType::D3D12DescriptorHeapType.
            /// Only one descriptor heap of each type can be set at one time, which means a maximum of 2
            /// heaps(one sampler, one CBV / SRV / UAV) can be set at one time.</param>
            void SetDescriptorHeaps(...array<D3D12DescriptorHeap^>^ descriptorHeaps);

            /// <summary>
            /// Sets the layout of the compute root signature.
            /// </summary>
            /// <param name="rootSignature">A D3D12RootSignature object.</param>
            void SetComputeRootSignature(
                D3D12RootSignature^ rootSignature
            );

            /// <summary>
            /// Sets the layout of the graphics root signature.
            /// </summary>
            /// <param name="rootSignature">A D3D12RootSignature object.</param>
            void SetGraphicsRootSignature(
                D3D12RootSignature^ rootSignature
            );

            /// <summary>
            /// Sets a descriptor table into the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="baseDescriptor">A GPU_descriptor_handle object for the base descriptor
            /// to set.</param>
            void SetComputeRootDescriptorTable(
                unsigned int rootParameterIndex,
                D3D12GPUDescriptorHandle baseDescriptor
            );

            /// <summary>
            /// Sets a descriptor table into the graphics root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="baseDescriptor">A GPU_descriptor_handle object for the base descriptor
            /// to set.</param>
            void SetGraphicsRootDescriptorTable(
                unsigned int rootParameterIndex,
                D3D12GPUDescriptorHandle baseDescriptor
            );

            /// <summary>
            /// Sets a constant in the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="srcData">The source data for the constant to set. Convert a data
            /// into binary and again to uint using BitConverter or something else.</param>
            /// <param name="destOffsetIn32BitValue">The offset, in 32-bit values, to set the constant
            /// in the root signature.</param>
            void SetComputeRoot32BitConstant(
                unsigned int rootParameterIndex,
                unsigned int srcData,
                unsigned int destOffsetIn32BitValue
            );

            /// <summary>
            /// Sets a constant in the graphics root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="srcData">The source data for the constant to set. Convert a data
            /// into binary and again to uint using BitConverter or something else.</param>
            /// <param name="destOffsetIn32BitValue">The offset, in 32-bit values, to set the constant
            /// in the root signature.</param>
            void SetGraphicsRoot32BitConstant(
                unsigned int rootParameterIndex,
                unsigned int srcData,
                unsigned int destOffsetIn32BitValue
            );

            /// <summary>
            /// Sets a group of constants in the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="num32BitValuesToSet">The number of constants to set in the root signature.
            /// </param>
            /// <param name="srcData">The source data for the group of constants to set. The length
            /// of the byte array should be at leeast num32BitValuesToSet * 4.</param>
            /// <param name="destOffsetIn32BitValue">The offset, in 32-bit values, to set the first
            /// constant of the group in the root signature.</param>
            void SetComputeRoot32BitConstants(
                unsigned int rootParameterIndex,
                unsigned int num32BitValuesToSet,
                array<unsigned char>^ srcData,
                unsigned int destOffsetIn32BitValue
            );

            /// <summary>
            /// Sets a group of constants in the graphics root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="num32BitValuesToSet">The number of constants to set in the root signature.
            /// </param>
            /// <param name="srcData">The source data for the group of constants to set. The length
            /// of the byte array should be at leeast num32BitValuesToSet * 4.</param>
            /// <param name="destOffsetIn32BitValue">The offset, in 32-bit values, to set the first
            /// constant of the group in the root signature.</param>
            void SetGraphicsRoot32BitConstants(
                unsigned int rootParameterIndex,
                unsigned int num32BitValuesToSet,
                array<unsigned char>^ srcData,
                unsigned int destOffsetIn32BitValue
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the constant buffer in the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetComputeRootConstantBufferView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the constant buffer in the graphics root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetGraphicsRootConstantBufferView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the shader resource in the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetComputeRootShaderResourceView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the shader resource in the graphics root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetGraphicsRootShaderResourceView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the unordered-access-view in the compute root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetComputeRootUnorderedAccessView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets a CPU descriptor handle for the unordered-access-view in the graphics
            /// root signature.
            /// </summary>
            /// <param name="rootParameterIndex">The slot number for binding.</param>
            /// <param name="bufferLocation">Specifies the D3D12_GPU_VIRTUAL_ADDRESS of the
            /// constant buffer.</param>
            void SetGraphicsRootUnorderedAccessView(
                unsigned int rootParameterIndex,
                D3D12_GPU_VIRTUAL_ADDRESS bufferLocation
            );

            /// <summary>
            /// Sets the view for the index buffer.
            /// </summary>
            /// <param name="view">The view specifies the index buffer's address, size, and DXGIFormat,
            /// as a D3D12IndexBufferView structure.</param>
            void IASetIndexBuffer(Nullable<D3D12IndexBufferView> view);

            /// <summary>
            /// Sets a CPU descriptor handle for the vertex buffers.
            /// </summary>
            /// <param name="startSlot">Index into the device's zero-based array to begin setting
            /// vertex buffers.</param>
            /// <param name="views">Specifies the vertex buffer views in an array of
            /// D3D12VertexBufferView structures.</param>
            void IASetVertexBuffers(unsigned int startSlot, ...array<D3D12VertexBufferView>^ views);

            /// <summary>
            /// Sets the stream output buffer views.
            /// </summary>
            /// <param name="startSlot">Index into the device's zero-based array to begin setting
            /// stream output buffers.</param>
            /// <param name="views">Specifies an array of D3D12StreamOutputBufferView structures.</param>
            void SOSetTargets(unsigned int startSlot, ...array<D3D12StreamOutputBufferView>^ views);

            /// <summary>
            /// Sets CPU descriptor handles for the render targets and depth stencil.
            /// </summary>
            /// <param name="rtsSingleHandleToDescriptorRange">True means the handle passed in is the
            /// pointer to a contiguous range of NumRenderTargetDescriptors descriptors. This case is
            /// useful if the set of descriptors to bind already happens to be contiguous in memory (so
            /// all that¡¯s needed is a handle to the first one). False means that the handle is the
            /// first of an array of NumRenderTargetDescriptors handles. The false case allows an
            /// application to bind a set of descriptors from different locations at once.</param>
            /// <param name="depthStencilDescriptor">A D3D12CPUDescriptorHandle structure that describe
            /// the CPU descriptor handle that represents the start of the heap that holds the depth
            /// stencil descriptor. If this parameter is NULL, no depth stencil descriptor is bound.
            /// </param>
            /// <param name="renderTargetDescriptor">Specifies an array of D3D12CPUDescriptorHandle
            /// structures that describe the CPU descriptor handles that represents the start of the
            /// heap of render target descriptors. If the length of the array is 0, no render targets
            /// are bound.</param>
            void OMSetRenderTargets(
                bool rtsSingleHandleToDescriptorRange,
                Nullable<D3D12CPUDescriptorHandle> depthStencilDescriptor,
                ...array<D3D12CPUDescriptorHandle>^ renderTargetDescriptor
            );

            /// <summary>
            /// Clears the depth-stencil resource.
            /// </summary>
            /// <param name="depthStencilView">Describes the CPU descriptor handle that represents
            /// the start of the heap for the depth stencil to be cleared.</param>
            /// <param name="clearFlags">A combination of D3D12ClearFlags values that are combined
            /// by using a bitwise OR operation. The resulting value identifies the type of data to
            /// clear (depth buffer, stencil buffer, or both).</param>
            /// <param name="depth">A value to clear the depth buffer with. This value will be
            /// clamped between 0 and 1.</param>
            /// <param name="stencil">A value to clear the stencil buffer with.</param>
            /// <param name="rects">An array of Rect structures for the rectangles in the resource
            /// view to clear. If the length of the array is 0, ClearDepthStencilView clears the
            /// entire resource view.</param>
            void ClearDepthStencilView(
                D3D12CPUDescriptorHandle depthStencilView,
                D3D12ClearFlags clearFlags,
                float depth,
                unsigned char stencil,
                ...array<Rect>^ rects
            );

            /// <summary>
            /// Sets all the elements in a render target to one value.
            /// </summary>
            /// <param name="renderTargetView">Specifies a D3D12CPUDescriptorHandle structure that
            /// describes the CPU descriptor handle that represents the start of the heap for the render
            /// target to be cleared.</param>
            /// <param name="colorRGBA">A D3DColorValue that represents the color to fill the render
            /// target with.</param>
            /// <param name="rects">An array of Rect structures for the rectangles in the resource
            /// view to clear. If the length of the array is 0, ClearRenderTargetView clears the
            /// entire resource view.</param>
            void ClearRenderTargetView(
                D3D12CPUDescriptorHandle renderTargetView,
                D3DColorValue colorRGBA,
                ...array<Rect>^ rects
            );

            /// <summary>
            /// Sets all the elements in a unordered-access view (UAV) to the specified integer values.
            /// </summary>
            /// <param name="viewGPUHandleInCurrentHeap">A D3D12GPUDescriptorHandle that references an
            /// initialized descriptor for the unordered-access view (UAV) that is to be cleared. This
            /// descriptor must be in a shader-visible descriptor heap, which must be set on the command
            /// list via SetDescriptorHeaps.</param>
            /// <param name="viewCPUHandle">A D3D12CPUDescriptorHandle in a non-shader visible descriptor
            /// heap that references an initialized descriptor for the unordered-access view (UAV) that
            /// is to be cleared.</param>
            /// <param name="resource">A D3D12Resource object that represents the
            /// unordered-access-view (UAV) resource to clear.</param>
            /// <param name="values">A 4-component array that containing the values to fill the
            /// unordered-access-view resource with. This array's length must be 4.</param>
            /// <param name="rects">An array of Rect structures for the rectangles in the resource
            /// view to clear. If the length of the array is 0, ClearUnorderedAccessViewUint clears the
            /// entire resource view.</param>
            void ClearUnorderedAccessViewUint(
                D3D12GPUDescriptorHandle viewGPUHandleInCurrentHeap,
                D3D12CPUDescriptorHandle viewCPUHandle,
                D3D12Resource^ resource,
                array<unsigned int>^ values,
                ...array<Rect>^ rects
            );

            /// <summary>
            /// Sets all the elements in a unordered-access view (UAV) to the specified float values.
            /// </summary>
            /// <param name="viewGPUHandleInCurrentHeap">A D3D12GPUDescriptorHandle that references an
            /// initialized descriptor for the unordered-access view (UAV) that is to be cleared. This
            /// descriptor must be in a shader-visible descriptor heap, which must be set on the command
            /// list via SetDescriptorHeaps.</param>
            /// <param name="viewCPUHandle">A D3D12CPUDescriptorHandle in a non-shader visible descriptor
            /// heap that references an initialized descriptor for the unordered-access view (UAV) that
            /// is to be cleared.</param>
            /// <param name="resource">A D3D12Resource object that represents the
            /// unordered-access-view (UAV) resource to clear.</param>
            /// <param name="values">A 4-component array that containing the values to fill the
            /// unordered-access-view resource with. This array's length must be 4.</param>
            /// <param name="rects">An array of Rect structures for the rectangles in the resource
            /// view to clear. If the length of the array is 0, ClearUnorderedAccessViewUint clears the
            /// entire resource view.</param>
            void ClearUnorderedAccessViewFloat(
                D3D12GPUDescriptorHandle viewGPUHandleInCurrentHeap,
                D3D12CPUDescriptorHandle viewCPUHandle,
                D3D12Resource^ resource,
                array<float>^ values,
                ...array<Rect>^ rects
            );

            /// <summary>
            /// Indicates that the contents of a resource don't need to be preserved. The function
            /// may re-initialize resource metadata in some cases.
            /// </summary>
            /// <param name="resource">A D3D12Resource object for the resource to discard.</param>
            /// <param name="region">An optional D3D12DiscardRegion structure that describes details
            /// for the discard-resource operation.</param>
            void DiscardResource(
                D3D12Resource^ resource,
                [Optional] Nullable<D3D12DiscardRegion> region
            );

            /// <summary>
            /// Starts a query running.
            /// </summary>
            /// <param name="queryHeap">Specifies the D3D12QueryHeap containing the query.</param>
            /// <param name="type">Specifies one member of D3D12QueryType.</param>
            /// <param name="index">Specifies the index of the query within the query heap.</param>
            void BeginQuery(
                D3D12QueryHeap^ queryHeap,
                D3D12QueryType type,
                unsigned int index
            );

            /// <summary>
            /// Ends a running query.
            /// </summary>
            /// <param name="queryHeap">Specifies the D3D12QueryHeap containing the query.</param>
            /// <param name="type">Specifies one member of D3D12QueryType.</param>
            /// <param name="index">Specifies the index of the query within the query heap.</param>
            void EndQuery(
                D3D12QueryHeap^ queryHeap,
                D3D12QueryType type,
                unsigned int index
            );

            /// <summary>
            /// Extracts data from a query. ResolveQueryData works with all heap types (default, upload,
            /// and readback).
            /// </summary>
            /// <param name="queryHeap">Specifies the D3D12QueryHeap containing the queries to resolve.
            /// </param>
            /// <param name="type">Specifies the type of query, one member of D3D12QueryType.</param>
            /// <param name="startIndex">Specifies an index of the first query to resolve.</param>
            /// <param name="numQueries">Specifies the number of queries to resolve.</param>
            /// <param name="destinationBuffer">Specifies an ID3D12Resource destination buffer,
            /// which must be in the state D3D12ResourceState::CopyDest.</param>
            /// <param name="alignedDestinationBufferOffset">Specifies an alignment offset into the
            /// destination buffer. Must be a multiple of 8 bytes.</param>
            void ResolveQueryData(
                D3D12QueryHeap^ queryHeap,
                D3D12QueryType type,
                unsigned int startIndex,
                unsigned int numQueries,
                D3D12Resource^ destinationBuffer,
                unsigned long long alignedDestinationBufferOffset
            );

            /// <summary>
            /// Sets a rendering predicate.
            /// </summary>
            /// <param name="buffer">The buffer, as an ID3D12Resource, which must be in the
            /// D3D12ResourceStates::Predication or D3D12ResourceStates::IndirectArgument state
            /// (both values are identical, and provided as aliases for clarity), or null to disable
            /// predication.</param>
            /// <param name="alignedBufferOffset">The aligned buffer offset, as a ulong.</param>
            /// <param name="operation">Specifies a D3D12PredicationOp, such as
            /// D3D12PredicationOp::EqualZero or D3D12PredicationOp::NotEqualZero.</param>
            void SetPredication(
                D3D12Resource^ buffer,
                unsigned long long alignedBufferOffset,
                D3D12PredicationOp operation
            );

            [Obsolete("Not intended to be called directly.  Use the PIX event runtime to insert events into a command list.")]
            void SetMarker(
                unsigned int metadata,
                void* pData,
                unsigned int size
            );

            [Obsolete("Not intended to be called directly.  Use the PIX event runtime to insert events into a command list.")]
            void BeginEvent(
                unsigned int metadata,
                void* pData,
                unsigned int size
            );

            [Obsolete("Not intended to be called directly.  Use the PIX event runtime to insert events into a command list.")]
            void EndEvent();

            /// <summary>
            /// Apps perform indirect draws/dispatches using the ExecuteIndirect method.
            /// </summary>
            /// <param name="commandSignature">Specifies a D3D12CommandSignature. The data referenced
            /// by argumentBuffer will be interpreted depending on the contents of the command
            /// signature.</param>
            /// <param name="maxCommandCount">If countBuffer is not null, then maxCommandCount
            /// specifies the maximum number of operations which will be performed. The actual number
            /// of operations to be performed are defined by the minimum of this value, and a 32-bit
            /// unsigned integer contained in countBuffer (at the byte offset specified by
            /// countBufferOffset). If countBuffer is null, the maxCommandCount specifies the exact
            /// number of operations which will be performed.</param>
            /// <param name="argumentBuffer">Specifies one or more D3D12Resource objects, containing
            /// the command arguments.</param>
            /// <param name="argumentBufferOffset">Specifies an offset into argumentBuffer to identify\
            /// the first command argument.</param>
            /// <param name="countBuffer">Specifies a D3D12Resource. This can be null.</param>
            /// <param name="countBufferOffset">Specifies a ulong that is the offset into countBuffer,
            /// identifying the argument count.</param>
            void ExecuteIndirect(
                D3D12CommandSignature^ commandSignature,
                unsigned int maxCommandCount,
                D3D12Resource^ argumentBuffer,
                unsigned long long argumentBufferOffset,
                D3D12Resource^ countBuffer,
                unsigned long long countBufferOffset
            );
        };
    }
}
