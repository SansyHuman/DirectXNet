#include "D3D12Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Resource::D3D12Resource(::ID3D12Resource* pResource)
    : D3D12Pageable((::ID3D12Pageable*)pResource)
{
    this->pResource.Attach(pResource);
}

void DirectXNet::DirectX12::D3D12Resource::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pResource.Release();
    pResource.Attach((::ID3D12Resource*)pComObj);
}

Guid DirectXNet::DirectX12::D3D12Resource::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Resource), Guid);
}

IntPtr DirectXNet::DirectX12::D3D12Resource::Map(
    unsigned int subresource, Nullable<D3D12Range> readRange)
{
    ::D3D12_RANGE* pRange = __nullptr;
    if(readRange.HasValue)
        pRange = (::D3D12_RANGE*)&readRange.Value;
    void* pData = __nullptr;

    Result::ThrowIfFailed(pResource->Map(subresource, pRange, &pData));

    return IntPtr(pData);
}

D3D12Range DirectXNet::DirectX12::D3D12Resource::Map(unsigned int subresource)
{
    D3D12Range range;
    Result::ThrowIfFailed(pResource->Map(subresource, (const ::D3D12_RANGE*)&range, __nullptr));
    return range;
}

void DirectXNet::DirectX12::D3D12Resource::Unmap(
    unsigned int subresource, Nullable<D3D12Range> writtenRange)
{
    ::D3D12_RANGE* pRange = __nullptr;
    if(writtenRange.HasValue)
        pRange = (::D3D12_RANGE*)&writtenRange.Value;
    pResource->Unmap(subresource, pRange);
}

D3D12ResourceDesc DirectXNet::DirectX12::D3D12Resource::ResourceDesc::get()
{
    return *((D3D12ResourceDesc*)&pResource->GetDesc());
}

D3D12_GPU_VIRTUAL_ADDRESS DirectXNet::DirectX12::D3D12Resource::GPUVirtualAddresss::get()
{
    return pResource->GetGPUVirtualAddress();
}

Result DirectXNet::DirectX12::D3D12Resource::WriteToSubresource(
    IntPtr srcData, unsigned int srcRowPitch, unsigned int srcDepthPitch,
    unsigned int dstSubresource, Nullable<D3D12Box> dstBox)
{
    ::D3D12_BOX* pDstBox = __nullptr;
    if(dstBox.HasValue)
        pDstBox = (::D3D12_BOX*)&dstBox.Value;

    return Result(pResource->WriteToSubresource(
        dstSubresource,
        pDstBox,
        srcData.ToPointer(),
        srcRowPitch,
        srcDepthPitch
    ));
}

Result DirectXNet::DirectX12::D3D12Resource::ReadFromSubresource(IntPtr% dstData, unsigned int dstRowPitch, unsigned int dstDepthPitch, unsigned int srcSubresource, Nullable<D3D12Box> srcBox)
{
    ::D3D12_BOX* pSrcBox = __nullptr;
    if(srcBox.HasValue)
        pSrcBox = (::D3D12_BOX*)&srcBox.Value;

    return Result(pResource->ReadFromSubresource(
        dstData.ToPointer(),
        dstRowPitch,
        dstDepthPitch,
        srcSubresource,
        pSrcBox
    ));
}

Result DirectXNet::DirectX12::D3D12Resource::GetHeapProperties(
    D3D12HeapProperties% heapProperties,
    D3D12HeapFlags% heapFlags)
{
    pin_ptr<D3D12HeapProperties> pProperties = &heapProperties;
    pin_ptr<D3D12HeapFlags> pFlags = &heapFlags;

    return Result(pResource->GetHeapProperties(
        (::D3D12_HEAP_PROPERTIES*)pProperties,
        (::D3D12_HEAP_FLAGS*)pFlags
    ));
}
