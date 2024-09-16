void StreamTcpIncrMemuse(uint64_t size)
{
    (void) SC_ATOMIC_ADD(st_memuse, size);
    SCLogDebug("STREAM %"PRIu64", incr %"PRIu64, StreamTcpMemuseCounter(), size);
    return;
}
