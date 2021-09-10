#pragma once

#include "../pch.h"
#include "DXGIDeviceSubObject.h"
#include "DXGIStructs.h"

using namespace System;
using namespace msclr;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        /// <summary>
        /// The DXGISurface class implements methods for image-data objects.
        /// </summary>
        public ref class DXGISurface : DXGIDeviceSubObject
        {
        private:
            ::IDXGISurface* pSurface;

        internal:
            DXGISurface(::IDXGISurface* pSurface);
            DXGISurface() : DXGIDeviceSubObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGISurface.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Get a description of the surface.
            /// </summary>
            property DXGISurfaceDesc SurfaceDesc
            {
                DXGISurfaceDesc get();
            }

            /// <summary>
            /// Get a pointer to the data contained in the surface, and deny GPU access to the surface.
            /// </summary>
            /// <param name="mapFlags">CPU read-write flags.</param>
            /// <returns>Mapped rect if succeeded.</returns>
            DXGIMappedRect Map(DXGIMapFlag mapFlags);

            /// <summary>
            /// Invalidate the pointer to the surface retrieved by DXGISurface::Map and re-enable GPU access
            /// to the resource.
            /// </summary>
            void Unmap();
        };
    }
}