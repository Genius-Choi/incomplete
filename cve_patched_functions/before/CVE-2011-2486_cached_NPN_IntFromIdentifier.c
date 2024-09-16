cached_NPN_IntFromIdentifier(NPIdentifier identifier)
{
  int32_t value;
  if (!use_npidentifier_cache())
	value = invoke_NPN_IntFromIdentifier(identifier);
  else {
#if USE_NPIDENTIFIER_CACHE
	NPIdentifierInfo *npi = npidentifier_cache_lookup(identifier);
	if (npi) {
	  assert(npi->string_len == 0);
	  value = npi->u.value;
	}
	else {
	  value = invoke_NPN_IntFromIdentifier(identifier);
	  npidentifier_cache_reserve(1);
	  npidentifier_cache_add_int(identifier, value);
	}
#endif
  }
  return value;
}
