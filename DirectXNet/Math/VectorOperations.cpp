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
    g_XMMask3 = Vector128::Create(0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000U);
    g_XMFixUnsigned = Vector128::Create(32768.0f * 65536.0f);
    g_XMMaxInt = Vector128::Create(65536.0f * 32768.0f - 128.0f);
    g_XMMaxUInt = Vector128::Create(65536.0f * 65536.0f - 256.0f);
    g_XMUnsignedFix = Vector128::Create(32768.0f * 65536.0f);
    g_XMAbsMask = Vector128::Create(0x7FFFFFFF);
    g_XMIdentityR3 = Vector128::Create(0.0f, 0.0f, 0.0f, 1.0f);
    g_XMNegativeZero = Vector128::Create(0x80000000);
    g_XMOne = Vector128::Create(1.0f);
    g_XMZero = Vector128::Create(0.0f);
#endif
}

float DirectXNet::Math::DXMath::XMConvertToRadians(float fDegrees)
{
    return fDegrees * (Pi / 180.0f);
}

float DirectXNet::Math::DXMath::XMConvertToDegrees(float fRadians)
{
    return fRadians * (180.0f / Pi);
}

bool DirectXNet::Math::DXMath::XMComparisonAllTrue(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6True) == CRMaskCR6True);
}

bool DirectXNet::Math::DXMath::XMComparisonAnyTrue(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6False) != CRMaskCR6False);
}

bool DirectXNet::Math::DXMath::XMComparisonAllFalse(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6False) == CRMaskCR6False);
}

bool DirectXNet::Math::DXMath::XMComparisonAnyFalse(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6True) != CRMaskCR6True);
}

bool DirectXNet::Math::DXMath::XMComparisonMixed(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6) == 0);
}

bool DirectXNet::Math::DXMath::XMComparisonAllInBounds(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6Bounds) == CRMaskCR6Bounds);
}

bool DirectXNet::Math::DXMath::XMComparisonAnyOutOfBounds(unsigned __int32 CR)
{
    return (((CR)&CRMaskCR6Bounds) != CRMaskCR6Bounds);
}

#ifdef _NETCORE
Vector128<float> DirectXNet::Math::DXMath::XMPermutePS(
    Vector128<float> v, unsigned int c)
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
    XMVector vResult;
    vResult.vector.vector4_u32[0] = (0 - (C0 & 1)) & 0x3F800000;
    vResult.vector.vector4_u32[1] = (0 - (C1 & 1)) & 0x3F800000;
    vResult.vector.vector4_u32[2] = (0 - (C2 & 1)) & 0x3F800000;
    vResult.vector.vector4_u32[3] = (0 - (C3 & 1)) & 0x3F800000;
    return vResult;
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
    XMVector V;
    V.vector.vector4_u32 = Vector4UInt(IntConstant, IntConstant, IntConstant, IntConstant);
    return XMConvertVectorIntToFloat(V, DivExponent);
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
    XMVector V;
    V.vector.vector4_u32 = Vector4UInt(IntConstant, IntConstant, IntConstant, IntConstant);
    return V;
#endif
}

