#include "DXGIFactory.h"
#include "DXGISwapChain.h"
#include "../Common/Result.h"
#include "DXGIAdapter.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIFactory::DXGIFactory(::IDXGIFactory* pFactory)
    : DXGI::DXGIObject((::IDXGIObject*)pFactory)
{
    this->pFactory.Attach(pFactory);
}

void DirectXNet::DXGI::DXGIFactory::AttatchComObj(::IUnknown* pComObj)
{
    DXGI::DXGIObject::AttatchComObj(pComObj);
    pFactory.Release();
    pFactory.Attach((::IDXGIFactory*)pComObj);
}

Guid DirectXNet::DXGI::DXGIFactory::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIFactory), Guid);
}

Result DirectXNet::DXGI::DXGIFactory::EnumAdapters(unsigned int index, DXGIAdapter^% adapter)
{
    ::IDXGIAdapter* pAdapter = __nullptr;

    try
    {
        Result result(pFactory->EnumAdapters(index, &pAdapter));
        if(result.Failed)
        {
            adapter = nullptr;
            return result;
        }

        adapter = gcnew DXGIAdapter(pAdapter);

        return result;
    }
    finally
    {
        SAFE_RELEASE(pAdapter);
    }
}

DXGISwapChain^ DirectXNet::DXGI::DXGIFactory::CreateSwapChain(
    Common::Unknown^ device,
    DXGISwapChainDesc% desc)
{
    ::IUnknown* pDevice = __nullptr;
    ::IDXGISwapChain* pSwapchain = __nullptr;

    try
    {
        pDevice = device->GetNativeInterface();
        pin_ptr<DXGISwapChainDesc> pDesc = &desc;
        ::DXGI_SWAP_CHAIN_DESC* pDescNative = (::DXGI_SWAP_CHAIN_DESC*)pDesc;

        Result::ThrowIfFailed(pFactory->CreateSwapChain(
            pDevice,
            pDescNative,
            &pSwapchain
        ));

        DXGISwapChain^ swapchain = gcnew DXGISwapChain(pSwapchain);

        return swapchain;
    }
    finally
    {
        SAFE_RELEASE(pDevice);
        SAFE_RELEASE(pSwapchain);
    }
}

IntPtr DirectXNet::DXGI::DXGIFactory::GetWindowAssociation()
{
    HWND hwnd = __nullptr;
    Result::ThrowIfFailed(pFactory->GetWindowAssociation(&hwnd));

    return IntPtr((void*)hwnd);
}

void DirectXNet::DXGI::DXGIFactory::MakeWindowAssociation(IntPtr windowHandle, WindowAssociationFlag flags)
{
    Result::ThrowIfFailed(pFactory->MakeWindowAssociation((HWND)windowHandle.ToPointer(), (UINT)flags));
}

DXGIAdapter^ DirectXNet::DXGI::DXGIFactory::CreateSoftwareAdapter(IntPtr module)
{
    ::IDXGIAdapter* pAdapter = __nullptr;

    try
    {
        Result::ThrowIfFailed(pFactory->CreateSoftwareAdapter((HMODULE)module.ToPointer(), &pAdapter));

        return gcnew DXGIAdapter(pAdapter);
    }
    finally
    {
        SAFE_RELEASE(pAdapter);
    }
}
