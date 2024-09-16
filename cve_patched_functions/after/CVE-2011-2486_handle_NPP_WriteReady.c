static int handle_NPP_WriteReady(rpc_connection_t *connection)
{
  D(bug("handle_NPP_WriteReady\n"));

  PluginInstance *plugin;
  NPStream *stream;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
								  RPC_TYPE_NP_STREAM, &stream,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_WriteReady() get args", error);
	return error;
  }

  int32_t ret = g_NPP_WriteReady(PLUGIN_INSTANCE_NPP(plugin), stream);

  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
