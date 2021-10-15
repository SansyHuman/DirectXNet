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
        /// Represents a composite geometry, composed of other D2D1Geometry objects.
        /// </summary>
        public ref class D2D1GeometryGroup : D2D1Geometry
        {
        private:
            ::ID2D1GeometryGroup* pGroup;

        internal:
            D2D1GeometryGroup(::ID2D1GeometryGroup* pGroup);
            D2D1GeometryGroup() : D2D1Geometry() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1GeometryGroup.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Indicates how the intersecting areas of the geometries contained in this geometry group are
            /// combined.
            /// </summary>
            property D2D1FillMode FillMode
            {
                D2D1FillMode get();
            }

            /// <summary>
            /// Indicates the number of geometry objects in the geometry group.
            /// </summary>
            property unsigned int SourceGeometryCount
            {
                unsigned int get();
            }

            /// <summary>
            /// Retrieves the geometries in the geometry group.
            /// </summary>
            /// <param name="geometries">The buffer array that contains geometries when the method returns.
            /// If the length of this array is less than the number of geometries in the geometry group, the
            /// remaining geometries are omitted. If the length of this array is larger than the number of
            /// geometries in the geometry group, the extra geometries are set to null.</param>
            void GetSourceGeometries(array<D2D1Geometry^>^ geometries);
        };
    }
}
