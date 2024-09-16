static inline void npidentifier_cache_destroy(void)
{
  if (g_npidentifier_cache) {
	g_hash_table_destroy(g_npidentifier_cache);
	g_npidentifier_cache = NULL;
  }
}
