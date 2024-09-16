PVOID ParaNdis_AllocateMemory(PARANDIS_ADAPTER *pContext, ULONG ulRequiredSize)
{
    return ParaNdis_AllocateMemoryRaw(pContext->MiniportHandle, ulRequiredSize);
}
