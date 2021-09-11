#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

#ifdef _NETCORE
using namespace System::Runtime::Intrinsics;
using namespace System::Runtime::Intrinsics::X86;
#else
using namespace System::Numerics;
#endif

#define FXMVector [In][IsReadOnly] XMVector%
#define GXMVector FXMVector
#define HXMVector FXMVector
#define CXMVector FXMVector

namespace DirectXNet
{
    namespace Math
    {
#ifdef _NETCORE        
        /// <summary>
        /// __m128 intrinsic type in .NET Core.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 16, Pack = 16)]
        public value struct __M128
        {
            [FieldOffset(0)] Vector128<float> m128_f32;           
            [FieldOffset(0)] Vector128<__int8> m128_i8;
            [FieldOffset(0)] Vector128<__int16> m128_i16;
            [FieldOffset(0)] Vector128<__int32> m128_i32;
            [FieldOffset(0)] Vector128<__int64> m128_i64;
            [FieldOffset(0)] Vector128<unsigned __int8> m128_u8;
            [FieldOffset(0)] Vector128<unsigned __int16> m128_u16;
            [FieldOffset(0)] Vector128<unsigned __int32> m128_u32;
            [FieldOffset(0)] Vector128<unsigned __int64> m128_u64;
        };
#else
        [StructLayout(LayoutKind::Sequential)]
        public value struct Vector4UInt
        {
            unsigned __int32 X;
            unsigned __int32 Y;
            unsigned __int32 Z;
            unsigned __int32 W;

            Vector4UInt(
                unsigned __int32 x,
                unsigned __int32 y,
                unsigned __int32 z,
                unsigned __int32 w
                );

            property unsigned __int32 default[int]
            {
                unsigned __int32 get(int index);
                void set(int index, unsigned __int32 value);
            }
        };

        /// <summary>
        /// __vector4 type in .NET Framework.
        /// </summary>
        [StructLayout(LayoutKind::Explicit, Size = 16)]
        public value struct __Vector4
        {
            [FieldOffset(0)] Vector4 vector4_f32;
            [FieldOffset(0)] Vector4UInt vector4_u32;
        };
#endif
        /// <summary>
        /// XMVECTOR in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMVector
        {
#ifdef _NETCORE
            __M128 m128;
#else
            __Vector4 vector;
#endif
            static XMVector operator+(FXMVector v);

            static XMVector operator-(FXMVector v);

            static XMVector operator+(FXMVector v1, FXMVector v2);

            static XMVector operator-(FXMVector v1, FXMVector v2);
        };
    }
}