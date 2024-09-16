side_closed (ProxySide *side)
{
  GSocket *socket, *other_socket;
  ProxySide *other_side = get_other_side (side);

  if (side->closed)
    return;

  socket = g_socket_connection_get_socket (side->connection);
  g_socket_close (socket, NULL);
  side->closed = TRUE;

  other_socket = g_socket_connection_get_socket (other_side->connection);
  if (!other_side->closed && other_side->buffers == NULL)
    {
      g_socket_close (other_socket, NULL);
      other_side->closed = TRUE;
    }

  if (other_side->closed)
    {
      g_object_unref (side->client);
    }
  else
    {
      GError *error = NULL;

      if (!g_socket_shutdown (other_socket, TRUE, FALSE, &error))
        {
          g_warning ("Unable to shutdown read side: %s", error->message);
          g_error_free (error);
        }
    }
}
