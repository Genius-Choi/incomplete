g_NPN_Status(NPP instance, const char *message)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_Status not called from the main thread\n");
	return;
  }

  PluginInstance *plugin = NULL;
  if (instance)
	plugin = PLUGIN_INSTANCE(instance);

  D(bugiI("NPN_Status instance=%p, message='%s'\n", instance, message));
  npw_plugin_instance_ref(plugin);
  invoke_NPN_Status(plugin, message);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_Status done\n"));
}
