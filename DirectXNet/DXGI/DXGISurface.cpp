#include "DXGISurface.h"
#include "../Common/Result.h"

using namespace DirectXNet::Common;
using namespace msclr::interop;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGISurface::DXGISurface(::IDXGISurface* pSurface)
    : DXGIDeviceSubObject((::IDXGIDeviceSubObject*)pSurface)
{
    this->pSurface.Attach(pSurface);
}

void DirectXNet::DXGI::DXGISurface::AttatchComObj(::IUnknown* pComObj)
{
    DXGIDeviceSubObject::AttatchComObj(pComObj);
    pSurface.Release();
    pSurface.Attach((::IDXGISurface*)pComObj);
}

Guid DirectXNet::DXGI::DXGISurface::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGISurface), Guid);
}

DXGISurfaceDesc DirectXNet::DXGI::DXGISurface::SurfaceDesc::get()
{
    DXGISurfaceDesc desc;
    Result::ThrowIfFailed(pSurface->GetDesc((::DXGI_SURFACE_DESC*)&desc));

    return desc;
}

DXGIMappedRect DirectXNet::DXGI::DXGISurface::Map(DXGIMapFlag mapFlags)
{
    DXGIMappedRect rect;
    Result::ThrowIfFailed(pSurface->Map((::DXGI_MAPPED_RECT*)&rect, (UINT)mapFlags));

    return rect;
}

void DirectXNet::DXGI::DXGISurface::Unmap()
{
    Result::ThrowIfFailed(pSurface->Unmap());
}
