#include "D3D12DebugDevice.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugDevice::D3D12DebugDevice(::ID3D12DebugDevice* pDevice)
    : DirectXNet::Common::Unknown((::IUnknown*)pDevice)
{
    this->pDevice = pDevice;
}

void DirectXNet::DirectX12::Debug::D3D12DebugDevice::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDevice = (::ID3D12DebugDevice*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugDevice::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugDevice), Guid);
}

D3D12DebugFeature DirectXNet::DirectX12::Debug::D3D12DebugDevice::FeatureMask::get()
{
    return (D3D12DebugFeature)pDevice->GetFeatureMask();
}

void DirectXNet::DirectX12::Debug::D3D12DebugDevice::FeatureMask::set(D3D12DebugFeature mask)
{
    Result::ThrowIfFailed(pDevice->SetFeatureMask((::D3D12_DEBUG_FEATURE)mask));
}

Result DirectXNet::DirectX12::Debug::D3D12DebugDevice::ReportLiveDeviceObjects(D3D12RLDOFlags flags)
{
    return Result(pDevice->ReportLiveDeviceObjects((::D3D12_RLDO_FLAGS)flags));
}
