#include "DXGIAdapter.h"
#include "../Common/Result.h"
#include "DXGIOutput.h"

using namespace DirectXNet::Common;
using namespace msclr::interop;

DirectXNet::DXGI::DXGIAdapter::DXGIAdapter(::IDXGIAdapter* pAdapter)
    : DXGIObject((::IDXGIObject*)pAdapter)
{
    this->pAdapter = pAdapter;
}

void DirectXNet::DXGI::DXGIAdapter::AttatchComObj(::IUnknown* pComObj)
{
    DXGIObject::AttatchComObj(pComObj);
    pAdapter = (::IDXGIAdapter*)pComObj;
}

Guid DirectXNet::DXGI::DXGIAdapter::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIAdapter), Guid);
}

Result DirectXNet::DXGI::DXGIAdapter::EnumOutputs(unsigned int index, DXGIOutput^% output)
{
    ::IDXGIOutput* pOutput = __nullptr;

    try
    {
        HRESULT hr = pAdapter->EnumOutputs(index, &pOutput);
        if(FAILED(hr))
        {
            output = nullptr;
            return Result(hr);
        }

        output = gcnew DXGIOutput(pOutput);

        return Result(hr);
    }
    finally
    {
        SAFE_RELEASE(pOutput);
    }
}

DirectXNet::DXGI::DXGIAdapterDesc DirectXNet::DXGI::DXGIAdapter::AdapterDesc::get()
{
    ::DXGI_ADAPTER_DESC desc = {};
    Result::ThrowIfFailed(pAdapter->GetDesc(&desc));

    DirectXNet::DXGI::DXGIAdapterDesc clrDesc;
    clrDesc.Description = marshal_as<System::String^>(desc.Description);
    clrDesc.VendorId = desc.VendorId;
    clrDesc.DeviceId = desc.DeviceId;
    clrDesc.SubSysId = desc.SubSysId;
    clrDesc.Revision = desc.Revision;
    clrDesc.DedicatedVideoMemory = desc.DedicatedVideoMemory;
    clrDesc.DedicatedSystemMemory = desc.DedicatedSystemMemory;
    clrDesc.SharedSystemMemory = desc.SharedSystemMemory;
    clrDesc.AdapterLuid = *((Common::Luid*)&desc.VendorId);

    return clrDesc;
}
