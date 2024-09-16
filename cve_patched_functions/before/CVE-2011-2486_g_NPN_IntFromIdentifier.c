g_NPN_IntFromIdentifier(NPIdentifier identifier)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_IntFromIdentifier not called from the main thread\n");
	return 0;
  }
  
  D(bugiI("NPN_IntFromIdentifier identifier=%p\n", identifier));
  int32_t ret = cached_NPN_IntFromIdentifier(identifier);
  D(bugiD("NPN_IntFromIdentifier return: %d\n", ret));
  return ret;
}
