#pragma once

#include "../../pch.h"


using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace msclr;

namespace DirectXNet
{
    namespace DXGI
    {
        namespace Debug
        {
            value struct DXGIInfoQueueFilter;
            value struct DXGIInfoQueueFilterDesc;
            value struct DXGIInfoQueueMessage;

            /// <summary>
            /// Flags used with ReportLiveObjects to specify the amount of info to report about an
            /// object's lifetime.
            /// </summary>
            [Flags]
            public enum class DXGIDebugRLOFlags : UINT
            {
                /// <summary>
                /// A flag that specifies to obtain a summary about an object's lifetime.
                /// </summary>
                Summary = ::DXGI_DEBUG_RLO_SUMMARY,

                /// <summary>
                /// A flag that specifies to obtain detailed info about an object's lifetime.
                /// </summary>
                Detail = ::DXGI_DEBUG_RLO_DETAIL,

                /// <summary>
                /// This flag indicates to ignore objects which have no external refcounts keeping them alive.
                /// D3D objects are printed using an external refcountand an internal refcount.
                /// Typically, all objects are printed.
                /// This flag means ignore the objects whose external refcount is 0, because the
                /// application is not responsible for keeping them alive.
                /// </summary>
                IgnoreInternal = ::DXGI_DEBUG_RLO_IGNORE_INTERNAL,

                /// <summary>
                /// A flag that specifies to obtain both a summary and detailed info about an
                /// object's lifetime.
                /// </summary>
                All = ::DXGI_DEBUG_RLO_ALL
            };

            /// <summary>
            /// Values that specify categories of debug messages.
            /// </summary>
            public enum class DXGIInfoQueueMessageCategory : UINT
            {
                /// <summary>
                /// Unknown category.
                /// </summary>
                Unknown = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN,

                /// <summary>
                /// Miscellaneous category.
                /// </summary>
                Miscellaneous = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS,

                /// <summary>
                /// Initialization category.
                /// </summary>
                Initialization = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION,

                /// <summary>
                /// Cleanup category.
                /// </summary>
                Cleanup = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP,

                /// <summary>
                /// Compilation category.
                /// </summary>
                Compilation = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION,

                /// <summary>
                /// State creation category.
                /// </summary>
                StateCreation = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION,

                /// <summary>
                /// State setting category.
                /// </summary>
                StateSetting = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING,

                /// <summary>
                /// State getting category.
                /// </summary>
                StateGetting = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING,

                /// <summary>
                /// Resource manipulation category.
                /// </summary>
                ResourceManipulation = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION,

                /// <summary>
                /// Execution category.
                /// </summary>
                Execution = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION,

                /// <summary>
                /// Shader category.
                /// </summary>
                Shader = ::DXGI_INFO_QUEUE_MESSAGE_CATEGORY_SHADER
            };

            /// <summary>
            /// Values that specify debug message severity levels for an information queue.
            /// </summary>
            public enum class DXGIInfoQueueMessageSeverity : UINT
            {
                /// <summary>
                /// Defines some type of corruption that has occurred.
                /// </summary>
                Corruption = ::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION,

                /// <summary>
                /// Defines an error message.
                /// </summary>
                Error = ::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR,

                /// <summary>
                /// Defines a warning message.
                /// </summary>
                Warning = ::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING,

                /// <summary>
                /// Defines an information message.
                /// </summary>
                Info = ::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO,

                /// <summary>
                /// Defines a message other than corruption, error, warning, or information.
                /// </summary>
                Message = ::DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE
            };


            /// <summary>
            /// Globally unique identifier (GUID) values that identify producers of debug messages.
            /// </summary>
            public ref struct DXGIDebugID abstract sealed
            {
                /// <summary>
                /// All Direct3D and DXGI objects and private apps.
                /// </summary>
                static initonly Guid All;

                /// <summary>
                /// Direct3D and DXGI objects.
                /// </summary>
                static initonly Guid DX;

                /// <summary>
                /// DXGI.
                /// </summary>
                static initonly Guid DXGI;

                /// <summary>
                /// Private apps. Any messages that you add with DXGIInfoQueue::AddApplicationMessage.
                /// </summary>
                static initonly Guid APP;

                /// <summary>
                /// Direct3D 12.
                /// </summary>
                static initonly Guid D3D12;

            private:
                static DXGIDebugID();
            };

            /// <summary>
            /// Describes the types of messages to allow or deny to pass through a filter.
            /// </summary>
            public value struct DXGIInfoQueueFilterDesc
            {
                /// <summary>
                /// An array of DXGIInfoQueueMessageCategory enumeration values that describe the
                /// message categories to allow or deny.
                /// </summary>
                array<DXGIInfoQueueMessageCategory>^ CategoryList;

                /// <summary>
                /// An array of DXGIInfoQueueMessageSeverity enumeration values that describe the
                /// message severity levels to allow or deny.
                /// </summary>
                array<DXGIInfoQueueMessageSeverity>^ SeverityList;

                /// <summary>
                /// An array of integers that represent the message IDs to allow or deny.
                /// </summary>
                array<int>^ IDList;
            };

            /// <summary>
            /// Describes a debug message filter, which contains lists of message types to allow and deny.
            /// </summary>
            public value struct DXGIInfoQueueFilter
            {
                /// <summary>
                /// A DXGIInfoQueueFilterDesc structure that describes the types of messages to allow.
                /// </summary>
                DXGIInfoQueueFilterDesc AllowList;

                /// <summary>
                /// A DXGIInfoQueueFilterDesc structure that describes the types of messages to deny.
                /// </summary>
                DXGIInfoQueueFilterDesc DenyList;
            };

            /// <summary>
            /// Describes a debug message in the information queue.
            /// </summary>
            public value struct DXGIInfoQueueMessage
            {
                /// <summary>
                /// A DXGIDebugID value that identifies the entity that produced the message.
                /// </summary>
                Guid Producer;

                /// <summary>
                /// A DXGIInfoQueueMessageCategory-typed value that specifies the category of the message.
                /// </summary>
                DXGIInfoQueueMessageCategory Category;

                /// <summary>
                /// A DXGIInfoQueueMessageSeverity-typed value that specifies the severity of the message.
                /// </summary>
                DXGIInfoQueueMessageSeverity Severity;

                /// <summary>
                /// An integer that uniquely identifies the message.
                /// </summary>
                int ID;

                /// <summary>
                /// The message string.
                /// </summary>
                String^ Description;
            };
        }
    }
}