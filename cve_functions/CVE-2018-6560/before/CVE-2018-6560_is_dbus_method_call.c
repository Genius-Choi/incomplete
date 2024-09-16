is_dbus_method_call (Header *header)
{
  return
    is_for_bus (header) &&
    header->type == G_DBUS_MESSAGE_TYPE_METHOD_CALL &&
    g_strcmp0 (header->interface, "org.freedesktop.DBus") == 0;
}
