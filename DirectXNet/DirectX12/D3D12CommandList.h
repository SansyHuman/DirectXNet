#pragma once

#include "../pch.h"
#include "D3D12DeviceChild.h"
#include "../Common/Result.h"
#include "D3D12Structs.h"

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
        /// <summary>
        /// A class from which D3D12GraphicsCommandList inherits. It represents an ordered set of
        /// commands that the GPU executes, while allowing for extension to support other command
        /// lists than just those for graphics (such as compute and copy).
        /// </summary>
        public ref class D3D12CommandList : D3D12DeviceChild
        {
        private:
            com::ptr<::ID3D12CommandList> pList;

        internal:
            D3D12CommandList(::ID3D12CommandList* pList);
            D3D12CommandList() : D3D12DeviceChild() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12CommandList.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the type of the command list, such as direct, bundle, compute, or copy.
            /// </summary>
            property D3D12CommandListType Type
            {
                D3D12CommandListType get();
            }
        };
    }
}