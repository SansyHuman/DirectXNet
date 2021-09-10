#include "D3D12QueryHeap.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12QueryHeap::D3D12QueryHeap(::ID3D12QueryHeap* pHeap)
    : D3D12Pageable((::ID3D12Pageable*)pHeap)
{
    
}

void DirectXNet::DirectX12::D3D12QueryHeap::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
}

Guid DirectXNet::DirectX12::D3D12QueryHeap::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12QueryHeap), Guid);
}
