#include "D2D1StrokeStyle.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1StrokeStyle::D2D1StrokeStyle(::ID2D1StrokeStyle* pStroke)
    : D2D1Resource((::ID2D1Resource*)pStroke)
{
    this->pStroke = pStroke;
}

void DirectXNet::Direct2D::D2D1StrokeStyle::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Resource::AttatchComObj(pComObj);
    pStroke = (::ID2D1StrokeStyle*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1StrokeStyle::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1StrokeStyle), Guid);
}

D2D1CapStyle DirectXNet::Direct2D::D2D1StrokeStyle::StartCap::get()
{
    return (D2D1CapStyle)pStroke->GetStartCap();
}

D2D1CapStyle DirectXNet::Direct2D::D2D1StrokeStyle::EndCap::get()
{
    return (D2D1CapStyle)pStroke->GetEndCap();
}

D2D1CapStyle DirectXNet::Direct2D::D2D1StrokeStyle::DashCap::get()
{
    return (D2D1CapStyle)pStroke->GetDashCap();
}

float DirectXNet::Direct2D::D2D1StrokeStyle::MiterLimit::get()
{
    return pStroke->GetMiterLimit();
}

D2D1LineJoin DirectXNet::Direct2D::D2D1StrokeStyle::LineJoin::get()
{
    return (D2D1LineJoin)pStroke->GetLineJoin();
}

float DirectXNet::Direct2D::D2D1StrokeStyle::DashOffset::get()
{
    return pStroke->GetDashOffset();
}

D2D1DashStyle DirectXNet::Direct2D::D2D1StrokeStyle::DashStyle::get()
{
    return (D2D1DashStyle)pStroke->GetDashStyle();
}

unsigned int DirectXNet::Direct2D::D2D1StrokeStyle::DashesCount::get()
{
    return pStroke->GetDashesCount();
}

void DirectXNet::Direct2D::D2D1StrokeStyle::GetDashes(array<float>^ dashes)
{
    pin_ptr<float> pDashes = &dashes[0];
    pStroke->GetDashes((float*)pDashes, dashes->Length);
}
