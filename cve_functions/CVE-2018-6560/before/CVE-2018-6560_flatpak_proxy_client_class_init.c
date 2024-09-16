flatpak_proxy_client_class_init (FlatpakProxyClientClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = flatpak_proxy_client_finalize;
}
