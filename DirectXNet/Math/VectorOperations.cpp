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

XMVector DirectXNet::Math::DXMath::XMVectorNegate(FXMVector V)
{
#ifdef _NETCORE
    Vector128<float> Z = Vector128::Create(0.0f);

    return CAST_TO(Sse::Subtract(Z, V.m128.m128_f32), XMVector);
#else
    XMVector Result;
    Result.vector.vector4_f32 = Vector4::Negate(V.vector.vector4_f32);
    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorAdd(FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Add(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Result;
    Result.vector.vector4_f32 = Vector4::Add(V1.vector.vector4_f32, V2.vector.vector4_f32);
    return Result;
#endif
}

XMVector DirectXNet::Math::DXMath::XMVectorSubtract(
    FXMVector V1, FXMVector V2)
{
#ifdef _NETCORE
    return CAST_TO(Sse::Subtract(V1.m128.m128_f32, V2.m128.m128_f32), XMVector);
#else
    XMVector Result;
    Result.vector.vector4_f32 = Vector4::Subtract(V1.vector.vector4_f32, V2.vector.vector4_f32);
    return Result;
#endif
}
