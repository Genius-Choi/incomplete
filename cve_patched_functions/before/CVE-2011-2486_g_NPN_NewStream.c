g_NPN_NewStream(NPP instance, NPMIMEType type, const char *target, NPStream **stream)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_NewStream not called from the main thread\n");
	return NPERR_INVALID_INSTANCE_ERROR;
  }

  if (instance == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NPERR_INVALID_INSTANCE_ERROR;

  if (stream == NULL)
	return NPERR_INVALID_PARAM;
  *stream = NULL;

  D(bugiI("NPN_NewStream instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  NPError ret = invoke_NPN_NewStream(plugin, type, target, stream);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_NewStream return: %d [%s]\n", ret, string_of_NPError(ret)));
  return ret;
}
