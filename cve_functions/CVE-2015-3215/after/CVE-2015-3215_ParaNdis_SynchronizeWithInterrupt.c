BOOLEAN ParaNdis_SynchronizeWithInterrupt(
    PARANDIS_ADAPTER *pContext,
    ULONG messageId,
    tSynchronizedProcedure procedure,
    PVOID parameter)
{
    tSynchronizedContext SyncContext;
    NDIS_SYNC_PROC_TYPE syncProc;
#pragma warning (push)
#pragma warning (disable:4152)
    syncProc = (NDIS_SYNC_PROC_TYPE) procedure;
#pragma warning (pop)
    SyncContext.pContext  = pContext;
    SyncContext.Parameter = parameter;
    return NdisMSynchronizeWithInterruptEx(pContext->InterruptHandle, messageId, syncProc, &SyncContext);
}
