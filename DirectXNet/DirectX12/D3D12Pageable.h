#pragma once

#include "../pch.h"
#include "D3D12DeviceChild.h"
#include "../Common/Result.h"

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
        /// An interface from which many other core interfaces inherit from. It indicates that the
        /// object type encapsulates some amount of GPU-accessible memory; but does not strongly
        /// indicate whether the application can manipulate the object's residency.
        /// </summary>
        public ref class D3D12Pageable : D3D12DeviceChild
        {
        internal:
            D3D12Pageable(::ID3D12Pageable* pPageable);
            D3D12Pageable() : D3D12DeviceChild() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Pageable.</returns>
            virtual Guid GetGuid() override;
        };
    }
}