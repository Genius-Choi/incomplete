is_for_bus (Header *header)
{
  return g_strcmp0 (header->destination, "org.freedesktop.DBus") == 0;
}
