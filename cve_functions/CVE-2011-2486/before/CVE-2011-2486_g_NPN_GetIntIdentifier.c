g_NPN_GetIntIdentifier(int32_t intid)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetIntIdentifier not called from the main thread\n");
	return NULL;
  }

  D(bugiI("NPN_GetIntIdentifier intid=%d\n", intid));
  NPIdentifier ret = cached_NPN_GetIntIdentifier(intid);
  D(bugiD("NPN_GetIntIdentifier return: %p\n", ret));
  return ret;
}
