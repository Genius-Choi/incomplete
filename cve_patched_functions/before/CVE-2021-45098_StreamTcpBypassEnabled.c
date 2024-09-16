int StreamTcpBypassEnabled(void)
{
    return (stream_config.flags & STREAMTCP_INIT_FLAG_BYPASS);
}
