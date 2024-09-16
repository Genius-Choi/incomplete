ringbuffer_free(struct ringbuffer *buf, bool content_only)
{
  if (!buf)
    return;

  free(buf->buffer);

  if (content_only)
    memset(buf, 0, sizeof(struct ringbuffer));
  else
    free(buf);
}
