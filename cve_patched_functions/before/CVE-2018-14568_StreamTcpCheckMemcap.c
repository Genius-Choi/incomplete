int StreamTcpCheckMemcap(uint64_t size)
{
    uint64_t memcapcopy = SC_ATOMIC_GET(stream_config.memcap);
    if (memcapcopy == 0 || size + SC_ATOMIC_GET(st_memuse) <= memcapcopy)
        return 1;
    return 0;
}
