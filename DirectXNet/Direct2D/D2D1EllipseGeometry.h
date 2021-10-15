#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "D2D1Geometry.h"
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
        /// Represents an ellipse.
        /// </summary>
        public ref class D2D1EllipseGeometry : D2D1Geometry
        {
        private:
            ::ID2D1EllipseGeometry* pEllipse;

        internal:
            D2D1EllipseGeometry(::ID2D1EllipseGeometry* pEllipse);
            D2D1EllipseGeometry() : D2D1Geometry() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1EllipseGeometry.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the D2D1Ellipse structure that describes this ellipse geometry.
            /// </summary>
            property D2D1Ellipse Ellipse
            {
                D2D1Ellipse get();
            }
        };
    }
}
