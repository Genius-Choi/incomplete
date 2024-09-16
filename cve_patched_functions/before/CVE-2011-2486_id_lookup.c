void *id_lookup(int id)
{
  return g_hash_table_lookup(g_ids, id_key(id));
}
