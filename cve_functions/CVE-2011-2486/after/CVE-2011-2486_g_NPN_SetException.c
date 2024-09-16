g_NPN_SetException(NPObject *npobj, const NPUTF8 *message)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_SetException not called from the main thread\n");
	return;
  }

  D(bugiI("NPN_SetException npobj=%p, message='%s'\n", npobj, message));
  invoke_NPN_SetException(npobj, message);
  D(bugiD("NPN_SetException done\n"));
}
