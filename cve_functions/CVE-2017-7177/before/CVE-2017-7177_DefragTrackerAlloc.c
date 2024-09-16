DefragTracker *DefragTrackerAlloc(void)
{
    if (!(DEFRAG_CHECK_MEMCAP(sizeof(DefragTracker)))) {
        return NULL;
    }

    (void) SC_ATOMIC_ADD(defrag_memuse, sizeof(DefragTracker));

    DefragTracker *dt = SCMalloc(sizeof(DefragTracker));
    if (unlikely(dt == NULL))
        goto error;

    memset(dt, 0x00, sizeof(DefragTracker));

    SCMutexInit(&dt->lock, NULL);
    SC_ATOMIC_INIT(dt->use_cnt);
    return dt;

error:
    return NULL;
}
