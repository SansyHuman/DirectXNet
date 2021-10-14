using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DirectXNet.Common;

namespace DirectXNet.DirectX12
{
    public static class D3D12DeviceExtension
    {
        public static Result CheckFeatureSupport<T>(
            this D3D12Device obj, ref T featureSupportData) where T : struct, ID3D12FeatureData
        {
            return obj.CheckFeatureSupport<T>(featureSupportData.FeatureType, ref featureSupportData);
        }

        public static Result CreateCommandAllocatorAndList<T>(
            this D3D12Device obj, uint nodeMask, D3D12CommandListType type,
            out D3D12CommandAllocator commandAllocator, out T commandList,
            D3D12PipelineState initialState = null) where T : D3D12CommandList
        {
            D3D12CommandAllocator alloc = null;
            T list = null;

            try
            {
                alloc = obj.CreateCommandAllocator(type);
                list = obj.CreateCommandList<T>(nodeMask, type, alloc, initialState);

                commandAllocator = alloc;
                commandList = list;

                return new Result(0);
            }
            catch (Exception e)
            {
                if (alloc != null)
                    alloc.Dispose();
                if (list != null)
                    list.Dispose();

                commandAllocator = null;
                commandList = null;

                return new Result(e.HResult);
            }
        }

        public static D3D12RootSignature CreateRootSignature(
            this D3D12Device obj, uint nodeMask, D3D10Blob blobWithRootSignature)
        {
            return obj.CreateRootSignature(
                nodeMask, blobWithRootSignature.BufferPointer, blobWithRootSignature.BufferSize);
        }
    }
}
