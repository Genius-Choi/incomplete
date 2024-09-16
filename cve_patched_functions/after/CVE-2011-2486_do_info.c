static int do_info(void)
{
  if (do_test() != 0)
	return 1;
  const char *plugin_name = NULL;
  if (g_NP_GetValue(NPPVpluginNameString, &plugin_name) == NPERR_NO_ERROR && plugin_name)
	printf("PLUGIN_NAME %zd\n%s\n", strlen(plugin_name), plugin_name);
  const char *plugin_desc = NULL;
  if (g_NP_GetValue(NPPVpluginDescriptionString, &plugin_desc) == NPERR_NO_ERROR && plugin_desc)
	printf("PLUGIN_DESC %zd\n%s\n", strlen(plugin_desc), plugin_desc);
  const char *mime_info = g_NP_GetMIMEDescription();
  if (mime_info)
	printf("PLUGIN_MIME %zd\n%s\n", strlen(mime_info), mime_info);
  return 0;
}
