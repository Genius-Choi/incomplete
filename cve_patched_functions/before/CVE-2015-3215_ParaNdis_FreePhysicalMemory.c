VOID ParaNdis_FreePhysicalMemory(
    PARANDIS_ADAPTER *pContext,
    tCompletePhysicalAddress *pAddresses)
{

    NdisMFreeSharedMemory(
        pContext->MiniportHandle,
        pAddresses->size,
        TRUE,
        pAddresses->Virtual,
        pAddresses->Physical);
}
