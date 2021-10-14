#include "DXGIInfoQueue.h"
#include "../../Common/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System;
using namespace DirectXNet::Common;
using namespace DirectXNet::DXGI::Debug;
using namespace msclr::interop;

DirectXNet::DXGI::Debug::DXGIInfoQueue::DXGIInfoQueue(::IDXGIInfoQueue* pQueue)
    : DirectXNet::Common::Unknown((::IUnknown*)pQueue)
{
    this->pQueue = pQueue;
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pQueue = (::IDXGIInfoQueue*)pComObj;
}

Guid DirectXNet::DXGI::Debug::DXGIInfoQueue::GetGuid()
{
    return CAST_TO(__uuidof(::IDXGIInfoQueue), Guid);
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::SetMessageCountLimit(
    Guid producer, unsigned long long messageCountLimit)
{
    return Result(pQueue->SetMessageCountLimit(CAST_TO(producer, _GUID), messageCountLimit));
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::ClearStoredMessages(Guid producer)
{
    pQueue->ClearStoredMessages(CAST_TO(producer, GUID));
}

DXGIInfoQueueMessage DirectXNet::DXGI::Debug::DXGIInfoQueue::GetMessage(
    Guid producer, unsigned long long messageIndex)
{
    DXGI_DEBUG_ID guid = CAST_TO(producer, GUID);
    SIZE_T messageLength = 0;
    Result::ThrowIfFailed(pQueue->GetMessage(guid, messageIndex, __nullptr, &messageLength));

    ::DXGI_INFO_QUEUE_MESSAGE* pMessage = __nullptr;

    try
    {
        pMessage = (::DXGI_INFO_QUEUE_MESSAGE*)malloc(messageLength);
        Result::ThrowIfFailed(pQueue->GetMessage(guid, messageIndex, pMessage, &messageLength));

        DXGIInfoQueueMessage message;
        message.Producer = CAST_TO(pMessage->Producer, Guid);
        message.Category = (DXGIInfoQueueMessageCategory)pMessage->Category;
        message.Severity = (DXGIInfoQueueMessageSeverity)pMessage->Severity;
        message.ID = pMessage->ID;
        message.Description = marshal_as<String^>(pMessage->pDescription);

        return message;
    }
    finally
    {
        free(pMessage);
    }
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetNumStoredMessagesAllowedByRetrievalFilters(
    Guid producer)
{
    return pQueue->GetNumStoredMessagesAllowedByRetrievalFilters(CAST_TO(producer, _GUID));
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetNumStoredMessages(Guid producer)
{
    return pQueue->GetNumStoredMessages(CAST_TO(producer, _GUID));
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetNumMessagesDiscardedByMessageCountLimit(
    Guid producer)
{
    return pQueue->GetNumMessagesDiscardedByMessageCountLimit(CAST_TO(producer, _GUID));
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetMessageCountLimit(Guid producer)
{
    return pQueue->GetMessageCountLimit(CAST_TO(producer, _GUID));
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetNumMessagesAllowedByStorageFilter(Guid producer)
{
    return pQueue->GetNumMessagesAllowedByStorageFilter(CAST_TO(producer, _GUID));
}

unsigned long long DirectXNet::DXGI::Debug::DXGIInfoQueue::GetNumMessagesDeniedByStorageFilter(Guid producer)
{
    return pQueue->GetNumMessagesDeniedByStorageFilter(CAST_TO(producer, _GUID));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::AddStorageFilterEntries(
    Guid producer, DXGIInfoQueueFilter% filter)
{
    ::DXGI_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<int> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (int*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<int> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (int*)pDenyIDList;

    return Result(pQueue->AddStorageFilterEntries(CAST_TO(producer, _GUID), &filterN));
}

DXGIInfoQueueFilter DirectXNet::DXGI::Debug::DXGIInfoQueue::GetStorageFilter(Guid producer)
{
    SIZE_T filterByteLength = 0;
    DXGI_DEBUG_ID guid = CAST_TO(producer, _GUID);

    Result::ThrowIfFailed(pQueue->GetStorageFilter(guid, __nullptr, &filterByteLength));

    ::DXGI_INFO_QUEUE_FILTER* pFilter = __nullptr;
    try
    {
        pFilter = (::DXGI_INFO_QUEUE_FILTER*)malloc(filterByteLength);
        Result::ThrowIfFailed(pQueue->GetStorageFilter(guid, pFilter, &filterByteLength));

        DXGIInfoQueueFilter filter;

        filter.AllowList.CategoryList = gcnew array<DXGIInfoQueueMessageCategory>(pFilter->AllowList.NumCategories);
        pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategories = &filter.AllowList.CategoryList[0];
        memcpy((void*)pAllowCategories, (void*)pFilter->AllowList.pCategoryList, pFilter->AllowList.NumCategories * sizeof(::DXGI_INFO_QUEUE_MESSAGE_CATEGORY));

        filter.AllowList.SeverityList = gcnew array<DXGIInfoQueueMessageSeverity>(pFilter->AllowList.NumSeverities);
        pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverities = &filter.AllowList.SeverityList[0];
        memcpy((void*)pAllowSeverities, (void*)pFilter->AllowList.pSeverityList, pFilter->AllowList.NumSeverities * sizeof(::DXGI_INFO_QUEUE_MESSAGE_SEVERITY));

        filter.AllowList.IDList = gcnew array<int>(pFilter->AllowList.NumIDs);
        pin_ptr<int> pAllowIDs = &filter.AllowList.IDList[0];
        memcpy((void*)pAllowIDs, (void*)pFilter->AllowList.pIDList, pFilter->AllowList.NumIDs * sizeof(int));

        filter.DenyList.CategoryList = gcnew array<DXGIInfoQueueMessageCategory>(pFilter->DenyList.NumCategories);
        pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategories = &filter.DenyList.CategoryList[0];
        memcpy((void*)pDenyCategories, (void*)pFilter->DenyList.pCategoryList, pFilter->DenyList.NumCategories * sizeof(::DXGI_INFO_QUEUE_MESSAGE_CATEGORY));

        filter.DenyList.SeverityList = gcnew array<DXGIInfoQueueMessageSeverity>(pFilter->DenyList.NumSeverities);
        pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverities = &filter.DenyList.SeverityList[0];
        memcpy((void*)pDenySeverities, (void*)pFilter->DenyList.pSeverityList, pFilter->DenyList.NumSeverities * sizeof(::DXGI_INFO_QUEUE_MESSAGE_SEVERITY));

        filter.DenyList.IDList = gcnew array<int>(pFilter->DenyList.NumIDs);
        pin_ptr<int> pDenyIDs = &filter.DenyList.IDList[0];
        memcpy((void*)pDenyIDs, (void*)pFilter->DenyList.pIDList, pFilter->DenyList.NumIDs * sizeof(int));

        return filter;
    }
    finally
    {
        free(pFilter);
    }
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::ClearStorageFilter(Guid producer)
{
    pQueue->ClearStorageFilter(CAST_TO(producer, _GUID));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushEmptyStorageFilter(Guid producer)
{
    return Result(pQueue->PushEmptyStorageFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushDenyAllStorageFilter(Guid producer)
{
    return Result(pQueue->PushDenyAllStorageFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushCopyOfStorageFilter(Guid producer)
{
    return Result(pQueue->PushCopyOfStorageFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushStorageFilter(Guid producer, DXGIInfoQueueFilter% filter)
{
    ::DXGI_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<int> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (int*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<int> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (int*)pDenyIDList;

    return Result(pQueue->PushStorageFilter(CAST_TO(producer, _GUID), &filterN));
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::PopStorageFilter(Guid producer)
{
    pQueue->PopStorageFilter(CAST_TO(producer, _GUID));
}

unsigned int DirectXNet::DXGI::Debug::DXGIInfoQueue::GetStorageFilterStackSize(Guid producer)
{
    return pQueue->GetStorageFilterStackSize(CAST_TO(producer, _GUID));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::AddRetrievalFilterEntries(
    Guid producer, DXGIInfoQueueFilter% filter)
{
    ::DXGI_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<int> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (int*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<int> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (int*)pDenyIDList;

    return Result(pQueue->AddRetrievalFilterEntries(CAST_TO(producer, _GUID), &filterN));
}

DXGIInfoQueueFilter DirectXNet::DXGI::Debug::DXGIInfoQueue::GetRetrievalFilter(Guid producer)
{
    SIZE_T filterByteLength = 0;
    DXGI_DEBUG_ID guid = CAST_TO(producer, _GUID);

    Result::ThrowIfFailed(pQueue->GetRetrievalFilter(guid, __nullptr, &filterByteLength));

    ::DXGI_INFO_QUEUE_FILTER* pFilter = __nullptr;
    try
    {
        pFilter = (::DXGI_INFO_QUEUE_FILTER*)malloc(filterByteLength);
        Result::ThrowIfFailed(pQueue->GetRetrievalFilter(guid, pFilter, &filterByteLength));

        DXGIInfoQueueFilter filter;

        filter.AllowList.CategoryList = gcnew array<DXGIInfoQueueMessageCategory>(pFilter->AllowList.NumCategories);
        pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategories = &filter.AllowList.CategoryList[0];
        memcpy((void*)pAllowCategories, (void*)pFilter->AllowList.pCategoryList, pFilter->AllowList.NumCategories * sizeof(::DXGI_INFO_QUEUE_MESSAGE_CATEGORY));

        filter.AllowList.SeverityList = gcnew array<DXGIInfoQueueMessageSeverity>(pFilter->AllowList.NumSeverities);
        pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverities = &filter.AllowList.SeverityList[0];
        memcpy((void*)pAllowSeverities, (void*)pFilter->AllowList.pSeverityList, pFilter->AllowList.NumSeverities * sizeof(::DXGI_INFO_QUEUE_MESSAGE_SEVERITY));

        filter.AllowList.IDList = gcnew array<int>(pFilter->AllowList.NumIDs);
        pin_ptr<int> pAllowIDs = &filter.AllowList.IDList[0];
        memcpy((void*)pAllowIDs, (void*)pFilter->AllowList.pIDList, pFilter->AllowList.NumIDs * sizeof(int));

        filter.DenyList.CategoryList = gcnew array<DXGIInfoQueueMessageCategory>(pFilter->DenyList.NumCategories);
        pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategories = &filter.DenyList.CategoryList[0];
        memcpy((void*)pDenyCategories, (void*)pFilter->DenyList.pCategoryList, pFilter->DenyList.NumCategories * sizeof(::DXGI_INFO_QUEUE_MESSAGE_CATEGORY));

        filter.DenyList.SeverityList = gcnew array<DXGIInfoQueueMessageSeverity>(pFilter->DenyList.NumSeverities);
        pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverities = &filter.DenyList.SeverityList[0];
        memcpy((void*)pDenySeverities, (void*)pFilter->DenyList.pSeverityList, pFilter->DenyList.NumSeverities * sizeof(::DXGI_INFO_QUEUE_MESSAGE_SEVERITY));

        filter.DenyList.IDList = gcnew array<int>(pFilter->DenyList.NumIDs);
        pin_ptr<int> pDenyIDs = &filter.DenyList.IDList[0];
        memcpy((void*)pDenyIDs, (void*)pFilter->DenyList.pIDList, pFilter->DenyList.NumIDs * sizeof(int));

        return filter;
    }
    finally
    {
        free(pFilter);
    }
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::ClearRetrievalFilter(Guid producer)
{
    pQueue->ClearRetrievalFilter(CAST_TO(producer, _GUID));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushEmptyRetrievalFilter(Guid producer)
{
    return Result(pQueue->PushEmptyRetrievalFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushDenyAllRetrievalFilter(Guid producer)
{
    return Result(pQueue->PushDenyAllRetrievalFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushCopyOfRetrievalFilter(Guid producer)
{
    return Result(pQueue->PushCopyOfRetrievalFilter(CAST_TO(producer, _GUID)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::PushRetrievalFilter(Guid producer, DXGIInfoQueueFilter% filter)
{
    ::DXGI_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<int> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (int*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<DXGIInfoQueueMessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<DXGIInfoQueueMessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<int> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (int*)pDenyIDList;

    return Result(pQueue->PushRetrievalFilter(CAST_TO(producer, _GUID), &filterN));
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::PopRetrievalFilter(Guid producer)
{
    pQueue->PopRetrievalFilter(CAST_TO(producer, _GUID));
}

unsigned int DirectXNet::DXGI::Debug::DXGIInfoQueue::GetRetrievalFilterStackSize(Guid producer)
{
    return pQueue->GetRetrievalFilterStackSize(CAST_TO(producer, _GUID));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::AddMessage(
    Guid producer, DXGIInfoQueueMessageCategory category, DXGIInfoQueueMessageSeverity severity,
    int id, String^ description)
{
    marshal_context context;
    return Result(pQueue->AddMessage(
        CAST_TO(producer, _GUID),
        (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY)category,
        (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY)severity,
        id,
        context.marshal_as<LPCSTR>(description)
    ));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::AddApplicationMessage(DXGIInfoQueueMessageSeverity severity, String^ description)
{
    marshal_context context;
    return Result(pQueue->AddApplicationMessage((::DXGI_INFO_QUEUE_MESSAGE_SEVERITY)severity, context.marshal_as<LPCSTR>(description)));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::SetBreakOnCategory(
    Guid producer, DXGIInfoQueueMessageCategory category, bool enable)
{
    return Result(pQueue->SetBreakOnCategory(CAST_TO(producer, _GUID), (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY)category, (BOOL)enable));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::SetBreakOnSeverity(
    Guid producer, DXGIInfoQueueMessageSeverity severity, bool enable)
{
    return Result(pQueue->SetBreakOnSeverity(CAST_TO(producer, _GUID), (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY)severity, (BOOL)enable));
}

Result DirectXNet::DXGI::Debug::DXGIInfoQueue::SetBreakOnID(Guid producer, int id, bool enable)
{
    return Result(pQueue->SetBreakOnID(CAST_TO(producer, _GUID), id, (BOOL)enable));
}

bool DirectXNet::DXGI::Debug::DXGIInfoQueue::GetBreakOnCategory(
    Guid producer, DXGIInfoQueueMessageCategory category)
{
    return !!(pQueue->GetBreakOnCategory(CAST_TO(producer, _GUID), (::DXGI_INFO_QUEUE_MESSAGE_CATEGORY)category));
}

bool DirectXNet::DXGI::Debug::DXGIInfoQueue::GetBreakOnSeverity(
    Guid producer, DXGIInfoQueueMessageSeverity severity)
{
    return !!(pQueue->GetBreakOnSeverity(CAST_TO(producer, _GUID), (::DXGI_INFO_QUEUE_MESSAGE_SEVERITY)severity));
}

bool DirectXNet::DXGI::Debug::DXGIInfoQueue::GetBreakOnID(Guid producer, int id)
{
    return !!(pQueue->GetBreakOnID(CAST_TO(producer, _GUID), id));
}

void DirectXNet::DXGI::Debug::DXGIInfoQueue::SetMuteDebugOutput(Guid producer, bool mute)
{
    pQueue->SetMuteDebugOutput(CAST_TO(producer, _GUID), (BOOL)mute);
}

bool DirectXNet::DXGI::Debug::DXGIInfoQueue::GetMuteDebugOutput(Guid producer)
{
    return !!(pQueue->GetMuteDebugOutput(CAST_TO(producer, _GUID)));
}
