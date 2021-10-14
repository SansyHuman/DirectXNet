#include "DXGIOutput.h"
#include "DXGISurface.h"

using namespace DirectXNet::Common;
using namespace msclr::interop;
using namespace DirectXNet::DXGI;

DirectXNet::DXGI::DXGIOutput::DXGIOutput(::IDXGIOutput* pOutput)
    : DXGIObject((::IDXGIObject*)pOutput)
{
    this->pOutput = pOutput;
}

void DirectXNet::DXGI::DXGIOutput::AttatchComObj(::IUnknown* pComObj)
{
    DXGIObject::AttatchComObj(pComObj);
    pOutput = (::IDXGIOutput*)pComObj;
}

Guid DirectXNet::DXGI::DXGIOutput::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIOutput), Guid);
}

DXGIModeDesc DirectXNet::DXGI::DXGIOutput::FindClosestMatchingMode(
    DXGIModeDesc% modeToMatch, DirectXNet::Common::Unknown^ concernedDevice)
{
    ::IUnknown* pConcernedDevice = __nullptr;

    try
    {
        pin_ptr<DXGIModeDesc> pModeToMatch = &modeToMatch;
        ::DXGI_MODE_DESC* pModeToMatchN = (::DXGI_MODE_DESC*)pModeToMatch;
        DXGIModeDesc closestMatch;
        if(concernedDevice != nullptr)
            pConcernedDevice = concernedDevice->GetNativeInterface();

        Result::ThrowIfFailed(pOutput->FindClosestMatchingMode(
            pModeToMatchN, (::DXGI_MODE_DESC*)&closestMatch, pConcernedDevice));

        return closestMatch;
    }
    finally
    {
        SAFE_RELEASE(pConcernedDevice);
    }
}

DXGIOutputDesc DirectXNet::DXGI::DXGIOutput::OutputDesc::get()
{
    DXGI_OUTPUT_DESC desc = {};
    Result::ThrowIfFailed(pOutput->GetDesc(&desc));

    DXGIOutputDesc clrDesc;
    clrDesc.DeviceName = marshal_as<System::String^>(desc.DeviceName);
    clrDesc.DesktopCoordinates = *((Common::Rect*)&desc.DesktopCoordinates);
    clrDesc.AttachedToDesktop = (Common::CBool)desc.AttachedToDesktop;
    clrDesc.Rotation = (DXGIModeRotation)desc.Rotation;
    clrDesc.Monitor = IntPtr((void*)desc.Monitor);

    return clrDesc;
}

array<DXGIModeDesc>^ DirectXNet::DXGI::DXGIOutput::GetDisplayModeList(DXGIFormat enumFormat, DXGIEnumModes flags)
{
    UINT num = 0;
    pOutput->GetDisplayModeList((::DXGI_FORMAT)enumFormat, (UINT)flags, &num, __nullptr);

    array<DXGIModeDesc>^ modes = gcnew array<DXGIModeDesc>(num);
    pin_ptr<DXGIModeDesc> pModes = &modes[0];
    ::DXGI_MODE_DESC* pModesN = (::DXGI_MODE_DESC*)pModes;

    Result::ThrowIfFailed(pOutput->GetDisplayModeList((::DXGI_FORMAT)enumFormat, (UINT)flags, &num, pModesN));

    pModes = nullptr;
    return modes;
}

Result DirectXNet::DXGI::DXGIOutput::GetDisplaySurfaceData(DXGISurface^ destination)
{
    ::IDXGISurface* pDestination = __nullptr;

    try
    {
        pDestination = (::IDXGISurface*)destination->GetNativeInterface();
        HRESULT hr = pOutput->GetDisplaySurfaceData(pDestination);

        return Result(hr);
    }
    finally
    {
        SAFE_RELEASE(pDestination);
    }
}

