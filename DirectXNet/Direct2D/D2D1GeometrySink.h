#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "D2D1SimplifiedGeometrySink.h"
#include "D2D1Structs.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Common;

// Done.

namespace DirectXNet
{
    namespace Direct2D
    {
        /// <summary>
        /// Describes a geometric path that can contain lines, arcs, cubic Bezier curves, and quadratic
        /// Bezier curves.
        /// </summary>
        public ref class D2D1GeometrySink : D2D1SimplifiedGeometrySink
        {
        private:
            ::ID2D1GeometrySink* pSink;

        internal:
            D2D1GeometrySink(::ID2D1GeometrySink* pSink);
            D2D1GeometrySink() : D2D1SimplifiedGeometrySink() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1GeometrySink.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Creates a line segment between the current point and the specified end point and adds it to
            /// the geometry sink.
            /// </summary>
            /// <param name="point">The end point of the line to draw.</param>
            void AddLine(D2DPoint2F point);

            /// <summary>
            /// Creates a cubic Bezier curve between the current point and the specified end point.
            /// </summary>
            /// <param name="bezier">A structure that describes the control points and end point of the
            /// Bezier curve to add.</param>
            void AddBezier(
                [In][IsReadOnly] D2D1BezierSegment% bezier
            );

            /// <summary>
            /// Creates a quadratic Bezier curve between the current point and the specified end point.
            /// </summary>
            /// <param name="bezier">A structure that describes the control point and the end point of the
            /// quadratic Bezier curve to add.</param>
            void AddQuadraticBezier(
                [In][IsReadOnly] D2D1QuadraticBezierSegment% bezier
            );

            /// <summary>
            /// Adds a sequence of quadratic Bezier segments as an array in a single call.
            /// </summary>
            /// <param name="beziers">An array of a sequence of quadratic Bezier segments.</param>
            void AddQuadraticBeziers(
                ...array<D2D1QuadraticBezierSegment>^ beziers
            );

            /// <summary>
            /// Adds a single arc to the path geometry.
            /// </summary>
            /// <param name="arc">The arc segment to add to the figure.</param>
            void AddArc(
                [In][IsReadOnly] D2D1ArcSegment% arc
            );
        };
    }
}
