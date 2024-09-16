VOID NBLSetRSCInfo(PPARANDIS_ADAPTER pContext, PNET_BUFFER_LIST pNBL,
                   PNET_PACKET_INFO PacketInfo, UINT nCoalescedSegments)
{
    NDIS_TCP_IP_CHECKSUM_NET_BUFFER_LIST_INFO qCSInfo;

    qCSInfo.Value = NULL;
    qCSInfo.Receive.IpChecksumSucceeded = TRUE;
    qCSInfo.Receive.IpChecksumValueInvalid = TRUE;
    qCSInfo.Receive.TcpChecksumSucceeded = TRUE;
    qCSInfo.Receive.TcpChecksumValueInvalid = TRUE;
    NET_BUFFER_LIST_INFO(pNBL, TcpIpChecksumNetBufferListInfo) = qCSInfo.Value;

    NET_BUFFER_LIST_COALESCED_SEG_COUNT(pNBL) = (USHORT) nCoalescedSegments;
    NET_BUFFER_LIST_DUP_ACK_COUNT(pNBL) = 0;

    NdisInterlockedAddLargeStatistic(&pContext->RSC.Statistics.CoalescedOctets, PacketInfo->L2PayloadLen);
    NdisInterlockedAddLargeStatistic(&pContext->RSC.Statistics.CoalesceEvents, 1);
    NdisInterlockedAddLargeStatistic(&pContext->RSC.Statistics.CoalescedPkts, nCoalescedSegments);
}
