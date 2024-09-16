NDIS_STATUS ParaNdis6_SendPauseRestart(
    PARANDIS_ADAPTER *pContext,
    BOOLEAN bPause,
    ONPAUSECOMPLETEPROC Callback
)
{
    NDIS_STATUS status = NDIS_STATUS_SUCCESS;
    DEBUG_ENTRY(4);
    if (bPause)
    {
        ParaNdis_DebugHistory(pContext, hopInternalSendPause, NULL, 1, 0, 0);
        if (pContext->SendState == srsEnabled)
        {
            {
                CNdisPassiveWriteAutoLock tLock(pContext->m_PauseLock);

                pContext->SendState = srsPausing;
                pContext->SendPauseCompletionProc = Callback;
            }

            for (UINT i = 0; i < pContext->nPathBundles; i++)
            {
                if (!pContext->pPathBundles[i].txPath.Pause())
                {
                    status = NDIS_STATUS_PENDING;
                }
            }

            if (status == NDIS_STATUS_SUCCESS)
            {
                pContext->SendState = srsDisabled;
            }
        }
        if (status == NDIS_STATUS_SUCCESS)
        {
            ParaNdis_DebugHistory(pContext, hopInternalSendPause, NULL, 0, 0, 0);
        }
    }
    else
    {
        pContext->SendState = srsEnabled;
        ParaNdis_DebugHistory(pContext, hopInternalSendResume, NULL, 0, 0, 0);
    }
    return status;
}
