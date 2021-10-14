#pragma once

#include "../../pch.h"
#include "D3D12Debug3.h"
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
            /// Adds the ability to disable the debug layer.
            /// </summary>
            public ref class D3D12Debug4 : D3D12Debug3
            {
            private:
                ::ID3D12Debug4* pDebug4;

            internal:
                D3D12Debug4(::ID3D12Debug4* pDebug4);
                D3D12Debug4() : D3D12Debug3() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug4.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Disables the debug layer.
                /// </summary>
                void DisableDebugLayer();
            };
        }
    }
}