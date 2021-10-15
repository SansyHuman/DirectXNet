#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common::D2D;

namespace DirectXNet
{
    namespace Direct2D
    {
        /// <summary>
        /// Pre-defined colors.
        /// </summary>
        public enum class D2DColor : UINT
        {
            AliceBlue = 0xF0F8FF,
            AntiqueWhite = 0xFAEBD7,
            Aqua = 0x00FFFF,
            Aquamarine = 0x7FFFD4,
            Azure = 0xF0FFFF,
            Beige = 0xF5F5DC,
            Bisque = 0xFFE4C4,
            Black = 0x000000,
            BlanchedAlmond = 0xFFEBCD,
            Blue = 0x0000FF,
            BlueViolet = 0x8A2BE2,
            Brown = 0xA52A2A,
            BurlyWood = 0xDEB887,
            CadetBlue = 0x5F9EA0,
            Chartreuse = 0x7FFF00,
            Chocolate = 0xD2691E,
            Coral = 0xFF7F50,
            CornflowerBlue = 0x6495ED,
            Cornsilk = 0xFFF8DC,
            Crimson = 0xDC143C,
            Cyan = 0x00FFFF,
            DarkBlue = 0x00008B,
            DarkCyan = 0x008B8B,
            DarkGoldenrod = 0xB8860B,
            DarkGray = 0xA9A9A9,
            DarkGreen = 0x006400,
            DarkKhaki = 0xBDB76B,
            DarkMagenta = 0x8B008B,
            DarkOliveGreen = 0x556B2F,
            DarkOrange = 0xFF8C00,
            DarkOrchid = 0x9932CC,
            DarkRed = 0x8B0000,
            DarkSalmon = 0xE9967A,
            DarkSeaGreen = 0x8FBC8F,
            DarkSlateBlue = 0x483D8B,
            DarkSlateGray = 0x2F4F4F,
            DarkTurquoise = 0x00CED1,
            DarkViolet = 0x9400D3,
            DeepPink = 0xFF1493,
            DeepSkyBlue = 0x00BFFF,
            DimGray = 0x696969,
            DodgerBlue = 0x1E90FF,
            Firebrick = 0xB22222,
            FloralWhite = 0xFFFAF0,
            ForestGreen = 0x228B22,
            Fuchsia = 0xFF00FF,
            Gainsboro = 0xDCDCDC,
            GhostWhite = 0xF8F8FF,
            Gold = 0xFFD700,
            Goldenrod = 0xDAA520,
            Gray = 0x808080,
            Green = 0x008000,
            GreenYellow = 0xADFF2F,
            Honeydew = 0xF0FFF0,
            HotPink = 0xFF69B4,
            IndianRed = 0xCD5C5C,
            Indigo = 0x4B0082,
            Ivory = 0xFFFFF0,
            Khaki = 0xF0E68C,
            Lavender = 0xE6E6FA,
            LavenderBlush = 0xFFF0F5,
            LawnGreen = 0x7CFC00,
            LemonChiffon = 0xFFFACD,
            LightBlue = 0xADD8E6,
            LightCoral = 0xF08080,
            LightCyan = 0xE0FFFF,
            LightGoldenrodYellow = 0xFAFAD2,
            LightGreen = 0x90EE90,
            LightGray = 0xD3D3D3,
            LightPink = 0xFFB6C1,
            LightSalmon = 0xFFA07A,
            LightSeaGreen = 0x20B2AA,
            LightSkyBlue = 0x87CEFA,
            LightSlateGray = 0x778899,
            LightSteelBlue = 0xB0C4DE,
            LightYellow = 0xFFFFE0,
            Lime = 0x00FF00,
            LimeGreen = 0x32CD32,
            Linen = 0xFAF0E6,
            Magenta = 0xFF00FF,
            Maroon = 0x800000,
            MediumAquamarine = 0x66CDAA,
            MediumBlue = 0x0000CD,
            MediumOrchid = 0xBA55D3,
            MediumPurple = 0x9370DB,
            MediumSeaGreen = 0x3CB371,
            MediumSlateBlue = 0x7B68EE,
            MediumSpringGreen = 0x00FA9A,
            MediumTurquoise = 0x48D1CC,
            MediumVioletRed = 0xC71585,
            MidnightBlue = 0x191970,
            MintCream = 0xF5FFFA,
            MistyRose = 0xFFE4E1,
            Moccasin = 0xFFE4B5,
            NavajoWhite = 0xFFDEAD,
            Navy = 0x000080,
            OldLace = 0xFDF5E6,
            Olive = 0x808000,
            OliveDrab = 0x6B8E23,
            Orange = 0xFFA500,
            OrangeRed = 0xFF4500,
            Orchid = 0xDA70D6,
            PaleGoldenrod = 0xEEE8AA,
            PaleGreen = 0x98FB98,
            PaleTurquoise = 0xAFEEEE,
            PaleVioletRed = 0xDB7093,
            PapayaWhip = 0xFFEFD5,
            PeachPuff = 0xFFDAB9,
            Peru = 0xCD853F,
            Pink = 0xFFC0CB,
            Plum = 0xDDA0DD,
            PowderBlue = 0xB0E0E6,
            Purple = 0x800080,
            Red = 0xFF0000,
            RosyBrown = 0xBC8F8F,
            RoyalBlue = 0x4169E1,
            SaddleBrown = 0x8B4513,
            Salmon = 0xFA8072,
            SandyBrown = 0xF4A460,
            SeaGreen = 0x2E8B57,
            SeaShell = 0xFFF5EE,
            Sienna = 0xA0522D,
            Silver = 0xC0C0C0,
            SkyBlue = 0x87CEEB,
            SlateBlue = 0x6A5ACD,
            SlateGray = 0x708090,
            Snow = 0xFFFAFA,
            SpringGreen = 0x00FF7F,
            SteelBlue = 0x4682B4,
            Tan = 0xD2B48C,
            Teal = 0x008080,
            Thistle = 0xD8BFD8,
            Tomato = 0xFF6347,
            Turquoise = 0x40E0D0,
            Violet = 0xEE82EE,
            Wheat = 0xF5DEB3,
            White = 0xFFFFFF,
            WhiteSmoke = 0xF5F5F5,
            Yellow = 0xFFFF00,
            YellowGreen = 0x9ACD32,
        };

