static size_t ZSTD_NCountCost(unsigned const* count, unsigned const max,
                              size_t const nbSeq, unsigned const FSELog)
{
    BYTE wksp[FSE_NCOUNTBOUND];
    S16 norm[MaxSeq + 1];
    const U32 tableLog = FSE_optimalTableLog(FSELog, nbSeq, max);
    CHECK_F(FSE_normalizeCount(norm, tableLog, count, nbSeq, max));
    return FSE_writeNCount(wksp, sizeof(wksp), norm, max, tableLog);
}
