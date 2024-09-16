header_free (Header *header)
{
  if (header->buffer)
    buffer_unref (header->buffer);
  g_free (header);
}
