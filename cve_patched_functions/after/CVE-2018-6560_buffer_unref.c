buffer_unref (Buffer *buffer)
{
  g_assert (buffer->refcount > 0);
  buffer->refcount--;

  if (buffer->refcount == 0)
    {
      g_list_free_full (buffer->control_messages, g_object_unref);
      g_free (buffer);
    }
}
