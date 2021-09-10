#pragma once

#include "../pch.h"
#include "D3D12Pageable.h"
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
        /// Represents the allocations of storage for graphics processing unit (GPU) commands.
        /// </summary>
        public ref class D3D12CommandAllocator : D3D12Pageable
        {
        private:
            ::ID3D12CommandAllocator* pAlloc;

        internal:
            D3D12CommandAllocator(::ID3D12CommandAllocator* pAlloc);
            D3D12CommandAllocator() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12CommandAllocator.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Indicates to re-use the memory that is associated with the command allocator.
            /// </summary>
            /// <returns>Result code.</returns>
            Result Reset();
        };
    }
}