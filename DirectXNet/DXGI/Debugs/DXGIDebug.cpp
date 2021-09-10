#include "DXGIDebug.h"
#include "../../Common/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI::Debug;

DirectXNet::DXGI::Debug::DXGIDebug::DXGIDebug(::IDXGIDebug* pDebug)
    : DirectXNet::Common::Unknown((::IUnknown*)pDebug)
{
    this->pDebug = pDebug;
}

void DirectXNet::DXGI::Debug::DXGIDebug::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pDebug = (::IDXGIDebug*)pComObj;
}

Guid DirectXNet::DXGI::Debug::DXGIDebug::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIDebug), Guid);
}

Result DirectXNet::DXGI::Debug::DXGIDebug::ReportLiveObjects(Guid apiid, DXGIDebugRLOFlags flags)
{
    return Result(pDebug->ReportLiveObjects(CAST_TO(apiid, _GUID), (DXGI_DEBUG_RLO_FLAGS)flags));
}
