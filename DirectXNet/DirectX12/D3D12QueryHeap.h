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
        /// Manages a query heap. A query heap holds an array of queries, referenced by indexes.
        /// </summary>
        public ref class D3D12QueryHeap : D3D12Pageable
        {
        internal:
            D3D12QueryHeap(::ID3D12QueryHeap* pHeap);
            D3D12QueryHeap() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12QueryHeap.</returns>
            virtual Guid GetGuid() override;
        };
    }
}