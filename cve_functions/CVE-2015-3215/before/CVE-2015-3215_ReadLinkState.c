static void ReadLinkState(PARANDIS_ADAPTER *pContext)
{
    if (pContext->bLinkDetectSupported)
    {
        USHORT linkStatus = 0;
        VirtIODeviceGet(pContext->IODevice, ETH_LENGTH_OF_ADDRESS, &linkStatus, sizeof(linkStatus));
        pContext->bConnected = !!(linkStatus & VIRTIO_NET_S_LINK_UP);
    }
    else
    {
        pContext->bConnected = TRUE;
    }
}
