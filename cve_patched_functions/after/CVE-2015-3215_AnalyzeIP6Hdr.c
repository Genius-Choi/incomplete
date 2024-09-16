BOOLEAN AnalyzeIP6Hdr(
    IPv6Header *ip6Hdr,
    ULONG dataLength,
    PULONG ip6HdrLength,
    PUCHAR nextHdr,
    PULONG homeAddrOffset,
    PULONG destAddrOffset)
{
    *homeAddrOffset = 0;
    *destAddrOffset = 0;

    *ip6HdrLength = sizeof(*ip6Hdr);
    if(dataLength < *ip6HdrLength)
        return FALSE;

    *nextHdr = ip6Hdr->ip6_next_header;
    for(;;)
    {
        switch (*nextHdr)
        {
        default:
        case IP6_HDR_NONE:
        case PROTOCOL_TCP:
        case PROTOCOL_UDP:
        case IP6_HDR_FRAGMENT:
            return TRUE;
        case IP6_HDR_DESTINATON:
            {
                IPV6_ADDRESS *homeAddr = NULL;
                ULONG destHdrOffset = *ip6HdrLength;
                if(!SkipIP6ExtensionHeader(ip6Hdr, dataLength, ip6HdrLength, nextHdr))
                    return FALSE;

                if(!AnalyzeIP6DestinationExtension(RtlOffsetToPointer(ip6Hdr, destHdrOffset),
                    *ip6HdrLength - destHdrOffset, &homeAddr))
                    return FALSE;

                *homeAddrOffset = homeAddr ? RtlPointerToOffset(ip6Hdr, homeAddr) : 0;
            }
            break;
        case IP6_HDR_ROUTING:
            {
                IPV6_ADDRESS *destAddr = NULL;
                ULONG routingHdrOffset = *ip6HdrLength;

                if(!SkipIP6ExtensionHeader(ip6Hdr, dataLength, ip6HdrLength, nextHdr))
                    return FALSE;

                if(!AnalyzeIP6RoutingExtension((PIP6_TYPE2_ROUTING_HEADER) RtlOffsetToPointer(ip6Hdr, routingHdrOffset),
                    *ip6HdrLength - routingHdrOffset, &destAddr))
                    return FALSE;

                *destAddrOffset = destAddr ? RtlPointerToOffset(ip6Hdr, destAddr) : 0;
            }
            break;
        case IP6_HDR_HOP_BY_HOP:
        case IP6_HDR_ESP:
        case IP6_HDR_AUTHENTICATION:
        case IP6_HDR_MOBILITY:
            if(!SkipIP6ExtensionHeader(ip6Hdr, dataLength, ip6HdrLength, nextHdr))
                return FALSE;

            break;
        }
    }
}
