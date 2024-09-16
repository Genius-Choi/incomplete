g_NPN_ReleaseObject_Now(NPObject *npobj)
{
  D(bugiI("NPN_ReleaseObject npobj=%p\n", npobj));
  uint32_t refcount = invoke_NPN_ReleaseObject(npobj);
  D(bugiD("NPN_ReleaseObject done (refcount: %d)\n", refcount));

  if ((npobj->referenceCount = refcount) == 0)
	npobject_destroy(npobj);
}
