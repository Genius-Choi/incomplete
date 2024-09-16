static int64_t http_seek(URLContext *h, int64_t off, int whence)
{
    return http_seek_internal(h, off, whence, 0);
}
