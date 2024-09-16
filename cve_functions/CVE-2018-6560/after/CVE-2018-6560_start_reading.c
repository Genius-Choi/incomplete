start_reading (ProxySide *side)
{
  GSocket *socket;

  socket = g_socket_connection_get_socket (side->connection);
  side->in_source = g_socket_create_source (socket, G_IO_IN, NULL);
  g_source_set_callback (side->in_source, (GSourceFunc) side_in_cb, side, NULL);
  g_source_attach (side->in_source, NULL);
  g_source_unref (side->in_source);
}
