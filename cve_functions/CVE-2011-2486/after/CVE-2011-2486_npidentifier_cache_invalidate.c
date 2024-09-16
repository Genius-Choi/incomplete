static void npidentifier_cache_invalidate(void)
{
#if defined(HAVE_G_HASH_TABLE_REMOVE_ALL) && !defined(BUILD_GENERIC)
  if (g_npidentifier_cache)
	g_hash_table_remove_all(g_npidentifier_cache);
#else
  npidentifier_cache_destroy();
  npidentifier_cache_create();
#endif
}
