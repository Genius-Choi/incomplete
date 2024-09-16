static int do_recv_NPW_PluginInstance(rpc_message_t *message, void *p_value)
{
  int error;
  uint32_t instance_id;

  if ((error = rpc_message_recv_uint32(message, &instance_id)) < 0)
	return error;

  NPW_PluginInstance *plugin = id_lookup(instance_id);
  if (instance_id && plugin == NULL)
	npw_printf("ERROR: no valid NPP -> PluginInstance mapping found\n");
  else if (plugin && plugin->instance == NULL)
	npw_printf("ERROR: no valid PluginInstance -> NPP mapping found\n");
  else if (plugin && !npw_plugin_instance_is_valid(plugin))
	npw_printf("ERROR: received PluginInstance was invalidated earlier\n");
  *((NPW_PluginInstance **)p_value) = plugin;
  return RPC_ERROR_NO_ERROR;
}
