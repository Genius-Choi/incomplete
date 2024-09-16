static NPError g_NPP_Destroy_Now(PluginInstance *plugin, NPSavedData **save)
{
  D(bug("g_NPP_Destroy_Now\n"));

  NPSavedData *save_area = NULL;
  NPError ret = g_NPP_Destroy(PLUGIN_INSTANCE_NPP(plugin), &save_area);
  if (save) {
	*save = save_area;
  } else if (save_area) {
	npw_printf("WARNING: NPP_Destroy returned save_area, but it was ignored\n");
    if (save_area->buf)
      NPN_MemFree(save_area->buf);
    NPN_MemFree(save_area);
  }

  rpc_connection_unref(g_rpc_connection);
  return ret;
}
