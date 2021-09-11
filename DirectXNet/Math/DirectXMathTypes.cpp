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
