static int buffer_get(void *data)
{
    char c;
    buffer_data_t *stream = data;
    if(stream->pos >= stream->len)
      return EOF;

    c = stream->data[stream->pos];
    stream->pos++;
    return (unsigned char)c;
}
