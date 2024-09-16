void ParaNdis_DeleteQueue(PARANDIS_ADAPTER *pContext, struct virtqueue **ppq, tCompletePhysicalAddress *ppa)
{
    if (*ppq) VirtIODeviceDeleteQueue(*ppq, NULL);
    *ppq = NULL;
    if (ppa->Virtual) ParaNdis_FreePhysicalMemory(pContext, ppa);
    RtlZeroMemory(ppa, sizeof(*ppa));
}
