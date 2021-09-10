#pragma once

#include "../pch.h"
#include "DXGIAdapter.h"
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
        /// <summary>
        /// The DXGIAdapter1 interface represents a display sub-system (including one or more GPU's,
        /// DACs and video memory).
        /// </summary>
        public ref class DXGIAdapter1 : DXGIAdapter
        {
        private:
            ::IDXGIAdapter1* pAdapter1;
            
        internal:
            DXGIAdapter1(::IDXGIAdapter1* pAdapter1);
            DXGIAdapter1() : DXGIAdapter() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIAdapter1.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets a DXGI 1.1 description of an adapter (or video card).
            /// </summary>
            property DXGIAdapterDesc1 AdapterDesc1
            {
                DXGIAdapterDesc1 get();
            }
        };
    }
}