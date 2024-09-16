void StreamTcpDetectLogFlush(ThreadVars *tv, StreamTcpThread *stt, Flow *f, Packet *p, PacketQueue *pq)
{
    TcpSession *ssn = f->protoctx;
    ssn->client.flags |= STREAMTCP_STREAM_FLAG_TRIGGER_RAW;
    ssn->server.flags |= STREAMTCP_STREAM_FLAG_TRIGGER_RAW;
    bool ts = PKT_IS_TOSERVER(p) ? true : false;
    ts ^= StreamTcpInlineMode();
    StreamTcpPseudoPacketCreateDetectLogFlush(tv, stt, p, ssn, pq, ts^0);
    StreamTcpPseudoPacketCreateDetectLogFlush(tv, stt, p, ssn, pq, ts^1);
}
