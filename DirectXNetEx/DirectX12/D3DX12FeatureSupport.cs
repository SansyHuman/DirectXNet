using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

using DirectXNet.Common;
using DirectXNet.Common.D3D;
using DirectXNet.DXGI;

namespace DirectXNet.DirectX12
{
    public class D3DX12FeatureSupport
    {
        private struct ProtectedResourceSessionTypesLocal
        {
            public D3D12FeatureDataProtectedResourceSessionTypes Types;
            public Guid[] TypeVec;
        }

        private D3D12Device device;
        private Result status;

        private D3D12FeatureDataD3D12Options options;
        private D3DFeatureLevel maxFeatureLevel;
        private D3D12FeatureDataGPUVirtualAddressSupport gpuVASupport;
        private D3D12FeatureDataShaderModel shaderModel;
        private D3D12FeatureDataD3D12Options1 options1;
        private D3D12FeatureDataProtectedResourceSessionSupport[] protectedResourceSessionSupport;
        private D3D12FeatureDataRootSignature rootSignature;
        private D3D12FeatureDataArchitecture1[] architecture1;
        private D3D12FeatureDataD3D12Options2 options2;
        private D3D12FeatureDataShaderCache shaderCache;
        private D3D12FeatureDataCommandQueuePriority commandQueuePriority;
        private D3D12FeatureDataD3D12Options3 options3;
        private D3D12FeatureDataExistingHeaps existingHeaps;
        private D3D12FeatureDataD3D12Options4 options4;
        private D3D12FeatureDataSerialization[] serialization;
        private D3D12FeatureDataCrossNode crossNode;
        private D3D12FeatureDataD3D12Options5 options5;
        private D3D12FeatureDataD3D12Options6 options6;
        private D3D12FeatureDataD3D12Options7 options7;
        private D3D12FeatureDataProtectedResourceSessionTypeCount[] protectedResourceSessionTypeCount;
        private ProtectedResourceSessionTypesLocal[] protectedResourceSessionTypes;
        private D3D12FeatureDataD3D12Options8 options8;
        private D3D12FeatureDataD3D12Options9 options9;

        private const int E_INVALIDARG = unchecked((int)0x80070057);
        private const int DXGI_ERROR_UNSUPPORTED = unchecked((int)0x887A0004);
        private const int S_OK = 0;

        private Result QueryHighestShaderModel()
        {
            Result result;

            D3DShaderModel[] allModelVersions =
            {
                D3DShaderModel.ShaderModel6_7,
                D3DShaderModel.ShaderModel6_6,
                D3DShaderModel.ShaderModel6_5,
                D3DShaderModel.ShaderModel6_4,
                D3DShaderModel.ShaderModel6_3,
                D3DShaderModel.ShaderModel6_2,
                D3DShaderModel.ShaderModel6_1,
                D3DShaderModel.ShaderModel6_0,
                D3DShaderModel.ShaderModel5_1
            };

            for (int i = 0; i < allModelVersions.Length; i++)
            {
                shaderModel.HighestShaderModel = allModelVersions[i];
                result = device.CheckFeatureSupport(D3D12Feature.ShaderModel, ref shaderModel);
                if (result.result != E_INVALIDARG)
                {
                    if (result.Failed)
                    {
                        shaderModel.HighestShaderModel = (D3DShaderModel)0;
                    }
                    return result;
                }
            }

            shaderModel.HighestShaderModel = (D3DShaderModel)0;
            return new Result(S_OK);
        }

        private Result QueryHighestRootSignatureVersion()
        {
            Result result;

            D3DRootSignatureVersion[] allRootSignatureVersions =
            {
                D3DRootSignatureVersion.Version1_1,
                D3DRootSignatureVersion.Version1_0,
                D3DRootSignatureVersion.Version1
            };

            for (int i = 0; i < allRootSignatureVersions.Length; i++)
            {
                rootSignature.HighestVersion = allRootSignatureVersions[i];
                result = device.CheckFeatureSupport(D3D12Feature.RootSignature, ref rootSignature);
                if (result.result != E_INVALIDARG)
                {
                    if (result.Failed)
                    {
                        rootSignature.HighestVersion = (D3DRootSignatureVersion)0;
                    }
                    return result;
                }
            }

            rootSignature.HighestVersion = (D3DRootSignatureVersion)0;
            return new Result(S_OK);
        }

