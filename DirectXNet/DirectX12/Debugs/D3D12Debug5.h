#pragma once

#include "../../pch.h"
#include "D3D12Debug4.h"
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
            /// Adds to the debug layer the ability to configure the auto-naming of objects.
            /// </summary>
            public ref class D3D12Debug5 : D3D12Debug4
            {
            private:
                ::ID3D12Debug5* pDebug5;

            internal:
                D3D12Debug5(::ID3D12Debug5* pDebug5);
                D3D12Debug5() : D3D12Debug4() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug5.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Configures the auto-naming of objects.
                /// </summary>
                /// <param name="enable">true to enable auto-naming; false to disable auto-naming.</param>
                void SetEnableAutoName(bool enable);
            };
        }
    }
}