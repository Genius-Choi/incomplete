static inline uint32_t StreamTcpResetGetMaxAck(TcpStream *stream, uint32_t seq)
{
    uint32_t ack = seq;

    if (stream->seg_list_tail != NULL) {
        if (SEQ_GT((stream->seg_list_tail->seq + TCP_SEG_LEN(stream->seg_list_tail)), ack))
        {
            ack = stream->seg_list_tail->seq + TCP_SEG_LEN(stream->seg_list_tail);
        }
    }

    SCReturnUInt(ack);
}
