static inline int DefragTrackerCompare(DefragTracker *t, Packet *p)
{
    uint32_t id;
    if (PKT_IS_IPV4(p)) {
        id = (uint32_t)IPV4_GET_IPID(p);
    } else {
        id = IPV6_EXTHDR_GET_FH_ID(p);
    }

    return CMP_DEFRAGTRACKER(t, p, id);
}
