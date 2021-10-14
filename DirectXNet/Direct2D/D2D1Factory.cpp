#include "D2D1Factory.h"
#include "D2D1RectangleGeometry.h"
#include "D2D1RoundedRectangleGeometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1Factory::D2D1Factory(::ID2D1Factory* pFactory)
    : DirectXNet::Common::Unknown((::IUnknown*)pFactory)
{
    this->pFactory = pFactory;
}

void DirectXNet::Direct2D::D2D1Factory::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pFactory = (::ID2D1Factory*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1Factory::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1Factory), Guid);
}

Result DirectXNet::Direct2D::D2D1Factory::ReloadSystemMetrics()
{
    return Result(pFactory->ReloadSystemMetrics());
}

void DirectXNet::Direct2D::D2D1Factory::GetDesktopDpi(float% dpiX, float% dpiY)
{
    float x = 0, y = 0;
    pFactory->GetDesktopDpi(&x, &y);
    dpiX = x;
    dpiY = y;
}

D2D1RectangleGeometry^ DirectXNet::Direct2D::D2D1Factory::CreateRectangleGeometry(D2DRectF% rectangle)
{
    ::ID2D1RectangleGeometry* pRect = __nullptr;

    try
    {
        pin_ptr<D2DRectF> pRectangle = &rectangle;

        Result::ThrowIfFailed(pFactory->CreateRectangleGeometry(
            (::D2D1_RECT_F*)pRectangle,
            &pRect
        ));

        return gcnew D2D1RectangleGeometry(pRect);
    }
    finally
    {
        SAFE_RELEASE(pRect);
    }
}

D2D1RoundedRectangleGeometry^ DirectXNet::Direct2D::D2D1Factory::CreateRoundedRectangleGeometry(
    D2D1RoundedRect% roundedRectangle)
{
    ::ID2D1RoundedRectangleGeometry* pRect = __nullptr;

    try
    {
        pin_ptr<D2D1RoundedRect> pRectangle = &roundedRectangle;

        Result::ThrowIfFailed(pFactory->CreateRoundedRectangleGeometry(
            (::D2D1_ROUNDED_RECT*)pRectangle,
            &pRect
        ));

        return gcnew D2D1RoundedRectangleGeometry(pRect);
    }
    finally
    {
        SAFE_RELEASE(pRect);
    }
}
