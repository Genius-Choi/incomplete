static inline bool npidentifier_cache_has_int(int32_t value, NPIdentifier *pident)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	return false;

  NPIdentifierFindArgs args;
  args.info.string_len = 0;
  args.info.u.value = value;
  return npidentifier_cache_find(&args, pident);
}
