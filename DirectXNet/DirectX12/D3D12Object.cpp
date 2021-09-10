#include "D3D12Object.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;

DirectXNet::DirectX12::D3D12Object::D3D12Object(::ID3D12Object* pD3D12Obj)
    : DirectXNet::Common::Unknown((::IUnknown*)pD3D12Obj)
{
    this->pD3D12Obj = pD3D12Obj;
}

void DirectXNet::DirectX12::D3D12Object::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pD3D12Obj = (::ID3D12Object*)pComObj;
}

Guid DirectXNet::DirectX12::D3D12Object::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12Object), Guid);
}

String^ DirectXNet::DirectX12::D3D12Object::Name::get()
{
    UINT dataSize = 0;
    pD3D12Obj->GetPrivateData(WKPDID_D3DDebugObjectNameW, &dataSize, __nullptr);

    UINT strLen = dataSize / sizeof(wchar_t);
    std::vector<wchar_t> name(strLen + 1);
    Common::Result::ThrowIfFailed(pD3D12Obj->GetPrivateData(WKPDID_D3DDebugObjectNameW, &dataSize, (void*)name.data()));

    return msclr::interop::marshal_as<String^>(name.data());
}

void DirectXNet::DirectX12::D3D12Object::Name::set(String^ name)
{
    msclr::interop::marshal_context context;
    const wchar_t* cname = context.marshal_as<const wchar_t*>(name);
    Common::Result::ThrowIfFailed(pD3D12Obj->SetName(cname));
}
