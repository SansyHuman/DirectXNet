#include "D3D12CommandQueue.h"
#include "D3D12Resource.h"
#include "D3D12Heap.h"
#include "D3D12CommandList.h"
#include "D3D12Fence.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12CommandQueue::D3D12CommandQueue(::ID3D12CommandQueue* pQueue)
    : D3D12Pageable((::ID3D12Pageable*)pQueue)
{
    this->pQueue = pQueue;
}

void DirectXNet::DirectX12::D3D12CommandQueue::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pQueue = (::ID3D12CommandQueue*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12CommandQueue::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12CommandQueue), Guid);
}

void DirectXNet::DirectX12::D3D12CommandQueue::UpdateTileMappings(
    D3D12Resource^ resource,
    unsigned int numResourceRegions,
    unsigned int numRanges,
    D3D12TileMappingFlags flags,
    array<D3D12TiledResourceCoordinate>^ resourceRegionStartCoordinates,
    array<D3D12TileRegionSize>^ resourceRegionSizes,
    D3D12Heap^ heap,
    array<D3D12TileRangeFlags>^ rangeFlags,
    array<unsigned int>^ heapRangeStartOffsets,
    array<unsigned int>^ rangeTileCounts)
{
    ::ID3D12Resource* pResource = __nullptr;
    ::ID3D12Heap* pHeap = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();

        pin_ptr<D3D12TiledResourceCoordinate> pResourceRegionStartCoordinates = nullptr;
        if(resourceRegionStartCoordinates != nullptr)
            pResourceRegionStartCoordinates = &resourceRegionStartCoordinates[0];

        pin_ptr<D3D12TileRegionSize> pResourceRegionSizes = nullptr;
        if(resourceRegionSizes != nullptr)
            pResourceRegionSizes = &resourceRegionSizes[0];

        if(heap != nullptr)
            pHeap = (::ID3D12Heap*)heap->GetNativeInterface();

        pin_ptr<D3D12TileRangeFlags> pRangeFlags = nullptr;
        if(rangeFlags != nullptr)
            pRangeFlags = &rangeFlags[0];

        pin_ptr<unsigned int> pHeapRangeStartOffsets = nullptr;
        if(heapRangeStartOffsets != nullptr)
            pHeapRangeStartOffsets = &heapRangeStartOffsets[0];

        pin_ptr<unsigned int> pRangeTileCounts = nullptr;
        if(rangeTileCounts != nullptr)
            pRangeTileCounts = &rangeTileCounts[0];

        pQueue->UpdateTileMappings(
            pResource,
            numResourceRegions,
            (const ::D3D12_TILED_RESOURCE_COORDINATE*)pResourceRegionStartCoordinates,
            (const ::D3D12_TILE_REGION_SIZE*)pResourceRegionSizes,
            pHeap,
            numRanges,
            (const ::D3D12_TILE_RANGE_FLAGS*)pRangeFlags,
            (const UINT*)pHeapRangeStartOffsets,
            (const UINT*)pRangeTileCounts,
            (::D3D12_TILE_MAPPING_FLAGS)flags
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
        SAFE_RELEASE(pHeap);
    }
}

