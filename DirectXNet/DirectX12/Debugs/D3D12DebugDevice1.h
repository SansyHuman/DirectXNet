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
            /// Specifies device-wide debug layer settings.
            /// </summary>
            public ref class D3D12DebugDevice1 : Common::Unknown
            {
            private:
                ::ID3D12DebugDevice1* pDevice;

            internal:
                D3D12DebugDevice1(::ID3D12DebugDevice1* pDevice);
                D3D12DebugDevice1() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12DebugDevice1.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Modifies the D3D12 optional device-wide Debug Layer settings.
                /// </summary>
                /// <typeparam name="T">Type of the parameter.</typeparam>
                /// <param name="type">Specifies a D3D12DebugDeviceParameterType value that indicates
                /// which debug parameter data to set.</param>
                /// <param name="data">Debug parameter data to set.</param>
                /// <returns>Result code.</returns>
                generic <typename T> where T : IDeviceDebugParameter, value class
                Result SetDebugParameter(
                    D3D12DebugDeviceParameterType type,
                    [In][IsReadOnly] T% data
                );

                /// <summary>
                /// Gets optional device-wide Debug Layer settings.
                /// </summary>
                /// <typeparam name="T">Type of the parameter.</typeparam>
                /// <param name="type">Specifies a D3D12DebugDeviceParameterType value that indicates
                /// which debug parameter data to get.</param>
                /// <param name="data">Reference to the memory that will be filled with a copy of the
                /// debug parameter data. The interpretation of this data depends on the
                /// D3D12DebugDeviceParameterType given in the type parameter.</param>
                /// <returns>Result code.</returns>
                generic <typename T> where T : IDeviceDebugParameter, value class
                Result GetDebugParameter(
                    D3D12DebugDeviceParameterType type,
                    [Out] T% data
                );

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
