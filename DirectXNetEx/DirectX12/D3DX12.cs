using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using DirectXNet.DXGI;
using DirectXNet.Common.D3D;
using System.Buffers;

namespace DirectXNet.DirectX12
{
    public static class D3DX12
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static uint CalcSubresource(
            uint mipSlice,
            uint arraySlice,
            uint planeSlice,
            uint mipLevels,
            uint arraySize
        )
        {
            return mipSlice + arraySlice * mipLevels + planeSlice * mipLevels * arraySize;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void DecomposeSubresource(
            uint subresource,
            uint mipLevels,
            uint arraySize,
            out uint mipSlice,
            out uint arraySlice,
            out uint planeSlice
        )
        {
            mipSlice = subresource % mipLevels;
            arraySlice = (subresource / mipLevels) % arraySize;
            planeSlice = subresource / (mipLevels * arraySize);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static byte GetFormatPlaneCount(D3D12Device device, DXGIFormat format)
        {
            D3D12FeatureDataFormatInfo formatInfo = new D3D12FeatureDataFormatInfo(format);
            if ((device.CheckFeatureSupport(D3D12Feature.FormatInfo, ref formatInfo)).Failed)
                return 0;
            return formatInfo.PlaneCount;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static bool IsLayoutOpaque(D3D12TextureLayout layout)
        {
            return layout == D3D12TextureLayout.Unknown || layout == D3D12TextureLayout.Layout64KBUndefinedSwizzle;
        }

        public static unsafe ulong GetRequiredIntermediateSize(
            D3D12Resource destinationResource,
            uint firstSubresource,
            uint numSubresources
        )
        {
            var desc = destinationResource.ResourceDesc;
            ulong requiredSize = 0;

            using (D3D12Device device = destinationResource.GetDevice<D3D12Device>())
            {
                device.GetCopyableFootprints(&desc, firstSubresource, numSubresources, 0, null, null, null, &requiredSize);
            }
            return requiredSize;
        }

        public static unsafe void MemcpySubresource(
            in D3D12MemcpyDest dest,
            in D3D12SubresourceData src,
            ulong rowSizeInBytes,
            uint numRows,
            uint numSlices
        )
        {
            for (uint z = 0; z < numSlices; ++z)
            {
                var pDestSlice = (byte*)dest.pData.ToPointer() + dest.SlicePitch * z;
                var pSrcSlice = (byte*)src.pData.ToPointer() + src.SlicePitch * (long)z;
                for (uint y = 0; y < numRows; ++y)
                {
                    Buffer.MemoryCopy(
                        (void*)(pSrcSlice + src.RowPitch * (long)y),
                        (void*)(pDestSlice + dest.RowPitch * y),
                        rowSizeInBytes,
                        rowSizeInBytes);
                }
            }
        }

        public static unsafe void MemcpySubresource(
            in D3D12MemcpyDest dest,
            IntPtr pResourceData,
            in D3D12SubresourceInfo src,
            ulong rowSizeInBytes,
            uint numRows,
            uint numSlices
        )
        {
            for (uint z = 0; z < numSlices; ++z)
            {
                var pDestSlice = (byte*)dest.pData.ToPointer() + dest.SlicePitch * z;
                var pSrcSlice = ((byte*)pResourceData.ToPointer() + src.Offset) + (ulong)src.DepthPitch * (ulong)z;
                for (uint y = 0; y < numRows; ++y)
                {
                    Buffer.MemoryCopy(
                        (void*)(pSrcSlice + (ulong)src.RowPitch * (ulong)y),
                        (void*)(pDestSlice + dest.RowPitch * y),
                        rowSizeInBytes,
                        rowSizeInBytes);
                }
            }
        }

        public static ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            uint firstSubresource,
            uint numSubresources,
            ulong requiredSize,
            D3D12PlacedSubresourceFootprint[] layouts,
            uint[] numRows,
            ulong[] rowSizesInBytes,
            D3D12SubresourceData[] srcData
        )
        {
            D3D12ResourceDesc IntermediateDesc = intermediate.ResourceDesc;
            D3D12ResourceDesc DestinationDesc = destinationResource.ResourceDesc;
            if (IntermediateDesc.Dimension != D3D12ResourceDimension.Buffer ||
               IntermediateDesc.Width < requiredSize + layouts[0].Offset ||
               requiredSize > unchecked((ulong)-1) ||
               (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer &&
                (firstSubresource != 0 || numSubresources != 1)))
            {
                return 0;
            }

            IntPtr pData = IntPtr.Zero;

            try
            {
                pData = intermediate.Map(0, null);
            }
            catch (Exception)
            {
                return 0;
            }

            for (uint i = 0; i < numSubresources; ++i)
            {
                if (rowSizesInBytes[i] > unchecked((ulong)-1))
                    return 0;
                D3D12MemcpyDest DestData = new D3D12MemcpyDest 
                { 
                    pData = pData + (int)layouts[i].Offset,
                    RowPitch = layouts[i].Footprint.RowPitch,
                    SlicePitch = (ulong)layouts[i].Footprint.RowPitch * (ulong)numRows[i]
                };
                D3DX12.MemcpySubresource(DestData, srcData[i], (ulong)rowSizesInBytes[i], numRows[i], layouts[i].Footprint.Depth);
            }
            intermediate.Unmap(0);

            if (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer)
            {
                cmdList.CopyBufferRegion(
                    destinationResource, 0, intermediate, layouts[0].Offset, layouts[0].Footprint.Width);
            }
            else
            {
                for (uint i = 0; i < numSubresources; ++i)
                {
                    D3D12TextureCopyLocation Dst = new D3D12TextureCopyLocation(destinationResource, i +firstSubresource);
                    D3D12TextureCopyLocation Src = new D3D12TextureCopyLocation(intermediate, layouts[i]);
                    cmdList.CopyTextureRegion(Dst, 0, 0, 0, Src);
                }
            }
            return requiredSize;
        }

        internal static unsafe ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            uint firstSubresource,
            uint numSubresources,
            ulong requiredSize,
            D3D12PlacedSubresourceFootprint* layouts,
            uint* numRows,
            ulong* rowSizesInBytes,
            D3D12SubresourceData[] srcData
        )
        {
            D3D12ResourceDesc IntermediateDesc = intermediate.ResourceDesc;
            D3D12ResourceDesc DestinationDesc = destinationResource.ResourceDesc;
            if (IntermediateDesc.Dimension != D3D12ResourceDimension.Buffer ||
               IntermediateDesc.Width < requiredSize + layouts[0].Offset ||
               requiredSize > unchecked((ulong)-1) ||
               (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer &&
                (firstSubresource != 0 || numSubresources != 1)))
            {
                return 0;
            }

            IntPtr pData = IntPtr.Zero;

            try
            {
                pData = intermediate.Map(0, null);
            }
            catch (Exception)
            {
                return 0;
            }

            for (uint i = 0; i < numSubresources; ++i)
            {
                if (rowSizesInBytes[i] > unchecked((ulong)-1))
                    return 0;
                D3D12MemcpyDest DestData = new D3D12MemcpyDest
                {
                    pData = pData + (int)layouts[i].Offset,
                    RowPitch = layouts[i].Footprint.RowPitch,
                    SlicePitch = (ulong)layouts[i].Footprint.RowPitch * (ulong)numRows[i]
                };
                D3DX12.MemcpySubresource(DestData, srcData[i], (ulong)rowSizesInBytes[i], numRows[i], layouts[i].Footprint.Depth);
            }
            intermediate.Unmap(0);

            if (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer)
            {
                cmdList.CopyBufferRegion(
                    destinationResource, 0, intermediate, layouts[0].Offset, layouts[0].Footprint.Width);
            }
            else
            {
                for (uint i = 0; i < numSubresources; ++i)
                {
                    D3D12TextureCopyLocation Dst = new D3D12TextureCopyLocation(destinationResource, i + firstSubresource);
                    D3D12TextureCopyLocation Src = new D3D12TextureCopyLocation(intermediate, layouts[i]);
                    cmdList.CopyTextureRegion(Dst, 0, 0, 0, Src);
                }
            }
            return requiredSize;
        }

        public static ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            uint firstSubresource,
            uint numSubresources,
            ulong requiredSize,
            D3D12PlacedSubresourceFootprint[] layouts,
            uint[] numRows,
            ulong[] rowSizesInBytes,
            IntPtr pResourceData,
            D3D12SubresourceInfo[] srcData
        )
        {
            D3D12ResourceDesc IntermediateDesc = intermediate.ResourceDesc;
            D3D12ResourceDesc DestinationDesc = destinationResource.ResourceDesc;
            if (IntermediateDesc.Dimension != D3D12ResourceDimension.Buffer ||
               IntermediateDesc.Width < requiredSize + layouts[0].Offset ||
               requiredSize > unchecked((ulong)-1) ||
               (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer &&
                (firstSubresource != 0 || numSubresources != 1)))
            {
                return 0;
            }

            IntPtr pData = IntPtr.Zero;

            try
            {
                pData = intermediate.Map(0, null);
            }
            catch (Exception)
            {
                return 0;
            }

            for (uint i = 0; i < numSubresources; ++i)
            {
                if (rowSizesInBytes[i] > unchecked((ulong)-1))
                    return 0;
                D3D12MemcpyDest DestData = new D3D12MemcpyDest
                {
                    pData = pData + (int)layouts[i].Offset,
                    RowPitch = layouts[i].Footprint.RowPitch,
                    SlicePitch = (ulong)layouts[i].Footprint.RowPitch * (ulong)numRows[i]
                };
                D3DX12.MemcpySubresource(DestData, pResourceData, srcData[i], (ulong)rowSizesInBytes[i], numRows[i], layouts[i].Footprint.Depth);
            }
            intermediate.Unmap(0);

            if (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer)
            {
                cmdList.CopyBufferRegion(
                    destinationResource, 0, intermediate, layouts[0].Offset, layouts[0].Footprint.Width);
            }
            else
            {
                for (uint i = 0; i < numSubresources; ++i)
                {
                    D3D12TextureCopyLocation Dst = new D3D12TextureCopyLocation(destinationResource, i + firstSubresource);
                    D3D12TextureCopyLocation Src = new D3D12TextureCopyLocation(intermediate, layouts[i]);
                    cmdList.CopyTextureRegion(Dst, 0, 0, 0, Src);
                }
            }
            return requiredSize;
        }

