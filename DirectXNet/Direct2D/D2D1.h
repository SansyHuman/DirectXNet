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

namespace DirectXNet
{
    namespace Direct2D
    {
        public ref class D2D1 abstract sealed
        {
        private:
            literal float Deg2Rad = (float)System::Math::PI / 180;

            static D2D1();

        public:
            /// <summary>
            /// Creates a rotation transformation that rotates by the specified angle about the
            /// specified point.
            /// </summary>
            /// <param name="angle">The clockwise rotation angle, in degrees.</param>
            /// <param name="center">The point about which to rotate.</param>
            /// <returns>The new rotation transformation.</returns>
            static D2DMatrix3X2F MakeRotateMatrix(float angle, D2DPoint2F center);

            /// <summary>
            /// Creates a skew transformation that has the specified x-axis angle, y-axis angle, and
            /// center point.
            /// </summary>
            /// <param name="angleX">The x-axis skew angle, which is measured in degrees counterclockwise
            /// from the y-axis.</param>
            /// <param name="angleY">The y-axis skew angle, which is measured in degrees counterclockwise
            /// from the x-axis.</param>
            /// <param name="center">The center point of the skew operation.</param>
            /// <returns>The skew transformation.</returns>
            static D2DMatrix3X2F MakeSkewMatrix(float angleX, float angleY, D2DPoint2F center);

            // Helper methods.

            /// <summary>
            /// Returns the maximum floating-point value.
            /// </summary>
            static property float FloatMax
            {
                float get();
            }

        private:
            literal unsigned int sc_redShift = 16;
            literal unsigned int sc_greenShift = 8;
            literal unsigned int sc_blueShift = 0;

            literal unsigned int sc_redMask = 0xff << sc_redShift;
            literal unsigned int sc_greenMask = 0xff << sc_greenShift;
            literal unsigned int sc_blueMask = 0xff << sc_blueShift;

        public:
            /// <summary>
            /// Instantiates a new instance of the D3DColorValue struct that contains the specified RGB and
            /// alpha values.
            /// </summary>
            /// <param name="rgb">The RGB value for the color to be constructed.</param>
            /// <param name="a">The alpha value for the color to be constructed. An alpha channel value
            /// ranges from 0.0 to 1.0, where 0.0 represents a fully transparent color and 1.0 represents a
            /// fully opaque color. The default value is 1.0.</param>
            /// <returns>D3DColorValue struct.</returns>
            static D2DColorF ColorF(
                unsigned int rgb,
                [Optional] Nullable<float> a
            );

            /// <summary>
            /// Instantiates a new instance of the D3DColorValue struct that contains the specified RGB and
            /// alpha values.
            /// </summary>
            /// <param name="knownColor">The D2DColor which contains the known RGB values.</param>
            /// <param name="a">The alpha value for the color to be constructed. An alpha channel value
            /// ranges from 0.0 to 1.0, where 0.0 represents a fully transparent color and 1.0 represents a
            /// fully opaque color. The default value is 1.0.</param>
            /// <returns>D3DColorValue struct.</returns>
            static D2DColorF ColorF(
                D2DColor knownColor,
                [Optional] Nullable<float> a
            );

            /// <summary>
            /// Instantiates a new instance of the D3DColorValue struct that contains the specified red,
            /// green, blue, and alpha values.
            /// </summary>
            /// <param name="r">The red component of the color to be constructed.</param>
            /// <param name="g">The green component of the color to be constructed.</param>
            /// <param name="b">The blue component of the color to be constructed.</param>
            /// <param name="a">The alpha value for the color to be constructed. An alpha channel value
            /// ranges from 0.0 to 1.0, where 0.0 represents a fully transparent color and 1.0 represents a
            /// fully opaque color. The default value is 1.0.</param>
            /// <returns>D3DColorValue struct.</returns>
            static D2DColorF ColorF(
                float r,
                float g,
                float b,
                [Optional] Nullable<float> a
            );

            /// <summary>
            /// Gets an identity matrix.
            /// </summary>
            static property D2DMatrix3X2F IdentityMatrix
            {
                D2DMatrix3X2F get();
            }
        };
    }
}
