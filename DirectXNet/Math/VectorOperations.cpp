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
    g_XMOne = Vector128::Create(1.0f);
    g_XMEpsilon = Vector128::Create(1.192092896e-7f);
    g_XMInfinity = Vector128::Create(0x7F800000);
    g_XMQNaN = Vector128::Create(0x7FC00000);
    g_XMNegOneMask = Vector128::Create(0xFFFFFFFF);
    g_XMNoFraction = Vector128::Create(8388608.0f);
    g_XMFixUnsigned = Vector128::Create(32768.0f * 65536.0f);
    g_XMMaxInt = Vector128::Create(65536.0f * 32768.0f - 128.0f);
    g_XMMaxUInt = Vector128::Create(65536.0f * 65536.0f - 256.0f);
    g_XMUnsignedFix = Vector128::Create(32768.0f * 65536.0f);
    g_XMAbsMask = Vector128::Create(0x7FFFFFFF);
    g_XMIdentityR3 = Vector128::Create(0.0f, 0.0f, 0.0f, 1.0f);
    g_XMNegativeZero = Vector128::Create(0x80000000);
    g_XMOne = Vector128::Create(1.0f);
    g_XMZero = Vector128::Create(0.0f);
    g_XMNegativeOne = Vector128::Create(-1.0f);
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

XMVector DirectXNet::Math::DXMath::XMVectorZero()
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(0.0f), XMVector);
#else
    return CAST_TO(Vector4(0), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSet(float x, float y, float z, float w)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(x, y, z, w), XMVector);
#else
    return CAST_TO(Vector4(x, y, z, w), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetInt(
    unsigned __int32 x, unsigned __int32 y, unsigned __int32 z, unsigned __int32 w)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(x, y, z, w), XMVector);
#else
    return CAST_TO(Vector4UInt(x, y, z, w), XMVector);
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

