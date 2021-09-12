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
            // Macro
#ifdef _NETCORE
            __INLINE static Vector128<float> XMPermutePS(
                Vector128<float>% v, unsigned int c);
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
            static initonly Vector128<float> g_XMFixUnsigned;
            static initonly Vector128<float> g_XMMaxInt;
            static initonly Vector128<float> g_XMMaxUInt;
            static initonly Vector128<float> g_XMUnsignedFix;
            static initonly Vector128<int> g_XMAbsMask;
            static initonly Vector128<unsigned __int32> g_XMNegativeZero;
            static initonly Vector128<float> g_XMOne;
            static initonly Vector128<float> g_XMZero;
#endif
        };
    }
}