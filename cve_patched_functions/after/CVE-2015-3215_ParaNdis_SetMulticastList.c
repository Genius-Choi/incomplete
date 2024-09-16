NDIS_STATUS ParaNdis_SetMulticastList(
    PARANDIS_ADAPTER *pContext,
    PVOID Buffer,
    ULONG BufferSize,
    PUINT pBytesRead,
    PUINT pBytesNeeded)
{
    NDIS_STATUS status;
    ULONG length = BufferSize;
    if (length > sizeof(pContext->MulticastData.MulticastList))
    {
        status = NDIS_STATUS_MULTICAST_FULL;
        *pBytesNeeded = sizeof(pContext->MulticastData.MulticastList);
    }
    else if (length % ETH_LENGTH_OF_ADDRESS)
    {
        status = NDIS_STATUS_INVALID_LENGTH;
        *pBytesNeeded = (length / ETH_LENGTH_OF_ADDRESS) * ETH_LENGTH_OF_ADDRESS;
    }
    else
    {
        NdisZeroMemory(pContext->MulticastData.MulticastList, sizeof(pContext->MulticastData.MulticastList));
        if (length)
            NdisMoveMemory(pContext->MulticastData.MulticastList, Buffer, length);
        pContext->MulticastData.nofMulticastEntries = length / ETH_LENGTH_OF_ADDRESS;
        DPrintf(1, ("[%s] New multicast list of %d bytes\n", __FUNCTION__, length));
        *pBytesRead = length;
        status = NDIS_STATUS_SUCCESS;
    }
    return status;
}
