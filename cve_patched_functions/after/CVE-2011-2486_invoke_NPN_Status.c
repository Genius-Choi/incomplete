invoke_NPN_Status(PluginInstance *plugin, const char *message)
{
  npw_return_if_fail(rpc_method_invoke_possible(g_rpc_connection));

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_STATUS,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_STRING, message,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_Status() invoke", error);
	return;
  }

  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_Status() wait for reply", error);
	return;
  }
}
