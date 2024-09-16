g_NPN_InvalidateRect(NPP instance, NPRect *invalidRect)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_InvalidateRect not called from the main thread\n");
	return;
  }

  if (instance == NULL)
	return;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return;

  if (invalidRect == NULL)
	return;

  D(bugiI("NPN_InvalidateRect instance=%p\n", PLUGIN_INSTANCE_NPP(plugin)));
  npw_plugin_instance_ref(plugin);
  invoke_NPN_InvalidateRect(plugin, invalidRect);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_InvalidateRect done\n"));
}
