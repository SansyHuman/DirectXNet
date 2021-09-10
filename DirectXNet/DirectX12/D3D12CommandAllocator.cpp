#include "D3D12CommandAllocator.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12CommandAllocator::D3D12CommandAllocator(::ID3D12CommandAllocator* pAlloc)
    : D3D12Pageable((::ID3D12Pageable*)pAlloc)
{
    this->pAlloc = pAlloc;
}

void DirectXNet::DirectX12::D3D12CommandAllocator::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pAlloc = (::ID3D12CommandAllocator*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12CommandAllocator::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12CommandAllocator), Guid);
}

Result DirectXNet::DirectX12::D3D12CommandAllocator::Reset()
{
    return Result(pAlloc->Reset());
}
