invoke_NPN_SetValue(PluginInstance *plugin, NPPVariable variable, void *value)
{
  switch (rpc_type_of_NPPVariable(variable)) {
  case RPC_TYPE_BOOLEAN:
	break;
  default:
	D(bug("WARNING: unhandled variable %d in NPN_SetValue()\n", variable));
	return NPERR_INVALID_PARAM;
  }

  npw_return_val_if_fail(rpc_method_invoke_possible(g_rpc_connection),
						 NPERR_GENERIC_ERROR);

  int error = rpc_method_invoke(g_rpc_connection,
								RPC_METHOD_NPN_SET_VALUE,
								RPC_TYPE_NPW_PLUGIN_INSTANCE, plugin,
								RPC_TYPE_UINT32, variable,
								RPC_TYPE_BOOLEAN, (uint32_t)(uintptr_t)value,
								RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_SetValue() invoke", error);
	return NPERR_GENERIC_ERROR;
  }

  int32_t ret;
  error = rpc_method_wait_for_reply(g_rpc_connection, RPC_TYPE_INT32, &ret, RPC_TYPE_INVALID);
  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPN_SetValue() wait for reply", error);
	return NPERR_GENERIC_ERROR;
  }
  return ret;
}
