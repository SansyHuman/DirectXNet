#include "D3D12DebugCommandQueue.h"
#include "../D3D12Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12DebugCommandQueue::D3D12DebugCommandQueue(
    ::ID3D12DebugCommandQueue* pQueue)
    : DirectXNet::Common::Unknown((::IUnknown*)pQueue)
{
    this->pQueue = pQueue;
}

void DirectXNet::DirectX12::Debug::D3D12DebugCommandQueue::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pQueue = (::ID3D12DebugCommandQueue*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugCommandQueue::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugCommandQueue), Guid);
}

bool DirectXNet::DirectX12::Debug::D3D12DebugCommandQueue::AssertResourceState(
    D3D12Resource^ resource, unsigned int subresource, D3D12ResourceStates state)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        return (!!(pQueue->AssertResourceState(pResource, subresource, (UINT)state)));
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}
