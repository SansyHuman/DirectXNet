#include "DXGISwapChain.h"
#include "../Common/Result.h"
#include "DXGIOutput.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGISwapChain::DXGISwapChain(::IDXGISwapChain* pSwapchain)
    : DXGIDeviceSubObject((::IDXGIDeviceSubObject*)pSwapchain)
{
    this->pSwapchain = pSwapchain;
}

void DirectXNet::DXGI::DXGISwapChain::AttatchComObj(::IUnknown* pComObj)
{
    DXGIDeviceSubObject::AttatchComObj(pComObj);
    pSwapchain = (::IDXGISwapChain*)pComObj;
}

Guid DirectXNet::DXGI::DXGISwapChain::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGISwapChain), Guid);
}

Result DirectXNet::DXGI::DXGISwapChain::Present(unsigned int syncInterval, DXGIPresent flags)
{
    return Result(pSwapchain->Present(syncInterval, (UINT)flags));
}

generic <typename T> where T : DirectXNet::Common::Unknown
T DirectXNet::DXGI::DXGISwapChain::GetBuffer(unsigned int index)
{
    ::IUnknown* queried = __nullptr;

    try
    {
        _GUID objGuid = CAST_TO(DirectXNet::Common::Unknown::GetGuidOfObject<T>(), _GUID);

        Result::ThrowIfFailed(pSwapchain->GetBuffer(index, objGuid, (void**)&queried));

        T queryObj = (T)Activator::CreateInstance(T::typeid, true);
        queryObj->AttatchComObj(queried);

        return queryObj;
    }
    finally
    {
        SAFE_RELEASE(queried);
    }
}

Result DirectXNet::DXGI::DXGISwapChain::SetFullscreenState(bool fullscreen, DXGIOutput^ target)
{
    ::IDXGIOutput* pTarget = __nullptr;

    try
    {
        if(target != nullptr)
            pTarget = (::IDXGIOutput*)target->GetNativeInterface();

        return Result(pSwapchain->SetFullscreenState((BOOL)fullscreen, pTarget));
    }
    finally
    {
        SAFE_RELEASE(pTarget);
    }
}

Result DirectXNet::DXGI::DXGISwapChain::GetFullscreenState(bool% fullscreen, DXGIOutput^% target)
{
    ::IDXGIOutput* pTarget = __nullptr;

    try
    {
        BOOL full = FALSE;

        Result result(pSwapchain->GetFullscreenState(&full, &pTarget));

        fullscreen = (bool)full;
        if(pTarget == __nullptr)
        {
            target = nullptr;
        }
        else
        {
            target = gcnew DXGIOutput(pTarget);
        }

        return result;
    }
    finally
    {
        SAFE_RELEASE(pTarget);
    }
}

DXGISwapChainDesc DirectXNet::DXGI::DXGISwapChain::SwapChainDesc::get()
{
    DXGISwapChainDesc desc;
    Result::ThrowIfFailed(pSwapchain->GetDesc((::DXGI_SWAP_CHAIN_DESC*)&desc));

    return desc;
}

Result DirectXNet::DXGI::DXGISwapChain::ResizeBuffers(
    unsigned int bufferCount, unsigned int width, unsigned int height, DXGIFormat newFormat,
    DXGISwapChainFlag flags)
{
    return Result(
        pSwapchain->ResizeBuffers(bufferCount, width, height, (DXGI_FORMAT)newFormat, (UINT)flags));
}

Result DirectXNet::DXGI::DXGISwapChain::ResizeTarget(DXGIModeDesc% newTargetParameters)
{
    pin_ptr<DXGIModeDesc> pParam = &newTargetParameters;
    return Result(pSwapchain->ResizeTarget((::DXGI_MODE_DESC*)pParam));
}

DXGIOutput^ DirectXNet::DXGI::DXGISwapChain::ContainingOutput::get()
{
    ::IDXGIOutput* pOutput = __nullptr;

    try
    {
        Result result(pSwapchain->GetContainingOutput(&pOutput));
        if(result.Succeeded)
        {
            DXGIOutput^ output = gcnew DXGIOutput(pOutput);
            return output;
        }
        else
        {
            result.ThrowIfFailed();
            return nullptr;
        }
    }
    finally
    {
        SAFE_RELEASE(pOutput);
    }
}

DXGIFrameStatistics DirectXNet::DXGI::DXGISwapChain::FrameStatistics::get()
{
    DXGIFrameStatistics stats;
    Result::ThrowIfFailed(pSwapchain->GetFrameStatistics((::DXGI_FRAME_STATISTICS*)&stats));
    return stats;
}

unsigned int DirectXNet::DXGI::DXGISwapChain::LastPresentCount::get()
{
    unsigned int cnt = 0;
    Result::ThrowIfFailed(pSwapchain->GetLastPresentCount(&cnt));
    return cnt;
}
