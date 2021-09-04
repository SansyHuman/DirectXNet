#include "D3D12Device.h"
#include "D3D12CommandQueue.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Device::D3D12Device(::ID3D12Device* pDevice)
    : D3D12Object((::ID3D12Object*)pDevice)
{
    this->pDevice.Attach(pDevice);
}

void DirectXNet::DirectX12::D3D12Device::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Object::AttatchComObj(pComObj);
    pDevice.Release();
    pDevice.Attach((::ID3D12Device*)pComObj);
}

Guid DirectXNet::DirectX12::D3D12Device::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Device), Guid);
}

unsigned int DirectXNet::DirectX12::D3D12Device::NodeCount::get()
{
    return pDevice->GetNodeCount();
}

generic <typename T> where T : D3D12CommandQueue
T DirectXNet::DirectX12::D3D12Device::CreateCommandQueue(D3D12CommandQueueDesc% desc)
{
    ::IUnknown* pCommandQueue = __nullptr;

    try
    {
        pin_ptr<D3D12CommandQueueDesc> pDesc = &desc;
        _GUID riid = CAST_TO(DirectXNet::Common::Unknown::GetGuidOfObject<T>(), _GUID);
        Result::ThrowIfFailed(pDevice->CreateCommandQueue(
            (const ::D3D12_COMMAND_QUEUE_DESC*)pDesc,
            riid,
            (void**)&pCommandQueue
        ));

        T commandQueue = (T)Activator::CreateInstance(T::typeid, true);
        commandQueue->AttatchComObj(pCommandQueue);

        return commandQueue;
    }
    finally
    {
        SAFE_RELEASE(pCommandQueue);
    }
}

generic <typename T>  where T : value class, ID3D12FeatureData
Result DirectXNet::DirectX12::D3D12Device::CheckFeatureSupport(
    D3D12Feature feature, T% featureSupportData)
{
    pin_ptr<T> pFeatureSupportData = &featureSupportData;
    return Result(pDevice->CheckFeatureSupport(
        (::D3D12_FEATURE)feature,
        (void*)pFeatureSupportData,
        sizeof(T)
    ));
}

unsigned int DirectXNet::DirectX12::D3D12Device::GetDescriptorHandleIncrementSize(
    D3D12DescriptorHeapType type)
{
    return pDevice->GetDescriptorHandleIncrementSize((::D3D12_DESCRIPTOR_HEAP_TYPE)type);
}

void DirectXNet::DirectX12::D3D12Device::CreateConstantBufferView(
    D3D12ConstantBufferViewDesc desc, D3D12CPUDescriptorHandle destDescriptor)
{
    return pDevice->CreateConstantBufferView(
        (const ::D3D12_CONSTANT_BUFFER_VIEW_DESC*)&desc,
        {destDescriptor.ptr}
    );
}

Result DirectXNet::DirectX12::D3D12Device::GetDeviceRemovedReason()
{
    return Result(pDevice->GetDeviceRemovedReason());
}

Result DirectXNet::DirectX12::D3D12Device::SetStablePowerState(bool enable)
{
    return Result(pDevice->SetStablePowerState((BOOL)enable));
}

Luid DirectXNet::DirectX12::D3D12Device::AdapterLuid::get()
{
    return *((Luid*)&pDevice->GetAdapterLuid());
}
