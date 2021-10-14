#pragma once

#include "CommonStructs.h"
#include "../DXGI/DXGIStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::DXGI;

namespace DirectXNet
{
    namespace Common
    {
        namespace D2D
        {
            /// <summary>
            /// The measuring method used for text layout.
            /// </summary>
            public enum class DWriteMeasuringMode : UINT
            {
                /// <summary>
                /// Text is measured using glyph ideal metrics whose values are independent to the
                /// current display resolution.
                /// </summary>
                Natural = DWRITE_MEASURING_MODE_NATURAL,

                /// <summary>
                /// Text is measured using glyph display compatible metrics whose values tuned for
                /// the current display resolution.
                /// </summary>
                GDIClassic = DWRITE_MEASURING_MODE_GDI_CLASSIC,

                /// <summary>
                /// Text is measured using the same glyph display metrics as text measured by GDI using
                /// a font created with CLEARTYPE_NATURAL_QUALITY.
                /// </summary>
                GDINatural = DWRITE_MEASURING_MODE_GDI_NATURAL
            };

            /// <summary>
            /// Fonts may contain multiple drawable data formats for glyphs. These flags specify which
            /// formats are supported in the font, either at a font-wide level or per glyph, and the app
            /// may use them to tell DWrite which formats to return when splitting a color glyph run.
            /// </summary>
            [Flags]
            public enum class DWriteGlyphImageFormats : UINT
            {
                /// <summary>
                /// Indicates no data is available for this glyph.
                /// </summary>
                None = DWRITE_GLYPH_IMAGE_FORMATS_NONE,

                /// <summary>
                /// The glyph has TrueType outlines.
                /// </summary>
                Truetype = DWRITE_GLYPH_IMAGE_FORMATS_TRUETYPE,

                /// <summary>
                /// The glyph has CFF outlines.
                /// </summary>
                CFF = DWRITE_GLYPH_IMAGE_FORMATS_CFF,

                /// <summary>
                /// The glyph has multilayered COLR data.
                /// </summary>
                COLR = DWRITE_GLYPH_IMAGE_FORMATS_COLR,

                /// <summary>
                /// The glyph has SVG outlines as standard XML.
                /// </summary>
                /// <remarks>
                /// Fonts may store the content gzip'd rather than plain text,
                /// indicated by the first two bytes as gzip header {0x1F 0x8B}.
                /// </remarks>
                SVG = DWRITE_GLYPH_IMAGE_FORMATS_SVG,

                /// <summary>
                /// The glyph has PNG image data, with standard PNG IHDR.
                /// </summary>
                PNG = DWRITE_GLYPH_IMAGE_FORMATS_PNG,

                /// <summary>
                /// The glyph has JPEG image data, with standard JIFF SOI header.
                /// </summary>
                JPEG = DWRITE_GLYPH_IMAGE_FORMATS_JPEG,

                /// <summary>
                /// The glyph has TIFF image data.
                /// </summary>
                TIFF = DWRITE_GLYPH_IMAGE_FORMATS_TIFF,

                /// <summary>
                /// The glyph has raw 32-bit premultiplied BGRA data.
                /// </summary>
                PremultipliedB8G8R8A8 = DWRITE_GLYPH_IMAGE_FORMATS_PREMULTIPLIED_B8G8R8A8,
            };

            /// <summary>
            /// Qualifies how alpha is to be treated in a bitmap or render target containing
            /// alpha.
            /// </summary>
            public enum class D2D1AlphaMode : UINT
            {
                /// <summary>
                /// Alpha mode should be determined implicitly. Some target surfaces do not supply
                /// or imply this information in which case alpha must be specified.
                /// </summary>
                Unknown = D2D1_ALPHA_MODE_UNKNOWN,

                /// <summary>
                /// Treat the alpha as premultipled.
                /// </summary>
                Premultiplied = D2D1_ALPHA_MODE_PREMULTIPLIED,

                /// <summary>
                /// Opacity is in the 'A' component only.
                /// </summary>
                Straight = D2D1_ALPHA_MODE_STRAIGHT,

                /// <summary>
                /// Ignore any alpha channel information.
                /// </summary>
                Ignore = D2D1_ALPHA_MODE_IGNORE
            };



