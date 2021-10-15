#include "D2D1TransformedGeometry.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1TransformedGeometry::D2D1TransformedGeometry(
    ::ID2D1TransformedGeometry* pTrans)
    : D2D1Geometry((::ID2D1Geometry*)pTrans)
{
    this->pTrans = pTrans;
}

void DirectXNet::Direct2D::D2D1TransformedGeometry::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Geometry::AttatchComObj(pComObj);
    pTrans = (::ID2D1TransformedGeometry*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1TransformedGeometry::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1TransformedGeometry), Guid);
}

D2D1Geometry^ DirectXNet::Direct2D::D2D1TransformedGeometry::SourceGeometry::get()
{
    ::ID2D1Geometry* pGeo = __nullptr;

    try
    {
        pTrans->GetSourceGeometry(&pGeo);
        return gcnew D2D1Geometry(pGeo);
    }
    finally
    {
        SAFE_RELEASE(pGeo);
    }
}

D2DMatrix3X2F DirectXNet::Direct2D::D2D1TransformedGeometry::Transform::get()
{
    D2DMatrix3X2F transform;
    pTrans->GetTransform((::D2D1_MATRIX_3X2_F*)&transform);

    return transform;
}
