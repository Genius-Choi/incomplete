bool id_remove(int id)
{
  return g_hash_table_remove(g_ids, id_key(id));
}