__INLINE XMVector DirectXNet::Math::DXMath::XMLoadInt(__int32 source)
{
#ifdef _NETCORE
    return CAST_TO(Sse::LoadScalarVector128((float*)&source), XMVector);
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
    return CAST_TO(Sse::LoadScalarVector128((float*)&source), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = source;
    V.vector.vector4_u32[1] = 0;
    V.vector.vector4_u32[2] = 0;
    V.vector.vector4_u32[3] = 0;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadFloat(float source)
{
#ifdef _NETCORE
    return CAST_TO(Sse::LoadScalarVector128(&source), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = source;
    V.vector.vector4_f32.Y = 0.0f;
    V.vector.vector4_f32.Z = 0.0f;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadInt2(unsigned __int32* pSource)
{
#ifdef _NETCORE
    return CAST_TO(Sse2::LoadScalarVector128((double*)pSource), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = pSource[0];
    V.vector.vector4_u32[1] = pSource[1];
    V.vector.vector4_u32[2] = 0;
    V.vector.vector4_u32[3] = 0;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadFloat2(XMFloat2* pSource)
{
#ifdef _NETCORE
    return CAST_TO(Sse2::LoadScalarVector128((double*)pSource), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = pSource->x;
    V.vector.vector4_f32.Y = pSource->y;
    V.vector.vector4_f32.Z = 0.0f;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadSInt2(XMInt2* pSource)
{
#ifdef _NETCORE
    Vector128<int> V = Vector128::AsInt32(Sse2::LoadScalarVector128((double*)pSource));
    return CAST_TO(Sse2::ConvertToVector128Single(V), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = 0.0f;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadUInt2(XMUInt2* pSource)
{
#ifdef _NETCORE
    Vector128<float> V = Vector128::AsSingle(Sse2::LoadScalarVector128((double*)pSource));
    Vector128<float> vMask = Sse::And(V, Vector128::AsSingle(g_XMNegativeZero));
    Vector128<float> vResult = Sse::Xor(V, vMask);
    vResult = Sse2::ConvertToVector128Single(Vector128::AsInt32(vResult));
    Vector128<int> iMask = Sse2::ShiftRightArithmetic(Vector128::AsInt32(vMask), 31);
    vMask = Sse::And(Vector128::AsSingle(iMask), g_XMFixUnsigned);
    vResult = Sse::Add(vResult, vMask);
    return CAST_TO(vResult, XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = 0.0f;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadInt3(unsigned __int32* pSource)
{
#ifdef _NETCORE
    Vector128<float> xy = Vector128::AsSingle(Sse2::LoadScalarVector128((double*)pSource));
    Vector128<float> z = Sse::LoadScalarVector128((float*)(pSource + 2));
    return CAST_TO(Sse::MoveLowToHigh(xy, z), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = pSource[0];
    V.vector.vector4_u32[1] = pSource[1];
    V.vector.vector4_u32[2] = pSource[2];
    V.vector.vector4_u32[3] = 0;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadFloat3(XMFloat3* pSource)
{
#ifdef _NETCORE
    Vector128<float> x = Sse::LoadScalarVector128(&pSource->x);
    Vector128<float> y = Sse::LoadScalarVector128(&pSource->y);
    Vector128<float> z = Sse::LoadScalarVector128(&pSource->z);
    Vector128<float> xy = Sse::UnpackLow(x, y);
    return CAST_TO(Sse::MoveLowToHigh(xy, z), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = pSource->x;
    V.vector.vector4_f32.Y = pSource->y;
    V.vector.vector4_f32.Z = pSource->z;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadSInt3(XMInt3* pSource)
{
#ifdef _NETCORE
    Vector128<float> xy = Vector128::AsSingle(Sse2::LoadScalarVector128((double*)pSource));
    Vector128<float> z = Sse::LoadScalarVector128((float*)(&pSource->z));
    Vector128<float> V = Sse::MoveLowToHigh(xy, z);
    return CAST_TO(Sse2::ConvertToVector128Single(Vector128::AsInt32(V)), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = (float)pSource->z;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadUInt3(XMUInt3* pSource)
{
#ifdef _NETCORE
    Vector128<float> xy = Vector128::AsSingle(Sse2::LoadScalarVector128((double*)pSource));
    Vector128<float> z = Sse::LoadScalarVector128((float*)(&pSource->z));
    Vector128<float> V = Sse::MoveLowToHigh(xy, z);
    Vector128<float> vMask = Sse::And(V, Vector128::AsSingle(g_XMNegativeZero));
    Vector128<float> vResult = Sse::Xor(V, vMask);
    vResult = Sse2::ConvertToVector128Single(Vector128::AsInt32(vResult));
    Vector128<int> iMask = Sse2::ShiftRightArithmetic(Vector128::AsInt32(vMask), 31);
    vMask = Sse::And(Vector128::AsSingle(iMask), g_XMFixUnsigned);
    vResult = Sse::Add(vResult, vMask);
    return CAST_TO(vResult, XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = (float)pSource->z;
    V.vector.vector4_f32.W = 0.0f;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadInt4(unsigned __int32* pSource)
{
#ifdef _NETCORE
    return CAST_TO(Sse2::LoadVector128(pSource), XMVector);
#else
    XMVector V;
    V.vector.vector4_u32[0] = pSource[0];
    V.vector.vector4_u32[1] = pSource[1];
    V.vector.vector4_u32[2] = pSource[2];
    V.vector.vector4_u32[3] = pSource[3];
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadFloat4(XMFloat4* pSource)
{
#ifdef _NETCORE
    return CAST_TO(Sse::LoadVector128(&pSource->x), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = pSource->x;
    V.vector.vector4_f32.Y = pSource->y;
    V.vector.vector4_f32.Z = pSource->z;
    V.vector.vector4_f32.W = pSource->w;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadSInt4(XMInt4* pSource)
{
#ifdef _NETCORE
    return CAST_TO(Sse2::ConvertToVector128Single(Sse2::LoadVector128((int*)pSource)), XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = (float)pSource->z;
    V.vector.vector4_f32.W = (float)pSource->w;
    return V;
#endif
}

XMVector DirectXNet::Math::DXMath::XMLoadUInt4(XMUInt4* pSource)
{
#ifdef _NETCORE
    Vector128<float> V = Vector128::AsSingle(Sse2::LoadVector128((unsigned int*)pSource));
    Vector128<float> vMask = Sse::And(V, Vector128::AsSingle(g_XMNegativeZero));
    Vector128<float> vResult = Sse::Xor(V, vMask);
    vResult = Sse2::ConvertToVector128Single(Vector128::AsInt32(vResult));
    Vector128<int> iMask = Sse2::ShiftRightArithmetic(Vector128::AsInt32(vMask), 31);
    vMask = Sse::And(Vector128::AsSingle(iMask), g_XMFixUnsigned);
    vResult = Sse::Add(vResult, vMask);
    return CAST_TO(vResult, XMVector);
#else
    XMVector V;
    V.vector.vector4_f32.X = (float)pSource->x;
    V.vector.vector4_f32.Y = (float)pSource->y;
    V.vector.vector4_f32.Z = (float)pSource->z;
    V.vector.vector4_f32.W = (float)pSource->w;
    return V;
#endif
}

XMMatrix DirectXNet::Math::DXMath::XMLoadFloat3x3(XMFloat3X3* pSource)
{
#ifdef _NETCORE
    Vector128<float> Z = Vector128::Create(0.0f);

    Vector128<float> V1 = Sse::LoadVector128(&pSource->_11);
    Vector128<float> V2 = Sse::LoadVector128(&pSource->_22);
    Vector128<float> V3 = Sse::LoadScalarVector128(&pSource->_33);

    Vector128<float> T1 = Sse::UnpackHigh(V1, Z);
    Vector128<float> T2 = Sse::UnpackLow(V2, Z);
    Vector128<float> T3 = Sse::Shuffle(V3, T2, _MM_SHUFFLE(0, 1, 0, 0));
    Vector128<float> T4 = Sse::MoveHighToLow(T2, T3);
    Vector128<float> T5 = Sse::MoveHighToLow(Z, T1);

    XMMatrix M;
    M.r0.m128.m128_f32 = Sse::MoveLowToHigh(V1, T1);
    M.r1.m128.m128_f32 = Sse::Add(T4, T5);
    M.r2.m128.m128_f32 = Sse::Shuffle(V2, V3, _MM_SHUFFLE(1, 0, 3, 2));
    M.r3.m128.m128_f32 = g_XMIdentityR3;

    return M;
#else
    XMMatrix M;
    M.r0.vector.vector4_f32 = Vector4(pSource->_11, pSource->_12, pSource->_13, 0.0f);
    M.r1.vector.vector4_f32 = Vector4(pSource->_21, pSource->_22, pSource->_23, 0.0f);
    M.r2.vector.vector4_f32 = Vector4(pSource->_31, pSource->_32, pSource->_33, 0.0f);
    M.r3.vector.vector4_f32 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
    return M;
#endif
}

XMMatrix DirectXNet::Math::DXMath::XMLoadFloat4x3(XMFloat4X3* pSource)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = Sse::LoadVector128(&pSource->_11);
    Vector128<float> vTemp2 = Sse::LoadVector128(&pSource->_22);
    Vector128<float> vTemp4 = Sse::LoadVector128(&pSource->_33);
    Vector128<float> vTemp3 = Sse::Shuffle(vTemp2, vTemp4, _MM_SHUFFLE(0, 0, 3, 2));
    vTemp2 = Sse::Shuffle(vTemp2, vTemp1, _MM_SHUFFLE(3, 3, 1, 0));
    vTemp2 = XMPermutePS(vTemp2, _MM_SHUFFLE(1, 1, 0, 2));
    vTemp1 = Sse::And(vTemp1, Vector128::AsSingle(g_XMMask3));
    vTemp2 = Sse::And(vTemp2, Vector128::AsSingle(g_XMMask3));
    vTemp3 = Sse::And(vTemp3, Vector128::AsSingle(g_XMMask3));
    Vector128<int> vTemp4i = Sse2::ShiftRightLogical128BitLane(Vector128::AsInt32(vTemp4), 32 / 8);
    vTemp4i = Sse2::Or(vTemp4i, Vector128::AsInt32(g_XMIdentityR3));

    XMMatrix M;
    M.r0.m128.m128_f32 = vTemp1;
    M.r1.m128.m128_f32 = vTemp2;
    M.r2.m128.m128_f32 = vTemp3;
    M.r3.m128.m128_f32 = Vector128::AsSingle(vTemp4i);

    return M;
#else
    XMMatrix M;
    M.r0.vector.vector4_f32 = Vector4(pSource->_11, pSource->_12, pSource->_13, 0.0f);
    M.r1.vector.vector4_f32 = Vector4(pSource->_21, pSource->_22, pSource->_23, 0.0f);
    M.r2.vector.vector4_f32 = Vector4(pSource->_31, pSource->_32, pSource->_33, 0.0f);
    M.r3.vector.vector4_f32 = Vector4(pSource->_41, pSource->_42, pSource->_43, 1.0f);
    return M;
#endif
}

XMMatrix DirectXNet::Math::DXMath::XMLoadFloat3x4(XMFloat3X4* pSource)
{
#ifdef _NETCORE
    XMMatrix M;
    M.r0.m128.m128_f32 = Sse::LoadVector128(&pSource->_11);
    M.r1.m128.m128_f32 = Sse::LoadVector128(&pSource->_21);
    M.r2.m128.m128_f32 = Sse::LoadVector128(&pSource->_31);
    M.r3.m128.m128_f32 = g_XMIdentityR3;

    Vector128<float> vTemp1 = Sse::Shuffle(M.r0.m128.m128_f32, M.r1.m128.m128_f32, _MM_SHUFFLE(1, 0, 1, 0));
    Vector128<float> vTemp3 = Sse::Shuffle(M.r0.m128.m128_f32, M.r1.m128.m128_f32, _MM_SHUFFLE(3, 2, 3, 2));
    Vector128<float> vTemp2 = Sse::Shuffle(M.r2.m128.m128_f32, M.r3.m128.m128_f32, _MM_SHUFFLE(1, 0, 1, 0));
    Vector128<float> vTemp4 = Sse::Shuffle(M.r2.m128.m128_f32, M.r3.m128.m128_f32, _MM_SHUFFLE(3, 2, 3, 2));
    XMMatrix mResult;
    
    mResult.r0.m128.m128_f32 = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(2, 0, 2, 0));
    mResult.r1.m128.m128_f32 = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(3, 1, 3, 1));
    mResult.r2.m128.m128_f32 = Sse::Shuffle(vTemp3, vTemp4, _MM_SHUFFLE(2, 0, 2, 0));
    mResult.r3.m128.m128_f32 = Sse::Shuffle(vTemp3, vTemp4, _MM_SHUFFLE(3, 1, 3, 1));
    return mResult;
#else
    XMMatrix M;
    M.r0.vector.vector4_f32 = Vector4(pSource->_11, pSource->_21, pSource->_31, 0.0f);
    M.r1.vector.vector4_f32 = Vector4(pSource->_12, pSource->_22, pSource->_32, 0.0f);
    M.r2.vector.vector4_f32 = Vector4(pSource->_13, pSource->_23, pSource->_33, 0.0f);
    M.r3.vector.vector4_f32 = Vector4(pSource->_14, pSource->_24, pSource->_34, 1.0f);
    return M;
#endif
}

XMMatrix DirectXNet::Math::DXMath::XMLoadFloat4x4(XMFloat4X4* pSource)
{
#ifdef _NETCORE
    XMMatrix M;
    M.r0.m128.m128_f32 = Sse::LoadVector128(&pSource->_11);
    M.r1.m128.m128_f32 = Sse::LoadVector128(&pSource->_21);
    M.r2.m128.m128_f32 = Sse::LoadVector128(&pSource->_31);
    M.r3.m128.m128_f32 = Sse::LoadVector128(&pSource->_41);
    return M;
#else
    XMMatrix M;
    M.r0.vector.vector4_f32 = Vector4(pSource->_11, pSource->_12, pSource->_13, pSource->_14);
    M.r1.vector.vector4_f32 = Vector4(pSource->_21, pSource->_22, pSource->_23, pSource->_24);
    M.r2.vector.vector4_f32 = Vector4(pSource->_31, pSource->_32, pSource->_33, pSource->_34);
    M.r3.vector.vector4_f32 = Vector4(pSource->_41, pSource->_42, pSource->_43, pSource->_44);
    return M;
#endif
}

void DirectXNet::Math::DXMath::XMStoreInt(__int32* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Sse::StoreScalar((float*)pDestination, V.m128.m128_f32);
#else
    *pDestination = (__int32)V.vector.vector4_u32[0];
#endif
}

void DirectXNet::Math::DXMath::XMStoreInt(unsigned __int32* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Sse::StoreScalar((float*)pDestination, V.m128.m128_f32);
#else
    *pDestination = V.vector.vector4_u32[0];
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat(float* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Sse::StoreScalar(pDestination, V.m128.m128_f32);
#else
    *pDestination = V.vector.vector4_f32.X;
#endif
}

void DirectXNet::Math::DXMath::XMStoreInt2(unsigned __int32* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> T = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar((float*)&pDestination[0], V.m128.m128_f32);
    Sse::StoreScalar((float*)&pDestination[1], T);
#else
    pDestination[0] = V.vector.vector4_u32[0];
    pDestination[1] = V.vector.vector4_u32[1];
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat2(XMFloat2* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> T = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar(&pDestination->x, V.m128.m128_f32);
    Sse::StoreScalar(&pDestination->y, T);
#else
    pDestination->x = V.vector.vector4_f32.X;
    pDestination->y = V.vector.vector4_f32.Y;
#endif
}

void DirectXNet::Math::DXMath::XMStoreSInt2(XMInt2* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vOverflow = Sse::CompareGreaterThan(V.m128.m128_f32, g_XMMaxInt);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(V.m128.m128_f32);
    Vector128<float> vResult = Sse::And(vOverflow, Vector128::AsSingle(g_XMAbsMask));
    vOverflow = Sse::AndNot(vOverflow, Vector128::AsSingle(vResulti));
    vOverflow = Sse::Or(vOverflow, vResult);
    Vector128<float> T = XMPermutePS(vOverflow, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar((float*)&pDestination->x, vOverflow);
    Sse::StoreScalar((float*)&pDestination->y, T);
#else
    pDestination->x = (int)V.vector.vector4_f32.X;
    pDestination->y = (int)V.vector.vector4_f32.Y;
#endif
}

void DirectXNet::Math::DXMath::XMStoreUInt2(XMUInt2* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = Sse::Max(V.m128.m128_f32, g_XMZero);
    Vector128<float> vOverflow = Sse::CompareGreaterThan(vResult, g_XMMaxUInt);
    Vector128<float> vValue = g_XMUnsignedFix;
    Vector128<float> vMask = Sse::CompareGreaterThanOrEqual(vResult, vValue);
    vValue = Sse::And(vValue, vMask);
    vResult = Sse::Subtract(vResult, vValue);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(vResult);
    vMask = Sse::And(vMask, Vector128::AsSingle(g_XMNegativeZero));
    vResult = Sse::Xor(Vector128::AsSingle(vResulti), vMask);
    vResult = Sse::Or(vResult, vOverflow);
    Vector128<float> T = XMPermutePS(vResult, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar((float*)&pDestination->x, vResult);
    Sse::StoreScalar((float*)&pDestination->y, T);
#else
    pDestination->x = (unsigned int)V.vector.vector4_f32.X;
    pDestination->y = (unsigned int)V.vector.vector4_f32.Y;
#endif
}

void DirectXNet::Math::DXMath::XMStoreInt3(unsigned __int32* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> T1 = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Vector128<float> T2 = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar((float*)pDestination, V.m128.m128_f32);
    Sse::StoreScalar((float*)&pDestination[1], T1);
    Sse::StoreScalar((float*)&pDestination[2], T2);
#else
    pDestination[0] = V.vector.vector4_u32[0];
    pDestination[1] = V.vector.vector4_u32[1];
    pDestination[2] = V.vector.vector4_u32[2];
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat3(XMFloat3* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> T1 = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Vector128<float> T2 = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar(&pDestination->x, V.m128.m128_f32);
    Sse::StoreScalar(&pDestination->y, T1);
    Sse::StoreScalar(&pDestination->z, T2);
#else
    pDestination->x = V.vector.vector4_f32.X;
    pDestination->y = V.vector.vector4_f32.Y;
    pDestination->z = V.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreSInt3(XMInt3* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vOverflow = Sse::CompareGreaterThan(V.m128.m128_f32, g_XMMaxInt);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(V.m128.m128_f32);
    Vector128<float> vResult = Sse::And(vOverflow, Vector128::AsSingle(g_XMAbsMask));
    vOverflow = Sse::AndNot(vOverflow, Vector128::AsSingle(vResulti));
    vOverflow = Sse::Or(vOverflow, vResult);
    Vector128<float> T1 = XMPermutePS(vOverflow, _MM_SHUFFLE(1, 1, 1, 1));
    Vector128<float> T2 = XMPermutePS(vOverflow, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar((float*)&pDestination->x, vOverflow);
    Sse::StoreScalar((float*)&pDestination->y, T1);
    Sse::StoreScalar((float*)&pDestination->z, T2);
#else
    pDestination->x = (int)V.vector.vector4_f32.X;
    pDestination->y = (int)V.vector.vector4_f32.Y;
    pDestination->z = (int)V.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreUInt3(XMUInt3* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = Sse::Max(V.m128.m128_f32, g_XMZero);
    Vector128<float> vOverflow = Sse::CompareGreaterThan(vResult, g_XMMaxUInt);
    Vector128<float> vValue = g_XMUnsignedFix;
    Vector128<float> vMask = Sse::CompareGreaterThanOrEqual(vResult, vValue);
    vValue = Sse::And(vValue, vMask);
    vResult = Sse::Subtract(vResult, vValue);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(vResult);
    vMask = Sse::And(vMask, Vector128::AsSingle(g_XMNegativeZero));
    vResult = Sse::Xor(Vector128::AsSingle(vResulti), vMask);
    vResult = Sse::Or(vResult, vOverflow);
    Vector128<float> T1 = XMPermutePS(vResult, _MM_SHUFFLE(1, 1, 1, 1));
    Vector128<float> T2 = XMPermutePS(vResult, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar((float*)&pDestination->x, vResult);
    Sse::StoreScalar((float*)&pDestination->y, T1);
    Sse::StoreScalar((float*)&pDestination->z, T2);
#else
    pDestination->x = (unsigned int)V.vector.vector4_f32.X;
    pDestination->y = (unsigned int)V.vector.vector4_f32.Y;
    pDestination->z = (unsigned int)V.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreInt4(unsigned __int32* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Sse2::Store(pDestination, V.m128.m128_u32);
#else
    pDestination[0] = V.vector.vector4_u32[0];
    pDestination[1] = V.vector.vector4_u32[1];
    pDestination[2] = V.vector.vector4_u32[2];
    pDestination[3] = V.vector.vector4_u32[3];
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat4(XMFloat4* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Sse::Store(&pDestination->x, V.m128.m128_f32);
#else
    pDestination->x = V.vector.vector4_f32.X;
    pDestination->y = V.vector.vector4_f32.Y;
    pDestination->z = V.vector.vector4_f32.Z;
    pDestination->w = V.vector.vector4_f32.W;
#endif
}

void DirectXNet::Math::DXMath::XMStoreSInt4(XMInt4* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vOverflow = Sse::CompareGreaterThan(V.m128.m128_f32, g_XMMaxInt);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(V.m128.m128_f32);
    Vector128<float> vResult = Sse::And(vOverflow, Vector128::AsSingle(g_XMAbsMask));
    vOverflow = Sse::AndNot(vOverflow, Vector128::AsSingle(vResulti));
    vOverflow = Sse::Or(vOverflow, vResult);
    Sse2::Store((int*)pDestination, Vector128::AsInt32(vOverflow));
#else
    pDestination->x = (int)V.vector.vector4_f32.X;
    pDestination->y = (int)V.vector.vector4_f32.Y;
    pDestination->z = (int)V.vector.vector4_f32.Z;
    pDestination->w = (int)V.vector.vector4_f32.W;
#endif
}

void DirectXNet::Math::DXMath::XMStoreUInt4(XMUInt4* pDestination, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = Sse::Max(V.m128.m128_f32, g_XMZero);
    Vector128<float> vOverflow = Sse::CompareGreaterThan(vResult, g_XMMaxUInt);
    Vector128<float> vValue = g_XMUnsignedFix;
    Vector128<float> vMask = Sse::CompareGreaterThanOrEqual(vResult, vValue);
    vValue = Sse::And(vValue, vMask);
    vResult = Sse::Subtract(vResult, vValue);
    Vector128<int> vResulti = Sse2::ConvertToVector128Int32WithTruncation(vResult);
    vMask = Sse::And(vMask, Vector128::AsSingle(g_XMNegativeZero));
    vResult = Sse::Xor(Vector128::AsSingle(vResulti), vMask);
    vResult = Sse::Or(vResult, vOverflow);
    Sse2::Store((unsigned int*)pDestination, Vector128::AsUInt32(vResult));
#else
    pDestination->x = (unsigned int)V.vector.vector4_f32.X;
    pDestination->y = (unsigned int)V.vector.vector4_f32.Y;
    pDestination->z = (unsigned int)V.vector.vector4_f32.Z;
    pDestination->w = (unsigned int)V.vector.vector4_f32.W;
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat3x3(XMFloat3X3* pDestination, FXMMatrix M)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = M.r0.m128.m128_f32;
    Vector128<float> vTemp2 = M.r1.m128.m128_f32;
    Vector128<float> vTemp3 = M.r2.m128.m128_f32;
    Vector128<float> vWork = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(0, 0, 2, 2));
    vTemp1 = Sse::Shuffle(vTemp1, vWork, _MM_SHUFFLE(2, 0, 1, 0));
    Sse::Store(&pDestination->_11, vTemp1);
    vTemp2 = Sse::Shuffle(vTemp2, vTemp3, _MM_SHUFFLE(1, 0, 2, 1));
    Sse::Store(&pDestination->_22, vTemp2);
    vTemp3 = XMPermutePS(vTemp3, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar(&pDestination->_33, vTemp3);
#else
    pDestination->_11 = M.r0.vector.vector4_f32.X;
    pDestination->_12 = M.r0.vector.vector4_f32.Y;
    pDestination->_13 = M.r0.vector.vector4_f32.Z;

    pDestination->_21 = M.r1.vector.vector4_f32.X;
    pDestination->_22 = M.r1.vector.vector4_f32.Y;
    pDestination->_23 = M.r1.vector.vector4_f32.Z;

    pDestination->_31 = M.r2.vector.vector4_f32.X;
    pDestination->_32 = M.r2.vector.vector4_f32.Y;
    pDestination->_33 = M.r2.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat4x3(XMFloat4X3* pDestination, FXMMatrix M)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = M.r0.m128.m128_f32;
    Vector128<float> vTemp2 = M.r1.m128.m128_f32;
    Vector128<float> vTemp3 = M.r2.m128.m128_f32;
    Vector128<float> vTemp4 = M.r3.m128.m128_f32;
    Vector128<float> vTemp2x = Sse::Shuffle(vTemp2, vTemp3, _MM_SHUFFLE(1, 0, 2, 1));
    vTemp2 = Sse::Shuffle(vTemp2, vTemp1, _MM_SHUFFLE(2, 2, 0, 0));
    vTemp1 = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(0, 2, 1, 0));
    vTemp3 = Sse::Shuffle(vTemp3, vTemp4, _MM_SHUFFLE(0, 0, 2, 2));
    vTemp3 = Sse::Shuffle(vTemp3, vTemp4, _MM_SHUFFLE(2, 1, 2, 0));
    Sse::Store(&pDestination->_11, vTemp1);
    Sse::Store(&pDestination->_22, vTemp2x);
    Sse::Store(&pDestination->_33, vTemp3);
#else
    pDestination->_11 = M.r0.vector.vector4_f32.X;
    pDestination->_12 = M.r0.vector.vector4_f32.Y;
    pDestination->_13 = M.r0.vector.vector4_f32.Z;

    pDestination->_21 = M.r1.vector.vector4_f32.X;
    pDestination->_22 = M.r1.vector.vector4_f32.Y;
    pDestination->_23 = M.r1.vector.vector4_f32.Z;

    pDestination->_31 = M.r2.vector.vector4_f32.X;
    pDestination->_32 = M.r2.vector.vector4_f32.Y;
    pDestination->_33 = M.r2.vector.vector4_f32.Z;

    pDestination->_41 = M.r3.vector.vector4_f32.X;
    pDestination->_42 = M.r3.vector.vector4_f32.Y;
    pDestination->_43 = M.r3.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat3x4(XMFloat3X4* pDestination, FXMMatrix M)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = Sse::Shuffle(M.r0.m128.m128_f32, M.r1.m128.m128_f32, _MM_SHUFFLE(1, 0, 1, 0));
    Vector128<float> vTemp3 = Sse::Shuffle(M.r0.m128.m128_f32, M.r1.m128.m128_f32, _MM_SHUFFLE(3, 2, 3, 2));
    Vector128<float> vTemp2 = Sse::Shuffle(M.r2.m128.m128_f32, M.r3.m128.m128_f32, _MM_SHUFFLE(1, 0, 1, 0));
    Vector128<float> vTemp4 = Sse::Shuffle(M.r2.m128.m128_f32, M.r3.m128.m128_f32, _MM_SHUFFLE(3, 2, 3, 2));

    Vector128<float> r0 = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(2, 0, 2, 0));
    Vector128<float> r1 = Sse::Shuffle(vTemp1, vTemp2, _MM_SHUFFLE(3, 1, 3, 1));
    Vector128<float> r2 = Sse::Shuffle(vTemp3, vTemp4, _MM_SHUFFLE(2, 0, 2, 0));

    Sse::Store(&pDestination->_11, r0);
    Sse::Store(&pDestination->_21, r1);
    Sse::Store(&pDestination->_31, r2);
#else
    pDestination->_11 = M.r0.vector.vector4_f32.X;
    pDestination->_12 = M.r1.vector.vector4_f32.X;
    pDestination->_13 = M.r2.vector.vector4_f32.X;
    pDestination->_14 = M.r3.vector.vector4_f32.X;

    pDestination->_21 = M.r0.vector.vector4_f32.Y;
    pDestination->_22 = M.r1.vector.vector4_f32.Y;
    pDestination->_23 = M.r2.vector.vector4_f32.Y;
    pDestination->_24 = M.r3.vector.vector4_f32.Y;

    pDestination->_31 = M.r0.vector.vector4_f32.Z;
    pDestination->_32 = M.r1.vector.vector4_f32.Z;
    pDestination->_33 = M.r2.vector.vector4_f32.Z;
    pDestination->_34 = M.r3.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMStoreFloat4x4(XMFloat4X4* pDestination, FXMMatrix M)
{
#ifdef _NETCORE
    Sse::Store(&pDestination->_11, M.r0.m128.m128_f32);
    Sse::Store(&pDestination->_21, M.r1.m128.m128_f32);
    Sse::Store(&pDestination->_31, M.r2.m128.m128_f32);
    Sse::Store(&pDestination->_41, M.r3.m128.m128_f32);
#else
    pDestination->_11 = M.r0.vector.vector4_f32.X;
    pDestination->_12 = M.r0.vector.vector4_f32.Y;
    pDestination->_13 = M.r0.vector.vector4_f32.Z;
    pDestination->_14 = M.r0.vector.vector4_f32.W;

    pDestination->_21 = M.r1.vector.vector4_f32.X;
    pDestination->_22 = M.r1.vector.vector4_f32.Y;
    pDestination->_23 = M.r1.vector.vector4_f32.Z;
    pDestination->_24 = M.r1.vector.vector4_f32.W;

    pDestination->_31 = M.r2.vector.vector4_f32.X;
    pDestination->_32 = M.r2.vector.vector4_f32.Y;
    pDestination->_33 = M.r2.vector.vector4_f32.Z;
    pDestination->_34 = M.r2.vector.vector4_f32.W;

    pDestination->_41 = M.r3.vector.vector4_f32.X;
    pDestination->_42 = M.r3.vector.vector4_f32.Y;
    pDestination->_43 = M.r3.vector.vector4_f32.Z;
    pDestination->_44 = M.r3.vector.vector4_f32.W;
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
