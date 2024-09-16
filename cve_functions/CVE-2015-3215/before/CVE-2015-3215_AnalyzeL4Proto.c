VOID AnalyzeL4Proto(
    UCHAR l4Protocol,
    PNET_PACKET_INFO packetInfo)
{
    packetInfo->isTCP = (l4Protocol == PROTOCOL_TCP);
    packetInfo->isUDP = (l4Protocol == PROTOCOL_UDP);
}
