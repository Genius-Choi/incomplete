static void ParaNdis_RemoveDriverOKStatus(PPARANDIS_ADAPTER pContext )
{
    VirtIODeviceRemoveStatus(pContext->IODevice, VIRTIO_CONFIG_S_DRIVER_OK);

    KeMemoryBarrier();

    pContext->bDeviceInitialized = FALSE;
}
