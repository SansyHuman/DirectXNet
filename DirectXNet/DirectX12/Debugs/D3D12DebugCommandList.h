#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"
#include "D3D12DebugStructs.h"
#include "../D3D12Structs.h"

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
        ref class D3D12Resource;

        namespace Debug
        {
            /// <summary>
            /// Provides methods to monitor and debug a command list.
            /// </summary>
            public ref class D3D12DebugCommandList : Common::Unknown
            {
            private:
                ::ID3D12DebugCommandList* pList;

            internal:
                D3D12DebugCommandList(::ID3D12DebugCommandList* pList);
                D3D12DebugCommandList() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12DebugCommandList.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Checks whether a resource, or subresource, is in a specified state, or not.
                /// </summary>
                /// <param name="resource">Specifies the D3D12Resource to check.</param>
                /// <param name="subresource">The index of the subresource to check. This can be set to an
                /// index, or D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES(0xffffffff).</param>
                /// <param name="state">Specifies the state to check for. This can be one or more
                /// D3D12ResourceStates flags Or'ed together.</param>
                /// <returns>This method returns true if the resource or subresource is in the specified
                /// state, false otherwise.</returns>
                bool AssertResourceState(
                    D3D12Resource^ resource,
                    unsigned int subresource,
                    D3D12ResourceStates state
                );

                /// <summary>
                /// Gets or sets the debug feature flags that have been set on a command list.
                /// </summary>
                property D3D12DebugFeature FeatureMask
                {
                    D3D12DebugFeature get();
                    void set(D3D12DebugFeature mask);
                }
            };
        }
    }
}