#include "Result.h"
#include <comdef.h>

DirectXNet::Common::Result::Result(HRESULT code)
{
    result = code;
}

bool DirectXNet::Common::Result::Succeeded::get()
{
    return SUCCEEDED(result);
}

bool DirectXNet::Common::Result::Failed::get()
{
    return FAILED(result);
}

void DirectXNet::Common::Result::ThrowIfFailed()
{
    System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(result);
}

System::String^ DirectXNet::Common::Result::Message::get()
{
    _com_error error(result);
    return msclr::interop::marshal_as<System::String^>(error.ErrorMessage());
}

void DirectXNet::Common::Result::ThrowIfFailed(HRESULT result)
{
    System::Runtime::InteropServices::Marshal::ThrowExceptionForHR(result);
}
