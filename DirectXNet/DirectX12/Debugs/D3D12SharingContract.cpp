#include "D3D12SharingContract.h"
#include "../D3D12Resource.h"
#include "../D3D12Fence.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12SharingContract::D3D12SharingContract(::ID3D12SharingContract* pContract)
    : DirectXNet::Common::Unknown((::IUnknown*)pContract)
{
    this->pContract = pContract;
}

void DirectXNet::DirectX12::Debug::D3D12SharingContract::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pContract = (::ID3D12SharingContract*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12SharingContract::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12SharingContract), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12SharingContract::Present(
    D3D12Resource^ resource, unsigned int subresource, IntPtr window)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        pContract->Present(pResource, subresource, (HWND)window.ToPointer());
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::Debug::D3D12SharingContract::SharedFenceSignal(
    D3D12Fence^ fence, unsigned long long fenceValue)
{
    ::ID3D12Fence* pFence = __nullptr;

    try
    {
        pFence = (::ID3D12Fence*)fence->GetNativeInterface();
        pContract->SharedFenceSignal(pFence, fenceValue);
    }
    finally
    {
        SAFE_RELEASE(pFence);
    }
}
