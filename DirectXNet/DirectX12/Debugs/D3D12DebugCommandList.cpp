#include "D3D12DebugCommandList.h"
#include "../D3D12Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugCommandList::D3D12DebugCommandList(::ID3D12DebugCommandList* pList)
    : DirectXNet::Common::Unknown((::IUnknown*)pList)
{
    this->pList = pList;
}

void DirectXNet::DirectX12::Debug::D3D12DebugCommandList::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pList = (::ID3D12DebugCommandList*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugCommandList::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugCommandList), Guid);
}

bool DirectXNet::DirectX12::Debug::D3D12DebugCommandList::AssertResourceState(
    D3D12Resource^ resource, unsigned int subresource, D3D12ResourceStates state)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        return (!!(pList->AssertResourceState(pResource, subresource, (UINT)state)));
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

D3D12DebugFeature DirectXNet::DirectX12::Debug::D3D12DebugCommandList::FeatureMask::get()
{
    return (D3D12DebugFeature)pList->GetFeatureMask();
}

void DirectXNet::DirectX12::Debug::D3D12DebugCommandList::FeatureMask::set(D3D12DebugFeature mask)
{
    Result::ThrowIfFailed(pList->SetFeatureMask((::D3D12_DEBUG_FEATURE)mask));
}
