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
            /// Adds configurable levels of GPU-based validation to the debug layer.
            /// </summary>
            public ref class D3D12Debug2 : Common::Unknown
            {
            private:
                ::ID3D12Debug2* pDebug;

            internal:
                D3D12Debug2(::ID3D12Debug2* pDebug);
                D3D12Debug2() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug2.</returns>
                virtual Guid GetGuid() override;

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