#pragma once

#include "../pch.h"
#include "D3D12Structs.h"
#include "../Common/CommonStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DirectXNet::DXGI;
using namespace DirectXNet::Common::D3D;

namespace DirectXNet
{
    namespace Common
    {
        ref class Unknown;
    }

    namespace DirectX12
    {
        ref class D3D12Device;

        /// <summary>
        /// Class containing DirectX12 functions.
        /// </summary>
        public ref class D3D12 abstract sealed
        {
        private:
            static D3D12();

        public:
            /// <summary>
            /// Default value for struct initialization.
            /// </summary>
            static initonly D3DDefault Default = D3DDefault();

            /// <summary>
            /// Creates a device that represents the display adapter.
            /// </summary>
            /// <typeparam name="T">Type of the device.</typeparam>
            /// <param name="minimumFeatureLevel">The minimum D3DFeatureLevel required for
            /// successful device creation.</param>
            /// <param name="adapter">A video adapter to use when creating a device. Pass null to use
            /// the default adapter, which is the first adapter that is enumerated by
            /// DXGIFactory1::EnumAdapters.</param>
            /// <returns></returns>
            generic <typename T> where T : D3D12Device
            static T CreateDevice(
                D3DFeatureLevel minimumFeatureLevel,
                [Optional] DirectXNet::Common::Unknown^ adapter
            );

            /// <summary>
            /// Gets the number of planes for the specified DXGI format for the specified virtual
            /// adapter (an ID3D12Device).
            /// </summary>
            /// <param name="device">The virtual adapter (an ID3D12Device) for which to get the
            /// plane count.</param>
            /// <param name="format">The DXGIFormat for which to get the plane count.</param>
            /// <returns>The plane count for the specified format on the specified virtual adapter.
            /// </returns>
            [MethodImpl(MethodImplOptions::AggressiveInlining)]
            static unsigned char GetFormatPlaneCount(D3D12Device^ device, DXGIFormat format);

            /// <summary>
            /// Calculates a subresource index for a texture.
            /// </summary>
            /// <param name="mipSlice">The zero-based index for the mipmap level to address;
            /// 0 indicates the first, most detailed mipmap level.</param>
            /// <param name="arraySlice">The zero-based index for the array level to address; always
            /// use 0 for volume (3D) textures.</param>
            /// <param name="planeSlice">The zero-based index for the plane level to address.</param>
            /// <param name="mipLevels">The number of mipmap levels in the resource.</param>
            /// <param name="arraySize">The number of elements in the array.</param>
            /// <returns>The index.</returns>
            [MethodImpl(MethodImplOptions::AggressiveInlining)]
            static unsigned int CalcSubresource(
                unsigned int mipSlice,
                unsigned int arraySlice,
                unsigned int planeSlice,
                unsigned int mipLevels,
                unsigned int arraySize
            );
         
            /// <summary>
            /// Encode sharder 4-component mapping.
            /// </summary>
            /// <param name="src0">Mapping for first component.</param>
            /// <param name="src1">Mapping for second component.</param>
            /// <param name="src2">Mapping for third component.</param>
            /// <param name="src3">Mapping for fourth component.</param>
            /// <returns>Encoded mapping.</returns>
            [MethodImpl(MethodImplOptions::AggressiveInlining)]
            static unsigned int EncodeShader4ComponentMapping(
                D3D12ShaderComponentMapping src0,
                D3D12ShaderComponentMapping src1,
                D3D12ShaderComponentMapping src2,
                D3D12ShaderComponentMapping src3
            );

            /// <summary>
            /// Decode shader 4-component mapping.
            /// </summary>
            /// <param name="componentToExtract">Component to obtain(0 to 3).</param>
            /// <param name="mapping">Encoded mapping.</param>
            /// <returns>Decoded mapping.</returns>
            [MethodImpl(MethodImplOptions::AggressiveInlining)]
            static D3D12ShaderComponentMapping DecodeShader4ComponentMapping(
                unsigned int componentToExtract,
                unsigned int mapping
            );

            literal unsigned int DefaultShader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        };
    }
}