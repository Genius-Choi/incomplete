invoke_NPN_GetURL(PluginInstance *plugin, const char *url, const char *target)
{
  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection),
						 NPERR_GENERIC_ERROR);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_GET_URL,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_STRING, url,
								RPC_TYPE_STRING, target,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_GetURL() invoke", error);
	return NPERR_GENERIC_ERROR;
  }

  int32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INT32, &ret, RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_GetURL() wait for reply", error);
	return NPERR_GENERIC_ERROR;
  }

  return ret;
}
