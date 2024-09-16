get_error_for_roundtrip (FlatpakProxyClient *client, Header *header, const char *error_name)
{
  Buffer *ping_buffer = get_ping_buffer_for_header (header);
  GDBusMessage *reply;

  reply = get_error_for_header (client, header, error_name);
  g_hash_table_replace (client->rewrite_reply, GINT_TO_POINTER (header->serial), reply);
  return ping_buffer;
}
