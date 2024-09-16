bool id_init(void)
{
  if (g_ids == NULL)
	g_ids = g_hash_table_new(NULL, NULL);
  return g_ids != NULL;
}