            /// <summary>
            /// Description of a pixel format.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2D1PixelFormat
            {
                /// <summary>
                /// A value that specifies the size and arrangement of channels in each pixel.
                /// </summary>
                DXGIFormat format;

                /// <summary>
                /// A value that specifies whether the alpha channel is using pre-multiplied alpha,
                /// straight alpha, whether it should be ignored and considered opaque, or whether it is
                /// unknown.
                /// </summary>
                D2D1AlphaMode alphaMode;
            };

            /// <summary>
            /// Represents an x-coordinate and y-coordinate pair in two-dimensional space.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DPoint2U
            {
                /// <summary>
                /// The x-coordinate value of the point.
                /// </summary>
                unsigned int x;

                /// <summary>
                /// The y-coordinate value of the point.
                /// </summary>
                unsigned int y;

                /// <summary>
                /// Creates a D2DPoint2U structure that contains the specified x-coordinates and
                /// y-coordinates.
                /// </summary>
                /// <param name="x">The x-coordinate of the point. The default value is 0.</param>
                /// <param name="y">The y-coordinate of the point. The default value is 0.</param>
                D2DPoint2U(
                    [Optional] Nullable<unsigned int> x,
                    [Optional] Nullable<unsigned int> y
                );
            };

            /// <summary>
            /// Represents an x-coordinate and y-coordinate pair in two-dimensional space.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DPoint2F
            {
                /// <summary>
                /// The x-coordinate value of the point.
                /// </summary>
                float x;

                /// <summary>
                /// The y-coordinate value of the point.
                /// </summary>
                float y;

                /// <summary>
                /// Creates a D2DPoint2F structure that contains the specified x-coordinates and
                /// y-coordinates.
                /// </summary>
                /// <param name="x">The x-coordinate of the point. The default value is 0.f.</param>
                /// <param name="y">The y-coordinate of the point. The default value is 0.f.</param>
                D2DPoint2F(
                    [Optional] Nullable<float> x,
                    [Optional] Nullable<float> y
                );

                static D2DPoint2F operator*(
                    [In][IsReadOnly] D2DPoint2F% point,
                    [In][IsReadOnly] System::Numerics::Matrix3x2% matrix
                    );
            };

            /// <summary>
            /// Represents an x-coordinate and y-coordinate pair in two-dimensional space.
            /// </summary>
            using D2DPoint2L = DirectXNet::Common::Point;

            /// <summary>
            /// A vector of 2 float values (x, y).
            /// </summary>
            using D2DVector2F = System::Numerics::Vector2;

            /// <summary>
            /// A vector of 3 float values (x, y, z).
            /// </summary>
            using D2DVector3F = System::Numerics::Vector3;

            /// <summary>
            /// A vector of 4 float values (x, y, z, w).
            /// </summary>
            using D2DVector4F = System::Numerics::Vector4;

            /// <summary>
            /// Represents a rectangle defined by the coordinates of the upper-left corner
            /// (left, top) and the coordinates of the lower-right corner (right, bottom).
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DRectF
            {
                /// <summary>
                /// The x-coordinate of the upper-left corner of the rectangle.
                /// </summary>
                float left;

                /// <summary>
                /// The y-coordinate of the upper-left corner of the rectangle.
                /// </summary>
                float top;
                
                /// <summary>
                /// The x-coordinate of the lower-right corner of the rectangle.
                /// </summary>
                float right;

                /// <summary>
                /// The y-coordinate of the lower-right corner of the rectangle.
                /// </summary>
                float bottom;

                /// <summary>
                /// Creates a D2DRectF structure that contains the specified dimensions.
                /// </summary>
                /// <param name="left">The x-coordinate of the upper-left corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="top">The y-coordinate of the upper-left corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="right">The x-coordinate of the lower-right corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="bottom">The y-coordinate of the lower-right corner of the rectangle.
                /// The default value is 0.f.</param>
                D2DRectF(
                    [Optional] Nullable<float> left,
                    [Optional] Nullable<float> top,
                    [Optional] Nullable<float> right,
                    [Optional] Nullable<float> bottom
                );

                static property D2DRectF InfiniteRect
                {
                    D2DRectF get();
                }
            };

