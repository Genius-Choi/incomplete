ZSTD_encodeSequences_bmi2(
            void* dst, size_t dstCapacity,
            FSE_CTable const* CTable_MatchLength, BYTE const* mlCodeTable,
            FSE_CTable const* CTable_OffsetBits, BYTE const* ofCodeTable,
            FSE_CTable const* CTable_LitLength, BYTE const* llCodeTable,
            seqDef const* sequences, size_t nbSeq, int longOffsets)
{
    return ZSTD_encodeSequences_body(dst, dstCapacity,
                                    CTable_MatchLength, mlCodeTable,
                                    CTable_OffsetBits, ofCodeTable,
                                    CTable_LitLength, llCodeTable,
                                    sequences, nbSeq, longOffsets);
}
