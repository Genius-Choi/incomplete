buffer_ref (Buffer *buffer)
{
  g_assert (buffer->refcount > 0);
  buffer->refcount++;
  return buffer;
}
