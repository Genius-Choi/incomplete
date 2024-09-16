static inline int StreamTcpValidateChecksum(Packet *p)
{
    int ret = 1;

    if (p->flags & PKT_IGNORE_CHECKSUM)
        return ret;

    if (p->level4_comp_csum == -1) {
        if (PKT_IS_IPV4(p)) {
            p->level4_comp_csum = TCPChecksum(p->ip4h->s_ip_addrs,
                                              (uint16_t *)p->tcph,
                                              (p->payload_len +
                                                  TCP_GET_HLEN(p)),
                                              p->tcph->th_sum);
        } else if (PKT_IS_IPV6(p)) {
            p->level4_comp_csum = TCPV6Checksum(p->ip6h->s_ip6_addrs,
                                                (uint16_t *)p->tcph,
                                                (p->payload_len +
                                                    TCP_GET_HLEN(p)),
                                                p->tcph->th_sum);
        }
    }

    if (p->level4_comp_csum != 0) {
        ret = 0;
        if (p->livedev) {
            (void) SC_ATOMIC_ADD(p->livedev->invalid_checksums, 1);
        } else if (p->pcap_cnt) {
            PcapIncreaseInvalidChecksum();
        }
    }

    return ret;
}
