#include "DXGISurface1.h"
#include "../Common/Result.h"

using namespace DirectXNet::Common;
using namespace msclr::interop;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGISurface1::DXGISurface1(::IDXGISurface1* pSurface1)
    :DXGISurface((::IDXGISurface*)pSurface1)
{
    this->pSurface1.Attach(pSurface1);
}

void DirectXNet::DXGI::DXGISurface1::AttatchComObj(::IUnknown* pComObj)
{
    DXGISurface::AttatchComObj(pComObj);
    pSurface1.Release();
    pSurface1.Attach((::IDXGISurface1*)pComObj);
}

Guid DirectXNet::DXGI::DXGISurface1::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGISurface1), Guid);
}

IntPtr DirectXNet::DXGI::DXGISurface1::GetDC(bool discard)
{
    HDC hdc = __nullptr;
    Result::ThrowIfFailed(pSurface1->GetDC((BOOL)discard, &hdc));
    return IntPtr(hdc);
}

Result DirectXNet::DXGI::DXGISurface1::ReleaseDC(Nullable<Rect> dirtyRect)
{
    RECT* pRect = __nullptr;
    if(dirtyRect.HasValue)
        pRect = (RECT*)&dirtyRect.Value;

    return Result(pSurface1->ReleaseDC(pRect));
}
