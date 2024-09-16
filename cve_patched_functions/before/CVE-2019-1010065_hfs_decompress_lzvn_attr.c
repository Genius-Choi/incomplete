static int hfs_decompress_lzvn_attr(char* rawBuf, uint32_t rawSize, uint64_t uncSize, char** dstBuf, uint64_t* dstSize, int* dstBufFree)
{
    if (rawBuf[0] == 0x06) {
        return hfs_decompress_noncompressed_attr(
            rawBuf, rawSize, uncSize, dstBuf, dstSize, dstBufFree);
    }
    
    char* uncBuf = (char *) tsk_malloc((size_t) uncSize);
    *dstSize = lzvn_decode_buffer(uncBuf, uncSize, rawBuf, rawSize);
    *dstBuf = uncBuf;
    *dstBufFree = TRUE;

    return 1;
}
