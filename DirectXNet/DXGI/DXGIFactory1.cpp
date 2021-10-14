#include "DXGIFactory1.h"
#include "../Common/Result.h"
#include "DXGIAdapter1.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIFactory1::DXGIFactory1(::IDXGIFactory1* pFactory1)
    : DXGIFactory((::IDXGIFactory*)pFactory1)
{
    this->pFactory1 = pFactory1;
}

void DirectXNet::DXGI::DXGIFactory1::AttatchComObj(::IUnknown* pComObj)
{
    DXGIFactory::AttatchComObj(pComObj);
    pFactory1 = (::IDXGIFactory1*)pComObj;
}

Guid DirectXNet::DXGI::DXGIFactory1::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIFactory1), Guid);
}

Result DirectXNet::DXGI::DXGIFactory1::EnumAdapters1(unsigned int index, DXGIAdapter1^% adapter)
{
    ::IDXGIAdapter1* pAdapter = __nullptr;

    try
    {
        Result result(pFactory1->EnumAdapters1(index, &pAdapter));
        if(result.Failed)
        {
            adapter = nullptr;
            return result;
        }

        adapter = gcnew DXGIAdapter1(pAdapter);

        return result;
    }
    finally
    {
        SAFE_RELEASE(pAdapter);
    }
}

bool DirectXNet::DXGI::DXGIFactory1::IsCurrent::get()
{
    return !!(pFactory1->IsCurrent());
}
