get_error_for_header (FlatpakProxyClient *client, Header *header, const char *error)
{
  GDBusMessage *reply;

  reply = g_dbus_message_new ();
  g_dbus_message_set_message_type (reply, G_DBUS_MESSAGE_TYPE_ERROR);
  g_dbus_message_set_flags (reply, G_DBUS_MESSAGE_FLAGS_NO_REPLY_EXPECTED);
  g_dbus_message_set_reply_serial (reply, header->serial - client->serial_offset);
  g_dbus_message_set_error_name (reply, error);
  g_dbus_message_set_body (reply, g_variant_new ("(s)", error));

  return reply;
}
