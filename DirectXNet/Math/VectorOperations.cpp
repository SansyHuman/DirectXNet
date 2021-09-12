#include "VectorOperations.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

#ifdef _NETCORE
using namespace System::Runtime::Intrinsics;
using namespace System::Runtime::Intrinsics::X86;
#else
using namespace System::Numerics;
#endif

using namespace DirectXNet::Math;

DirectXNet::Math::DXMath::DXMath()
{
#ifdef _NETCORE
    g_XMFixUnsigned = Vector128::Create(32768.0f * 65536.0f);
    g_XMMaxInt = Vector128::Create(65536.0f * 32768.0f - 128.0f);
    g_XMMaxUInt = Vector128::Create(65536.0f * 65536.0f - 256.0f);
    g_XMUnsignedFix = Vector128::Create(32768.0f * 65536.0f);
    g_XMAbsMask = Vector128::Create(0x7FFFFFFF);
    g_XMNegativeZero = Vector128::Create(0x80000000);
    g_XMOne = Vector128::Create(1.0f);
    g_XMZero = Vector128::Create(0.0f);
#endif
}

#ifdef _NETCORE
Vector128<float> DirectXNet::Math::DXMath::XMPermutePS(
    Vector128<float>% v, unsigned int c)
{
    return Sse::Shuffle(v, v, (unsigned char)c);
}
#endif

