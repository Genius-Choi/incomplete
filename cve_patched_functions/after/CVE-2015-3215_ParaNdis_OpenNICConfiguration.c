NDIS_HANDLE ParaNdis_OpenNICConfiguration(PARANDIS_ADAPTER *pContext)
{
    NDIS_CONFIGURATION_OBJECT co;
    NDIS_HANDLE cfg;
    NDIS_STATUS status;
    DEBUG_ENTRY(2);
    co.Header.Type = NDIS_OBJECT_TYPE_CONFIGURATION_OBJECT;
    co.Header.Revision = NDIS_CONFIGURATION_OBJECT_REVISION_1;
    co.Header.Size = sizeof(co);
    co.Flags = 0;
    co.NdisHandle = pContext->MiniportHandle;
    status = NdisOpenConfigurationEx(&co, &cfg);
    if (status != NDIS_STATUS_SUCCESS)
        cfg = NULL;
    DEBUG_EXIT_STATUS(status == NDIS_STATUS_SUCCESS ? 2 : 0, status);
    return cfg;
}
