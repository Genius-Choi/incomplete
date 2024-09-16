BOOLEAN RxDPCWorkBody(PARANDIS_ADAPTER *pContext, CPUPathesBundle *pathBundle, ULONG nPacketsToIndicate)
{
    BOOLEAN res = FALSE;
    BOOLEAN bMoreDataInRing;

    PNET_BUFFER_LIST indicate, indicateTail;
    ULONG nIndicate;

    CCHAR CurrCpuReceiveQueue = GetReceiveQueueForCurrentCPU(pContext);

    do
    {
        indicate = nullptr;
        indicateTail = nullptr;
        nIndicate = 0;

        {
            CNdisDispatchReadAutoLock tLock(pContext->m_PauseLock);

            pathBundle->rxPath.ProcessRxRing(CurrCpuReceiveQueue);

            res |= ProcessReceiveQueue(pContext, &nPacketsToIndicate, PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED,
                &indicate, &indicateTail, &nIndicate);

            if(CurrCpuReceiveQueue != PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED)
            {
                res |= ProcessReceiveQueue(pContext, &nPacketsToIndicate, CurrCpuReceiveQueue,
                    &indicate, &indicateTail, &nIndicate);
            }

            bMoreDataInRing = pathBundle->rxPath.RestartQueue();
        }

        if (nIndicate)
        {
            NdisMIndicateReceiveNetBufferLists(pContext->MiniportHandle,
                indicate,
                0,
                nIndicate,
                0);
        }

        ParaMdis_TestPausing(pContext);

    } while (bMoreDataInRing);

    return res;
}