        private Result QueryHighestFeatureLevel()
        {
            Result result;

            D3DFeatureLevel[] allLevels =
            {
                D3DFeatureLevel.Level12_2,
                D3DFeatureLevel.Level12_1,
                D3DFeatureLevel.Level12_0,
                D3DFeatureLevel.Level11_1,
                D3DFeatureLevel.Level11_0,
                D3DFeatureLevel.Level10_1,
                D3DFeatureLevel.Level10_0,
                D3DFeatureLevel.Level9_3,
                D3DFeatureLevel.Level9_2,
                D3DFeatureLevel.Level9_1,
                D3DFeatureLevel.Level1_0Core
            };

            GCHandle pinptr = new GCHandle();
            try
            {
                D3D12FeatureDataFeatureLevels featureLevel = new D3D12FeatureDataFeatureLevels(allLevels, out pinptr);

                result = device.CheckFeatureSupport(D3D12Feature.FeatureLevels, ref featureLevel);
                if (result.Succeeded)
                {
                    maxFeatureLevel = featureLevel.MaxSupportedFeatureLevel;
                }
                else
                {
                    maxFeatureLevel = (D3DFeatureLevel)0;

                    if (result.result == DXGI_ERROR_UNSUPPORTED)
                    {
                        result = new Result(S_OK);
                    }
                }

                return result;
            }
            finally
            {
                if (pinptr.IsAllocated)
                    pinptr.Free();
            }
        }

        private Result QueryProtectedResourceSessionTypes(int nodeIndex, uint count)
        {
            unsafe
            {
                var protectedResourceSessionTypesTmp = new ProtectedResourceSessionTypesLocal();
                protectedResourceSessionTypesTmp.TypeVec = new Guid[count];

                GCHandle pinptr = new GCHandle();

                try
                {
                    protectedResourceSessionTypesTmp.Types = new D3D12FeatureDataProtectedResourceSessionTypes(
                        (uint)nodeIndex, protectedResourceSessionTypesTmp.TypeVec, out pinptr);

                    Result result = device.CheckFeatureSupport(
                        D3D12Feature.ProtectedResourceSessionTypes, ref protectedResourceSessionTypesTmp.Types);
                    if (result.Failed)
                    {
                        protectedResourceSessionTypesTmp.TypeVec = new Guid[0];
                    }

                    protectedResourceSessionTypesTmp.Types.pTypes = null;
                    protectedResourceSessionTypes[nodeIndex] = protectedResourceSessionTypesTmp;

                    return result;
                }
                finally
                {
                    if (pinptr.IsAllocated)
                        pinptr.Free();
                }
            }
        }

        public D3DX12FeatureSupport()
        {
            device = null;
            status = new Result(E_INVALIDARG);
        }

