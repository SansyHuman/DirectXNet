#include "DXGIDebugStructs.h"

DirectXNet::DXGI::Debug::DXGIDebugID::DXGIDebugID()
{
    All = CAST_TO(::DXGI_DEBUG_ALL, Guid);
    DX = CAST_TO(::DXGI_DEBUG_DX, Guid);
    DXGI = CAST_TO(::DXGI_DEBUG_DXGI, Guid);
    APP = CAST_TO(::DXGI_DEBUG_APP, Guid);
    D3D12 = CAST_TO(::DXGI_DEBUG_D3D12, Guid);
}