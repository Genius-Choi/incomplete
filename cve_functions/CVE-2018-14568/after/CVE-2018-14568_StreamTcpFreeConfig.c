void StreamTcpFreeConfig(char quiet)
{
    SC_ATOMIC_DESTROY(stream_config.memcap);
    SC_ATOMIC_DESTROY(stream_config.reassembly_memcap);

    StreamTcpReassembleFree(quiet);

    SCMutexLock(&ssn_pool_mutex);
    if (ssn_pool != NULL) {
        PoolThreadFree(ssn_pool);
        ssn_pool = NULL;
    }
    SCMutexUnlock(&ssn_pool_mutex);
    SCMutexDestroy(&ssn_pool_mutex);

    SCLogDebug("ssn_pool_cnt %"PRIu64"", ssn_pool_cnt);
}
