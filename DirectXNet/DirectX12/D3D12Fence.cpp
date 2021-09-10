#include "D3D12Fence.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Fence::D3D12Fence(::ID3D12Fence* pFence)
    : D3D12Pageable((::ID3D12Pageable*)pFence)
{
    this->pFence = pFence;
}

void DirectXNet::DirectX12::D3D12Fence::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pFence = (::ID3D12Fence*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12Fence::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Fence), Guid);
}

unsigned long long DirectXNet::DirectX12::D3D12Fence::CompletedValue::get()
{
    return pFence->GetCompletedValue();
}

Result DirectXNet::DirectX12::D3D12Fence::SetEventOnCompletion(unsigned long long value, IntPtr hEvent)
{
    return Result(pFence->SetEventOnCompletion(value, hEvent.ToPointer()));
}

Result DirectXNet::DirectX12::D3D12Fence::Signal(unsigned long long value)
{
    return Result(pFence->Signal(value));
}
