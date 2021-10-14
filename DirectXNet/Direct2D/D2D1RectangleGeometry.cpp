#include "D2D1RectangleGeometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1RectangleGeometry::D2D1RectangleGeometry(::ID2D1RectangleGeometry* pRect)
    : D2D1Geometry((::ID2D1Geometry*)pRect)
{
    this->pRect = pRect;
}

void DirectXNet::Direct2D::D2D1RectangleGeometry::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Geometry::AttatchComObj(pComObj);
    pRect = (::ID2D1RectangleGeometry*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1RectangleGeometry::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1RectangleGeometry), Guid);
}

D2DRectF DirectXNet::Direct2D::D2D1RectangleGeometry::Rect::get()
{
    D2DRectF rect;
    pRect->GetRect((::D2D1_RECT_F*)&rect);

    return rect;
}
