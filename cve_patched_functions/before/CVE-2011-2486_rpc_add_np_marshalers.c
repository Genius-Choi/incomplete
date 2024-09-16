int rpc_add_np_marshalers(rpc_connection_t *connection)
{
  return rpc_connection_add_message_descriptors(connection, message_descs, sizeof(message_descs) / sizeof(message_descs[0]));
}
