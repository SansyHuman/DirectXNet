#pragma once

#include "../pch.h"
#include "D3D12DeviceChild.h"
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
        /// The root signature defines what resources are bound to the graphics pipeline.
        /// A root signature is configured by the app and links command lists to the resources
        /// the shaders require. Currently, there is one graphics and one compute root signature per
        /// app.
        /// </summary>
        public ref class D3D12RootSignature : D3D12DeviceChild
        {
        internal:
            D3D12RootSignature(::ID3D12RootSignature* pSignature);
            D3D12RootSignature() : D3D12DeviceChild() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12RootSignature.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the native root signature pointer. This does not increase the reference count of the
            /// root signature. Do not use this other than filling some structs.
            /// </summary>
            property IntPtr NativeRootSignature
            {
                IntPtr get();
            }
        };
    }
}