g_NP_GetMIMEDescription(void)
{
  if (g_plugin_NP_GetMIMEDescription == NULL)
	return NULL;

  D(bugiI("NP_GetMIMEDescription\n"));
  char *str = g_plugin_NP_GetMIMEDescription();
  D(bugiD("NP_GetMIMEDescription return: %s\n", str ? str : "<empty>"));
  return str;
}
