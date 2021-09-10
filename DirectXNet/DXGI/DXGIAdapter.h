#pragma once

#include "../pch.h"
#include "DXGIObject.h"
#include "DXGIStructs.h"
#include "../Common/Result.h"

using namespace System;
using namespace msclr;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        ref class DXGIOutput;

        /// <summary>
        /// The DXGIAdapter class represents a display subsystem (including one or more GPUs, DACs and
        /// video memory).
        /// </summary>
        public ref class DXGIAdapter : DXGIObject
        {
        private:
            ::IDXGIAdapter* pAdapter;

        internal:
            DXGIAdapter(::IDXGIAdapter* pAdapter);
            DXGIAdapter() : DXGIObject() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIAdapter.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Enumerate adapter (video card) outputs.
            /// </summary>
            /// <param name="index">The index of the output.</param>
            /// <param name="output">The reference to an DXGIOutput at the position specified by the index
            /// parameter.</param>
            /// <returns>A code that indicates success or failure. DXGI_ERROR_NOT_FOUND is returned if the index
            /// is greater than the number of outputs.</returns>
            Common::Result EnumOutputs(
                unsigned int index,
                [Out] DXGIOutput^% output
            );

            /// <summary>
            /// Gets a DXGI 1.0 description of an adapter (or video card).
            /// </summary>
            property DXGIAdapterDesc AdapterDesc
            {
                DXGIAdapterDesc get();
            }

            // CheckInterfaceSupport is deprecated.
        };
    }
}