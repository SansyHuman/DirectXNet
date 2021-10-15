#include "D2D1Factory.h"
#include "D2D1RectangleGeometry.h"
#include "D2D1RoundedRectangleGeometry.h"
#include "D2D1EllipseGeometry.h"
#include "D2D1GeometryGroup.h"
#include "D2D1Geometry.h"
#include "D2D1TransformedGeometry.h"

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

D2D1EllipseGeometry^ DirectXNet::Direct2D::D2D1Factory::CreateEllipseGeometry(D2D1Ellipse% ellipse)
{
    ::ID2D1EllipseGeometry* pEllipse = __nullptr;

    try
    {
        pin_ptr<D2D1Ellipse> pEll = &ellipse;

        Result::ThrowIfFailed(pFactory->CreateEllipseGeometry(
            (::D2D1_ELLIPSE*)pEll,
            &pEllipse
        ));

        return gcnew D2D1EllipseGeometry(pEllipse);
    }
    finally
    {
        SAFE_RELEASE(pEllipse);
    }
}

D2D1GeometryGroup^ DirectXNet::Direct2D::D2D1Factory::CreateGeometryGroup(
    D2D1FillMode fillMode, ...array<D2D1Geometry^>^ geometries)
{
    UINT32 geometriesCount = geometries->Length;
    std::vector<::ID2D1Geometry*> geo(geometriesCount, __nullptr);
    ::ID2D1GeometryGroup* pGroup = __nullptr;

    try
    {
        for(UINT i = 0; i < geometriesCount; i++)
        {
            geo[i] = (::ID2D1Geometry*)geometries[i]->GetNativeInterface();
        }

        Result::ThrowIfFailed(pFactory->CreateGeometryGroup(
            (::D2D1_FILL_MODE)fillMode,
            geo.data(),
            geometriesCount,
            &pGroup
        ));

        return gcnew D2D1GeometryGroup(pGroup);
    }
    finally
    {
        for(UINT i = 0; i < geometriesCount; i++)
        {
            SAFE_RELEASE(geo[i]);
        }

        SAFE_RELEASE(pGroup);
    }
}

D2D1TransformedGeometry^ DirectXNet::Direct2D::D2D1Factory::CreateTransformedGeometry(
    D2D1Geometry^ sourceGeometry, D2DMatrix3X2F% transform)
{
    ::ID2D1Geometry* pSource = __nullptr;
    ::ID2D1TransformedGeometry* pTrans = __nullptr;

    try
    {
        pSource = (::ID2D1Geometry*)sourceGeometry->GetNativeInterface();
        pin_ptr<D2DMatrix3X2F> pTransform = &transform;

        Result::ThrowIfFailed(pFactory->CreateTransformedGeometry(
            pSource,
            (::D2D1_MATRIX_3X2_F*)pTransform,
            &pTrans
        ));

        return gcnew D2D1TransformedGeometry(pTrans);
    }
    finally
    {
        SAFE_RELEASE(pSource);
        SAFE_RELEASE(pTrans);
    }
}
