#pragma once

#include "../pch.h"
#include "DXGIObject.h"
#include "DXGIStructs.h"
#include "../Common/Result.h"

using namespace System;
using namespace msclr;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGISwapChain;
        ref class DXGIAdapter;

        /// <summary>
        /// A DXGIFactory class implements methods for generating DXGI objects (which handle full
        /// screen transitions).
        /// </summary>
        public ref class DXGIFactory : DXGIObject
        {
        private:
            com::ptr<::IDXGIFactory> pFactory;

        internal:
            DXGIFactory(::IDXGIFactory* pFactory);
            DXGIFactory() : DXGIObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIFactory.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Enumerates the adapters (video cards).
            /// </summary>
            /// <param name="index">The index of the adapter to enumerate.</param>
            /// <param name="adapter">The reference to an DXGIAdapter at the position specified by the
            /// index parameter.</param>
            /// <returns>Result code.</returns>
            Common::Result EnumAdapters(
                unsigned int index,
                [Out] DXGIAdapter^% adapter
            );

            /// <summary>
            /// Creates a swap chain.
            /// </summary>
            /// <param name="device">For Direct3D 11, and earlier versions of Direct3D, this is
            /// a pointer to the Direct3D device for the swap chain. For Direct3D 12 this is
            /// a pointer to a direct command queue.</param>
            /// <param name="desc">Swap-chain description</param>
            /// <returns>Created swap chain if succeeded.</returns>
            DXGISwapChain^ CreateSwapChain(
                Common::Unknown^ device,
                [In][IsReadOnly] DXGISwapChainDesc% desc
            );

            /// <summary>
            /// Get the window through which the user controls the transition to and from full screen.
            /// </summary>
            /// <returns>Window handle.</returns>
            IntPtr GetWindowAssociation();

            [Flags]
            enum class WindowAssociationFlag : UINT
            {
                None = 0,
                NoWindowChanges = DXGI_MWA_NO_WINDOW_CHANGES,
                NoAltEnter = DXGI_MWA_NO_ALT_ENTER,
                NoPrintScreen = DXGI_MWA_NO_PRINT_SCREEN
            };

            /// <summary>
            /// Allows DXGI to monitor an application's message queue for the alt-enter key sequence
            /// (which causes the application to switch from windowed to full screen or vice versa).
            /// </summary>
            /// <param name="windowHandle">The handle of the window that is to be monitored. This
            /// parameter can be NULL; but only if Flags is also 0.</param>
            /// <param name="flags">One or more of the following values.
            /// <para>NoWindowChanges - Prevent DXGI from monitoring an applications message queue; this makes DXGI unable to respond to mode changes.</para>
            /// <para>NoAltEnter - Prevent DXGI from responding to an alt - enter sequence.</para>
            /// <para>NoPrintScreen - Prevent DXGI from responding to a print - screen key.</para>
            /// </param>
            void MakeWindowAssociation(IntPtr windowHandle, WindowAssociationFlag flags);

            /// <summary>
            /// Create an adapter interface that represents a software adapter.
            /// </summary>
            /// <param name="module">Handle to the software adapter's dll. Handle can be obtained
            /// with GetModuleHandle or LoadLibrary.</param>
            /// <returns>Created software adapter if succeeded.</returns>
            DXGIAdapter^ CreateSoftwareAdapter(IntPtr module);
        };
    }
}