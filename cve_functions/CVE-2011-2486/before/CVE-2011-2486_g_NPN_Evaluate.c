g_NPN_Evaluate(NPP instance, NPObject *npobj, NPString *script, NPVariant *result)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_Evaluate not called from the main thread\n");
	return false;
  }

  if (instance == NULL)
	return false;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return false;

  if (!npobj)
	return false;

  if (!script || !script->UTF8Length || !script->UTF8Characters)
	return true; // nothing to evaluate

  D(bugiI("NPN_Evaluate instance=%p, npobj=%p\n", instance, npobj));
  npw_plugin_instance_ref(plugin);
  bool ret = invoke_NPN_Evaluate(plugin, npobj, script, result);
  npw_plugin_instance_unref(plugin);
  gchar *result_str = string_of_NPVariant(result);
  D(bugiD("NPN_Evaluate return: %d (%s)\n", ret, result_str));
  g_free(result_str);
  return ret;
}
