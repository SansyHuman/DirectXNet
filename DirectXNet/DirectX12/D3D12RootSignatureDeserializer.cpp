#include "D3D12RootSignatureDeserializer.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12RootSignatureDeserializer::D3D12RootSignatureDeserializer(
    ::ID3D12RootSignatureDeserializer* pDeserializer)
    : Unknown((::IUnknown*)pDeserializer)
{
    this->pDeserializer = pDeserializer;
}

void DirectXNet::DirectX12::D3D12RootSignatureDeserializer::AttatchComObj(::IUnknown* pComObj)
{
    Unknown::AttatchComObj(pComObj);
    pDeserializer = (::ID3D12RootSignatureDeserializer*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12RootSignatureDeserializer::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12RootSignatureDeserializer), Guid);
}

D3D12RootSignatureDesc DirectXNet::DirectX12::D3D12RootSignatureDeserializer::RootSignatureDesc::get()
{
    return *((D3D12RootSignatureDesc*)pDeserializer->GetRootSignatureDesc());
}
