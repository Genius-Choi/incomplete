bool ParaNdis_DPCWorkBody(PARANDIS_ADAPTER *pContext, ULONG ulMaxPacketsToIndicate)
{
    bool stillRequiresProcessing = false;
    UINT numOfPacketsToIndicate = min(ulMaxPacketsToIndicate, pContext->uNumberOfHandledRXPacketsInDPC);

    DEBUG_ENTRY(5);

    InterlockedIncrement(&pContext->counterDPCInside);

    CPUPathesBundle *pathBundle = nullptr;

    if (pContext->nPathBundles == 1)
    {
        pathBundle = pContext->pPathBundles;
    }
    else
    {
        ULONG procNumber = KeGetCurrentProcessorNumber();
        if (procNumber < pContext->nPathBundles)
        {
            pathBundle = pContext->pPathBundles + procNumber;
        }
    }

    if (pathBundle == nullptr)
    {
        return false;
    }

    if (pContext->bEnableInterruptHandlingDPC)
    {
        bool bDoKick = false;

        InterlockedExchange(&pContext->bDPCInactive, 0);

        if (RxDPCWorkBody(pContext, pathBundle, numOfPacketsToIndicate))
        {
            stillRequiresProcessing = true;
        }

        if (pContext->CXPath.WasInterruptReported() && pContext->bLinkDetectSupported)
        {
            ReadLinkState(pContext);
            ParaNdis_SynchronizeLinkState(pContext);
            pContext->CXPath.ClearInterruptReport();
        }

        if (!stillRequiresProcessing)
        {
            bDoKick = pathBundle->txPath.DoPendingTasks(true);
            if (pathBundle->txPath.RestartQueue(bDoKick))
            {
                stillRequiresProcessing = true;
            }
        }
    }
    InterlockedDecrement(&pContext->counterDPCInside);

    return stillRequiresProcessing;
}