XMVector DirectXNet::Math::DXMath::XMVectorReplicateInt(unsigned __int32 Value)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(Value), XMVector);
#else
    return CAST_TO(Vector4UInt(Value, Value, Value, Value), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorTrueInt()
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(-1), XMVector);
#else
    return CAST_TO(Vector4UInt(0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU, 0xFFFFFFFFU), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorFalseInt()
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(0.0f), XMVector);
#else
    return CAST_TO(Vector4(0.0f), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatX(FXMVector V)
{
#ifdef _NETCORE
    return CAST_TO(XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(0, 0, 0, 0)), XMVector);
#else
    return CAST_TO(Vector4(V.vector.vector4_f32.X), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatY(FXMVector V)
{
#ifdef _NETCORE
    return CAST_TO(XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1)), XMVector);
#else
    return CAST_TO(Vector4(V.vector.vector4_f32.Y), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatZ(FXMVector V)
{
#ifdef _NETCORE
    return CAST_TO(XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(2, 2, 2, 2)), XMVector);
#else
    return CAST_TO(Vector4(V.vector.vector4_f32.Z), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatW(FXMVector V)
{
#ifdef _NETCORE
    return CAST_TO(XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 3, 3, 3)), XMVector);
#else
    return CAST_TO(Vector4(V.vector.vector4_f32.W), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatOne()
{
#ifdef _NETCORE
    Vector128<float> one = g_XMOne;
    return CAST_TO(one, XMVector);
#else
    return CAST_TO(Vector4(1.0f), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatInfinity()
{
#ifdef _NETCORE
    Vector128<int> inf = g_XMInfinity;
    return CAST_TO(inf, XMVector);
#else
    return CAST_TO(Vector4UInt(0x7F800000, 0x7F800000, 0x7F800000, 0x7F800000), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatQNaN()
{
#ifdef _NETCORE
    Vector128<int> nan = g_XMQNaN;
    return CAST_TO(nan, XMVector);
#else
    return CAST_TO(Vector4UInt(0x7FC00000, 0x7FC00000, 0x7FC00000, 0x7FC00000), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatEpsilon()
{
#ifdef _NETCORE
    Vector128<float> eps = g_XMEpsilon;
    return CAST_TO(eps, XMVector);
#else
    return CAST_TO(Vector4UInt(0x34000000, 0x34000000, 0x34000000, 0x34000000), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSplatSignMask()
{
#ifdef _NETCORE
    return CAST_TO(Vector128::Create(0x80000000), XMVector);
#else
    return CAST_TO(Vector4UInt(0x80000000U, 0x80000000U, 0x80000000U, 0x80000000U), XMVector);
#endif
}

float DirectXNet::Math::DXMath::XMVectorGetByIndex(FXMVector V, int i)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_f32, i);
#else
    switch(i)
    {
    case 0:
        return V.vector.vector4_f32.X;
    case 1:
        return V.vector.vector4_f32.Y;
    case 2:
        return V.vector.vector4_f32.Z;
    case 3:
        return V.vector.vector4_f32.W;
    default:
        throw gcnew IndexOutOfRangeException();
    }
#endif
}

float DirectXNet::Math::DXMath::XMVectorGetX(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::ToScalar(V.m128.m128_f32);
#else
    return V.vector.vector4_f32.X;
#endif
}

float DirectXNet::Math::DXMath::XMVectorGetY(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_f32, 1);
#else
    return V.vector.vector4_f32.Y;
#endif
}

float DirectXNet::Math::DXMath::XMVectorGetZ(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_f32, 2);
#else
    return V.vector.vector4_f32.Z;
#endif
}

float DirectXNet::Math::DXMath::XMVectorGetW(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_f32, 3);
#else
    return V.vector.vector4_f32.W;
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetByIndexPtr(float* f, FXMVector V, int i)
{
#ifdef _NETCORE
    *f = Vector128::GetElement(V.m128.m128_f32, i);
#else
    switch(i)
    {
    case 0:
        *f = V.vector.vector4_f32.X;
        break;
    case 1:
        *f = V.vector.vector4_f32.Y;
        break;
    case 2:
        *f = V.vector.vector4_f32.Z;
        break;
    case 3:
        *f = V.vector.vector4_f32.W;
        break;
    default:
        throw gcnew IndexOutOfRangeException();
    }
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetXPtr(float* x, FXMVector V)
{
#ifdef _NETCORE
    Sse::StoreScalar(x, V.m128.m128_f32);
#else
    *x = V.vector.vector4_f32.X;
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetYPtr(float* y, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar(y, vResult);
#else
    *y = V.vector.vector4_f32.Y;
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetZPtr(float* z, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar(z, vResult);
#else
    *z = V.vector.vector4_f32.Z;
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetWPtr(float* w, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 3, 3, 3));
    Sse::StoreScalar(w, vResult);
#else
    *w = V.vector.vector4_f32.W;
#endif
}

unsigned __int32 DirectXNet::Math::DXMath::XMVectorGetIntByIndex(FXMVector V, int i)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_u32, i);
#else
    return V.vector.vector4_u32[i];
#endif
}

unsigned __int32 DirectXNet::Math::DXMath::XMVectorGetIntX(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::ToScalar(V.m128.m128_u32);
#else
    return V.vector.vector4_u32[0];
#endif
}

unsigned __int32 DirectXNet::Math::DXMath::XMVectorGetIntY(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_u32, 1);
#else
    return V.vector.vector4_u32[1];
#endif
}

unsigned __int32 DirectXNet::Math::DXMath::XMVectorGetIntZ(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_u32, 2);
#else
    return V.vector.vector4_u32[2];
#endif
}

unsigned __int32 DirectXNet::Math::DXMath::XMVectorGetIntW(FXMVector V)
{
#ifdef _NETCORE
    return Vector128::GetElement(V.m128.m128_u32, 3);
#else
    return V.vector.vector4_u32[3];
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetIntByIndexPtr(unsigned __int32* x, FXMVector V, int i)
{
#ifdef _NETCORE
    *x = Vector128::GetElement(V.m128.m128_u32, i);
#else
    *x = V.vector.vector4_u32[i];
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetIntXPtr(unsigned __int32* x, FXMVector V)
{
#ifdef _NETCORE
    Sse::StoreScalar((float*)x, V.m128.m128_f32);
#else
    *x = V.vector.vector4_u32[0];
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetIntYPtr(unsigned __int32* y, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(1, 1, 1, 1));
    Sse::StoreScalar((float*)y, vResult);
#else
    *y = V.vector.vector4_u32[1];
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetIntZPtr(unsigned __int32* z, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(2, 2, 2, 2));
    Sse::StoreScalar((float*)z, vResult);
#else
    *z = V.vector.vector4_u32[2];
#endif
}

void DirectXNet::Math::DXMath::XMVectorGetIntWPtr(unsigned __int32* w, FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 3, 3, 3));
    Sse::StoreScalar((float*)w, vResult);
#else
    *w = V.vector.vector4_u32[3];
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetByIndex(FXMVector V, float f, int i)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::WithElement(V.m128.m128_f32, i, f), XMVector);
#else
    XMVector U = V;
    switch(i)
    {
    case 0:
        U.vector.vector4_f32.X = f;
        break;
    case 1:
        U.vector.vector4_f32.Y = f;
        break;
    case 2:
        U.vector.vector4_f32.Z = f;
        break;
    case 3:
        U.vector.vector4_f32.W = f;
        break;
    default:
        throw gcnew IndexOutOfRangeException();
    }

    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetX(FXMVector V, float x)
{
#ifdef _NETCORE
    Vector128<float> vResult = Vector128::CreateScalar(x);
    vResult = Sse::MoveScalar(V.m128.m128_f32, vResult);
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.X = x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetY(FXMVector V, float y)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 2, 0, 1));
    Vector128<float> vTemp = Vector128::CreateScalar(y);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 2, 0, 1));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.Y = y;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetZ(FXMVector V, float z)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 0, 1, 2));
    Vector128<float> vTemp = Vector128::CreateScalar(z);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 0, 1, 2));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.Z = z;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetW(FXMVector V, float w)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(0, 2, 1, 3));
    Vector128<float> vTemp = Vector128::CreateScalar(w);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(0, 2, 1, 3));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.W = w;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetByIndexPtr(FXMVector V, float* f, int i)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::WithElement(V.m128.m128_f32, i, *f), XMVector);
