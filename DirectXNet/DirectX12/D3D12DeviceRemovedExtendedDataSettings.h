#pragma once

#include "../pch.h"
#include "../Common/Unknown.h"
#include "../Common/Result.h"
#include "D3D12Structs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DirectX12
    {
        /// <summary>
        /// This class controls Device Removed Extended Data (DRED) settings. You should configure all DRED
        /// settings before you create a Direct3D 12 device. To retrieve the
        /// D3D12DeviceRemovedExtendedDataSettings object, call D3D12::GetDebugInterface.
        /// </summary>
        public ref class D3D12DeviceRemovedExtendedDataSettings : Common::Unknown
        {
        private:
            ::ID3D12DeviceRemovedExtendedDataSettings* pSettings;

        internal:
            D3D12DeviceRemovedExtendedDataSettings(::ID3D12DeviceRemovedExtendedDataSettings* pSettings);
            D3D12DeviceRemovedExtendedDataSettings() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12DeviceRemovedExtendedDataSettings.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Configures the enablement settings for Device Removed Extended Data (DRED) auto-breadcrumbs.
            /// </summary>
            /// <param name="enablement">A D3D12DREDEnablement value.</param>
            void SetAutoBreadcrumbsEnablement(D3D12DREDEnablement enablement);

            /// <summary>
            /// Configures the enablement settings for Device Removed Extended Data (DRED) page fault
            /// reporting.
            /// </summary>
            /// <param name="enablement">A D3D12DREDEnablement value.</param>
            void SetPageFaultEnablement(D3D12DREDEnablement enablement);

            /// <summary>
            /// Configures the enablement settings for Device Removed Extended Data (DRED) dump creation
            /// for Windows Error Reporting (WER), also known as Watson.
            /// </summary>
            /// <param name="enablement">A D3D12DREDEnablement value.</param>
            void SetWatsonDumpEnablement(D3D12DREDEnablement enablement);
        };
    }
}