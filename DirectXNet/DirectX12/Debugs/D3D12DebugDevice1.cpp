#include "D3D12DebugDevice1.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugDevice1::D3D12DebugDevice1(::ID3D12DebugDevice1* pDevice)
    : DirectXNet::Common::Unknown((::IUnknown*)pDevice)
{
    this->pDevice = pDevice;
}

void DirectXNet::DirectX12::Debug::D3D12DebugDevice1::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDevice = (::ID3D12DebugDevice1*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugDevice1::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugDevice1), Guid);
}

generic <typename T> where T : IDeviceDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugDevice1::SetDebugParameter(
    D3D12DebugDeviceParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pDevice->SetDebugParameter(
        (::D3D12_DEBUG_DEVICE_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}

generic <typename T> where T : IDeviceDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugDevice1::GetDebugParameter(
    D3D12DebugDeviceParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pDevice->GetDebugParameter(
        (::D3D12_DEBUG_DEVICE_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}

Result DirectXNet::DirectX12::Debug::D3D12DebugDevice1::ReportLiveDeviceObjects(D3D12RLDOFlags flags)
{
    return Result(pDevice->ReportLiveDeviceObjects((::D3D12_RLDO_FLAGS)flags));
}
