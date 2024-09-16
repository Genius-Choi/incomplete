message_to_buffer (GDBusMessage *message)
{
  Buffer *buffer;
  guchar *blob;
  gsize blob_size;

  blob = g_dbus_message_to_blob (message, &blob_size, G_DBUS_CAPABILITY_FLAGS_NONE, NULL);
  buffer = buffer_new (blob_size, NULL);
  memcpy (buffer->data, blob, blob_size);
  g_free (blob);

  return buffer;
}
