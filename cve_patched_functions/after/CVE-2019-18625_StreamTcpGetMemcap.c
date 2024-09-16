uint64_t StreamTcpGetMemcap(void)
{
    uint64_t memcapcopy = SC_ATOMIC_GET(stream_config.memcap);
    return memcapcopy;
}
