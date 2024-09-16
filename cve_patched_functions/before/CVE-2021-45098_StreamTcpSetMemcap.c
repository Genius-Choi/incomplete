int StreamTcpSetMemcap(uint64_t size)
{
    if (size == 0 || (uint64_t)SC_ATOMIC_GET(st_memuse) < size) {
        SC_ATOMIC_SET(stream_config.memcap, size);
        return 1;
    }

    return 0;
}
