static BOOLEAN MiniportMSIInterrupt(
    IN PVOID  MiniportInterruptContext,
    IN ULONG  MessageId,
    OUT PBOOLEAN  QueueDefaultInterruptDpc,
    OUT PULONG  TargetProcessors
    )
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)MiniportInterruptContext;

    PARADNIS_STORE_LAST_INTERRUPT_TIMESTAMP(pContext);

    *TargetProcessors = 0;

    if (!pContext->bDeviceInitialized) {
        *QueueDefaultInterruptDpc = FALSE;
        return TRUE;
    }

    CParaNdisAbstractPath *path = GetPathByMessageId(pContext, MessageId);

    path->DisableInterrupts();
    path->ReportInterrupt();


#if NDIS_SUPPORT_NDIS620
    if (path->DPCAffinity.Mask)
    {
        NdisMQueueDpcEx(pContext->InterruptHandle, MessageId, &path->DPCAffinity, NULL);
        *QueueDefaultInterruptDpc = FALSE;
    }
    else
    {
        *QueueDefaultInterruptDpc = TRUE;
    }
#else
    *TargetProcessors = (ULONG)path->DPCTargetProcessor;
    *QueueDefaultInterruptDpc = TRUE;
#endif

    pContext->ulIrqReceived += 1;
    return true;
}
