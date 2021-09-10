#include "D3D12Heap.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Heap::D3D12Heap(::ID3D12Heap* pHeap)
    : D3D12Pageable((::ID3D12Pageable*)pHeap)
{
    this->pHeap = pHeap;
}

void DirectXNet::DirectX12::D3D12Heap::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pHeap = (::ID3D12Heap*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12Heap::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Heap), Guid);
}

D3D12HeapDesc DirectXNet::DirectX12::D3D12Heap::HeapDesc::get()
{
    return CAST_TO(pHeap->GetDesc(), D3D12HeapDesc);
}
