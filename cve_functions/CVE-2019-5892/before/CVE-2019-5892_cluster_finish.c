static void cluster_finish(void)
{
	hash_clean(cluster_hash, (void (*)(void *))cluster_free);
	hash_free(cluster_hash);
	cluster_hash = NULL;
}
