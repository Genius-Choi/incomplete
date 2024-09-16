static TcpStateQueue *StreamTcp3whsFindSynAckByAck(TcpSession *ssn, Packet *p)
{
    uint32_t ack = TCP_GET_SEQ(p);
    uint32_t seq = TCP_GET_ACK(p) - 1;
    TcpStateQueue *q = ssn->queue;

    while (q != NULL) {
        if (seq == q->seq &&
            ack == q->ack) {
            return q;
        }

        q = q->next;
    }

    return NULL;
}
