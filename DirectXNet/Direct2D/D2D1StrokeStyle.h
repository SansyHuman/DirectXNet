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
        /// <summary>
        /// Describes the caps, miter limit, line join, and dash information for a stroke.
        /// </summary>
        public ref class D2D1StrokeStyle : D2D1Resource
        {
        private:
            ::ID2D1StrokeStyle* pStroke;

        internal:
            D2D1StrokeStyle(::ID2D1StrokeStyle* pStroke);
            D2D1StrokeStyle() : D2D1Resource() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1StrokeStyle.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the type of shape used at the beginning of a stroke.
            /// </summary>
            property D2D1CapStyle StartCap
            {
                D2D1CapStyle get();
            }

            /// <summary>
            /// Retrieves the type of shape used at the end of a stroke.
            /// </summary>
            property D2D1CapStyle EndCap
            {
                D2D1CapStyle get();
            }

            /// <summary>
            /// Gets a value that specifies how the ends of each dash are drawn.
            /// </summary>
            property D2D1CapStyle DashCap
            {
                D2D1CapStyle get();
            }

            /// <summary>
            /// Retrieves the limit on the ratio of the miter length to half the stroke's thickness.
            /// </summary>
            property float MiterLimit
            {
                float get();
            }

            /// <summary>
            /// Retrieves the type of joint used at the vertices of a shape's outline.
            /// </summary>
            property D2D1LineJoin LineJoin
            {
                D2D1LineJoin get();
            }

            /// <summary>
            /// Retrieves a value that specifies how far in the dash sequence the stroke will start.
            /// </summary>
            property float DashOffset
            {
                float get();
            }

            /// <summary>
            /// Gets a value that describes the stroke's dash pattern.
            /// </summary>
            property D2D1DashStyle DashStyle
            {
                D2D1DashStyle get();
            }

            /// <summary>
            /// Retrieves the number of entries in the dashes array.
            /// </summary>
            property unsigned int DashesCount
            {
                unsigned int get();
            }

            /// <summary>
            /// Copies the dash pattern to the specified array.
            /// </summary>
            /// <param name="dashes">An array that will receive the dash pattern. The array must be able to
            /// contain at least as many elements as specified by dashesCount. You must allocate storage for
            /// this array.</param>
            void GetDashes(array<float>^ dashes);
        };
    }
}
