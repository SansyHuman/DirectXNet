#include "D3D12GraphicsCommandList.h"
#include "D3D12CommandAllocator.h"
#include "D3D12PipelineState.h"
#include "D3D12Resource.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12RootSignature.h"
#include "D3D12QueryHeap.h"
#include "D3D12CommandSignature.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12GraphicsCommandList::D3D12GraphicsCommandList(
    ::ID3D12GraphicsCommandList* pGraphicsList)
    : D3D12CommandList((::ID3D12CommandList*)pGraphicsList)
{
    this->pGraphicsList = pGraphicsList;
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::AttatchComObj(::IUnknown* pComObj)
{
    D3D12CommandList::AttatchComObj(pComObj);
    pGraphicsList = (::ID3D12GraphicsCommandList*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12GraphicsCommandList::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12GraphicsCommandList), Guid);
}

Result DirectXNet::DirectX12::D3D12GraphicsCommandList::Close()
{
    return Result(pGraphicsList->Close());
}

Result DirectXNet::DirectX12::D3D12GraphicsCommandList::Reset(
    D3D12CommandAllocator^ allocator, D3D12PipelineState^ initialState)
{
    ::ID3D12CommandAllocator* pAllocator = __nullptr;
    ::ID3D12PipelineState* pState = __nullptr;

    try
    {
        pAllocator = (::ID3D12CommandAllocator*)allocator->GetNativeInterface();
        if(initialState != nullptr)
            pState = (::ID3D12PipelineState*)initialState->GetNativeInterface();

        return Result(pGraphicsList->Reset(pAllocator, pState));
    }
    finally
    {
        SAFE_RELEASE(pAllocator);
        SAFE_RELEASE(pState);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ClearState(D3D12PipelineState^ pipelineState)
{
    ::ID3D12PipelineState* pState = __nullptr;

    try
    {
        if(pipelineState != nullptr)
            pState = (::ID3D12PipelineState*)pipelineState->GetNativeInterface();

        pGraphicsList->ClearState(pState);
    }
    finally
    {
        SAFE_RELEASE(pState);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::DrawInstanced(
    unsigned int vertexCountPerInstance, unsigned int instanceCount,
    unsigned int startVertexLocation, unsigned int startInstanceLocation)
{
    pGraphicsList->DrawInstanced(
        vertexCountPerInstance,
        instanceCount,
        startVertexLocation,
        startInstanceLocation
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::DrawIndexedInstanced(
    unsigned int indexCountPerInstance, unsigned int instanceCount,
    unsigned int startIndexLocation, int baseVertexLocation, unsigned int startInstanceLocation)
{
    pGraphicsList->DrawIndexedInstanced(
        indexCountPerInstance,
        instanceCount,
        startIndexLocation,
        baseVertexLocation,
        startInstanceLocation
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::Dispatch(
    unsigned int threadGroupCountX, unsigned int threadGroupCountY, unsigned int threadGroupCountZ)
{
    pGraphicsList->Dispatch(threadGroupCountX, threadGroupCountY, threadGroupCountZ);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::CopyBufferRegion(
    D3D12Resource^ dstBuffer, unsigned long long dstOffset,
    D3D12Resource^ srcBuffer, unsigned long long srcOffset, unsigned long long numBytes)
{
    ::ID3D12Resource* pDstBuffer = __nullptr;
    ::ID3D12Resource* pSrcBuffer = __nullptr;

    try
    {
        pDstBuffer = (::ID3D12Resource*)dstBuffer->GetNativeInterface();
        pSrcBuffer = (::ID3D12Resource*)srcBuffer->GetNativeInterface();

        pGraphicsList->CopyBufferRegion(pDstBuffer, dstOffset, pSrcBuffer, srcOffset, numBytes);
    }
    finally
    {
        SAFE_RELEASE(pDstBuffer);
        SAFE_RELEASE(pSrcBuffer);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::CopyTextureRegion(
    D3D12TextureCopyLocation% dst, unsigned int dstX, unsigned int dstY, unsigned int dstZ,
    D3D12TextureCopyLocation% src, Nullable<D3D12Box> srcBox)
{
    pin_ptr<D3D12TextureCopyLocation> pDst = &dst;
    pin_ptr<D3D12TextureCopyLocation> pSrc = &src;
    ::D3D12_BOX* pSrcBox = __nullptr;
    if(srcBox.HasValue)
        pSrcBox = (::D3D12_BOX*)&srcBox.Value;

    pGraphicsList->CopyTextureRegion(
        (const ::D3D12_TEXTURE_COPY_LOCATION*)pDst, dstX, dstY, dstZ,
        (const ::D3D12_TEXTURE_COPY_LOCATION*)pSrc, pSrcBox
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::CopyResource(
    D3D12Resource^ dstResource, D3D12Resource^ srcResource)
{
    ::ID3D12Resource* pDstResource = __nullptr;
    ::ID3D12Resource* pSrcResource = __nullptr;

    try
    {
        pDstResource = (::ID3D12Resource*)dstResource->GetNativeInterface();
        pSrcResource = (::ID3D12Resource*)srcResource->GetNativeInterface();

        pGraphicsList->CopyResource(pDstResource, pSrcResource);
    }
    finally
    {
        SAFE_RELEASE(pDstResource);
        SAFE_RELEASE(pSrcResource);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::CopyTiles(
    D3D12Resource^ tiledResource, D3D12TiledResourceCoordinate% tileRegionStartCoordinate,
    D3D12TileRegionSize% tileRegionSize, D3D12Resource^ buffer,
    unsigned long long bufferStartOffsetInBytes, D3D12TileCopyFlags flags)
{
    ::ID3D12Resource* pTiled = __nullptr;
    ::ID3D12Resource* pBuffer = __nullptr;

    try
    {
        pTiled = (::ID3D12Resource*)tiledResource->GetNativeInterface();
        pBuffer = (::ID3D12Resource*)buffer->GetNativeInterface();

        pin_ptr<D3D12TiledResourceCoordinate> pTileRegionStartCoordinate = &tileRegionStartCoordinate;
        pin_ptr<D3D12TileRegionSize> pTileRegionSize = &tileRegionSize;

        pGraphicsList->CopyTiles(
            pTiled,
            (const ::D3D12_TILED_RESOURCE_COORDINATE*)pTileRegionStartCoordinate,
            (const ::D3D12_TILE_REGION_SIZE*)pTileRegionSize,
            pBuffer,
            bufferStartOffsetInBytes,
            (::D3D12_TILE_COPY_FLAGS)flags
        );
    }
    finally
    {
        SAFE_RELEASE(pTiled);
        SAFE_RELEASE(pBuffer);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ResolveSubresource(
    D3D12Resource^ dstResource, unsigned int dstSubresource, D3D12Resource^ srcResource,
    unsigned int srcSubresource, DXGIFormat format)
{
    ::ID3D12Resource* pDstResource = __nullptr;
    ::ID3D12Resource* pSrcResource = __nullptr;

    try
    {
        pDstResource = (::ID3D12Resource*)dstResource->GetNativeInterface();
        pSrcResource = (::ID3D12Resource*)srcResource->GetNativeInterface();

        pGraphicsList->ResolveSubresource(
            pDstResource,
            dstSubresource,
            pSrcResource,
            srcSubresource,
            (::DXGI_FORMAT)format
        );
    }
    finally
    {
        SAFE_RELEASE(pDstResource);
        SAFE_RELEASE(pSrcResource);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::IASetPrimitiveTopology(
    D3DPrimitiveTopology primitiveTopology)
{
    pGraphicsList->IASetPrimitiveTopology((::D3D_PRIMITIVE_TOPOLOGY)primitiveTopology);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::RSSetViewports(...array<D3D12Viewport>^ viewports)
{
    if(viewports->Length == 0)
    {
        pGraphicsList->RSSetViewports(0, __nullptr);
        return;
    }

    pin_ptr<D3D12Viewport> pViewports = &viewports[0];

    pGraphicsList->RSSetViewports(viewports->Length, (const ::D3D12_VIEWPORT*)pViewports);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::RSSetScissorRects(...array<Rect>^ rects)
{
    if(rects->Length == 0)
    {
        pGraphicsList->RSSetScissorRects(0, __nullptr);
        return;
    }

    pin_ptr<Rect> pRects = &rects[0];

    pGraphicsList->RSSetScissorRects(rects->Length, (const ::D3D12_RECT*)pRects);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::OMSetBlendFactor(
    Nullable<D3DColorValue> blendFactor)
{
    if(!blendFactor.HasValue)
        pGraphicsList->OMSetBlendFactor(__nullptr);
    else
    {
        float factor[4] = { blendFactor.Value.r, blendFactor.Value.g, blendFactor.Value.b, blendFactor.Value.a };
        pGraphicsList->OMSetBlendFactor(factor);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::OMSetStencilRef(unsigned int stencilRef)
{
    pGraphicsList->OMSetStencilRef(stencilRef);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetPipelineState(D3D12PipelineState^ pipelineState)
{
    ::ID3D12PipelineState* pPipelineState = __nullptr;

    try
    {
        pPipelineState = (::ID3D12PipelineState*)pipelineState->GetNativeInterface();

        pGraphicsList->SetPipelineState(pPipelineState);
    }
    finally
    {
        SAFE_RELEASE(pPipelineState);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ResourceBarrier(
    ...array<D3D12ResourceBarrier>^ barriers)
{
    pin_ptr<D3D12ResourceBarrier> pBarriers = &barriers[0];

    pGraphicsList->ResourceBarrier(barriers->Length, (const ::D3D12_RESOURCE_BARRIER*)pBarriers);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ExecuteBundle(
    D3D12GraphicsCommandList^ commandList)
{
    ::ID3D12GraphicsCommandList* pCommandList = __nullptr;

    try
    {
        pCommandList = (::ID3D12GraphicsCommandList*)commandList->GetNativeInterface();

        pGraphicsList->ExecuteBundle(pCommandList);
    }
    finally
    {
        SAFE_RELEASE(pCommandList);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetDescriptorHeaps(
    ...array<D3D12DescriptorHeap^>^ descriptorHeaps)
{
    UINT numDescriptorHeaps = descriptorHeaps->Length;
    std::vector<::ID3D12DescriptorHeap*> heaps(numDescriptorHeaps, __nullptr);

    try
    {
        for(UINT i = 0; i < numDescriptorHeaps; i++)
            heaps[i] = (::ID3D12DescriptorHeap*)descriptorHeaps[i]->GetNativeInterface();

        pGraphicsList->SetDescriptorHeaps(numDescriptorHeaps, heaps.data());
    }
    finally
    {
        for(UINT i = 0; i < numDescriptorHeaps; i++)
            SAFE_RELEASE(heaps[i]);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRootSignature(
    D3D12RootSignature^ rootSignature)
{
    ::ID3D12RootSignature* pRootSignature = __nullptr;

    try
    {
        if(rootSignature != nullptr)
            pRootSignature = (::ID3D12RootSignature*)rootSignature->GetNativeInterface();

        pGraphicsList->SetComputeRootSignature(pRootSignature);
    }
    finally
    {
        SAFE_RELEASE(pRootSignature);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRootSignature(D3D12RootSignature^ rootSignature)
{
    ::ID3D12RootSignature* pRootSignature = __nullptr;

    try
    {
        if(rootSignature != nullptr)
            pRootSignature = (::ID3D12RootSignature*)rootSignature->GetNativeInterface();

        pGraphicsList->SetGraphicsRootSignature(pRootSignature);
    }
    finally
    {
        SAFE_RELEASE(pRootSignature);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRootDescriptorTable(
    unsigned int rootParameterIndex, D3D12GPUDescriptorHandle baseDescriptor)
{
    pGraphicsList->SetComputeRootDescriptorTable(
        rootParameterIndex,
        CAST_TO(baseDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE)
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRootDescriptorTable(
    unsigned int rootParameterIndex, D3D12GPUDescriptorHandle baseDescriptor)
{
    pGraphicsList->SetGraphicsRootDescriptorTable(
        rootParameterIndex,
        CAST_TO(baseDescriptor, D3D12_GPU_DESCRIPTOR_HANDLE)
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRoot32BitConstant(
    unsigned int rootParameterIndex, unsigned int srcData, unsigned int destOffsetIn32BitValue)
{
    pGraphicsList->SetComputeRoot32BitConstant(rootParameterIndex, srcData, destOffsetIn32BitValue);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRoot32BitConstant(
    unsigned int rootParameterIndex, unsigned int srcData, unsigned int destOffsetIn32BitValue)
{
    pGraphicsList->SetGraphicsRoot32BitConstant(rootParameterIndex, srcData, destOffsetIn32BitValue);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRoot32BitConstants(
    unsigned int rootParameterIndex, unsigned int num32BitValuesToSet,
    array<unsigned char>^ srcData, unsigned int destOffsetIn32BitValue)
{
    pin_ptr<unsigned char> pSrcData = &srcData[0];

    pGraphicsList->SetComputeRoot32BitConstants(
        rootParameterIndex,
        num32BitValuesToSet,
        (const void*)pSrcData,
        destOffsetIn32BitValue
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRoot32BitConstants(
    unsigned int rootParameterIndex, unsigned int num32BitValuesToSet,
    array<unsigned char>^ srcData, unsigned int destOffsetIn32BitValue)
{
    pin_ptr<unsigned char> pSrcData = &srcData[0];

    pGraphicsList->SetGraphicsRoot32BitConstants(
        rootParameterIndex,
        num32BitValuesToSet,
        (const void*)pSrcData,
        destOffsetIn32BitValue
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRootConstantBufferView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetComputeRootConstantBufferView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRootConstantBufferView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetGraphicsRootConstantBufferView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRootShaderResourceView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetComputeRootShaderResourceView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRootShaderResourceView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetGraphicsRootShaderResourceView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetComputeRootUnorderedAccessView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetComputeRootUnorderedAccessView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetGraphicsRootUnorderedAccessView(
    unsigned int rootParameterIndex, D3D12_GPU_VIRTUAL_ADDRESS bufferLocation)
{
    pGraphicsList->SetGraphicsRootUnorderedAccessView(rootParameterIndex, bufferLocation);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::IASetIndexBuffer(
    Nullable<D3D12IndexBufferView> view)
{
    ::D3D12_INDEX_BUFFER_VIEW* pView = __nullptr;
    if(view.HasValue)
        pView = (::D3D12_INDEX_BUFFER_VIEW*)&view.Value;

    pGraphicsList->IASetIndexBuffer(pView);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::IASetVertexBuffers(
    unsigned int startSlot, ...array<D3D12VertexBufferView>^ views)
{
    if(views->Length == 0)
    {
        pGraphicsList->IASetVertexBuffers(startSlot, 0, __nullptr);
        return;
    }

    pin_ptr<D3D12VertexBufferView> pViews = &views[0];
    pGraphicsList->IASetVertexBuffers(
        startSlot, views->Length, (const ::D3D12_VERTEX_BUFFER_VIEW*)pViews);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SOSetTargets(
    unsigned int startSlot, ...array<D3D12StreamOutputBufferView>^ views)
{
    if(views->Length == 0)
    {
        pGraphicsList->SOSetTargets(startSlot, 0, __nullptr);
        return;
    }

    pin_ptr<D3D12StreamOutputBufferView> pViews = &views[0];
    pGraphicsList->SOSetTargets(
        startSlot, views->Length, (const ::D3D12_STREAM_OUTPUT_BUFFER_VIEW*)pViews);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::OMSetRenderTargets(
    bool rtsSingleHandleToDescriptorRange,
    Nullable<D3D12CPUDescriptorHandle> depthStencilDescriptor,
    ...array<D3D12CPUDescriptorHandle>^ renderTargetDescriptor)
{
    ::D3D12_CPU_DESCRIPTOR_HANDLE* pDepthStencilDescriptor = __nullptr;
    if(depthStencilDescriptor.HasValue)
        pDepthStencilDescriptor = (::D3D12_CPU_DESCRIPTOR_HANDLE*)&depthStencilDescriptor.Value;

    ::D3D12_CPU_DESCRIPTOR_HANDLE* pRenderTargetDescriptors = __nullptr;
    pin_ptr<D3D12CPUDescriptorHandle> pRTD = nullptr;
    if(renderTargetDescriptor->Length != 0)
    {
        pRTD = &renderTargetDescriptor[0];
        pRenderTargetDescriptors = (::D3D12_CPU_DESCRIPTOR_HANDLE*)pRTD;
    }

    pGraphicsList->OMSetRenderTargets(
        renderTargetDescriptor->Length, pRenderTargetDescriptors,
        (BOOL)rtsSingleHandleToDescriptorRange, pDepthStencilDescriptor);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ClearDepthStencilView(
    D3D12CPUDescriptorHandle depthStencilView, D3D12ClearFlags clearFlags,
    float depth, unsigned char stencil, ...array<Rect>^ rects)
{
    ::D3D12_RECT* pRects = __nullptr;
    pin_ptr<Rect> pR = nullptr;
    if(rects->Length != 0)
    {
        pR = &rects[0];
        pRects = (::D3D12_RECT*)pR;
    }

    pGraphicsList->ClearDepthStencilView(
        CAST_TO(depthStencilView, ::D3D12_CPU_DESCRIPTOR_HANDLE),
        (::D3D12_CLEAR_FLAGS)clearFlags,
        depth,
        stencil,
        rects->Length,
        pRects
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ClearRenderTargetView(
    D3D12CPUDescriptorHandle renderTargetView, D3DColorValue colorRGBA, ...array<Rect>^ rects)
{
    float color[4] = { colorRGBA.r, colorRGBA.g, colorRGBA.b, colorRGBA.a };

    ::D3D12_RECT* pRects = __nullptr;
    pin_ptr<Rect> pR = nullptr;
    if(rects->Length != 0)
    {
        pR = &rects[0];
        pRects = (::D3D12_RECT*)pR;
    }

    pGraphicsList->ClearRenderTargetView(
        CAST_TO(renderTargetView, ::D3D12_CPU_DESCRIPTOR_HANDLE),
        color,
        rects->Length,
        pRects
    );
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ClearUnorderedAccessViewUint(
    D3D12GPUDescriptorHandle viewGPUHandleInCurrentHeap, D3D12CPUDescriptorHandle viewCPUHandle,
    D3D12Resource^ resource, array<unsigned int>^ values, ...array<Rect>^ rects)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();

        pin_ptr<unsigned int> pValues = &values[0];

        ::D3D12_RECT* pRects = __nullptr;
        pin_ptr<Rect> pR = nullptr;
        if(rects->Length != 0)
        {
            pR = &rects[0];
            pRects = (::D3D12_RECT*)pR;
        }

        pGraphicsList->ClearUnorderedAccessViewUint(
            CAST_TO(viewGPUHandleInCurrentHeap, D3D12_GPU_DESCRIPTOR_HANDLE),
            CAST_TO(viewCPUHandle, D3D12_CPU_DESCRIPTOR_HANDLE),
            pResource,
            (const unsigned int*)pValues,
            rects->Length,
            pRects
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ClearUnorderedAccessViewFloat(
    D3D12GPUDescriptorHandle viewGPUHandleInCurrentHeap, D3D12CPUDescriptorHandle viewCPUHandle,
    D3D12Resource^ resource, array<float>^ values, ...array<Rect>^ rects)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();

        pin_ptr<float> pValues = &values[0];

        ::D3D12_RECT* pRects = __nullptr;
        pin_ptr<Rect> pR = nullptr;
        if(rects->Length != 0)
        {
            pR = &rects[0];
            pRects = (::D3D12_RECT*)pR;
        }

        pGraphicsList->ClearUnorderedAccessViewFloat(
            CAST_TO(viewGPUHandleInCurrentHeap, D3D12_GPU_DESCRIPTOR_HANDLE),
            CAST_TO(viewCPUHandle, D3D12_CPU_DESCRIPTOR_HANDLE),
            pResource,
            (const float*)pValues,
            rects->Length,
            pRects
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::DiscardResource(
    D3D12Resource^ resource, Nullable<D3D12DiscardRegion> region)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        ::D3D12_DISCARD_REGION* pRegion = __nullptr;
        if(region.HasValue)
            pRegion = (::D3D12_DISCARD_REGION*)&region.Value;

        pGraphicsList->DiscardResource(pResource, pRegion);
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::BeginQuery(
    D3D12QueryHeap^ queryHeap, D3D12QueryType type, unsigned int index)
{
    ::ID3D12QueryHeap* pQueryHeap = __nullptr;

    try
    {
        pQueryHeap = (::ID3D12QueryHeap*)queryHeap->GetNativeInterface();

        pGraphicsList->BeginQuery(pQueryHeap, (::D3D12_QUERY_TYPE)type, index);
    }
    finally
    {
        SAFE_RELEASE(pQueryHeap);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::EndQuery(
    D3D12QueryHeap^ queryHeap, D3D12QueryType type, unsigned int index)
{
    ::ID3D12QueryHeap* pQueryHeap = __nullptr;

    try
    {
        pQueryHeap = (::ID3D12QueryHeap*)queryHeap->GetNativeInterface();

        pGraphicsList->EndQuery(pQueryHeap, (::D3D12_QUERY_TYPE)type, index);
    }
    finally
    {
        SAFE_RELEASE(pQueryHeap);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ResolveQueryData(
    D3D12QueryHeap^ queryHeap, D3D12QueryType type, unsigned int startIndex, unsigned int numQueries,
    D3D12Resource^ destinationBuffer, unsigned long long alignedDestinationBufferOffset)
{
    ::ID3D12QueryHeap* pQueryHeap = __nullptr;
    ::ID3D12Resource* pDestinationBuffer = __nullptr;

    try
    {
        pQueryHeap = (::ID3D12QueryHeap*)queryHeap->GetNativeInterface();
        pDestinationBuffer = (::ID3D12Resource*)destinationBuffer->GetNativeInterface();

        pGraphicsList->ResolveQueryData(
            pQueryHeap,
            (::D3D12_QUERY_TYPE)type,
            startIndex,
            numQueries,
            pDestinationBuffer,
            alignedDestinationBufferOffset
        );
    }
    finally
    {
        SAFE_RELEASE(pQueryHeap);
        SAFE_RELEASE(pDestinationBuffer);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetPredication(
    D3D12Resource^ buffer, unsigned long long alignedBufferOffset, D3D12PredicationOp operation)
{
    ::ID3D12Resource* pBuffer = __nullptr;

    try
    {
        if(buffer != nullptr)
            pBuffer = (::ID3D12Resource*)buffer->GetNativeInterface();

        pGraphicsList->SetPredication(pBuffer, alignedBufferOffset, (::D3D12_PREDICATION_OP)operation);
    }
    finally
    {
        SAFE_RELEASE(pBuffer);
    }
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::SetMarker(
    unsigned int metadata, void* pData, unsigned int size)
{
    pGraphicsList->SetMarker(metadata, pData, size);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::BeginEvent(
    unsigned int metadata, void* pData, unsigned int size)
{
    pGraphicsList->BeginEvent(metadata, pData, size);
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::EndEvent()
{
    pGraphicsList->EndEvent();
}

void DirectXNet::DirectX12::D3D12GraphicsCommandList::ExecuteIndirect(
    D3D12CommandSignature^ commandSignature, unsigned int maxCommandCount,
    D3D12Resource^ argumentBuffer, unsigned long long argumentBufferOffset,
    D3D12Resource^ countBuffer, unsigned long long countBufferOffset)
{
    ::ID3D12CommandSignature* pCommandSignature = __nullptr;
    ::ID3D12Resource* pArgumentBuffer = __nullptr;
    ::ID3D12Resource* pCountBuffer = __nullptr;

    try
    {
        pCommandSignature = (::ID3D12CommandSignature*)commandSignature->GetNativeInterface();
        pArgumentBuffer = (::ID3D12Resource*)argumentBuffer->GetNativeInterface();
        if(countBuffer != nullptr)
            pCountBuffer = (::ID3D12Resource*)countBuffer->GetNativeInterface();

        pGraphicsList->ExecuteIndirect(
            pCommandSignature,
            maxCommandCount,
            pArgumentBuffer,
            argumentBufferOffset,
            pCountBuffer,
            countBufferOffset
        );
    }
    finally
    {
        SAFE_RELEASE(pCommandSignature);
        SAFE_RELEASE(pArgumentBuffer);
        SAFE_RELEASE(pCountBuffer);
    }
}
