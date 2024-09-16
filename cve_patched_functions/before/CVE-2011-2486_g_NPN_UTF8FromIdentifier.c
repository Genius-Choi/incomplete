g_NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_UTF8FromIdentifier not called from the main thread\n");
	return NULL;
  }

  D(bugiI("NPN_UTF8FromIdentifier identifier=%p\n", identifier));
  NPUTF8 *ret = cached_NPN_UTF8FromIdentifier(identifier);
  D(bugiD("NPN_UTF8FromIdentifier return: '%s'\n", ret));
  return ret;
}
