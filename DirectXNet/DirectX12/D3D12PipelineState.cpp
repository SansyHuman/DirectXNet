#include "D3D12PipelineState.h"
#include "../Common/D3D10Blob.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12PipelineState::D3D12PipelineState(::ID3D12PipelineState* pState)
    : D3D12Pageable((::ID3D12Pageable*)pState)
{
    this->pState = pState;
}

void DirectXNet::DirectX12::D3D12PipelineState::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Pageable::AttatchComObj(pComObj);
    pState = (::ID3D12PipelineState*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12PipelineState::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12PipelineState), Guid);
}

D3D10Blob^ DirectXNet::DirectX12::D3D12PipelineState::CachedBlob::get()
{
    ::ID3D10Blob* pBlob = __nullptr;

    try
    {
        Result::ThrowIfFailed(pState->GetCachedBlob(&pBlob));

        return gcnew D3D10Blob(pBlob);
    }
    finally
    {
        SAFE_RELEASE(pBlob);
    }
}