        public Result Init(D3D12Device device)
        {
            if (device == null)
            {
                status = new Result(E_INVALIDARG);
                return status;
            }

            this.device = device;

            if(this.device.CheckFeatureSupport(D3D12Feature.D3D12Options, ref options).Failed)
            {
                options.DoublePrecisionFloatShaderOps = CBool.False;
                options.OutputMergerLogicOp = CBool.False;
                options.MinPrecisionSupport = D3D12ShaderMinPrecisionSupport.None;
                options.TiledResourcesTier = D3D12TiledResourceTier.NotSupported;
                options.ResourceBindingTier = (D3D12ResourceBindingTier)0;
                options.PSSpecifiedStencilRefSupported = CBool.False;
                options.TypedUAVLoadAdditionalFormats = CBool.False;
                options.ROVsSupported = CBool.False;
                options.ConservativeRasterizationTier = D3D12ConservativeRasterizationTier.NotSupported;
                options.MaxGPUVirtualAddressBitsPerResource = 0;
                options.StandardSwizzle64KBSupported = CBool.False;
                options.CrossNodeSharingTier = D3D12CrossNodeSharingTier.NotSupported;
                options.CrossAdapterRowMajorTextureSupported = CBool.False;
                options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation = CBool.False;
                options.ResourceHeapTier = (D3D12ResourceHeapTier)0;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.GpuVirtualAddressSupport, ref gpuVASupport).Failed)
            {
                gpuVASupport.MaxGPUVirtualAddressBitsPerProcess = 0;
                gpuVASupport.MaxGPUVirtualAddressBitsPerResource = 0;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options1, ref options1).Failed)
            {
                options1.WaveOps = CBool.False;
                options1.WaveLaneCountMax = 0;
                options1.WaveLaneCountMin = 0;
                options1.TotalLaneCount = 0;
                options1.ExpandedComputeResourceStates = 0;
                options1.Int64ShaderOps = 0;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options2, ref options2).Failed)
            {
                options2.DepthBoundsTestSupported = CBool.False;
                options2.ProgrammableSamplePositionsTier = D3D12ProgrammableSamplePositionsTier.NotSupported;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.ShaderCache, ref shaderCache).Failed)
            {
                shaderCache.SupportFlags = D3D12ShaderCacheSupportFlags.None;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options3, ref options3).Failed)
            {
                options3.CopyQueueTimestampQueriesSupported = CBool.False;
                options3.CastingFullyTypedFormatSupported = CBool.False;
                options3.WriteBufferImmediateSupportFlags = D3D12CommandListSupportFlags.None;
                options3.ViewInstancingTier = D3D12ViewInstancingTier.NotSupported;
                options3.BarycentricsSupported = CBool.False;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.ExistingHeaps, ref existingHeaps).Failed)
            {
                existingHeaps.Supported = CBool.False;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options4, ref options4).Failed)
            {
                options4.MSAA64KBAlignedTextureSupported = CBool.False;
                options4.Native16BitShaderOpsSupported = CBool.False;
                options4.SharedResourceCompatibilityTier = D3D12SharedResourceCompatibilityTier.Tier0;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.CrossNode, ref crossNode).Failed)
            {
                crossNode.SharingTier = D3D12CrossNodeSharingTier.NotSupported;
                crossNode.AtomicShaderInstructions = CBool.False;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options5, ref options5).Failed)
            {
                options5.SRVOnlyTiledResourceTier3 = CBool.False;
                options5.RenderPassesTier = D3D12RenderPassTier.Tier0;
                options5.RaytracingTier = D3D12RaytracingTier.NotSupported;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options6, ref options6).Failed)
            {
                options6.AdditionalShadingRatesSupported = CBool.False;
                options6.PerPrimitiveShadingRateSupportedWithViewportIndexing = CBool.False;
                options6.VariableShadingRateTier = D3D12VariableShadingRateTier.NotSupported;
                options6.ShadingRateImageTileSize = 0;
                options6.BackgroundProcessingSupported = CBool.False;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options7, ref options7).Failed)
            {
                options7.MeshShaderTier = D3D12MeshShaderTier.NotSupported;
                options7.SamplerFeedbackTier = D3D12SamplerFeedbackTier.NotSupported;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options8, ref options8).Failed)
            {
                options8.UnalignedBlockTexturesSupported = CBool.False;
            }

            if (this.device.CheckFeatureSupport(D3D12Feature.Options9, ref options9).Failed)
            {
                options9.MeshShaderPipelineStatsSupported = CBool.False;
                options9.MeshShaderSupportsFullRangeRenderTargetArrayIndex = CBool.False;
                options9.AtomicInt64OnGroupSharedSupported = CBool.False;
                options9.AtomicInt64OnTypedResourceSupported = CBool.False;
                options9.DerivativesInMeshAndAmplificationShadersSupported = CBool.False;
                options9.WaveMMATier = D3D12WaveMMATier.NotSupported;
            }

            int nodeCount = (int)this.device.NodeCount;

            protectedResourceSessionSupport = new D3D12FeatureDataProtectedResourceSessionSupport[nodeCount];
            architecture1 = new D3D12FeatureDataArchitecture1[nodeCount];
            serialization = new D3D12FeatureDataSerialization[nodeCount];
            protectedResourceSessionTypeCount = new D3D12FeatureDataProtectedResourceSessionTypeCount[nodeCount];
            protectedResourceSessionTypes = new ProtectedResourceSessionTypesLocal[nodeCount];

            for (int nodeIndex = 0; nodeIndex < nodeCount; nodeIndex++)
            {
                var protectedResourceSessionSupportTmp = new D3D12FeatureDataProtectedResourceSessionSupport((uint)nodeIndex);
                if (this.device.CheckFeatureSupport(D3D12Feature.ProtectedResourceSessionSupport, ref protectedResourceSessionSupportTmp).Failed)
                {
                    protectedResourceSessionSupportTmp.Support = D3D12ProtectedResourceSessionSupportFlags.None;
                }
                protectedResourceSessionSupport[nodeIndex] = protectedResourceSessionSupportTmp;

                var architecture1Tmp = new D3D12FeatureDataArchitecture1((uint)nodeIndex);
                if (this.device.CheckFeatureSupport(D3D12Feature.Architecture1, ref architecture1Tmp).Failed)
                {
                    D3D12FeatureDataArchitecture archLocal = new D3D12FeatureDataArchitecture((uint)nodeIndex);
                    if (this.device.CheckFeatureSupport(D3D12Feature.Architecture, ref archLocal).Failed)
                    {
                        archLocal.TileBasedRenderer = CBool.False;
                        archLocal.UMA = CBool.False;
                        archLocal.CacheCoherentUMA = CBool.False;
                    }

                    architecture1Tmp.TileBasedRenderer = archLocal.TileBasedRenderer;
                    architecture1Tmp.UMA = archLocal.UMA;
                    architecture1Tmp.CacheCoherentUMA = archLocal.CacheCoherentUMA;
                    architecture1Tmp.IsolatedMMU = CBool.False;
                }
                architecture1[nodeIndex] = architecture1Tmp;

                var serializationTmp = new D3D12FeatureDataSerialization((uint)nodeIndex);
                if (this.device.CheckFeatureSupport(D3D12Feature.Serialization, ref serializationTmp).Failed)
                {
                    serializationTmp.HeapSerializationTier = D3D12HeapSerializationTier.Tier0;
                }
                serialization[nodeIndex] = serializationTmp;

                var protectedResourceSessionTypeCountTmp = new D3D12FeatureDataProtectedResourceSessionTypeCount((uint)nodeIndex);
                if (this.device.CheckFeatureSupport(D3D12Feature.ProtectedResourceSessionTypeCount, ref protectedResourceSessionTypeCountTmp).Failed)
                {
                    protectedResourceSessionTypeCountTmp.Count = 0;
                }
                protectedResourceSessionTypeCount[nodeIndex] = protectedResourceSessionTypeCountTmp;

                if (protectedResourceSessionTypeCount[nodeIndex].Count > 0)
                {
                    QueryProtectedResourceSessionTypes(nodeIndex, protectedResourceSessionTypeCount[nodeIndex].Count);
                }
            }

            status = QueryHighestShaderModel();
            if (status.Failed)
                return status;

            status = QueryHighestRootSignatureVersion();
            if (status.Failed)
                return status;

            status = QueryHighestFeatureLevel();
            if (status.Failed)
                return status;

            return status;
        }

        public Result Status => status;

        public bool DoublePrecisionFloatShaderOps => (options.DoublePrecisionFloatShaderOps == CBool.True);

        public bool OutputMergerLogicOp => (options.OutputMergerLogicOp == CBool.True);

        public D3D12ShaderMinPrecisionSupport MinPrecisionSupport => options.MinPrecisionSupport;

        public D3D12TiledResourceTier TiledResourcesTier => options.TiledResourcesTier;

        public D3D12ResourceBindingTier ResourceBindingTier => options.ResourceBindingTier;

        public bool PSSpecifiedStencilRefSupported => (options.PSSpecifiedStencilRefSupported == CBool.True);

        public bool TypedUAVLoadAdditionalFormats => (options.TypedUAVLoadAdditionalFormats == CBool.True);

        public bool ROVsSupported => (options.ROVsSupported == CBool.True);

        public D3D12ConservativeRasterizationTier ConservativeRasterizationTier => options.ConservativeRasterizationTier;

        public bool StandardSwizzle64KBSupported => (options.StandardSwizzle64KBSupported == CBool.True);

        public bool CrossAdapterRowMajorTextureSupported => (options.CrossAdapterRowMajorTextureSupported == CBool.True);

        public bool VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation => (options.VPAndRTArrayIndexFromAnyShaderFeedingRasterizerSupportedWithoutGSEmulation == CBool.True);

        public D3D12ResourceHeapTier ResourceHeapTier => options.ResourceHeapTier;

        public D3D12CrossNodeSharingTier CrossNodeSharingTier
        {
            get
            {
                if (crossNode.SharingTier > D3D12CrossNodeSharingTier.NotSupported)
                {
                    return crossNode.SharingTier;
                }
                else
                {
                    return options.CrossNodeSharingTier;
                }
            }
        }

        public uint MaxGPUVirtualAddressBitsPerResource
        {
            get
            {
                if (options.MaxGPUVirtualAddressBitsPerResource > 0)
                {
                    return options.MaxGPUVirtualAddressBitsPerResource;
                }
                else
                {
                    return gpuVASupport.MaxGPUVirtualAddressBitsPerResource;
                }
            }
        }

        public D3DFeatureLevel MaxSupportedFeatureLevel => maxFeatureLevel;

        public Result FormatSupport(
            DXGIFormat format,
            out D3D12FormatSupport1 support1,
            out D3D12FormatSupport2 support2
        )
        {
            D3D12FeatureDataFormatSupport formatSupport = new D3D12FeatureDataFormatSupport(format);

            Result result = device.CheckFeatureSupport(D3D12Feature.FormatSupport, ref formatSupport);

            support1 = formatSupport.Support1;
            support2 = formatSupport.Support2;

            return result;
        }

        public Result MultisampleQualityLevels(
            DXGIFormat format,
            uint sampleCount,
            D3D12MultisampleQualityLevelFlags flags,
            out uint numQualityLevels
        )
        {
            D3D12FeatureDataMultisampleQualityLevels multisampleQualityLevels = new D3D12FeatureDataMultisampleQualityLevels(format, sampleCount, flags);

            Result result = device.CheckFeatureSupport(D3D12Feature.MultisampleQualityLevels, ref multisampleQualityLevels);

            if (result.Succeeded)
            {
                numQualityLevels = multisampleQualityLevels.NumQualityLevels;
            }
            else
            {
                numQualityLevels = 0;
            }

            return result;
        }

        public Result FormatInfo(DXGIFormat format, out byte planeCount)
        {
            D3D12FeatureDataFormatInfo formatInfo = new D3D12FeatureDataFormatInfo(format);

            Result result = device.CheckFeatureSupport(D3D12Feature.FormatInfo, ref formatInfo);

            if (result.Failed)
            {
                planeCount = 0;
            }
            else
            {
                planeCount = formatInfo.PlaneCount;
            }

            return result;
        }

        public uint MaxGPUVirtualAddressBitsPerProcess => gpuVASupport.MaxGPUVirtualAddressBitsPerProcess;

        public D3DShaderModel HighestShaderModel => shaderModel.HighestShaderModel;

        public bool WaveOps => (options1.WaveOps == CBool.True);

        public uint WaveLaneCountMin => options1.WaveLaneCountMin;

        public uint WaveLaneCountMax => options1.WaveLaneCountMax;

        public uint TotalLaneCount => options1.TotalLaneCount;

        public bool ExpandedComputeResourceStates => (options1.ExpandedComputeResourceStates == CBool.True);

        public bool Int64ShaderOps => (options1.Int64ShaderOps == CBool.True);

        public D3D12ProtectedResourceSessionSupportFlags ProtectedResourceSessionSupport(int nodeIndex)
        {
            return protectedResourceSessionSupport[nodeIndex].Support;
        }

        public D3DRootSignatureVersion HighestRootSignatureVersion => rootSignature.HighestVersion;

        public bool TileBasedRenderer(int nodeIndex)
        {
            return architecture1[nodeIndex].TileBasedRenderer == CBool.True;
        }

        public bool UMA(int nodeIndex)
        {
            return architecture1[nodeIndex].UMA == CBool.True;
        }

        public bool CacheCoherentUMA(int nodeIndex)
        {
            return architecture1[nodeIndex].CacheCoherentUMA == CBool.True;
        }

        public bool IsolatedMMU(int nodeIndex)
        {
            return architecture1[nodeIndex].IsolatedMMU == CBool.True;
        }

        public bool DepthBoundsTestSupported => (options2.DepthBoundsTestSupported == CBool.True);

        public D3D12ProgrammableSamplePositionsTier ProgrammableSamplePositionsTier => options2.ProgrammableSamplePositionsTier;

        public D3D12ShaderCacheSupportFlags ShaderCacheSupportFlags => shaderCache.SupportFlags;

        public bool CommandQueuePrioritySupported(D3D12CommandListType commandListType, uint priority)
        {
            commandQueuePriority.CommandListType = commandListType;
            commandQueuePriority.Priority = priority;

            if (device.CheckFeatureSupport(D3D12Feature.CommandQueuePriority, ref commandQueuePriority).Failed)
            {
                return false;
            }

            return commandQueuePriority.PriorityForTypeIsSupported == CBool.True;
        }

        public bool CopyQueueTimestampQueriesSupported => (options3.CopyQueueTimestampQueriesSupported == CBool.True);

        public bool CastingFullyTypedFormatSupported => (options3.CastingFullyTypedFormatSupported == CBool.True);

        public D3D12CommandListSupportFlags WriteBufferImmediateSupportFlags => options3.WriteBufferImmediateSupportFlags;

        public D3D12ViewInstancingTier ViewInstancingTier => options3.ViewInstancingTier;

        public bool BarycentricsSupported => (options3.BarycentricsSupported == CBool.True);

        public bool ExistingHeapsSupported => (existingHeaps.Supported == CBool.True);

        public bool MSAA64KBAlignedTextureSupported => (options4.MSAA64KBAlignedTextureSupported == CBool.True);

        public D3D12SharedResourceCompatibilityTier SharedResourceCompatibilityTier => options4.SharedResourceCompatibilityTier;

        public bool Native16BitShaderOpsSupported => (options4.Native16BitShaderOpsSupported == CBool.True);

        public D3D12HeapSerializationTier HeapSerializationTier(int nodeIndex)
        {
            return serialization[nodeIndex].HeapSerializationTier;
        }

        public bool CrossNodeAtomicShaderInstructions => (crossNode.AtomicShaderInstructions == CBool.True);

        public bool SRVOnlyTiledResourceTier3 => (options5.SRVOnlyTiledResourceTier3 == CBool.True);

        public D3D12RenderPassTier RenderPassesTier => options5.RenderPassesTier;

        public D3D12RaytracingTier RaytracingTier => options5.RaytracingTier;

        public bool AdditionalShadingRatesSupported => (options6.AdditionalShadingRatesSupported == CBool.True);

        public bool PerPrimitiveShadingRateSupportedWithViewportIndexing => (options6.PerPrimitiveShadingRateSupportedWithViewportIndexing == CBool.True);

        public D3D12VariableShadingRateTier VariableShadingRateTier => options6.VariableShadingRateTier;

        public uint ShadingRateImageTileSize => options6.ShadingRateImageTileSize;

        public bool BackgroundProcessingSupported => (options6.BackgroundProcessingSupported == CBool.True);

        public Result QueryMetaCommand(ref D3D12FeatureDataQueryMetaCommand queryMetaCommand)
        {
            return device.CheckFeatureSupport(D3D12Feature.QueryMetaCommand, ref queryMetaCommand);
        }

        public D3D12MeshShaderTier MeshShaderTier => options7.MeshShaderTier;

        public D3D12SamplerFeedbackTier SamplerFeedbackTier => options7.SamplerFeedbackTier;

        public uint ProtectedResourceSessionTypeCount(int nodeIndex)
        {
            return protectedResourceSessionTypeCount[nodeIndex].Count;
        }

        public Guid[] ProtectedResourceSessionTypes(int nodeIndex)
        {
            return protectedResourceSessionTypes[nodeIndex].TypeVec;
        }

        public bool UnalignedBlockTexturesSupported => (options8.UnalignedBlockTexturesSupported == CBool.True);

        public bool MeshShaderPipelineStatsSupported => (options9.MeshShaderPipelineStatsSupported == CBool.True);

        public bool MeshShaderSupportsFullRangeRenderTargetArrayIndex => (options9.MeshShaderSupportsFullRangeRenderTargetArrayIndex == CBool.True);

        public bool AtomicInt64OnTypedResourceSupported => (options9.AtomicInt64OnTypedResourceSupported == CBool.True);

        public bool AtomicInt64OnGroupSharedSupported => (options9.AtomicInt64OnGroupSharedSupported == CBool.True);

        public bool DerivativesInMeshAndAmplificationShadersSupported => (options9.DerivativesInMeshAndAmplificationShadersSupported == CBool.True);

        public D3D12WaveMMATier WaveMMATier => options9.WaveMMATier;
    }
}
