static int do_send_NPP(rpc_message_t *message, void *p_value)
{
  NPP instance = (NPP)p_value;
  NPW_PluginInstance *plugin = NULL;
  if (instance)
	plugin = NPW_PLUGIN_INSTANCE(instance);
  return do_send_NPW_PluginInstance(message, plugin);
}
