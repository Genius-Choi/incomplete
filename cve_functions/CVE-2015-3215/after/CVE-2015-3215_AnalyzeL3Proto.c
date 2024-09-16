VOID AnalyzeL3Proto(
    USHORT L3Proto,
    PNET_PACKET_INFO packetInfo)
{
    packetInfo->isIP4 = (L3Proto == RtlUshortByteSwap(ETH_PROTO_IP4));
    packetInfo->isIP6 = (L3Proto == RtlUshortByteSwap(ETH_PROTO_IP6));
}
