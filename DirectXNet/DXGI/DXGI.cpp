#include "DXGI.h"
#include "../Common/Result.h"
#include "../Common/Unknown.h"
#include "DXGIAdapter.h"
#include "DXGIAdapter1.h"
#include "DXGIDevice.h"
#include "DXGIDevice1.h"
#include "DXGIDeviceSubObject.h"
#include "DXGIFactory.h"
#include "DXGIFactory1.h"
#include "DXGIKeyedMutex.h"
#include "DXGIObject.h"
#include "DXGIOutput.h"
#include "DXGIResource.h"
#include "DXGISurface.h"
#include "DXGISurface1.h"
#include "DXGISwapChain.h"

#include "Debug/DXGIDebug.h"
#include "Debug/DXGIInfoQueue.h"

using namespace DirectXNet::DXGI;
using namespace DirectXNet::Common;
using namespace System::Runtime::InteropServices;

#ifndef CHECK_DXGI_GUID
#define CHECK_DXGI_GUID(type) if(*((_GUID*)&Unknown::GetGuidOfObject<DirectXNet::DXGI:: ## type ## ^>()) != __uuidof(::I ## type)) throw gcnew Exception("GUID check error");
#endif

#ifndef CHECK_DXGI_DEBUG_GUID
#define CHECK_DXGI_DEBUG_GUID(type) if(*((_GUID*)&Unknown::GetGuidOfObject<DirectXNet::DXGI::Debug:: ## type ## ^>()) != __uuidof(::I ## type)) throw gcnew Exception("GUID check error");
#endif


DirectXNet::DXGI::DXGI::DXGI()
{
#if defined(DEBUG) | defined (_DEBUG)
    CHECK_DXGI_GUID(DXGIAdapter);
    CHECK_DXGI_GUID(DXGIAdapter1);
    CHECK_DXGI_GUID(DXGIDevice);
    CHECK_DXGI_GUID(DXGIDevice1);
    CHECK_DXGI_GUID(DXGIDeviceSubObject);
    CHECK_DXGI_GUID(DXGIFactory);
    CHECK_DXGI_GUID(DXGIFactory1);
    CHECK_DXGI_GUID(DXGIKeyedMutex);
    CHECK_DXGI_GUID(DXGIObject);
    CHECK_DXGI_GUID(DXGIOutput);
    CHECK_DXGI_GUID(DXGIResource);
    CHECK_DXGI_GUID(DXGISurface);
    CHECK_DXGI_GUID(DXGISurface1);
    CHECK_DXGI_GUID(DXGISwapChain);

    CHECK_DXGI_DEBUG_GUID(DXGIDebug);
    CHECK_DXGI_DEBUG_GUID(DXGIInfoQueue);
#endif
}

generic <typename T> where T : DXGIFactory
T DirectXNet::DXGI::DXGI::CreateDXGIFactory()
{
    ::IUnknown* pFactory = __nullptr;

    try
    {
        Guid guid = Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(::CreateDXGIFactory(*((_GUID*)&guid), (void**)&pFactory));

        T factory = (T)Activator::CreateInstance(T::typeid, true);
        factory->AttatchComObj(pFactory);

        return factory;
    }
    finally
    {
        SAFE_RELEASE(pFactory);
    }
}

generic <typename T> where T : DXGIFactory
T DirectXNet::DXGI::DXGI::CreateDXGIFactory1()
{
    ::IUnknown* pFactory = __nullptr;

    try
    {
        Guid guid = Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(::CreateDXGIFactory1(CAST_TO(guid, _GUID), (void**)&pFactory));

        T factory = (T)Activator::CreateInstance(T::typeid, true);
        factory->AttatchComObj(pFactory);

        return factory;
    }
    finally
    {
        SAFE_RELEASE(pFactory);
    }
}

DirectXNet::DXGI::DXGI::Debug::Debug()
{
    debugDLL = LoadLibraryW(L"dxgidebug.dll");
    if(debugDLL == __nullptr)
    {
        Result::ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }

    DXGIGetDebugInterface = (fPtr)GetProcAddress(debugDLL, "DXGIGetDebugInterface");
    if(DXGIGetDebugInterface == __nullptr)
    {
        Result::ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
    }
}

generic <typename T> where T : DirectXNet::Common::Unknown
T DirectXNet::DXGI::DXGI::Debug::GetDebugInterface()
{
    ::IUnknown* pDebug = __nullptr;

    try
    {
        Guid guid = Unknown::GetGuidOfObject<T>();

        Result::ThrowIfFailed(DXGIGetDebugInterface(CAST_TO(guid, _GUID), (void**)&pDebug));

        T debug = (T)Activator::CreateInstance(T::typeid, true);
        debug->AttatchComObj(pDebug);

        return debug;
    }
    finally
    {
        SAFE_RELEASE(pDebug);
    }
}
