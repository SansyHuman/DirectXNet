#include "DXGIDevice.h"
#include "../Common/Result.h"
#include "DXGIAdapter.h"
#include "DXGISurface.h"
#include <vector>

using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIDevice::DXGIDevice(::IDXGIDevice* pDevice)
    : DXGIObject((::IDXGIObject*)pDevice)
{
    this->pDevice = pDevice;
}

void DirectXNet::DXGI::DXGIDevice::AttatchComObj(::IUnknown* pComObj)
{
    DXGI::DXGIObject::AttatchComObj(pComObj);
    pDevice = (::IDXGIDevice*)pComObj;
}

Guid DirectXNet::DXGI::DXGIDevice::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIDevice), Guid);
}

DXGIAdapter^ DirectXNet::DXGI::DXGIDevice::Adapter::get()
{
    ::IDXGIAdapter* pAdapter = __nullptr;

    try
    {
        Result::ThrowIfFailed(pDevice->GetAdapter(&pAdapter));

        return gcnew DXGIAdapter(pAdapter);
    }
    finally
    {
        SAFE_RELEASE(pAdapter);
    }
}

DXGISurface^ DirectXNet::DXGI::DXGIDevice::CreateSurface(
    DXGISurfaceDesc% desc, unsigned int numSurfaces, DXGIUsage usage,
    Nullable<DXGISharedResource> sharedResource)
{
    ::IDXGISurface* pSurface = __nullptr;

    try
    {
        pin_ptr<DXGISurfaceDesc> pDesc = &desc;
        ::DXGI_SURFACE_DESC* pDescN = (::DXGI_SURFACE_DESC*)pDesc;
        ::DXGI_SHARED_RESOURCE* pResource = __nullptr;
        if(sharedResource.HasValue)
            pResource = (::DXGI_SHARED_RESOURCE*)&sharedResource.Value;

        Result::ThrowIfFailed(pDevice->CreateSurface(pDescN, numSurfaces, (::DXGI_USAGE)usage, pResource, &pSurface));

        return gcnew DXGISurface(pSurface);
    }
    finally
    {
        SAFE_RELEASE(pSurface);
    }
}

array<DXGIResidency>^ DirectXNet::DXGI::DXGIDevice::QueryResourceResidency(array<Common::Unknown^>^ resources)
{
    UINT numResources = resources->Length;
    std::vector<::IUnknown*> pResources(numResources);

    try
    {
        for(int i = 0; i < numResources; i++)
        {
            pResources[i] = resources[i]->GetNativeInterface();
        }

        array<DXGIResidency>^ residencies = gcnew array<DXGIResidency>(numResources);
        pin_ptr<DXGIResidency> pResidencies = &residencies[0];
        ::DXGI_RESIDENCY* pResidenciesN = (::DXGI_RESIDENCY*)pResidencies;

        Result::ThrowIfFailed(pDevice->QueryResourceResidency(
            pResources.data(), pResidenciesN, numResources));

        return residencies;
    }
    finally
    {
        for(int i = 0; i < numResources; i++)
        {
            SAFE_RELEASE(pResources[i])
        }
    }
}

int DirectXNet::DXGI::DXGIDevice::GPUThreadPriority::get()
{
    int priority = 0;
    Result::ThrowIfFailed(pDevice->GetGPUThreadPriority(&priority));

    return priority;
}

void DirectXNet::DXGI::DXGIDevice::GPUThreadPriority::set(int value)
{
    Result::ThrowIfFailed(pDevice->SetGPUThreadPriority(value));
}
