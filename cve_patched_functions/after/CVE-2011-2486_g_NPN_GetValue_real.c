g_NPN_GetValue_real(NPP instance, NPNVariable variable, void *value)
{
  PluginInstance *plugin = NULL;
  if (instance)
	plugin = PLUGIN_INSTANCE(instance);

  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_GetValue(plugin, variable, value);
  npw_plugin_instance_unref(plugin);
  return ret;
}
