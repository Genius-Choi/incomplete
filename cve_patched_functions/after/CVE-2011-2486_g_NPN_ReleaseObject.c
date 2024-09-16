g_NPN_ReleaseObject(NPObject *npobj)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_ReleaseObject not called from the main thread\n");
	return;
  }
	
  if (npobj == NULL)
	return;

  if (rpc_method_invoke_possible(g_rpc_connection)) {
	D(bug("NPN_ReleaseObject <now>\n"));
	g_NPN_ReleaseObject_Now(npobj);
  }
  else {
	D(bug("NPN_ReleaseObject <delayed>\n"));
	g_NPN_ReleaseObject_Delayed(npobj);
  }
}
