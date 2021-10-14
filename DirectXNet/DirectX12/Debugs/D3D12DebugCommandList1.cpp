#include "D3D12DebugCommandList1.h"
#include "../D3D12Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::D3D12DebugCommandList1(::ID3D12DebugCommandList1* pList)
    : DirectXNet::Common::Unknown((::IUnknown*)pList)
{
    this->pList = pList;
}

void DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pList = (::ID3D12DebugCommandList1*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugCommandList1), Guid);
}

bool DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::AssertResourceState(
    D3D12Resource^ resource, unsigned int subresource, D3D12ResourceStates state)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        return (!!(pList->AssertResourceState(pResource, subresource, (UINT)state)));
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

generic <typename T> where T : ICommandListDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::SetDebugParameter(
    D3D12DebugCommandListParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pList->SetDebugParameter(
        (::D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}

generic <typename T> where T : ICommandListDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugCommandList1::GetDebugParameter(
    D3D12DebugCommandListParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pList->GetDebugParameter(
        (::D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}
