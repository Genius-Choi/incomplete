static void FUZ_displayMallocStats(mallocCounter_t count)
{
    DISPLAYLEVEL(3, "peak:%6u KB,  nbMallocs:%2u, total:%6u KB \n",
        (U32)(count.peakMalloc >> 10),
        count.nbMalloc,
        (U32)(count.totalMalloc >> 10));
}
