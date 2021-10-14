#include "D3D12DebugDevice2.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugDevice2::D3D12DebugDevice2(::ID3D12DebugDevice2* pDevice2)
    : D3D12DebugDevice((::ID3D12DebugDevice*)pDevice2)
{
    this->pDevice2 = pDevice2;
}

void DirectXNet::DirectX12::Debug::D3D12DebugDevice2::AttatchComObj(::IUnknown* pComObj)
{
    D3D12DebugDevice::AttatchComObj(pComObj);
    pDevice2 = (::ID3D12DebugDevice2*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugDevice2::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugDevice2), Guid);
}

generic <typename T> where T : IDeviceDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugDevice2::SetDebugParameter(
    D3D12DebugDeviceParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pDevice2->SetDebugParameter(
        (::D3D12_DEBUG_DEVICE_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}

generic <typename T> where T : IDeviceDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugDevice2::GetDebugParameter(
    D3D12DebugDeviceParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pDevice2->GetDebugParameter(
        (::D3D12_DEBUG_DEVICE_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}
