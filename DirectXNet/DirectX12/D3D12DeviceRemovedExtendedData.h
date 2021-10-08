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
        /// Provides runtime access to Device Removed Extended Data (DRED) data. To retrieve the
        /// D3D12DeviceRemovedExtendedData object, call QueryInterface on an D3D12Device (or derived)
        /// object.
        /// </summary>
        public ref class D3D12DeviceRemovedExtendedData : Common::Unknown
        {
        private:
            ::ID3D12DeviceRemovedExtendedData* pData;

        internal:
            D3D12DeviceRemovedExtendedData(::ID3D12DeviceRemovedExtendedData* pData);
            D3D12DeviceRemovedExtendedData() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12DeviceRemovedExtendedData.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the Device Removed Extended Data (DRED) auto-breadcrumbs output after device removal.
            /// </summary>
            property D3D12DREDAutoBreadcrumbsOutput AutoBreadcrumbsOutput
            {
                D3D12DREDAutoBreadcrumbsOutput get();
            }

            /// <summary>
            /// Retrieves the Device Removed Extended Data (DRED) page fault data, including matching
            /// allocation for both living and recently-deleted runtime objects. The object whose address is
            /// passed receives the data.
            /// </summary>
            property D3D12DREDPageFaultOutput PageFaultAllocationOutput
            {
                D3D12DREDPageFaultOutput get();
            }
        };
    }
}