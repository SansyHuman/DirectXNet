#pragma once

#include "../pch.h"
#include "DXGIDeviceSubObject.h"
#include "DXGIStructs.h"

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
        /// A DXGIResource interface allows resource sharing and identifies the memory that a resource
        /// resides in.
        /// </summary>
        public ref class DXGIResource : DXGIDeviceSubObject
        {
        private:
            com::ptr<::IDXGIResource> pResource;

        public:
            literal unsigned int ResourcePriorityMinimum = DXGI_RESOURCE_PRIORITY_MINIMUM;
            literal unsigned int ResourcePriorityLow = DXGI_RESOURCE_PRIORITY_LOW;
            literal unsigned int ResourcePriorityNormal = DXGI_RESOURCE_PRIORITY_NORMAL;
            literal unsigned int ResourcePriorityHigh = DXGI_RESOURCE_PRIORITY_HIGH;
            literal unsigned int ResourcePriorityMaximum = DXGI_RESOURCE_PRIORITY_MAXIMUM;

        internal:
            DXGIResource(::IDXGIResource* pResource);
            DXGIResource() : DXGIDeviceSubObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIResource.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the handle to a shared resource.
            /// </summary>
            property IntPtr SharedHandle
            {
                IntPtr get();
            }

            /// <summary>
            /// Get the expected resource usage.
            /// </summary>
            property DXGIUsage Usage
            {
                DXGIUsage get();
            }

            /// <summary>
            /// Gets and sets the eviction priority.
            /// </summary>
            property unsigned int EvictionPriority
            {
                unsigned int get();
                void set(unsigned int priority);
            }
        };
    }
}