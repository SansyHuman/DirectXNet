#include "D3D12RootSignature.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12RootSignature::D3D12RootSignature(::ID3D12RootSignature* pSignature)
    : D3D12DeviceChild((::ID3D12DeviceChild*)pSignature)
{
    
}

void DirectXNet::DirectX12::D3D12RootSignature::AttatchComObj(::IUnknown* pComObj)
{
    D3D12DeviceChild::AttatchComObj(pComObj);
}

Guid DirectXNet::DirectX12::D3D12RootSignature::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12RootSignature), Guid);
}

IntPtr DirectXNet::DirectX12::D3D12RootSignature::NativeRootSignature::get()
{
    ::IUnknown* pSignature = __nullptr;

    try
    {
        pSignature = GetNativeInterface();
        return IntPtr((void*)pSignature);
    }
    finally
    {
        SAFE_RELEASE(pSignature);
    }
}
