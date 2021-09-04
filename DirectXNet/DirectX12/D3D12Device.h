#pragma once

#include "../pch.h"
#include "D3D12Object.h"
#include "../Common/Result.h"
#include "D3D12Structs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

namespace DirectXNet
{
    namespace DirectX12
    {
        ref class D3D12CommandQueue;

        /// <summary>
        /// Represents a virtual adapter; it is used to create command allocators, command lists,
        /// command queues, fences, resources, pipeline state objects, heaps, root signatures, samplers,
        /// and many resource views.
        /// </summary>
        public ref class D3D12Device : D3D12Object
        {
        private:
            com::ptr<::ID3D12Device> pDevice;

        internal:
            D3D12Device(::ID3D12Device* pDevice);
            D3D12Device() : D3D12Object() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
            /// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of ID3D12Device.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the number of physical adapters (nodes) that are associated with this device.
            /// </summary>
            property unsigned int NodeCount
            {
                unsigned int get();
            }

            /// <summary>
            /// Creates a command queue.
            /// </summary>
            /// <typeparam name="T">Type of the command queue.</typeparam>
            /// <param name="desc">Specifies a D3D12CommandQueueDesc that describes the command queue.
            /// </param>
            /// <returns>Command queue if succeeded.</returns>
            generic <typename T> where T : D3D12CommandQueue
            T CreateCommandQueue(
                [In][IsReadOnly] D3D12CommandQueueDesc% desc
            );

            /// <summary>
            /// Gets information about the features that are supported by the current graphics driver.
            /// </summary>
            /// <typeparam name="T">Structs that contain feature data.</typeparam>
            /// <param name="feature">A constant from the D3D12Feature enumeration describing the
            /// feature(s) that you want to query for support.</param>
            /// <param name="featureSupportData">A reference to a data structure that corresponds to
            /// the value of the Feature parameter.</param>
            /// <returns></returns>
            generic <typename T> where T : value class, ID3D12FeatureData
            Result CheckFeatureSupport(D3D12Feature feature, T% featureSupportData);

            /// <summary>
            /// Gets the size of the handle increment for the given type of descriptor heap. This
            /// value is typically used to increment a handle into a descriptor array by the
            /// correct amount.
            /// </summary>
            /// <param name="type">The D3D12DescriptorHeapType-typed value that specifies the type
            /// of descriptor heap to get the size of the handle increment for.</param>
            /// <returns>The descriptor size.</returns>
            unsigned int GetDescriptorHandleIncrementSize(D3D12DescriptorHeapType type);

            /// <summary>
            /// Creates a constant-buffer view for accessing resource data.
            /// </summary>
            /// <param name="desc">A D3D12ConstantBufferViewDesc structure that describes the
            /// constant-buffer view.</param>
            /// <param name="destDescriptor">Describes the CPU descriptor handle that represents
            /// the start of the heap that holds the constant-buffer view.</param>
            void CreateConstantBufferView(
                D3D12ConstantBufferViewDesc desc,
                D3D12CPUDescriptorHandle destDescriptor
            );

            /// <summary>
            /// Gets the reason that the device was removed.
            /// </summary>
            /// <returns>This method returns the reason that the device was removed.</returns>
            Result GetDeviceRemovedReason();

            /// <summary>
            /// A development-time aid for certain types of profiling and experimental prototyping.
            /// </summary>
            /// <param name="enable">Specifies a bool that turns the stable power state on or off.
            /// </param>
            /// <returns>Result code.</returns>
            [Obsolete("Do not call this method in normal execution for a shipped application. This method only works while the machine is in developer mode.")]
            Result SetStablePowerState(bool enable);

            /// <summary>
            /// Gets a locally unique identifier for the current device (adapter).
            /// </summary>
            property Luid AdapterLuid
            {
                Luid get();
            }
        };
    }
}