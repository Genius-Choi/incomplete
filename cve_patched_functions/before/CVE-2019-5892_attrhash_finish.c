static void attrhash_finish(void)
{
	hash_clean(attrhash, attr_vfree);
	hash_free(attrhash);
	attrhash = NULL;
}
