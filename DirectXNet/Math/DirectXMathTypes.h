#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

#ifdef _NETCORE
using namespace System::Runtime::Intrinsics;
using namespace System::Runtime::Intrinsics::X86;
#endif
using namespace System::Numerics;

#define FXMVector [In][IsReadOnly] XMVector%
#define GXMVector [In][IsReadOnly] XMVector%
#define HXMVector [In][IsReadOnly] XMVector%
#define CXMVector [In][IsReadOnly] XMVector%

#define FXMMatrix [In][IsReadOnly] XMMatrix%
#define CXMMatrix [In][IsReadOnly] XMMatrix%

#define __INLINE [MethodImpl(MethodImplOptions::AggressiveInlining)]

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
#ifdef _NETCORE
        [StructLayout(LayoutKind::Sequential, Pack = 16)]
#else
        [StructLayout(LayoutKind::Sequential)]
#endif
        public value struct XMVector
        {
#ifdef _NETCORE
            __M128 m128;
#else
            __Vector4 vector;
#endif
            
            __INLINE static XMVector operator+(FXMVector v);

            __INLINE static XMVector operator-(FXMVector v);

            __INLINE static XMVector operator+(FXMVector v1, FXMVector v2);

            __INLINE static XMVector operator-(FXMVector v1, FXMVector v2);

            __INLINE static XMVector operator*(FXMVector v1, FXMVector v2);

            __INLINE static XMVector operator/(FXMVector v1, FXMVector v2);

            __INLINE static XMVector operator*(FXMVector v, float s);

            __INLINE static XMVector operator*(float s, FXMVector v);

            __INLINE static XMVector operator/(FXMVector v, float s);
        };

        /// <summary>
        /// XMMATRIX in .NET.
        /// </summary>
#ifdef _NETCORE
        [StructLayout(LayoutKind::Sequential, Pack = 16)]
#else
        [StructLayout(LayoutKind::Explicit, Size = 64)]
