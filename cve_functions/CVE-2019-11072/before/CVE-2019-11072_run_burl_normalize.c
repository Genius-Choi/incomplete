static void run_burl_normalize (buffer *psrc, buffer *ptmp, int flags, int line, const char *in, size_t in_len, const char *out, size_t out_len) {
    int qs;
    buffer_copy_string_len(psrc, in, in_len);
    qs = burl_normalize(psrc, ptmp, flags);
    if (out_len == (size_t)-2) {
        if (-2 == qs) return;
        fprintf(stderr,
                "%s.%d: %s('%s') failed: expected error, got '%s'\n",
                __FILE__, line, __func__+4, in, psrc->ptr);
    }
    else {
        if (buffer_is_equal_string(psrc, out, out_len)) return;
        fprintf(stderr,
                "%s.%d: %s('%s') failed: expected '%s', got '%s'\n",
                __FILE__, line, __func__+4, in, out, psrc->ptr);
    }
    fflush(stderr);
    abort();
}
