#pragma once

#include "../../pch.h"
#include "D3D12InfoQueue.h"
#include "../../Common/Result.h"
#include "D3D12DebugStructs.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

namespace DirectXNet
{
    namespace DirectX12
    {
        namespace Debug
        {
            /// <summary>
            /// This class supports message callback.
            /// </summary>
            public ref class D3D12InfoQueue1 : D3D12InfoQueue
            {
            private:
                ::ID3D12InfoQueue1* pQueue1;

                Dictionary<DWORD, D3D12MessageCallback^>^ callbacks = gcnew Dictionary<DWORD, D3D12MessageCallback^>();;

            internal:
                D3D12InfoQueue1(::ID3D12InfoQueue1* pQueue1);
                D3D12InfoQueue1() : D3D12InfoQueue() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12InfoQueue1.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Registers a callback that is called at the time a debug message
                /// is produced.
                /// </summary>
                /// <param name="callbackFunc">A callback function pointer which allows users to register
                /// a callback that is called at the time a debug message is produced.</param>
                /// <param name="callbackFilterFlags">If this value is set to IgnoreFilters, current callback
                /// is unfiltered. If this value is set to None, current callback is filtered in the exact
                /// same way as what gets logged as debug text.</param>
                /// <param name="pContext">Can be set to point to anything users want. They can access
                /// pContext they specified here in D3D12MessageCallback. This allows users to attach their
                /// own additional data to the callback.</param>
                /// <param name="callbackCookie">An output parameter that uniquely identifies the registered
                /// callback, the value pointed to by callbackCookie is set to zero if the callback
                /// registration fails.</param>
                /// <returns>Result code.</returns>
                Result RegisterMessageCallback(
                    D3D12MessageCallback^ callbackFunc,
                    D3D12MessageCallbackFlags callbackFilterFlags,
                    void* pContext,
                    DWORD% callbackCookie
                );

                /// <summary>
                /// Unregisters a previously registered callback.
                /// </summary>
                /// <param name="callbackCookie">The cookie that identifies the callback to unregister.
                /// </param>
                /// <returns>Result code.</returns>
                Result UnregisterMessageCallback(DWORD callbackCookie);
            };
        }
    }
}
