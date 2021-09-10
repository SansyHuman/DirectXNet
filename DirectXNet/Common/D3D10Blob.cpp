#include "../pch.h"
#include "D3D10Blob.h"
#include "Result.h"

using namespace System::Runtime::InteropServices;
using namespace System;

DirectXNet::Common::D3D10Blob::D3D10Blob(::ID3D10Blob* pBlob)
    : Unknown((::IUnknown*)pBlob)
{
    this->pBlob = pBlob;
}

void DirectXNet::Common::D3D10Blob::AttatchComObj(::IUnknown* pComObj)
{
    Unknown::AttatchComObj(pComObj);
    pBlob = (::ID3D10Blob*)pComObj;
}

Guid DirectXNet::Common::D3D10Blob::GetGuid()
{
    return *((Guid*)&__uuidof(::ID3D10Blob));
}

IntPtr DirectXNet::Common::D3D10Blob::BufferPointer::get()
{
    return IntPtr(pBlob->GetBufferPointer());
}

SIZE_T  DirectXNet::Common::D3D10Blob::BufferSize::get()
{
    return pBlob->GetBufferSize();
}

unsigned char DirectXNet::Common::D3D10Blob::default::get(SIZE_T index)
{
    if(index >= pBlob->GetBufferSize())
        throw gcnew IndexOutOfRangeException("Index out of blob buffer range.");

    unsigned char* pBuffer = (unsigned char*)pBlob->GetBufferPointer();
    return pBuffer[index];
}

void DirectXNet::Common::D3D10Blob::default::set(SIZE_T index, unsigned char value)
{
    if(index >= pBlob->GetBufferSize())
        throw gcnew IndexOutOfRangeException("Index out of blob buffer range.");

    unsigned char* pBuffer = (unsigned char*)pBlob->GetBufferPointer();
    pBuffer[index] = value;
}

generic <typename T> where T : value class
T DirectXNet::Common::D3D10Blob::GetValue(SIZE_T index)
{
    SIZE_T valSize = sizeof(T);
    if((index + 1) * valSize > pBlob->GetBufferSize())
        throw gcnew IndexOutOfRangeException("Index out of blob buffer range.");

    interior_ptr<T> pBuffer = (interior_ptr<T>)pBlob->GetBufferPointer();
    return pBuffer[index];
}

generic <typename T> where T : value class
void DirectXNet::Common::D3D10Blob::SetValue(SIZE_T index, T value)
{
    SIZE_T valSize = sizeof(T);
    if((index + 1) * valSize > pBlob->GetBufferSize())
        throw gcnew IndexOutOfRangeException("Index out of blob buffer range.");

    __int8* pBuffer = (__int8*)pBlob->GetBufferPointer();
    pBuffer += index * valSize;
    pin_ptr<T> pValue = &value;

    memcpy((void*)pBuffer, (const void*)pValue, valSize);
}

generic <typename T> where T : value class
SIZE_T DirectXNet::Common::D3D10Blob::GetBufferSize()
{
    return pBlob->GetBufferSize() / sizeof(T);
}