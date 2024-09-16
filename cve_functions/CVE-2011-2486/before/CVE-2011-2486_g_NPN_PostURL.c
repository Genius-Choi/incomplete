g_NPN_PostURL(NPP instance, const char *url, const char *target, uint32_t len, const char *buf, NPBool file)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_PostURL not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }

  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  D(bugiI("NPN_PostURL instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_PostURL(plugin, url, target, len, buf, file);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_PostURL return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
