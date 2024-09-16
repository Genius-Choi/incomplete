g_NPN_GetURL(NPP instance, const char *url, const char *target)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetURL not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }

  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  D(bugiI("NPN_GetURL instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_GetURL(plugin, url, target);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_GetURL return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
