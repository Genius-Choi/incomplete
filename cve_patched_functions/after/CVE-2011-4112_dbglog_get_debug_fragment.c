u32 dbglog_get_debug_fragment(s8 *datap, u32 len, u32 limit)
{
    s32 *buffer;
    u32 count;
    u32 numargs;
    u32 length;
    u32 fraglen;

    count = fraglen = 0;
    buffer = (s32 *)datap;
    length = (limit >> 2);

    if (len <= limit) {
        fraglen = len;
    } else {
        while (count < length) {
            numargs = DBGLOG_GET_NUMARGS(buffer[count]);
            fraglen = (count << 2);
            count += numargs + 1;
        }
    }

    return fraglen;
}
