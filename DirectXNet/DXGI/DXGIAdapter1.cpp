#include "DXGIAdapter1.h"

#include "../Common/Result.h"
#include "DXGIOutput.h"

using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;
using namespace msclr::interop;

DirectXNet::DXGI::DXGIAdapter1::DXGIAdapter1(::IDXGIAdapter1* pAdapter1)
    : DXGIAdapter((::IDXGIAdapter*)pAdapter1)
{
    this->pAdapter1 = pAdapter1;
}

void DirectXNet::DXGI::DXGIAdapter1::AttatchComObj(::IUnknown* pComObj)
{
    DXGIAdapter::AttatchComObj(pComObj);
    pAdapter1 = (::IDXGIAdapter1*)pComObj;
}

Guid DirectXNet::DXGI::DXGIAdapter1::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIAdapter1), Guid);
}

DXGIAdapterDesc1 DirectXNet::DXGI::DXGIAdapter1::AdapterDesc1::get()
{
    ::DXGI_ADAPTER_DESC1 desc = {};
    Result::ThrowIfFailed(pAdapter1->GetDesc1(&desc));

    DXGIAdapterDesc1 clrDesc;
    clrDesc.Description = marshal_as<System::String^>(desc.Description);
    clrDesc.VendorId = desc.VendorId;
    clrDesc.DeviceId = desc.DeviceId;
    clrDesc.SubSysId = desc.SubSysId;
    clrDesc.Revision = desc.Revision;
    clrDesc.DedicatedVideoMemory = desc.DedicatedVideoMemory;
    clrDesc.DedicatedSystemMemory = desc.DedicatedSystemMemory;
    clrDesc.SharedSystemMemory = desc.SharedSystemMemory;
    clrDesc.AdapterLuid = *((Common::Luid*)&desc.VendorId);
    clrDesc.Flags = (DXGIAdapterFlag)desc.Flags;

    return clrDesc;
}