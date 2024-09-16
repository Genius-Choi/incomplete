flatpak_proxy_finalize (GObject *object)
{
  FlatpakProxy *proxy = FLATPAK_PROXY (object);

  if (g_socket_service_is_active (G_SOCKET_SERVICE (proxy)))
    unlink (proxy->socket_path);

  g_assert (proxy->clients == NULL);

  g_hash_table_destroy (proxy->policy);
  g_hash_table_destroy (proxy->wildcard_policy);
  g_hash_table_destroy (proxy->filters);

  g_free (proxy->socket_path);
  g_free (proxy->dbus_address);

  G_OBJECT_CLASS (flatpak_proxy_parent_class)->finalize (object);
}
