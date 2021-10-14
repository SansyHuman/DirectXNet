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
        ref class D3D12Resource;
        ref class D3D12Fence;

        namespace Debug
        {
            /// <summary>
            /// Part of a contract between D3D11On12 diagnostic layers and graphics diagnostics tools.
            /// This interface facilitates diagnostics tools to capture information at a lower level than
            /// the DXGI swapchain.
            /// </summary>
            public ref class D3D12SharingContract : Common::Unknown
            {
            private:
                ::ID3D12SharingContract* pContract;

            internal:
                D3D12SharingContract(::ID3D12SharingContract* pContract);
                D3D12SharingContract() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12SharingContract.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Notifies diagnostic tools about an end-of-frame operation without the use of a swap
                /// chain. Calling this API enables usage of tools like PIX with applications that either
                /// don't render to a window, or that do so in non-traditional ways.
                /// </summary>
                /// <param name="resource">A resource that contains the final frame contents. This resource
                /// is treated as the back buffer of the Present.</param>
                /// <param name="subresource">An unsigned 32bit subresource id.</param>
                /// <param name="window">If provided, indicates which window the tools should use for
                /// displaying additional diagnostic information.</param>
                void Present(
                    D3D12Resource^ resource,
                    unsigned int subresource,
                    IntPtr window
                );

                /// <summary>
                /// Signals a shared fence between the D3D layers and diagnostics tools.
                /// </summary>
                /// <param name="fence">A shared fence to signal.</param>
                /// <param name="fenceValue">An unsigned 64bit value to signal the shared fence with.</param>
                void SharedFenceSignal(
                    D3D12Fence^ fence,
                    unsigned long long fenceValue
                );
            };
        }
    }
}
