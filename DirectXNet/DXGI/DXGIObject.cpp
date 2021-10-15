#include "DXGIObject.h"
#include "../Common/Result.h"

using namespace System::Runtime::InteropServices;

DirectXNet::DXGI::DXGIObject::DXGIObject(::IDXGIObject* pObj)
    : Common::Unknown((::IUnknown*)pObj)
{
    pDxgiObj = pObj;
}

void DirectXNet::DXGI::DXGIObject::AttatchComObj(::IUnknown* pComObj)
{
    Common::Unknown::AttatchComObj(pComObj);
    pDxgiObj = (::IDXGIObject*)pComObj;
}

Guid DirectXNet::DXGI::DXGIObject::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIObject), Guid);
}

generic <typename T> where T : DirectXNet::Common::Unknown
T DirectXNet::DXGI::DXGIObject::GetParent()
{
    ::IUnknown* parent = __nullptr;

    try
    {
        T parentObj = (T)Activator::CreateInstance(T::typeid, true);
        _GUID objGuid = CAST_TO(parentObj->GetGuid(), _GUID);

        Common::Result::ThrowIfFailed(pDxgiObj->GetParent(objGuid, (void**)&parent));

        parentObj->AttatchComObj(parent);

        return parentObj;
    }
    finally
    {
        SAFE_RELEASE(parent);
    }
}

String^ DirectXNet::DXGI::DXGIObject::DebugObjectName::get()
{
    UINT dataSize = 0;
    pDxgiObj->GetPrivateData(WKPDID_D3DDebugObjectName, &dataSize, __nullptr);

    UINT strLen = dataSize / sizeof(char);
    std::vector<char> name(strLen + 1, 0);
    Common::Result::ThrowIfFailed(pDxgiObj->GetPrivateData(WKPDID_D3DDebugObjectName, &dataSize, (void*)name.data()));

    return msclr::interop::marshal_as<String^>(name.data());
}

void DirectXNet::DXGI::DXGIObject::DebugObjectName::set(String^ name)
{
    msclr::interop::marshal_context context;
    const char* cname = context.marshal_as<const char*>(name);
    UINT dataSize = std::strlen(cname) * sizeof(char);
    Common::Result::ThrowIfFailed(pDxgiObj->SetPrivateData(WKPDID_D3DDebugObjectName, dataSize, (const void*)cname));
}