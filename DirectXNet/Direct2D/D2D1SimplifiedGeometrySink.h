#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "../Common/Unknown.h"
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
        /// Describes a geometric path that does not contain quadratic bezier curves or arcs.
        /// </summary>
        public ref class D2D1SimplifiedGeometrySink : Common::Unknown
        {
        private:
            ::ID2D1SimplifiedGeometrySink* pSimpl;

        internal:
            D2D1SimplifiedGeometrySink(::ID2D1SimplifiedGeometrySink* pSimpl);
            D2D1SimplifiedGeometrySink() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1SimplifiedGeometrySink.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Specifies the method used to determine which points are inside the geometry described by
            /// this geometry sink and which points are outside.
            /// </summary>
            property D2D1FillMode FillMode
            {
                void set(D2D1FillMode mode);
            }

            /// <summary>
            /// Specifies stroke and join options to be applied to new segments added to the geometry sink.
            /// </summary>
            property D2D1PathSegment SegmentFlags
            {
                void set(D2D1PathSegment flags);
            }

            /// <summary>
            /// Starts a new figure at the specified point.
            /// </summary>
            /// <param name="startPoint">The point at which to begin the new figure.</param>
            /// <param name="figureBegin">Whether the new figure should be hollow or filled.</param>
            void BeginFigure(D2DPoint2F startPoint, D2D1FigureBegin figureBegin);

            /// <summary>
            /// Creates a sequence of lines using the specified points and adds them to the geometry sink.
            /// </summary>
            /// <param name="points">An array of one or more points that describe the lines to draw. A line
            /// is drawn from the geometry sink's current point (the end point of the last segment drawn or
            /// the location specified by BeginFigure) to the first point in the array. if the array contains
            /// additional points, a line is drawn from the first point to the second point in the array,
            /// from the second point to the third point, and so on.</param>
            void AddLines(...array<D2DPoint2F>^ points);

            /// <summary>
            /// Creates a sequence of cubic Bezier curves and adds them to the geometry sink.
            /// </summary>
            /// <param name="beziers">An array of Bezier segments that describes the Bezier curves to create.
            /// A curve is drawn from the geometry sink's current point (the end point of the last segment
            /// drawn or the location specified by BeginFigure) to the end point of the first Bezier segment
            /// in the array. if the array contains additional Bezier segments, each subsequent Bezier
            /// segment uses the end point of the preceding Bezier segment as its start point.</param>
            void AddBeziers(...array<D2D1BezierSegment>^ beziers);

            /// <summary>
            /// Ends the current figure; optionally, closes it.
            /// </summary>
            /// <param name="figureEnd">A value that indicates whether the current figure is closed. If the
            /// figure is closed, a line is drawn between the current point and the start point specified by
            /// BeginFigure.</param>
            void EndFigure(D2D1FigureEnd figureEnd);

            /// <summary>
            /// Closes the geometry sink, indicates whether it is in an error state, and resets the sink's
            /// error state.
            /// </summary>
            /// <returns>Result code.</returns>
            Result Close();
        };
    }
}
