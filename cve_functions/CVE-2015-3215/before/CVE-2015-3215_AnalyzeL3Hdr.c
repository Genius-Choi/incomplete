BOOLEAN AnalyzeL3Hdr(
    PNET_PACKET_INFO packetInfo)
{
    if(packetInfo->isIP4)
    {
        IPv4Header *ip4Hdr = (IPv4Header *) RtlOffsetToPointer(packetInfo->headersBuffer, packetInfo->L2HdrLen);

        if(packetInfo->dataLength < packetInfo->L2HdrLen + sizeof(*ip4Hdr))
            return FALSE;

        packetInfo->L3HdrLen = IP_HEADER_LENGTH(ip4Hdr);
        if ((packetInfo->L3HdrLen < sizeof(*ip4Hdr)) ||
            (packetInfo->dataLength < packetInfo->L2HdrLen + packetInfo->L3HdrLen))
            return FALSE;

        if(IP_HEADER_VERSION(ip4Hdr) != 4)
            return FALSE;

        packetInfo->isFragment = IP_HEADER_IS_FRAGMENT(ip4Hdr);

        if(!packetInfo->isFragment)
        {
            AnalyzeL4Proto(ip4Hdr->ip_protocol, packetInfo);
        }
    }
    else if(packetInfo->isIP6)
    {
        ULONG homeAddrOffset, destAddrOffset;
        UCHAR l4Proto;

        IPv6Header *ip6Hdr = (IPv6Header *) RtlOffsetToPointer(packetInfo->headersBuffer, packetInfo->L2HdrLen);

        if(IP6_HEADER_VERSION(ip6Hdr) != 6)
            return FALSE;

        if(!AnalyzeIP6Hdr(ip6Hdr, packetInfo->L2PayloadLen,
            &packetInfo->L3HdrLen, &l4Proto, &homeAddrOffset, &destAddrOffset))
            return FALSE;

        if (packetInfo->L3HdrLen > MAX_SUPPORTED_IPV6_HEADERS)
            return FALSE;

        packetInfo->ip6HomeAddrOffset = (homeAddrOffset) ? packetInfo->L2HdrLen + homeAddrOffset : 0;
        packetInfo->ip6DestAddrOffset = (destAddrOffset) ? packetInfo->L2HdrLen + destAddrOffset : 0;

        packetInfo->isFragment = (l4Proto == IP6_HDR_FRAGMENT);

        if(!packetInfo->isFragment)
        {
            AnalyzeL4Proto(l4Proto, packetInfo);
        }
    }

    return TRUE;
}
