buffer_read (ProxySide *side,
             Buffer    *buffer,
             GSocket   *socket)
{
  gssize res;
  GInputVector v;
  GError *error = NULL;
  GSocketControlMessage **messages;
  int num_messages, i;

  if (side->extra_input_data)
    {
      gsize extra_size;
      const guchar *extra_bytes = g_bytes_get_data (side->extra_input_data, &extra_size);

      res = MIN (extra_size, buffer->size - buffer->pos);
      memcpy (&buffer->data[buffer->pos], extra_bytes, res);

      if (res < extra_size)
        {
          side->extra_input_data =
            g_bytes_new_with_free_func (extra_bytes + res,
                                        extra_size - res,
                                        (GDestroyNotify) g_bytes_unref,
                                        side->extra_input_data);
        }
      else
        {
          g_clear_pointer (&side->extra_input_data, g_bytes_unref);
        }
    }
  else
    {
      int flags = 0;
      v.buffer = &buffer->data[buffer->pos];
      v.size = buffer->size - buffer->pos;

      res = g_socket_receive_message (socket, NULL, &v, 1,
                                      &messages,
                                      &num_messages,
                                      &flags, NULL, &error);
      if (res < 0 && g_error_matches (error, G_IO_ERROR, G_IO_ERROR_WOULD_BLOCK))
        {
          g_error_free (error);
          return FALSE;
        }

      if (res <= 0)
        {
          if (res != 0)
            {
              g_debug ("Error reading from socket: %s", error->message);
              g_error_free (error);
            }

          side_closed (side);
          return FALSE;
        }

      for (i = 0; i < num_messages; i++)
        buffer->control_messages = g_list_append (buffer->control_messages, messages[i]);

      g_free (messages);
    }

  buffer->pos += res;
  return TRUE;
}
