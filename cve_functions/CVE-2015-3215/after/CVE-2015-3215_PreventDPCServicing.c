static void PreventDPCServicing(PARANDIS_ADAPTER *pContext)
{
    LONG inside;
    pContext->bEnableInterruptHandlingDPC = FALSE;
    KeMemoryBarrier();
    do
    {
        inside = InterlockedIncrement(&pContext->counterDPCInside);
        InterlockedDecrement(&pContext->counterDPCInside);
        if (inside > 1)
        {
            DPrintf(0, ("[%s] waiting!\n", __FUNCTION__));
            NdisMSleep(20000);
        }
    } while (inside > 1);
}
