#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"
#include "D3D12DebugStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

namespace DirectXNet
{
    namespace DirectX12
    {
        namespace Debug
        {
            /// <summary>
            /// This class controls the debug information queue, and can only be used if the debug layer
            /// is turned on.
            /// </summary>
            public ref class D3D12InfoQueue : Common::Unknown
            {
            private:
                ::ID3D12InfoQueue* pQueue;

            internal:
                D3D12InfoQueue(::ID3D12InfoQueue* pQueue);
                D3D12InfoQueue() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of ID3D12InfoQueue.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Sets the maximum number of messages that can be added to the message queue.
                /// </summary>
                /// <param name="messageCountLimit">The maximum number of messages that can be added to
                /// the queue. -1 means no limit.</param>
                /// <returns>Result code.</returns>
                Result SetMessageCountLimit(unsigned long long messageCountLimit);

                /// <summary>
                /// Clears all messages from the message queue.
                /// </summary>
                void ClearStoredMessages();

                /// <summary>
                /// Gets a message from the message queue.
                /// </summary>
                /// <param name="messageIndex">An index into the message queue after an optional retrieval
                /// filter has been applied. This can be between 0 and the number of messages in the
                /// message queue that pass through the retrieval filter.
                /// Call DXGIInfoQueue::GetNumStoredMessagesAllowedByRetrievalFilters to obtain this number.
                /// 0 is the message at the beginning of the message queue.</param>
                /// <returns>Message if succeeded.</returns>
                D3D12Message GetMessage(unsigned long long messageIndex);

                /// <summary>
                /// Gets the number of messages that can pass through a retrieval filter.
                /// </summary>
                /// <returns>The number of messages that can pass through a retrieval filter.</returns>
                unsigned long long GetNumStoredMessagesAllowedByRetrievalFilter();

                /// <summary>
                /// Gets the number of messages currently stored in the message queue.
                /// </summary>
                /// <returns>The number of messages currently stored in the message queue.</returns>
                unsigned long long GetNumStoredMessages();

                /// <summary>
                /// Gets the number of messages that were discarded due to the message count limit.
                /// </summary>
                /// <returns>The number of messages that were discarded.</returns>
                unsigned long long GetNumMessagesDiscardedByMessageCountLimit();

                /// <summary>
                /// Gets the maximum number of messages that can be added to the message queue.
                /// </summary>
                /// <returns>The maximum number of messages that can be added to the queue.
                /// -1 means no limit.</returns>
                unsigned long long GetMessageCountLimit();

                /// <summary>
                /// Gets the number of messages that a storage filter allowed to pass through.
                /// </summary>
                /// <returns>The number of messages allowed by a storage filter.</returns>
                unsigned long long GetNumMessagesAllowedByStorageFilter();

                /// <summary>
                /// Gets the number of messages that were denied passage through a storage filter.
                /// </summary>
                /// <returns>The number of messages denied by a storage filter.</returns>
                unsigned long long GetNumMessagesDeniedByStorageFilter();

                /// <summary>
                /// Adds storage filters to the top of the storage-filter stack.
                /// </summary>
                /// <param name="filter">A D3D12InfoQueueFilter structure that describe the filters.</param>
                /// <returns></returns>
                Result AddStorageFilterEntries(
                    [In][IsReadOnly] D3D12InfoQueueFilter% filter
                );

                /// <summary>
                /// Gets the storage filter at the top of the storage-filter stack.
                /// </summary>
                /// <returns>Storage filter if succeeded.</returns>
                D3D12InfoQueueFilter GetStorageFilter();

                /// <summary>
                /// Removes a storage filter from the top of the storage-filter stack.
                /// </summary>
                void ClearStorageFilter();

                /// <summary>
                /// Pushes an empty storage filter onto the storage-filter stack.
                /// </summary>
                /// <returns>Result code.</returns>
                Result PushEmptyStorageFilter();

                /// <summary>
                /// Pushes a copy of the storage filter that is currently on the top of the
                /// storage-filter stack onto the storage-filter stack.
                /// </summary>
                /// <returns>Result code.</returns>
                Result PushCopyOfStorageFilter();

                /// <summary>
                /// Pushes a storage filter onto the storage-filter stack.
                /// </summary>
                /// <param name="filter">A D3D12InfoQueueFilter structure that describes the filter.</param>
                /// <returns>Result code.</returns>
                Result PushStorageFilter(
                    [In][IsReadOnly] D3D12InfoQueueFilter% filter
                );

                /// <summary>
                /// Pops a storage filter from the top of the storage-filter stack.
                /// </summary>
                void PopStorageFilter();

                /// <summary>
                /// Gets the size of the storage-filter stack in bytes.
                /// </summary>
                /// <returns>The size of the storage-filter stack in bytes.</returns>
                unsigned int GetStorageFilterStackSize();

                /// <summary>
                /// Adds retrieval filters to the top of the retrieval-filter stack.
                /// </summary>
                /// <param name="filter">An D3D12InfoQueueFilter structure that describe the filters.</param>
                /// <returns>Result code.</returns>
                Result AddRetrievalFilterEntries(
                    [In][IsReadOnly] D3D12InfoQueueFilter% filter
                );

                /// <summary>
                /// Gets the retrieval filter at the top of the retrieval-filter stack.
                /// </summary>
                /// <returns>Retrieval filter if succeeded.</returns>
                D3D12InfoQueueFilter GetRetrievalFilter();

                /// <summary>
                /// Removes a retrieval filter from the top of the retrieval-filter stack.
                /// </summary>
                void ClearRetrievalFilter();

                /// <summary>
                /// Pushes an empty retrieval filter onto the retrieval-filter stack.
                /// </summary>
                /// <returns>Result code.</returns>
                Result PushEmptyRetrievalFilter();

                /// <summary>
                /// Pushes a copy of the retrieval filter that is currently on the top of the
                /// retrieval-filter stack onto the retrieval-filter stack.
                /// </summary>
                /// <returns>Result code.</returns>
                Result PushCopyOfRetrievalFilter();

                /// <summary>
                /// Pushes a retrieval filter onto the retrieval-filter stack.
                /// </summary>
                /// <param name="filter">A D3D12InfoQueueFilter structure that describes the filter.</param>
                /// <returns>Result code.</returns>
                Result PushRetrievalFilter(
                    [In][IsReadOnly] D3D12InfoQueueFilter% filter
                );

                /// <summary>
                /// Pops a retrieval filter from the top of the retrieval-filter stack.
                /// </summary>
                void PopRetrievalFilter();

                /// <summary>
                /// Gets the size of the retrieval-filter stack in bytes.
                /// </summary>
                /// <returns>The size of the retrieval-filter stack in bytes.</returns>
                unsigned int GetRetrievalFilterStackSize();

                /// <summary>
                /// Adds a debug message to the message queue and sends that message to the debug output.
                /// </summary>
                /// <param name="category">A D3D12MessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <param name="severity">A D3D12MessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="id">An integer that uniquely identifies the message.</param>
                /// <param name="description">The message string.</param>
                /// <returns>Result code.</returns>
                Result AddMessage(
                    D3D12MessageCategory category,
                    D3D12MessageSeverity severity,
                    D3D12MessageID id,
                    String^ description
                );

                /// <summary>
                /// Adds a user-defined message to the message queue and sends that message to the
                /// debug output.
                /// </summary>
                /// <param name="severity">A D3D12MessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="description">The message string.</param>
                /// <returns>Result code.</returns>
                Result AddApplicationMessage(D3D12MessageSeverity severity, String^ description);

                /// <summary>
                /// Sets a message category to break on when a message with that category passes through
                /// the storage filter.
                /// </summary>
                /// <param name="category">A D3D12MessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnCategory turns on
                /// or off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnCategory(D3D12MessageCategory category, bool enable);

                /// <summary>
                /// Sets a message severity level to break on when a message with that severity level
                /// passes through the storage filter.
                /// </summary>
                /// <param name="severity">A D3D12MessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnSeverity turns on
                /// or off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnSeverity(D3D12MessageSeverity severity, bool enable);

                /// <summary>
                /// Sets a message identifier to break on when a message with that identifier passes
                /// through the storage filter.
                /// </summary>
                /// <param name="id">An integer value that specifies the identifier of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnID turns on or
                /// off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnID(D3D12MessageID id, bool enable);

                /// <summary>
                /// Determines whether the break on a message category is turned on or off.
                /// </summary>
                /// <param name="category">A D3D12MessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <returns>A Boolean value that specifies whether this category of breaking condition
                /// is turned on or off.</returns>
                bool GetBreakOnCategory(D3D12MessageCategory category);

                /// <summary>
                /// Determines whether the break on a message severity level is turned on or off.
                /// </summary>
                /// <param name="severity">A D3D12MessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <returns>A Boolean value that specifies whether this severity of breaking condition
                /// is turned on or off.</returns>
                bool GetBreakOnSeverity(D3D12MessageSeverity severity);

                /// <summary>
                /// Determines whether the break on a message identifier is turned on or off.
                /// </summary>
                /// <param name="id">An integer value that specifies the identifier of the message.</param>
                /// <returns>A Boolean value that specifies whether this break on a message identifier
                /// is turned on or off.</returns>
                bool GetBreakOnID(D3D12MessageID id);

                /// <summary>
                /// Turns the debug output on or off.
                /// </summary>
                /// <param name="mute">A Boolean value that specifies whether to turn the debug output on
                /// or off.</param>
                void SetMuteDebugOutput(bool mute);

                /// <summary>
                /// Determines whether the debug output is turned on or off.
                /// </summary>
                /// <returns>A Boolean value that specifies whether the debug output is turned on or off.
                /// </returns>
                bool GetMuteDebugOutput();
            };
        }
    }
}
