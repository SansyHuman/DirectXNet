#include "D3D12DeviceChild.h"
#include "D3D12Device.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12DeviceChild::D3D12DeviceChild(::ID3D12DeviceChild* pDeviceChild)
    : D3D12Object((::ID3D12Object*)pDeviceChild)
{
    this->pDeviceChild = pDeviceChild;
}

void DirectXNet::DirectX12::D3D12DeviceChild::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Object::AttatchComObj(pComObj);
    pDeviceChild = (::ID3D12DeviceChild*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12DeviceChild::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12DeviceChild), Guid);
}

generic <typename T> where T : D3D12Device
T DirectXNet::DirectX12::D3D12DeviceChild::GetDevice()
{
    ::IUnknown* pDevice = __nullptr;

    try
    {
        Guid guid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDeviceChild->GetDevice(CAST_TO(guid, _GUID), (void**)&pDevice));

        T device = (T)Activator::CreateInstance(T::typeid, true);
        device->AttatchComObj(pDevice);

        return device;
    }
    finally
    {
        SAFE_RELEASE(pDevice);
    }
}
