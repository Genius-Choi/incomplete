static int do_recv_NPP(rpc_message_t *message, void *p_value)
{
  int error;
  NPW_PluginInstance *plugin;

  if ((error = do_recv_NPW_PluginInstance(message, &plugin)) < 0)
	return error;

  *((NPP *)p_value) = plugin ? plugin->instance : NULL;
  return RPC_ERROR_NO_ERROR;
}
