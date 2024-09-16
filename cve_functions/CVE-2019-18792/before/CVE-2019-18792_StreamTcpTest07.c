static int StreamTcpTest07 (void)
{
    Packet *p = SCMalloc(SIZE_OF_PACKET);
    FAIL_IF(unlikely(p == NULL));
    Flow f;
    ThreadVars tv;
    StreamTcpThread stt;
    TCPHdr tcph;
    uint8_t payload[1] = {0x42};
    PacketQueue pq;

    memset(p, 0, SIZE_OF_PACKET);
    memset(&pq,0,sizeof(PacketQueue));
    memset (&f, 0, sizeof(Flow));
    memset(&tv, 0, sizeof (ThreadVars));
    memset(&stt, 0, sizeof(StreamTcpThread));
    memset(&tcph, 0, sizeof(TCPHdr));

    FLOW_INITIALIZE(&f);
    p->flow = &f;

    StreamTcpUTInit(&stt.ra_ctx);
    stream_config.midstream = TRUE;

    tcph.th_win = htons(5480);
    tcph.th_seq = htonl(10);
    tcph.th_ack = htonl(20);
    tcph.th_flags = TH_ACK|TH_PUSH;
    p->tcph = &tcph;

    p->tcpvars.ts_set = TRUE;
    p->tcpvars.ts_val = 10;
    p->tcpvars.ts_ecr = 11;

    p->payload = payload;
    p->payload_len = 1;

    FAIL_IF(StreamTcpPacket(&tv, p, &stt, &pq) == -1);

    p->tcph->th_seq = htonl(11);
    p->tcph->th_ack = htonl(23);
    p->tcph->th_flags = TH_ACK|TH_PUSH;
    p->flowflags = FLOW_PKT_TOSERVER;

    p->tcpvars.ts_val = 2;

    FAIL_IF(StreamTcpPacket(&tv, p, &stt, &pq) != -1);

    FAIL_IF(((TcpSession *) (p->flow->protoctx))->client.next_seq != 11);

    StreamTcpSessionClear(p->flow->protoctx);
    SCFree(p);
    FLOW_DESTROY(&f);
    StreamTcpUTDeinit(stt.ra_ctx);
    PASS;
}
