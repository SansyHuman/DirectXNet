#pragma once

#include "../../pch.h"
#include "../../Common/Unknown.h"
#include "../../Common/Result.h"
#include "DXGIDebugStructs.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace msclr;

// Done.

namespace DirectXNet
{
    namespace DXGI
    {
        namespace Debug
        {
            /// <summary>
            /// This class controls the debug information queue, and can only be used if the debug layer
            /// is turned on.
            /// </summary>
            public ref class DXGIInfoQueue : Common::Unknown
            {
            private:
                ::IDXGIInfoQueue* pQueue;

            public:
                DXGIInfoQueue(::IDXGIInfoQueue* pQueue);
                DXGIInfoQueue() : Common::Unknown() {}

            internal:
                virtual void AttatchComObj(::IUnknown* pComObj) override;

            public:
                /// <summary>
                /// Gets GUID of the interface.
                /// Override it to returns GUID of the interface.
                /// </summary>
                /// <returns>GUID of IDXGIInfoQueue.</returns>
                virtual Guid GetGuid() override;

                /// <summary>
                /// Sets the maximum number of messages that can be added to the message queue.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that sets the
                /// limit on the number of messages.</param>
                /// <param name="messageCountLimit">The maximum number of messages that can be added to
                /// the queue. -1 means no limit.</param>
                /// <returns>Result code.</returns>
                Result SetMessageCountLimit(Guid producer, unsigned long long messageCountLimit);

                /// <summary>
                /// Clears all messages from the message queue.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that clears
                /// the messages.</param>
                void ClearStoredMessages(Guid producer);

                /// <summary>
                /// Gets a message from the message queue.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the message.</param>
                /// <param name="messageIndex">An index into the message queue after an optional retrieval
                /// filter has been applied. This can be between 0 and the number of messages in the
                /// message queue that pass through the retrieval filter.
                /// Call DXGIInfoQueue::GetNumStoredMessagesAllowedByRetrievalFilters to obtain this number.
                /// 0 is the message at the beginning of the message queue.</param>
                /// <returns>Message if succeeded.</returns>
                DXGIInfoQueueMessage GetMessage(Guid producer, unsigned long long messageIndex);

                /// <summary>
                /// Gets the number of messages that can pass through a retrieval filter.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The number of messages that can pass through a retrieval filter.</returns>
                unsigned long long GetNumStoredMessagesAllowedByRetrievalFilters(Guid producer);

                /// <summary>
                /// Gets the number of messages currently stored in the message queue.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The number of messages currently stored in the message queue.</returns>
                unsigned long long GetNumStoredMessages(Guid producer);

                /// <summary>
                /// Gets the number of messages that were discarded due to the message count limit.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The number of messages that were discarded.</returns>
                unsigned long long GetNumMessagesDiscardedByMessageCountLimit(Guid producer);

                /// <summary>
                /// Gets the maximum number of messages that can be added to the message queue.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The maximum number of messages that can be added to the queue.
                /// -1 means no limit.</returns>
                unsigned long long GetMessageCountLimit(Guid producer);

                /// <summary>
                /// Gets the number of messages that a storage filter allowed to pass through.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The number of messages allowed by a storage filter.</returns>
                unsigned long long GetNumMessagesAllowedByStorageFilter(Guid producer);

                /// <summary>
                /// Gets the number of messages that were denied passage through a storage filter.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the number.</param>
                /// <returns>The number of messages denied by a storage filter.</returns>
                unsigned long long GetNumMessagesDeniedByStorageFilter(Guid producer);

                /// <summary>
                /// Adds storage filters to the top of the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that produced
                /// the filters.</param>
                /// <param name="filter">A DXGIInfoQueueFilter structure that describe the filters.</param>
                /// <returns></returns>
                Result AddStorageFilterEntries(
                    Guid producer,
                    [In][IsReadOnly] DXGIInfoQueueFilter% filter
                );

                /// <summary>
                /// Gets the storage filter at the top of the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the filter.</param>
                /// <returns>Storage filter if succeeded.</returns>
                DXGIInfoQueueFilter GetStorageFilter(Guid producer);

                /// <summary>
                /// Removes a storage filter from the top of the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that removes
                /// the filter.</param>
                void ClearStorageFilter(Guid producer);

                /// <summary>
                /// Pushes an empty storage filter onto the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the empty storage filter.</param>
                /// <returns>Result code.</returns>
                Result PushEmptyStorageFilter(Guid producer);

                /// <summary>
                /// Pushes a deny-all storage filter onto the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the filter.</param>
                /// <returns>Result code.</returns>
                Result PushDenyAllStorageFilter(Guid producer);

                /// <summary>
                /// Pushes a copy of the storage filter that is currently on the top of the
                /// storage-filter stack onto the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the copy of the storage filter.</param>
                /// <returns>Result code.</returns>
                Result PushCopyOfStorageFilter(Guid producer);

                /// <summary>
                /// Pushes a storage filter onto the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the filter.</param>
                /// <param name="filter">A DXGIInfoQueueFilter structure that describes the filter.</param>
                /// <returns>Result code.</returns>
                Result PushStorageFilter(
                    Guid producer,
                    [In][IsReadOnly] DXGIInfoQueueFilter% filter
                );

                /// <summary>
                /// Pops a storage filter from the top of the storage-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pops
                /// the filter.</param>
                void PopStorageFilter(Guid producer);

                /// <summary>
                /// Gets the size of the storage-filter stack in bytes.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the size.</param>
                /// <returns>The size of the storage-filter stack in bytes.</returns>
                unsigned int GetStorageFilterStackSize(Guid producer);

                /// <summary>
                /// Adds retrieval filters to the top of the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that produced
                /// the filters.</param>
                /// <param name="filter">An DXGIInfoQueueFilter structure that describe the filters.</param>
                /// <returns>Result code.</returns>
                Result AddRetrievalFilterEntries(
                    Guid producer,
                    [In][IsReadOnly] DXGIInfoQueueFilter% filter
                );

                /// <summary>
                /// Gets the retrieval filter at the top of the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the filter.</param>
                /// <returns>Retrieval filter if succeeded.</returns>
                DXGIInfoQueueFilter GetRetrievalFilter(Guid producer);

                /// <summary>
                /// Removes a retrieval filter from the top of the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that removes
                /// the filter.</param>
                void ClearRetrievalFilter(Guid producer);

                /// <summary>
                /// Pushes an empty retrieval filter onto the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the empty retrieval filter.</param>
                /// <returns>Result code.</returns>
                Result PushEmptyRetrievalFilter(Guid producer);

                /// <summary>
                /// Pushes a deny-all retrieval filter onto the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the deny-all retrieval filter.</param>
                /// <returns>Result code.</returns>
                Result PushDenyAllRetrievalFilter(Guid producer);

                /// <summary>
                /// Pushes a copy of the retrieval filter that is currently on the top of the
                /// retrieval-filter stack onto the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the copy of the retrieval filter.</param>
                /// <returns>Result code.</returns>
                Result PushCopyOfRetrievalFilter(Guid producer);

                /// <summary>
                /// Pushes a retrieval filter onto the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pushes
                /// the filter.</param>
                /// <param name="filter">A DXGIInfoQueueFilter structure that describes the filter.</param>
                /// <returns>Result code.</returns>
                Result PushRetrievalFilter(
                    Guid producer,
                    [In][IsReadOnly] DXGIInfoQueueFilter% filter
                );

                /// <summary>
                /// Pops a retrieval filter from the top of the retrieval-filter stack.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that pops
                /// the filter.</param>
                void PopRetrievalFilter(Guid producer);

                /// <summary>
                /// Gets the size of the retrieval-filter stack in bytes.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the size.</param>
                /// <returns>The size of the retrieval-filter stack in bytes.</returns>
                unsigned int GetRetrievalFilterStackSize(Guid producer);

                /// <summary>
                /// Adds a debug message to the message queue and sends that message to the debug output.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that produced
                /// the message.</param>
                /// <param name="category">A DXGIInfoQueueMessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <param name="severity">A DXGIInfoQueueMessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="id">An integer that uniquely identifies the message.</param>
                /// <param name="description">The message string.</param>
                /// <returns>Result code.</returns>
                Result AddMessage(
                    Guid producer,
                    DXGIInfoQueueMessageCategory category,
                    DXGIInfoQueueMessageSeverity severity,
                    int id,
                    String^ description
                );

                /// <summary>
                /// Adds a user-defined message to the message queue and sends that message to the
                /// debug output.
                /// </summary>
                /// <param name="severity">A DXGIInfoQueueMessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="description">The message string.</param>
                /// <returns>Result code.</returns>
                Result AddApplicationMessage(DXGIInfoQueueMessageSeverity severity, String^ description);

                /// <summary>
                /// Sets a message category to break on when a message with that category passes through
                /// the storage filter.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that sets
                /// the breaking condition.</param>
                /// <param name="category">A DXGIInfoQueueMessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnCategory turns on
                /// or off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnCategory(Guid producer, DXGIInfoQueueMessageCategory category, bool enable);

                /// <summary>
                /// Sets a message severity level to break on when a message with that severity level
                /// passes through the storage filter.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that sets
                /// the breaking condition.</param>
                /// <param name="severity">A DXGIInfoQueueMessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnSeverity turns on
                /// or off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnSeverity(Guid producer, DXGIInfoQueueMessageSeverity severity, bool enable);

                /// <summary>
                /// Sets a message identifier to break on when a message with that identifier passes
                /// through the storage filter.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that sets
                /// the breaking condition.</param>
                /// <param name="id">An integer value that specifies the identifier of the message.</param>
                /// <param name="enable">A Boolean value that specifies whether SetBreakOnID turns on or
                /// off this breaking condition.</param>
                /// <returns>Result code.</returns>
                Result SetBreakOnID(Guid producer, int id, bool enable);

                /// <summary>
                /// Determines whether the break on a message category is turned on or off.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the breaking status.</param>
                /// <param name="category">A DXGIInfoQueueMessageCategory-typed value that specifies
                /// the category of the message.</param>
                /// <returns>A Boolean value that specifies whether this category of breaking condition
                /// is turned on or off.</returns>
                bool GetBreakOnCategory(Guid producer, DXGIInfoQueueMessageCategory category);

                /// <summary>
                /// Determines whether the break on a message severity level is turned on or off.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the breaking status.</param>
                /// <param name="severity">A DXGIInfoQueueMessageSeverity-typed value that specifies
                /// the severity of the message.</param>
                /// <returns>A Boolean value that specifies whether this severity of breaking condition
                /// is turned on or off.</returns>
                bool GetBreakOnSeverity(Guid producer, DXGIInfoQueueMessageSeverity severity);

                /// <summary>
                /// Determines whether the break on a message identifier is turned on or off.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets
                /// the breaking status.</param>
                /// <param name="id">An integer value that specifies the identifier of the message.</param>
                /// <returns>A Boolean value that specifies whether this break on a message identifier
                /// is turned on or off.</returns>
                bool GetBreakOnID(Guid producer, int id);

                /// <summary>
                /// Turns the debug output on or off.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets the
                /// mute status.</param>
                /// <param name="mute">A Boolean value that specifies whether to turn the debug output on
                /// or off.</param>
                void SetMuteDebugOutput(Guid producer, bool mute);

                /// <summary>
                /// Determines whether the debug output is turned on or off.
                /// </summary>
                /// <param name="producer">A DXGIDebugID value that identifies the entity that gets the
                /// mute status.</param>
                /// <returns>A Boolean value that specifies whether the debug output is turned on or off.
                /// </returns>
                bool GetMuteDebugOutput(Guid producer);
            };
        }
    }
}