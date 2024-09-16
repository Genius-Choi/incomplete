static void plugin_instance_finalize(PluginInstance *plugin)
{
  if (plugin->browser_toplevel) {
	g_object_unref(plugin->browser_toplevel);
	plugin->browser_toplevel = NULL;
  }
  if (plugin->instance) {
	free(plugin->instance);
	plugin->instance = NULL;
  }
}
