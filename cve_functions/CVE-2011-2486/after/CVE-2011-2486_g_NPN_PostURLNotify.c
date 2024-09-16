g_NPN_PostURLNotify(NPP instance, const char *url, const char *target, uint32_t len, const char *buf, NPBool file, void *notifyData)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_PostURLNotify not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }
	
  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  D(bugiI("NPN_PostURLNotify instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_PostURLNotify(plugin, url, target, len, buf, file, notifyData);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_PostURLNotify return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