        internal static unsafe ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            uint firstSubresource,
            uint numSubresources,
            ulong requiredSize,
            D3D12PlacedSubresourceFootprint* layouts,
            uint* numRows,
            ulong* rowSizesInBytes,
            IntPtr pResourceData,
            D3D12SubresourceInfo[] srcData
        )
        {
            D3D12ResourceDesc IntermediateDesc = intermediate.ResourceDesc;
            D3D12ResourceDesc DestinationDesc = destinationResource.ResourceDesc;
            if (IntermediateDesc.Dimension != D3D12ResourceDimension.Buffer ||
               IntermediateDesc.Width < requiredSize + layouts[0].Offset ||
               requiredSize > unchecked((ulong)-1) ||
               (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer &&
                (firstSubresource != 0 || numSubresources != 1)))
            {
                return 0;
            }

            IntPtr pData = IntPtr.Zero;

            try
            {
                pData = intermediate.Map(0, null);
            }
            catch (Exception)
            {
                return 0;
            }

            for (uint i = 0; i < numSubresources; ++i)
            {
                if (rowSizesInBytes[i] > unchecked((ulong)-1))
                    return 0;
                D3D12MemcpyDest DestData = new D3D12MemcpyDest
                {
                    pData = pData + (int)layouts[i].Offset,
                    RowPitch = layouts[i].Footprint.RowPitch,
                    SlicePitch = (ulong)layouts[i].Footprint.RowPitch * (ulong)numRows[i]
                };
                D3DX12.MemcpySubresource(DestData, pResourceData, srcData[i], (ulong)rowSizesInBytes[i], numRows[i], layouts[i].Footprint.Depth);
            }
            intermediate.Unmap(0);

            if (DestinationDesc.Dimension == D3D12ResourceDimension.Buffer)
            {
                cmdList.CopyBufferRegion(
                    destinationResource, 0, intermediate, layouts[0].Offset, layouts[0].Footprint.Width);
            }
            else
            {
                for (uint i = 0; i < numSubresources; ++i)
                {
                    D3D12TextureCopyLocation Dst = new D3D12TextureCopyLocation(destinationResource, i + firstSubresource);
                    D3D12TextureCopyLocation Src = new D3D12TextureCopyLocation(intermediate, layouts[i]);
                    cmdList.CopyTextureRegion(Dst, 0, 0, 0, Src);
                }
            }
            return requiredSize;
        }

        public static unsafe ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            ulong intermediateOffset,
            uint firstSubresource,
            uint numSubresources,
            D3D12SubresourceData[] srcData
        )
        {
            ulong requiredSize = 0;
            var MemToAlloc = (ulong)(Marshal.SizeOf<D3D12PlacedSubresourceFootprint>() + sizeof(uint) + sizeof(ulong)) * numSubresources;
            if (MemToAlloc > ulong.MaxValue)
            {
                return 0;
            }

            IntPtr pMem = Marshal.AllocHGlobal((int)MemToAlloc);
            if (pMem == IntPtr.Zero)
                return 0;

            var pLayouts = (D3D12PlacedSubresourceFootprint*)pMem;
            var pRowSizesInBytes = (ulong*)(pLayouts + numSubresources);
            var pNumRows = (uint*)(pRowSizesInBytes + numSubresources);

            var Desc = destinationResource.ResourceDesc;
            using (D3D12Device device = destinationResource.GetDevice<D3D12Device>())
            {
                device.GetCopyableFootprints(&Desc, firstSubresource, numSubresources, intermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &requiredSize);
            }

            ulong Result = UpdateSubresources(cmdList, destinationResource, intermediate, firstSubresource, numSubresources, requiredSize, pLayouts, pNumRows, pRowSizesInBytes, srcData);
            Marshal.FreeHGlobal(pMem);

            return Result;
        }

        public static unsafe ulong UpdateSubresources(
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            ulong intermediateOffset,
            uint firstSubresource,
            uint numSubresources,
            IntPtr pResourceData,
            D3D12SubresourceInfo[] srcData
        )
        {
            ulong requiredSize = 0;
            var MemToAlloc = (ulong)(Marshal.SizeOf<D3D12PlacedSubresourceFootprint>() + sizeof(uint) + sizeof(ulong)) * numSubresources;
            if (MemToAlloc > ulong.MaxValue)
            {
                return 0;
            }

            IntPtr pMem = Marshal.AllocHGlobal((int)MemToAlloc);
            if (pMem == IntPtr.Zero)
                return 0;

            var pLayouts = (D3D12PlacedSubresourceFootprint*)pMem;
            var pRowSizesInBytes = (ulong*)(pLayouts + numSubresources);
            var pNumRows = (uint*)(pRowSizesInBytes + numSubresources);

            var Desc = destinationResource.ResourceDesc;
            using (D3D12Device device = destinationResource.GetDevice<D3D12Device>())
            {
                device.GetCopyableFootprints(&Desc, firstSubresource, numSubresources, intermediateOffset, pLayouts, pNumRows, pRowSizesInBytes, &requiredSize);
            }

            ulong Result = UpdateSubresources(cmdList, destinationResource, intermediate, firstSubresource, numSubresources, requiredSize, pLayouts, pNumRows, pRowSizesInBytes, pResourceData, srcData);
            Marshal.FreeHGlobal(pMem);

            return Result;
        }

        public static unsafe ulong UpdateSubresources(
            uint maxSubresources,
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            ulong intermediateOffset,
            uint firstSubresource,
            uint numSubresources,
            D3D12SubresourceData[] srcData
        )
        {
            ulong requiredSize = 0;
            D3D12PlacedSubresourceFootprint* Layouts = stackalloc D3D12PlacedSubresourceFootprint[(int)maxSubresources];
            uint* NumRows = stackalloc uint[(int)maxSubresources];
            ulong* RowSizesInBytes = stackalloc ulong[(int)maxSubresources];

            var Desc = destinationResource.ResourceDesc;
            using (D3D12Device device = destinationResource.GetDevice<D3D12Device>())
            {
                device.GetCopyableFootprints(&Desc, firstSubresource, numSubresources, intermediateOffset, Layouts, NumRows, RowSizesInBytes, &requiredSize);
            }

            return UpdateSubresources(cmdList, destinationResource, intermediate, firstSubresource, numSubresources, requiredSize, Layouts, NumRows, RowSizesInBytes, srcData);
        }

        public static unsafe ulong UpdateSubresources(
            uint maxSubresources,
            D3D12GraphicsCommandList cmdList,
            D3D12Resource destinationResource,
            D3D12Resource intermediate,
            ulong intermediateOffset,
            uint firstSubresource,
            IntPtr pResourceData,
            uint numSubresources,
            D3D12SubresourceInfo[] srcData
        )
        {
            ulong requiredSize = 0;
            D3D12PlacedSubresourceFootprint* Layouts = stackalloc D3D12PlacedSubresourceFootprint[(int)maxSubresources];
            uint* NumRows = stackalloc uint[(int)maxSubresources];
            ulong* RowSizesInBytes = stackalloc ulong[(int)maxSubresources];

            var Desc = destinationResource.ResourceDesc;
            using (D3D12Device device = destinationResource.GetDevice<D3D12Device>())
            {
                device.GetCopyableFootprints(&Desc, firstSubresource, numSubresources, intermediateOffset, Layouts, NumRows, RowSizesInBytes, &requiredSize);
            }

            return UpdateSubresources(cmdList, destinationResource, intermediate, firstSubresource, numSubresources, requiredSize, Layouts, NumRows, RowSizesInBytes, pResourceData, srcData);
        }
    }
}
