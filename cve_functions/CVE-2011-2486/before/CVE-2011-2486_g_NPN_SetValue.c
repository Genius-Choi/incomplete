g_NPN_SetValue(NPP instance, NPPVariable variable, void *value)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_SetValue not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }

  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  D(bugiI("NPN_SetValue instance=%p, variable=%d [%s]\n", instance, variable, string_of_NPPVariable(variable)));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_SetValue(plugin, variable, value);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_SetValue return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
