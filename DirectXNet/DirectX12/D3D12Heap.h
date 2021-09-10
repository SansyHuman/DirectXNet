#pragma once

#include "../pch.h"
#include "D3D12Pageable.h"
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
        /// An interface from which many other core interfaces inherit from. It indicates that the
        /// object type encapsulates some amount of GPU-accessible memory; but does not strongly
        /// indicate whether the application can manipulate the object's residency.
        /// </summary>
        public ref class D3D12Heap : D3D12Pageable
        {
        private:
            ::ID3D12Heap* pHeap;

        internal:
            D3D12Heap(::ID3D12Heap* pHeap);
            D3D12Heap() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Heap.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the heap description.
            /// </summary>
            property D3D12HeapDesc HeapDesc
            {
                D3D12HeapDesc get();
            }
        };
    }
}