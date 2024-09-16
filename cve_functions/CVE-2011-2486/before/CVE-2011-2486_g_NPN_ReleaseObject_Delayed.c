g_NPN_ReleaseObject_Delayed(NPObject *npobj)
{
  delayed_calls_add(RPC_DELAYED_NPN_RELEASE_OBJECT, npobj);
}