XMVector DirectXNet::Math::DXMath::XMConvertVectorIntToFloat(
    FXMVector VInt, unsigned __int32 DivExponent)
{
    if(DivExponent >= 32)
        throw gcnew ArgumentException("Div exponent is larger than 31.");
#ifdef _NETCORE
    Vector128<float> vResult = Sse2::ConvertToVector128Single(VInt.m128.m128_i32);
    unsigned __int32 uScale = 0x3F800000U - (DivExponent << 23);
    Vector128<int> vScale = Vector128::Create((int)uScale);
    vResult = Sse::Multiply(vResult, Vector128::AsSingle(vScale));
    return CAST_TO(vResult, XMVector);
#else
    float fScale = 1.0f / (float)(1U << DivExponent);
    return CAST_TO(Vector4(
        (float)VInt.vector.vector4_u32[0] * fScale,
        (float)VInt.vector.vector4_u32[1] * fScale,
        (float)VInt.vector.vector4_u32[2] * fScale,
        (float)VInt.vector.vector4_u32[3] * fScale
    ), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMConvertVectorFloatToInt(
    FXMVector VFloat, unsigned __int32 MulExponent)
{
    if(MulExponent >= 32)
        throw gcnew ArgumentException("Mul exponent is larger than 31.");
#ifdef _NETCORE
    Vector128<float> vResult = Vector128::Create((float)(1U << MulExponent));
    vResult = Sse::Multiply(vResult, VFloat.m128.m128_f32);
    Vector128<float> vOverflow = Sse::CompareGreaterThan(vResult, g_XMMaxInt);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(vResult);
    vResult = Sse::And(vOverflow, Vector128::AsSingle(g_XMAbsMask));
    vOverflow = Sse::AndNot(vOverflow, Vector128::AsSingle(g_XMAbsMask));
    vOverflow = Sse::Or(vOverflow, vResult);
    return CAST_TO(vOverflow, XMVector);
#else
    auto fScale = static_cast<float>(1U << MulExponent);
    XMVector Result;
    int32_t iResult;

    float fTemp = VFloat.vector.vector4_f32.X * fScale;
    if(fTemp <= -(65536.0f * 32768.0f))
    {
        iResult = (-0x7FFFFFFF) - 1;
    }
    else if(fTemp > (65536.0f * 32768.0f) - 128.0f)
    {
        iResult = 0x7FFFFFFF;
    }
    else
    {
        iResult = static_cast<int32_t>(fTemp);
    }
    Result.vector.vector4_u32.X = static_cast<uint32_t>(iResult);

    fTemp = VFloat.vector.vector4_f32.Y * fScale;
    if(fTemp <= -(65536.0f * 32768.0f))
    {
        iResult = (-0x7FFFFFFF) - 1;
    }
    else if(fTemp > (65536.0f * 32768.0f) - 128.0f)
    {
        iResult = 0x7FFFFFFF;
    }
    else
    {
        iResult = static_cast<int32_t>(fTemp);
    }
    Result.vector.vector4_u32.Y = static_cast<uint32_t>(iResult);

    fTemp = VFloat.vector.vector4_f32.Z * fScale;
    if(fTemp <= -(65536.0f * 32768.0f))
    {
        iResult = (-0x7FFFFFFF) - 1;
    }
    else if(fTemp > (65536.0f * 32768.0f) - 128.0f)
    {
        iResult = 0x7FFFFFFF;
    }
    else
    {
        iResult = static_cast<int32_t>(fTemp);
    }
    Result.vector.vector4_u32.Z = static_cast<uint32_t>(iResult);

    fTemp = VFloat.vector.vector4_f32.W * fScale;
    if(fTemp <= -(65536.0f * 32768.0f))
    {
        iResult = (-0x7FFFFFFF) - 1;
    }
    else if(fTemp > (65536.0f * 32768.0f) - 128.0f)
    {
        iResult = 0x7FFFFFFF;
    }
    else
    {
        iResult = static_cast<int32_t>(fTemp);
    }
    Result.vector.vector4_u32.W = static_cast<uint32_t>(iResult);

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMConvertVectorUIntToFloat(FXMVector VUInt, unsigned __int32 DivExponent)
{
    if(DivExponent >= 32)
        throw gcnew ArgumentException("Div exponent is larger than 31.");
#ifdef _NETCORE
    Vector128<float> vMask = Sse::And(VUInt.m128.m128_f32, Vector128::AsSingle(g_XMNegativeZero));
    Vector128<float> vResult = Sse::Xor(VUInt.m128.m128_f32, vMask);
    vResult = Sse2::ConvertToVector128Single(Vector128::AsInt32(vResult));
    Vector128<int> iMask = Sse2::ShiftRightArithmetic(Vector128::AsInt32(vMask), 31);
    vMask = Sse::And(Vector128::AsSingle(iMask), g_XMFixUnsigned);
    vResult = Sse::Add(vResult, vMask);
    unsigned __int32 uScale = 0x3F800000U - (DivExponent << 23);
    iMask = Vector128::Create((int)uScale);
    vResult = Sse::Multiply(vResult, Vector128::AsSingle(iMask));
    return CAST_TO(vResult, XMVector);
#else
    float fScale = 1.0f / (float)(1U << DivExponent);
    return CAST_TO(Vector4(
        (float)VUInt.vector.vector4_u32[0] * fScale,
        (float)VUInt.vector.vector4_u32[1] * fScale,
        (float)VUInt.vector.vector4_u32[2] * fScale,
        (float)VUInt.vector.vector4_u32[3] * fScale
    ), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMConvertVectorFloatToUInt(
    FXMVector VFloat, unsigned __int32 MulExponent)
{
    if(MulExponent >= 32)
        throw gcnew ArgumentException("Mul exponent is larger than 31.");
#ifdef _NETCORE
    Vector128<float> vResult = Vector128::Create((float)(1U << MulExponent));
    vResult = Sse::Multiply(vResult, VFloat.m128.m128_f32);
    vResult = Sse::Max(vResult, g_XMZero);
    Vector128<float> vOverflow = Sse::CompareGreaterThan(vResult, g_XMMaxUInt);
    Vector128<float> vValue = g_XMUnsignedFix;
    Vector128<float> vMask = Sse::CompareGreaterThanOrEqual(vResult, vValue);
    vValue = Sse::And(vValue, vMask);
    vResult = Sse::Subtract(vResult, vValue);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(vResult);
    vMask = Sse::And(vMask, Vector128::AsSingle(g_XMNegativeZero));
    vResult = Sse::Xor(Vector128::AsSingle(vResulti), vMask);
    vResult = Sse::Or(vResult, vOverflow);
    return CAST_TO(vResult, XMVector);
#else
    auto fScale = static_cast<float>(1U << MulExponent);
    XMVector Result;
    uint32_t uResult;

    float fTemp = VFloat.vector.vector4_f32.X * fScale;
    if(fTemp <= 0.0f)
    {
        uResult = 0;
    }
    else if(fTemp > (65536.0f * 65536.0f))
    {
        uResult = 0xFFFFFFFFU;
    }
    else
    {
        uResult = static_cast<uint32_t>(fTemp);
    }
    Result.vector.vector4_u32.X = uResult;

    fTemp = VFloat.vector.vector4_f32.Y * fScale;
    if(fTemp <= 0.0f)
    {
        uResult = 0;
    }
    else if(fTemp > (65536.0f * 65536.0f))
    {
        uResult = 0xFFFFFFFFU;
    }
    else
    {
        uResult = static_cast<uint32_t>(fTemp);
    }
    Result.vector.vector4_u32.Y = uResult;

    fTemp = VFloat.vector.vector4_f32.Z * fScale;
    if(fTemp <= 0.0f)
    {
        uResult = 0;
    }
    else if(fTemp > (65536.0f * 65536.0f))
    {
        uResult = 0xFFFFFFFFU;
    }
    else
    {
        uResult = static_cast<uint32_t>(fTemp);
    }
    Result.vector.vector4_u32.Z = uResult;

    fTemp = VFloat.vector.vector4_f32.W * fScale;
    if(fTemp <= 0.0f)
    {
        uResult = 0;
    }
    else if(fTemp > (65536.0f * 65536.0f))
    {
        uResult = 0xFFFFFFFFU;
    }
    else
    {
        uResult = static_cast<uint32_t>(fTemp);
    }
    Result.vector.vector4_u32.W = uResult;

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetBinaryConstant(
    unsigned __int32 C0, unsigned __int32 C1,
    unsigned __int32 C2, unsigned __int32 C3)
{
#ifdef _NETCORE
    Vector128<unsigned __int32> g_vMask1 = Vector128::Create(1U);
    Vector128<int> vTemp = Vector128::Create((int)C0, (int)C1, (int)C2, (int)C3);
    vTemp = Sse2::And(vTemp, Vector128::AsInt32(g_vMask1));
    vTemp = Sse2::CompareEqual(vTemp, Vector128::AsInt32(g_vMask1));
    vTemp = Sse2::And(vTemp, Vector128::AsInt32(g_XMOne));
    return CAST_TO(vTemp, XMVector);
#else
    DirectX::XMVECTORU32 vResult;
    vResult.u[0] = (0 - (C0 & 1)) & 0x3F800000;
    vResult.u[1] = (0 - (C1 & 1)) & 0x3F800000;
    vResult.u[2] = (0 - (C2 & 1)) & 0x3F800000;
    vResult.u[3] = (0 - (C3 & 1)) & 0x3F800000;
    return CAST_TO(vResult.v, XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatConstant(
    int IntConstant, unsigned __int32 DivExponent)
{
    if(IntConstant < -16)
        throw gcnew ArgumentException("Int constant is smaller than -16.");
    if(IntConstant > 15)
        throw gcnew ArgumentException("Int constant is larger than 15");
    if(DivExponent >= 32)
        throw gcnew ArgumentException("Div exponent is larger than 31.");
#ifdef _NETCORE
    Vector128<int> vScale = Vector128::Create(IntConstant);
    Vector128<float> vResult = Sse2::ConvertToVector128Single(vScale);
    uint32_t uScale = 0x3F800000U - (DivExponent << 23);
    vScale = Vector128::Create((int)uScale);
    vResult = Sse::Multiply(vResult, Vector128::AsSingle(vScale));
    return CAST_TO(vResult, XMVector);
#else
    DirectX::XMVECTORI32 V = { { { IntConstant, IntConstant, IntConstant, IntConstant } } };
    return XMConvertVectorIntToFloat(CAST_TO(V.v, XMVector), DivExponent);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatConstantInt(int IntConstant)
{
    if(IntConstant < -16)
        throw gcnew ArgumentException("Int constant is smaller than -16.");
    if(IntConstant > 15)
        throw gcnew ArgumentException("Int constant is larger than 15");
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(IntConstant), XMVector);
#else
    DirectX::XMVECTORI32 V = { { { IntConstant, IntConstant, IntConstant, IntConstant } } };
    return CAST_TO(V.v, XMVector);
#endif
}

__INLINE XMVector DirectXNet::Math::DXMath::XMLoadInt(__int32 source)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::CreateScalar(source), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = *((unsigned __int32*)&source);
    V.vector.vector4_u32[1] = 0;
    V.vector.vector4_u32[2] = 0;
    V.vector.vector4_u32[3] = 0;
    return V;
#endif
}

__INLINE XMVector DirectXNet::Math::DXMath::XMLoadInt(unsigned __int32 source)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::CreateScalar(source), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = source;
    V.vector.vector4_u32[1] = 0;
    V.vector.vector4_u32[2] = 0;
    V.vector.vector4_u32[3] = 0;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorReplicate(float Value)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(Value), XMVector);
#else
    return CAST_TO(Vector4(Value), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorNegate(FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> Z = Vector128::Create(0.0f);

    return CAST_TO(Sse::Subtract(Z, V.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Negate(V.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorAdd(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Add(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Add(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSubtract(
    FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Subtract(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Subtract(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorMultiply(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Multiply(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Multiply(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorDivide(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Divide(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Divide(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorScale(FXMVector V, float ScaleFactor)
{
#ifdef _NETCORE
    Vector128<float> vResult = Vector128::Create(ScaleFactor);
    return CAST_TO(Sse::Multiply(vResult, V.m128.m128_f32), XMVector);
#else
    return CAST_TO(V.vector.vector4_f32 * ScaleFactor, XMVector);
#endif
}

XMMatrix DirectXNet::Math::DXMath::XMMatrixMultiply(FXMMatrix M1, CXMMatrix M2)
{
#ifdef _NETCORE
    XMMatrix mResult;

    Vector128<float> vX, vY, vZ, vW;
    pin_ptr<XMMatrix> pM1 = &M1;
    pin_ptr<XMMatrix> pM2 = &M2;
    
    if(Avx::IsSupported)
    {
        vX = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r0) + 0
        );
        vY = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r0) + 1
        );
        vZ = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r0) + 2
        );
        vW = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r0) + 3
        );
    }
    else
    {
        vW = M1.r0.m128.m128_f32;
        vX = XMPermutePS(vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = XMPermutePS(vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = XMPermutePS(vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = XMPermutePS(vW, _MM_SHUFFLE(3, 3, 3, 3));
    }

    vX = Sse::Multiply(vX, M2.r0.m128.m128_f32);
    vY = Sse::Multiply(vY, M2.r1.m128.m128_f32);
    vZ = Sse::Multiply(vZ, M2.r2.m128.m128_f32);
    vW = Sse::Multiply(vW, M2.r3.m128.m128_f32);

    vX = Sse::Add(vX, vZ);
    vY = Sse::Add(vY, vW);
    vX = Sse::Add(vX, vY);
    mResult.r0.m128.m128_f32 = vX;

    
    if(Avx::IsSupported)
    {
        vX = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r1) + 0
        );
        vY = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r1) + 1
        );
        vZ = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r1) + 2
        );
        vW = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r1) + 3
        );
    }
    else
    {
        vW = M1.r1.m128.m128_f32;
        vX = XMPermutePS(vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = XMPermutePS(vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = XMPermutePS(vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = XMPermutePS(vW, _MM_SHUFFLE(3, 3, 3, 3));
    }

    vX = Sse::Multiply(vX, M2.r0.m128.m128_f32);
    vY = Sse::Multiply(vY, M2.r1.m128.m128_f32);
    vZ = Sse::Multiply(vZ, M2.r2.m128.m128_f32);
    vW = Sse::Multiply(vW, M2.r3.m128.m128_f32);

    vX = Sse::Add(vX, vZ);
    vY = Sse::Add(vY, vW);
    vX = Sse::Add(vX, vY);
    mResult.r1.m128.m128_f32 = vX;


    if(Avx::IsSupported)
    {
        vX = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r2) + 0
        );
        vY = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r2) + 1
        );
        vZ = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r2) + 2
        );
        vW = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r2) + 3
        );
    }
    else
    {
        vW = M1.r2.m128.m128_f32;
        vX = XMPermutePS(vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = XMPermutePS(vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = XMPermutePS(vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = XMPermutePS(vW, _MM_SHUFFLE(3, 3, 3, 3));
    }

    vX = Sse::Multiply(vX, M2.r0.m128.m128_f32);
    vY = Sse::Multiply(vY, M2.r1.m128.m128_f32);
    vZ = Sse::Multiply(vZ, M2.r2.m128.m128_f32);
    vW = Sse::Multiply(vW, M2.r3.m128.m128_f32);

    vX = Sse::Add(vX, vZ);
    vY = Sse::Add(vY, vW);
    vX = Sse::Add(vX, vY);
    mResult.r2.m128.m128_f32 = vX;


    if(Avx::IsSupported)
    {
        vX = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r3) + 0
        );
        vY = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r3) + 1
        );
        vZ = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r3) + 2
        );
        vW = Avx::BroadcastScalarToVector128(
            reinterpret_cast<float*>(&pM1->r3) + 3
        );
    }
    else
    {
        vW = M1.r3.m128.m128_f32;
        vX = XMPermutePS(vW, _MM_SHUFFLE(0, 0, 0, 0));
        vY = XMPermutePS(vW, _MM_SHUFFLE(1, 1, 1, 1));
        vZ = XMPermutePS(vW, _MM_SHUFFLE(2, 2, 2, 2));
        vW = XMPermutePS(vW, _MM_SHUFFLE(3, 3, 3, 3));
    }

    vX = Sse::Multiply(vX, M2.r0.m128.m128_f32);
    vY = Sse::Multiply(vY, M2.r1.m128.m128_f32);
    vZ = Sse::Multiply(vZ, M2.r2.m128.m128_f32);
    vW = Sse::Multiply(vW, M2.r3.m128.m128_f32);

    vX = Sse::Add(vX, vZ);
    vY = Sse::Add(vY, vW);
    vX = Sse::Add(vX, vY);
    mResult.r3.m128.m128_f32 = vX;

    return mResult;
#else
    return CAST_TO(M1.matrix * M2.matrix, XMMatrix);
#endif
}
