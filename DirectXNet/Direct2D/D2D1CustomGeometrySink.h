#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
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
        struct D2D1CustomGeometrySinkNative;

        /// <summary>
        /// A custom geometry sink that can receive geometry data with D2D1PathGeometry::Stream.
        /// </summary>
        public ref class D2D1CustomGeometrySink abstract
        {
        private:
            D2D1CustomGeometrySinkNative* pCustomSink;

        internal:
            /// <summary>
            /// Gets the native pointer of the sink. Adds reference count to the sink.
            /// </summary>
            property D2D1CustomGeometrySinkNative* NativeSink
            {
                D2D1CustomGeometrySinkNative* get();
            }

        public:
            D2D1CustomGeometrySink();
            ~D2D1CustomGeometrySink();
            !D2D1CustomGeometrySink();

            /// <summary>
            /// Specifies the method used to determine which points are inside the geometry described by
            /// this geometry sink and which points are outside.
            /// </summary>
            virtual property D2D1FillMode FillMode
            {
                virtual void set(D2D1FillMode mode) abstract;
            }

            /// <summary>
            /// Specifies stroke and join options to be applied to new segments added to the geometry sink.
            /// </summary>
            virtual property D2D1PathSegment SegmentFlags
            {
                void set(D2D1PathSegment flags) abstract;
            }

            /// <summary>
            /// Starts a new figure at the specified point.
            /// </summary>
            /// <param name="startPoint">The point at which to begin the new figure.</param>
            /// <param name="figureBegin">Whether the new figure should be hollow or filled.</param>
            virtual void BeginFigure(D2DPoint2F startPoint, D2D1FigureBegin figureBegin) abstract;

            /// <summary>
            /// Creates a sequence of lines using the specified points and adds them to the geometry sink.
            /// </summary>
            /// <param name="points">An array of one or more points that describe the lines to draw. A line
            /// is drawn from the geometry sink's current point (the end point of the last segment drawn or
            /// the location specified by BeginFigure) to the first point in the array. if the array contains
            /// additional points, a line is drawn from the first point to the second point in the array,
            /// from the second point to the third point, and so on.</param>
            /// <param name="pointsCount">The number of points in the array.</param>
            virtual void AddLines(D2DPoint2F* points, unsigned int pointsCount) abstract;

            /// <summary>
            /// Creates a sequence of cubic Bezier curves and adds them to the geometry sink.
            /// </summary>
            /// <param name="beziers">An array of Bezier segments that describes the Bezier curves to create.
            /// A curve is drawn from the geometry sink's current point (the end point of the last segment
            /// drawn or the location specified by BeginFigure) to the end point of the first Bezier segment
            /// in the array. if the array contains additional Bezier segments, each subsequent Bezier
            /// segment uses the end point of the preceding Bezier segment as its start point.</param>
            /// <param name="beziersCount">The number of segments in the array.</param>
            virtual void AddBeziers(D2D1BezierSegment* beziers, unsigned int beziersCount) abstract;

            /// <summary>
            /// Ends the current figure; optionally, closes it.
            /// </summary>
            /// <param name="figureEnd">A value that indicates whether the current figure is closed. If the
            /// figure is closed, a line is drawn between the current point and the start point specified by
            /// BeginFigure.</param>
            virtual void EndFigure(D2D1FigureEnd figureEnd) abstract;

            /// <summary>
            /// Closes the geometry sink, indicates whether it is in an error state, and resets the sink's
            /// error state.
            /// </summary>
            /// <returns>Result code.</returns>
            virtual Result Close() abstract;

            /// <summary>
            /// Creates a line segment between the current point and the specified end point and adds it to
            /// the geometry sink.
            /// </summary>
            /// <param name="point">The end point of the line to draw.</param>
            virtual void AddLine(D2DPoint2F point) abstract;

            /// <summary>
            /// Creates a cubic Bezier curve between the current point and the specified end point.
            /// </summary>
            /// <param name="bezier">A structure that describes the control points and end point of the
            /// Bezier curve to add.</param>
            virtual void AddBezier(
                [In][IsReadOnly] D2D1BezierSegment% bezier
            ) abstract;

            /// <summary>
            /// Creates a quadratic Bezier curve between the current point and the specified end point.
            /// </summary>
            /// <param name="bezier">A structure that describes the control point and the end point of the
            /// quadratic Bezier curve to add.</param>
            virtual void AddQuadraticBezier(
                [In][IsReadOnly] D2D1QuadraticBezierSegment% bezier
            ) abstract;

            /// <summary>
            /// Adds a sequence of quadratic Bezier segments as an array in a single call.
            /// </summary>
            /// <param name="beziers">An array of a sequence of quadratic Bezier segments.</param>
            /// <param name="beziersCount">The number of segments in the array.</param>
            virtual void AddQuadraticBeziers(
                D2D1QuadraticBezierSegment* beziers, unsigned int beziersCount
            ) abstract;

            /// <summary>
            /// Adds a single arc to the path geometry.
            /// </summary>
            /// <param name="arc">The arc segment to add to the figure.</param>
            virtual void AddArc(
                [In][IsReadOnly] D2D1ArcSegment% arc
            ) abstract;
        };
    }
}
