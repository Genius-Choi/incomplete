cached_NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
  NPUTF8 *str;
  if (!use_npidentifier_cache())
	str = invoke_NPN_UTF8FromIdentifier(identifier);
  else {
#if USE_NPIDENTIFIER_CACHE
	str = npidentifier_cache_get_string_copy(identifier);
	if (str == NULL) {
	  str = invoke_NPN_UTF8FromIdentifier(identifier);
	  npidentifier_cache_reserve(1);
	  npidentifier_cache_add_string(identifier, str);
	}
#endif
  }
  return str;
}
