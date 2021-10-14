#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"

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
            /// Adds GPU-Based Validation and Dependent Command Queue Synchronization to the debug layer.
            /// </summary>
            public ref class D3D12Debug1 : Common::Unknown
            {
            private:
                ::ID3D12Debug1* pDebug;

            internal:
                D3D12Debug1(::ID3D12Debug1* pDebug);
                D3D12Debug1() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns G2ID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug1.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Enables the debug layer.
                /// </summary>
                void EnableDebugLayer();

                /// <summary>
                /// This method enables or disables GPU-Based Validation (GBV) before creating a device
                /// with the debug layer enabled.
                /// </summary>
                /// <param name="enable">true to enable GPU-Based Validation, otherwise false.</param>
                void SetEnableGPUBasedValidation(bool enable);

                /// <summary>
                /// Enables or disables dependent command queue synchronization when using a D3D12 device
                /// with the debug layer enabled.
                /// </summary>
                /// <param name="enable">true to enable Dependent Command Queue Synchronization, otherwise
                /// false.</param>
                void SetEnableSynchronizedCommandQueueValidation(bool enable);
            };
        }
    }
}