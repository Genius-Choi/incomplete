queue_outgoing_buffer (ProxySide *side, Buffer *buffer)
{
  if (side->out_source == NULL)
    {
      GSocket *socket;

      socket = g_socket_connection_get_socket (side->connection);
      side->out_source = g_socket_create_source (socket, G_IO_OUT, NULL);
      g_source_set_callback (side->out_source, (GSourceFunc) side_out_cb, side, NULL);
      g_source_attach (side->out_source, NULL);
      g_source_unref (side->out_source);
    }

  buffer->pos = 0;
  side->buffers = g_list_append (side->buffers, buffer);
}
