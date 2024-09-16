void *jas_mb_get_data(jas_mb_t *mb)
{
	return JAS_CAST(void *, JAS_CAST(max_align_t *, mb) + JAS_MB_ADJUST);
}
