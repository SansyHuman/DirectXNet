#include "DXGIKeyedMutex.h"
#include "../Common/Result.h"

using namespace System::Runtime::InteropServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIKeyedMutex::DXGIKeyedMutex(::IDXGIKeyedMutex* pMutex)
    : DXGIDeviceSubObject((::IDXGIDeviceSubObject*)pMutex)
{
    this->pMutex = pMutex;
}

void DirectXNet::DXGI::DXGIKeyedMutex::AttatchComObj(::IUnknown* pComObj)
{
    DXGIDeviceSubObject::AttatchComObj(pComObj);
    pMutex = (::IDXGIKeyedMutex*)pComObj;
}

Guid DirectXNet::DXGI::DXGIKeyedMutex::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIKeyedMutex), Guid);
}

Result DirectXNet::DXGI::DXGIKeyedMutex::AcquireSync(unsigned long long key, unsigned long milliseconds)
{
    return Result(pMutex->AcquireSync(key, milliseconds));
}

Result DirectXNet::DXGI::DXGIKeyedMutex::ReleaseSync(unsigned long long key)
{
    return Result(pMutex->ReleaseSync(key));
}
