UpdateReceiveFailStatistics(PPARANDIS_ADAPTER pContext, UINT nCoalescedSegmentsCount)
{
    pContext->Statistics.ifInErrors++;
    pContext->Statistics.ifInDiscards += nCoalescedSegmentsCount;
}
