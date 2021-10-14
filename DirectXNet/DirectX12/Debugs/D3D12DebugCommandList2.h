#pragma once

#include "../../pch.h"
#include "D3D12DebugCommandList.h"
#include "../../Common/Result.h"
#include "D3D12DebugStructs.h"

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
        namespace Debug
        {
            /// <summary>
            /// This interface enables modification of additional command list debug layer settings.
            /// </summary>
            public ref class D3D12DebugCommandList2 : D3D12DebugCommandList
            {
            private:
                ::ID3D12DebugCommandList2* pList2;

            internal:
                D3D12DebugCommandList2(::ID3D12DebugCommandList2* pList2);
                D3D12DebugCommandList2() : D3D12DebugCommandList() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12DebugCommandList2.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Modifies optional Debug Layer settings of a command list.
                /// </summary>
                /// <typeparam name="T">Type of the debug parameter.</typeparam>
                /// <param name="type">Specifies a D3D12DebugCommandListParameterType value that indicates
                /// which debug parameter data to set.</param>
                /// <param name="data">Debug parameter data to set. The interpretation of this data depends
                /// on the D3D12DebugCommandListParameterType given in the type parameter.</param>
                /// <returns>Result code.</returns>
                generic<typename T> where T : ICommandListDebugParameter, value class
                    Result SetDebugParameter(
                        D3D12DebugCommandListParameterType type,
                        [In][IsReadOnly] T% data
                    );

                /// <summary>
                /// Gets optional Command List Debug Layer settings.
                /// </summary>
                /// <typeparam name="T">Type of the debug parameter.</typeparam>
                /// <param name="type">Specifies a D3D12DebugCommandListParameterType value that
                /// determines which debug parameter data to copy to the memory pointed to by data.</param>
                /// <param name="data">Reference to the memory that will be filled with a copy of the debug
                /// parameter data. The interpretation of this data depends on the
                /// D3D12DebugCommandListParameterType given in the type parameter.</param>
                /// <returns>Result code.</returns>
                generic<typename T> where T : ICommandListDebugParameter, value class
                    Result GetDebugParameter(
                        D3D12DebugCommandListParameterType type,
                        [Out] T% data
                    );
            };
        }
    }
}