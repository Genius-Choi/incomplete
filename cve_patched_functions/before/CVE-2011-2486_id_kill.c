void id_kill(void)
{
  if (g_ids) {
	g_hash_table_destroy(g_ids);
	g_ids = NULL;
  }
}
