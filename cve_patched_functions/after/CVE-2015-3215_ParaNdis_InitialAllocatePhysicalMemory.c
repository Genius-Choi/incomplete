BOOLEAN ParaNdis_InitialAllocatePhysicalMemory(
    PARANDIS_ADAPTER *pContext,
    tCompletePhysicalAddress *pAddresses)
{
    NdisMAllocateSharedMemory(
        pContext->MiniportHandle,
        pAddresses->size,
        TRUE,
        &pAddresses->Virtual,
        &pAddresses->Physical);
    return pAddresses->Virtual != NULL;
}
