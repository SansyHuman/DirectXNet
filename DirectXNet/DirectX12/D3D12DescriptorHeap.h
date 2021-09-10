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
        /// A descriptor heap is a collection of contiguous allocations of descriptors, one allocation
        /// for every descriptor. Descriptor heaps contain many object types that are not part of a
        /// Pipeline State Object (PSO), such as Shader Resource Views (SRVs), Unordered Access Views
        /// (UAVs), Constant Buffer Views (CBVs), and Samplers.
        /// </summary>
        public ref class D3D12DescriptorHeap : D3D12Pageable
        {
        private:
            ::ID3D12DescriptorHeap* pHeap;

        internal:
            D3D12DescriptorHeap(::ID3D12DescriptorHeap* pHeap);
            D3D12DescriptorHeap() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12DescriptorHeap.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the descriptor heap description.
            /// </summary>
            property D3D12DescriptorHeapDesc DescriptorHeapDesc
            {
                D3D12DescriptorHeapDesc get();
            }

            /// <summary>
            /// Gets the CPU descriptor handle that represents the start of the heap.
            /// </summary>
            property D3D12CPUDescriptorHandle CPUDescriptorHandleForHeapStart
            {
                D3D12CPUDescriptorHandle get();
            }

            /// <summary>
            /// Gets the GPU descriptor handle that represents the start of the heap.
            /// </summary>
            property D3D12GPUDescriptorHandle GPUDescriptorHandleForHeapStart
            {
                D3D12GPUDescriptorHandle get();
            }
        };
    }
}