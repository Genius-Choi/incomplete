g_NPN_Write(NPP instance, NPStream *stream, int32_t len, void *buf)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_Write not called from the main thread\n");
	return -1;
  }
  
  if (instance == NULL)
	return -1;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return -1;

  if (stream == NULL)
	return -1;

  D(bugiI("NPN_Write instance=%p, stream=%p, len=%d, buf=%p\n", instance, stream, len, buf));
  npw_plugin_instance_ref(plugin);
  int32_t ret = invoke_NPN_Write(plugin, stream, len, buf);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_Write return: %d\n", ret));
  return ret;
}
