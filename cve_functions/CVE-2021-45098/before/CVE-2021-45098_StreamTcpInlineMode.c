int StreamTcpInlineMode(void)
{
    return (stream_config.flags & STREAMTCP_INIT_FLAG_INLINE) ? 1 : 0;
}
