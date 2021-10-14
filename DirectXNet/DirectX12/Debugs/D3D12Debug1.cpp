#include "D3D12Debug1.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug1::D3D12Debug1(::ID3D12Debug1* pDebug)
    : DirectXNet::Common::Unknown((::IUnknown*)pDebug)
{
    this->pDebug = pDebug;
}

void DirectXNet::DirectX12::Debug::D3D12Debug1::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDebug = (::ID3D12Debug1*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug1::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug1), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug1::EnableDebugLayer()
{
    pDebug->EnableDebugLayer();
}

void DirectXNet::DirectX12::Debug::D3D12Debug1::SetEnableGPUBasedValidation(bool enable)
{
    pDebug->SetEnableGPUBasedValidation((BOOL)enable);
}

void DirectXNet::DirectX12::Debug::D3D12Debug1::SetEnableSynchronizedCommandQueueValidation(bool enable)
{
    pDebug->SetEnableSynchronizedCommandQueueValidation((BOOL)enable);
}