DXGIFrameStatistics DirectXNet::DXGI::DXGIOutput::FrameStatistics::get()
{
    DXGIFrameStatistics stat;
    Result::ThrowIfFailed(pOutput->GetFrameStatistics((::DXGI_FRAME_STATISTICS*)&stat));

    return stat;
}

DXGIGammaControl DirectXNet::DXGI::DXGIOutput::GammaControl::get()
{
    DXGI_GAMMA_CONTROL control = {};
    Result::ThrowIfFailed(pOutput->GetGammaControl(&control));

    DXGIGammaControl clrControl;
    clrControl.Scale = CAST_TO(control.Scale, DXGIRGB);
    clrControl.Offset = CAST_TO(control.Offset, DXGIRGB);
    clrControl.GammaCurve = gcnew array<DXGIRGB>(1025);
    pin_ptr<DXGIRGB> pCurve = &clrControl.GammaCurve[0];
    memcpy((void*)pCurve, (void*)&control.GammaCurve[0], sizeof(DXGIRGB) * 1025);

    pCurve = nullptr;
    return clrControl;
}

void DirectXNet::DXGI::DXGIOutput::GammaControl::set(DXGIGammaControl control)
{
    ::DXGI_GAMMA_CONTROL controlN = {};

    controlN.Scale = CAST_TO(control.Scale, DXGI_RGB);
    controlN.Offset = CAST_TO(control.Offset, DXGI_RGB);
    pin_ptr<DXGIRGB> pCurve = &control.GammaCurve[0];
    memcpy((void*)&controlN.GammaCurve[0], (void*)pCurve, sizeof(::DXGI_RGB) * control.GammaCurve->Length);

    Result::ThrowIfFailed(pOutput->SetGammaControl(&controlN));
    pCurve = nullptr;
}

DXGIGammaControlCapabilities DirectXNet::DXGI::DXGIOutput::GammaControlCapabilities::get()
{
    ::DXGI_GAMMA_CONTROL_CAPABILITIES caps = {};
    Result::ThrowIfFailed(pOutput->GetGammaControlCapabilities(&caps));

    DXGIGammaControlCapabilities clrCaps;
    clrCaps.ScaleAndOffsetSupported = (CBool)caps.ScaleAndOffsetSupported;
    clrCaps.MaxConvertedValue = caps.MaxConvertedValue;
    clrCaps.MinConvertedValue = caps.MinConvertedValue;
    clrCaps.NumGammaControlPoints = caps.NumGammaControlPoints;
    clrCaps.ControlPointPositions = gcnew array<float>(clrCaps.NumGammaControlPoints);
    pin_ptr<float> pControlPoints = &clrCaps.ControlPointPositions[0];
    memcpy((void*)pControlPoints, &caps.ControlPointPositions[0], sizeof(float) * clrCaps.NumGammaControlPoints);
    pControlPoints = nullptr;

    return clrCaps;
}

void DirectXNet::DXGI::DXGIOutput::ReleaseOwnership()
{
    pOutput->ReleaseOwnership();
}

Result DirectXNet::DXGI::DXGIOutput::SetDisplaySurface(DXGISurface^ scanoutSurface)
{
    ::IDXGISurface* pSurface = __nullptr;

    try
    {
        pSurface = (::IDXGISurface*)scanoutSurface->GetNativeInterface();
        Result result(pOutput->SetDisplaySurface(pSurface));

        return result;
    }
    finally
    {
        SAFE_RELEASE(pSurface);
    }
}

Result DirectXNet::DXGI::DXGIOutput::TakeOwnership(Unknown^ device, bool exclusive)
{
    ::IUnknown* pDevice = __nullptr;

    try
    {
        pDevice = device->GetNativeInterface();
        Result result(pOutput->TakeOwnership(pDevice, (BOOL)exclusive));

        return result;
    }
    finally
    {
        SAFE_RELEASE(pDevice);
    }
}

Result DirectXNet::DXGI::DXGIOutput::WaitForVBlank()
{
    return Result(pOutput->WaitForVBlank());
}
