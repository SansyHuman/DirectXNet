#include "D2D1Geometry.h"
#include "D2D1StrokeStyle.h"
#include "D2D1SimplifiedGeometrySink.h"
#include "D2D1CustomGeometrySink.h"
#include "D2D1CustomGeometrySinkNative.h"
#include "D2D1TessellationSink.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1Geometry::D2D1Geometry(::ID2D1Geometry* pGeometry)
    : D2D1Resource((::ID2D1Resource*)pGeometry)
{
    this->pGeometry = pGeometry;
}

void DirectXNet::Direct2D::D2D1Geometry::AttatchComObj(::IUnknown* pComObj)
{
    D2D1Resource::AttatchComObj(pComObj);
    pGeometry = (::ID2D1Geometry*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1Geometry::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1Geometry), Guid);
}

D2DRectF DirectXNet::Direct2D::D2D1Geometry::GetBounds(Nullable<D2DMatrix3X2F> worldTransform)
{
    ::D2D1_MATRIX_3X2_F* pTransform = __nullptr;
    if(worldTransform.HasValue)
        pTransform = (::D2D1_MATRIX_3X2_F*)&worldTransform.Value;

    D2DRectF bounds;
    Result::ThrowIfFailed(pGeometry->GetBounds(pTransform, (::D2D1_RECT_F*)&bounds));

    return bounds;
}

D2DRectF DirectXNet::Direct2D::D2D1Geometry::GetWidenedBounds(
    float strokeWidth, float flatteningTolerance,
    D2D1StrokeStyle^ strokeStyle, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1StrokeStyle* pStyle = __nullptr;

    try
    {
        if(strokeStyle != nullptr)
            pStyle = (::ID2D1StrokeStyle*)strokeStyle->GetNativeInterface();
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        D2DRectF bounds;
        Result::ThrowIfFailed(pGeometry->GetWidenedBounds(
            strokeWidth,
            pStyle,
            pTransform,
            flatteningTolerance,
            (::D2D1_RECT_F*)&bounds
        ));

        return bounds;
    }
    finally
    {
        SAFE_RELEASE(pStyle);
    }
}

bool DirectXNet::Direct2D::D2D1Geometry::StrokeContainsPoint(
    D2DPoint2F point, float strokeWidth, float flatteningTolerance,
    D2D1StrokeStyle^ strokeStyle, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1StrokeStyle* pStyle = __nullptr;

    try
    {
        if(strokeStyle != nullptr)
            pStyle = (::ID2D1StrokeStyle*)strokeStyle->GetNativeInterface();
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        BOOL contains;
        Result::ThrowIfFailed(pGeometry->StrokeContainsPoint(
            CAST_TO(point, ::D2D1_POINT_2F),
            strokeWidth,
            pStyle,
            pTransform,
            flatteningTolerance,
            &contains
        ));

        return !!contains;
    }
    finally
    {
        SAFE_RELEASE(pStyle);
    }
}

bool DirectXNet::Direct2D::D2D1Geometry::FillContainsPoint(
    D2DPoint2F point, float flatteningTolerance, Nullable<D2DMatrix3X2F> worldTransform)
{
    D2D1_MATRIX_3X2_F* pTransform = __nullptr;
    if(worldTransform.HasValue)
        pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

    BOOL contains;
    Result::ThrowIfFailed(pGeometry->FillContainsPoint(
        CAST_TO(point, ::D2D1_POINT_2F),
        pTransform,
        flatteningTolerance,
        &contains
    ));

    return !!contains;
}

