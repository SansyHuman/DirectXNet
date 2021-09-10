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
        /// The fence value when the event is to be signaled.
        /// </summary>
        public ref class D3D12Fence : D3D12Pageable
        {
        private:
            ::ID3D12Fence* pFence;

        internal:
            D3D12Fence(::ID3D12Fence* pFence);
            D3D12Fence() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Fence.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the current value of the fence.
            /// </summary>
            property unsigned long long CompletedValue
            {
                unsigned long long get();
            }

            /// <summary>
            /// Specifies an event that should be fired when the fence reaches a certain value.
            /// </summary>
            /// <param name="value">The fence value when the event is to be signaled.</param>
            /// <param name="hEvent">A handle to the event object.</param>
            /// <returns></returns>
            Result SetEventOnCompletion(unsigned long long value, IntPtr hEvent);

            /// <summary>
            /// Sets the fence to the specified value.
            /// </summary>
            /// <param name="value">The value to set the fence to.</param>
            /// <returns>Result code.</returns>
            Result Signal(unsigned long long value);
        };
    }
}