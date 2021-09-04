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
        ref class D3D12Resource;
        ref class D3D12Heap;
        ref class D3D12CommandList;
        ref class D3D12Fence;

        /// <summary>
        /// Provides methods for submitting command lists, synchronizing command list execution,
        /// instrumenting the command queue, and updating resource tile mappings.
        /// </summary>
        public ref class D3D12CommandQueue : D3D12Pageable
        {
        private:
            com::ptr<::ID3D12CommandQueue> pQueue;

        internal:
            D3D12CommandQueue(::ID3D12CommandQueue* pQueue);
            D3D12CommandQueue() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12CommandQueue.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Updates mappings of tile locations in reserved resources to memory locations in
            /// a resource heap.
            /// </summary>
            /// <param name="resource">The reserved resource.</param>
            /// <param name="numResourceRegions">The number of reserved resource regions.</param>
            /// <param name="numRanges">The number of tile ranges.</param>
            /// <param name="flags">A combination of D3D12TileMappingFlags values that are combined
            /// by using a bitwise OR operation.</param>
            /// <param name="resourceRegionStartCoordinates">An array of D3D12TiledResourceCoordinate
            /// structures that describe the starting coordinates of the reserved resource regions.
            /// The numResourceRegions parameter specifies the number of D3D12TiledResourceCoordinate
            /// structures in the array. If numResourceRegions is 1, for convenience this can be null.
            /// Null for resourceRegionStartCoordinates means the start coordinate is all 0s.</param>
            /// <param name="resourceRegionSizes">An array of D3D12TileRegionSize structures that
            /// describe the sizes of the reserved resource regions. The numResourceRegions parameter
            /// specifies the number of D3D12TileRegionSize structures in the array. If
            /// numResourceRegions is 1, for convenience this can be null. Null for resourceRegionSizes
            /// identifies a default region that is the full set of tiles for the entire reserved
            /// resource, including all mipmaps, array slices, or both. If resourceRegionStartCoordinates
            /// isn't null and resourceRegionSizes is null, the region size defaults to 1 tile for all
            /// regions. This makes it easy to define mappings for a set of individual tiles each at
            /// disparate locations by providing an array of locations in resourceRegionStartCoordinates
            /// without having to send an array of resourceRegionSizes all set to 1.</param>
            /// <param name="heap">A resource heap. Heap provides memory where tile mappings can go.
            /// If UpdateTileMappings only defines NULL mappings, you don't need to specify a heap.
            /// </param>
            /// <param name="rangeFlags">An array of D3D12TileRangeFlags values that describes each
            /// tile range. The numRanges parameter specifies the number of values in the array. If
            /// rangeFlags is null, all ranges are sequential tiles in the heap/</param>
            /// <param name="heapRangeStartOffsets">An array of offsets into the resource heap.
            /// These are 0-based tile offsets, counting in tiles (not bytes).</param>
            /// <param name="rangeTileCounts">An array of tiles. An array of values that specify the
            /// number of tiles in each tile range. The NumRanges parameter specifies the number of
            /// values in the array.</param>
            void UpdateTileMappings(
                D3D12Resource^ resource,
                unsigned int numResourceRegions,
                unsigned int numRanges,
                D3D12TileMappingFlags flags,
                [Optional] array<D3D12TiledResourceCoordinate>^ resourceRegionStartCoordinates,
                [Optional] array<D3D12TileRegionSize>^ resourceRegionSizes,
                [Optional] D3D12Heap^ heap,
                [Optional] array<D3D12TileRangeFlags>^ rangeFlags,
                [Optional] array<unsigned int>^ heapRangeStartOffsets,
                [Optional] array<unsigned int>^ rangeTileCounts
            );

            /// <summary>
            /// Copies mappings from a source reserved resource to a destination reserved resource.
            /// </summary>
            /// <param name="dstResource">A destination reserved resource.</param>
            /// <param name="dstRegionStartCoordinate">A D3D12TiledResourceCoordinate structure that
            /// describes the starting coordinates of the destination reserved resource.</param>
            /// <param name="srcResource">A source reserved resource.</param>
            /// <param name="srcRegionStartCoordinate">A D3D12TiledResourceCoordinate structure that
            /// describes the starting coordinates of the source reserved resource.</param>
            /// <param name="regionSize">A D3D12TileRegionSize structure that describes the size of
            /// the reserved region.</param>
            /// <param name="flags">One member of D3D12TileMappingFlags.</param>
            void CopyTileMappings(
                D3D12Resource^ dstResource,
                [In][IsReadOnly] D3D12TiledResourceCoordinate% dstRegionStartCoordinate,
                D3D12Resource^ srcResource,
                [In][IsReadOnly] D3D12TiledResourceCoordinate% srcRegionStartCoordinate,
                [In][IsReadOnly] D3D12TileRegionSize% regionSize,
                D3D12TileMappingFlags flags
            );

            /// <summary>
            /// Submits an array of command lists for execution.
            /// </summary>
            /// <param name="commandLists">D3D12CommandList command lists to be executed.</param>
            void ExecuteCommandLists(
                ...array<D3D12CommandList^>^ commandLists
            );

            /// <summary>
            /// Not intended to be called directly. Use the PIX event runtime to insert events into
            /// a command queue.
            /// </summary>
            /// <param name="metadata"></param>
            /// <param name="pData"></param>
            /// <param name="size"></param>
            [Obsolete("Not intended to be called directly. Use the PIX event runtime to insert events into a command queue.")]
            void SetMarker(unsigned int metadata, void* pData, unsigned int size);

            /// <summary>
            /// Not intended to be called directly. Use the PIX event runtime to insert events into
            /// a command queue.
            /// </summary>
            /// <param name="metadata"></param>
            /// <param name="pData"></param>
            /// <param name="size"></param>
            [Obsolete("Not intended to be called directly. Use the PIX event runtime to insert events into a command queue.")]
            void BeginEvent(unsigned int metadata, void* pData, unsigned int size);

            /// <summary>
            /// Not intended to be called directly. Use the PIX event runtime to insert events into
            /// a command queue.
            /// </summary>
            [Obsolete("Not intended to be called directly. Use the PIX event runtime to insert events into a command queue.")]
            void EndEvent();

            /// <summary>
            /// Updates a fence to a specified value.
            /// </summary>
            /// <param name="fence">A D3D12Fence object.</param>
            /// <param name="value">The value to set the fence to.</param>
            /// <returns>Result code.</returns>
            Result Signal(D3D12Fence^ fence, unsigned long long value);

            /// <summary>
            /// Queues a GPU-side wait, and returns immediately. A GPU-side wait is where the GPU
            /// waits until the specified fence reaches or exceeds the specified value.
            /// </summary>
            /// <param name="fence">A D3D12Fence object.</param>
            /// <param name="value">The value that the command queue is waiting for the fence to reach
            /// or exceed. So when D3D12Fence::CompletedValue is greater than or equal to Value, the
            /// wait is terminated.</param>
            /// <returns>Result code.</returns>
            Result Wait(D3D12Fence^ fence, unsigned long long value);

            /// <summary>
            /// Gets the rate at which the GPU timestamp counter increments.
            /// </summary>
            property unsigned long long TimestampFrequency
            {
                unsigned long long get();
            }

            /// <summary>
            /// This method samples the CPU and GPU timestamp counters at the same moment in time.
            /// </summary>
            /// <param name="gpuTimestamp">The value of the GPU timestamp counter.</param>
            /// <param name="cpuTimestamp">The value of the CPU timestamp counter.</param>
            /// <returns>Result code.</returns>
            Result GetClockCalibration(
                [Out] unsigned long long% gpuTimestamp,
                [Out] unsigned long long% cpuTimestamp
            );

            /// <summary>
            /// Gets the description of the command queue.
            /// </summary>
            property D3D12CommandQueueDesc CommandQueueDesc
            {
                D3D12CommandQueueDesc get();
            }
        };
    }
}