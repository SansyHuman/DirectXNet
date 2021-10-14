#include "D2D1RoundedRectangleGeometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1RoundedRectangleGeometry::D2D1RoundedRectangleGeometry(
    ::ID2D1RoundedRectangleGeometry* pRect)
    : D2D1Geometry((::ID2D1Geometry*)pRect)
{
    this->pRect = pRect;
}

void DirectXNet::Direct2D::D2D1RoundedRectangleGeometry::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Geometry::AttatchComObj(pComObj);
    pRect = (::ID2D1RoundedRectangleGeometry*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1RoundedRectangleGeometry::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1RoundedRectangleGeometry), Guid);
}

D2D1RoundedRect DirectXNet::Direct2D::D2D1RoundedRectangleGeometry::RoundedRect::get()
{
    D2D1RoundedRect rect;
    pRect->GetRoundedRect((::D2D1_ROUNDED_RECT*)&rect);

    return rect;
}
