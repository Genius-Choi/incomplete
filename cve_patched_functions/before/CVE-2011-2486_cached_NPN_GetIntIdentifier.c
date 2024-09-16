cached_NPN_GetIntIdentifier(int32_t intid)
{
  NPIdentifier ident;
  if (!use_npidentifier_cache())
	ident = invoke_NPN_GetIntIdentifier(intid);
#if USE_NPIDENTIFIER_CACHE
  else if (!npidentifier_cache_has_int(intid, &ident)) {
	ident = invoke_NPN_GetIntIdentifier(intid);
	npidentifier_cache_reserve(1);
	npidentifier_cache_add_int(ident, intid);
  }
#endif
  return ident;
}
