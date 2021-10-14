#include "D2D1CustomGeometrySinkNative.h"
#include "D2D1CustomGeometrySink.h"

using namespace DirectXNet::Direct2D;
using namespace DirectXNet::Common::D2D;

DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::D2D1CustomGeometrySinkNative(
    D2D1CustomGeometrySink^ managedSink)
    : m_cRef(1), m_managedSink(managedSink)
{
    
}

HRESULT __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::QueryInterface(
    REFIID riid, void** ppvObject)
{
    if(!ppvObject)
        return E_INVALIDARG;

    *ppvObject = __nullptr;
    if(riid == IID_IUnknown || riid == IID_ID2D1SimplifiedGeometrySink ||
       riid == IID_ID2D1GeometrySink)
    {
        // Increment the reference count and return the pointer.
        *ppvObject = (LPVOID)this;
        AddRef();
        return NOERROR;
    }
    return E_NOINTERFACE;
}

ULONG __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddRef()
{
    InterlockedIncrement((volatile ULONG*)&m_cRef);
    return m_cRef;
}

ULONG __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::Release()
{
    ULONG ulRefCount = InterlockedDecrement((volatile ULONG*)&m_cRef);
    if(0 == ulRefCount)
    {
        delete this;
    }
    return ulRefCount;
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::SetFillMode(D2D1_FILL_MODE fillMode)
{
    m_managedSink->FillMode = (D2D1FillMode)fillMode;
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::SetSegmentFlags(
    D2D1_PATH_SEGMENT vertexFlags)
{
    m_managedSink->SegmentFlags = (D2D1PathSegment)vertexFlags;
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::BeginFigure(D2D1_POINT_2F startPoint, D2D1_FIGURE_BEGIN figureBegin)
{
    m_managedSink->BeginFigure(CAST_TO(startPoint, D2DPoint2F), (D2D1FigureBegin)figureBegin);
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddLines(
    const D2D1_POINT_2F* points, UINT32 pointsCount)
{
    m_managedSink->AddLines(
        (D2DPoint2F*)(const_cast<::D2D1_POINT_2F*>(points)), pointsCount
    );
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddBeziers(
    const D2D1_BEZIER_SEGMENT* beziers, UINT32 beziersCount)
{
    m_managedSink->AddBeziers(
        (D2D1BezierSegment*)(const_cast<::D2D1_BEZIER_SEGMENT*>(beziers)), beziersCount
    );
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::EndFigure(D2D1_FIGURE_END figureEnd)
{
    m_managedSink->EndFigure((D2D1FigureEnd)figureEnd);
}

HRESULT __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::Close()
{
    return m_managedSink->Close().result;
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddLine(D2D1_POINT_2F point)
{
    m_managedSink->AddLine(CAST_TO(point, D2DPoint2F));
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddBezier(const D2D1_BEZIER_SEGMENT* bezier)
{
    m_managedSink->AddBezier(*((D2D1BezierSegment*)const_cast<::D2D1_BEZIER_SEGMENT*>(bezier)));
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddQuadraticBezier(
    const D2D1_QUADRATIC_BEZIER_SEGMENT* bezier)
{
    m_managedSink->AddQuadraticBezier(
        *((D2D1QuadraticBezierSegment*)const_cast<::D2D1_QUADRATIC_BEZIER_SEGMENT*>(bezier)));
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddQuadraticBeziers(
    const D2D1_QUADRATIC_BEZIER_SEGMENT* beziers, UINT32 beziersCount)
{
    m_managedSink->AddQuadraticBeziers(
        (D2D1QuadraticBezierSegment*)const_cast<::D2D1_QUADRATIC_BEZIER_SEGMENT*>(beziers),
        beziersCount
    );
}

void __stdcall DirectXNet::Direct2D::D2D1CustomGeometrySinkNative::AddArc(const D2D1_ARC_SEGMENT* arc)
{
    m_managedSink->AddArc(*((D2D1ArcSegment*)const_cast<::D2D1_ARC_SEGMENT*>(arc)));
}
