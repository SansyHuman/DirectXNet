#include "D2D1GeometrySink.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1GeometrySink::D2D1GeometrySink(
    ::ID2D1GeometrySink* pSink)
    : D2D1SimplifiedGeometrySink((::ID2D1SimplifiedGeometrySink*)pSink)
{
    this->pSink = pSink;
}

void DirectXNet::Direct2D::D2D1GeometrySink::AttatchComObj(::IUnknown* pComObj)
{
    D2D1SimplifiedGeometrySink::AttatchComObj(pComObj);
    pSink = (::ID2D1GeometrySink*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1GeometrySink::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1GeometrySink), Guid);
}

void DirectXNet::Direct2D::D2D1GeometrySink::AddLine(D2DPoint2F point)
{
    pSink->AddLine(CAST_TO(point, ::D2D1_POINT_2F));
}

void DirectXNet::Direct2D::D2D1GeometrySink::AddBezier(D2D1BezierSegment% bezier)
{
    pin_ptr<D2D1BezierSegment> pBezier = &bezier;
    pSink->AddBezier((::D2D1_BEZIER_SEGMENT*)pBezier);
}

void DirectXNet::Direct2D::D2D1GeometrySink::AddQuadraticBezier(D2D1QuadraticBezierSegment% bezier)
{
    pin_ptr<D2D1QuadraticBezierSegment> pBezier = &bezier;
    pSink->AddQuadraticBezier((::D2D1_QUADRATIC_BEZIER_SEGMENT*)pBezier);
}

void DirectXNet::Direct2D::D2D1GeometrySink::AddQuadraticBeziers(
    ...array<D2D1QuadraticBezierSegment>^ beziers)
{
    pin_ptr<D2D1QuadraticBezierSegment> pBeziers = &beziers[0];
    pSink->AddQuadraticBeziers((::D2D1_QUADRATIC_BEZIER_SEGMENT*)pBeziers, beziers->Length);
}

void DirectXNet::Direct2D::D2D1GeometrySink::AddArc(D2D1ArcSegment% arc)
{
    pin_ptr<D2D1ArcSegment> pArc = &arc;
    pSink->AddArc((::D2D1_ARC_SEGMENT*)pArc);
}
