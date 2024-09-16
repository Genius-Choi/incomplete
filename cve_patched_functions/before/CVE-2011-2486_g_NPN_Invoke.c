g_NPN_Invoke(NPP instance, NPObject *npobj, NPIdentifier methodName,
			 const NPVariant *args, uint32_t argCount, NPVariant *result)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_Invoke not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;
	
  if (!npobj || !npobj->_class || !npobj->_class->invoke)
	return false;

  D(bugiI("NPN_Invoke instance=%p, npobj=%p, methodName=%p\n", instance, npobj, methodName));
  print_npvariant_args(args, argCount);
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_Invoke(plugin, npobj, methodName, args, argCount, result);
  npw_plugin_instance_unref(plugin);
  gchar *result_str = string_of_NPVariant(result);
  D(bugiD("NPN_Invoke return: %d (%s)\n", ret, result_str));
  g_free(result_str);
  return ret;
}
