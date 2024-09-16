static int StreamTcpPacketIsFinShutdownAck(TcpSession *ssn, Packet *p)
{
    TcpStream *stream = NULL, *ostream = NULL;
    uint32_t seq;
    uint32_t ack;

    if (p->flags & PKT_PSEUDO_STREAM_END)
        return 0;
    if (!(ssn->state == TCP_TIME_WAIT || ssn->state == TCP_CLOSE_WAIT || ssn->state == TCP_LAST_ACK))
        return 0;
    if (p->tcph->th_flags != TH_ACK)
        return 0;
    if (p->payload_len != 0)
        return 0;

    if (PKT_IS_TOSERVER(p)) {
        stream = &ssn->client;
        ostream = &ssn->server;
    } else {
        stream = &ssn->server;
        ostream = &ssn->client;
    }

    seq = TCP_GET_SEQ(p);
    ack = TCP_GET_ACK(p);

    SCLogDebug("%"PRIu64", seq %u ack %u stream->next_seq %u ostream->next_seq %u",
            p->pcap_cnt, seq, ack, stream->next_seq, ostream->next_seq);

    if (SEQ_EQ(stream->next_seq + 1, seq) && SEQ_EQ(ack, ostream->next_seq + 1)) {
        return 1;
    }
    return 0;
}
