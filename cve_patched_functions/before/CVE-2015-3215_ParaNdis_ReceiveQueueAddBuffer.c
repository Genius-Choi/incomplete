VOID ParaNdis_ReceiveQueueAddBuffer(PPARANDIS_RECEIVE_QUEUE pQueue, pRxNetDescriptor pBuffer)
{
    NdisInterlockedInsertTailList(  &pQueue->BuffersList,
                                    &pBuffer->ReceiveQueueListEntry,
                                    &pQueue->Lock);
}
