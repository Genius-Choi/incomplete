static void npidentifier_cache_add_string(NPIdentifier ident, const gchar *str)
{
  if (G_UNLIKELY(g_npidentifier_cache == NULL))
	return;
  NPIdentifierInfo *npi = npidentifier_info_new();
  if (G_UNLIKELY(npi == NULL))
	return;
  npi->string_len = strlen(str) + 1;
  if ((npi->u.string = NPW_MemAlloc(npi->string_len)) == NULL) {
	npidentifier_info_destroy(npi);
	return;
  }
  memcpy(npi->u.string, str, npi->string_len);
  g_hash_table_insert(g_npidentifier_cache, ident, npi);
}
