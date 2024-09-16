static VOID ParaNdis_DeviceFiltersUpdateAddresses(PARANDIS_ADAPTER *pContext)
{
    u32 u32UniCastEntries = 0;
    pContext->CXPath.SendControlMessage(VIRTIO_NET_CTRL_MAC, VIRTIO_NET_CTRL_MAC_TABLE_SET,
                        &u32UniCastEntries,
                        sizeof(u32UniCastEntries),
                        &pContext->MulticastData,
                        sizeof(pContext->MulticastData.nofMulticastEntries) + pContext->MulticastData.nofMulticastEntries * ETH_LENGTH_OF_ADDRESS,
                        2);
}