        /// <summary>
        /// Describes the shape at the end of a line or segment.
        /// </summary>
        public enum class D2D1CapStyle : UINT
        {
            /// <summary>
            /// A cap that does not extend past the last point of the line. Comparable to cap used for
            /// objects other than lines.
            /// </summary>
            Flat = D2D1_CAP_STYLE_FLAT,

            /// <summary>
            /// Half of a square that has a length equal to the line thickness.
            /// </summary>
            Square = D2D1_CAP_STYLE_SQUARE,

            /// <summary>
            /// A semicircle that has a diameter equal to the line thickness.
            /// </summary>
            Round = D2D1_CAP_STYLE_ROUND,

            /// <summary>
            /// An isosceles right triangle whose hypotenuse is equal in length to the thickness of
            /// the line.
            /// </summary>
            Triangle = D2D1_CAP_STYLE_TRIANGLE
        };

        /// <summary>
        /// Describes the sequence of dashes and gaps in a stroke.
        /// </summary>
        public enum class D2D1DashStyle : UINT
        {
            /// <summary>
            /// A solid line with no breaks.
            /// </summary>
            Solid = D2D1_DASH_STYLE_SOLID,

            /// <summary>
            /// A dash followed by a gap of equal length. The dash and the gap are each twice as long
            /// as the stroke thickness.
            /// </summary>
            Dash = D2D1_DASH_STYLE_DASH,

            /// <summary>
            /// A dot followed by a longer gap.
            /// </summary>
            Dot = D2D1_DASH_STYLE_DOT,

            /// <summary>
            /// A dash, followed by a gap, followed by a dot, followed by another gap.
            /// </summary>
            DashDot = D2D1_DASH_STYLE_DASH_DOT,

            /// <summary>
            /// A dash, followed by a gap, followed by a dot, followed by another gap, followed by
            /// another dot, followed by another gap.
            /// </summary>
            DashDotDot = D2D1_DASH_STYLE_DASH_DOT_DOT,

            /// <summary>
            /// The dash pattern is specified by an array of floating-point values.
            /// </summary>
            Custom = D2D1_DASH_STYLE_CUSTOM
        };

        /// <summary>
        /// Describes the shape that joins two lines or segments.
        /// </summary>
        public enum class D2D1LineJoin : UINT
        {
            /// <summary>
            /// Regular angular vertices.
            /// </summary>
            Miter = D2D1_LINE_JOIN_MITER,

            /// <summary>
            /// Beveled vertices.
            /// </summary>
            Bevel = D2D1_LINE_JOIN_BEVEL,

            /// <summary>
            /// Rounded vertices.
            /// </summary>
            Round = D2D1_LINE_JOIN_ROUND,

