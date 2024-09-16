static int TcpSessionPacketIsStreamStarter(const Packet *p)
{
    if (p->tcph->th_flags == TH_SYN) {
        SCLogDebug("packet %"PRIu64" is a stream starter: %02x", p->pcap_cnt, p->tcph->th_flags);
        return 1;
    }

    if (stream_config.midstream == TRUE || stream_config.async_oneside == TRUE) {
        if (p->tcph->th_flags == (TH_SYN|TH_ACK)) {
            SCLogDebug("packet %"PRIu64" is a midstream stream starter: %02x", p->pcap_cnt, p->tcph->th_flags);
            return 1;
        }
    }
    return 0;
}
