NDIS_STATUS ParaNdis_ConfigureMSIXVectors(PARANDIS_ADAPTER *pContext)
{
    NDIS_STATUS status = NDIS_STATUS_RESOURCES;
    UINT i;
    PIO_INTERRUPT_MESSAGE_INFO pTable = pContext->pMSIXInfoTable;
    if (pTable && pTable->MessageCount)
    {
        status = NDIS_STATUS_SUCCESS;
        DPrintf(0, ("[%s] Using MSIX interrupts (%d messages, irql %d)\n",
            __FUNCTION__, pTable->MessageCount, pTable->UnifiedIrql));
        for (i = 0; i < pContext->pMSIXInfoTable->MessageCount; ++i)
        {
            DPrintf(0, ("[%s] MSIX message%d=%08X=>%I64X\n",
                __FUNCTION__, i,
                pTable->MessageInfo[i].MessageData,
                pTable->MessageInfo[i].MessageAddress));
        }
        for (UINT j = 0; j < pContext->nPathBundles && status == NDIS_STATUS_SUCCESS; ++j)
        {
            status = pContext->pPathBundles[j].rxPath.SetupMessageIndex(2 * u16(j) + 1);
            status = pContext->pPathBundles[j].txPath.SetupMessageIndex(2 * u16(j));
        }

        if (pContext->bCXPathCreated)
        {
            pContext->CXPath.SetupMessageIndex(2 * u16(pContext->nPathBundles));
        }
    }

    if (status == NDIS_STATUS_SUCCESS)
    {
        for (UINT j = 0; j < pContext->nPathBundles && status == NDIS_STATUS_SUCCESS; ++j)
        {
            DPrintf(0, ("[%s] Using messages %u/%u for RX/TX queue %u\n", __FUNCTION__, pContext->pPathBundles[j].rxPath.getMessageIndex(),
                pContext->pPathBundles[j].txPath.getMessageIndex(), j));
        }
        if (pContext->bCXPathCreated)
        {
            DPrintf(0, ("[%s] Using message %u for controls\n", __FUNCTION__, pContext->CXPath.getMessageIndex()));
        }
        else
        {
            DPrintf(0, ("[%s] - No control path\n", __FUNCTION__));
        }
    }
    DEBUG_EXIT_STATUS(2, status);
    return status;
}
