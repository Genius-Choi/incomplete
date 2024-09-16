static int handle_NPP_Write(rpc_connection_t *connection)
{
  D(bug("handle_NPP_Write\n"));

  PluginInstance *plugin;
  NPStream *stream;
  unsigned char *buf;
  int32_t offset, len;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
								  RPC_TYPE_NP_STREAM, &stream,
								  RPC_TYPE_INT32, &offset,
								  RPC_TYPE_ARRAY, RPC_TYPE_CHAR, &len, &buf,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_Write() get args", error);
	return error;
  }

  int32_t ret = g_NPP_Write(PLUGIN_INSTANCE_NPP(plugin), stream, offset, len, buf);

  if (buf)
	free(buf);

  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