#endif
        public value struct XMMatrix
        {
#ifdef _NETCORE
            XMVector r0;
            XMVector r1;
            XMVector r2;
            XMVector r3;
#else
            [FieldOffset(0)] XMVector r0;
            [FieldOffset(16)] XMVector r1;
            [FieldOffset(32)] XMVector r2;
            [FieldOffset(48)] XMVector r3;
            [FieldOffset(0)] Matrix4x4 matrix;
#endif
            __INLINE XMMatrix(
                FXMVector r0, FXMVector r1, FXMVector r2, CXMVector r3);

            __INLINE XMMatrix(float m00, float m01, float m02, float m03,
                     float m10, float m11, float m12, float m13,
                     float m20, float m21, float m22, float m23,
                     float m30, float m31, float m32, float m33);
            
            __INLINE static XMMatrix operator+(FXMMatrix m);
            __INLINE static XMMatrix operator-(FXMMatrix m);
            __INLINE static XMMatrix operator+(FXMMatrix m1, CXMMatrix m2);
            __INLINE static XMMatrix operator-(FXMMatrix m1, CXMMatrix m2);
            __INLINE static XMMatrix operator*(FXMMatrix m1, CXMMatrix m2);
            __INLINE static XMMatrix operator*(FXMMatrix m, float s);
            __INLINE static XMMatrix operator*(float s, FXMMatrix m);
            __INLINE static XMMatrix operator/(FXMMatrix m, float s);
        };

        /// <summary>
        /// XMFLOAT2 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat2
        {
            float x;
            float y;

            __INLINE XMFloat2(float x, float y) : x(x), y(y) {}
            __INLINE static operator XMFloat2(Vector2 v);
            __INLINE static operator Vector2(XMFloat2 v);
        };

        /// <summary>
        /// XMINT2 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMInt2
        {
            int x;
            int y;

            __INLINE XMInt2(int x, int y) : x(x), y(y) {}
        };

        /// <summary>
        /// XMUINT2 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMUInt2
        {
            unsigned int x;
            unsigned int y;

            __INLINE XMUInt2(unsigned int x, unsigned int y) : x(x), y(y) {}
        };

        /// <summary>
        /// XMFLOAT3 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat3
        {
            float x;
            float y;
            float z;

            __INLINE XMFloat3(float x, float y, float z) : x(x), y(y), z(z) {}
            __INLINE static operator XMFloat3(Vector3 v);
            __INLINE static operator Vector3(XMFloat3 v);
        };

        /// <summary>
        /// XMINT3 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMInt3
        {
            int x;
            int y;
            int z;

            __INLINE XMInt3(int x, int y, int z) : x(x), y(y), z(z) {}
        };

        /// <summary>
        /// XMUINT3 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMUInt3
        {
            unsigned int x;
            unsigned int y;
            unsigned int z;

            __INLINE XMUInt3(unsigned int x, unsigned int y, unsigned int z) : x(x), y(y), z(z) {}
        };

        /// <summary>
        /// XMFLOAT4 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat4
        {
            float x;
            float y;
            float z;
            float w;

            __INLINE XMFloat4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
            __INLINE static operator XMFloat4(Vector4 v);
            __INLINE static operator Vector4(XMFloat4 v);
        };

        /// <summary>
        /// XMINT4 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMInt4
        {
            int x;
            int y;
            int z;
            int w;

            __INLINE XMInt4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {}
        };

        /// <summary>
        /// XMUINT4 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMUInt4
        {
            unsigned int x;
            unsigned int y;
            unsigned int z;
            unsigned int w;

            __INLINE XMUInt4(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
                : x(x), y(y), z(z), w(w) {}
        };

        /// <summary>
        /// XMFLOAT3X3 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat3X3
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;

            __INLINE XMFloat3X3(float m00, float m01, float m02,
                       float m10, float m11, float m12,
                       float m20, float m21, float m22)
                : _11(m00), _12(m01), _13(m02),
                _21(m10), _22(m11), _23(m12),
                _31(m20), _32(m21), _33(m22)
            {
            }
        };

        /// <summary>
        /// XMFLOAT4X3 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat4X3
        {
            float _11, _12, _13;
            float _21, _22, _23;
            float _31, _32, _33;
            float _41, _42, _43;
            
            __INLINE XMFloat4X3(float m00, float m01, float m02,
                                 float m10, float m11, float m12,
                                 float m20, float m21, float m22,
                                 float m30, float m31, float m32)
                : _11(m00), _12(m01), _13(m02),
                _21(m10), _22(m11), _23(m12),
                _31(m20), _32(m21), _33(m22),
                _41(m30), _42(m31), _43(m32)
            {
            }
        };

        /// <summary>
        /// XMFLOAT3X4 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat3X4
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;

            __INLINE XMFloat3X4(float m00, float m01, float m02, float m03,
                                 float m10, float m11, float m12, float m13,
                                 float m20, float m21, float m22, float m23)
                : _11(m00), _12(m01), _13(m02), _14(m03),
                _21(m10), _22(m11), _23(m12), _24(m13),
                _31(m20), _32(m21), _33(m22), _34(m23)
            {
            }
        };

        /// <summary>
        /// XMFLOAT4X4 in .NET.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct XMFloat4X4
        {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;

            __INLINE XMFloat4X4(float m00, float m01, float m02, float m03,
                                 float m10, float m11, float m12, float m13,
                                 float m20, float m21, float m22, float m23,
                                 float m30, float m31, float m32, float m33)
                : _11(m00), _12(m01), _13(m02), _14(m03),
                _21(m10), _22(m11), _23(m12), _24(m13),
                _31(m20), _32(m21), _33(m22), _34(m23),
                _41(m30), _42(m31), _43(m32), _44(m33)
            {
            }

            __INLINE static operator XMFloat4X4([In][IsReadOnly] Matrix4x4% v);
            __INLINE static operator Matrix4x4([In][IsReadOnly] XMFloat4X4% v);
        };
    }
}