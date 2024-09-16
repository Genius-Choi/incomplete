size_t ZSTD_endStream(ZSTD_CStream* zcs, ZSTD_outBuffer* output)
{
    ZSTD_inBuffer input = { NULL, 0, 0 };
    if (output->pos > output->size) return ERROR(GENERIC);
    CHECK_F( ZSTD_compressStream_generic(zcs, output, &input, ZSTD_e_end) );
    {   size_t const lastBlockSize = zcs->frameEnded ? 0 : ZSTD_BLOCKHEADERSIZE;
        size_t const checksumSize = zcs->frameEnded ? 0 : zcs->appliedParams.fParams.checksumFlag * 4;
        size_t const toFlush = zcs->outBuffContentSize - zcs->outBuffFlushedSize + lastBlockSize + checksumSize;
        DEBUGLOG(4, "ZSTD_endStream : remaining to flush : %u", (U32)toFlush);
        return toFlush;
    }
}
