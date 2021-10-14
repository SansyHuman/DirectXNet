#include "DXGIDeviceSubObject.h"
#include "DXGIDevice.h"
#include "../Common/Result.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIDeviceSubObject::DXGIDeviceSubObject(::IDXGIDeviceSubObject* pSubObj)
    : DXGIObject((::IDXGIObject*)pSubObj)
{
    this->pSubObj = pSubObj;
}

void DirectXNet::DXGI::DXGIDeviceSubObject::AttatchComObj(::IUnknown* pComObj)
{
    DXGIObject::AttatchComObj(pComObj);
    pSubObj = (::IDXGIDeviceSubObject*)pComObj;
}

Guid DirectXNet::DXGI::DXGIDeviceSubObject::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIDeviceSubObject), Guid);
}

generic <typename T> where T : DirectXNet::Common::Unknown
T DXGIDeviceSubObject::GetDevice()
{
    ::IUnknown* pDevice = __nullptr;

    try
    {
        Guid guid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pSubObj->GetDevice(CAST_TO(guid, _GUID), (void**)&pDevice));

        T device = (T)Activator::CreateInstance(T::typeid, true);
        device->AttatchComObj(pDevice);

        return device;
    }
    finally
    {
        SAFE_RELEASE(pDevice);
    }
}