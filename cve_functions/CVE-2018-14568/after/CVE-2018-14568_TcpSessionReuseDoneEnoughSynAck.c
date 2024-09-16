static int TcpSessionReuseDoneEnoughSynAck(const Packet *p, const Flow *f, const TcpSession *ssn)
{
    if (FlowGetPacketDirection(f, p) == TOCLIENT) {
        if (ssn == NULL) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p null. No reuse.", p->pcap_cnt, ssn);
            return 0;
        }
        if (SEQ_EQ(ssn->server.isn, TCP_GET_SEQ(p))) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p. Packet SEQ == Stream ISN. Retransmission. Don't reuse.", p->pcap_cnt, ssn);
            return 0;
        }
        if (ssn->state >= TCP_LAST_ACK) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state >= TCP_LAST_ACK (%u). Reuse.", p->pcap_cnt, ssn, ssn->state);
            return 1;
        }
        if (ssn->state == TCP_NONE) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state == TCP_NONE (%u). Reuse.", p->pcap_cnt, ssn, ssn->state);
            return 1;
        }
        if (ssn->state < TCP_LAST_ACK) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state < TCP_LAST_ACK (%u). Don't reuse.", p->pcap_cnt, ssn, ssn->state);
            return 0;
        }

    } else {
        if (ssn == NULL) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p null. Reuse.", p->pcap_cnt, ssn);
            return 1;
        }
        if (ssn->state >= TCP_LAST_ACK) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state >= TCP_LAST_ACK (%u). Reuse.", p->pcap_cnt, ssn, ssn->state);
            return 1;
        }
        if (ssn->state == TCP_NONE) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state == TCP_NONE (%u). Reuse.", p->pcap_cnt, ssn, ssn->state);
            return 1;
        }
        if (ssn->state < TCP_LAST_ACK) {
            SCLogDebug("steam starter packet %"PRIu64", ssn %p state < TCP_LAST_ACK (%u). Don't reuse.", p->pcap_cnt, ssn, ssn->state);
            return 0;
        }
    }

    SCLogDebug("default: how did we get here?");
    return 0;
}
