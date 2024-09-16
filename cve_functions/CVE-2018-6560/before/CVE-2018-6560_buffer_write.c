buffer_write (ProxySide *side,
              Buffer    *buffer,
              GSocket   *socket)
{
  gssize res;
  GOutputVector v;
  GError *error = NULL;
  GSocketControlMessage **messages = NULL;
  int i, n_messages;
  GList *l;

  if (buffer->send_credentials &&
      G_IS_UNIX_CONNECTION (side->connection))
    {
      g_assert (buffer->size == 1);

      if (!g_unix_connection_send_credentials (G_UNIX_CONNECTION (side->connection),
                                               NULL,
                                               &error))
        {
          if (g_error_matches (error, G_IO_ERROR, G_IO_ERROR_WOULD_BLOCK))
            {
              g_error_free (error);
              return FALSE;
            }

          g_warning ("Error writing credentials to socket: %s", error->message);
          g_error_free (error);

          side_closed (side);
          return FALSE;
        }

      buffer->pos = 1;
      return TRUE;
    }

  n_messages = g_list_length (buffer->control_messages);
  messages = g_new (GSocketControlMessage *, n_messages);
  for (l = buffer->control_messages, i = 0; l != NULL; l = l->next, i++)
    messages[i] = l->data;

  v.buffer = &buffer->data[buffer->pos];
  v.size = buffer->size - buffer->pos;

  res = g_socket_send_message (socket, NULL, &v, 1,
                               messages, n_messages,
                               G_SOCKET_MSG_NONE, NULL, &error);
  g_free (messages);
  if (res < 0 && g_error_matches (error, G_IO_ERROR, G_IO_ERROR_WOULD_BLOCK))
    {
      g_error_free (error);
      return FALSE;
    }

  if (res <= 0)
    {
      if (res < 0)
        {
          g_warning ("Error writing credentials to socket: %s", error->message);
          g_error_free (error);
        }

      side_closed (side);
      return FALSE;
    }

  g_list_free_full (buffer->control_messages, g_object_unref);
  buffer->control_messages = NULL;

  buffer->pos += res;
  return TRUE;
}
