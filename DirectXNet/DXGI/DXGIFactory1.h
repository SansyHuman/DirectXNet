#pragma once

#include "../pch.h"
#include "DXGIFactory.h"
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
        ref class DXGIAdapter1;

        /// <summary>
        /// The DXGIFactory1 class implements methods for generating DXGI objects.
        /// </summary>
        public ref class DXGIFactory1 : DXGIFactory
        {
        private:
            ::IDXGIFactory1* pFactory1;

        internal:
            DXGIFactory1(::IDXGIFactory1* pFactory1);
            DXGIFactory1() : DXGIFactory() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIFactory1.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Enumerates both adapters (video cards) with or without outputs.
            /// </summary>
            /// <param name="index">The index of the adapter to enumerate.</param>
            /// <param name="adapter">The reference to an DXGIAdapter1 class at the position specified by
            /// the Adapter parameter.</param>
            /// <returns>Result code.</returns>
            Common::Result EnumAdapters1(
                unsigned int index,
                [Out] DXGIAdapter1^% adapter
            );

            /// <summary>
            /// Informs an application of the possible need to re-enumerate adapters.
            /// False, if a new adapter is becoming available or the current adapter is going away. true,
            /// no adapter changes.
            /// </summary>
            property bool IsCurrent
            {
                bool get();
            }
        };
    }
}