init_side (FlatpakProxyClient *client, ProxySide *side)
{
  side->got_first_byte = (side == &client->bus_side);
  side->client = client;
  side->header_buffer.size = 16;
  side->header_buffer.pos = 0;
  side->current_read_buffer = &side->header_buffer;
  side->expected_replies = g_hash_table_new (g_direct_hash, g_direct_equal);
}
