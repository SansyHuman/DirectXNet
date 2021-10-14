#pragma once

#include "../pch.h"
#include "../Common/CommonStructs.h"
#include "../Common/CommonD2DStructs.h"
#include "../Common/Unknown.h"
#include "D2D1Structs.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common::D2D;
using namespace DirectXNet::Common;

// Done.

namespace DirectXNet
{
    namespace Direct2D
    {
        ref class D2D1Factory;

        /// <summary>
        /// Represents a Direct2D drawing resource.
        /// </summary>
        public ref class D2D1Resource : Common::Unknown
        {
        private:
            ::ID2D1Resource* pResource;

        internal:
            D2D1Resource(::ID2D1Resource* pResource);
            D2D1Resource() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1Resource.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Retrieves the factory associated with this resource.
            /// </summary>
            property D2D1Factory^ Factory
            {
                D2D1Factory^ get();
            }
        };
    }
}
