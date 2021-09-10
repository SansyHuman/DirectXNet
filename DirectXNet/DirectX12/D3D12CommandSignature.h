#pragma once

#include "../pch.h"
#include "D3D12Pageable.h"
#include "../Common/Result.h"

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
        /// <summary>
        /// A command signature object enables apps to specify indirect drawing, including the
        /// buffer format, command type and resource bindings to be used.
        /// </summary>
        public ref class D3D12CommandSignature : D3D12Pageable
        {
        public:
            D3D12CommandSignature(::ID3D12CommandSignature* pSignature);
            D3D12CommandSignature() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12CommandSignature.</returns>
            virtual Guid GetGuid() override;
        };
    }
}