BOOLEAN ParaNdis_IsSendPossible(PARANDIS_ADAPTER *pContext)
{
    BOOLEAN b;
    b =  !pContext->bSurprizeRemoved && pContext->bConnected && pContext->SendState == srsEnabled;
    return b;
}
