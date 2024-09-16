flatpak_proxy_client_new (FlatpakProxy *proxy, GSocketConnection *connection)
{
  FlatpakProxyClient *client;

  g_socket_set_blocking (g_socket_connection_get_socket (connection), FALSE);

  client = g_object_new (FLATPAK_TYPE_PROXY_CLIENT, NULL);
  client->proxy = g_object_ref (proxy);
  client->client_side.connection = g_object_ref (connection);

  proxy->clients = g_list_prepend (proxy->clients, client);

  return client;
}
