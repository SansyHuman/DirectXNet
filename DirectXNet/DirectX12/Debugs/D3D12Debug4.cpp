#include "D3D12Debug4.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug4::D3D12Debug4(::ID3D12Debug4* pDebug4)
    : D3D12Debug3((::ID3D12Debug3*)pDebug4)
{
    this->pDebug4 = pDebug4;
}

void DirectXNet::DirectX12::Debug::D3D12Debug4::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Debug3::AttatchComObj(pComObj);
    pDebug4 = (::ID3D12Debug4*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug4::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug4), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug4::DisableDebugLayer()
{
    pDebug4->DisableDebugLayer();
}
