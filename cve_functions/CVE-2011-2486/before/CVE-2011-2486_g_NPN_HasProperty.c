g_NPN_HasProperty(NPP instance, NPObject *npobj, NPIdentifier propertyName)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_HasProperty not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj || !npobj->_class || !npobj->_class->hasProperty)
	return false;

  D(bugiI("NPN_HasProperty instance=%p, npobj=%p, propertyName=%p\n", instance, npobj, propertyName));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_HasProperty(plugin, npobj, propertyName);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_HasProperty return: %d\n", ret));
  return ret;
}
