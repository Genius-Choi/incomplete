static void reap_alien(struct kmem_cache *cachep, struct kmem_cache_node *n)
{
	int node = __this_cpu_read(slab_reap_node);

	if (n->alien) {
		struct alien_cache *alc = n->alien[node];
		struct array_cache *ac;

		if (alc) {
			ac = &alc->ac;
			if (ac->avail && spin_trylock_irq(&alc->lock)) {
				LIST_HEAD(list);

				__drain_alien_cache(cachep, ac, node, &list);
				spin_unlock_irq(&alc->lock);
				slabs_destroy(cachep, &list);
			}
		}
	}
}
