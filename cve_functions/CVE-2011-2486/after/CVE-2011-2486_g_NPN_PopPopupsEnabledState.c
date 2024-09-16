g_NPN_PopPopupsEnabledState(NPP instance)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_PophPopupsEnabledState not called from the main thread\n");
	return;
  }

  if (instance == NULL)
	return;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return;

  D(bugiI("NPN_PopPopupsEnabledState instance=%p\n", instance));
  npw_plugin_instance_ref(plugin);
  invoke_NPN_PopPopupsEnabledState(plugin);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_PopPopupsEnabledState done\n"));
}
