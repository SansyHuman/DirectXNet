#pragma once

#include "DirectXMathTypes.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

#ifdef _NETCORE
using namespace System::Runtime::Intrinsics;
using namespace System::Runtime::Intrinsics::X86;
#else
using namespace System::Numerics;
#endif

namespace DirectXNet
{
    namespace Math
    {
        public ref class DXMath abstract sealed
        {
        public:
            static DXMath();

            // Constant definitions
            literal float Pi = 3.141592654f;
            literal float TwoPi = 6.283185307f;
            literal float OneDivPi = 0.318309886f;
            literal float OneDivTwoPi = 0.159154943f;
            literal float PiDivTwo = 1.570796327f;
            literal float PiDivFour = 0.785398163f;

            literal unsigned __int32 Select0 = 0x00000000;
            literal unsigned __int32 Select1 = 0xFFFFFFFF;

            literal unsigned __int32 Permute0X = 0;
            literal unsigned __int32 Permute0Y = 1;
            literal unsigned __int32 Permute0Z = 2;
            literal unsigned __int32 Permute0W = 3;
            literal unsigned __int32 Permute1X = 4;
            literal unsigned __int32 Permute1Y = 5;
            literal unsigned __int32 Permute1Z = 6;
            literal unsigned __int32 Permute1W = 7;

            literal unsigned __int32 SwizzleX = 0;
            literal unsigned __int32 SwizzleY = 1;
            literal unsigned __int32 SwizzleZ = 2;
            literal unsigned __int32 SwizzleW = 3;

            literal unsigned __int32 CRMaskCR6 = 0x000000F0;
            literal unsigned __int32 CRMaskCR6True = 0x00000080;
            literal unsigned __int32 CRMaskCR6False = 0x00000020;
            literal unsigned __int32 CRMaskCR6Bounds = CRMaskCR6False;

            literal size_t CacheLineSize = 64;

            // Macros

            // Unit conversion
            __INLINE static float XMConvertToRadians(float fDegrees);
            __INLINE static float XMConvertToDegrees(float fRadians);

            // Condition register evaluation proceeding a recording (R) comparison
            __INLINE static bool XMComparisonAllTrue(unsigned __int32 CR);
            __INLINE static bool XMComparisonAnyTrue(unsigned __int32 CR);
            __INLINE static bool XMComparisonAllFalse(unsigned __int32 CR);
            __INLINE static bool XMComparisonAnyFalse(unsigned __int32 CR);
            __INLINE static bool XMComparisonMixed(unsigned __int32 CR);
            __INLINE static bool XMComparisonAllInBounds(unsigned __int32 CR);
            __INLINE static bool XMComparisonAnyOutOfBounds(unsigned __int32 CR);

#ifdef _NETCORE
            __INLINE static Vector128<float> XMPermutePS(
                Vector128<float> v, unsigned int c);
#endif

            // Data conversion operations
            __INLINE static XMVector XMConvertVectorIntToFloat(
                FXMVector VInt, unsigned __int32 DivExponent
            );
            __INLINE static XMVector XMConvertVectorFloatToInt(
                FXMVector VFloat, unsigned __int32 MulExponent
            );
            __INLINE static XMVector XMConvertVectorUIntToFloat(
                FXMVector VUInt, unsigned __int32 DivExponent
            );
            __INLINE static XMVector XMConvertVectorFloatToUInt(
                FXMVector VFloat, unsigned __int32 MulExponent
            );
            __INLINE static XMVector XMVectorSetBinaryConstant(
                unsigned __int32 C0,
                unsigned __int32 C1,
                unsigned __int32 C2,
                unsigned __int32 C3
            );
            __INLINE static XMVector XMVectorSplatConstant(
                int IntConstant, unsigned __int32 DivExponent
            );
            __INLINE static XMVector XMVectorSplatConstantInt(
                int IntConstant
            );

            // Load operations
            __INLINE static XMVector XMLoadInt(__int32 source);
            __INLINE static XMVector XMLoadInt(unsigned __int32 source);
            __INLINE static XMVector XMLoadFloat(float source);

            __INLINE static XMVector XMLoadInt2(unsigned __int32* pSource);
            __INLINE static XMVector XMLoadFloat2(XMFloat2* pSource);
            __INLINE static XMVector XMLoadSInt2(XMInt2* pSource);
            __INLINE static XMVector XMLoadUInt2(XMUInt2* pSource);

            __INLINE static XMVector XMLoadInt3(unsigned __int32* pSource);
            __INLINE static XMVector XMLoadFloat3(XMFloat3* pSource);
            __INLINE static XMVector XMLoadSInt3(XMInt3* pSource);
            __INLINE static XMVector XMLoadUInt3(XMUInt3* pSource);

            __INLINE static XMVector XMLoadInt4(unsigned __int32* pSource);
            __INLINE static XMVector XMLoadFloat4(XMFloat4* pSource);
            __INLINE static XMVector XMLoadSInt4(XMInt4* pSource);
            __INLINE static XMVector XMLoadUInt4(XMUInt4* pSource);

            __INLINE static XMMatrix XMLoadFloat3x3(XMFloat3X3* pSource);
            __INLINE static XMMatrix XMLoadFloat4x3(XMFloat4X3* pSource);
            __INLINE static XMMatrix XMLoadFloat3x4(XMFloat3X4* pSource);
            __INLINE static XMMatrix XMLoadFloat4x4(XMFloat4X4* pSource);

            // Store operations
            __INLINE static void XMStoreInt(__int32* pDestination, FXMVector V);
            __INLINE static void XMStoreInt(unsigned __int32* pDestination, FXMVector V);
            __INLINE static void XMStoreFloat(float* pDestination, FXMVector V);

            __INLINE static void XMStoreInt2(unsigned __int32* pDestination, FXMVector V);
            __INLINE static void XMStoreFloat2(XMFloat2* pDestination, FXMVector V);
            __INLINE static void XMStoreSInt2(XMInt2* pDestination, FXMVector V);
            __INLINE static void XMStoreUInt2(XMUInt2* pDestination, FXMVector V);

            __INLINE static void XMStoreInt3(unsigned __int32* pDestination, FXMVector V);
            __INLINE static void XMStoreFloat3(XMFloat3* pDestination, FXMVector V);
            __INLINE static void XMStoreSInt3(XMInt3* pDestination, FXMVector V);
            __INLINE static void XMStoreUInt3(XMUInt3* pDestination, FXMVector V);

            __INLINE static void XMStoreInt4(unsigned __int32* pDestination, FXMVector V);
            __INLINE static void XMStoreFloat4(XMFloat4* pDestination, FXMVector V);
            __INLINE static void XMStoreSInt4(XMInt4* pDestination, FXMVector V);
            __INLINE static void XMStoreUInt4(XMUInt4* pDestination, FXMVector V);

            __INLINE static void XMStoreFloat3x3(XMFloat3X3* pDestination, FXMMatrix M);
            __INLINE static void XMStoreFloat4x3(XMFloat4X3* pDestination, FXMMatrix M);
            __INLINE static void XMStoreFloat3x4(XMFloat3X4* pDestination, FXMMatrix M);
            __INLINE static void XMStoreFloat4x4(XMFloat4X4* pDestination, FXMMatrix M);

            // General vector operations
            __INLINE static XMVector XMVectorReplicate(float Value);

            __INLINE static XMVector XMVectorNegate(FXMVector V);
            __INLINE static XMVector XMVectorAdd(FXMVector V1, FXMVector V2);
            __INLINE static XMVector XMVectorSubtract(FXMVector V1, FXMVector V2);
            __INLINE static XMVector XMVectorMultiply(FXMVector V1, FXMVector V2);
            __INLINE static XMVector XMVectorDivide(FXMVector V1, FXMVector V2);
            __INLINE static XMVector XMVectorScale(FXMVector V, float ScaleFactor);

            // Matrix operations
            __INLINE static XMMatrix XMMatrixMultiply(FXMMatrix M1, CXMMatrix M2);

            // Globals
#ifdef _NETCORE
            static initonly Vector128<unsigned __int32> g_XMMask3;
            static initonly Vector128<float> g_XMFixUnsigned;
            static initonly Vector128<float> g_XMMaxInt;
            static initonly Vector128<float> g_XMMaxUInt;
            static initonly Vector128<float> g_XMUnsignedFix;
            static initonly Vector128<int> g_XMAbsMask;
            static initonly Vector128<float> g_XMIdentityR3;
            static initonly Vector128<unsigned __int32> g_XMNegativeZero;
            static initonly Vector128<float> g_XMOne;
            static initonly Vector128<float> g_XMZero;
#endif
        };
    }
}