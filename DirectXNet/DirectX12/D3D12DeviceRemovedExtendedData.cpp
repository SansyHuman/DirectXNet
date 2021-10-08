#include "D3D12DeviceRemovedExtendedData.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12DeviceRemovedExtendedData::D3D12DeviceRemovedExtendedData(
    ::ID3D12DeviceRemovedExtendedData* pData)
    : DirectXNet::Common::Unknown((::IUnknown*)pData)
{
    this->pData = pData;
}

void DirectXNet::DirectX12::D3D12DeviceRemovedExtendedData::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pData = (::ID3D12DeviceRemovedExtendedData*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12DeviceRemovedExtendedData::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DeviceRemovedExtendedData), Guid);
}

D3D12DREDAutoBreadcrumbsOutput DirectXNet::DirectX12::D3D12DeviceRemovedExtendedData::AutoBreadcrumbsOutput::get()
{
    ::D3D12_DRED_AUTO_BREADCRUMBS_OUTPUT output = {};
    Result::ThrowIfFailed(pData->GetAutoBreadcrumbsOutput(&output));

    return (D3D12DREDAutoBreadcrumbsOutput)output;
}

D3D12DREDPageFaultOutput DirectXNet::DirectX12::D3D12DeviceRemovedExtendedData::PageFaultAllocationOutput::get()
{
    ::D3D12_DRED_PAGE_FAULT_OUTPUT output = {};
    Result::ThrowIfFailed(pData->GetPageFaultAllocationOutput(&output));

    return (D3D12DREDPageFaultOutput)output;
}
