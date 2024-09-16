flatpak_proxy_incoming (GSocketService    *service,
                        GSocketConnection *connection,
                        GObject           *source_object)
{
  FlatpakProxy *proxy = FLATPAK_PROXY (service);
  FlatpakProxyClient *client;

  client = flatpak_proxy_client_new (proxy, connection);

  g_dbus_address_get_stream (proxy->dbus_address,
                             NULL,
                             client_connected_to_dbus,
                             client);
  return TRUE;
}
