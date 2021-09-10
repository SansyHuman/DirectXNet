#pragma once

#include "../pch.h"
#include "D3D12Pageable.h"
#include "../Common/Result.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace Common
    {
        ref class D3D10Blob;
    }

    namespace DirectX12
    {
        /// <summary>
        /// Represents the state of all currently set shaders as well as certain fixed function
        /// state objects.
        /// </summary>
        public ref class D3D12PipelineState : D3D12Pageable
        {
        private:
            ::ID3D12PipelineState* pState;

        internal:
            D3D12PipelineState(::ID3D12PipelineState* pState);
            D3D12PipelineState() : D3D12Pageable() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12PipelineState.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the cached blob representing the pipeline state.
            /// </summary>
            property D3D10Blob^ CachedBlob
            {
                D3D10Blob^ get();
            }
        };
    }
}