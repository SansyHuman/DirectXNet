#include "D2D1Resource.h"
#include "D2D1Factory.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::Direct2D;

DirectXNet::Direct2D::D2D1Resource::D2D1Resource(::ID2D1Resource* pResource)
    : DirectXNet::Common::Unknown((::IUnknown*)pResource)
{
    this->pResource = pResource;
}

void DirectXNet::Direct2D::D2D1Resource::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pResource = (::ID2D1Resource*)pComObj;
}

Guid DirectXNet::Direct2D::D2D1Resource::GetGuid()
{
    return CAST_TO(__uuidof(::ID2D1Resource), Guid);
}

D2D1Factory^ DirectXNet::Direct2D::D2D1Resource::Factory::get()
{
    ::ID2D1Factory* pFactory = __nullptr;

    try
    {
        pResource->GetFactory(&pFactory);
        return gcnew D2D1Factory(pFactory);
    }
    finally
    {
        SAFE_RELEASE(pFactory);
    }
}
