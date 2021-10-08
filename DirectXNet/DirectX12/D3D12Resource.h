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
        /// Encapsulates a generalized ability of the CPU and GPU to read and write to physical memory,
        /// or heaps. It contains abstractions for organizing and manipulating simple arrays of data
        /// as well as multidimensional data optimized for shader sampling.
        /// </summary>
        public ref class D3D12Resource : D3D12Pageable
        {
        private:
            ::ID3D12Resource* pResource;

        internal:
            D3D12Resource(::ID3D12Resource* pResource);
            D3D12Resource() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Resource.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the native resource pointer. This does not increase the reference count of the
            /// resource. Do not use this other than filling some structs.
            /// </summary>
            property IntPtr NativeResource
            {
                IntPtr get();
            }

            /// <summary>
            /// Gets a CPU pointer to the specified subresource in the resource, but may not disclose
            /// the pointer value to applications. Map also invalidates the CPU cache, when necessary,
            /// so that CPU reads to this address reflect any modifications made by the GPU.
            /// </summary>
            /// <param name="subresource">Specifies the index number of the subresource.</param>
            /// <param name="readRange">An optional D3D12_RANGE structure that describes the range
            /// of memory to access.
            /// This indicates the region the CPU might read, and the coordinates are subresource -
            /// relative. A null pointer indicates the entire subresource might be read by the CPU. It
            /// is valid to specify the CPU won't read any data by passing a range where End is less
            /// than or equal to Begin.</param>
            /// <returns>A pointer to the resource data if succeeded.</returns>
            IntPtr Map(
                unsigned int subresource,
                Nullable<D3D12Range> readRange
            );

            /// <summary>
            /// Cache a CPU virtual address range of the resource.
            /// </summary>
            /// <param name="subresource">Specifies the index number of the subresource.</param>
            /// <returns>Address range if succeeded.</returns>
            D3D12Range Map(unsigned int subresource);

            /// <summary>
            /// Invalidates the CPU pointer to the specified subresource in the resource.
            /// </summary>
            /// <param name="subresource">Specifies the index of the subresource.</param>
            /// <param name="writtenRange">An optional D3D12Range structure that describes the range
            /// of memory to unmap.
            /// This indicates the region the CPU might have modified, and the coordinates are
            /// subresource - relative. A null pointer indicates the entire subresource might have been
            /// modified by the CPU. It is valid to specify the CPU didn't write any data by passing
            /// a range where End is less than or equal to Begin.</param>
            void Unmap(
                unsigned int subresource,
                [Optional] Nullable<D3D12Range> writtenRange
            );

            /// <summary>
            /// Gets the resource description.
            /// </summary>
            property D3D12ResourceDesc ResourceDesc
            {
                D3D12ResourceDesc get();
            }

            /// <summary>
            /// Gets the GPU virtual address of a buffer resource.
            /// </summary>
            property D3D12_GPU_VIRTUAL_ADDRESS GPUVirtualAddresss
            {
                D3D12_GPU_VIRTUAL_ADDRESS get();
            }

            /// <summary>
            /// Uses the CPU to copy data into a subresource, enabling the CPU to modify the contents
            /// of most textures with undefined layouts.
            /// </summary>
            /// <param name="srcData">A pointer to the source data in memory.</param>
            /// <param name="srcRowPitch">The distance from one row of source data to the next row.
            /// </param>
            /// <param name="srcDepthPitch">The distance from one depth slice of source data to
            /// the next.</param>
            /// <param name="dstSubresource">Specifies the index of the subresource.</param>
            /// <param name="dstBox">A box that defines the portion of the destination subresource
            /// to copy the resource data into. If null, the data is written to the destination
            /// subresource with no offset.</param>
            /// <returns>Result code.</returns>
            Result WriteToSubresource(
                IntPtr srcData,
                unsigned int srcRowPitch,
                unsigned int srcDepthPitch,
                unsigned int dstSubresource,
                [Optional] Nullable<D3D12Box> dstBox
            );

            /// <summary>
            /// Uses the CPU to copy data from a subresource, enabling the CPU to read the contents
            /// of most textures with undefined layouts.
            /// </summary>
            /// <param name="dstData">A pointer to the destination data in memory.</param>
            /// <param name="dstRowPitch">The distance from one row of destination data to the
            /// next row.</param>
            /// <param name="dstDepthPitch">The distance from one depth slice of destination data to
            /// the next.</param>
            /// <param name="srcSubresource">Specifies the index of the subresource to read from.</param>
            /// <param name="srcBox">A box that defines the portion of the destination subresource
            /// to copy the resource data from. If null, the data is read from the destination
            /// subresource with no offset.</param>
            /// <returns>Result code.</returns>
            Result ReadFromSubresource(
                [In][IsReadOnly] IntPtr% dstData,
                unsigned int dstRowPitch,
                unsigned int dstDepthPitch,
                unsigned int srcSubresource,
                [Optional] Nullable<D3D12Box> srcBox
            );

            /// <summary>
            /// Retrieves the properties of the resource heap, for placed and committed resources.
            /// </summary>
            /// <param name="heapProperties">Reference to a D3D12HeapProperties structure, that
            /// on successful completion of the method will contain the resource heap properties.</param>
            /// <param name="heapFlags">Specifies a D3D12HeapFlags variable, that on
            /// successful completion of the method will contain any miscellaneous heap flags.</param>
            /// <returns>Result code.</returns>
            Result GetHeapProperties(
                [Out] D3D12HeapProperties% heapProperties,
                [Out] D3D12HeapFlags% heapFlags
            );
        };
    }
}