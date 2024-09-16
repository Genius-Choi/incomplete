void ParaNdis_FreeRxBufferDescriptor(PARANDIS_ADAPTER *pContext, pRxNetDescriptor p)
{
    ULONG i;
    for(i = 0; i < p->PagesAllocated; i++)
    {
        ParaNdis_FreePhysicalMemory(pContext, &p->PhysicalPages[i]);
    }

    if(p->BufferSGArray) NdisFreeMemory(p->BufferSGArray, 0, 0);
    if(p->PhysicalPages) NdisFreeMemory(p->PhysicalPages, 0, 0);
    NdisFreeMemory(p, 0, 0);
}
