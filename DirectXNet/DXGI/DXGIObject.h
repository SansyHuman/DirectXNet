#pragma once

#include "../pch.h"
#include "../Common/Unknown.h"

using namespace System;
using namespace msclr;

// Done

namespace DirectXNet
{
    namespace DXGI
    {
        /// <summary>
        /// An DXGIObject class is a base class for all DXGI objects; DXGIObject supports associating
        /// caller-defined (private data) with an object and retrieval of an interface to the parent object.
        /// </summary>
        public ref class DXGIObject : Common::Unknown
        {
        private:
            com::ptr<::IDXGIObject> pDxgiObj;

        internal:
            DXGIObject(::IDXGIObject* pObj);
            DXGIObject() : Common::Unknown() {}

        internal:
            virtual void AttatchComObj(::IUnknown* pComObj) override;

        public:
            /// <summary>
            /// Gets GUID of the interface.
			/// Override it to returns GUID of the interface.
            /// </summary>
            /// <returns>GUID of IDXGIObject.</returns>
            virtual Guid GetGuid() override;

            /// <summary>
            /// Gets the parent of the object.
            /// </summary>
            /// <typeparam name="T">Type of parent.</typeparam>
            /// <returns>Parent object if succeeded.</returns>
            /// <exception cref="System::Runtime::InteropServices::COMException">Thrown when failed.</exception>
            generic <typename T> where T : Common::Unknown
                T GetParent();

            /// <summary>
            /// Gets and sets object's name used in debug layer.
            /// </summary>
            property String^ DebugObjectName
            {
                String^ get();
                void set(String^ name);
            }
        };
    }
}
