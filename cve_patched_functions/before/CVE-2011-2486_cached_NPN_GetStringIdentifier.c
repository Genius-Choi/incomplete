cached_NPN_GetStringIdentifier(const NPUTF8 *name)
{
  NPIdentifier ident;
  if (!use_npidentifier_cache())
	ident = invoke_NPN_GetStringIdentifier(name);
#if USE_NPIDENTIFIER_CACHE
  else if (!npidentifier_cache_has_string(name, &ident)) {
	ident = invoke_NPN_GetStringIdentifier(name);
	npidentifier_cache_reserve(1);
	npidentifier_cache_add_string(ident, name);
  }
#endif
  return ident;
}
