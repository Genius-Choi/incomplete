pRxNetDescriptor ReceiveQueueGetBuffer(PPARANDIS_RECEIVE_QUEUE pQueue)
{
    PLIST_ENTRY pListEntry = NdisInterlockedRemoveHeadList(&pQueue->BuffersList, &pQueue->Lock);
    return pListEntry ? CONTAINING_RECORD(pListEntry, RxNetDescriptor, ReceiveQueueListEntry) : NULL;
}
