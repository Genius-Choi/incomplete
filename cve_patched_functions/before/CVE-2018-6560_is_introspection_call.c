is_introspection_call (Header *header)
{
  return
    header->type == G_DBUS_MESSAGE_TYPE_METHOD_CALL &&
    g_strcmp0 (header->interface, "org.freedesktop.DBus.Introspectable") == 0;
}
