ringbuffer_write(struct ringbuffer *buf, const void* src, size_t srclen)
{
  int remaining;

  if (buf->write_avail == 0 || srclen == 0)
    return 0;

  if (srclen > buf->write_avail)
   srclen = buf->write_avail;

  remaining = buf->size - buf->write_pos;
  if (srclen > remaining)
    {
      memcpy(buf->buffer + buf->write_pos, src, remaining);
      memcpy(buf->buffer, src + remaining, srclen - remaining);
    }
  else
    {
      memcpy(buf->buffer + buf->write_pos, src, srclen);
    }

  buf->write_pos = (buf->write_pos + srclen) % buf->size;

  buf->write_avail -= srclen;
  buf->read_avail += srclen;

  return srclen;
}
