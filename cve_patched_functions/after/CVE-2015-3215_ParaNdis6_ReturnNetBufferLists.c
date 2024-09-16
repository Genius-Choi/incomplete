VOID ParaNdis6_ReturnNetBufferLists(
    NDIS_HANDLE miniportAdapterContext,
    PNET_BUFFER_LIST pNBL,
    ULONG returnFlags)
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)miniportAdapterContext;

    UNREFERENCED_PARAMETER(returnFlags);

    DEBUG_ENTRY(5);
    while (pNBL)
    {
        PNET_BUFFER_LIST pTemp = pNBL;
        pRxNetDescriptor pBuffersDescriptor = (pRxNetDescriptor)pNBL->MiniportReserved[0];
        DPrintf(3, ("  Returned NBL of pBuffersDescriptor %p!\n", pBuffersDescriptor));
        pNBL = NET_BUFFER_LIST_NEXT_NBL(pNBL);
        NET_BUFFER_LIST_NEXT_NBL(pTemp) = NULL;
        NdisFreeNetBufferList(pTemp);
        pBuffersDescriptor->Queue->ReuseReceiveBuffer(pContext->ReuseBufferRegular, pBuffersDescriptor);
    }
    ParaMdis_TestPausing(pContext);
}
