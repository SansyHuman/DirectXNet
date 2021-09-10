#include "../pch.h"
#include "Unknown.h"
#include "Result.h"

using namespace System::Runtime::InteropServices;

DirectXNet::Common::Unknown::Unknown(::IUnknown* pComObj)
{
    this->pComObj = pComObj;
    pComObj->AddRef();
}

DirectXNet::Common::Unknown::~Unknown()
{
    this->!Unknown();
}

DirectXNet::Common::Unknown::!Unknown()
{
    SAFE_RELEASE(this->pComObj);
}

void DirectXNet::Common::Unknown::AttatchComObj(::IUnknown* pComObj)
{
    SAFE_RELEASE(this->pComObj);
    this->pComObj = pComObj;
    pComObj->AddRef();
}

::IUnknown* DirectXNet::Common::Unknown::GetNativeInterface()
{
    if(this->pComObj == __nullptr)
        return __nullptr;

    this->pComObj->AddRef();
    return this->pComObj;
}

Guid DirectXNet::Common::Unknown::GetGuid()
{
    return *((Guid*)&__uuidof(::IUnknown));
}

generic <typename T> where T : DirectXNet::Common::Unknown
Guid DirectXNet::Common::Unknown::GetGuidOfObject()
{
    T obj = (T)Activator::CreateInstance(T::typeid, true);
    Guid guid = obj->GetGuid();
    delete obj;

    return guid;
}

generic <typename T> where T : DirectXNet::Common::Unknown
T DirectXNet::Common::Unknown::QueryInterface()
{
    ::IUnknown* queried = __nullptr;

    try
    {
        T queryObj = (T)Activator::CreateInstance(T::typeid, true);
        _GUID objGuid = *((_GUID*)&queryObj->GetGuid());

        Result::ThrowIfFailed(pComObj->QueryInterface(objGuid, (void**)&queried));

        queryObj->AttatchComObj(queried);

        return queryObj;
    }
    finally
    {
        SAFE_RELEASE(queried);
    }
}

bool DirectXNet::Common::Unknown::NativeEquals(Unknown^ obj)
{
    if(obj == nullptr)
        return false;

    ::IUnknown* rhs = __nullptr;
    ::IUnknown* lhs = __nullptr;

    try
    {
        rhs = this->GetNativeInterface();
        lhs = obj->GetNativeInterface();

        if(rhs == __nullptr || lhs == __nullptr)
            return false;

        return rhs == lhs;
    }
    finally
    {
        SAFE_RELEASE(rhs);
        SAFE_RELEASE(lhs);
    }
}