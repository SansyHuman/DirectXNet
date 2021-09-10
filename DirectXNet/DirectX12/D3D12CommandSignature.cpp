#include "D3D12CommandSignature.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12CommandSignature::D3D12CommandSignature(::ID3D12CommandSignature* pSignature)
    : D3D12Pageable((::ID3D12Pageable*)pSignature)
{

}

void DirectXNet::DirectX12::D3D12CommandSignature::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
}

Guid DirectXNet::DirectX12::D3D12CommandSignature::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12CommandSignature), Guid);
}
