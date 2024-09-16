static int handle_NPP_HandleEvent(rpc_connection_t *connection)
{
  D(bug("handle_NPP_HandleEvent\n"));

  PluginInstance *plugin;
  NPEvent event;
  int error = rpc_method_get_args(connection,
								  RPC_TYPE_NPW_PLUGIN_INSTANCE, &plugin,
								  RPC_TYPE_NP_EVENT, &event,
								  RPC_TYPE_INVALID);

  if (error != RPC_ERROR_NO_ERROR) {
	npw_perror("NPP_HandleEvent() get args", error);
	return error;
  }

  event.xany.display = x_display;
  int16_t ret = g_NPP_HandleEvent(PLUGIN_INSTANCE_NPP(plugin), &event);

  return rpc_method_send_reply(connection, RPC_TYPE_INT32, ret, RPC_TYPE_INVALID);
}
