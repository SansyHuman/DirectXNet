#pragma once

#include "../pch.h"
#include "DXGIObject.h"

using namespace System;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGIDevice;

        /// <summary>
        /// Inherited from objects that are tied to the device so that they can retrieve a pointer to it.
        /// </summary>
        public ref class DXGIDeviceSubObject : DXGIObject
        {
        private:
            ::IDXGIDeviceSubObject* pSubObj;

        internal:
            DXGIDeviceSubObject(::IDXGIDeviceSubObject* pSubObj);
            DXGIDeviceSubObject() : DXGIObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIDeviceSubObject.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the device.
            /// </summary>
            /// <typeparam name="T">The type of device object.</typeparam>
            /// <returns>Device if succeeded.</returns>
            generic <typename T> where T : Common::Unknown
            T GetDevice();
        };
    }
}