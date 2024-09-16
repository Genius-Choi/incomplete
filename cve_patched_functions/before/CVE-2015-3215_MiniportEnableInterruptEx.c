static VOID MiniportEnableInterruptEx(IN PVOID MiniportInterruptContext)
{
    DEBUG_ENTRY(0);
    PARANDIS_ADAPTER *pContext = (PARANDIS_ADAPTER *)MiniportInterruptContext;

    for (UINT i = 0; i < pContext->nPathBundles; i++)
    {
        pContext->pPathBundles[i].txPath.EnableInterrupts();
        pContext->pPathBundles[i].rxPath.EnableInterrupts();
    }
    if (pContext->bCXPathCreated)
    {
        pContext->CXPath.EnableInterrupts();
    }
}
