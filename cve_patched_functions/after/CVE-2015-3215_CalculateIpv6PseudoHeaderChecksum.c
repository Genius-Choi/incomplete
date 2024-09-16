static __inline USHORT CalculateIpv6PseudoHeaderChecksum(IPv6Header *pIpHeader, USHORT headerAndPayloadLen)
{
    tIPv6PseudoHeader ipph;
    USHORT checksum;
    ipph.ipph_src[0]  = pIpHeader->ip6_src_address[0];
    ipph.ipph_src[1]  = pIpHeader->ip6_src_address[1];
    ipph.ipph_src[2]  = pIpHeader->ip6_src_address[2];
    ipph.ipph_src[3]  = pIpHeader->ip6_src_address[3];
    ipph.ipph_dest[0] = pIpHeader->ip6_dst_address[0];
    ipph.ipph_dest[1] = pIpHeader->ip6_dst_address[1];
    ipph.ipph_dest[2] = pIpHeader->ip6_dst_address[2];
    ipph.ipph_dest[3] = pIpHeader->ip6_dst_address[3];
    ipph.z1 = ipph.z2 = ipph.z3 = 0;
    ipph.ipph_protocol = pIpHeader->ip6_next_header;
    ipph.ipph_length = swap_short(headerAndPayloadLen);
    checksum = CheckSumCalculatorFlat(&ipph, sizeof(ipph));
    return ~checksum;
}
