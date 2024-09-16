uint64_t StreamTcpMemuseCounter(void)
{
    uint64_t memusecopy = SC_ATOMIC_GET(st_memuse);
    return memusecopy;
}
