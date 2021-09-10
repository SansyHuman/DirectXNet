#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"
#include "DXGIDebugStructs.h"

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
        namespace Debug
        {
            /// <summary>
            /// This class controls debug settings, and can only be used if the debug layer is turned on.
            /// </summary>
            public ref class DXGIDebug : Common::Unknown
            {
            private:
                ::IDXGIDebug* pDebug;

            internal:
                DXGIDebug(::IDXGIDebug* pDebug);
                DXGIDebug() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of IDXGIDebug.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Reports info about the lifetime of an object or objects.
                /// </summary>
                /// <param name="apiid">The globally unique identifier (GUID) of the object or objects to
                /// get info about. Use one of the DXGIDebugID GUIDs.</param>
                /// <param name="flags">A DXGIDebugRLOFlags-typed value that specifies the amount of info
                /// to report.</param>
                /// <returns>Result code.</returns>
                Result ReportLiveObjects(Guid apiid, DXGIDebugRLOFlags flags);
            };
        }
    }
}