static void npidentifier_cache_reserve(int n_entries)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	npidentifier_cache_create();
  if (g_hash_table_size(g_npidentifier_cache) + n_entries > NPIDENTIFIER_CACHE_SIZE)
	npidentifier_cache_invalidate();
}
