static gboolean delayed_destroys_process_cb(gpointer user_data)
{
  while (g_delayed_destroys != NULL) {
	PluginInstance *plugin = (PluginInstance *)g_delayed_destroys->data;
	g_delayed_destroys = g_list_delete_link(g_delayed_destroys,
											g_delayed_destroys);
	g_NPP_Destroy_Now(plugin, NULL);
  }

  if (g_delayed_destroys)
	return TRUE;

  if (g_delayed_destroys_id) {
	g_source_remove(g_delayed_destroys_id);
	g_delayed_destroys_id = 0;
  }
  return FALSE;
}
