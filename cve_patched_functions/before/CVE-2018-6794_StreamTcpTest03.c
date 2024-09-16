static int StreamTcpTest03 (void)
{
    Packet *p = SCMalloc(SIZE_OF_PACKET);
    if (unlikely(p == NULL))
        return 0;
    Flow f;
    ThreadVars tv;
    StreamTcpThread stt;
    TCPHdr tcph;
    memset(p, 0, SIZE_OF_PACKET);
    PacketQueue pq;
    memset(&pq,0,sizeof(PacketQueue));
    memset (&f, 0, sizeof(Flow));
    memset(&tv, 0, sizeof (ThreadVars));
    memset(&stt, 0, sizeof (StreamTcpThread));
    memset(&tcph, 0, sizeof (TCPHdr));
    FLOW_INITIALIZE(&f);
    p->flow = &f;

    StreamTcpUTInit(&stt.ra_ctx);

    tcph.th_win = htons(5480);
    tcph.th_seq = htonl(10);
    tcph.th_ack = htonl(20);
    tcph.th_flags = TH_SYN|TH_ACK;
    p->tcph = &tcph;
    int ret = 0;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1)
        goto end;

    p->tcph->th_seq = htonl(20);
    p->tcph->th_ack = htonl(11);
    p->tcph->th_flags = TH_ACK;
    p->flowflags = FLOW_PKT_TOSERVER;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1)
        goto end;

    p->tcph->th_seq = htonl(19);
    p->tcph->th_ack = htonl(11);
    p->tcph->th_flags = TH_ACK|TH_PUSH;
    p->flowflags = FLOW_PKT_TOSERVER;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1)
        goto end;

    if (stream_config.midstream != TRUE) {
        ret = 1;
        goto end;
    }
    if (((TcpSession *)(p->flow->protoctx))->state != TCP_ESTABLISHED)
        goto end;

    if (((TcpSession *)(p->flow->protoctx))->client.next_seq != 20 &&
            ((TcpSession *)(p->flow->protoctx))->server.next_seq != 11)
        goto end;

    StreamTcpSessionClear(p->flow->protoctx);

    ret = 1;
end:
    SCFree(p);
    FLOW_DESTROY(&f);
    StreamTcpUTDeinit(stt.ra_ctx);
    return ret;
}
