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
        /// Represents a geometry that has been transformed.
        /// </summary>
        public ref class D2D1TransformedGeometry : D2D1Geometry
        {
        private:
            ::ID2D1TransformedGeometry* pTrans;

        internal:
            D2D1TransformedGeometry(::ID2D1TransformedGeometry* pTrans);
            D2D1TransformedGeometry() : D2D1Geometry() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1TransformedGeometry.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the source geometry of this transformed geometry object.
            /// </summary>
            property D2D1Geometry^ SourceGeometry
            {
                D2D1Geometry^ get();
            }

            /// <summary>
            /// Retrieves the matrix used to transform the D2D1TransformedGeometry object's source geometry.
            /// </summary>
            property D2DMatrix3X2F Transform
            {
                D2DMatrix3X2F get();
            }
        };
    }
}
