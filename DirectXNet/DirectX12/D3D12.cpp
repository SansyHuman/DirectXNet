#include "D3D12.h"
#include "../Common/Result.h"
#include "../Common/Unknown.h"
#include "D3D12CommandAllocator.h"
#include "D3D12CommandList.h"
#include "D3D12CommandQueue.h"
#include "D3D12CommandSignature.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12Device.h"
#include "D3D12DeviceChild.h"
#include "D3D12DeviceRemovedExtendedData.h"
#include "D3D12DeviceRemovedExtendedDataSettings.h"
#include "D3D12Fence.h"
#include "D3D12GraphicsCommandList.h"
#include "D3D12Heap.h"
#include "D3D12Object.h"
#include "D3D12Pageable.h"
#include "D3D12PipelineState.h"
#include "D3D12QueryHeap.h"
#include "D3D12Resource.h"
#include "D3D12RootSignature.h"
#include "D3D12RootSignatureDeserializer.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace msclr::interop;

#ifndef CHECK_D3D12_GUID
#define CHECK_D3D12_GUID(type) if(*((_GUID*)&Unknown::GetGuidOfObject<DirectXNet::DirectX12:: ## type ## ^>()) != __uuidof(::I ## type)) throw gcnew Exception("GUID check error");
#endif

DirectXNet::DirectX12::D3D12::D3D12()
{
#if defined(DEBUG) | defined (_DEBUG)
    CHECK_D3D12_GUID(D3D12CommandAllocator);
    CHECK_D3D12_GUID(D3D12CommandList);
    CHECK_D3D12_GUID(D3D12CommandQueue);
    CHECK_D3D12_GUID(D3D12CommandSignature);
    CHECK_D3D12_GUID(D3D12DescriptorHeap);
    CHECK_D3D12_GUID(D3D12Device);
    CHECK_D3D12_GUID(D3D12DeviceChild);
    CHECK_D3D12_GUID(D3D12DeviceRemovedExtendedData);
    CHECK_D3D12_GUID(D3D12DeviceRemovedExtendedDataSettings);
    CHECK_D3D12_GUID(D3D12Fence);
    CHECK_D3D12_GUID(D3D12GraphicsCommandList);
    CHECK_D3D12_GUID(D3D12Heap);
    CHECK_D3D12_GUID(D3D12Object);
    CHECK_D3D12_GUID(D3D12Pageable);
    CHECK_D3D12_GUID(D3D12PipelineState);
    CHECK_D3D12_GUID(D3D12QueryHeap);
    CHECK_D3D12_GUID(D3D12Resource);
    CHECK_D3D12_GUID(D3D12RootSignature);
    CHECK_D3D12_GUID(D3D12RootSignatureDeserializer);
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

Result DirectXNet::DirectX12::D3D12::SerializeRootSignature(
    D3D12RootSignatureDesc% rootSignature, D3DRootSignatureVersion version,
    D3D10Blob^% blob, String^% errorMessage)
{
    ::ID3DBlob* pBlob = __nullptr;
    ::ID3DBlob* pErrorBlob = __nullptr;

    try
    {
        pin_ptr<D3D12RootSignatureDesc> pRootSignature = &rootSignature;

        Result result(D3D12SerializeRootSignature(
            (::D3D12_ROOT_SIGNATURE_DESC*)pRootSignature,
            (::D3D_ROOT_SIGNATURE_VERSION)version,
            &pBlob,
            &pErrorBlob
        ));

        if(result.Failed)
        {
            errorMessage = marshal_as<String^>((const char*)pErrorBlob->GetBufferPointer());
            blob = nullptr;
        }
        else
        {
            blob = gcnew D3D10Blob(pBlob);
            errorMessage = nullptr;
        }

        return result;
    }
    finally
    {
        SAFE_RELEASE(pBlob);
        SAFE_RELEASE(pErrorBlob);
    }
}

D3D12RootSignatureDeserializer^ DirectXNet::DirectX12::D3D12::CreateRootSignatureDeserializer(
    IntPtr pSrcData, SIZE_T srcDataSizeInBytes)
{
    ::IUnknown* pDeserializer = __nullptr;

    try
    {
        Result::ThrowIfFailed(D3D12CreateRootSignatureDeserializer(
            pSrcData.ToPointer(),
            srcDataSizeInBytes,
            __uuidof(::ID3D12RootSignatureDeserializer),
            (void**)&pDeserializer
        ));

        return gcnew D3D12RootSignatureDeserializer((::ID3D12RootSignatureDeserializer*)pDeserializer);
    }
    finally
    {
        SAFE_RELEASE(pDeserializer);
    }
}

unsigned int DirectXNet::DirectX12::D3D12::EncodeShader4ComponentMapping(
    D3D12ShaderComponentMapping src0, D3D12ShaderComponentMapping src1,
    D3D12ShaderComponentMapping src2, D3D12ShaderComponentMapping src3)
{
    return D3D12_ENCODE_SHADER_4_COMPONENT_MAPPING((UINT)src0, (UINT)src1, (UINT)src2, (UINT)src3);
}

D3D12ShaderComponentMapping DirectXNet::DirectX12::D3D12::DecodeShader4ComponentMapping(
    unsigned int componentToExtract, unsigned int mapping)
{
    return (D3D12ShaderComponentMapping)D3D12_DECODE_SHADER_4_COMPONENT_MAPPING(componentToExtract, mapping);
}

unsigned char DirectXNet::DirectX12::D3D12::GetFormatPlaneCount(D3D12Device^ device, DXGIFormat format)
{
    D3D12FeatureDataFormatInfo formatInfo(format);
    if((device->CheckFeatureSupport(D3D12Feature::FormatInfo, formatInfo)).Failed)
        return 0;
    return formatInfo.PlaneCount;
}

unsigned int DirectXNet::DirectX12::D3D12::CalcSubresource(unsigned int mipSlice, unsigned int arraySlice, unsigned int planeSlice, unsigned int mipLevels, unsigned int arraySize)
{
    return mipSlice + arraySlice * mipLevels + planeSlice * mipLevels * arraySize;
}
