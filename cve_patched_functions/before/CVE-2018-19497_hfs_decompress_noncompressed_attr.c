static int hfs_decompress_noncompressed_attr(char* rawBuf, uint32_t rawSize, uint64_t uncSize, char** dstBuf, uint64_t* dstSize, int* dstBufFree) {
    if (tsk_verbose)
        tsk_fprintf(stderr,
            "%s: Leading byte, 0x%02x, indicates that the data is not really compressed.\n"
            "%s:  Loading the default DATA attribute.", __func__, rawBuf[0], __func__);

    *dstBuf = rawBuf + 1;  // + 1 indicator byte
    *dstSize = uncSize;
    *dstBufFree = FALSE;
    return 1;
}