void DirectXNet::DirectX12::D3D12CommandQueue::CopyTileMappings(
    D3D12Resource^ dstResource, D3D12TiledResourceCoordinate% dstRegionStartCoordinate,
    D3D12Resource^ srcResource, D3D12TiledResourceCoordinate% srcRegionStartCoordinate,
    D3D12TileRegionSize% regionSize, D3D12TileMappingFlags flags)
{
    ::ID3D12Resource* pDstResource = __nullptr;
    ::ID3D12Resource* pSrcResource = __nullptr;

    try
    {
        pDstResource = (::ID3D12Resource*)dstResource->GetNativeInterface();
        pin_ptr<D3D12TiledResourceCoordinate> pDstRegionStartCoordinate = &dstRegionStartCoordinate;
        pSrcResource = (::ID3D12Resource*)srcResource->GetNativeInterface();
        pin_ptr<D3D12TiledResourceCoordinate> pSrcRegionStartCoordinate = &srcRegionStartCoordinate;
        pin_ptr<D3D12TileRegionSize> pRegionSize = &regionSize;

        pQueue->CopyTileMappings(
            pDstResource,
            (const ::D3D12_TILED_RESOURCE_COORDINATE*)pDstRegionStartCoordinate,
            pSrcResource,
            (const ::D3D12_TILED_RESOURCE_COORDINATE*)pSrcRegionStartCoordinate,
            (const ::D3D12_TILE_REGION_SIZE*)pRegionSize,
            (::D3D12_TILE_MAPPING_FLAGS)flags
        );
    }
    finally
    {
        SAFE_RELEASE(pDstResource);
        SAFE_RELEASE(pSrcResource);
    }
}

void DirectXNet::DirectX12::D3D12CommandQueue::ExecuteCommandLists(
    ...array<D3D12CommandList^>^ commandLists)
{
    UINT numCommandLists = commandLists->Length;
    std::vector<::ID3D12CommandList*> lists(numCommandLists, __nullptr);

    try
    {
        for(size_t i = 0; i < numCommandLists; i++)
        {
            lists[i] = (::ID3D12CommandList*)commandLists[i]->GetNativeInterface();
        }

        pQueue->ExecuteCommandLists(numCommandLists, lists.data());
    }
    finally
    {
        for(size_t i = 0; i < numCommandLists; i++)
        {
            SAFE_RELEASE(lists[i]);
        }
    }
}

void DirectXNet::DirectX12::D3D12CommandQueue::SetMarker(
    unsigned int metadata, void* pData, unsigned int size)
{
    pQueue->SetMarker(metadata, pData, size);
}

void DirectXNet::DirectX12::D3D12CommandQueue::BeginEvent(
    unsigned int metadata, void* pData, unsigned int size)
{
    pQueue->BeginEvent(metadata, pData, size);
}

void DirectXNet::DirectX12::D3D12CommandQueue::EndEvent()
{
    pQueue->EndEvent();
}

Result DirectXNet::DirectX12::D3D12CommandQueue::Signal(D3D12Fence^ fence, unsigned long long value)
{
    ::ID3D12Fence* pFence = __nullptr;

    try
    {
        pFence = (::ID3D12Fence*)fence->GetNativeInterface();
        return Result(pQueue->Signal(pFence, value));
    }
    finally
    {
        SAFE_RELEASE(pFence);
    }
}

Result DirectXNet::DirectX12::D3D12CommandQueue::Wait(D3D12Fence^ fence, unsigned long long value)
{
    ::ID3D12Fence* pFence = __nullptr;

    try
    {
        pFence = (::ID3D12Fence*)fence->GetNativeInterface();
        return Result(pQueue->Wait(pFence, value));
    }
    finally
    {
        SAFE_RELEASE(pFence);
    }
}

unsigned long long DirectXNet::DirectX12::D3D12CommandQueue::TimestampFrequency::get()
{
    unsigned long long frequency = 0;
    Result::ThrowIfFailed(pQueue->GetTimestampFrequency(&frequency));

    return frequency;
}

Result DirectXNet::DirectX12::D3D12CommandQueue::GetClockCalibration(
    unsigned long long% gpuTimestamp, unsigned long long% cpuTimestamp)
{
    unsigned long long gpu = 0;
    unsigned long long cpu = 0;
    Result result(pQueue->GetClockCalibration(&gpu, &cpu));

    gpuTimestamp = gpu;
    cpuTimestamp = cpu;
    return result;
}

D3D12CommandQueueDesc DirectXNet::DirectX12::D3D12CommandQueue::CommandQueueDesc::get()
{
    return *((D3D12CommandQueueDesc*)&pQueue->GetDesc());
}
