#include "D3DCompiler.h"
#include "../Common/D3D10Blob.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;

D3D10Blob^ DirectXNet::HLSL::D3DCompiler::CreateBlob(SIZE_T size)
{
    ::ID3D10Blob* pBlob = __nullptr;

    try
    {
        Result::ThrowIfFailed(D3DCreateBlob(size, &pBlob));
        return gcnew D3D10Blob(pBlob);
    }
    finally
    {
        SAFE_RELEASE(pBlob);
    }
}
