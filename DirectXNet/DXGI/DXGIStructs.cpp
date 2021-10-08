#include "DXGIStructs.h"

DirectXNet::DXGI::D3DColorValue::D3DColorValue(float r, float g, float b, float a)
    : r(r), g(g), b(b), a(a)
{
    
}

bool DirectXNet::DXGI::D3DColorValue::operator==(D3DColorValue% lhs, D3DColorValue% rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

bool DirectXNet::DXGI::D3DColorValue::operator!=(D3DColorValue% lhs, D3DColorValue% rhs)
{
    return !(lhs == rhs);
}

bool DirectXNet::DXGI::D3DColorValue::Equals(Object^ obj)
{
    if(obj->GetType() != D3DColorValue::typeid)
        return false;

    return *this == safe_cast<D3DColorValue>(obj);
}

bool DirectXNet::DXGI::D3DColorValue::Equals(D3DColorValue other)
{
    return *this == other;
}

float DirectXNet::DXGI::D3DColorValue::default::get(int index)
{
    switch(index)
    {
    case 0:
        return r;
    case 1:
        return g;
    case 2:
        return b;
    case 3:
        return a;
    default:
        throw gcnew IndexOutOfRangeException();
    }
}

void DirectXNet::DXGI::D3DColorValue::default::set(int index, float value)
{
    switch(index)
    {
    case 0:
        r = value;
        break;
    case 1:
        g = value;
        break;
    case 2:
        b = value;
        break;
    case 3:
        a = value;
        break;
    default:
        throw gcnew IndexOutOfRangeException();
    }
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
