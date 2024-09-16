BOOLEAN SkipIP6ExtensionHeader(
    IPv6Header *ip6Hdr,
    ULONG dataLength,
    PULONG ip6HdrLength,
    PUCHAR nextHdr)
{
    IPv6ExtHeader* ip6ExtHdr;

    if (*ip6HdrLength + sizeof(*ip6ExtHdr) > dataLength)
        return FALSE;

    ip6ExtHdr = (IPv6ExtHeader *)RtlOffsetToPointer(ip6Hdr, *ip6HdrLength);
    *nextHdr = ip6ExtHdr->ip6ext_next_header;
    *ip6HdrLength += (ip6ExtHdr->ip6ext_hdr_len + 1) * IP6_EXT_HDR_GRANULARITY;
    return TRUE;
}
