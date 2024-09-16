PVOID ParaNdis_AllocateMemoryRaw(NDIS_HANDLE MiniportHandle, ULONG ulRequiredSize)
{
    return NdisAllocateMemoryWithTagPriority(
            MiniportHandle,
            ulRequiredSize,
            PARANDIS_MEMORY_TAG,
            NormalPoolPriority);
}
