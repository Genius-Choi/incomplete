flatpak_proxy_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  FlatpakProxy *proxy = FLATPAK_PROXY (object);

  switch (prop_id)
    {
    case PROP_DBUS_ADDRESS:
      g_value_set_string (value, proxy->dbus_address);
      break;

    case PROP_SOCKET_PATH:
      g_value_set_string (value, proxy->socket_path);
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}
