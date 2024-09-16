message_is_name_owner_changed (FlatpakProxyClient *client, Header *header)
{
  if (header->type == G_DBUS_MESSAGE_TYPE_SIGNAL &&
      g_strcmp0 (header->sender, "org.freedesktop.DBus") == 0 &&
      g_strcmp0 (header->interface, "org.freedesktop.DBus") == 0 &&
      g_strcmp0 (header->member, "NameOwnerChanged") == 0)
    return TRUE;
  return FALSE;
}
