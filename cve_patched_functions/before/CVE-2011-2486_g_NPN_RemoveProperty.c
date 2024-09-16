g_NPN_RemoveProperty(NPP instance, NPObject *npobj, NPIdentifier propertyName)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_RemoveProperty not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj || !npobj->_class || !npobj->_class->removeProperty)
	return false;

  D(bugiI("NPN_RemoveProperty instance=%p, npobj=%p, propertyName=%p\n", instance, npobj, propertyName));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_RemoveProperty(plugin, npobj, propertyName);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_RemoveProperty return: %d\n", ret));
  return ret;
}