#else
    XMVector U = V;
    switch(i)
    {
    case 0:
        U.vector.vector4_f32.X = *f;
        break;
    case 1:
        U.vector.vector4_f32.Y = *f;
        break;
    case 2:
        U.vector.vector4_f32.Z = *f;
        break;
    case 3:
        U.vector.vector4_f32.W = *f;
        break;
    default:
        throw gcnew IndexOutOfRangeException();
    }

    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetXPtr(FXMVector V, float* x)
{
#ifdef _NETCORE
    Vector128<float> vResult = Sse::LoadScalarVector128(x);
    vResult = Sse::MoveScalar(V.m128.m128_f32, vResult);
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.X = *x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetYPtr(FXMVector V, float* y)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 2, 0, 1));
    Vector128<float> vTemp = Sse::LoadScalarVector128(y);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 2, 0, 1));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.Y = *y;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetZPtr(FXMVector V, float* z)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 0, 1, 2));
    Vector128<float> vTemp = Sse::LoadScalarVector128(z);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 0, 1, 2));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.Z = *z;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetWPtr(FXMVector V, float* w)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(0, 2, 1, 3));
    Vector128<float> vTemp = Sse::LoadScalarVector128(w);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(0, 2, 1, 3));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_f32.W = *w;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntByIndex(FXMVector V, unsigned __int32 x, int i)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::WithElement(V.m128.m128_u32, i, x), XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[i] = x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntX(FXMVector V, unsigned __int32 x)
{
#ifdef _NETCORE
    Vector128<int> vTemp = Sse2::ConvertScalarToVector128Int32((int)x);
    Vector128<float> vResult = Sse::MoveScalar(V.m128.m128_f32, Vector128::AsSingle(vTemp));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[0] = x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntY(FXMVector V, unsigned __int32 y)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 2, 0, 1));
    Vector128<int> vTemp = Sse2::ConvertScalarToVector128Int32((int)y);
    vResult = Sse::MoveScalar(vResult, Vector128::AsSingle(vTemp));
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 2, 0, 1));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[1] = y;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntZ(FXMVector V, unsigned __int32 z)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 0, 1, 2));
    Vector128<int> vTemp = Sse2::ConvertScalarToVector128Int32((int)z);
    vResult = Sse::MoveScalar(vResult, Vector128::AsSingle(vTemp));
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 0, 1, 2));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[2] = z;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntW(FXMVector V, unsigned __int32 w)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(0, 2, 1, 3));
    Vector128<int> vTemp = Sse2::ConvertScalarToVector128Int32((int)w);
    vResult = Sse::MoveScalar(vResult, Vector128::AsSingle(vTemp));
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(0, 2, 1, 3));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[3] = w;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntByIndexPtr(FXMVector V, unsigned __int32* x, int i)
{
#ifdef _NETCORE
    return CAST_TO(Vector128::WithElement(V.m128.m128_u32, i, *x), XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[i] = *x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntXPtr(FXMVector V, unsigned __int32* x)
{
#ifdef _NETCORE
    Vector128<float> vTemp = Sse::LoadScalarVector128((float*)x);
    Vector128<float> vResult = Sse::MoveScalar(V.m128.m128_f32, vTemp);
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[0] = *x;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntYPtr(FXMVector V, unsigned __int32* y)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 2, 0, 1));
    Vector128<float> vTemp = Sse::LoadScalarVector128((float*)y);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 2, 0, 1));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[1] = *y;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntZPtr(FXMVector V, unsigned __int32* z)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(3, 0, 1, 2));
    Vector128<float> vTemp = Sse::LoadScalarVector128((float*)z);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(3, 0, 1, 2));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[2] = *z;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSetIntWPtr(FXMVector V, unsigned __int32* w)
{
#ifdef _NETCORE
    Vector128<float> vResult = XMPermutePS(V.m128.m128_f32, _MM_SHUFFLE(0, 2, 1, 3));
    Vector128<float> vTemp = Sse::LoadScalarVector128((float*)w);
    vResult = Sse::MoveScalar(vResult, vTemp);
    vResult = XMPermutePS(vResult, _MM_SHUFFLE(0, 2, 1, 3));
    return CAST_TO(vResult, XMVector);
#else
    XMVector U = V;
    U.vector.vector4_u32[3] = *w;
    return U;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSwizzle(
    FXMVector V, unsigned __int32 E0, unsigned __int32 E1,
    unsigned __int32 E2, unsigned __int32 E3)
{
#ifdef _NETCORE
    if(Avx::IsSupported)
    {
        unsigned __int32 elem[4] = { E0, E1, E2, E3 };
        Vector128<__int32> vControl = Sse2::LoadVector128((int*)&elem[0]);
        return CAST_TO(Avx::PermuteVar(V.m128.m128_f32, vControl), XMVector);
    }
    else
    {
        interior_ptr<unsigned __int32> aPtr = (interior_ptr<unsigned __int32>)&V;

        XMVector Result;
        unsigned __int32* pWork = (unsigned __int32*)&Result;

        pWork[0] = aPtr[E0];
        pWork[1] = aPtr[E1];
        pWork[2] = aPtr[E2];
        pWork[3] = aPtr[E3];

        return Result;
    }
#else
    Vector4UInt Result(V.vector.vector4_u32[E0], V.vector.vector4_u32[E1], V.vector.vector4_u32[E2], V.vector.vector4_u32[E3]);
    return CAST_TO(Result, XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorPermute(
    FXMVector V1, FXMVector V2, unsigned __int32 PermuteX, unsigned __int32 PermuteY,
    unsigned __int32 PermuteZ, unsigned int PermuteW)
{
#ifdef _NETCORE
    if(Avx::IsSupported)
    {
        Vector128<int> three = Vector128::Create(3);

        unsigned int elem[4] = { PermuteX, PermuteY, PermuteZ, PermuteW };
        Vector128<int> vControl = Sse2::LoadVector128((int*)&elem[0]);

        Vector128<int> vSelect = Sse2::CompareGreaterThan(vControl, three);
        vControl = Vector128::AsInt32(Sse::And(Vector128::AsSingle(vControl), Vector128::AsSingle(vControl)));

        Vector128<float> shuffled1 = Avx::PermuteVar(V1.m128.m128_f32, vControl);
        Vector128<float> shuffled2 = Avx::PermuteVar(V2.m128.m128_f32, vControl);

        Vector128<float> masked1 = Sse::AndNot(Vector128::AsSingle(vSelect), shuffled1);
        Vector128<float> masked2 = Sse::And(Vector128::AsSingle(vSelect), shuffled2);

        return CAST_TO(Sse::Or(masked1, masked2), XMVector);
    }
    else
    {
        unsigned __int32* aPtr[2];
        pin_ptr<XMVector> pV1 = &V1;
        pin_ptr<XMVector> pV2 = &V2;
        aPtr[0] = (unsigned __int32*)pV1;
        aPtr[1] = (unsigned __int32*)pV2;

        XMVector Result;
        unsigned __int32* pWork = (unsigned __int32*)&Result;

        unsigned __int32 i0 = PermuteX & 3;
        unsigned __int32 vi0 = PermuteX >> 2;
        pWork[0] = aPtr[vi0][i0];

        unsigned __int32 i1 = PermuteY & 3;
        unsigned __int32 vi1 = PermuteY >> 2;
        pWork[1] = aPtr[vi1][i1];

        unsigned __int32 i2 = PermuteZ & 3;
        unsigned __int32 vi2 = PermuteZ >> 2;
        pWork[2] = aPtr[vi2][i2];

        unsigned __int32 i3 = PermuteW & 3;
        unsigned __int32 vi3 = PermuteW >> 2;
        pWork[3] = aPtr[vi3][i3];

        return Result;
    }
#else
    unsigned __int32* aPtr[2];
    pin_ptr<XMVector> pV1 = &V1;
    pin_ptr<XMVector> pV2 = &V2;
    aPtr[0] = (unsigned __int32*)pV1;
    aPtr[1] = (unsigned __int32*)pV2;

    XMVector Result;
    unsigned __int32* pWork = (unsigned __int32*)&Result;

    unsigned __int32 i0 = PermuteX & 3;
    unsigned __int32 vi0 = PermuteX >> 2;
    pWork[0] = aPtr[vi0][i0];

    unsigned __int32 i1 = PermuteY & 3;
    unsigned __int32 vi1 = PermuteY >> 2;
    pWork[1] = aPtr[vi1][i1];

    unsigned __int32 i2 = PermuteZ & 3;
    unsigned __int32 vi2 = PermuteZ >> 2;
    pWork[2] = aPtr[vi2][i2];

    unsigned __int32 i3 = PermuteW & 3;
    unsigned __int32 vi3 = PermuteW >> 2;
    pWork[3] = aPtr[vi3][i3];

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSelectControl(unsigned __int32 VectorIndex0, unsigned __int32 VectorIndex1, unsigned __int32 VectorIndex2, unsigned __int32 VectorIndex3)
{
#ifdef _NETCORE
    Vector128<int> vTemp = Vector128::Create(
        (int)VectorIndex0, (int)VectorIndex1, (int)VectorIndex2, (int)VectorIndex3);
    vTemp = Sse2::CompareGreaterThan(vTemp, Vector128::AsInt32(g_XMZero));
    return CAST_TO(vTemp, XMVector);
#else
    XMVector ControlVector;

    ControlVector.vector.vector4_u32[0] = VectorIndex0 == 0 ? Select0 : Select1;
    ControlVector.vector.vector4_u32[1] = VectorIndex1 == 0 ? Select0 : Select1;
    ControlVector.vector.vector4_u32[2] = VectorIndex2 == 0 ? Select0 : Select1;
    ControlVector.vector.vector4_u32[3] = VectorIndex3 == 0 ? Select0 : Select1;

    return ControlVector;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSelect(FXMVector V1, FXMVector V2, FXMVector Control)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = Sse::AndNot(Control.m128.m128_f32, V1.m128.m128_f32);
    Vector128<float> vTemp2 = Sse::And(V2.m128.m128_f32, Control.m128.m128_f32);
    return CAST_TO(Sse::Or(vTemp1, vTemp2), XMVector);
#else
    XMVector Result;

    Result.vector.vector4_u32[0] = (V1.vector.vector4_u32[0] & ~Control.vector.vector4_u32[0]) |
        (V2.vector.vector4_u32[0] & Control.vector.vector4_u32[0]);
    Result.vector.vector4_u32[1] = (V1.vector.vector4_u32[1] & ~Control.vector.vector4_u32[1]) |
        (V2.vector.vector4_u32[1] & Control.vector.vector4_u32[1]);
    Result.vector.vector4_u32[2] = (V1.vector.vector4_u32[2] & ~Control.vector.vector4_u32[2]) |
        (V2.vector.vector4_u32[2] & Control.vector.vector4_u32[2]);
    Result.vector.vector4_u32[3] = (V1.vector.vector4_u32[3] & ~Control.vector.vector4_u32[3]) |
        (V2.vector.vector4_u32[3] & Control.vector.vector4_u32[3]);

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorMergeXY(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::UnpackLow(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Result;

    Result.vector.vector4_u32[0] = V1.vector.vector4_u32[0];
    Result.vector.vector4_u32[1] = V2.vector.vector4_u32[0];
    Result.vector.vector4_u32[2] = V1.vector.vector4_u32[1];
    Result.vector.vector4_u32[3] = V2.vector.vector4_u32[1];

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorMergeZW(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::UnpackHigh(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Result;

    Result.vector.vector4_u32[0] = V1.vector.vector4_u32[2];
    Result.vector.vector4_u32[1] = V2.vector.vector4_u32[2];
    Result.vector.vector4_u32[2] = V1.vector.vector4_u32[3];
    Result.vector.vector4_u32[3] = V2.vector.vector4_u32[3];

    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorShiftLeft(
    FXMVector V1, FXMVector V2, unsigned __int32 Elements)
{
    return XMVectorPermute(V1, V2, Elements, Elements + 1, Elements + 2, Elements + 3);
}

XMVector DirectXNet::Math::DXMath::XMVectorRotateLeft(FXMVector V, unsigned __int32 Elements)
{
    return XMVectorSwizzle(V, Elements & 3, (Elements + 1) & 3, (Elements + 2) & 3, (Elements + 3) & 3);
}

XMVector DirectXNet::Math::DXMath::XMVectorRotateRight(FXMVector V, unsigned __int32 Elements)
{
    return XMVectorSwizzle(V, (4 - Elements) & 3, (5 - Elements) & 3, (6 - Elements) & 3, (7 - Elements) & 3);
}

XMVector DirectXNet::Math::DXMath::XMVectorInsert(
    FXMVector VD, FXMVector VS, unsigned __int32 VSLeftRotateElements,
    unsigned __int32 Select0, unsigned __int32 Select1,
    unsigned __int32 Select2, unsigned __int32 Select3)
{
    XMVector Control = XMVectorSelectControl(Select0 & 1, Select1 & 1, Select2 & 1, Select3 & 1);
    return XMVectorSelect(VD, XMVectorRotateLeft(VS, VSLeftRotateElements), Control);
}

XMVector DirectXNet::Math::DXMath::XMVectorEqual(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareEqual(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X == V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y == V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z == V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W == V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorEqualR(
    unsigned __int32% CR, FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<float> vTemp = Sse::CompareEqual(V1.m128.m128_f32, V2.m128.m128_f32);
    CR = 0;
    int iTest = Sse::MoveMask(vTemp);
    if(iTest == 0xf)
    {
        CR = CRMaskCR6True;
    }
    else if(!iTest)
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(vTemp, XMVector);
#else
    unsigned __int32 ux = (V1.vector.vector4_f32.X == V2.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uy = (V1.vector.vector4_f32.Y == V2.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uz = (V1.vector.vector4_f32.Z == V2.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uw = (V1.vector.vector4_f32.W == V2.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;
    CR = 0;
    if(ux & uy & uz & uw)
    {
        CR = CRMaskCR6True;
    }
    else if(!(ux | uy | uz | uw))
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(Vector4UInt(ux, uy, uz, uw), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorEqualInt(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse2::CompareEqual(V1.m128.m128_u32, V2.m128.m128_u32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_u32[0] == V2.vector.vector4_u32[0]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_u32[1] == V2.vector.vector4_u32[1]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_u32[2] == V2.vector.vector4_u32[2]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_u32[3] == V2.vector.vector4_u32[3]) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorEqualIntR(
    unsigned __int32% CR, FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<unsigned __int32> V = Sse2::CompareEqual(V1.m128.m128_u32, V2.m128.m128_u32);
    int iTemp = Sse::MoveMask(Vector128::AsSingle(V));
    CR = 0;
    if(iTemp == 0x0F)
    {
        CR = CRMaskCR6True;
    }
    else if(!iTemp)
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(V, XMVector);
#else
    XMVector Control = XMVectorEqualInt(V1, V2);

    CR = 0;
    if(XMVector4EqualInt(Control, XMVectorTrueInt()))
    {
        CR |= CRMaskCR6True;
    }
    else if(XMVector4EqualInt(Control, XMVectorFalseInt()))
    {
        CR |= CRMaskCR6False;
    }

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorNearEqual(FXMVector V1, FXMVector V2, FXMVector Epsilon)
{
#ifdef _NETCORE
    Vector128<float> vDelta = Sse::Subtract(V1.m128.m128_f32, V2.m128.m128_f32);
    Vector128<float> vTemp = Vector128::Create(0.0f);
    vTemp = Sse::Subtract(vTemp, vDelta);
    vTemp = Sse::Max(vTemp, vDelta);
    vTemp = Sse::CompareLessThanOrEqual(vTemp, Epsilon.m128.m128_f32);
    return CAST_TO(vTemp, XMVector);
#else
    float fDeltax = V1.vector.vector4_f32.X - V2.vector.vector4_f32.X;
    float fDeltay = V1.vector.vector4_f32.Y - V2.vector.vector4_f32.Y;
    float fDeltaz = V1.vector.vector4_f32.Z - V2.vector.vector4_f32.Z;
    float fDeltaw = V1.vector.vector4_f32.W - V2.vector.vector4_f32.W;

    fDeltax = System::Math::Abs(fDeltax);
    fDeltay = System::Math::Abs(fDeltay);
    fDeltaz = System::Math::Abs(fDeltaz);
    fDeltaw = System::Math::Abs(fDeltaw);

    XMVector Control;

    Control.vector.vector4_u32[0] = (fDeltax <= Epsilon.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[1] = (fDeltay <= Epsilon.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[2] = (fDeltaz <= Epsilon.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[3] = (fDeltaw <= Epsilon.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorNotEqual(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareNotEqual(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X != V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y != V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z != V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W != V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorNotEqualInt(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<unsigned __int32> V = Sse2::CompareEqual(V1.m128.m128_u32, V2.m128.m128_u32);
    return CAST_TO(Sse::Xor(Vector128::AsSingle(V), Vector128::AsSingle(g_XMNegOneMask)), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_u32[0] != V2.vector.vector4_u32[0]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_u32[1] != V2.vector.vector4_u32[1]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_u32[2] != V2.vector.vector4_u32[2]) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_u32[3] != V2.vector.vector4_u32[3]) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorGreater(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareGreaterThan(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X > V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y > V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z > V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W > V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorGreaterR(
    unsigned __int32% CR, FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<float> vTemp = Sse::CompareGreaterThan(V1.m128.m128_f32, V2.m128.m128_f32);
    CR = 0;
    int iTest = Sse::MoveMask(vTemp);
    if(iTest == 0xf)
    {
        CR = CRMaskCR6True;
    }
    else if(!iTest)
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(vTemp, XMVector);
#else
    unsigned __int32 ux = (V1.vector.vector4_f32.X > V2.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uy = (V1.vector.vector4_f32.Y > V2.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uz = (V1.vector.vector4_f32.Z > V2.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uw = (V1.vector.vector4_f32.W > V2.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;
    CR = 0;
    if(ux & uy & uz & uw)
    {
        CR = CRMaskCR6True;
    }
    else if(!(ux | uy | uz | uw))
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(Vector4UInt(ux, uy, uz, uw), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorGreaterOrEqual(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareGreaterThanOrEqual(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X >= V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y >= V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z >= V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W >= V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorGreaterOrEqualR(unsigned __int32% CR, FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<float> vTemp = Sse::CompareGreaterThanOrEqual(V1.m128.m128_f32, V2.m128.m128_f32);
    CR = 0;
    int iTest = Sse::MoveMask(vTemp);
    if(iTest == 0xf)
    {
        CR = CRMaskCR6True;
    }
    else if(!iTest)
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(vTemp, XMVector);
#else
    unsigned __int32 ux = (V1.vector.vector4_f32.X >= V2.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uy = (V1.vector.vector4_f32.Y >= V2.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uz = (V1.vector.vector4_f32.Z >= V2.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    unsigned __int32 uw = (V1.vector.vector4_f32.W >= V2.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;
    CR = 0;
    if(ux & uy & uz & uw)
    {
        CR = CRMaskCR6True;
    }
    else if(!(ux | uy | uz | uw))
    {
        CR = CRMaskCR6False;
    }

    return CAST_TO(Vector4UInt(ux, uy, uz, uw), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorLess(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareLessThan(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X < V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y < V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z < V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W < V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorLessOrEqual(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareLessThanOrEqual(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V1.vector.vector4_f32.X <= V2.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V1.vector.vector4_f32.Y <= V2.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V1.vector.vector4_f32.Z <= V2.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V1.vector.vector4_f32.W <= V2.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorInBounds(FXMVector V, FXMVector Bounds)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = Sse::CompareLessThanOrEqual(V.m128.m128_f32, Bounds.m128.m128_f32);
    Vector128<float> vTemp2 = Sse::Multiply(Bounds.m128.m128_f32, g_XMNegativeOne);
    vTemp2 = Sse::CompareLessThanOrEqual(vTemp2, V.m128.m128_f32);
    vTemp1 = Sse::And(vTemp1, vTemp2);
    return CAST_TO(vTemp1, XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = (V.vector.vector4_f32.X <= Bounds.vector.vector4_f32.X
                                     && V.vector.vector4_f32.X >= -Bounds.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[1] = (V.vector.vector4_f32.Y <= Bounds.vector.vector4_f32.Y
                                     && V.vector.vector4_f32.Y >= -Bounds.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[2] = (V.vector.vector4_f32.Z <= Bounds.vector.vector4_f32.Z
                                     && V.vector.vector4_f32.Z >= -Bounds.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    Control.vector.vector4_u32[3] = (V.vector.vector4_f32.W <= Bounds.vector.vector4_f32.W
                                     && V.vector.vector4_f32.W >= -Bounds.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorInBoundsR(unsigned __int32% CR, FXMVector V, FXMVector Bounds)
{
#ifdef _NETCORE
    Vector128<float> vTemp1 = Sse::CompareLessThanOrEqual(V.m128.m128_f32, Bounds.m128.m128_f32);
    Vector128<float> vTemp2 = Sse::Multiply(Bounds.m128.m128_f32, g_XMNegativeOne);
    vTemp2 = Sse::CompareLessThanOrEqual(vTemp2, V.m128.m128_f32);
    vTemp1 = Sse::And(vTemp1, vTemp2);

    CR = 0;
    if(Sse::MoveMask(vTemp1) == 0xf)
    {
        CR = CRMaskCR6Bounds;
    }
    return CAST_TO(vTemp1, XMVector);
#else
    unsigned __int32 ux = (V.vector.vector4_f32.X <= Bounds.vector.vector4_f32.X
                                     && V.vector.vector4_f32.X >= -Bounds.vector.vector4_f32.X) ?
        0xFFFFFFFF : 0;
    unsigned __int32 uy = (V.vector.vector4_f32.Y <= Bounds.vector.vector4_f32.Y
                                     && V.vector.vector4_f32.Y >= -Bounds.vector.vector4_f32.Y) ?
        0xFFFFFFFF : 0;
    unsigned __int32 uz = (V.vector.vector4_f32.Z <= Bounds.vector.vector4_f32.Z
                                     && V.vector.vector4_f32.Z >= -Bounds.vector.vector4_f32.Z) ?
        0xFFFFFFFF : 0;
    unsigned __int32 uw = (V.vector.vector4_f32.W <= Bounds.vector.vector4_f32.W
                                     && V.vector.vector4_f32.W >= -Bounds.vector.vector4_f32.W) ?
        0xFFFFFFFF : 0;

    CR = 0;
    if(ux & uy & uz & uw)
    {
        CR = CRMaskCR6Bounds;
    }
    return CAST_TO(Vector4UInt(ux, uy, uz, uw), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorIsNaN(FXMVector V)
{
#ifdef _NETCORE
    return CAST_TO(Sse::CompareNotEqual(V.m128.m128_f32, V.m128.m128_f32), XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = Single::IsNaN(V.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[1] = Single::IsNaN(V.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[2] = Single::IsNaN(V.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[3] = Single::IsNaN(V.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorIsInfinite(FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> vTemp = Sse::And(V.m128.m128_f32, Vector128::AsSingle(g_XMAbsMask));
    vTemp = Sse::CompareEqual(vTemp, Vector128::AsSingle(g_XMInfinity));
    return CAST_TO(vTemp, XMVector);
#else
    XMVector Control;

    Control.vector.vector4_u32[0] = Single::IsInfinity(V.vector.vector4_f32.X) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[1] = Single::IsInfinity(V.vector.vector4_f32.Y) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[2] = Single::IsInfinity(V.vector.vector4_f32.Z) ? 0xFFFFFFFFU : 0;
    Control.vector.vector4_u32[3] = Single::IsInfinity(V.vector.vector4_f32.W) ? 0xFFFFFFFFU : 0;

    return Control;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorMin(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Min(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Min(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorMax(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Max(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    return CAST_TO(Vector4::Max(V1.vector.vector4_f32, V2.vector.vector4_f32), XMVector);
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorRound(FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> sign = Sse::And(V.m128.m128_f32, Vector128::AsSingle(g_XMNegativeZero));
    Vector128<float> sMagic = Sse::Or(g_XMNoFraction, sign);
    Vector128<float> R1 = Sse::Add(V.m128.m128_f32, sMagic);
    R1 = Sse::Subtract(R1, sMagic);
    Vector128<float> R2 = Sse::And(V.m128.m128_f32, Vector128::AsSingle(g_XMAbsMask));
    Vector128<float> mask = Sse::CompareLessThanOrEqual(R2, g_XMNoFraction);
    R2 = Sse::AndNot(mask, V.m128.m128_f32);
    return CAST_TO(Sse::Xor(R1, R2), XMVector);
#else
    return CAST_TO(Vector4(
        (float)System::Math::Round(V.vector.vector4_f32.X),
        (float)System::Math::Round(V.vector.vector4_f32.Y),
        (float)System::Math::Round(V.vector.vector4_f32.Z),
        (float)System::Math::Round(V.vector.vector4_f32.W)
    ), XMVector);
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

bool DirectXNet::Math::DXMath::XMVector4EqualInt(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    Vector128<unsigned __int32> vTemp = Sse2::CompareEqual(V1.m128.m128_u32, V2.m128.m128_u32);
    return ((Sse::MoveMask(Vector128::AsSingle(vTemp)) == 0xf) != 0);
#else
    return (((V1.vector.vector4_u32[0] == V2.vector.vector4_u32[0]) &&
             (V1.vector.vector4_u32[1] == V2.vector.vector4_u32[1]) &&
             (V1.vector.vector4_u32[2] == V2.vector.vector4_u32[2]) &&
             (V1.vector.vector4_u32[3] == V2.vector.vector4_u32[3])) != 0);
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
