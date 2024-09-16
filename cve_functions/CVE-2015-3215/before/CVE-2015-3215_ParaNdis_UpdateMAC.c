ParaNdis_UpdateMAC(PARANDIS_ADAPTER *pContext)
{
    if (pContext->bCtrlMACAddrSupported)
    {
        pContext->CXPath.SendControlMessage(VIRTIO_NET_CTRL_MAC, VIRTIO_NET_CTRL_MAC_ADDR_SET,
                           pContext->CurrentMacAddress,
                           ETH_LENGTH_OF_ADDRESS,
                           NULL, 0, 4);
    }
}
