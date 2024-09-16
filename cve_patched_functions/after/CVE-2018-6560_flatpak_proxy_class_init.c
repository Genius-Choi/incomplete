flatpak_proxy_class_init (FlatpakProxyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GSocketServiceClass *socket_service_class = G_SOCKET_SERVICE_CLASS (klass);

  object_class->get_property = flatpak_proxy_get_property;
  object_class->set_property = flatpak_proxy_set_property;
  object_class->finalize = flatpak_proxy_finalize;

  socket_service_class->incoming = flatpak_proxy_incoming;

  g_object_class_install_property (object_class,
                                   PROP_DBUS_ADDRESS,
                                   g_param_spec_string ("dbus-address",
                                                        "",
                                                        "",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class,
                                   PROP_SOCKET_PATH,
                                   g_param_spec_string ("socket-path",
                                                        "",
                                                        "",
                                                        NULL,
                                                        G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY));

}
