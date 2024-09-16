static inline bool npidentifier_cache_find(NPIdentifierFindArgs *args, NPIdentifier *pident)
{
  args->ident = NULL;
#if defined(HAVE_G_HASH_TABLE_FIND) && !defined(BUILD_GENERIC)
  if (!g_hash_table_find(g_npidentifier_cache, npidentifier_cache_find_info, args))
	return false;
#else
  g_hash_table_foreach(g_npidentifier_cache, (GHFunc)npidentifier_cache_find_info, args);
  if (args->ident == NULL)
	return false;
#endif

  if (pident)
	*pident = args->ident;
  return true;
}
