static inline NPIdentifierInfo *npidentifier_cache_lookup(NPIdentifier ident)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	return NULL;
  return g_hash_table_lookup(g_npidentifier_cache, ident);
}
