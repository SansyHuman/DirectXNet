#include "D3D12DebugCommandList2.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12DebugCommandList2::D3D12DebugCommandList2(
    ::ID3D12DebugCommandList2* pList2)
    : D3D12DebugCommandList((::ID3D12DebugCommandList*)pList2)
{
    this->pList2 = pList2;
}

void DirectXNet::DirectX12::Debug::D3D12DebugCommandList2::AttatchComObj(::IUnknown* pComObj)
{
    D3D12DebugCommandList::AttatchComObj(pComObj);
    pList2 = (::ID3D12DebugCommandList2*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12DebugCommandList2::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DebugCommandList2), Guid);
}

generic<typename T> where T : ICommandListDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugCommandList2::SetDebugParameter(
    D3D12DebugCommandListParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pList2->SetDebugParameter(
        (::D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}

generic<typename T> where T : ICommandListDebugParameter, value class
Result DirectXNet::DirectX12::Debug::D3D12DebugCommandList2::GetDebugParameter(
    D3D12DebugCommandListParameterType type, T% data)
{
    pin_ptr<T> pData = &data;
    return Result(pList2->GetDebugParameter(
        (::D3D12_DEBUG_COMMAND_LIST_PARAMETER_TYPE)type,
        (void*)pData,
        sizeof(T)
    ));
}
