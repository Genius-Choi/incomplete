SetDeviceMAC(PPARANDIS_ADAPTER pContext, PUCHAR pDeviceMAC)
{
    if(pContext->bCfgMACAddrSupported && !pContext->bCtrlMACAddrSupported)
    {
        VirtIODeviceSet(pContext->IODevice, 0, pDeviceMAC, ETH_LENGTH_OF_ADDRESS);
    }
}
