#include "D3D12Pageable.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Pageable::D3D12Pageable(::ID3D12Pageable* pPageable)
    : D3D12DeviceChild((::ID3D12DeviceChild*)pPageable)
{
    
}

void DirectXNet::DirectX12::D3D12Pageable::AttatchComObj(::IUnknown* pComObj)
{
    D3D12DeviceChild::AttatchComObj(pComObj);
}

Guid DirectXNet::DirectX12::D3D12Pageable::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Pageable), Guid);
}
