#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "D2D1Resource.h"
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
        ref class D2D1StrokeStyle;
        ref class D2D1SimplifiedGeometrySink;
        ref class D2D1CustomGeometrySink;
        ref class D2D1TessellationSink;

        /// <summary>
        /// Represents a geometry resource and defines a set of helper methods for manipulating and
        /// measuring geometric shapes.
        /// </summary>
        public ref class D2D1Geometry : D2D1Resource
        {
        private:
            ::ID2D1Geometry* pGeometry;

        internal:
            D2D1Geometry(::ID2D1Geometry* pGeometry);
            D2D1Geometry() : D2D1Resource() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1Geometry.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the bounds of the geometry.
            /// </summary>
            /// <param name="worldTransform">The transform to apply to this geometry before calculating
            /// its bounds, or null.</param>
            /// <returns>The bounds of this geometry. If the bounds are empty, this parameter will be a
            /// rect where left > right.</returns>
            D2DRectF GetBounds(
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Gets the bounds of the geometry after it has been widened by the specified stroke width and
            /// style and transformed by the specified matrix.
            /// </summary>
            /// <param name="strokeWidth">The amount by which to widen the geometry by stroking its outline.
            /// </param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="strokeStyle">The optional style of the stroke that widens the geometry.</param>
            /// <param name="worldTransform">A transform to apply to the geometry after the geometry is
            /// transformed and after the geometry has been stroked, or null.</param>
            /// <returns>The bounds of the widened geometry.</returns>
            D2DRectF GetWidenedBounds(
                float strokeWidth,
                float flatteningTolerance,
                [Optional] D2D1StrokeStyle^ strokeStyle,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Determines whether the geometry's stroke contains the specified point given the specified
            /// stroke thickness, style, and transform.
            /// </summary>
            /// <param name="point">The point to test for containment.</param>
            /// <param name="strokeWidth">The amount by which to widen the geometry by stroking its outline.
            /// </param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="strokeStyle">The optional style of the stroke that widens the geometry.</param>
            /// <param name="worldTransform">A transform to apply to the geometry after the geometry is
            /// transformed and after the geometry has been stroked, or null.</param>
            /// <returns>true if the geometry's stroke contains the specified point; otherwise, false.
            /// </returns>
            bool StrokeContainsPoint(
                D2DPoint2F point,
                float strokeWidth,
                float flatteningTolerance,
                [Optional] D2D1StrokeStyle^ strokeStyle,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Indicates whether the area filled by the geometry would contain the specified point given
            /// the specified flattening tolerance.
            /// </summary>
            /// <param name="point">The point to test.</param>
            /// <param name="flatteningTolerance">The numeric accuracy with which the precise geometric path
            /// and path intersection is calculated. Points missing the fill by less than the tolerance are
            /// still considered inside. Smaller values produce more accurate results but cause slower
            /// execution.</param>
            /// <param name="worldTransform">The transform to apply to the geometry prior to testing for
            /// containment, or null.</param>
            /// <returns>true if the area filled by the geometry contains point; otherwise, false.</returns>
            bool FillContainsPoint(
                D2DPoint2F point,
                float flatteningTolerance,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Describes the intersection between this geometry and the specified geometry. The comparison
            /// is performed by using the specified flattening tolerance.
            /// </summary>
            /// <param name="inputGeometry">The geometry to test.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="inputGeometryTransform">The transform to apply to inputGeometry, or null.</param>
            /// <returns>A value that describes how this geometry is related to inputGeometry.</returns>
            D2D1GeometryRelation CompareWithGeometry(
                D2D1Geometry^ inputGeometry,
                float flatteningTolerance,
                [Optional] Nullable<D2DMatrix3X2F> inputGeometryTransform
            );

            /// <summary>
            /// Creates a simplified version of the geometry that contains only lines and (optionally)
            /// cubic Bezier curves and writes the result to an D2D1SimplifiedGeometrySink.
            /// </summary>
            /// <param name="simplificationOption">A value that specifies whether the simplified geometry
            /// should contain curves.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="geometrySink">The D2D1SimplifiedGeometrySink to which the simplified geometry is
            /// appended.</param>
            /// <param name="worldTransform">The transform to apply to the simplified geometry, or null.
            /// </param>
            /// <returns>Result code.</returns>
            Result Simplify(
                D2D1GeometrySimplificationOption simplificationOption,
                float flatteningTolerance,
                D2D1SimplifiedGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Creates a simplified version of the geometry that contains only lines and (optionally)
            /// cubic Bezier curves and writes the result in a custom geometry sink.
            /// </summary>
            /// <param name="simplificationOption">A value that specifies whether the simplified geometry
            /// should contain curves.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="geometrySink">The implementation of D2D1CustomGeometrySink that receives the
            /// simplified geometry information.</param>
            /// <param name="worldTransform">The transform to apply to the simplified geometry, or null.
            /// </param>
            /// <returns>Result code.</returns>
            Result Simplify(
                D2D1GeometrySimplificationOption simplificationOption,
                float flatteningTolerance,
                D2D1CustomGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Creates a set of clockwise-wound triangles that cover the geometry after it has been
            /// transformed using the specified matrix and flattened using the specified tolerance.
            /// </summary>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="tessellationSink">The D2D1TessellationSink to which the tessellated is
            /// appended.</param>
            /// <param name="worldTransform">The transform to apply to this geometry, or null.</param>
            /// <returns>Result code.</returns>
            Result Tessellate(
                float flatteningTolerance,
                D2D1TessellationSink^ tessellationSink,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Combines this geometry with the specified geometry and stores the result in an
            /// D2D1SimplifiedGeometrySink.
            /// </summary>
            /// <param name="inputGeometry">The geometry to combine with this instance.</param>
            /// <param name="combineMode">The type of combine operation to perform.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="geometrySink">The result of the combine operation.</param>
            /// <param name="inputGeometryTransform">The transform to apply to inputGeometry before
            /// combining, or null.</param>
            /// <returns>Result code.</returns>
            Result CombineWithGeometry(
                D2D1Geometry^ inputGeometry,
                D2D1CombineMode combineMode,
                float flatteningTolerance,
                D2D1SimplifiedGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> inputGeometryTransform
            );

            /// <summary>
            /// Combines this geometry with the specified geometry and stores the result in custom geometry
            /// sink.
            /// </summary>
            /// <param name="inputGeometry">The geometry to combine with this instance.</param>
            /// <param name="combineMode">The type of combine operation to perform.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="geometrySink">The result of the combine operation.</param>
            /// <param name="inputGeometryTransform">The transform to apply to inputGeometry before
            /// combining, or null.</param>
            /// <returns>Result code.</returns>
            Result CombineWithGeometry(
                D2D1Geometry^ inputGeometry,
                D2D1CombineMode combineMode,
                float flatteningTolerance,
                D2D1CustomGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> inputGeometryTransform
            );

            /// <summary>
            /// Computes the outline of the geometry and writes the result to an D2D1SimplifiedGeometrySink.
            /// </summary>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="geometrySink">The D2D1SimplifiedGeometrySink to which the geometry's transformed
            /// outline is appended.</param>
            /// <param name="worldTransform">The transform to apply to the geometry outline, or null.</param>
            /// <returns>Result code.</returns>
            Result Outline(
                float flatteningTolerance,
                D2D1SimplifiedGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Computes the outline of the geometry and writes the result to custom sink.
            /// </summary>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="geometrySink">The custom sink to which the geometry's transformed
            /// outline is appended.</param>
            /// <param name="worldTransform">The transform to apply to the geometry outline, or null.</param>
            /// <returns>Result code.</returns>
            Result Outline(
                float flatteningTolerance,
                D2D1CustomGeometrySink^ geometrySink,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Computes the area of the geometry after it has been transformed by the specified matrix and
            /// flattened using the specified tolerance.
            /// </summary>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="worldTransform">The transform to apply to this geometry before computing its
            /// area, or null.</param>
            /// <returns>Area of the geometry.</returns>
            float ComputeArea(
                float flatteningTolerance,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Calculates the length of the geometry as though each segment were unrolled into a line.
            /// </summary>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="worldTransform">The transform to apply to this geometry before computing its
            /// length, or null.</param>
            /// <returns>Length of the geometry.</returns>
            float ComputeLength(
                float flatteningTolerance,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Calculates the point and tangent vector at the specified distance along the geometry after
            /// it has been transformed by the specified matrix and flattened using the specified tolerance.
            /// </summary>
            /// <param name="length">The distance along the geometry of the point and tangent to find. If
            /// this distance is less than 0, this method calculates the first point in the geometry. If this
            /// distance is greater than the length of the geometry, this method calculates the last point
            /// in the geometry.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from the
            /// original geometry by more than the flattening tolerance. Smaller values produce more accurate
            /// results but cause slower execution.</param>
            /// <param name="point">The location at the specified distance along the geometry. If the
            /// geometry is empty, this point contains NaN as its x and y values.</param>
            /// <param name="unitTangentVector">When this method returns, contains a pointer to the tangent
            /// vector at the specified distance along the geometry. If the geometry is empty, this vector
            /// contains NaN as its x and y values.</param>
            /// <param name="worldTransform">The transform to apply to the geometry before calculating the
            /// specified point and tangent, or null.</param>
            /// <returns>Result code.</returns>
            Result ComputePointAtLength(
                float length,
                float flatteningTolerance,
                [Out] D2DPoint2F% point,
                [Out] D2DPoint2F% unitTangentVector,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Widens the geometry by the specified stroke and writes the result to an
            /// D2D1SimplifiedGeometrySink after it has been transformed by the specified matrix and
            /// flattened using the specified tolerance.
            /// </summary>
            /// <param name="strokeWidth">The amount by which to widen the geometry.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="geometrySink">The D2D1SimplifiedGeometrySink to which the widened geometry is
            /// appended.</param>
            /// <param name="strokeStyle">The style of stroke to apply to the geometry, or null.</param>
            /// <param name="worldTransform">The transform to apply to the geometry after widening it, or
            /// null.</param>
            /// <returns>Result code.</returns>
            Result Widen(
                float strokeWidth,
                float flatteningTolerance,
                D2D1SimplifiedGeometrySink^ geometrySink,
                [Optional] D2D1StrokeStyle^ strokeStyle,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );

            /// <summary>
            /// Widens the geometry by the specified stroke and writes the result to an
            /// custom sink after it has been transformed by the specified matrix and
            /// flattened using the specified tolerance.
            /// </summary>
            /// <param name="strokeWidth">The amount by which to widen the geometry.</param>
            /// <param name="flatteningTolerance">The maximum error allowed when constructing a polygonal
            /// approximation of the geometry. No point in the polygonal representation will diverge from
            /// the original geometry by more than the flattening tolerance. Smaller values produce more
            /// accurate results but cause slower execution.</param>
            /// <param name="geometrySink">The custom sink to which the widened geometry is
            /// appended.</param>
            /// <param name="strokeStyle">The style of stroke to apply to the geometry, or null.</param>
            /// <param name="worldTransform">The transform to apply to the geometry after widening it, or
            /// null.</param>
            /// <returns>Result code.</returns>
            Result Widen(
                float strokeWidth,
                float flatteningTolerance,
                D2D1CustomGeometrySink^ geometrySink,
                [Optional] D2D1StrokeStyle^ strokeStyle,
                [Optional] Nullable<D2DMatrix3X2F> worldTransform
            );
        };
    }
}
