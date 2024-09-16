int StreamTcpInlineDropInvalid(void)
{
    return ((stream_config.flags & STREAMTCP_INIT_FLAG_INLINE)
            && (stream_config.flags & STREAMTCP_INIT_FLAG_DROP_INVALID));
}