            /// <summary>
            /// Represents a rectangle defined by the coordinates of the upper-left corner
            /// (left, top) and the coordinates of the lower-right corner (right, bottom).
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DRectU : IEquatable<D2DRectU>
            {
                /// <summary>
                /// The x-coordinate of the upper-left corner of the rectangle.
                /// </summary>
                unsigned int left;

                /// <summary>
                /// The y-coordinate of the upper-left corner of the rectangle.
                /// </summary>
                unsigned int top;

                /// <summary>
                /// The x-coordinate of the lower-right corner of the rectangle.
                /// </summary>
                unsigned int right;

                /// <summary>
                /// The y-coordinate of the lower-right corner of the rectangle.
                /// </summary>
                unsigned int bottom;

                /// <summary>
                /// Creates a D2DRectU structure that contains the specified dimensions.
                /// </summary>
                /// <param name="left">The x-coordinate of the upper-left corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="top">The y-coordinate of the upper-left corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="right">The x-coordinate of the lower-right corner of the rectangle.
                /// The default value is 0.f.</param>
                /// <param name="bottom">The y-coordinate of the lower-right corner of the rectangle.
                /// The default value is 0.f.</param>
                D2DRectU(
                    [Optional] Nullable<unsigned int> left,
                    [Optional] Nullable<unsigned int> top,
                    [Optional] Nullable<unsigned int> right,
                    [Optional] Nullable<unsigned int> bottom
                );

                virtual bool Equals(D2DRectU other);

                virtual bool Equals(Object^ other) override;

                static bool operator==(D2DRectU lhs, D2DRectU rhs);

                static bool operator!=(D2DRectU lhs, D2DRectU rhs);
            };

            /// <summary>
            /// Represents a rectangle defined by the coordinates of the upper-left corner
            /// (left, top) and the coordinates of the lower-right corner (right, bottom).
            /// </summary>
            using D2DRectL = DirectXNet::Common::Rect;

            /// <summary>
            /// Stores an ordered pair of floats, typically the width and height of a rectangle.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DSizeF
            {
                /// <summary>
                /// The horizontal component of this size.
                /// </summary>
                float width;
                
                /// <summary>
                /// The vertical component of this size.
                /// </summary>
                float height;

                /// <summary>
                /// Creates a D2DSizeF structure that contains the specified width and height.
                /// </summary>
                /// <param name="width">The width of the size. The default value is 0.f.</param>
                /// <param name="height">The height of the size. The default value is 0.f.</param>
                D2DSizeF(
                    [Optional] Nullable<float> width,
                    [Optional] Nullable<float> height
                );
            };

            /// <summary>
            /// Stores an ordered pair of integers, typically the width and height of a rectangle.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DSizeU : IEquatable<D2DSizeU>
            {
                /// <summary>
                /// The horizontal component of this size.
                /// </summary>
                unsigned int width;

                /// <summary>
                /// The vertical component of this size.
                /// </summary>
                unsigned int height;

                /// <summary>
                /// Creates a D2DSizeU structure that contains the specified width and height.
                /// </summary>
                /// <param name="width">The width of the size. The default value is 0.</param>
                /// <param name="height">The height of the size. The default value is 0.</param>
                D2DSizeU(
                    [Optional] Nullable<unsigned int> width,
                    [Optional] Nullable<unsigned int> height
                );

                virtual bool Equals(D2DSizeU other);

                virtual bool Equals(Object^ other) override;

                static bool operator==(D2DSizeU lhs, D2DSizeU rhs);

                static bool operator!=(D2DSizeU lhs, D2DSizeU rhs);
            };

            using D2DMatrix3X2F = System::Numerics::Matrix3x2;

            /// <summary>
            /// Represents a 4-by-3 matrix.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DMatrix4X3F
            {
                float _11, _12, _13;
                float _21, _22, _23;
                float _31, _32, _33;
                float _41, _42, _43;
            };

            using D2DMatrix4X4F = System::Numerics::Matrix4x4;

            /// <summary>
            /// Represents a 5-by-4 matrix.
            /// </summary>
            [StructLayout(LayoutKind::Sequential)]
            public value struct D2DMatrix5X4F
            {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
                float _51, _52, _53, _54;
            };

            using D2DColorF = DirectXNet::DXGI::D3DColorValue;
        }
    }
}