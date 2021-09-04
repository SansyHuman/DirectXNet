#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DirectXNet
{
    namespace Common
    {
        ref class D3D10Blob;

        /// <summary>
        /// Class that contains functions in d3dcompiler.h
        /// </summary>
        public ref class D3DCompiler abstract sealed
        {
        public:
            /// <summary>
            /// Creates a buffer.
            /// </summary>
            /// <param name="size">Number of bytes in the blob.</param>
            /// <returns>Created buffer if succeeded.</returns>
            static D3D10Blob^ CreateBlob(SIZE_T size);
        };
    }
}