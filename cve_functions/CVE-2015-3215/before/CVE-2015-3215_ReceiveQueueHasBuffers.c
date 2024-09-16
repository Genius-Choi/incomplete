BOOLEAN ReceiveQueueHasBuffers(PPARANDIS_RECEIVE_QUEUE pQueue)
{
    BOOLEAN res;

    NdisAcquireSpinLock(&pQueue->Lock);
    res = !IsListEmpty(&pQueue->BuffersList);
    NdisReleaseSpinLock(&pQueue->Lock);

    return res;
}
