AckFeature(PPARANDIS_ADAPTER pContext, UINT32 Feature)
{
    if (VirtIOIsFeatureEnabled(pContext->u32HostFeatures, Feature))
    {
        VirtIOFeatureEnable(pContext->u32GuestFeatures, Feature);
        return TRUE;
    }
    return FALSE;
}
