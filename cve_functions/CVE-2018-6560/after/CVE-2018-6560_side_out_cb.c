side_out_cb (GSocket *socket, GIOCondition condition, gpointer user_data)
{
  ProxySide *side = user_data;
  FlatpakProxyClient *client = side->client;
  gboolean retval = G_SOURCE_CONTINUE;

  g_object_ref (client);

  while (side->buffers)
    {
      Buffer *buffer = side->buffers->data;

      if (buffer_write (side, buffer, socket))
        {
          if (buffer->pos == buffer->size)
            {
              side->buffers = g_list_delete_link (side->buffers, side->buffers);
              buffer_unref (buffer);
            }
        }
      else
        {
          break;
        }
    }

  if (side->buffers == NULL)
    {
      ProxySide *other_side = get_other_side (side);

      side->out_source = NULL;
      retval = G_SOURCE_REMOVE;

      if (other_side->closed)
        side_closed (side);
    }

  g_object_unref (client);

  return retval;
}
