#pragma once

#include "DXResourceHandle.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::Win32::SafeHandles;

DirectXNet::Common::DXResourceHandle::DXResourceHandle(IntPtr handle)
    : SafeHandleZeroOrMinusOneIsInvalid(true)
{
    SetHandle(handle);
}

HANDLE DirectXNet::Common::DXResourceHandle::NativeHandle::get()
{
    return handle.ToPointer();
}

bool DirectXNet::Common::DXResourceHandle::ReleaseHandle()
{
    return (bool)CloseHandle(this->handle.ToPointer());
}
