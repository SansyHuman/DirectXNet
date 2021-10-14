#include "D2D1SimplifiedGeometrySink.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::D2D1SimplifiedGeometrySink(
    ::ID2D1SimplifiedGeometrySink* pSimpl)
    : DirectXNet::Common::Unknown((::IUnknown*)pSimpl)
{
    this->pSimpl = pSimpl;
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pSimpl = (::ID2D1SimplifiedGeometrySink*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1SimplifiedGeometrySink), Guid);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::FillMode::set(D2D1FillMode mode)
{
    pSimpl->SetFillMode((::D2D1_FILL_MODE)mode);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::SegmentFlags::set(D2D1PathSegment mode)
{
    pSimpl->SetSegmentFlags((::D2D1_PATH_SEGMENT)mode);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::BeginFigure(
    D2DPoint2F startPoint, D2D1FigureBegin figureBegin)
{
    pSimpl->BeginFigure(CAST_TO(startPoint, ::D2D1_POINT_2F), (::D2D1_FIGURE_BEGIN)figureBegin);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::AddLines(...array<D2DPoint2F>^ points)
{
    pin_ptr<D2DPoint2F> pPoints = &points[0];

    pSimpl->AddLines((::D2D1_POINT_2F*)pPoints, points->Length);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::AddBeziers(...array<D2D1BezierSegment>^ beziers)
{
    pin_ptr<D2D1BezierSegment> pBeziers = &beziers[0];

    pSimpl->AddBeziers((::D2D1_BEZIER_SEGMENT*)pBeziers, beziers->Length);
}

void DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::EndFigure(D2D1FigureEnd figureEnd)
{
    pSimpl->EndFigure((::D2D1_FIGURE_END)figureEnd);
}

Result DirectXNet::Direct2D::D2D1SimplifiedGeometrySink::Close()
{
    return Result(pSimpl->Close());
}