D2D1GeometryRelation DirectXNet::Direct2D::D2D1Geometry::CompareWithGeometry(
    D2D1Geometry^ inputGeometry, float flatteningTolerance, Nullable<D2DMatrix3X2F> inputGeometryTransform)
{
    ::ID2D1Geometry* pInput = __nullptr;

    try
    {
        pInput = (::ID2D1Geometry*)inputGeometry->GetNativeInterface();

        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(inputGeometryTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&inputGeometryTransform.Value;

        D2D1GeometryRelation relation = D2D1GeometryRelation::Unknown;
        Result::ThrowIfFailed(pGeometry->CompareWithGeometry(
            pInput,
            pTransform,
            flatteningTolerance,
            (::D2D1_GEOMETRY_RELATION*)&relation
        ));

        return relation;
    }
    finally
    {
        SAFE_RELEASE(pInput);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Simplify(
    D2D1GeometrySimplificationOption simplificationOption, float flatteningTolerance,
    D2D1SimplifiedGeometrySink^ geometrySink, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = (::ID2D1SimplifiedGeometrySink*)geometrySink->GetNativeInterface();

        return Result(pGeometry->Simplify(
            (::D2D1_GEOMETRY_SIMPLIFICATION_OPTION)simplificationOption,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Simplify(
    D2D1GeometrySimplificationOption simplificationOption, float flatteningTolerance,
    D2D1CustomGeometrySink^ geometrySink, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = geometrySink->NativeSink;

        return Result(pGeometry->Simplify(
            (::D2D1_GEOMETRY_SIMPLIFICATION_OPTION)simplificationOption,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Tessellate(
    float flatteningTolerance, D2D1TessellationSink^ tessellationSink,
    Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1TessellationSink* pSink = __nullptr;

    try
    {
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = (::ID2D1TessellationSink*)tessellationSink->GetNativeInterface();

        return Result(pGeometry->Tessellate(
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::CombineWithGeometry(
    D2D1Geometry^ inputGeometry, D2D1CombineMode combineMode, float flatteningTolerance,
    D2D1SimplifiedGeometrySink^ geometrySink, Nullable<D2DMatrix3X2F> inputGeometryTransform)
{
    ::ID2D1Geometry* pInput = __nullptr;
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        pInput = (::ID2D1Geometry*)inputGeometry->GetNativeInterface();
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(inputGeometryTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&inputGeometryTransform.Value;

        pSink = (::ID2D1SimplifiedGeometrySink*)geometrySink->GetNativeInterface();

        return Result(pGeometry->CombineWithGeometry(
            pInput,
            (D2D1_COMBINE_MODE)combineMode,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pInput);
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::CombineWithGeometry(
    D2D1Geometry^ inputGeometry, D2D1CombineMode combineMode, float flatteningTolerance,
    D2D1CustomGeometrySink^ geometrySink, Nullable<D2DMatrix3X2F> inputGeometryTransform)
{
    ::ID2D1Geometry* pInput = __nullptr;
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        pInput = (::ID2D1Geometry*)inputGeometry->GetNativeInterface();
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(inputGeometryTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&inputGeometryTransform.Value;

        pSink = geometrySink->NativeSink;

        return Result(pGeometry->CombineWithGeometry(
            pInput,
            (D2D1_COMBINE_MODE)combineMode,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pInput);
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Outline(
    float flatteningTolerance, D2D1SimplifiedGeometrySink^ geometrySink,
    Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = (::ID2D1SimplifiedGeometrySink*)geometrySink->GetNativeInterface();

        return Result(pGeometry->Outline(
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Outline(
    float flatteningTolerance, D2D1CustomGeometrySink^ geometrySink, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = geometrySink->NativeSink;

        return Result(pGeometry->Outline(
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pSink);
    }
}

float DirectXNet::Direct2D::D2D1Geometry::ComputeArea(
    float flatteningTolerance, Nullable<D2DMatrix3X2F> worldTransform)
{
    D2D1_MATRIX_3X2_F* pTransform = __nullptr;
    if(worldTransform.HasValue)
        pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

    float area = 0;
    Result::ThrowIfFailed(pGeometry->ComputeArea(pTransform, flatteningTolerance, &area));

    return area;
}

float DirectXNet::Direct2D::D2D1Geometry::ComputeLength(
    float flatteningTolerance, Nullable<D2DMatrix3X2F> worldTransform)
{
    D2D1_MATRIX_3X2_F* pTransform = __nullptr;
    if(worldTransform.HasValue)
        pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

    float length = 0;
    Result::ThrowIfFailed(pGeometry->ComputeLength(pTransform, flatteningTolerance, &length));

    return length;
}

Result DirectXNet::Direct2D::D2D1Geometry::ComputePointAtLength(
    float length, float flatteningTolerance, D2DPoint2F% point, D2DPoint2F% unitTangentVector,
    Nullable<D2DMatrix3X2F> worldTransform)
{
    D2D1_MATRIX_3X2_F* pTransform = __nullptr;
    if(worldTransform.HasValue)
        pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

    pin_ptr<D2DPoint2F> pPoint = &point;
    pin_ptr<D2DPoint2F> pTangent = &unitTangentVector;

    return Result(pGeometry->ComputePointAtLength(
        length,
        pTransform,
        flatteningTolerance,
        (::D2D1_POINT_2F*)pPoint,
        (::D2D1_POINT_2F*)pTangent
    ));
}

Result DirectXNet::Direct2D::D2D1Geometry::Widen(
    float strokeWidth, float flatteningTolerance, D2D1SimplifiedGeometrySink^ geometrySink,
    D2D1StrokeStyle^ strokeStyle, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1StrokeStyle* pStyle = __nullptr;
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        if(strokeStyle != nullptr)
            pStyle = (::ID2D1StrokeStyle*)strokeStyle->GetNativeInterface();

        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = (::ID2D1SimplifiedGeometrySink*)geometrySink->GetNativeInterface();

        return Result(pGeometry->Widen(
            strokeWidth,
            pStyle,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pStyle);
        SAFE_RELEASE(pSink);
    }
}

Result DirectXNet::Direct2D::D2D1Geometry::Widen(
    float strokeWidth, float flatteningTolerance, D2D1CustomGeometrySink^ geometrySink,
    D2D1StrokeStyle^ strokeStyle, Nullable<D2DMatrix3X2F> worldTransform)
{
    ::ID2D1StrokeStyle* pStyle = __nullptr;
    ::ID2D1SimplifiedGeometrySink* pSink = __nullptr;

    try
    {
        if(strokeStyle != nullptr)
            pStyle = (::ID2D1StrokeStyle*)strokeStyle->GetNativeInterface();

        D2D1_MATRIX_3X2_F* pTransform = __nullptr;
        if(worldTransform.HasValue)
            pTransform = (D2D1_MATRIX_3X2_F*)&worldTransform.Value;

        pSink = geometrySink->NativeSink;

        return Result(pGeometry->Widen(
            strokeWidth,
            pStyle,
            pTransform,
            flatteningTolerance,
            pSink
        ));
    }
    finally
    {
        SAFE_RELEASE(pStyle);
        SAFE_RELEASE(pSink);
    }
}
