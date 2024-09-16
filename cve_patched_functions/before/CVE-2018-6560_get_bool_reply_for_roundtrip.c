get_bool_reply_for_roundtrip (FlatpakProxyClient *client, Header *header, gboolean val)
{
  Buffer *ping_buffer = get_ping_buffer_for_header (header);
  GDBusMessage *reply;

  reply = get_bool_reply_for_header (client, header, val);
  g_hash_table_replace (client->rewrite_reply, GINT_TO_POINTER (header->serial), reply);

  return ping_buffer;
}
