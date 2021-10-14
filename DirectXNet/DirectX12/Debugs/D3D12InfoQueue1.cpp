#include "D3D12InfoQueue1.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12InfoQueue1::D3D12InfoQueue1(::ID3D12InfoQueue1* pQueue1)
    : D3D12InfoQueue((::ID3D12InfoQueue*)pQueue1)
{
    this->pQueue1 = pQueue1;
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue1::AttatchComObj(::IUnknown* pComObj)
{
    D3D12InfoQueue::AttatchComObj(pComObj);
    pQueue1 = (::ID3D12InfoQueue1*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12InfoQueue1::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12InfoQueue1), Guid);
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue1::RegisterMessageCallback(
    D3D12MessageCallback^ callbackFunc, D3D12MessageCallbackFlags callbackFilterFlags,
    void* pContext, DWORD% callbackCookie)
{
    ::D3D12MessageFunc nCallback = (::D3D12MessageFunc)Marshal::GetFunctionPointerForDelegate(callbackFunc).ToPointer();
    pin_ptr<DWORD> pCallbackCookie = &callbackCookie;

    Result result(pQueue1->RegisterMessageCallback(
        nCallback,
        (::D3D12_MESSAGE_CALLBACK_FLAGS)callbackFilterFlags,
        pContext,
        (DWORD*)pCallbackCookie
    ));

    if(result.Failed)
        return result;

    pCallbackCookie = nullptr;

    callbacks->Add(callbackCookie, callbackFunc);
    return result;
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue1::UnregisterMessageCallback(DWORD callbackCookie)
{
    Result result(pQueue1->UnregisterMessageCallback(callbackCookie));

    if(result.Failed)
        return result;

    callbacks->Remove(callbackCookie);
    return result;
}
