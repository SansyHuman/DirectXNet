#pragma once

#include "../pch.h"
#include "../Common/Unknown.h"
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
        /// A class from which D3D12Device and D3D12DeviceChild inherit from. It provides methods to
        /// associate private data and annotate object names.
        /// </summary>
        public ref class D3D12Object : Common::Unknown
        {
        private:
            ::ID3D12Object* pD3D12Obj;

        internal:
            D3D12Object(::ID3D12Object* pD3D12Obj);
            D3D12Object() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Object.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets and sets a name with the device object. This name is for use in debug diagnostics
            /// and tools.
            /// </summary>
            property String^ Name
            {
                String^ get();
                void set(String^ name);
            }
        };
    }
}