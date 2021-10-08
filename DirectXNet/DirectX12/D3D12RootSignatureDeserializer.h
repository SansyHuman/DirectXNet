#pragma once

#include "../pch.h"
#include "../Common/Unknown.h"
#include "../Common/Result.h"
#include "../Common/CommonStructs.h"
#include "D3D12Structs.h"

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
        /// Contains a method to return the deserialized D3D12RootSignatureDesc data structure, of a
        /// serialized root signature version 1.0.
        /// </summary>
        public ref class D3D12RootSignatureDeserializer : Common::Unknown
        {
        private:
            ::ID3D12RootSignatureDeserializer* pDeserializer;

        internal:
            D3D12RootSignatureDeserializer(::ID3D12RootSignatureDeserializer* pDeserializer);
            D3D12RootSignatureDeserializer() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12RootSignatureDeserializer.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the layout of the root signature.
            /// </summary>
            property D3D12RootSignatureDesc RootSignatureDesc
            {
                D3D12RootSignatureDesc get();
            }
        };
    }
}