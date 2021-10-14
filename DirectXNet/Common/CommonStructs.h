#pragma once

#include "../pch.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace DirectXNet
{
    namespace Common
    {
        /// <summary>
        /// Same to BOOL type in C.
        /// </summary>
        public enum class CBool : BOOL
        {
            True = TRUE,
            False = FALSE
        };

        /// <summary>
        /// Defines generic access rights.
        /// </summary>
        [Flags]
        public enum class AccessRights : DWORD
        {
            GenericRead = GENERIC_READ,
            GenericWrite = GENERIC_WRITE,
            GenericExecute = GENERIC_EXECUTE,
            GenericAll = GENERIC_ALL
        };



        /// <summary>
        /// Same to LUID structure in C.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct Luid
        {
            DWORD LowPart;
            LONG HighPart;

            static operator long long(Luid value);
            static operator unsigned long long(Luid value);
            static operator Luid(long long value);
            static operator Luid(unsigned long long value);
        };
        
        /// <summary>
        /// Same to RECT structure in C.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct Rect
        {
            /// <summary>
            /// Specifies the x-coordinate of the upper-left corner of the rectangle.
            /// </summary>
            LONG    left;

            /// <summary>
            /// Specifies the y-coordinate of the upper-left corner of the rectangle.
            /// </summary>
            LONG    top;

            /// <summary>
            /// Specifies the x-coordinate of the lower-right corner of the rectangle.
            /// </summary>
            LONG    right;

            /// <summary>
            /// Specifies the y-coordinate of the lower-right corner of the rectangle.
            /// </summary>
            LONG    bottom;
        };

        /// <summary>
        /// Same to POINT structure in C.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct Point
        {
            /// <summary>
            /// Specifies the x-coordinate of the point
            /// </summary>
            LONG x;

            /// <summary>
            /// Specifies the y-coordinate of the point
            /// </summary>
            LONG y;
        };

        /// <summary>
        /// Same to SECURITY_ATTRIBUTES in C.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct SecurityAttributes
        {
            /// <summary>
            /// The size, in bytes, of this structure.
            /// </summary>
            DWORD nLength;

            /// <summary>
            /// A pointer to a SECURITY_DESCRIPTOR structure that controls access to the object.
            /// In .NET, use RawSecurityDescriptor or derived classes of ObjectSecurity and allocate
            /// memory for the descriptor in this pointer with Marshal.AllocHGlobal.
            /// </summary>
            IntPtr lpSecurityDescriptor;

            /// <summary>
            /// A Boolean value that specifies whether the returned handle is inherited when a new
            /// process is created. If this member is True, the new process inherits the handle.
            /// </summary>
            CBool bInheritHandle;
        };
    }
}