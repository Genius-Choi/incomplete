VOID ParaNdis_QueueRSSDpc(PARANDIS_ADAPTER *pContext, ULONG MessageIndex, PGROUP_AFFINITY pTargetAffinity)
{
#if PARANDIS_SUPPORT_RSS
    NdisMQueueDpcEx(pContext->InterruptHandle, MessageIndex, pTargetAffinity, NULL);
#else
    UNREFERENCED_PARAMETER(pContext);
    UNREFERENCED_PARAMETER(MessageIndex);
    UNREFERENCED_PARAMETER(pTargetAffinity);

    ASSERT(FALSE);
#endif
}
