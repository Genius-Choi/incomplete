void ParaNdis_RestoreDeviceConfigurationAfterReset(
    PARANDIS_ADAPTER *pContext)
{
    ParaNdis_ConfigureMSIXVectors(pContext);
}
