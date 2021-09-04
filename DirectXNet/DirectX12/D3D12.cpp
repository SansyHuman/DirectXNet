#include "D3D12.h"
#include "../Common/Result.h"
#include "../Common/Unknown.h"
#include "D3D12CommandList.h"
#include "D3D12CommandQueue.h"
#include "D3D12Device.h"
#include "D3D12DeviceChild.h"
#include "D3D12Fence.h"
#include "D3D12Heap.h"
#include "D3D12Object.h"
#include "D3D12Pageable.h"
#include "D3D12Resource.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

#ifndef CHECK_D3D12_GUID
#define CHECK_D3D12_GUID(type) if(*((_GUID*)&Unknown::GetGuidOfObject<DirectXNet::DirectX12:: ## type ## ^>()) != __uuidof(::I ## type)) throw gcnew Exception("GUID check error");
#endif

DirectXNet::DirectX12::D3D12::D3D12()
{
#if defined(DEBUG) | defined (_DEBUG)
    CHECK_D3D12_GUID(D3D12CommandList);
    CHECK_D3D12_GUID(D3D12CommandQueue);
    CHECK_D3D12_GUID(D3D12Device);
    CHECK_D3D12_GUID(D3D12DeviceChild);
    CHECK_D3D12_GUID(D3D12Fence);
    CHECK_D3D12_GUID(D3D12Heap);
    CHECK_D3D12_GUID(D3D12Object);
    CHECK_D3D12_GUID(D3D12Pageable);
    CHECK_D3D12_GUID(D3D12Resource);
#endif
}

generic <typename T> where T : D3D12Device
T DirectXNet::DirectX12::D3D12::CreateDevice(
    D3DFeatureLevel minimumFeatureLevel, DirectXNet::Common::Unknown^ adapter)
{
    ::IUnknown* pAdapter = __nullptr;
    ::IUnknown* pDevice = __nullptr;

    try
    {
        if(adapter != nullptr)
            pAdapter = adapter->GetNativeInterface();
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(D3D12CreateDevice(
            pAdapter,
            (::D3D_FEATURE_LEVEL)minimumFeatureLevel,
            CAST_TO(riid, _GUID),
            (void**)&pDevice
        ));

        T device = (T)Activator::CreateInstance(T::typeid, true);
        device->AttatchComObj(pDevice);

        return device;
    }
    finally
    {
        SAFE_RELEASE(pAdapter);
        SAFE_RELEASE(pDevice);
    }
}

unsigned char DirectXNet::DirectX12::D3D12::GetFormatPlaneCount(D3D12Device^ device, DXGIFormat format)
{
    D3D12FeatureDataFormatInfo formatInfo(format);
    if((device->CheckFeatureSupport(D3D12Feature::FormatInfo, formatInfo)).Failed)
        return 0;
    return formatInfo.PlaneCount;
}

unsigned int DirectXNet::DirectX12::D3D12::CalcSubresource(
    unsigned int mipSlice, unsigned int arraySlice, unsigned int planeSlice,
    unsigned int mipLevels, unsigned int arraySize)
{
   return mipSlice + arraySlice * mipLevels + planeSlice * mipLevels * arraySize;
}
