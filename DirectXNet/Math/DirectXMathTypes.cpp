#include "DirectXMathTypes.h"
#include "VectorOperations.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

#ifdef _NETCORE
using namespace System::Runtime::Intrinsics;
using namespace System::Runtime::Intrinsics::X86;
#endif

using namespace DirectXNet::Math;

#ifdef _NETFRAMEWORK
DirectXNet::Math::Vector4UInt::Vector4UInt(
    unsigned __int32 x, unsigned __int32 y, unsigned __int32 z, unsigned __int32 w)
    : X(x), Y(y), Z(z), W(w)
{
    
}

unsigned __int32 DirectXNet::Math::Vector4UInt::default::get(int index)
{
    switch(index)
    {
    case 0:
        return X;
    case 1:
        return Y;
    case 2:
        return Z;
    case 3:
        return W;
    default:
        throw gcnew IndexOutOfRangeException("Vector index out of range.");
    }
}

void DirectXNet::Math::Vector4UInt::default::set(int index, unsigned __int32 value)
{
    switch(index)
    {
    case 0:
        X = value;
        break;
    case 1:
        Y = value;
        break;
    case 2:
        Z = value;
        break;
    case 3:
        W = value;
        break;
    default:
        throw gcnew IndexOutOfRangeException("Vector index out of range.");
    }
}
#endif

XMVector DirectXNet::Math::XMVector::operator+(FXMVector v)
{
    return v;
}

XMVector DirectXNet::Math::XMVector::operator-(FXMVector v)
{
    return DXMath::XMVectorNegate(v);
}

XMVector DirectXNet::Math::XMVector::operator+(
    FXMVector v1, FXMVector v2)
{
    return DXMath::XMVectorAdd(v1, v2);
}

XMVector DirectXNet::Math::XMVector::operator-(
    FXMVector v1, FXMVector v2)
{
    return DXMath::XMVectorSubtract(v1, v2);
}

XMVector DirectXNet::Math::XMVector::operator*(FXMVector v1, FXMVector v2)
{
    return DXMath::XMVectorMultiply(v1, v2);
}

XMVector DirectXNet::Math::XMVector::operator/(FXMVector v1, FXMVector v2)
{
    return DXMath::XMVectorDivide(v1, v2);
}

XMVector DirectXNet::Math::XMVector::operator*(FXMVector v, float s)
{
    return DXMath::XMVectorScale(v, s);
}

XMVector DirectXNet::Math::XMVector::operator*(float s, FXMVector v)
{
    return DXMath::XMVectorScale(v, s);
}

XMVector DirectXNet::Math::XMVector::operator/(FXMVector v, float s)
{
    XMVector vS = DXMath::XMVectorReplicate(s);
    return DXMath::XMVectorDivide(v, vS);
}

DirectXNet::Math::XMMatrix::XMMatrix(
    FXMVector r0, FXMVector r1, FXMVector r2, CXMVector r3)
{
#ifdef _NETCORE
    this->r0.m128.m128_f32 = r0.m128.m128_f32;
    this->r1.m128.m128_f32 = r1.m128.m128_f32;
    this->r2.m128.m128_f32 = r2.m128.m128_f32;
    this->r3.m128.m128_f32 = r3.m128.m128_f32;
#else
    this->r0.vector.vector4_f32 = r0.vector.vector4_f32;
    this->r1.vector.vector4_f32 = r1.vector.vector4_f32;
    this->r2.vector.vector4_f32 = r2.vector.vector4_f32;
    this->r3.vector.vector4_f32 = r3.vector.vector4_f32;
#endif
}

DirectXNet::Math::XMMatrix::XMMatrix(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
#ifdef _NETCORE
    this->r0.m128.m128_f32 = Vector128::Create(m00, m01, m02, m03);
    this->r1.m128.m128_f32 = Vector128::Create(m10, m11, m12, m13);
    this->r2.m128.m128_f32 = Vector128::Create(m20, m21, m22, m23);
    this->r3.m128.m128_f32 = Vector128::Create(m30, m31, m32, m33);
#else
    this->r0.vector.vector4_f32 = Vector4(m00, m01, m02, m03);
    this->r1.vector.vector4_f32 = Vector4(m10, m11, m12, m13);
    this->r2.vector.vector4_f32 = Vector4(m20, m21, m22, m23);
    this->r3.vector.vector4_f32 = Vector4(m30, m31, m32, m33);
#endif
}

XMMatrix DirectXNet::Math::XMMatrix::operator+(FXMMatrix m)
{
    return m;
}

XMMatrix DirectXNet::Math::XMMatrix::operator-(FXMMatrix m)
{
    return XMMatrix(-m.r0, -m.r1, -m.r2, -m.r3);
}

XMMatrix DirectXNet::Math::XMMatrix::operator+(FXMMatrix m1, CXMMatrix m2)
{
    return XMMatrix(
        DXMath::XMVectorAdd(m1.r0, m2.r0),
        DXMath::XMVectorAdd(m1.r1, m2.r1),
        DXMath::XMVectorAdd(m1.r2, m2.r2),
        DXMath::XMVectorAdd(m1.r3, m2.r3)
    );
}

XMMatrix DirectXNet::Math::XMMatrix::operator-(FXMMatrix m1, CXMMatrix m2)
{
    return XMMatrix(
        DXMath::XMVectorSubtract(m1.r0, m2.r0),
        DXMath::XMVectorSubtract(m1.r1, m2.r1),
        DXMath::XMVectorSubtract(m1.r2, m2.r2),
        DXMath::XMVectorSubtract(m1.r3, m2.r3)
    );
}

XMMatrix DirectXNet::Math::XMMatrix::operator*(FXMMatrix m1, CXMMatrix m2)
{
    return DXMath::XMMatrixMultiply(m1, m2);
}

XMMatrix DirectXNet::Math::XMMatrix::operator*(FXMMatrix m, float s)
{
    return XMMatrix(
        DXMath::XMVectorScale(m.r0, s),
        DXMath::XMVectorScale(m.r1, s),
        DXMath::XMVectorScale(m.r2, s),
        DXMath::XMVectorScale(m.r3, s)
    );
}

XMMatrix DirectXNet::Math::XMMatrix::operator*(float s, FXMMatrix m)
{
    return XMMatrix(
        DXMath::XMVectorScale(m.r0, s),
        DXMath::XMVectorScale(m.r1, s),
        DXMath::XMVectorScale(m.r2, s),
        DXMath::XMVectorScale(m.r3, s)
    );
}

XMMatrix DirectXNet::Math::XMMatrix::operator/(FXMMatrix m, float s)
{
#ifdef _NETCORE
    Vector128<float> vS = Vector128::Create(s);
    XMMatrix R;
    R.r0.m128.m128_f32 = Sse::Divide(m.r0.m128.m128_f32, vS);
    R.r1.m128.m128_f32 = Sse::Divide(m.r1.m128.m128_f32, vS);
    R.r2.m128.m128_f32 = Sse::Divide(m.r2.m128.m128_f32, vS);
    R.r3.m128.m128_f32 = Sse::Divide(m.r3.m128.m128_f32, vS);
    return R;
#else
    XMVector vS = DXMath::XMVectorReplicate(s);
    return XMMatrix(
        DXMath::XMVectorDivide(m.r0, vS),
        DXMath::XMVectorDivide(m.r1, vS),
        DXMath::XMVectorDivide(m.r2, vS),
        DXMath::XMVectorDivide(m.r3, vS)
    );
#endif
}