            /// <summary>
            /// Regular angular vertices unless the join would extend beyond the miter limit;
            /// otherwise, beveled vertices.
            /// </summary>
            MiterOrBevel = D2D1_LINE_JOIN_MITER_OR_BEVEL
        };

        /// <summary>
        /// Describes how one geometry object is spatially related to another geometry object.
        /// </summary>
        public enum class D2D1GeometryRelation : UINT
        {
            /// <summary>
            /// The relationship between the two geometries cannot be determined. This value is never
            /// returned by any D2D method.
            /// </summary>
            Unknown = D2D1_GEOMETRY_RELATION_UNKNOWN,

            /// <summary>
            /// The two geometries do not intersect at all.
            /// </summary>
            Disjoint = D2D1_GEOMETRY_RELATION_DISJOINT,

            /// <summary>
            /// The instance geometry is entirely contained by the passed-in geometry.
            /// </summary>
            IsContained = D2D1_GEOMETRY_RELATION_IS_CONTAINED,

            /// <summary>
            /// The instance geometry entirely contains the passed-in geometry.
            /// </summary>
            Contains = D2D1_GEOMETRY_RELATION_CONTAINS,

            /// <summary>
            /// The two geometries overlap but neither completely contains the other.
            /// </summary>
            Overlap = D2D1_GEOMETRY_RELATION_OVERLAP
        };

        /// <summary>
        /// Specifies how the intersecting areas of geometries or figures are combined to form the area
        /// of the composite geometry.
        /// </summary>
        public enum class D2D1FillMode : UINT
        {
            /// <summary>
            /// Determines whether a point is in the fill region by drawing a ray from that point to
            /// infinity in any direction, and then counting the number of path segments within the given
            /// shape that the ray crosses. If this number is odd, the point is in the fill region; if
            /// even, the point is outside the fill region.
            /// </summary>
            Alternate = D2D1_FILL_MODE_ALTERNATE,

            /// <summary>
            /// Determines whether a point is in the fill region of the path by drawing a ray from that
            /// point to infinity in any direction, and then examining the places where a segment of the
            /// shape crosses the ray. Starting with a count of zero, add one each time a segment crosses
            /// the ray from left to right and subtract one each time a path segment crosses the ray from
            /// right to left, as long as left and right are seen from the perspective of the ray. After
            /// counting the crossings, if the result is zero, then the point is outside the path.
            /// Otherwise, it is inside the path.
            /// </summary>
            Winding = D2D1_FILL_MODE_WINDING
        };

        /// <summary>
        /// Indicates whether a segment should be stroked and whether the join between this segment and
        /// the previous one should be smooth. This enumeration allows a bitwise combination of its
        /// member values.
        /// </summary>
        [Flags]
        public enum class D2D1PathSegment : UINT
        {
            /// <summary>
            /// The segment is joined as specified by the D2D1StrokeStyle interface, and it is stroked.
            /// </summary>
            None = D2D1_PATH_SEGMENT_NONE,

            /// <summary>
            /// The segment is not stroked.
            /// </summary>
            ForceUnstroked = D2D1_PATH_SEGMENT_FORCE_UNSTROKED,

            /// <summary>
            /// The segment is always joined with the one preceding it using a round line join,
            /// regardless of which D2D1LineJoin enumeration is specified by the D2D1StrokeStyle
            /// class. If this segment is the first segment and the figure is closed, a round line join
            /// is used to connect the closing segment with the first segment. If the figure is not
            /// closed, this setting has no effect on the first segment of the figure. If
            /// D2D1SimplifiedGeometrySink::SegmentFlags is called just before
            /// D2D1SimplifiedGeometrySink::EndFigure, the join between the closing segment and the last
            /// explicitly specified segment is affected.
            /// </summary>
            ForceRoundLineJoin = D2D1_PATH_SEGMENT_FORCE_ROUND_LINE_JOIN
        };

        /// <summary>
        /// Indicates whether a specific D2D1SimplifiedGeometrySink figure is filled or hollow.
        /// </summary>
        public enum class D2D1FigureBegin : UINT
        {
            /// <summary>
            /// Indicates the figure will be filled by the FillGeometry (D2D1CommandSink::FillGeometry
            /// or D2D1RenderTarget::FillGeometry) method.
            /// </summary>
            Filled = D2D1_FIGURE_BEGIN_FILLED,

            /// <summary>
            /// Indicates the figure will not be filled by the FillGeometry (D2D1CommandSink::FillGeometry
            /// or D2D1RenderTarget::FillGeometry) methodand will only consist of an outline. Moreover,
            /// the bounds of a hollow figure are zero. Hollow should be used for stroking, or for other
            /// geometry operations.
            /// </summary>
            Hollow = D2D1_FIGURE_BEGIN_HOLLOW
        };

