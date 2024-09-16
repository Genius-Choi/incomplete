g_NPN_GetURLNotify(NPP instance, const char *url, const char *target, void *notifyData)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetURLNotify not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }
	
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  D(bugiI("NPN_GetURLNotify instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_GetURLNotify(plugin, url, target, notifyData);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_GetURLNotify return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
