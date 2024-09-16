g_NPN_PushPopupsEnabledState(NPP instance, NPBool enabled)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_PushPopupsEnabledState not called from the main thread\n");
	return;
  }

  if (instance == NULL)
	return;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return;

  D(bugiI("NPN_PushPopupsEnabledState instance=%p, enabled=%d\n", instance, enabled));
  npw_plugin_instance_ref(plugin);
  invoke_NPN_PushPopupsEnabledState(plugin, enabled);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_PushPopupsEnabledState done\n"));
}
