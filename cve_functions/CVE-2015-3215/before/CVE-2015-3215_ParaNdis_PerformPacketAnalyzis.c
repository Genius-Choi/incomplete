BOOLEAN ParaNdis_PerformPacketAnalyzis(
#if PARANDIS_SUPPORT_RSS
                            PPARANDIS_RSS_PARAMS RSSParameters,
#endif
                            PNET_PACKET_INFO PacketInfo,
                            PVOID HeadersBuffer,
                            ULONG DataLength)
{
    if(!ParaNdis_AnalyzeReceivedPacket(HeadersBuffer, DataLength, PacketInfo))
        return FALSE;

#if PARANDIS_SUPPORT_RSS
    if(RSSParameters->RSSMode != PARANDIS_RSS_DISABLED)
    {
        ParaNdis6_RSSAnalyzeReceivedPacket(RSSParameters, HeadersBuffer, PacketInfo);
    }
#endif
    return TRUE;
}
