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
        /// <summary>
        /// Populates an D2D1Mesh object with triangles.
        /// </summary>
        public ref class D2D1TessellationSink : Common::Unknown
        {
        private:
            ::ID2D1TessellationSink* pSink;

        internal:
            D2D1TessellationSink(::ID2D1TessellationSink* pSink);
            D2D1TessellationSink() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID2D1TessellationSink.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Copies the specified triangles to the sink.
            /// </summary>
            /// <param name="triangles">An array of D2D1Triangle structures that describe the triangles to
            /// add to the sink.</param>
            void AddTriangled(...array<D2D1Triangle>^ triangles);

            /// <summary>
            /// Closes the sink and returns its error status.
            /// </summary>
            /// <returns>Result code.</returns>
            Result Close();
        };
    }
}
