#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"
#include "D3D12DebugStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DirectX12
    {
        namespace Debug
        {
            /// <summary>
            /// This interface represents a graphics device for debugging.
            /// </summary>
            public ref class D3D12DebugDevice : Common::Unknown
            {
            private:
                ::ID3D12DebugDevice* pDevice;

            internal:
                D3D12DebugDevice(::ID3D12DebugDevice* pDevice);
                D3D12DebugDevice() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12DebugDevice.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Gets and sets a bit field of flags that indicates which debug features are on or off.
                /// </summary>
                property D3D12DebugFeature FeatureMask
                {
                    D3D12DebugFeature get();
                    void set(D3D12DebugFeature mask);
                }

                /// <summary>
                /// Reports information about a device object's lifetime.
                /// </summary>
                /// <param name="flags">A value from the D3D12RLDOFlags enumeration. This method uses the
                /// value in flags to determine the amount of information to report about a device object's
                /// lifetime.</param>
                /// <returns>Result code.</returns>
                Result ReportLiveDeviceObjects(D3D12RLDOFlags flags);
            };
        }
    }
}