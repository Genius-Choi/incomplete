static int is_flash_player9_beta1(void)
{
  const char *plugin_desc = NULL;
  if (g_NP_GetValue(NPPVpluginDescriptionString, &plugin_desc) == NPERR_NO_ERROR
	  && plugin_desc && strcmp(plugin_desc, "Shockwave Flash 9.0 d55") == 0) {
	npw_printf("WARNING: Flash Player 9 beta 1 detected and rejected\n");
	return 1;
  }
  return 0;
}
