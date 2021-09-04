#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DirectXNet
{
    namespace Common
    {
        ref class Unknown;
    }

    namespace DXGI
    {
        ref class DXGIFactory;

        using fPtr = HRESULT(__stdcall*)(const IID&, void**);

        /// <summary>
        /// Class containing DXGI functions.
        /// </summary>
        public ref class DXGI abstract sealed
        {
        private:
            static DXGI();

        public:
            /// <summary>
            /// Creates a DXGI 1.0 factory that you can use to generate other DXGI objects.
            /// </summary>
            /// <typeparam name="T">Type of the factory.</typeparam>
            /// <returns>Factory if succedded.</returns>
            generic <typename T> where T : DXGIFactory
            static T CreateDXGIFactory();

            /// <summary>
            /// Creates a DXGI 1.1 factory that you can use to generate other DXGI objects.
            /// </summary>
            /// <typeparam name="T">Type of the factory.</typeparam>
            /// <returns>Factory if succeeded.</returns>
            generic <typename T> where T : DXGIFactory
            static T CreateDXGIFactory1();

            ref class Debug abstract sealed
            {
            private:
                static initonly HMODULE debugDLL;
                static initonly fPtr DXGIGetDebugInterface;

            private:
                static Debug();

            public:
                /// <summary>
                /// Retrieves a debugging interface.
                /// </summary>
                /// <typeparam name="T">Debug interface type such as DXGIDebug or DXGIInfoQueue.</typeparam>
                /// <returns>Debug interface if succeeded.</returns>
                generic <typename T> where T : Common::Unknown
                static T GetDebugInterface();
            };
        };
    }
}