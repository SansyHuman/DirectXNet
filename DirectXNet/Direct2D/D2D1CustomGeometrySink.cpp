#include "D2D1CustomGeometrySink.h"
#include "D2D1CustomGeometrySinkNative.h"

using namespace DirectXNet::Direct2D;

D2D1CustomGeometrySinkNative* DirectXNet::Direct2D::D2D1CustomGeometrySink::NativeSink::get()
{
    pCustomSink->AddRef();
    return pCustomSink;
}

DirectXNet::Direct2D::D2D1CustomGeometrySink::D2D1CustomGeometrySink()
{
    pCustomSink = new D2D1CustomGeometrySinkNative(this);
}

DirectXNet::Direct2D::D2D1CustomGeometrySink::~D2D1CustomGeometrySink()
{
    this->!D2D1CustomGeometrySink();
}

DirectXNet::Direct2D::D2D1CustomGeometrySink::!D2D1CustomGeometrySink()
{
    SAFE_RELEASE(pCustomSink);
}