        /// <summary>
        /// Indicates whether a specific D2D1SimplifiedGeometrySink figure is open or closed.
        /// </summary>
        public enum class D2D1FigureEnd : UINT
        {
            /// <summary>
            /// The figure is open.
            /// </summary>
            Open = D2D1_FIGURE_END_OPEN,

            /// <summary>
            /// The figure is closed.
            /// </summary>
            Closed = D2D1_FIGURE_END_CLOSED
        };

        /// <summary>
        /// Defines the direction that an elliptical arc is drawn.
        /// </summary>
        public enum class D2D1SweepDirection : UINT
        {
            /// <summary>
            /// Arcs are drawn in a counterclockwise (negative-angle) direction.
            /// </summary>
            CounterClockwise = D2D1_SWEEP_DIRECTION_COUNTER_CLOCKWISE,

            /// <summary>
            /// Arcs are drawn in a clockwise (positive-angle) direction.
            /// </summary>
            Clockwise = D2D1_SWEEP_DIRECTION_CLOCKWISE
        };

        /// <summary>
        /// Specifies whether an arc should be greater than 180 degrees.
        /// </summary>
        public enum class D2D1ArcSize : UINT
        {
            /// <summary>
            /// An arc's sweep should be 180 degrees or less.
            /// </summary>
            Small = D2D1_ARC_SIZE_SMALL,

            /// <summary>
            /// An arc's sweep should be 180 degrees or greater.
            /// </summary>
            Large = D2D1_ARC_SIZE_LARGE
        };

        /// <summary>
        /// Specifies how a geometry is simplified to an ID2D1SimplifiedGeometrySink.
        /// </summary>
        public enum class D2D1GeometrySimplificationOption : UINT
        {
            /// <summary>
            /// The output can contain cubic Bezier curves and line segments.
            /// </summary>
            CubicsAndLines = D2D1_GEOMETRY_SIMPLIFICATION_OPTION_CUBICS_AND_LINES,

            /// <summary>
            /// The output is flattened so that it contains only line segments.
            /// </summary>
            Lines = D2D1_GEOMETRY_SIMPLIFICATION_OPTION_LINES
        };

        /// <summary>
        /// Specifies the different methods by which two geometries can be combined.
        /// </summary>
        public enum class D2D1CombineMode : UINT
        {
            /// <summary>
            /// The two regions are combined by taking the union of both. Given two geometries,
            /// A and B, the resulting geometry is geometry A + geometry B.
            /// </summary>
            Union = D2D1_COMBINE_MODE_UNION,

            /// <summary>
            /// The two regions are combined by taking their intersection. The new area consists of the
            /// overlapping region between the two geometries.
            /// </summary>
            Intersect = D2D1_COMBINE_MODE_INTERSECT,

            /// <summary>
            /// The two regions are combined by taking the area that exists in the first region but not
            /// the second and the area that exists in the second region but not the first. Given two
            /// geometries, A and B, the new region consists of (A-B) + (B-A).
            /// </summary>
            Xor = D2D1_COMBINE_MODE_XOR,

            /// <summary>
            /// The second region is excluded from the first. Given two geometries, A and B, the area of
            /// geometry B is removed from the area of geometry A, producing a region that is A-B.
            /// </summary>
            Exclude = D2D1_COMBINE_MODE_EXCLUDE
        };



        /// <summary>
        /// Represents a cubic bezier segment drawn between two points.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1BezierSegment
        {
            /// <summary>
            /// The first control point for the Bezier segment.
            /// </summary>
            D2DPoint2F point1;

            /// <summary>
            /// The second control point for the Bezier segment.
            /// </summary>
            D2DPoint2F point2;

            /// <summary>
            /// The end point for the Bezier segment.
            /// </summary>
            D2DPoint2F point3;

            D2D1BezierSegment(
                [In][IsReadOnly] D2DPoint2F% point1,
                [In][IsReadOnly] D2DPoint2F% point2,
                [In][IsReadOnly] D2DPoint2F% point3
            );
        };

        /// <summary>
        /// Contains the control point and end point for a quadratic Bezier segment.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1QuadraticBezierSegment
        {
            /// <summary>
            /// The control point of the quadratic Bezier segment.
            /// </summary>
            D2DPoint2F point1;

            /// <summary>
            /// The end point of the quadratic Bezier segment.
            /// </summary>
            D2DPoint2F point2;

            D2D1QuadraticBezierSegment(
                [In][IsReadOnly] D2DPoint2F% point1,
                [In][IsReadOnly] D2DPoint2F% point2
            );
        };

