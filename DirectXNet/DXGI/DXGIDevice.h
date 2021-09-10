#pragma once

#include "../pch.h"
#include "DXGIObject.h"
#include "DXGIStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGIAdapter;
        ref class DXGISurface;

        /// <summary>
        /// A DXGIDevice class implements a derived class for DXGI objects that produce image data.
        /// </summary>
        public ref class DXGIDevice : DXGIObject
        {
        private:
            ::IDXGIDevice* pDevice;

        internal:
            DXGIDevice(::IDXGIDevice* pDevice);
            DXGIDevice() : DXGIObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIDevice.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Returns the adapter for the specified device.
            /// </summary>
            property DXGIAdapter^ Adapter
            {
                DXGIAdapter^ get();
            }

            /// <summary>
            /// Returns a surface.
            /// </summary>
            /// <param name="desc">A DXGISurfaceDesc structure that describes the surface.</param>
            /// <param name="numSurfaces">The number of surfaces to create.</param>
            /// <param name="usage">A DXGIUsage flag that specifies how the surface is expected to be used.
            /// </param>
            /// <param name="sharedResource">An optional DXGISharedResource structure that contains
            /// shared resource information for opening views of such resources.</param>
            /// <returns>First created surface if succeeded.</returns>
            [Obsolete("This method is used internally and you should not call it directly in your application.")]
            DXGISurface^ CreateSurface(
                [In][IsReadOnly] DXGISurfaceDesc% desc,
                unsigned int numSurfaces,
                DXGIUsage usage,
                [Optional] Nullable<DXGISharedResource> sharedResource
            );

            /// <summary>
            /// Gets the residency status of an array of resources.
            /// </summary>
            /// <param name="resources">An array of DXGIResource interfaces.</param>
            /// <returns>An array of DXGIResidency enumerations if succeeded.</returns>
            array<DXGIResidency>^ QueryResourceResidency(array<Common::Unknown^>^ resources);

            /// <summary>
            /// Gets and sets the GPU thread priority.
            /// </summary>
            property int GPUThreadPriority
            {
                int get();
                void set(int value);
            }
        };
    }
}