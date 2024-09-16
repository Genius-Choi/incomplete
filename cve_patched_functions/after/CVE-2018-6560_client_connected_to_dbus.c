client_connected_to_dbus (GObject      *source_object,
                          GAsyncResult *res,
                          gpointer      user_data)
{
  FlatpakProxyClient *client = user_data;
  GSocketConnection *connection;
  GError *error = NULL;
  GIOStream *stream;

  stream = g_dbus_address_get_stream_finish (res, NULL, &error);
  if (stream == NULL)
    {
      g_warning ("Failed to connect to bus: %s", error->message);
      g_object_unref (client);
      return;
    }

  connection = G_SOCKET_CONNECTION (stream);
  g_socket_set_blocking (g_socket_connection_get_socket (connection), FALSE);
  client->bus_side.connection = connection;

  start_reading (&client->client_side);
  start_reading (&client->bus_side);
}
