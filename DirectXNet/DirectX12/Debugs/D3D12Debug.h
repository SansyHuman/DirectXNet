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
            /// A class used to turn on the debug layer.
            /// </summary>
            public ref class D3D12Debug : Common::Unknown
            {
            private:
                ::ID3D12Debug* pDebug;

            internal:
                D3D12Debug(::ID3D12Debug* pDebug);
                D3D12Debug() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12Debug.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Enables the debug layer.
                /// </summary>
                void EnableDebugLayer();
            };
        }
    }
}