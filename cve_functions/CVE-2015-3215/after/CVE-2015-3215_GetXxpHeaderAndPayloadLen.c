static __inline USHORT GetXxpHeaderAndPayloadLen(IPHeader *pIpHeader, tTcpIpPacketParsingResult res)
{
    if (res.ipStatus == ppresIPV4)
    {
        USHORT headerLength = IP_HEADER_LENGTH(&pIpHeader->v4);
        USHORT len = swap_short(pIpHeader->v4.ip_length);
        return len - headerLength;          
    }
    if (res.ipStatus == ppresIPV6)
    {
        USHORT fullLength = swap_short(pIpHeader->v6.ip6_payload_len);
        return fullLength + sizeof(pIpHeader->v6) - (USHORT)res.ipHeaderSize;
    }
    return 0;
}
