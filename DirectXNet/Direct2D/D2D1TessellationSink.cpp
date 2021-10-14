#include "D2D1TessellationSink.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1TessellationSink::D2D1TessellationSink(
    ::ID2D1TessellationSink* pSink)
    : DirectXNet::Common::Unknown((::IUnknown*)pSink)
{
    this->pSink = pSink;
}

void DirectXNet::Direct2D::D2D1TessellationSink::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pSink = (::ID2D1TessellationSink*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1TessellationSink::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1TessellationSink), Guid);
}

void DirectXNet::Direct2D::D2D1TessellationSink::AddTriangled(...array<D2D1Triangle>^ triangles)
{
    pin_ptr<D2D1Triangle> pTriangles = &triangles[0];
    pSink->AddTriangles((::D2D1_TRIANGLE*)pTriangles, triangles->Length);
}

Result DirectXNet::Direct2D::D2D1TessellationSink::Close()
{
    return Result(pSink->Close());
}
