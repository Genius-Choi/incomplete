g_NP_Shutdown(void)
{
  if (g_plugin_NP_Shutdown == NULL)
	return NPERR_INVALID_FUNCTABLE_ERROR;

  D(bugiI("NP_Shutdown\n"));
  NPError ret = g_plugin_NP_Shutdown();
  D(bugiD("NP_Shutdown done\n"));

  if (NPN_HAS_FEATURE(NPRUNTIME_SCRIPTING))
	npobject_bridge_destroy();

  gtk_main_quit();

  return ret;
}
