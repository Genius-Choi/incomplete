static CParaNdisAbstractPath *GetPathByMessageId(PARANDIS_ADAPTER *pContext, ULONG MessageId)
{
    CParaNdisAbstractPath *path = NULL;

    UINT bundleId = MessageId / 2;
    if (bundleId >= pContext->nPathBundles)
    {
        path = &pContext->CXPath;
    }
    else if (MessageId % 2)
    {
        path = &(pContext->pPathBundles[bundleId].rxPath);
    }
    else
    {
        path = &(pContext->pPathBundles[bundleId].txPath);
    }

    return path;
}
