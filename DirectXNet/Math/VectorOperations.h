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
            static XMVector XMVectorNegate(FXMVector V);
            static XMVector XMVectorAdd(FXMVector V1, FXMVector V2);
            static XMVector XMVectorSubtract(FXMVector V1, FXMVector V2);
        };
    }
}