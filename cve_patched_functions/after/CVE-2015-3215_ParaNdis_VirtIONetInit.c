static NDIS_STATUS ParaNdis_VirtIONetInit(PARANDIS_ADAPTER *pContext)
{
    NDIS_STATUS status = NDIS_STATUS_RESOURCES;
    DEBUG_ENTRY(0);
    UINT i;
    USHORT nVirtIOQueues = pContext->nHardwareQueues * 2 + 2;

    pContext->nPathBundles = DetermineQueueNumber(pContext);
    if (pContext->nPathBundles == 0)
    {
        DPrintf(0, ("[%s] - no I/O pathes\n", __FUNCTION__));
        return NDIS_STATUS_RESOURCES;
    }

    if (nVirtIOQueues > pContext->IODevice->maxQueues)
    {
        ULONG IODeviceSize = VirtIODeviceSizeRequired(nVirtIOQueues);

        NdisFreeMemoryWithTagPriority(pContext->MiniportHandle, pContext->IODevice, PARANDIS_MEMORY_TAG);
        pContext->IODevice = (VirtIODevice *)NdisAllocateMemoryWithTagPriority(
            pContext->MiniportHandle,
            IODeviceSize,
            PARANDIS_MEMORY_TAG,
            NormalPoolPriority);
        if (pContext->IODevice == nullptr)
        {
            DPrintf(0, ("[%s] - IODevice allocation failed\n", __FUNCTION__));
            return NDIS_STATUS_RESOURCES;
        }

        VirtIODeviceInitialize(pContext->IODevice, pContext->AdapterResources.ulIOAddress, IODeviceSize);
        VirtIODeviceSetMSIXUsed(pContext->IODevice, pContext->bUsingMSIX ? true : false);
        DPrintf(0, ("[%s] %u queues' slots reallocated for size %lu\n", __FUNCTION__, pContext->IODevice->maxQueues, IODeviceSize));
    }

    new (&pContext->CXPath, PLACEMENT_NEW) CParaNdisCX();
    pContext->bCXPathAllocated = TRUE;
    if (!pContext->CXPath.Create(pContext, 2 * pContext->nHardwareQueues))
    {
        DPrintf(0, ("[%s] The Control vQueue does not work!\n", __FUNCTION__));
        pContext->bHasHardwareFilters = FALSE;
        pContext->bCtrlMACAddrSupported = FALSE;
    }
    else
    {
        pContext->bCXPathCreated = TRUE;
    }

    pContext->pPathBundles = (CPUPathesBundle *)NdisAllocateMemoryWithTagPriority(pContext->MiniportHandle, pContext->nPathBundles * sizeof(*pContext->pPathBundles),
        PARANDIS_MEMORY_TAG, NormalPoolPriority);
    if (pContext->pPathBundles == nullptr)
    {
        DPrintf(0, ("[%s] Path bundles allocation failed\n", __FUNCTION__));
        return status;
    }

    for (i = 0; i < pContext->nPathBundles; i++)
    {
        new (pContext->pPathBundles + i, PLACEMENT_NEW) CPUPathesBundle();

        if (!pContext->pPathBundles[i].rxPath.Create(pContext, i * 2))
        {
            DPrintf(0, ("%s: CParaNdisRX creation failed\n", __FUNCTION__));
            return status;
        }
        pContext->pPathBundles[i].rxCreated = true;

        if (!pContext->pPathBundles[i].txPath.Create(pContext, i * 2 + 1))
        {
            DPrintf(0, ("%s: CParaNdisTX creation failed\n", __FUNCTION__));
            return status;
        }
        pContext->pPathBundles[i].txCreated = true;
    }

    if (pContext->bCXPathCreated)
    {
        pContext->pPathBundles[0].cxPath = &pContext->CXPath;
    }

    status = NDIS_STATUS_SUCCESS;

    return status;
}
