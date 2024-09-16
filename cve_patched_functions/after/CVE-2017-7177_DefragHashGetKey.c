static inline uint32_t DefragHashGetKey(Packet *p)
{
    uint32_t key;

    if (p->ip4h != NULL) {
        DefragHashKey4 dhk;
        if (p->src.addr_data32[0] > p->dst.addr_data32[0]) {
            dhk.src = p->src.addr_data32[0];
            dhk.dst = p->dst.addr_data32[0];
        } else {
            dhk.src = p->dst.addr_data32[0];
            dhk.dst = p->src.addr_data32[0];
        }
        dhk.id = (uint32_t)IPV4_GET_IPID(p);
        dhk.vlan_id[0] = p->vlan_id[0];
        dhk.vlan_id[1] = p->vlan_id[1];

        uint32_t hash = hashword(dhk.u32, 4, defrag_config.hash_rand);
        key = hash % defrag_config.hash_size;
    } else if (p->ip6h != NULL) {
        DefragHashKey6 dhk;
        if (DefragHashRawAddressIPv6GtU32(p->src.addr_data32, p->dst.addr_data32)) {
            dhk.src[0] = p->src.addr_data32[0];
            dhk.src[1] = p->src.addr_data32[1];
            dhk.src[2] = p->src.addr_data32[2];
            dhk.src[3] = p->src.addr_data32[3];
            dhk.dst[0] = p->dst.addr_data32[0];
            dhk.dst[1] = p->dst.addr_data32[1];
            dhk.dst[2] = p->dst.addr_data32[2];
            dhk.dst[3] = p->dst.addr_data32[3];
        } else {
            dhk.src[0] = p->dst.addr_data32[0];
            dhk.src[1] = p->dst.addr_data32[1];
            dhk.src[2] = p->dst.addr_data32[2];
            dhk.src[3] = p->dst.addr_data32[3];
            dhk.dst[0] = p->src.addr_data32[0];
            dhk.dst[1] = p->src.addr_data32[1];
            dhk.dst[2] = p->src.addr_data32[2];
            dhk.dst[3] = p->src.addr_data32[3];
        }
        dhk.id = IPV6_EXTHDR_GET_FH_ID(p);
        dhk.vlan_id[0] = p->vlan_id[0];
        dhk.vlan_id[1] = p->vlan_id[1];

        uint32_t hash = hashword(dhk.u32, 10, defrag_config.hash_rand);
        key = hash % defrag_config.hash_size;
    } else
        key = 0;

    return key;
}
