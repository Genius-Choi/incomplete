invoke_NPN_Write(PluginInstance *plugin, NPStream *stream, int32_t len, void *buf)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), -1);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_WRITE,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_NP_STREAM, stream,
								RPC_TYPE_ARRAY, RPC_TYPE_CHAR, len, buf,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_Write() invoke", error);
	return -1;
  }

  int32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_INT32, &ret,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_Write() wait for reply", error);
	return -1;
  }

  return ret;
}
