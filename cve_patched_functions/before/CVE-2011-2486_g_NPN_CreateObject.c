g_NPN_CreateObject(NPP instance, NPClass *class)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_CreateObject not called from the main thread\n");
	return NULL;
  }
  
  if (instance == NULL)
	return NULL;

  PluginInstance *plugin = PLUGIN_INSTANCE(instance);
  if (plugin == NULL)
	return NULL;

  if (class == NULL)
	return NULL;

  D(bugiI("NPN_CreateObject\n"));
  npw_plugin_instance_ref(plugin);
  uint32_t npobj_id = invoke_NPN_CreateObject(plugin);
  npw_plugin_instance_unref(plugin);
  assert(npobj_id != 0);
  NPObject *npobj = npobject_new(npobj_id, instance, class);
  D(bugiD("NPN_CreateObject return: %p (refcount: %d)\n", npobj, npobj->referenceCount));
  return npobj;
}
