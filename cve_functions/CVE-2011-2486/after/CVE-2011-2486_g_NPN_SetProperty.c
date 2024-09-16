g_NPN_SetProperty(NPP instance, NPObject *npobj, NPIdentifier propertyName,
				  const NPVariant *value)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_SetProperty not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj || !npobj->_class || !npobj->_class->setProperty)
	return false;

  D(bugiI("NPN_SetProperty instance=%p, npobj=%p, propertyName=%p\n", instance, npobj, propertyName));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_SetProperty(plugin, npobj, propertyName, value);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_SetProperty return: %d\n", ret));
  return ret;
}
