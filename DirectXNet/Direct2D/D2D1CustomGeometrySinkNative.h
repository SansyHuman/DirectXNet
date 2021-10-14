#pragma once

#include "../pch.h"
#include "../Common/CommonD2DStructs.h"
#include "../Common/Result.h"
#include "D2D1Structs.h"

namespace DirectXNet
{
    namespace Direct2D
    {
        ref class D2D1CustomGeometrySink;

        struct D2D1CustomGeometrySinkNative : public ::ID2D1GeometrySink
        {
        private:
            ULONG m_cRef;
            msclr::gcroot<D2D1CustomGeometrySink^> m_managedSink;

        public:
            D2D1CustomGeometrySinkNative(D2D1CustomGeometrySink^ managedSink);

            virtual HRESULT __stdcall QueryInterface(
                REFIID riid,
                void** ppvObject
            ) override;

            virtual ULONG __stdcall AddRef() override;

            virtual ULONG __stdcall Release() override;

            STDMETHOD_(void, SetFillMode)(
                D2D1_FILL_MODE fillMode
                ) override;

            STDMETHOD_(void, SetSegmentFlags)(
                D2D1_PATH_SEGMENT vertexFlags
                ) override;

            STDMETHOD_(void, BeginFigure)(
                D2D1_POINT_2F startPoint,
                D2D1_FIGURE_BEGIN figureBegin
                ) override;

            STDMETHOD_(void, AddLines)(
                _In_reads_(pointsCount) CONST D2D1_POINT_2F* points,
                UINT32 pointsCount
                ) override;

            STDMETHOD_(void, AddBeziers)(
                _In_reads_(beziersCount) CONST D2D1_BEZIER_SEGMENT* beziers,
                UINT32 beziersCount
                ) override;

            STDMETHOD_(void, EndFigure)(
                D2D1_FIGURE_END figureEnd
                ) override;

            STDMETHOD(Close)(
                ) override;

            STDMETHOD_(void, AddLine)(
                D2D1_POINT_2F point
                ) override;

            STDMETHOD_(void, AddBezier)(
                _In_ CONST D2D1_BEZIER_SEGMENT* bezier
                ) override;

            STDMETHOD_(void, AddQuadraticBezier)(
                _In_ CONST D2D1_QUADRATIC_BEZIER_SEGMENT* bezier
                ) override;

            STDMETHOD_(void, AddQuadraticBeziers)(
                _In_reads_(beziersCount) CONST D2D1_QUADRATIC_BEZIER_SEGMENT* beziers,
                UINT32 beziersCount
                ) override;

            STDMETHOD_(void, AddArc)(
                _In_ CONST D2D1_ARC_SEGMENT* arc
                ) override;
        };
    }
}