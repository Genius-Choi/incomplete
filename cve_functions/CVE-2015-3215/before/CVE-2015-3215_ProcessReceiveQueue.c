static BOOLEAN ProcessReceiveQueue(PARANDIS_ADAPTER *pContext,
                                    PULONG pnPacketsToIndicateLeft,
                                    CCHAR nQueueIndex,
                                    PNET_BUFFER_LIST *indicate,
                                    PNET_BUFFER_LIST *indicateTail,
                                    ULONG *nIndicate)
{
    
    pRxNetDescriptor pBufferDescriptor;
    PPARANDIS_RECEIVE_QUEUE pTargetReceiveQueue = &pContext->ReceiveQueues[nQueueIndex];

    if(NdisInterlockedIncrement(&pTargetReceiveQueue->ActiveProcessorsCount) == 1)
    {
        while( (*pnPacketsToIndicateLeft > 0) &&
               (NULL != (pBufferDescriptor = ReceiveQueueGetBuffer(pTargetReceiveQueue))) )
        {
            PNET_PACKET_INFO pPacketInfo = &pBufferDescriptor->PacketInfo;

            if( !pContext->bSurprizeRemoved &&
                pContext->ReceiveState == srsEnabled &&
                pContext->bConnected &&
                ShallPassPacket(pContext, pPacketInfo))
            {
                UINT nCoalescedSegmentsCount;
                PNET_BUFFER_LIST packet = ParaNdis_PrepareReceivedPacket(pContext, pBufferDescriptor, &nCoalescedSegmentsCount);
                if(packet != NULL)
                {
                    UpdateReceiveSuccessStatistics(pContext, pPacketInfo, nCoalescedSegmentsCount);
                    if (*indicate == nullptr)
                    {
                        *indicate = *indicateTail = packet;
                    }
                    else
                    {
                        NET_BUFFER_LIST_NEXT_NBL(*indicateTail) = packet;
                        *indicateTail = packet;
                    }

                    NET_BUFFER_LIST_NEXT_NBL(*indicateTail) = NULL;
                    (*pnPacketsToIndicateLeft)--;
                    (*nIndicate)++;
                }
                else
                {
                    UpdateReceiveFailStatistics(pContext, nCoalescedSegmentsCount);
                    pBufferDescriptor->Queue->ReuseReceiveBuffer(pContext->ReuseBufferRegular, pBufferDescriptor);
                }
            }
            else
            {
                pContext->extraStatistics.framesFilteredOut++;
                pBufferDescriptor->Queue->ReuseReceiveBuffer(pContext->ReuseBufferRegular, pBufferDescriptor);
            }
        }
     }

    NdisInterlockedDecrement(&pTargetReceiveQueue->ActiveProcessorsCount);
    return ReceiveQueueHasBuffers(pTargetReceiveQueue);
}
