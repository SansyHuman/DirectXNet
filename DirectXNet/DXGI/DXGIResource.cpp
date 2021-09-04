#include "DXGIResource.h"
#include "../Common/Result.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIResource::DXGIResource(::IDXGIResource* pResource)
    : DXGIDeviceSubObject((::IDXGIDeviceSubObject*)pResource)
{
    this->pResource.Attach(pResource);
}

void DirectXNet::DXGI::DXGIResource::AttatchComObj(::IUnknown* pComObj)
{
    DXGIDeviceSubObject::AttatchComObj(pComObj);
    pResource.Release();
    pResource.Attach((::IDXGIResource*)pComObj);
}

Guid DirectXNet::DXGI::DXGIResource::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIResource), Guid);
}

IntPtr DirectXNet::DXGI::DXGIResource::SharedHandle::get()
{
    HANDLE handle = __nullptr;
    Result::ThrowIfFailed(pResource->GetSharedHandle(&handle));
    return IntPtr(handle);
}

DXGIUsage DirectXNet::DXGI::DXGIResource::Usage::get()
{
    DXGI_USAGE usage = 0;
    Result::ThrowIfFailed(pResource->GetUsage(&usage));
    return (DXGIUsage)usage;
}

unsigned int DirectXNet::DXGI::DXGIResource::EvictionPriority::get()
{
    unsigned int priority = 0;
    Result::ThrowIfFailed(pResource->GetEvictionPriority(&priority));
    return priority;
}

void DirectXNet::DXGI::DXGIResource::EvictionPriority::set(unsigned int priority)
{
    Result::ThrowIfFailed(pResource->SetEvictionPriority(priority));
}
