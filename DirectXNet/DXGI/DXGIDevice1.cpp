#include "DXGIDevice1.h"
#include "../Common/Result.h"
#include "DXGIAdapter.h"
#include "DXGISurface.h"
#include <vector>

using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIDevice1::DXGIDevice1(::IDXGIDevice1* pDevice1)
    : DXGIDevice((::IDXGIDevice*)pDevice1)
{
    this->pDevice1 = pDevice1;
}

void DirectXNet::DXGI::DXGIDevice1::AttatchComObj(::IUnknown* pComObj)
{
    DXGIDevice::AttatchComObj(pComObj);
    pDevice1 = (::IDXGIDevice1*)pComObj;
}

Guid DirectXNet::DXGI::DXGIDevice1::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIDevice1), Guid);
}

unsigned int DirectXNet::DXGI::DXGIDevice1::MaximumFrameLatency::get()
{
    unsigned int value = 0;
    Result::ThrowIfFailed(pDevice1->GetMaximumFrameLatency(&value));

    return value;
}

void DirectXNet::DXGI::DXGIDevice1::MaximumFrameLatency::set(unsigned int value)
{
    Result::ThrowIfFailed(pDevice1->SetMaximumFrameLatency(value));
}
