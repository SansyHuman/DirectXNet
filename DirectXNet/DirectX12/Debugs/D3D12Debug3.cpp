#include "D3D12Debug3.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::Debug::D3D12Debug3::D3D12Debug3(::ID3D12Debug3* pDebug3)
    : D3D12Debug((::ID3D12Debug*)pDebug3)
{
    this->pDebug3 = pDebug3;
}

void DirectXNet::DirectX12::Debug::D3D12Debug3::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Debug::AttatchComObj(pComObj);
    pDebug3 = (::ID3D12Debug3*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12Debug3::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Debug3), Guid);
}

void DirectXNet::DirectX12::Debug::D3D12Debug3::SetEnableGPUBasedValidation(bool enable)
{
    pDebug3->SetEnableGPUBasedValidation((BOOL)enable);
}

void DirectXNet::DirectX12::Debug::D3D12Debug3::SetEnableSynchronizedCommandQueueValidation(bool enable)
{
    pDebug3->SetEnableSynchronizedCommandQueueValidation((BOOL)enable);
}

void DirectXNet::DirectX12::Debug::D3D12Debug3::SetGPUBasedValidationFlags(D3D12GPUBasedValidationFlags flags)
{
    pDebug3->SetGPUBasedValidationFlags((::D3D12_GPU_BASED_VALIDATION_FLAGS)flags);
}
