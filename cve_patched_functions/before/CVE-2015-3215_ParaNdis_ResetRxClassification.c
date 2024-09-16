VOID ParaNdis_ResetRxClassification(PARANDIS_ADAPTER *pContext)
{
    ULONG i;
    PPARANDIS_RECEIVE_QUEUE pUnclassified = &pContext->ReceiveQueues[PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED];

    NdisAcquireSpinLock(&pUnclassified->Lock);

    for(i = PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED + 1; i < ARRAYSIZE(pContext->ReceiveQueues); i++)
    {
        PPARANDIS_RECEIVE_QUEUE pCurrQueue = &pContext->ReceiveQueues[i];
        NdisAcquireSpinLock(&pCurrQueue->Lock);

        while(!IsListEmpty(&pCurrQueue->BuffersList))
        {
            PLIST_ENTRY pListEntry = RemoveHeadList(&pCurrQueue->BuffersList);
            InsertTailList(&pUnclassified->BuffersList, pListEntry);
        }

        NdisReleaseSpinLock(&pCurrQueue->Lock);
    }

    NdisReleaseSpinLock(&pUnclassified->Lock);
}
