CCHAR ParaNdis_GetScalingDataForPacket(PARANDIS_ADAPTER *pContext, PNET_PACKET_INFO pPacketInfo, PPROCESSOR_NUMBER pTargetProcessor)
{
#if PARANDIS_SUPPORT_RSS
    return ParaNdis6_RSSGetScalingDataForPacket(&pContext->RSSParameters, pPacketInfo, pTargetProcessor);
#else
    UNREFERENCED_PARAMETER(pContext);
    UNREFERENCED_PARAMETER(pPacketInfo);
    UNREFERENCED_PARAMETER(pTargetProcessor);

    return PARANDIS_RECEIVE_QUEUE_UNCLASSIFIED;
#endif
}
