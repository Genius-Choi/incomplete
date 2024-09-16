uint32_t DefragTrackerSpareQueueGetSize(void)
{
    return DefragTrackerQueueLen(&defragtracker_spare_q);
}
