static inline bool npidentifier_cache_has_string(const gchar *str, NPIdentifier *pident)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	return false;

  NPIdentifierFindArgs args;
  args.info.string_len = strlen(str) + 1;
  args.info.u.string = (gchar *)str;
  return npidentifier_cache_find(&args, pident);
}
