#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Microsoft::Win32::SafeHandles;

namespace DirectXNet
{
    namespace Common
    {
        /// <summary>
        /// Wrapper of shared resource handle.
        /// </summary>
        public ref class DXResourceHandle : SafeHandleZeroOrMinusOneIsInvalid
        {
        private:
            DXResourceHandle() : SafeHandleZeroOrMinusOneIsInvalid(true) {}
        
        internal:
            DXResourceHandle(IntPtr handle);

            property HANDLE NativeHandle
            {
                HANDLE get();
            }

        protected:
            virtual bool ReleaseHandle() override;
        };
    }
}