#include "D2D1.h"

#include "D2D1Factory.h"
#include "D2D1Geometry.h"
#include "D2D1GeometrySink.h"
#include "D2D1RectangleGeometry.h"
#include "D2D1Resource.h"
#include "D2D1RoundedRectangleGeometry.h"
#include "D2D1SimplifiedGeometrySink.h"
#include "D2D1StrokeStyle.h"
#include "D2D1TessellationSink.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;
using namespace msclr::interop;

#ifndef CHECK_D2D1_GUID
#define CHECK_D2D1_GUID(type) if(*((_GUID*)&Unknown::GetGuidOfObject<DirectXNet::Direct2D:: ## type ## ^>()) != __uuidof(::I ## type)) throw gcnew Exception("GUID check error");
#endif

float DirectXNet::Direct2D::D2D1::FloatMax::get()
{
    return Single::MaxValue;
}

DirectXNet::Direct2D::D2D1::D2D1()
{
#if defined(DEBUG) | defined(_DEBUG)
    CHECK_D2D1_GUID(D2D1Factory);
    CHECK_D2D1_GUID(D2D1Geometry);
    CHECK_D2D1_GUID(D2D1GeometrySink);
    CHECK_D2D1_GUID(D2D1RectangleGeometry);
    CHECK_D2D1_GUID(D2D1Resource);
    CHECK_D2D1_GUID(D2D1RoundedRectangleGeometry);
    CHECK_D2D1_GUID(D2D1SimplifiedGeometrySink);
    CHECK_D2D1_GUID(D2D1StrokeStyle);
    CHECK_D2D1_GUID(D2D1TessellationSink);
#endif
}

D2DMatrix3X2F DirectXNet::Direct2D::D2D1::MakeRotateMatrix(float angle, D2DPoint2F center)
{
    return D2DMatrix3X2F::CreateRotation(angle * Deg2Rad, CAST_TO(center, System::Numerics::Vector2));
}

D2DMatrix3X2F DirectXNet::Direct2D::D2D1::MakeSkewMatrix(float angleX, float angleY, D2DPoint2F center)
{
    return D2DMatrix3X2F::CreateSkew(angleX * Deg2Rad, angleY * Deg2Rad, CAST_TO(center, System::Numerics::Vector2));
}

D2DColorF DirectXNet::Direct2D::D2D1::ColorF(unsigned int rgb, Nullable<float> a)
{
    D2DColorF color;
    color.r = static_cast<FLOAT>((rgb & sc_redMask) >> sc_redShift) / 255.f;
    color.g = static_cast<FLOAT>((rgb & sc_greenMask) >> sc_greenShift) / 255.f;
    color.b = static_cast<FLOAT>((rgb & sc_blueMask) >> sc_blueShift) / 255.f;
    color.a = a.HasValue ? a.Value : 1.0f;

    return color;
}

D2DColorF DirectXNet::Direct2D::D2D1::ColorF(D2DColor knownColor, Nullable<float> a)
{
    unsigned int rgb = (unsigned int)knownColor;

    D2DColorF color;
    color.r = static_cast<FLOAT>((rgb & sc_redMask) >> sc_redShift) / 255.f;
    color.g = static_cast<FLOAT>((rgb & sc_greenMask) >> sc_greenShift) / 255.f;
    color.b = static_cast<FLOAT>((rgb & sc_blueMask) >> sc_blueShift) / 255.f;
    color.a = a.HasValue ? a.Value : 1.0f;

    return color;
}

D2DColorF DirectXNet::Direct2D::D2D1::ColorF(float r, float g, float b, Nullable<float> a)
{
    D2DColorF color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a.HasValue ? a.Value : 1.0f;

    return color;
}

D2DMatrix3X2F DirectXNet::Direct2D::D2D1::IdentityMatrix::get()
{
    return D2DMatrix3X2F::Identity;
}
