NDIS_STATUS ParaNdis_FinishInitialization(PARANDIS_ADAPTER *pContext)
{
    NDIS_STATUS status = NDIS_STATUS_SUCCESS;
    DEBUG_ENTRY(0);

    status = ParaNdis_FinishSpecificInitialization(pContext);
    DPrintf(0, ("[%s] ParaNdis_FinishSpecificInitialization passed, status = %d\n", __FUNCTION__, status));


    if (status == NDIS_STATUS_SUCCESS)
    {
        status = ParaNdis_VirtIONetInit(pContext);
        DPrintf(0, ("[%s] ParaNdis_VirtIONetInit passed, status = %d\n", __FUNCTION__, status));
    }

    if (status == NDIS_STATUS_SUCCESS)
    {
        status = ParaNdis_ConfigureMSIXVectors(pContext);
        DPrintf(0, ("[%s] ParaNdis_VirtIONetInit passed, status = %d\n", __FUNCTION__, status));
    }

    if (status == NDIS_STATUS_SUCCESS)
    {
        status = SetupDPCTarget(pContext);
        DPrintf(0, ("[%s] SetupDPCTarget passed, status = %d\n", __FUNCTION__, status));
    }

    if (status == NDIS_STATUS_SUCCESS && pContext->nPathBundles > 1)
    {
        u16 nPathes = u16(pContext->nPathBundles);
        BOOLEAN sendSuccess = pContext->CXPath.SendControlMessage(VIRTIO_NET_CTRL_MQ, VIRTIO_NET_CTRL_MQ_VQ_PAIR_SET, &nPathes, sizeof(nPathes), NULL, 0, 2);
        if (!sendSuccess)
        {
            DPrintf(0, ("[%s] - Send MQ control message failed\n", __FUNCTION__));
            status = NDIS_STATUS_DEVICE_FAILED;
        }
    }

    pContext->Limits.nReusedRxBuffers = pContext->NetMaxReceiveBuffers / 4 + 1;

    if (status == NDIS_STATUS_SUCCESS)
    {
        ReadLinkState(pContext);
        pContext->bEnableInterruptHandlingDPC = TRUE;
        ParaNdis_SetPowerState(pContext, NdisDeviceStateD0);
        ParaNdis_SynchronizeLinkState(pContext);
        ParaNdis_AddDriverOKStatus(pContext);
        ParaNdis_UpdateMAC(pContext);
    }
    DEBUG_EXIT_STATUS(0, status);
    return status;
}
