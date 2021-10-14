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
        /// Describes a rounded rectangle.
        /// </summary>
        public ref class D2D1RoundedRectangleGeometry : D2D1Geometry
        {
        private:
            ::ID2D1RoundedRectangleGeometry* pRect;

        internal:
            D2D1RoundedRectangleGeometry(::ID2D1RoundedRectangleGeometry* pRect);
            D2D1RoundedRectangleGeometry() : D2D1Geometry() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1RoundedRectangleGeometry.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves a rounded rectangle that describes this rounded rectangle geometry.
            /// </summary>
            property D2D1RoundedRect RoundedRect
            {
                D2D1RoundedRect get();
            }
        };
    }
}
