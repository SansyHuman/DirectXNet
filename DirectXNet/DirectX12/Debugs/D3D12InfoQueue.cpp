#include "D3D12InfoQueue.h"

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace DirectXNet::Common;
using namespace DirectXNet::DirectX12;
using namespace DirectXNet::DirectX12::Debug;

DirectXNet::DirectX12::Debug::D3D12InfoQueue::D3D12InfoQueue(::ID3D12InfoQueue* pQueue)
    : DirectXNet::Common::Unknown((::IUnknown*)pQueue)
{
    this->pQueue = pQueue;
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::AttatchComObj(::IUnknown* pComObj)
{
    DirectXNet::Common::Unknown::AttatchComObj(pComObj);
    pQueue = (::ID3D12InfoQueue*)pComObj;
}

Guid DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetGuid()
{
    return CAST_TO(__uuidof(::ID3D12InfoQueue), Guid);
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::SetMessageCountLimit(
    unsigned long long messageCountLimit)
{
    return Result(pQueue->SetMessageCountLimit(messageCountLimit));
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::ClearStoredMessages()
{
    pQueue->ClearStoredMessages();
}

D3D12Message DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetMessage(
    unsigned long long messageIndex)
{
    SIZE_T messageLength = 0;
    Result::ThrowIfFailed(pQueue->GetMessage(messageIndex, __nullptr, &messageLength));

    ::D3D12_MESSAGE* pMessage = __nullptr;

    try
    {
        pMessage = (::D3D12_MESSAGE*)malloc(messageLength);
        Result::ThrowIfFailed(pQueue->GetMessage(messageIndex, pMessage, &messageLength));

        D3D12Message message;
        message.Category = (D3D12MessageCategory)pMessage->Category;
        message.Severity = (D3D12MessageSeverity)pMessage->Severity;
        message.ID = (D3D12MessageID)pMessage->ID;
        message.Description = marshal_as<String^>(pMessage->pDescription);

        return message;
    }
    finally
    {
        free(pMessage);
    }
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetNumStoredMessagesAllowedByRetrievalFilter()
{
    return pQueue->GetNumStoredMessagesAllowedByRetrievalFilter();
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetNumStoredMessages()
{
    return pQueue->GetNumStoredMessages();
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetNumMessagesDiscardedByMessageCountLimit()
{
    return pQueue->GetNumMessagesDiscardedByMessageCountLimit();
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetMessageCountLimit()
{
    return pQueue->GetMessageCountLimit();
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetNumMessagesAllowedByStorageFilter()
{
    return pQueue->GetNumMessagesAllowedByStorageFilter();
}

unsigned long long DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetNumMessagesDeniedByStorageFilter()
{
    return pQueue->GetNumMessagesDeniedByStorageFilter();
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::AddStorageFilterEntries(D3D12InfoQueueFilter% filter)
{
    ::D3D12_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<D3D12MessageID> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (::D3D12_MESSAGE_ID*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<D3D12MessageID> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (D3D12_MESSAGE_ID*)pDenyIDList;

    return Result(pQueue->AddStorageFilterEntries(&filterN));
}

D3D12InfoQueueFilter DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetStorageFilter()
{
    SIZE_T filterByteLength = 0;

    Result::ThrowIfFailed(pQueue->GetStorageFilter(__nullptr, &filterByteLength));

    ::D3D12_INFO_QUEUE_FILTER* pFilter = __nullptr;
    try
    {
        pFilter = (::D3D12_INFO_QUEUE_FILTER*)malloc(filterByteLength);
        Result::ThrowIfFailed(pQueue->GetStorageFilter(pFilter, &filterByteLength));

        D3D12InfoQueueFilter filter;

        filter.AllowList.CategoryList = gcnew array<D3D12MessageCategory>(pFilter->AllowList.NumCategories);
        pin_ptr<D3D12MessageCategory> pAllowCategories = &filter.AllowList.CategoryList[0];
        memcpy((void*)pAllowCategories, (void*)pFilter->AllowList.pCategoryList, pFilter->AllowList.NumCategories * sizeof(::D3D12_MESSAGE_CATEGORY));

        filter.AllowList.SeverityList = gcnew array<D3D12MessageSeverity>(pFilter->AllowList.NumSeverities);
        pin_ptr<D3D12MessageSeverity> pAllowSeverities = &filter.AllowList.SeverityList[0];
        memcpy((void*)pAllowSeverities, (void*)pFilter->AllowList.pSeverityList, pFilter->AllowList.NumSeverities * sizeof(::D3D12_MESSAGE_SEVERITY));

        filter.AllowList.IDList = gcnew array<D3D12MessageID>(pFilter->AllowList.NumIDs);
        pin_ptr<D3D12MessageID> pAllowIDs = &filter.AllowList.IDList[0];
        memcpy((void*)pAllowIDs, (void*)pFilter->AllowList.pIDList, pFilter->AllowList.NumIDs * sizeof(::D3D12_MESSAGE_ID));

        filter.DenyList.CategoryList = gcnew array<D3D12MessageCategory>(pFilter->DenyList.NumCategories);
        pin_ptr<D3D12MessageCategory> pDenyCategories = &filter.DenyList.CategoryList[0];
        memcpy((void*)pDenyCategories, (void*)pFilter->DenyList.pCategoryList, pFilter->DenyList.NumCategories * sizeof(::D3D12_MESSAGE_CATEGORY));

        filter.DenyList.SeverityList = gcnew array<D3D12MessageSeverity>(pFilter->DenyList.NumSeverities);
        pin_ptr<D3D12MessageSeverity> pDenySeverities = &filter.DenyList.SeverityList[0];
        memcpy((void*)pDenySeverities, (void*)pFilter->DenyList.pSeverityList, pFilter->DenyList.NumSeverities * sizeof(::D3D12_MESSAGE_SEVERITY));

        filter.DenyList.IDList = gcnew array<D3D12MessageID>(pFilter->DenyList.NumIDs);
        pin_ptr<D3D12MessageID> pDenyIDs = &filter.DenyList.IDList[0];
        memcpy((void*)pDenyIDs, (void*)pFilter->DenyList.pIDList, pFilter->DenyList.NumIDs * sizeof(::D3D12_MESSAGE_ID));

        return filter;
    }
    finally
    {
        free(pFilter);
    }
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::ClearStorageFilter()
{
    pQueue->ClearStorageFilter();
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushEmptyStorageFilter()
{
    return Result(pQueue->PushEmptyStorageFilter());
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushCopyOfStorageFilter()
{
    return Result(pQueue->PushCopyOfStorageFilter());
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushStorageFilter(D3D12InfoQueueFilter% filter)
{
    ::D3D12_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<D3D12MessageID> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (::D3D12_MESSAGE_ID*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<D3D12MessageID> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (::D3D12_MESSAGE_ID*)pDenyIDList;

    return Result(pQueue->PushStorageFilter(&filterN));
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::PopStorageFilter()
{
    pQueue->PopStorageFilter();
}

unsigned int DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetStorageFilterStackSize()
{
    return pQueue->GetStorageFilterStackSize();
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::AddRetrievalFilterEntries(D3D12InfoQueueFilter% filter)
{
    ::D3D12_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<D3D12MessageID> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (::D3D12_MESSAGE_ID*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<D3D12MessageID> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (::D3D12_MESSAGE_ID*)pDenyIDList;

    return Result(pQueue->AddRetrievalFilterEntries(&filterN));
}

D3D12InfoQueueFilter DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetRetrievalFilter()
{
    SIZE_T filterByteLength = 0;

    Result::ThrowIfFailed(pQueue->GetRetrievalFilter(__nullptr, &filterByteLength));

    ::D3D12_INFO_QUEUE_FILTER* pFilter = __nullptr;
    try
    {
        pFilter = (::D3D12_INFO_QUEUE_FILTER*)malloc(filterByteLength);
        Result::ThrowIfFailed(pQueue->GetRetrievalFilter(pFilter, &filterByteLength));

        D3D12InfoQueueFilter filter;

        filter.AllowList.CategoryList = gcnew array<D3D12MessageCategory>(pFilter->AllowList.NumCategories);
        pin_ptr<D3D12MessageCategory> pAllowCategories = &filter.AllowList.CategoryList[0];
        memcpy((void*)pAllowCategories, (void*)pFilter->AllowList.pCategoryList, pFilter->AllowList.NumCategories * sizeof(::D3D12_MESSAGE_CATEGORY));

        filter.AllowList.SeverityList = gcnew array<D3D12MessageSeverity>(pFilter->AllowList.NumSeverities);
        pin_ptr<D3D12MessageSeverity> pAllowSeverities = &filter.AllowList.SeverityList[0];
        memcpy((void*)pAllowSeverities, (void*)pFilter->AllowList.pSeverityList, pFilter->AllowList.NumSeverities * sizeof(::D3D12_MESSAGE_SEVERITY));

        filter.AllowList.IDList = gcnew array<D3D12MessageID>(pFilter->AllowList.NumIDs);
        pin_ptr<D3D12MessageID> pAllowIDs = &filter.AllowList.IDList[0];
        memcpy((void*)pAllowIDs, (void*)pFilter->AllowList.pIDList, pFilter->AllowList.NumIDs * sizeof(::D3D12_MESSAGE_ID));

        filter.DenyList.CategoryList = gcnew array<D3D12MessageCategory>(pFilter->DenyList.NumCategories);
        pin_ptr<D3D12MessageCategory> pDenyCategories = &filter.DenyList.CategoryList[0];
        memcpy((void*)pDenyCategories, (void*)pFilter->DenyList.pCategoryList, pFilter->DenyList.NumCategories * sizeof(::D3D12_MESSAGE_CATEGORY));

        filter.DenyList.SeverityList = gcnew array<D3D12MessageSeverity>(pFilter->DenyList.NumSeverities);
        pin_ptr<D3D12MessageSeverity> pDenySeverities = &filter.DenyList.SeverityList[0];
        memcpy((void*)pDenySeverities, (void*)pFilter->DenyList.pSeverityList, pFilter->DenyList.NumSeverities * sizeof(::D3D12_MESSAGE_SEVERITY));

        filter.DenyList.IDList = gcnew array<D3D12MessageID>(pFilter->DenyList.NumIDs);
        pin_ptr<D3D12MessageID> pDenyIDs = &filter.DenyList.IDList[0];
        memcpy((void*)pDenyIDs, (void*)pFilter->DenyList.pIDList, pFilter->DenyList.NumIDs * sizeof(::D3D12_MESSAGE_ID));

        return filter;
    }
    finally
    {
        free(pFilter);
    }
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::ClearRetrievalFilter()
{
    pQueue->ClearRetrievalFilter();
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushEmptyRetrievalFilter()
{
    return Result(pQueue->PushEmptyRetrievalFilter());
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushCopyOfRetrievalFilter()
{
    return Result(pQueue->PushCopyOfRetrievalFilter());
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::PushRetrievalFilter(D3D12InfoQueueFilter% filter)
{
    ::D3D12_INFO_QUEUE_FILTER filterN = {};

    filterN.AllowList.NumCategories = filter.AllowList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pAllowCategoryList = &filter.AllowList.CategoryList[0];
    filterN.AllowList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pAllowCategoryList;

    filterN.AllowList.NumSeverities = filter.AllowList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pAllowSeverityList = &filter.AllowList.SeverityList[0];
    filterN.AllowList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pAllowSeverityList;

    filterN.AllowList.NumIDs = filter.AllowList.IDList->Length;
    pin_ptr<D3D12MessageID> pAllowIDList = &filter.AllowList.IDList[0];
    filterN.AllowList.pIDList = (::D3D12_MESSAGE_ID*)pAllowIDList;

    filterN.DenyList.NumCategories = filter.DenyList.CategoryList->Length;
    pin_ptr<D3D12MessageCategory> pDenyCategoryList = &filter.DenyList.CategoryList[0];
    filterN.DenyList.pCategoryList = (::D3D12_MESSAGE_CATEGORY*)pDenyCategoryList;

    filterN.DenyList.NumSeverities = filter.DenyList.SeverityList->Length;
    pin_ptr<D3D12MessageSeverity> pDenySeverityList = &filter.DenyList.SeverityList[0];
    filterN.DenyList.pSeverityList = (::D3D12_MESSAGE_SEVERITY*)pDenySeverityList;

    filterN.DenyList.NumIDs = filter.DenyList.IDList->Length;
    pin_ptr<D3D12MessageID> pDenyIDList = &filter.DenyList.IDList[0];
    filterN.DenyList.pIDList = (::D3D12_MESSAGE_ID*)pDenyIDList;

    return Result(pQueue->PushRetrievalFilter(&filterN));
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::PopRetrievalFilter()
{
    pQueue->PopRetrievalFilter();
}

unsigned int DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetRetrievalFilterStackSize()
{
    return pQueue->GetRetrievalFilterStackSize();
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::AddMessage(
    D3D12MessageCategory category, D3D12MessageSeverity severity,
    D3D12MessageID id, String^ description)
{
    marshal_context context;
    return Result(pQueue->AddMessage(
        (::D3D12_MESSAGE_CATEGORY)category,
        (::D3D12_MESSAGE_SEVERITY)severity,
        (::D3D12_MESSAGE_ID)id,
        context.marshal_as<LPCSTR>(description)
    ));
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::AddApplicationMessage(
    D3D12MessageSeverity severity, String^ description)
{
    marshal_context context;
    return Result(pQueue->AddApplicationMessage((::D3D12_MESSAGE_SEVERITY)severity, context.marshal_as<LPCSTR>(description)));
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::SetBreakOnCategory(
    D3D12MessageCategory category, bool enable)
{
    return Result(pQueue->SetBreakOnCategory((::D3D12_MESSAGE_CATEGORY)category, (BOOL)enable));
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::SetBreakOnSeverity(
    D3D12MessageSeverity severity, bool enable)
{
    return Result(pQueue->SetBreakOnSeverity((::D3D12_MESSAGE_SEVERITY)severity, (BOOL)enable));
}

Result DirectXNet::DirectX12::Debug::D3D12InfoQueue::SetBreakOnID(D3D12MessageID id, bool enable)
{
    return Result(pQueue->SetBreakOnID((::D3D12_MESSAGE_ID)id, (BOOL)enable));
}

bool DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetBreakOnCategory(D3D12MessageCategory category)
{
    return !!(pQueue->GetBreakOnCategory((::D3D12_MESSAGE_CATEGORY)category));
}

bool DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetBreakOnSeverity(D3D12MessageSeverity severity)
{
    return !!(pQueue->GetBreakOnSeverity((::D3D12_MESSAGE_SEVERITY)severity));
}

bool DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetBreakOnID(D3D12MessageID id)
{
    return !!(pQueue->GetBreakOnID((::D3D12_MESSAGE_ID)id));
}

void DirectXNet::DirectX12::Debug::D3D12InfoQueue::SetMuteDebugOutput(bool mute)
{
    pQueue->SetMuteDebugOutput((BOOL)mute);
}

bool DirectXNet::DirectX12::Debug::D3D12InfoQueue::GetMuteDebugOutput()
{
    return !!(pQueue->GetMuteDebugOutput());
}
