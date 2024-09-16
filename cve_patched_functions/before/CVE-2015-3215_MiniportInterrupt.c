static BOOLEAN MiniportInterrupt(
    IN PVOID  MiniportInterruptContext,
    OUT PBOOLEAN  QueueDefaultInterruptDpc,
    OUT PULONG  TargetProcessors
    )
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)MiniportInterruptContext;
    ULONG status = VirtIODeviceISR(pContext->IODevice);

    *TargetProcessors = 0;

    if((status == 0) ||
       (status == VIRTIO_NET_INVALID_INTERRUPT_STATUS))
    {
        *QueueDefaultInterruptDpc = FALSE;
        return FALSE;
    }

    PARADNIS_STORE_LAST_INTERRUPT_TIMESTAMP(pContext);

    if(!pContext->bDeviceInitialized) {
        *QueueDefaultInterruptDpc = FALSE;
        return TRUE;
    }

    for (UINT i = 0; i < pContext->nPathBundles; i++)
    {
        pContext->pPathBundles[i].txPath.DisableInterrupts();
        pContext->pPathBundles[i].rxPath.DisableInterrupts();
    }
    if (pContext->bCXPathCreated)
    {
        pContext->CXPath.DisableInterrupts();
    }
    
    *QueueDefaultInterruptDpc = TRUE;
    pContext->ulIrqReceived += 1;

    return true;
}
