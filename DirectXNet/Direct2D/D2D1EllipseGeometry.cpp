#include "D2D1EllipseGeometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1EllipseGeometry::D2D1EllipseGeometry(
    ::ID2D1EllipseGeometry* pEllipse)
    : D2D1Geometry((::ID2D1Geometry*)pEllipse)
{
    this->pEllipse = pEllipse;
}

void DirectXNet::Direct2D::D2D1EllipseGeometry::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Geometry::AttatchComObj(pComObj);
    pEllipse = (::ID2D1EllipseGeometry*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1EllipseGeometry::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1EllipseGeometry), Guid);
}

D2D1Ellipse DirectXNet::Direct2D::D2D1EllipseGeometry::Ellipse::get()
{
    D2D1Ellipse ellipse;
    pEllipse->GetEllipse((::D2D1_ELLIPSE*)&ellipse);

    return ellipse;
}
