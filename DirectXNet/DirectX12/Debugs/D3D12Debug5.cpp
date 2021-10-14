#include "D3D12Debug5.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug5::D3D12Debug5(::ID3D12Debug5* pDebug5)
    : D3D12Debug4((::ID3D12Debug4*)pDebug5)
{
    this->pDebug5 = pDebug5;
}

void DirectXNet::DirectX12::Debug::D3D12Debug5::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Debug4::AttatchComObj(pComObj);
    pDebug5 = (::ID3D12Debug5*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug5::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug5), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug5::SetEnableAutoName(bool enable)
{
    pDebug5->SetEnableAutoName((BOOL)enable);
}
