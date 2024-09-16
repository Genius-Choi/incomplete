g_NPN_GetProperty(NPP instance, NPObject *npobj, NPIdentifier propertyName,
				  NPVariant *result)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetProperty not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj || !npobj->_class || !npobj->_class->getProperty)
	return false;

  D(bugiI("NPN_GetProperty instance=%p, npobj=%p, propertyName=%p\n", instance, npobj, propertyName));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_GetProperty(plugin, npobj, propertyName, result);
  npw_plugin_instance_unref(plugin);
  gchar *result_str = string_of_NPVariant(result);
  D(bugiD("NPN_GetProperty return: %d (%s)\n", ret, result_str));
  g_free(result_str);
  return ret;
}
