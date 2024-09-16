static U32 ZSTD_sufficientBuff(size_t bufferSize1, size_t maxNbSeq1,
                            size_t maxNbLit1,
                            ZSTD_buffered_policy_e buffPol2,
                            ZSTD_compressionParameters cParams2,
                            U64 pledgedSrcSize)
{
    size_t const windowSize2 = MAX(1, (size_t)MIN(((U64)1 << cParams2.windowLog), pledgedSrcSize));
    size_t const blockSize2 = MIN(ZSTD_BLOCKSIZE_MAX, windowSize2);
    size_t const maxNbSeq2 = blockSize2 / ((cParams2.searchLength == 3) ? 3 : 4);
    size_t const maxNbLit2 = blockSize2;
    size_t const neededBufferSize2 = (buffPol2==ZSTDb_buffered) ? windowSize2 + blockSize2 : 0;
    DEBUGLOG(4, "ZSTD_sufficientBuff: is neededBufferSize2=%u <= bufferSize1=%u",
                (U32)neededBufferSize2, (U32)bufferSize1);
    DEBUGLOG(4, "ZSTD_sufficientBuff: is maxNbSeq2=%u <= maxNbSeq1=%u",
                (U32)maxNbSeq2, (U32)maxNbSeq1);
    DEBUGLOG(4, "ZSTD_sufficientBuff: is maxNbLit2=%u <= maxNbLit1=%u",
                (U32)maxNbLit2, (U32)maxNbLit1);
    return (maxNbLit2 <= maxNbLit1)
         & (maxNbSeq2 <= maxNbSeq1)
         & (neededBufferSize2 <= bufferSize1);
}
