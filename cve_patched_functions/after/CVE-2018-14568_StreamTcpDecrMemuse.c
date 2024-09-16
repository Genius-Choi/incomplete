void StreamTcpDecrMemuse(uint64_t size)
{
#ifdef DEBUG_VALIDATION
    uint64_t presize = SC_ATOMIC_GET(st_memuse);
    if (RunmodeIsUnittests()) {
        BUG_ON(presize > UINT_MAX);
    }
#endif

    (void) SC_ATOMIC_SUB(st_memuse, size);

#ifdef DEBUG_VALIDATION
    if (RunmodeIsUnittests()) {
        uint64_t postsize = SC_ATOMIC_GET(st_memuse);
        BUG_ON(postsize > presize);
    }
#endif
    SCLogDebug("STREAM %"PRIu64", decr %"PRIu64, StreamTcpMemuseCounter(), size);
    return;
}
