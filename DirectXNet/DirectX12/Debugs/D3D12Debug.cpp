#include "D3D12Debug.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug::D3D12Debug(::ID3D12Debug* pDebug)
    : DirectXNet::Common::Unknown((::IUnknown*)pDebug)
{
    this->pDebug = pDebug;
}

void DirectXNet::DirectX12::Debug::D3D12Debug::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDebug = (::ID3D12Debug*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug::EnableDebugLayer()
{
    pDebug->EnableDebugLayer();
}
