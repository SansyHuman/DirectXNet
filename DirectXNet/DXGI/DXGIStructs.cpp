#include "DXGIStructs.h"

DirectXNet::DXGI::D3DColorValue::D3DColorValue(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{
    
}

DirectXNet::DXGI::DXGIRational::DXGIRational(unsigned int numerator, unsigned int denominator)
    : Numerator(numerator), Denominator(denominator)
{
    
}

DirectXNet::DXGI::DXGISampleDesc::DXGISampleDesc(unsigned int sampleCount, unsigned int quality)
    : Count(sampleCount), Quality(quality)
{
    
}

DirectXNet::DXGI::DXGIRGB::DXGIRGB(float r, float g, float b)
    : Red(r), Green(g), Blue(b)
{
    
}

DirectXNet::DXGI::DXGIGammaControl::DXGIGammaControl(
    DXGIRGB scale, DXGIRGB offset, array<DXGIRGB>^ gammaCurve)
    : Scale(scale), Offset(offset), GammaCurve(gammaCurve)
{
    
}
