static int http_read_stream_all(URLContext *h, uint8_t *buf, int size)
{
    int pos = 0;
    while (pos < size) {
        int len = http_read_stream(h, buf + pos, size - pos);
        if (len < 0)
            return len;
        pos += len;
    }
    return pos;
}
