g_NPN_UserAgent(NPP instance)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_UserAgent not called from the main thread\n");
	return NULL;
  }

  D(bugiI("NPN_UserAgent instance=%p\n", instance));
  if (g_user_agent == NULL)
	g_user_agent = invoke_NPN_UserAgent();
  D(bugiD("NPN_UserAgent return: '%s'\n", g_user_agent));
  return g_user_agent;
}
