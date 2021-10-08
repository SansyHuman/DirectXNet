#include "D3D12DeviceRemovedExtendedDataSettings.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::D3D12DeviceRemovedExtendedDataSettings(
    ::ID3D12DeviceRemovedExtendedDataSettings* pSettings)
    : DirectXNet::Common::Unknown((::IUnknown*)pSettings)
{
    this->pSettings = pSettings;
}

void DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pSettings = (::ID3D12DeviceRemovedExtendedDataSettings*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DeviceRemovedExtendedDataSettings), Guid);
}

void DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::SetAutoBreadcrumbsEnablement(
    D3D12DREDEnablement enablement)
{
    pSettings->SetAutoBreadcrumbsEnablement((::D3D12_DRED_ENABLEMENT)enablement);
}

void DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::SetPageFaultEnablement(
    D3D12DREDEnablement enablement)
{
    pSettings->SetPageFaultEnablement((::D3D12_DRED_ENABLEMENT)enablement);
}

void DirectXNet::DirectX12::D3D12DeviceRemovedExtendedDataSettings::SetWatsonDumpEnablement(
    D3D12DREDEnablement enablement)
{
    pSettings->SetWatsonDumpEnablement((::D3D12_DRED_ENABLEMENT)enablement);
}
