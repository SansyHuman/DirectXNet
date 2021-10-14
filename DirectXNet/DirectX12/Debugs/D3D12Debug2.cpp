#include "D3D12Debug2.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug2::D3D12Debug2(::ID3D12Debug2* pDebug)
    : DirectXNet::Common::Unknown((::IUnknown*)pDebug)
{
    this->pDebug = pDebug;
}

void DirectXNet::DirectX12::Debug::D3D12Debug2::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDebug = (::ID3D12Debug2*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug2::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug2), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug2::SetGPUBasedValidationFlags(D3D12GPUBasedValidationFlags flags)
{
    pDebug->SetGPUBasedValidationFlags((::D3D12_GPU_BASED_VALIDATION_FLAGS)flags);
}
