flatpak_proxy_stop (FlatpakProxy *proxy)
{
  unlink (proxy->socket_path);

  g_socket_service_stop (G_SOCKET_SERVICE (proxy));
}
