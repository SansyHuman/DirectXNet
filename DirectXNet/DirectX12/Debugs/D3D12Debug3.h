#pragma once

#include "../../pch.h"
#include "D3D12Debug.h"
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
            /// Adds configurable levels of GPU-based validation to the debug layer.
            /// </summary>
            public ref class D3D12Debug3 : D3D12Debug
            {
            private:
                ::ID3D12Debug3* pDebug3;

            internal:
                D3D12Debug3(::ID3D12Debug3* pDebug3);
                D3D12Debug3() : D3D12Debug() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug3.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// This method enables or disables GPU-based validation (GBV) before creating a device with
                /// the debug layer enabled.
                /// </summary>
                /// <param name="enable">true to enable GPU-based validation, otherwise false.</param>
                void SetEnableGPUBasedValidation(bool enable);

                /// <summary>
                /// Enables or disables dependent command queue synchronization when using a Direct3D 12
                /// device with the debug layer enabled.
                /// </summary>
                /// <param name="enable">true to enable Dependent Command Queue Synchronization, otherwise
                /// false.</param>
                void SetEnableSynchronizedCommandQueueValidation(bool enable);

                /// <summary>
                /// This method configures the level of GPU-based validation that the debug device is to
                /// perform at runtime.
                /// </summary>
                /// <param name="flags">Specifies the level of GPU-based validation to perform at runtime.
                /// </param>
                void SetGPUBasedValidationFlags(D3D12GPUBasedValidationFlags flags);
            };
        }
    }
}