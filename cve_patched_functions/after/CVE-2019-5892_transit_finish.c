static void transit_finish(void)
{
	hash_clean(transit_hash, (void (*)(void *))transit_free);
	hash_free(transit_hash);
	transit_hash = NULL;
}
