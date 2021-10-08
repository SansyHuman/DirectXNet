#include "D3D12Device.h"
#include "D3D12CommandQueue.h"
#include "D3D12CommandAllocator.h"
#include "D3D12CommandList.h"
#include "D3D12PipelineState.h"
#include "D3D12DescriptorHeap.h"
#include "D3D12RootSignature.h"
#include "D3D12Resource.h"
#include "D3D12Fence.h"
#include "D3D12Heap.h"
#include "D3D12DeviceChild.h"
#include "D3D12Pageable.h"
#include "D3D12QueryHeap.h"
#include "D3D12CommandSignature.h"

using namespace msclr::interop;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Device::D3D12Device(::ID3D12Device* pDevice)
    : D3D12Object((::ID3D12Object*)pDevice)
{
    this->pDevice = pDevice;
}

void DirectXNet::DirectX12::D3D12Device::AttatchComObj(::IUnknown* pComObj)
{
    D3D12Object::AttatchComObj(pComObj);
    pDevice = (::ID3D12Device*)pComObj;
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

D3D12CommandAllocator^ DirectXNet::DirectX12::D3D12Device::CreateCommandAllocator(
    D3D12CommandListType type)
{
    ::IUnknown* pAlloc = __nullptr;

    try
    {
        Result::ThrowIfFailed(pDevice->CreateCommandAllocator(
            (::D3D12_COMMAND_LIST_TYPE)type,
            __uuidof(::ID3D12CommandAllocator),
            (void**)&pAlloc
        ));

        return gcnew D3D12CommandAllocator((::ID3D12CommandAllocator*)pAlloc);
    }
    finally
    {
        SAFE_RELEASE(pAlloc);
    }
}

D3D12PipelineState^ DirectXNet::DirectX12::D3D12Device::CreateGraphicsPipelineState(
    D3D12GraphicsPipelineStateDesc% desc)
{
    ::IUnknown* pState = __nullptr;

    try
    {
        pin_ptr<D3D12GraphicsPipelineStateDesc> pDesc = &desc;
        Result::ThrowIfFailed(pDevice->CreateGraphicsPipelineState(
            (const ::D3D12_GRAPHICS_PIPELINE_STATE_DESC*)pDesc,
            __uuidof(::ID3D12PipelineState),
            (void**)&pState
        ));

        return gcnew D3D12PipelineState((::ID3D12PipelineState*)pState);
    }
    finally
    {
        SAFE_RELEASE(pState);
    }
}

D3D12PipelineState^ DirectXNet::DirectX12::D3D12Device::CreateComputePipelineState(
    D3D12ComputePipelineStateDesc% desc)
{
    ::IUnknown* pState = __nullptr;

    try
    {
        pin_ptr<D3D12ComputePipelineStateDesc> pDesc = &desc;
        Result::ThrowIfFailed(pDevice->CreateComputePipelineState(
            (const ::D3D12_COMPUTE_PIPELINE_STATE_DESC*)pDesc,
            __uuidof(::ID3D12PipelineState),
            (void**)&pState
        ));

        return gcnew D3D12PipelineState((::ID3D12PipelineState*)pState);
    }
    finally
    {
        SAFE_RELEASE(pState);
    }
}

generic <typename T> where T : D3D12CommandList
T DirectXNet::DirectX12::D3D12Device::CreateCommandList(
    unsigned int nodeMask, D3D12CommandListType type, D3D12CommandAllocator^ allocator, D3D12PipelineState^ initialState)
{
    ::IUnknown* pList = __nullptr;
    ::ID3D12CommandAllocator* pAlloc = __nullptr;
    ::ID3D12PipelineState* pState = __nullptr;

    try
    {
        pAlloc = (::ID3D12CommandAllocator*)allocator->GetNativeInterface();
        if(initialState != nullptr)
            pState = (::ID3D12PipelineState*)initialState->GetNativeInterface();

        GUID riid = CAST_TO(DirectXNet::Common::Unknown::GetGuidOfObject<T>(), _GUID);
        Result::ThrowIfFailed(pDevice->CreateCommandList(
            nodeMask,
            (::D3D12_COMMAND_LIST_TYPE)type,
            pAlloc,
            pState,
            riid,
            (void**)&pList
        ));

        T list = (T)Activator::CreateInstance(T::typeid, true);
        list->AttatchComObj(pList);

        return list;
    }
    finally
    {
        SAFE_RELEASE(pList);
        SAFE_RELEASE(pAlloc);
        SAFE_RELEASE(pState);
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

D3D12DescriptorHeap^ DirectXNet::DirectX12::D3D12Device::CreateDescriptorHeap(
    D3D12DescriptorHeapDesc% descriptorHeapDesc)
{
    ::IUnknown* pHeap = __nullptr;

    try
    {
        pin_ptr<D3D12DescriptorHeapDesc> pDescriptorHeapDesc = &descriptorHeapDesc;
        Result::ThrowIfFailed(pDevice->CreateDescriptorHeap(
            (const ::D3D12_DESCRIPTOR_HEAP_DESC*)pDescriptorHeapDesc,
            __uuidof(::ID3D12DescriptorHeap),
            (void**)&pHeap
        ));

        return gcnew D3D12DescriptorHeap((::ID3D12DescriptorHeap*)pHeap);
    }
    finally
    {
        SAFE_RELEASE(pHeap);
    }
}

unsigned int DirectXNet::DirectX12::D3D12Device::GetDescriptorHandleIncrementSize(
    D3D12DescriptorHeapType type)
{
    return pDevice->GetDescriptorHandleIncrementSize((::D3D12_DESCRIPTOR_HEAP_TYPE)type);
}

D3D12RootSignature^ DirectXNet::DirectX12::D3D12Device::CreateRootSignature(
    unsigned int nodeMask, IntPtr pBlobWithRootSignature, SIZE_T blobLengthInBytes)
{
    ::IUnknown* pRootSignature = __nullptr;

    try
    {
        Result::ThrowIfFailed(pDevice->CreateRootSignature(
            nodeMask,
            pBlobWithRootSignature.ToPointer(),
            blobLengthInBytes,
            __uuidof(::ID3D12RootSignature),
            (void**)&pRootSignature
        ));

        return gcnew D3D12RootSignature((::ID3D12RootSignature*)pRootSignature);
    }
    finally
    {
        SAFE_RELEASE(pRootSignature);
    }
}

void DirectXNet::DirectX12::D3D12Device::CreateConstantBufferView(
    D3D12ConstantBufferViewDesc desc, D3D12CPUDescriptorHandle destDescriptor)
{
    pDevice->CreateConstantBufferView(
        (const ::D3D12_CONSTANT_BUFFER_VIEW_DESC*)&desc,
        {destDescriptor.ptr}
    );
}

void DirectXNet::DirectX12::D3D12Device::CreateShaderResourceView(
    D3D12Resource^ resource, Nullable<D3D12ShaderResourceViewDesc> desc,
    D3D12CPUDescriptorHandle destDescriptor)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        if(resource != nullptr)
            pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        ::D3D12_SHADER_RESOURCE_VIEW_DESC* pDesc = __nullptr;
        if(desc.HasValue)
            pDesc = (::D3D12_SHADER_RESOURCE_VIEW_DESC*)&desc.Value;

        pDevice->CreateShaderResourceView(
            pResource, pDesc, CAST_TO(destDescriptor, ::D3D12_CPU_DESCRIPTOR_HANDLE));
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::D3D12Device::CreateUnorderedAccessView(
    D3D12Resource^ resource, D3D12Resource^ counterResource,
    Nullable<D3D12UnorderedAccessViewDesc> desc, D3D12CPUDescriptorHandle destDescriptor)
{
    ::ID3D12Resource* pResource = __nullptr;
    ::ID3D12Resource* pCounterResource = __nullptr;

    try
    {
        if(resource != nullptr)
            pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        if(counterResource != nullptr)
            pCounterResource = (::ID3D12Resource*)counterResource->GetNativeInterface();
        ::D3D12_UNORDERED_ACCESS_VIEW_DESC* pDesc = __nullptr;
        if(desc.HasValue)
            pDesc = (::D3D12_UNORDERED_ACCESS_VIEW_DESC*)&desc.Value;

        pDevice->CreateUnorderedAccessView(
            pResource,
            pCounterResource,
            pDesc,
            CAST_TO(destDescriptor, ::D3D12_CPU_DESCRIPTOR_HANDLE)
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
        SAFE_RELEASE(pCounterResource);
    }
}

void DirectXNet::DirectX12::D3D12Device::CreateRenderTargetView(
    D3D12Resource^ resource, Nullable<D3D12RenderTargetViewDesc> desc,
    D3D12CPUDescriptorHandle destDescriptor)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        if(resource != nullptr)
            pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        ::D3D12_RENDER_TARGET_VIEW_DESC* pDesc = __nullptr;
        if(desc.HasValue)
            pDesc = (::D3D12_RENDER_TARGET_VIEW_DESC*)&desc.Value;

        pDevice->CreateRenderTargetView(
            pResource, pDesc, CAST_TO(destDescriptor, ::D3D12_CPU_DESCRIPTOR_HANDLE)
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

void DirectXNet::DirectX12::D3D12Device::CreateDepthStencilView(
    D3D12Resource^ resource, Nullable<D3D12DepthStencilViewDesc> desc,
    D3D12CPUDescriptorHandle destDescriptor)
{
    ::ID3D12Resource* pResource = __nullptr;

    try
    {
        if(resource != nullptr)
            pResource = (::ID3D12Resource*)resource->GetNativeInterface();
        ::D3D12_DEPTH_STENCIL_VIEW_DESC* pDesc = __nullptr;
        if(desc.HasValue)
            pDesc = (::D3D12_DEPTH_STENCIL_VIEW_DESC*)&desc.Value;

        pDevice->CreateDepthStencilView(
            pResource, pDesc, CAST_TO(destDescriptor, ::D3D12_CPU_DESCRIPTOR_HANDLE)
        );
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}
void DirectXNet::DirectX12::D3D12Device::CreateSampler(
    D3D12SamplerDesc% desc, D3D12CPUDescriptorHandle destDescriptor)
{
    pin_ptr<D3D12SamplerDesc> pDesc = &desc;
    pDevice->CreateSampler(
        (::D3D12_SAMPLER_DESC*)pDesc, CAST_TO(destDescriptor, ::D3D12_CPU_DESCRIPTOR_HANDLE));
}
void DirectXNet::DirectX12::D3D12Device::CopyDescriptors(
    array<D3D12CPUDescriptorHandle>^ destDescriptorRangeStarts,
    array<unsigned int>^ destDescriptorRangeSizes,
    array<D3D12CPUDescriptorHandle>^ srcDescriptorRangeStarts,
    array<unsigned int>^ srcDescriptorRangeSizes,
    D3D12DescriptorHeapType descriptorHeapsType)
{
    pin_ptr<D3D12CPUDescriptorHandle> pDestDescriptorRangeStarts = &destDescriptorRangeStarts[0];
    pin_ptr<unsigned int> pDestDescriptorRangeSizes = nullptr;
    if(destDescriptorRangeSizes != nullptr)
        pDestDescriptorRangeSizes = &destDescriptorRangeSizes[0];
    pin_ptr<D3D12CPUDescriptorHandle> pSrcDescriptorRangeStarts = &srcDescriptorRangeStarts[0];
    pin_ptr<unsigned int> pSrcDescriptorRangeSizes = nullptr;
    if(srcDescriptorRangeSizes != nullptr)
        pSrcDescriptorRangeSizes = &srcDescriptorRangeSizes[0];

    pDevice->CopyDescriptors(
        destDescriptorRangeStarts->Length,
        (::D3D12_CPU_DESCRIPTOR_HANDLE*)pDestDescriptorRangeStarts,
        (unsigned int*)pDestDescriptorRangeSizes,
        srcDescriptorRangeStarts->Length,
        (::D3D12_CPU_DESCRIPTOR_HANDLE*)pSrcDescriptorRangeStarts,
        (unsigned int*)pSrcDescriptorRangeSizes,
        (::D3D12_DESCRIPTOR_HEAP_TYPE)descriptorHeapsType
    );
}

void DirectXNet::DirectX12::D3D12Device::CopyDescriptorsSimple(
    unsigned int numDescriptors, D3D12CPUDescriptorHandle destDescriptorRangeStart,
    D3D12CPUDescriptorHandle srcDescriptorRangeStart, D3D12DescriptorHeapType descriptorHeapsType)
{
    pDevice->CopyDescriptorsSimple(
        numDescriptors,
        CAST_TO(destDescriptorRangeStart, ::D3D12_CPU_DESCRIPTOR_HANDLE),
        CAST_TO(srcDescriptorRangeStart, ::D3D12_CPU_DESCRIPTOR_HANDLE),
        (::D3D12_DESCRIPTOR_HEAP_TYPE)descriptorHeapsType
    );
}

D3D12ResourceAllocationInfo DirectXNet::DirectX12::D3D12Device::GetResourceAllocationInfo(
    unsigned int visibleMask, ...array<D3D12ResourceDesc>^ resourceDescs)
{
    pin_ptr<D3D12ResourceDesc> pResourceDescs = &resourceDescs[0];
    return CAST_TO(
        pDevice->GetResourceAllocationInfo(
            visibleMask, resourceDescs->Length,
            (const ::D3D12_RESOURCE_DESC*)pResourceDescs),
        D3D12ResourceAllocationInfo
    );
}

D3D12HeapProperties DirectXNet::DirectX12::D3D12Device::GetCustomHeapProperties(
    unsigned int nodeMask, D3D12HeapType heapType)
{
    return CAST_TO(
        pDevice->GetCustomHeapProperties(nodeMask, (::D3D12_HEAP_TYPE)heapType),
        D3D12HeapProperties
    );
}

generic <typename T> where T : D3D12Resource
T DirectXNet::DirectX12::D3D12Device::CreateCommittedResource(
    D3D12HeapProperties% heapProperties, D3D12HeapFlags heapFlags, D3D12ResourceDesc% desc,
    D3D12ResourceStates initialResourceState, Nullable<D3D12ClearValue> optimizedClearValue)
{
    ::IUnknown* pResource = __nullptr;

    try
    {
        pin_ptr<D3D12HeapProperties> pHeapProperties = &heapProperties;
        pin_ptr<D3D12ResourceDesc> pDesc = &desc;
        ::D3D12_CLEAR_VALUE* pOptimizedClearValue = __nullptr;
        if(optimizedClearValue.HasValue)
            pOptimizedClearValue = (::D3D12_CLEAR_VALUE*)&optimizedClearValue.Value;
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->CreateCommittedResource(
            (const ::D3D12_HEAP_PROPERTIES*)pHeapProperties,
            (::D3D12_HEAP_FLAGS)heapFlags,
            (const ::D3D12_RESOURCE_DESC*)pDesc,
            (::D3D12_RESOURCE_STATES)initialResourceState,
            pOptimizedClearValue,
            CAST_TO(riid, _GUID),
            (void**)&pResource
        ));

        T resource = (T)Activator::CreateInstance(T::typeid, true);
        resource->AttatchComObj(pResource);

        return resource;
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

generic <typename T> where T : D3D12Heap
T DirectXNet::DirectX12::D3D12Device::CreateHeap(D3D12HeapDesc% desc)
{
    ::IUnknown* pHeap = __nullptr;

    try
    {
        pin_ptr<D3D12HeapDesc> pDesc = &desc;
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->CreateHeap(
            (const ::D3D12_HEAP_DESC*)pDesc,
            CAST_TO(riid, _GUID),
            (void**)&pHeap
        ));

        T heap = (T)Activator::CreateInstance(T::typeid, true);
        heap->AttatchComObj(pHeap);

        return heap;
    }
    finally
    {
        SAFE_RELEASE(pHeap)
    }
}

generic <typename T> where T : D3D12Resource
T DirectXNet::DirectX12::D3D12Device::CreatePlacedResource(
    D3D12Heap^ heap, unsigned long long heapOffset, D3D12ResourceDesc% desc,
    D3D12ResourceStates initialState, Nullable<D3D12ClearValue> optimizedClearValue)
{
    ::ID3D12Heap* pHeap = __nullptr;
    ::IUnknown* pResource = __nullptr;

    try
    {
        pHeap = (::ID3D12Heap*)heap->GetNativeInterface();
        pin_ptr<D3D12ResourceDesc> pDesc = &desc;
        ::D3D12_CLEAR_VALUE* pOptimizedClearValue = __nullptr;
        if(optimizedClearValue.HasValue)
            pOptimizedClearValue = (::D3D12_CLEAR_VALUE*)&optimizedClearValue.Value;
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->CreatePlacedResource(
            pHeap,
            heapOffset,
            (const ::D3D12_RESOURCE_DESC*)pDesc,
            (::D3D12_RESOURCE_STATES)initialState,
            pOptimizedClearValue,
            CAST_TO(riid, _GUID),
            (void**)&pResource
        ));

        T resource = (T)Activator::CreateInstance(T::typeid, true);
        resource->AttatchComObj(pResource);

        return resource;
    }
    finally
    {
        SAFE_RELEASE(pHeap);
        SAFE_RELEASE(pResource);
    }
}

generic <typename T> where T : D3D12Resource
T DirectXNet::DirectX12::D3D12Device::CreateReservedResource(
    D3D12ResourceDesc% desc, D3D12ResourceStates initialState,
    Nullable<D3D12ClearValue> optimizedClearValue)
{
    ::IUnknown* pResource = __nullptr;

    try
    {
        pin_ptr<D3D12ResourceDesc> pDesc = &desc;
        ::D3D12_CLEAR_VALUE* pOptimizedClearValue = __nullptr;
        if(optimizedClearValue.HasValue)
            pOptimizedClearValue = (::D3D12_CLEAR_VALUE*)&optimizedClearValue.Value;
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->CreateReservedResource(
            (const ::D3D12_RESOURCE_DESC*)pDesc,
            (::D3D12_RESOURCE_STATES)initialState,
            pOptimizedClearValue,
            CAST_TO(riid, _GUID),
            (void**)&pResource
        ));

        T resource = (T)Activator::CreateInstance(T::typeid, true);
        resource->AttatchComObj(pResource);

        return resource;
    }
    finally
    {
        SAFE_RELEASE(pResource);
    }
}

generic <typename T> where T : D3D12DeviceChild
T DirectXNet::DirectX12::D3D12Device::OpenSharedHandle(DXResourceHandle^ ntHandle)
{
    ::IUnknown* pObj = __nullptr;

    try
    {
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->OpenSharedHandle(
            ntHandle->NativeHandle,
            CAST_TO(riid, _GUID),
            (void**)&pObj
        ));

        T obj = (T)Activator::CreateInstance(T::typeid, true);
        obj->AttatchComObj(pObj);

        return obj;
    }
    finally
    {
        SAFE_RELEASE(pObj);
    }
}

generic <typename T> where T : D3D12Fence
T DirectXNet::DirectX12::D3D12Device::CreateFence(unsigned long long initialValue, D3D12FenceFlags flags)
{
    ::IUnknown* pFence = __nullptr;

    try
    {
        Guid riid = DirectXNet::Common::Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(pDevice->CreateFence(
            initialValue,
            (::D3D12_FENCE_FLAGS)flags,
            CAST_TO(riid, _GUID),
            (void**)&pFence
        ));

        T fence = (T)Activator::CreateInstance(T::typeid, true);
        fence->AttatchComObj(pFence);

        return fence;
    }
    finally
    {
        SAFE_RELEASE(pFence);
    }
}

DXResourceHandle^ DirectXNet::DirectX12::D3D12Device::CreateSharedHandle(
    D3D12DeviceChild^ object, AccessRights access, Nullable<SecurityAttributes> attributes, String^ name)
{
    ::ID3D12DeviceChild* pObject = __nullptr;

    try
    {
        marshal_context context;

        pObject = (::ID3D12DeviceChild*)object->GetNativeInterface();
        SECURITY_ATTRIBUTES* pAttributes = __nullptr;
        if(attributes.HasValue)
            pAttributes = (SECURITY_ATTRIBUTES*)&attributes.Value;
        LPCWSTR Name = __nullptr;
        if(name != nullptr)
            Name = context.marshal_as<LPCWSTR>(name);
        HANDLE handle = __nullptr;

        Result::ThrowIfFailed(pDevice->CreateSharedHandle(
            pObject,
            pAttributes,
            (DWORD)access,
            Name,
            &handle
        ));

        return gcnew DXResourceHandle(IntPtr(handle));
    }
    finally
    {
        SAFE_RELEASE(pObject);
    }
}

DXResourceHandle^ DirectXNet::DirectX12::D3D12Device::OpenSharedHandleByName(
    String^ name, AccessRights access)
{
    marshal_context context;

    LPCWSTR Name = context.marshal_as<LPCWSTR>(name);
    HANDLE ntHandle = __nullptr;

    Result::ThrowIfFailed(pDevice->OpenSharedHandleByName(Name, (DWORD)access, &ntHandle));

    return gcnew DXResourceHandle(IntPtr(ntHandle));
}

Result DirectXNet::DirectX12::D3D12Device::MakeResident(...array<D3D12Pageable^>^ objects)
{
    UINT numObjects = objects->Length;
    std::vector<::ID3D12Pageable*> pObjects(numObjects);

    try
    {
        for(UINT i = 0; i < numObjects; i++)
        {
            pObjects[i] = (::ID3D12Pageable*)objects[i]->GetNativeInterface();
        }

        return Result(pDevice->MakeResident(numObjects, pObjects.data()));
    }
    finally
    {
        for(UINT i = 0; i < numObjects; i++)
        {
            SAFE_RELEASE(pObjects[i]);
        }
    }
}

Result DirectXNet::DirectX12::D3D12Device::Evict(...array<D3D12Pageable^>^ objects)
{
    UINT numObjects = objects->Length;
    std::vector<::ID3D12Pageable*> pObjects(numObjects);

    try
    {
        for(UINT i = 0; i < numObjects; i++)
        {
            pObjects[i] = (::ID3D12Pageable*)objects[i]->GetNativeInterface();
        }

        return Result(pDevice->Evict(numObjects, pObjects.data()));
    }
    finally
    {
        for(UINT i = 0; i < numObjects; i++)
        {
            SAFE_RELEASE(pObjects[i]);
        }
    }
}

Result DirectXNet::DirectX12::D3D12Device::GetDeviceRemovedReason()
{
    return Result(pDevice->GetDeviceRemovedReason());
}

void DirectXNet::DirectX12::D3D12Device::GetCopyableFootprints(
    D3D12ResourceDesc% resourceDesc, unsigned int firstSubresource, unsigned int numSubresources,
    unsigned long long baseOffset, unsigned long long% totalBytes,
    array<D3D12PlacedSubresourceFootprint>^ layouts, array<unsigned int>^ numRows,
    array<unsigned long long>^ rowSizeInBytes)
{
    pin_ptr<D3D12ResourceDesc> pResourceDesc = &resourceDesc;
    pin_ptr<D3D12PlacedSubresourceFootprint> pLayouts = nullptr;
    if(layouts != nullptr)
        pLayouts = &layouts[0];
    pin_ptr<unsigned int> pNumRows = nullptr;
    if(numRows != nullptr)
        pNumRows = &numRows[0];
    pin_ptr<unsigned long long> pRowSizeInBytes = nullptr;
    if(rowSizeInBytes != nullptr)
        pRowSizeInBytes = &rowSizeInBytes[0];
    pin_ptr<unsigned long long> pTotalBytes = &totalBytes;

    pDevice->GetCopyableFootprints(
        (const ::D3D12_RESOURCE_DESC*)pResourceDesc,
        firstSubresource,
        numSubresources,
        baseOffset,
        (::D3D12_PLACED_SUBRESOURCE_FOOTPRINT*)pLayouts,
        (unsigned int*)pNumRows,
        (unsigned long long*)pRowSizeInBytes,
        (unsigned long long*)pTotalBytes
    );
}

D3D12QueryHeap^ DirectXNet::DirectX12::D3D12Device::CreateQueryHeap(D3D12QueryHeapDesc% desc)
{
    ::IUnknown* pHeap = __nullptr;

    try
    {
        pin_ptr<D3D12QueryHeapDesc> pDesc = &desc;

        Result::ThrowIfFailed(pDevice->CreateQueryHeap(
            (const ::D3D12_QUERY_HEAP_DESC*)pDesc,
            __uuidof(::ID3D12QueryHeap),
            (void**)&pHeap
        ));

        return gcnew D3D12QueryHeap((::ID3D12QueryHeap*)pHeap);
    }
    finally
    {
        SAFE_RELEASE(pHeap);
    }
}

Result DirectXNet::DirectX12::D3D12Device::SetStablePowerState(bool enable)
{
    return Result(pDevice->SetStablePowerState((BOOL)enable));
}

D3D12CommandSignature^ DirectXNet::DirectX12::D3D12Device::CreateCommandSignature(
    D3D12CommandSignatureDesc% desc, D3D12RootSignature^ rootSignature)
{
    ::ID3D12RootSignature* pRootSignature = __nullptr;
    ::IUnknown* pCommandSignature = __nullptr;

    try
    {
        pin_ptr<D3D12CommandSignatureDesc> pDesc = &desc;
        if(rootSignature != nullptr)
            pRootSignature = (::ID3D12RootSignature*)rootSignature->GetNativeInterface();

        Result::ThrowIfFailed(pDevice->CreateCommandSignature(
            (::D3D12_COMMAND_SIGNATURE_DESC*)pDesc,
            pRootSignature,
            __uuidof(::ID3D12CommandSignature),
            (void**)&pCommandSignature
        ));

        return gcnew D3D12CommandSignature((::ID3D12CommandSignature*)pCommandSignature);
    }
    finally
    {
        SAFE_RELEASE(pRootSignature);
        SAFE_RELEASE(pCommandSignature);
    }
}

void DirectXNet::DirectX12::D3D12Device::GetResourceTiling(
    D3D12Resource^ tiledResource, unsigned int% numTilesForEntireResource,
    D3D12PackedMipInfo% packedMipDesc, D3D12TileShape% standardTileShapeForNonPackedMips,
    unsigned int% numSubresourceTilings, unsigned int firstSubresourceTilingToGet,
    array<D3D12SubresourceTiling>^ subresourceTilingsForNonPackedMips)
{
    ::ID3D12Resource* pTiledResource = __nullptr;

    try
    {
        pTiledResource = (::ID3D12Resource*)tiledResource->GetNativeInterface();
        pin_ptr<unsigned int> pNumTilesForEntireResource = &numTilesForEntireResource;
        pin_ptr<D3D12PackedMipInfo> pPackedMipDesc = &packedMipDesc;
        pin_ptr<D3D12TileShape> pStandardTileShapeForNonPackedMips = &standardTileShapeForNonPackedMips;
        pin_ptr<unsigned int> pNumSubresourceTilings = &numSubresourceTilings;
        pin_ptr<D3D12SubresourceTiling> pSubresourceTilingsForNonPackedMips = &subresourceTilingsForNonPackedMips[0];

        pDevice->GetResourceTiling(
            pTiledResource,
            (UINT*)pNumTilesForEntireResource,
            (::D3D12_PACKED_MIP_INFO*)pPackedMipDesc,
            (::D3D12_TILE_SHAPE*)pStandardTileShapeForNonPackedMips,
            (UINT*)pNumSubresourceTilings,
            firstSubresourceTilingToGet,
            (::D3D12_SUBRESOURCE_TILING*)pSubresourceTilingsForNonPackedMips
        );
    }
    finally
    {
        SAFE_RELEASE(pTiledResource);
    }
}

Luid DirectXNet::DirectX12::D3D12Device::AdapterLuid::get()
{
    return *((Luid*)&pDevice->GetAdapterLuid());
}

void DirectXNet::DirectX12::D3D12Device::GetCopyableFootprints(
    D3D12ResourceDesc* resourceDesc, unsigned int firstSubresource,
    unsigned int numSubresources, unsigned long long baseOffset,
    D3D12PlacedSubresourceFootprint* layouts, unsigned int* numRows,
    unsigned long long* rowSizeInBytes, unsigned long long* totalBytes)
{
    pDevice->GetCopyableFootprints(
        (const ::D3D12_RESOURCE_DESC*)resourceDesc,
        firstSubresource,
        numSubresources,
        baseOffset,
        (::D3D12_PLACED_SUBRESOURCE_FOOTPRINT*)layouts,
        (unsigned int*)numRows,
        (unsigned long long*)rowSizeInBytes,
        (unsigned long long*)totalBytes
    );
}
