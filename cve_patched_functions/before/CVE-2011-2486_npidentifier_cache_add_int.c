static void npidentifier_cache_add_int(NPIdentifier ident, int32_t value)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	return;
  NPIdentifierInfo *npi = npidentifier_info_new();
  if (G_UNLIKELY(npi == NULL))
	return;
  npi->string_len = 0;
  npi->u.value = value;
  g_hash_table_insert(g_npidentifier_cache, ident, npi);
}