        /// <summary>
        /// Describes an elliptical arc between two points.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1ArcSegment
        {
            /// <summary>
            /// The end point of the arc.
            /// </summary>
            D2DPoint2F point;

            /// <summary>
            /// The x-radius and y-radius of the arc.
            /// </summary>
            D2DSizeF size;

            /// <summary>
            /// A value that specifies how many degrees in the clockwise direction the ellipse is
            /// rotated relative to the current coordinate system.
            /// </summary>
            float rotationAngle;

            /// <summary>
            /// A value that specifies whether the arc sweep is clockwise or counterclockwise.
            /// </summary>
            D2D1SweepDirection sweepDirection;

            /// <summary>
            /// A value that specifies whether the given arc is larger than 180 degrees.
            /// </summary>
            D2D1ArcSize arcSize;

            D2D1ArcSegment(
                [In][IsReadOnly] D2DPoint2F% point,
                [In][IsReadOnly] D2DSizeF% size,
                float rotationAngle,
                D2D1SweepDirection sweepDirection,
                D2D1ArcSize arcSize
            );
        };

        /// <summary>
        /// Contains the three vertices that describe a triangle.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1Triangle
        {
            /// <summary>
            /// The first vertex of a triangle.
            /// </summary>
            D2DPoint2F point1;

            /// <summary>
            /// The second vertex of a triangle.
            /// </summary>
            D2DPoint2F point2;

            /// <summary>
            /// The third vertex of a triangle.
            /// </summary>
            D2DPoint2F point3;
        };

        /// <summary>
        /// Contains the dimensions and corner radii of a rounded rectangle.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1RoundedRect
        {
            /// <summary>
            /// The coordinates of the rectangle.
            /// </summary>
            D2DRectF rect;

            /// <summary>
            /// The x-radius for the quarter ellipse that is drawn to replace every corner of the
            /// rectangle.
            /// </summary>
            float radiusX;

            /// <summary>
            /// The y-radius for the quarter ellipse that is drawn to replace every corner of the
            /// rectangle.
            /// </summary>
            float radiusY;

            D2D1RoundedRect(
                [In][IsReadOnly] D2DRectF% rect,
                float radiusX,
                float radiusY
            );
        };

        /// <summary>
        /// Contains the center point, x-radius, and y-radius of an ellipse.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct D2D1Ellipse
        {
            /// <summary>
            /// The center point of the ellipse.
            /// </summary>
            D2DPoint2F point;

            /// <summary>
            /// The X-radius of the ellipse.
            /// </summary>
            float radiusX;

            /// <summary>
            /// The Y-radius of the ellipse.
            /// </summary>
            float radiusY;

            D2D1Ellipse(
                [In][IsReadOnly] D2DPoint2F% point,
                float radiusX,
                float radiusY
            );
        };



        [Extension]
        public ref class Matrix3X2F abstract sealed
        {
        public:
            /// <summary>
            /// Calculates the determinant of the matrix.
            /// </summary>
            /// <returns>The determinant of this matrix.</returns>
            [Extension]
            static float Determinant(D2DMatrix3X2F obj);

            /// <summary>
            /// Indicates whether the matrix is invertible.
            /// </summary>
            /// <returns>true if the matrix is invertible; otherwise, false.</returns>
            [Extension]
            static bool IsInvertible(D2DMatrix3X2F obj);

            /// <summary>
            /// Inverts the matrix, if it is invertible.
            /// </summary>
            /// <returns>true if the matrix was inverted; otherwise, false.</returns>
            [Extension]
            static bool Invert(D2DMatrix3X2F% obj);

            /// <summary>
            /// Multiplies the two matrices and stores the result in this matrix.
            /// </summary>
            /// <param name="a">The first matrix to multiply.</param>
            /// <param name="b">The second matrix to multiply.</param>
            [Extension]
            static void SetProduct(
                D2DMatrix3X2F% obj,
                [In][IsReadOnly] D2DMatrix3X2F% a,
                [In][IsReadOnly] D2DMatrix3X2F% b
            );

            /// <summary>
            /// Uses this matrix to transform the specified point and returns the result.
            /// </summary>
            /// <param name="point">The point to transform.</param>
            /// <returns>The transformed point.</returns>
            [Extension]
            static D2DPoint2F TransformPoint(D2DMatrix3X2F obj, D2DPoint2F point);
        };
    }
}