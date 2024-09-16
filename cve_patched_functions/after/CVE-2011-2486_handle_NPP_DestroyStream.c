static int handle_NPP_DestroyStream(rpc_connection_t *connection)
{
  D(bug("handle_NPP_DestroyStream\n"));

  PluginInstance *plugin;
  NPStream *stream;
  int32_t reason;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
								  RPC_TYPE_NP_STREAM, &stream,
								  RPC_TYPE_INT32, &reason,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_DestroyStream() get args", error);
	return error;
  }

  NPError ret = g_NPP_DestroyStream(PLUGIN_INSTANCE_NPP(plugin), stream, reason);
  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
