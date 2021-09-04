#pragma once

#include "../pch.h"
#include "DXGIDevice.h"
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
        /// <summary>
        /// A DXGIDevice1 class implements a derived class for DXGI objects that produce image data.
        /// </summary>
        public ref class DXGIDevice1 : DXGIDevice
        {
        private:
            com::ptr<::IDXGIDevice1> pDevice1;

        internal:
            DXGIDevice1(::IDXGIDevice1* pDevice1);
            DXGIDevice1() : DXGIDevice() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIDevice1.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets ans sets the number of frames that the system is allowed to queue for rendering.
            /// </summary>
            property unsigned int MaximumFrameLatency
            {
                unsigned int get();
                void set(unsigned int value);
            }
        };
    }
}