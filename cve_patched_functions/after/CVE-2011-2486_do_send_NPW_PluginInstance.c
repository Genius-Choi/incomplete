static int do_send_NPW_PluginInstance(rpc_message_t *message, void *p_value)
{
  NPW_PluginInstance *plugin = (NPW_PluginInstance *)p_value;
  uint32_t instance_id = 0;
  if (plugin)
	instance_id = plugin->instance_id;
  return rpc_message_send_uint32(message, instance_id);
}
