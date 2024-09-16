static struct alien_cache *__alloc_alien_cache(int node, int entries,
						int batch, gfp_t gfp)
{
	size_t memsize = sizeof(void *) * entries + sizeof(struct alien_cache);
	struct alien_cache *alc = NULL;

	alc = kmalloc_node(memsize, gfp, node);
	init_arraycache(&alc->ac, entries, batch);
	spin_lock_init(&alc->lock);
	return alc;
}
