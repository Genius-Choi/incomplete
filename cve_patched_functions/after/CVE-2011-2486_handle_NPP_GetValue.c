static int handle_NPP_GetValue(rpc_connection_t *connection)
{
  D(bug("handle_NPP_GetValue\n"));

  int error;
  PluginInstance *plugin;
  int32_t variable;

  error = rpc_method_get_args(connection,
							  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
							  RPC_TYPE_INT32, &variable,
							  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_printf("ERROR: could not get NPP_GetValue variable\n");
	return error;
  }

  NPError ret = NPERR_GENERIC_ERROR;
  int variable_type = rpc_type_of_NPPVariable(variable);

  switch (variable_type) {
  case RPC_TYPE_STRING:
	{
	  char *str = NULL;
	  ret = g_NPP_GetValue(PLUGIN_INSTANCE_NPP(plugin), variable, (void *)&str);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_STRING, str, RPC_TYPE_INVALID);
	}
  case RPC_TYPE_INT32:
	{
	  uint32_t n = 0;
	  ret = g_NPP_GetValue(PLUGIN_INSTANCE_NPP(plugin), variable, (void *)&n);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INT32, n, RPC_TYPE_INVALID);
	}
  case RPC_TYPE_BOOLEAN:
	{
	  NPBool b = FALSE;
	  ret = g_NPP_GetValue(PLUGIN_INSTANCE_NPP(plugin), variable, (void *)&b);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_BOOLEAN, b, RPC_TYPE_INVALID);
	}
  case RPC_TYPE_NP_OBJECT:
	{
	  NPObject *npobj = NULL;
	  ret = g_NPP_GetValue(PLUGIN_INSTANCE_NPP(plugin), variable, (void *)&npobj);
	  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_NP_OBJECT, npobj, RPC_TYPE_INVALID);
	}
  }

  abort();
}
