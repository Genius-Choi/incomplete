g_NPN_HasMethod(NPP instance, NPObject *npobj, NPIdentifier methodName)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_HasMethod not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj || !npobj->_class || !npobj->_class->hasMethod)
	return false;

  D(bugiI("NPN_HasMethod instance=%p, npobj=%p, methodName=%p\n", instance, npobj, methodName));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_HasMethod(plugin, npobj, methodName);
  npw_plugin_instance_unref(plugin);
  D(bugiD("NPN_HasMethod return: %d\n", ret));
  return ret;
}
