#pragma once

#include "../pch.h"
#include "DXGISurface.h"
#include "../Common/CommonStructs.h"
#include "../Common/Result.h"

using namespace System;
using namespace msclr;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        /// <summary>
        /// The DXGISurface1 class extends the IDXGISurface by adding support for using Windows Graphics
        /// Device Interface (GDI) to render to a Microsoft DirectX Graphics Infrastructure (DXGI) surface.
        /// </summary>
        public ref class DXGISurface1 : DXGISurface
        {
        private:
            ::IDXGISurface1* pSurface1;

        internal:
            DXGISurface1(::IDXGISurface1* pSurface1);
            DXGISurface1() : DXGISurface() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGISurface1.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Returns a device context (DC) that allows you to render to a Microsoft DirectX
            /// Graphics Infrastructure (DXGI) surface using Windows Graphics Device Interface (GDI).
            /// </summary>
            /// <param name="discard">A Boolean value that specifies whether to preserve Direct3D contents
            /// in the GDI DC. True directs the runtime not to preserve Direct3D contents in the GDI DC;
            /// that is, the runtime discards the Direct3D contents. False guarantees that Direct3D
            /// contents are available in the GDI DC.</param>
            /// <returns>DC handle if succeeded.</returns>
            IntPtr GetDC(bool discard);

            /// <summary>
            /// Releases the GDI device context (DC) that is associated with the current surface and
            /// allows you to use Direct3D to render.
            /// </summary>
            /// <param name="dirtyRect">An optional Rect structure that identifies the dirty region of
            /// the surface.
            /// A dirty region is any part of the surface that you used for GDI renderingand that you want
            /// to preserve.This area is used as a performance hint to graphics subsystem in certain
            /// scenarios. Do not use this parameter to restrict rendering to the specified rectangular
            /// region. If you pass in null, ReleaseDC considers the whole surface as dirty. Otherwise,
            /// ReleaseDC uses the area specified by the RECT as a performance hint to indicate what
            /// areas have been manipulated by GDI rendering.
            /// You can pass a pointer to an empty Rect structure(a rectangle with no position or area) if
            /// you didn't change any content.</param>
            /// <returns>Result code</returns>
            Result ReleaseDC([Optional] Nullable<Rect> dirtyRect);
        };
    }
}