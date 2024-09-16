DefragGetTracker(ThreadVars *tv, DecodeThreadVars *dtv, Packet *p)
{
    return DefragGetTrackerFromHash(p);
}
