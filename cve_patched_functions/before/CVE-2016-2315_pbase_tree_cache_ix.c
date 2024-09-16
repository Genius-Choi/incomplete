static int pbase_tree_cache_ix(const unsigned char *sha1)
{
	return sha1[0] % ARRAY_SIZE(pbase_tree_cache);
}
