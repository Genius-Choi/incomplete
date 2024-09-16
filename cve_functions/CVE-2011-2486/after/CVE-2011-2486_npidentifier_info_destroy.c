static inline void npidentifier_info_destroy(NPIdentifierInfo *npi)
{
  if (G_UNLIKELY(npi == NULL))
	return;
  if (npi->string_len > 0) {
	NPW_MemFree(npi->u.string);
	npi->u.string = NULL;
  }
  NPW_MemFree(npi);
}
