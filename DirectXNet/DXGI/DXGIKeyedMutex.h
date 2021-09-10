#pragma once

#include "../pch.h"
#include "DXGIDeviceSubObject.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        /// <summary>
        /// Represents a keyed mutex, which allows exclusive access to a shared resource that is used
        /// by multiple devices.
        /// </summary>
        public ref class DXGIKeyedMutex : DXGIDeviceSubObject
        {
        private:
            ::IDXGIKeyedMutex* pMutex;

        internal:
            DXGIKeyedMutex(::IDXGIKeyedMutex* pMutex);
            DXGIKeyedMutex() : DXGIDeviceSubObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIKeyedMutex.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Using a key, acquires exclusive rendering access to a shared resource.
            /// </summary>
            /// <param name="key">A value that indicates which device to give access to. This method
            /// will succeed when the device that currently owns the surface calls the 
            /// DXGIKeyedMutex::ReleaseSync method using the same value. This value can be any
            /// UInt64 value.</param>
            /// <param name="milliseconds">The time-out interval, in milliseconds. This method will return
            /// if the interval elapses, and the keyed mutex has not been released using the specified Key.
            /// If this value is set to zero, the AcquireSync method will test to see if the keyed mutex
            /// has been released and returns immediately. If this value is set to UInt32::MaxValue, the
            /// time-out interval will never elapse.</param>
            /// <returns>Result code.</returns>
            Result AcquireSync(unsigned long long key, unsigned long milliseconds);

            /// <summary>
            /// Using a key, releases exclusive rendering access to a shared resource.
            /// </summary>
            /// <param name="key">A value that indicates which device to give access to. This method
            /// succeeds when the device that currently owns the surface calls the ReleaseSync method
            /// using the same value. This value can be any UInt64 value.</param>
            /// <returns></returns>
            Result ReleaseSync(unsigned long long key);
        };
    }
}