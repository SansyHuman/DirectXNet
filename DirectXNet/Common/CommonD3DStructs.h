#pragma once

#include "CommonStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DirectXNet
{
    namespace Common
    {
        namespace D3D
        {
            /// <summary>
            /// Driver type options.
            /// </summary>
            public enum class D3DDriverType : UINT
            {
                /// <summary>
                /// The driver type is unknown.
                /// </summary>
                Unknown = D3D_DRIVER_TYPE_UNKNOWN,

                /// <summary>
                /// A hardware driver, which implements Direct3D features in hardware. This is the
                /// primary driver that you should use in your Direct3D applications because it provides
                /// the best performance. A hardware driver uses hardware acceleration (on supported
                /// hardware) but can also use software for parts of the pipeline that are not supported
                /// in hardware. This driver type is often referred to as a hardware abstraction layer or
                /// HAL.
                /// </summary>
                Hardware = D3D_DRIVER_TYPE_HARDWARE,

                /// <summary>
                /// A reference driver, which is a software implementation that supports every Direct3D
                /// feature. A reference driver is designed for accuracy rather than speed and as a
                /// result is slow but accurate. The rasterizer portion of the driver does make use of
                /// special CPU instructions whenever it can, but it is not intended for retail
                /// applications; use it only for feature testing, demonstration of functionality,
                /// debugging, or verifying bugs in other drivers. The reference device for this driver
                /// is installed by the Windows SDK 8.0 or later and is intended only as a debug aid for
                /// development purposes. This driver may be referred to as a REF driver, a reference
                /// driver, or a reference rasterizer.
                /// </summary>
                Reference = D3D_DRIVER_TYPE_REFERENCE,

                /// <summary>
                /// A NULL driver, which is a reference driver without render capability. This driver
                /// is commonly used for debugging non-rendering API calls, it is not appropriate for
                /// retail applications. This driver is installed by the DirectX SDK.
                /// </summary>
                Null = D3D_DRIVER_TYPE_NULL,

                /// <summary>
                /// A software driver, which is a driver implemented completely in software. The
                /// software implementation is not intended for a high-performance application due to
                /// its very slow performance.
                /// </summary>
                Software = D3D_DRIVER_TYPE_SOFTWARE,

                /// <summary>
                /// A WARP driver, which is a high-performance software rasterizer. The rasterizer
                /// supports feature levels 9_1 through level 10_1 with a high performance software
                /// implementation.
                /// </summary>
                Warp = D3D_DRIVER_TYPE_WARP
            };

            /// <summary>
            /// Describes the set of features targeted by a Direct3D device.
            /// </summary>
            public enum class D3DFeatureLevel : UINT
            {
                Level1_0Core = D3D_FEATURE_LEVEL_1_0_CORE,
                Level9_1 = D3D_FEATURE_LEVEL_9_1,
                Level9_2 = D3D_FEATURE_LEVEL_9_2,
                Level9_3 = D3D_FEATURE_LEVEL_9_3,
                Level10_0 = D3D_FEATURE_LEVEL_10_0,
                Level10_1 = D3D_FEATURE_LEVEL_10_1,
                Level11_0 = D3D_FEATURE_LEVEL_11_0,
                Level11_1 = D3D_FEATURE_LEVEL_11_1,
                Level12_0 = D3D_FEATURE_LEVEL_12_0,
                Level12_1 = D3D_FEATURE_LEVEL_12_1,
                Level12_2 = D3D_FEATURE_LEVEL_12_2
            };

            /// <summary>
            /// Values that indicate how the pipeline interprets vertex data that is bound to the
            /// input-assembler stage. These primitive topology values determine how the vertex data
            /// is rendered on screen.
            /// </summary>
            public enum class D3DPrimitiveTopology : UINT
            {
                Undefined = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED,
                Pointlist = D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
                Linelist = D3D_PRIMITIVE_TOPOLOGY_LINELIST,
                Linestrip = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
                Trianglelist = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
                Trianglestrip = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
                LinelistAdj = D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ,
                LinestripAdj = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ,
                TrianglelistAdj = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ,
                TrianglestripAdj = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ,
                Num1ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST,
                Num2ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST,
                Num3ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST,
                Num4ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST,
                Num5ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST,
                Num6ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST,
                Num7ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST,
                Num8ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST,
                Num9ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST,
                Num10ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST,
                Num11ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST,
                Num12ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST,
                Num13ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST,
                Num14ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST,
                Num15ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST,
                Num16ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST,
                Num17ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST,
                Num18ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST,
                Num19ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST,
                Num20ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST,
                Num21ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST,
                Num22ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST,
                Num23ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST,
                Num24ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST,
                Num25ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST,
                Num26ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST,
                Num27ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST,
                Num28ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST,
                Num29ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST,
                Num30ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST,
                Num31ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST,
                Num32ControlPointPatchlist = D3D_PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST
            };

            /// <summary>
            /// Indicates how the pipeline interprets geometry or hull shader input primitives.
            /// </summary>
            public enum class D3DPrimitive : UINT
            {
                Undefined = D3D_PRIMITIVE_UNDEFINED,
                Point = D3D_PRIMITIVE_POINT,
                Line = D3D_PRIMITIVE_LINE,
                Triangle = D3D_PRIMITIVE_TRIANGLE,
                LineAdj = D3D_PRIMITIVE_LINE_ADJ,
                TriangleAdj = D3D_PRIMITIVE_TRIANGLE_ADJ,
                Num1ControlPointPatch = D3D_PRIMITIVE_1_CONTROL_POINT_PATCH,
                Num2ControlPointPatch = D3D_PRIMITIVE_2_CONTROL_POINT_PATCH,
                Num3ControlPointPatch = D3D_PRIMITIVE_3_CONTROL_POINT_PATCH,
                Num4ControlPointPatch = D3D_PRIMITIVE_4_CONTROL_POINT_PATCH,
                Num5ControlPointPatch = D3D_PRIMITIVE_5_CONTROL_POINT_PATCH,
                Num6ControlPointPatch = D3D_PRIMITIVE_6_CONTROL_POINT_PATCH,
                Num7ControlPointPatch = D3D_PRIMITIVE_7_CONTROL_POINT_PATCH,
                Num8ControlPointPatch = D3D_PRIMITIVE_8_CONTROL_POINT_PATCH,
                Num9ControlPointPatch = D3D_PRIMITIVE_9_CONTROL_POINT_PATCH,
                Num10ControlPointPatch = D3D_PRIMITIVE_10_CONTROL_POINT_PATCH,
                Num11ControlPointPatch = D3D_PRIMITIVE_11_CONTROL_POINT_PATCH,
                Num12ControlPointPatch = D3D_PRIMITIVE_12_CONTROL_POINT_PATCH,
                Num13ControlPointPatch = D3D_PRIMITIVE_13_CONTROL_POINT_PATCH,
                Num14ControlPointPatch = D3D_PRIMITIVE_14_CONTROL_POINT_PATCH,
                Num15ControlPointPatch = D3D_PRIMITIVE_15_CONTROL_POINT_PATCH,
                Num16ControlPointPatch = D3D_PRIMITIVE_16_CONTROL_POINT_PATCH,
                Num17ControlPointPatch = D3D_PRIMITIVE_17_CONTROL_POINT_PATCH,
                Num18ControlPointPatch = D3D_PRIMITIVE_18_CONTROL_POINT_PATCH,
                Num19ControlPointPatch = D3D_PRIMITIVE_19_CONTROL_POINT_PATCH,
                Num20ControlPointPatch = D3D_PRIMITIVE_20_CONTROL_POINT_PATCH,
                Num21ControlPointPatch = D3D_PRIMITIVE_21_CONTROL_POINT_PATCH,
                Num22ControlPointPatch = D3D_PRIMITIVE_22_CONTROL_POINT_PATCH,
                Num23ControlPointPatch = D3D_PRIMITIVE_23_CONTROL_POINT_PATCH,
                Num24ControlPointPatch = D3D_PRIMITIVE_24_CONTROL_POINT_PATCH,
                Num25ControlPointPatch = D3D_PRIMITIVE_25_CONTROL_POINT_PATCH,
                Num26ControlPointPatch = D3D_PRIMITIVE_26_CONTROL_POINT_PATCH,
                Num27ControlPointPatch = D3D_PRIMITIVE_27_CONTROL_POINT_PATCH,
                Num28ControlPointPatch = D3D_PRIMITIVE_28_CONTROL_POINT_PATCH,
                Num29ControlPointPatch = D3D_PRIMITIVE_29_CONTROL_POINT_PATCH,
                Num30ControlPointPatch = D3D_PRIMITIVE_30_CONTROL_POINT_PATCH,
                Num31ControlPointPatch = D3D_PRIMITIVE_31_CONTROL_POINT_PATCH,
                Num32ControlPointPatch = D3D_PRIMITIVE_32_CONTROL_POINT_PATCH,
            };

            /// <summary>
            /// Values that identify the type of resource to be viewed as a shader resource.
            /// </summary>
            public enum class D3DSrvDimension : UINT
            {
                Unknown = D3D_SRV_DIMENSION_UNKNOWN,
                Buffer = D3D_SRV_DIMENSION_BUFFER,
                Texture1D = D3D_SRV_DIMENSION_TEXTURE1D,
                Texture1DArray = D3D_SRV_DIMENSION_TEXTURE1DARRAY,
                Texture2D = D3D_SRV_DIMENSION_TEXTURE2D,
                Texture2DArray = D3D_SRV_DIMENSION_TEXTURE2DARRAY,
                Texture2DMs = D3D_SRV_DIMENSION_TEXTURE2DMS,
                Texture2DMsArray = D3D_SRV_DIMENSION_TEXTURE2DMSARRAY,
                Texture3D = D3D_SRV_DIMENSION_TEXTURE3D,
                TextureCube = D3D_SRV_DIMENSION_TEXTURECUBE,
                TextureCubeArray = D3D_SRV_DIMENSION_TEXTURECUBEARRAY,
                BufferEx = D3D_SRV_DIMENSION_BUFFEREX,
            };

            /// <summary>
            /// Defines a shader macro.
            /// </summary>
            public value struct D3DShaderMacro
            {
                /// <summary>
                /// The macro name.
                /// </summary>
                System::String^ Name;

                /// <summary>
                /// The macro definition.
                /// </summary>
                System::String^ Definition;
            };
        }
    }
}