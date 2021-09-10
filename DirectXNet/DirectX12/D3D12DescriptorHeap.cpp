#include "D3D12DescriptorHeap.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12DescriptorHeap::D3D12DescriptorHeap(::ID3D12DescriptorHeap* pHeap)
    : D3D12Pageable((::ID3D12Pageable*)pHeap)
{
    this->pHeap = pHeap;
}

void DirectXNet::DirectX12::D3D12DescriptorHeap::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pHeap = (::ID3D12DescriptorHeap*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12DescriptorHeap::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DescriptorHeap), Guid);
}

D3D12DescriptorHeapDesc DirectXNet::DirectX12::D3D12DescriptorHeap::DescriptorHeapDesc::get()
{
    return CAST_TO(pHeap->GetDesc(), D3D12DescriptorHeapDesc);
}

D3D12CPUDescriptorHandle
DirectXNet::DirectX12::D3D12DescriptorHeap::CPUDescriptorHandleForHeapStart::get()
{
    return CAST_TO(pHeap->GetCPUDescriptorHandleForHeapStart(), D3D12CPUDescriptorHandle);
}

D3D12GPUDescriptorHandle
DirectXNet::DirectX12::D3D12DescriptorHeap::GPUDescriptorHandleForHeapStart::get()
{
    return CAST_TO(pHeap->GetGPUDescriptorHandleForHeapStart(), D3D12GPUDescriptorHandle);
}
