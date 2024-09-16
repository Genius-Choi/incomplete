UpdateReceiveSuccessStatistics(PPARANDIS_ADAPTER pContext,
                               PNET_PACKET_INFO pPacketInfo,
                               UINT nCoalescedSegmentsCount)
{
    pContext->Statistics.ifHCInOctets += pPacketInfo->dataLength;

    if(pPacketInfo->isUnicast)
    {
        pContext->Statistics.ifHCInUcastPkts += nCoalescedSegmentsCount;
        pContext->Statistics.ifHCInUcastOctets += pPacketInfo->dataLength;
    }
    else if (pPacketInfo->isBroadcast)
    {
        pContext->Statistics.ifHCInBroadcastPkts += nCoalescedSegmentsCount;
        pContext->Statistics.ifHCInBroadcastOctets += pPacketInfo->dataLength;
    }
    else if (pPacketInfo->isMulticast)
    {
        pContext->Statistics.ifHCInMulticastPkts += nCoalescedSegmentsCount;
        pContext->Statistics.ifHCInMulticastOctets += pPacketInfo->dataLength;
    }
    else
    {
        ASSERT(FALSE);
    }
}
