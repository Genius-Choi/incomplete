VOID NBLSetRSSInfo(PPARANDIS_ADAPTER pContext, PNET_BUFFER_LIST pNBL, PNET_PACKET_INFO PacketInfo)
{
#if PARANDIS_SUPPORT_RSS
    CNdisRWLockState lockState;

    pContext->RSSParameters.rwLock.acquireReadDpr(lockState);
    if(pContext->RSSParameters.RSSMode != PARANDIS_RSS_DISABLED)
    {
        NET_BUFFER_LIST_SET_HASH_TYPE    (pNBL, PacketInfo->RSSHash.Type);
        NET_BUFFER_LIST_SET_HASH_FUNCTION(pNBL, PacketInfo->RSSHash.Function);
        NET_BUFFER_LIST_SET_HASH_VALUE   (pNBL, PacketInfo->RSSHash.Value);
    }
    pContext->RSSParameters.rwLock.releaseDpr(lockState);
#else
    UNREFERENCED_PARAMETER(pContext);
    UNREFERENCED_PARAMETER(pNBL);
    UNREFERENCED_PARAMETER(PacketInfo);
#endif
}
