static int TcpSessionReuseDoneEnough(const Packet *p, const Flow *f, const TcpSession *ssn)
{
    if (p->tcph->th_flags == TH_SYN) {
        return TcpSessionReuseDoneEnoughSyn(p, f, ssn);
    }

    if (stream_config.midstream == TRUE || stream_config.async_oneside == TRUE) {
        if (p->tcph->th_flags == (TH_SYN|TH_ACK)) {
            return TcpSessionReuseDoneEnoughSynAck(p, f, ssn);
        }
    }

    return 0;
}
