invoke_NPN_CreateObject(PluginInstance *plugin)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection), 0);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_CREATE_OBJECT,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_CreateObject() invoke", error);
	return 0;
  }

  uint32_t npobj_id = 0;
  error = rpc_method_wait_for_reply(g_rpc_connection,
									RPC_TYPE_UINT32, &npobj_id,
									RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_CreateObject() wait for reply", error);
	return 0;
  }

  return npobj_id;
}
