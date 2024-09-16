VOID ParaMdis_TestPausing(PARANDIS_ADAPTER *pContext)
{
    ONPAUSECOMPLETEPROC callback = nullptr;

    if (pContext->m_upstreamPacketPending == 0)
    {
        CNdisPassiveWriteAutoLock tLock(pContext->m_PauseLock);

        if (pContext->m_upstreamPacketPending == 0 && (pContext->ReceiveState == srsPausing || pContext->ReceivePauseCompletionProc))
        {
            callback = pContext->ReceivePauseCompletionProc;
            pContext->ReceiveState = srsDisabled;
            pContext->ReceivePauseCompletionProc = NULL;
            ParaNdis_DebugHistory(pContext, hopInternalReceivePause, NULL, 0, 0, 0);
        }
    }

    if (callback) callback(pContext);
}
