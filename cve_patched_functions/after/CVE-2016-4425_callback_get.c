static int callback_get(void *data)
{
    char c;
    callback_data_t *stream = data;

    if(stream->pos >= stream->len) {
        stream->pos = 0;
        stream->len = stream->callback(stream->data, MAX_BUF_LEN, stream->arg);
        if(stream->len == 0 || stream->len == (size_t)-1)
            return EOF;
    }

    c = stream->data[stream->pos];
    stream->pos++;
    return (unsigned char)c;
}
