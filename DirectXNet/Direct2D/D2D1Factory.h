#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "../Common/Unknown.h"
#include "D2D1Structs.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Common;

namespace DirectXNet
{
    namespace Direct2D
    {
        ref class D2D1RectangleGeometry;
        ref class D2D1RoundedRectangleGeometry;
        ref class D2D1EllipseGeometry;
        ref class D2D1GeometryGroup;
        ref class D2D1Geometry;
        ref class D2D1TransformedGeometry;

        /// <summary>
        /// Creates Direct2D resources.
        /// </summary>
        public ref class D2D1Factory : Common::Unknown
        {
        private:
            ::ID2D1Factory* pFactory;

        internal:
            D2D1Factory(::ID2D1Factory* pFactory);
            D2D1Factory() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1Factory.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Forces the factory to refresh any system defaults that it might have changed since factory
            /// creation.
            /// </summary>
            /// <returns>Result code.</returns>
            Result ReloadSystemMetrics();

            /// <summary>
            /// Retrieves the current desktop dots per inch (DPI). To refresh this value, call
            /// ReloadSystemMetrics.
            /// </summary>
            /// <param name="dpiX">When this method returns, contains the horizontal DPI of the desktop.
            /// </param>
            /// <param name="dpiY">When this method returns, contains the vertical DPI of the desktop.</param>
            void GetDesktopDpi([Out] float% dpiX, [Out] float% dpiY);

            /// <summary>
            /// Creates an D2D1RectangleGeometry.
            /// </summary>
            /// <param name="rectangle">The coordinates of the rectangle geometry.</param>
            /// <returns>Rectangle geometry if succeeded.</returns>
            D2D1RectangleGeometry^ CreateRectangleGeometry(
                [In][IsReadOnly] D2DRectF% rectangle
            );

            /// <summary>
            /// Creates an D2D1RoundedRectangleGeometry.
            /// </summary>
            /// <param name="roundedRectangle">The coordinates and corner radii of the rounded rectangle
            /// geometry.</param>
            /// <returns>Rounded rectangle geometry if succeeded.</returns>
            D2D1RoundedRectangleGeometry^ CreateRoundedRectangleGeometry(
                [In][IsReadOnly] D2D1RoundedRect% roundedRectangle
            );

            /// <summary>
            /// Creates an D2D1EllipseGeometry.
            /// </summary>
            /// <param name="ellipse">A value that describes the center point, x-radius, and y-radius of the
            /// ellipse geometry.</param>
            /// <returns>Ellipse geometry if succeeded.</returns>
            D2D1EllipseGeometry^ CreateEllipseGeometry(
                [In][IsReadOnly] D2D1Ellipse% ellipse
            );

            /// <summary>
            /// Creates an D2D1GeometryGroup, which is an object that holds other geometries.
            /// </summary>
            /// <param name="fillMode">A value that specifies the rule that a composite shape uses to
            /// determine whether a given point is part of the geometry.</param>
            /// <param name="geometries">An array containing the geometry objects to add to the geometry
            /// group.
            /// </param>
            /// <returns>Geometry group if succeeded.</returns>
            D2D1GeometryGroup^ CreateGeometryGroup(
                D2D1FillMode fillMode,
                ...array<D2D1Geometry^>^ geometries
            );

            /// <summary>
            /// Transforms the specified geometry and stores the result as an D2D1TransformedGeometry object.
            /// </summary>
            /// <param name="sourceGeometry">The geometry to transform.</param>
            /// <param name="transform">The transformation to apply.</param>
            /// <returns>Transformed geometry if succeeded.</returns>
            D2D1TransformedGeometry^ CreateTransformedGeometry(
                D2D1Geometry^ sourceGeometry,
                [In][IsReadOnly] D2DMatrix3X2F% transform
            );
        };
    }
}