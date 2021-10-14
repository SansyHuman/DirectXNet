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
        };
    }
}