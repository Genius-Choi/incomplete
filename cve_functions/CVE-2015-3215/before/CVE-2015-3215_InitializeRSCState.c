VOID InitializeRSCState(PPARANDIS_ADAPTER pContext)
{
#if PARANDIS_SUPPORT_RSC

    pContext->RSC.bIPv4Enabled = FALSE;
    pContext->RSC.bIPv6Enabled = FALSE;

    if(!pContext->bGuestChecksumSupported)
    {
        DPrintf(0, ("[%s] Guest TSO cannot be enabled without guest checksum\n", __FUNCTION__) );
        return;
    }

    if(pContext->RSC.bIPv4SupportedSW)
    {
        pContext->RSC.bIPv4Enabled =
            pContext->RSC.bIPv4SupportedHW =
                AckFeature(pContext, VIRTIO_NET_F_GUEST_TSO4);
    }
    else
    {
        pContext->RSC.bIPv4SupportedHW =
            VirtIOIsFeatureEnabled(pContext->u32HostFeatures, VIRTIO_NET_F_GUEST_TSO4);
    }

    if(pContext->RSC.bIPv6SupportedSW)
    {
        pContext->RSC.bIPv6Enabled =
            pContext->RSC.bIPv6SupportedHW =
                AckFeature(pContext, VIRTIO_NET_F_GUEST_TSO6);
    }
    else
    {
        pContext->RSC.bIPv6SupportedHW =
            VirtIOIsFeatureEnabled(pContext->u32HostFeatures, VIRTIO_NET_F_GUEST_TSO6);
    }

    pContext->RSC.bHasDynamicConfig = (pContext->RSC.bIPv4Enabled || pContext->RSC.bIPv6Enabled) &&
                                      AckFeature(pContext, VIRTIO_NET_F_CTRL_GUEST_OFFLOADS);

    DPrintf(0, ("[%s] Guest TSO state: IP4=%d, IP6=%d, Dynamic=%d\n", __FUNCTION__,
        pContext->RSC.bIPv4Enabled, pContext->RSC.bIPv6Enabled, pContext->RSC.bHasDynamicConfig) );
#else
    UNREFERENCED_PARAMETER(pContext);
#endif
}
