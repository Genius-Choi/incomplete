queue_fake_message (FlatpakProxyClient *client, GDBusMessage *message, ExpectedReplyType reply_type)
{
  Buffer *buffer;

  client->last_serial++;
  client->serial_offset++;
  g_dbus_message_set_serial (message, client->last_serial);
  buffer = message_to_buffer (message);
  g_object_unref (message);

  queue_outgoing_buffer (&client->bus_side, buffer);
  queue_expected_reply (&client->client_side, client->last_serial, reply_type);
}
