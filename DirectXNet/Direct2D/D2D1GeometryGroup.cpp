#include "D2D1GeometryGroup.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1GeometryGroup::D2D1GeometryGroup(
    ::ID2D1GeometryGroup* pGroup)
    : D2D1Geometry((::ID2D1Geometry*)pGroup)
{
    this->pGroup = pGroup;
}

void DirectXNet::Direct2D::D2D1GeometryGroup::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Geometry::AttatchComObj(pComObj);
    pGroup = (::ID2D1GeometryGroup*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1GeometryGroup::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1GeometryGroup), Guid);
}

D2D1FillMode DirectXNet::Direct2D::D2D1GeometryGroup::FillMode::get()
{
    return (D2D1FillMode)pGroup->GetFillMode();
}

unsigned int DirectXNet::Direct2D::D2D1GeometryGroup::SourceGeometryCount::get()
{
    return pGroup->GetSourceGeometryCount();
}

void DirectXNet::Direct2D::D2D1GeometryGroup::GetSourceGeometries(array<D2D1Geometry^>^ geometries)
{
    UINT32 geometriesCount = geometries->Length;

    std::vector<::ID2D1Geometry*> geo(geometriesCount, __nullptr);

    try
    {
        pGroup->GetSourceGeometries(geo.data(), geometriesCount);

        for(UINT32 i = 0; i < geometriesCount; i++)
        {
            geometries[i] = gcnew D2D1Geometry(geo[i]);
        }
    }
    finally
    {
        for(UINT32 i = 0; i < geometriesCount; i++)
        {
            SAFE_RELEASE(geo[i]);
        }
    }
}
