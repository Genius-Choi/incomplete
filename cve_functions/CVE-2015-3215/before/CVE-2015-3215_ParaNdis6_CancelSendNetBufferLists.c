VOID ParaNdis6_CancelSendNetBufferLists(
    NDIS_HANDLE  miniportAdapterContext,
    PVOID pCancelId)
{
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)miniportAdapterContext;

    DEBUG_ENTRY(0);
    for (UINT i = 0; i < pContext->nPathBundles; i++)
    {
        pContext->pPathBundles[i].txPath.CancelNBLs(pCancelId);
    }
}
