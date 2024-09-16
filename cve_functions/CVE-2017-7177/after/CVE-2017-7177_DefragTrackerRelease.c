void DefragTrackerRelease(DefragTracker *t)
{
    (void) DefragTrackerDecrUsecnt(t);
    SCMutexUnlock(&t->lock);
}
