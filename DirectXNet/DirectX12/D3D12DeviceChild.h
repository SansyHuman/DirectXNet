#pragma once

#include "../pch.h"
#include "D3D12Object.h"
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
        ref class D3D12Device;

        /// <summary>
        /// An interface from which other core interfaces inherit from, including (but not limited to)
        /// D3D12PipelineLibrary, D3D12CommandList, D3D12Pageable, and D3D12RootSignature. It provides
        /// a method to get back to the device object it was created against.
        /// </summary>
        public ref class D3D12DeviceChild : D3D12Object
        {
        private:
            com::ptr<::ID3D12DeviceChild> pDeviceChild;

        internal:
            D3D12DeviceChild(::ID3D12DeviceChild* pDeviceChild);
            D3D12DeviceChild() : D3D12Object() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12DeviceChild.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the device that created this interface.
            /// </summary>
            /// <typeparam name="T">The type of device.</typeparam>
            /// <returns>Device if succeeded.</returns>
            generic <typename T> where T : D3D12Device
            T GetDevice();
        };
    }
}