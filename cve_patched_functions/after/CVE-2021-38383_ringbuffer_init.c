ringbuffer_init(struct ringbuffer *buf, size_t size)
{
  memset(buf, 0, sizeof(struct ringbuffer));

  CHECK_NULL(L_MISC, buf->buffer = malloc(size));
  buf->size = size;
  buf->write_avail = size;
  return 0;
}
