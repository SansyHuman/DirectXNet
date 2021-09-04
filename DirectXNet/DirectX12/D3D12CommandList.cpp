#include "D3D12CommandList.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12CommandList::D3D12CommandList(::ID3D12CommandList* pList)
    : D3D12DeviceChild((::ID3D12DeviceChild*)pList)
{
    this->pList.Attach(pList);
}

void DirectXNet::DirectX12::D3D12CommandList::AttatchComObj(::IUnknown* pComObj)
{
    D3D12DeviceChild::AttatchComObj(pComObj);
    pList.Release();
    pList.Attach((::ID3D12CommandList*)pComObj);
}

Guid DirectXNet::DirectX12::D3D12CommandList::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12CommandList), Guid);
}

D3D12CommandListType DirectXNet::DirectX12::D3D12CommandList::Type::get()
{
    return (D3D12CommandListType)pList->GetType();
}
